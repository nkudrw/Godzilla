#include "subcam.h"

#include <QDebug>

#include "godzilla.h"

SubCam::SubCam(QObject *parent, const QString dest) : QObject (parent)
{
    _tcp = new TcpSender(this, dest);
    _tcp->doConnect();
}

/*          recvMainCamData
 * @param   mainCam MainCamのレンズ情報
 */
void SubCam::recvMainCamData(LensInfo mainCam)
{
    _mainCam = mainCam;

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
bool SubCam::calcSubCamAngle()
{
    return true;
}

/*          calcSubCamPTZ
 * @brief   角度からSubCamのPTZ値を算出
 * @param
 * @return  正常終了 true, 異常終了 false
 */
bool SubCam::calcSubCamPTZ()
{
    return true;
}

/*          createCmdString
 * @brief   SubCamに送信するAWコマンドの文字列を生成
 * @param
 * @return 　コマンドの文字列（/cgi-bin/xxx&res=1のxxxの部分）
 */QByteArray SubCam::createCmdString()
{
    return "ndi_hx_support"; // テスト用
}

