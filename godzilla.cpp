#include "godzilla.h"

#include <QDebug>

#define _USE_MATH_DEFINES
#include <math.h>


/*          コンストラクタ
 */
Godzilla::Godzilla(QObject *parent) : QObject(parent)
{
    _mainCamPTZData.clear();
    _subcam.clear();
}

/*          createUdpSocket
 * @param   更新通知の受信ポート番号
 */
void Godzilla::createUdpSocket(const quint16 port)
{
    _udp = new UdpReciever(this, port);
    _udp -> sendDummyData(); // テスト用関数 //削除予定

}

/*          addSubCam
 * @param   ipaddr 追加するSubCamのIPアドレス
 */
void Godzilla::addSubCam(const QString ipaddr)
{
    _subcam.append(new SubCam(this, ipaddr));
}

/*          recvUpdateNotice
 * @param   recvData MainCamの更新通知データ（解析前）
 */
void Godzilla::recvUpdateNotice(QByteArray recvData)
{
    _mainCamPTZData = recvData;
    qDebug() << "mainCamPTZData" << _mainCamPTZData.toHex(0);

    if(!parseUpdateNotice(recvData)) {
        qDebug() << "Update Notice is Invalid.";
    }

    if(!calcTargetPosi()) {
        qDebug() << "Can't Calculate the Target Position.";
    }

    for(int i = 0; i < _subcam.size(); ++i) {
        _subcam[i] -> recvMainCamData(_lensInfo, _TargetPosi);
    }
}

/*          parseUpdateNotice
 * @brief   更新通知の解析（文字列の解析と、データ変換）
 * @param   recvData MainCamの更新通知データ（解析前）
 * @return  正常終了 true, 異常終了 false
 */
bool Godzilla::parseUpdateNotice(QByteArray recvData)
{
    int temp_pan, temp_tilt, temp_zoom, temp_focus;
//    _lensInfo.pan = (int(recvData[2])<<16) + 0x0000FF00&(recvData[3]<<8) + recvData[4];
    temp_pan = static_cast<int>((recvData[2]<<16) | (0x0000FF00&(recvData[3]<<8)) | (0x000000FF&(recvData[4])));
    temp_tilt = static_cast<int>((recvData[5]<<16) | (0x0000FF00&(recvData[6]<<8)) | (0x000000FF&(recvData[7])));
    temp_zoom = static_cast<int>((recvData[20]<<16) | (0x0000FF00&(recvData[21]<<8)) | (0x000000FF&(recvData[22])));
    temp_focus = static_cast<int>((recvData[23]<<16) | (0x0000FF00&(recvData[24]<<8)) | (0x000000FF&(recvData[25])));
    _lensInfo.iris = static_cast<int>((0x0000FF00&(recvData[26]<<8)) | (0x000000FF&(recvData[27])));//とりあえず使わないので放置

    _lensInfo.pan = double(temp_pan)/0x00008000;
    _lensInfo.tilt = double(temp_tilt)/0x00008000;
    _lensInfo.zoom = temp_zoom;//とりあえず使わないので放置


    if(!calcDistFromFucus( temp_focus )) {
        qDebug() << "Can't Calculate the Distance from Focus Value.";
    }

    qDebug() << "Temp_pan:" << temp_pan;
    qDebug() << "Temp_tilt:" << temp_tilt;
    qDebug() << "pan:" << _lensInfo.pan;
    qDebug() << "tilt:" << _lensInfo.tilt;
    qDebug() << "zoom:" << _lensInfo.zoom;
    qDebug() << "focus:" << _lensInfo.focus;
    qDebug() << "iris:" << _lensInfo.iris;
    return true;
}

/*          parseUpdateNotice
 * @brief   Focus値から距離を算出(メートル)
 * @param
 * @return  正常終了 true, 異常終了 false
 */
bool Godzilla::calcDistFromFucus(int awFocus)
{
    _lensInfo.focus = 2;//AWコマンドで扱われている0x555～0xFFFの値を[m(メートル)]へ変換お願いします
    return true;
}

/*          parseUpdateNotice
 * @brief   Focus値から距離を算出(メートル)
 * @param
 * @return  正常終了 true, 異常終了 false
 */
bool Godzilla::calcTargetPosi()
{
    _TargetPosi.x = _lensInfo.focus * cos(_lensInfo.pan/180*M_PI);
    _TargetPosi.y = _lensInfo.focus * sin(_lensInfo.pan/180*M_PI);
    _TargetPosi.z = _lensInfo.focus * sin(_lensInfo.tilt/180*M_PI);
    qDebug() << "Yposi:" << _TargetPosi.y;
    return true;
}
