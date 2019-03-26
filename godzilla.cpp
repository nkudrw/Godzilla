#include "godzilla.h"

#include <QDebug>

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

    if(!calcDistFromFucus()) {
        qDebug() << "Can't Calculate the Distance from Focus Value.";
    }

    for(int i = 0; i < _subcam.size(); ++i) {
        _subcam[i] -> recvMainCamData(_lensInfo);
    }
}

/*          parseUpdateNotice
 * @brief   更新通知の解析（文字列の解析と、データ変換）
 * @param   recvData MainCamの更新通知データ（解析前）
 * @return  正常終了 true, 異常終了 false
 */
bool Godzilla::parseUpdateNotice(QByteArray recvData)
{
    return true;
}

/*          parseUpdateNotice
 * @brief   Focus値から距離を算出(メートル)
 * @param
 * @return  正常終了 true, 異常終了 false
 */
bool Godzilla::calcDistFromFucus()
{
    return true;
}
