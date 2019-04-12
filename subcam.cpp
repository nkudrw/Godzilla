#include "subcam.h"

#include <QDebug>

#include "godzilla.h"

#define _USE_MATH_DEFINES

#include <math.h>

SubCam::SubCam(QObject *parent, const QString dest, double x, double y, double z, double angle) : QObject (parent)
{
    _tcp = new TcpSender(this, dest);
    setSubCamPosi(x, y, z, angle);
}

/*          getSubCamLensInfo
 * @brief   SubCamの現在のLensInfo（PTZF）のGetter
 */
LensInfo SubCam::getSubCamLensInfo()
{
    return _subCamLensInfo;
}

/*          getSubCamLensInfo
 * @brief   SubCamの現在のLensInfo（PTZF）のGetter
 * @param   x SubCamの位置　x座標
 * @param   y SubCamの位置　y座標
 * @param   z SubCamの位置　z座標
 * @param   angle SubCamのカメラ自体の角度
 */
void SubCam::setSubCamPosi(double x, double y, double z, double angle)
{
    _subCamPosi.x = x;
    _subCamPosi.y = y;
    _subCamPosi.z = z;
    _subCamPosi.angle = angle;
    return;
}

/*          recvMainCamData
 * @param   mainCam MainCamのレンズ情報
 */
void SubCam::recvMainCamData(LensInfo mainCam, Location TargetPosi)
{
    QByteArray tmp;
    _mainCamLensInfo = mainCam;
    _targetPosi = TargetPosi;

    if(!calcSubCamAngle()) {
        qDebug() << "Can't Calculate the Angle.";
    }

    if(!calcSubCamPTZ()) {
        qDebug() << "Can't Calculate the PTZ Value.";
    }

    tmp = createCmdStrAPC();
    _tcp -> sendData(tmp);

    tmp = createCmdStrAXZ();
    _tcp -> sendData(tmp);
}

/*          calcSubCamAngle
 * @brief   MainCamのPTZ値、被写体との距離からSubCamの角度を算出
 * @param
 * @return  正常終了 true, 異常終了 false
 */
bool SubCam::calcSubCamAngle()
{
    double temppan, temptilt;
    //panの計算
    temppan = atan((_targetPosi.y - _subCamPosi.y)/(_targetPosi.x - _subCamPosi.x));
    if(_targetPosi.x >= _subCamPosi.x){
        _subCamLensInfo.pan = 180/M_PI*temppan;
    }else{
        if(temppan>=0){
            _subCamLensInfo.pan = 180/M_PI*temppan - 180;
        }else{
            _subCamLensInfo.pan = 180/M_PI*temppan + 180;
        }
    }
    _subCamLensInfo.pan = _subCamLensInfo.pan - _subCamPosi.angle;
    if( _subCamLensInfo.pan > 180 ){
        _subCamLensInfo.pan = _subCamLensInfo.pan - 360;
    }else if( _subCamLensInfo.pan < -180 ){
        _subCamLensInfo.pan = _subCamLensInfo.pan + 360;
	}
    //tiltの計算
    temptilt = atan((_targetPosi.z - _subCamPosi.z)/sqrt(pow(_targetPosi.y - _subCamPosi.y, 2)+pow(_targetPosi.x - _subCamPosi.x, 2)));
    _subCamLensInfo.tilt = 180/M_PI*temptilt;
/*    if( _targetPosi.x >= _subCamPosi.x ){//Todo:1対1対応しない問題
        _subCamLensInfo.tilt = 180/M_PI*temptilt;
    }else{
        _subCamLensInfo.tilt = 180/M_PI*temptilt + 180;
    }*/

    //画角の計算
    double len_subcam_taget;
    len_subcam_taget = sqrt(pow(_targetPosi.y - _subCamPosi.y, 2)+pow(_targetPosi.x - _subCamPosi.x, 2)+pow(_targetPosi.z - _subCamPosi.z, 2));
    _subCamLensInfo.zoom = 180/M_PI*(2*asin(_mainCamLensInfo.focus * sin(_mainCamLensInfo.zoom/180*M_PI/2) / len_subcam_taget));

    qDebug() << "rad(pan):" << _subCamLensInfo.pan;
    qDebug() << "rad(tilt):" << _subCamLensInfo.tilt;
    qDebug() << "rad(zoom):" << _subCamLensInfo.zoom;
    return true;
}

/*          calcSubCamPTZ
 * @brief   角度からSubCamのPTZ値を算出
 * @param
 * @return  正常終了 true, 異常終了 false
 */
bool SubCam::calcSubCamPTZ()
{
    _subCam_AWpan = static_cast<unsigned short>((0xF8D4-(_subCamLensInfo.pan+175)*182)/0xF8D4*0xA5EC+0x2D09);//UE150の計算式
    _subCam_AWtilt = static_cast<unsigned short>((0xAAA0-(_subCamLensInfo.tilt+30)*182)/0xAAA0*0x71C7+0x1C71);//UE150の計算式
    for(int cnt=0; cnt<ZOOM_TABLE_SIZE; cnt++){
        if( table_Zoom_Angle[cnt][1] <= _subCamLensInfo.zoom ){
            _subCam_AWzoom =static_cast<unsigned short>(table_Zoom_Angle[cnt][0]);
            break;
        }else if( _subCamLensInfo.zoom <= table_Zoom_Angle[ZOOM_TABLE_SIZE-1][1]){
            _subCam_AWzoom = 0xFFF;
        }
    }

    return true;
}

/*          createCmdStrAPC
 * @brief   SubCamに送信するAWコマンドの文字列を生成
 * @param
 * @return 　コマンドの文字列（/cgi-bin/xxx&res=1のxxxの部分）
 */QByteArray SubCam::createCmdStrAPC()
{
    QByteArray temp1, temp2, temp3, temp4;
    temp1 = "aw_ptz?cmd=%23APC";
    if(!num2ascii( _subCam_AWpan, temp2, 4 )){
        qDebug() << "ASCII Exchange Error";
    }
    if(!num2ascii( _subCam_AWtilt, temp3, 4 )){
        qDebug() << "ASCII Exchange Error";
    }
    temp4 = "&res=1";
//    qDebug() << temp1 << temp2 << temp3 << temp4;
    return temp1 + temp2 + temp3 + temp4;
//    return "aw_ptz?cmd=%23APC80008000&res=1"; // テスト用
}

/*          createCmdStrAXZ
 * @brief   SubCamに送信するAWコマンドの文字列を生成
 * @param
 * @return 　コマンドの文字列（/cgi-bin/xxx&res=1のxxxの部分）
 */QByteArray SubCam::createCmdStrAXZ()
{
    QByteArray temp1, temp2, temp3;
    temp1 = "aw_ptz?cmd=%23AXZ";
    if(!num2ascii( _subCam_AWzoom, temp2, 3 )){
        qDebug() << "ASCII Exchange Error";
    }
    temp3 = "&res=1";
//    qDebug() << temp1 << temp2 << temp3;
    return temp1 + temp2 + temp3;
//    return "aw_ptz?cmd=%23AXZ555&res=1"; // テスト用
}


/*          num2ascii
 * @brief   16進数をchar型に変換
 * @param
 * @return  正常終了 true, 異常終了 false
 */
bool SubCam::num2ascii(unsigned int num, QByteArray &array, int length){
    int i;
    unsigned int temp;
    for( i=length; i>0; i-- ){
        temp = num & 0x000F;
        num >>= 4;
        if( temp <= 9 ){
            array[i-1] = char(temp + '0');//0～9
        }else{
            array[i-1] = char(temp - 10 + 'A');//A～F
        }
    }
    return true;
}
