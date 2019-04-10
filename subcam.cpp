#include "subcam.h"

#include <QDebug>

#include "godzilla.h"

#define _USE_MATH_DEFINES
#include <math.h>

SubCam::SubCam(QObject *parent, const QString dest) : QObject (parent)
{
    _tcp = new TcpSender(this, dest);
}

/*          recvMainCamData
 * @param   mainCam MainCamのレンズ情報
 */
void SubCam::recvMainCamData(LensInfo mainCam, Location TagetPosi)
{
    _mainCam = mainCam;
    _TargetPosi = TagetPosi;

    if(!calcSubCamPosi()) {
        qDebug() << "Can't Calculate the Subcam Position.";
    }

    if(!calcSubCamAngle()) {
        qDebug() << "Can't Calculate the Angle.";
    }

    if(!calcSubCamPTZ()) {
        qDebug() << "Can't Calculate the PTZ Value.";
    }

    QByteArray tmp = createCmdString(); // テスト用 // 削除予定
    _tcp -> sendData(tmp); // テスト用 // 削除予定

}

/*          calcSubCamAngle
 * @brief   MainCamのPTZ値、被写体との距離からSubCamの角度を算出
 * @param
 * @return  正常終了 true, 異常終了 false
 */
bool SubCam::calcSubCamPosi()
{
    _SubcamPosi.x = 0;//本来はキャリブレーションで求める
    _SubcamPosi.y = 1;
    _SubcamPosi.z = 0;
    _SubcamPosi.angle = 0;
    return true;
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
    temppan = atan((_TargetPosi.y - _SubcamPosi.y)/(_TargetPosi.x - _SubcamPosi.x));
    if(_TargetPosi.x >= _SubcamPosi.x){
        _subCam.pan = 180/M_PI*temppan;
    }else{
        if(temppan>=0){
            _subCam.pan = 180/M_PI*temppan - 180;
        }else{
            _subCam.pan = 180/M_PI*temppan + 180;
        }
    }
    _subCam.pan = _subCam.pan - _SubcamPosi.angle;
    //tiltの計算
    temptilt = atan((_TargetPosi.z - _SubcamPosi.z)/sqrt(pow(_TargetPosi.y - _SubcamPosi.y, 2)+pow(_TargetPosi.x - _SubcamPosi.x, 2)));
    _subCam.tilt = 180/M_PI*temptilt;
/*    if( _TargetPosi.x >= _SubcamPosi.x ){//Todo:1対1対応しない問題
        _subCam.tilt = 180/M_PI*temptilt;
    }else{
        _subCam.tilt = 180/M_PI*temptilt + 180;
    }*/
    qDebug() << "rad(pan):" << _subCam.pan;
    qDebug() << "rad(tilt):" << _subCam.tilt;
    return true;
}

/*          calcSubCamPTZ
 * @brief   角度からSubCamのPTZ値を算出
 * @param
 * @return  正常終了 true, 異常終了 false
 */
bool SubCam::calcSubCamPTZ()
{
    _subcam_AWpan = static_cast<unsigned int>((0xF8D4-(_subCam.pan+175)*182)/0xF8D4*0xA5EC+0x2D09);//ToDo:計算式再確認
    _subcam_AWtilt = static_cast<unsigned int>((0xAAA0-(_subCam.tilt+30)*182)/0xAAA0*0x71C7+0x1C71);//ToDo:計算式再確認
    return true;
}

/*          createCmdString
 * @brief   SubCamに送信するAWコマンドの文字列を生成
 * @param
 * @return 　コマンドの文字列（/cgi-bin/xxx&res=1のxxxの部分）
 */QByteArray SubCam::createCmdString()
{
    QByteArray temp1, temp2, temp3, temp4;
    temp1 = "aw_ptz?cmd=%23APC";
    if(!num2ascii( _subcam_AWpan, temp2, 4 )){
        qDebug() << "ASCII Exchange Error";
    }
    if(!num2ascii( _subcam_AWtilt, temp3, 4 )){
        qDebug() << "ASCII Exchange Error";
    }
    temp4 = "&res=1";
    qDebug() << temp1 << temp2 << temp3 << temp4;
    return temp1 + temp2 + temp3 + temp4;
//    return "aw_ptz?cmd=%23APC80008000&res=1"; // テスト用
}

bool SubCam::num2ascii(unsigned int num, QByteArray &array, int length){
    int i;
    unsigned int temp;
    for( i=length; i>0; i-- ){
        temp = num & 0x000F;
        num >>= 4;
        if( temp <= 9 ){
            array[i-1] = char(temp + '0');
        }else{
            array[i-1] = char(temp - 10 + 'A');
        }
    }
    return true;
}
