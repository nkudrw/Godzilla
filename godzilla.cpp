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
Q_INVOKABLE void Godzilla::createUdpSocket(const quint16 port)
{
    _udp = new UdpReciever(this, port);
    _udp -> sendDummyData(); // テスト用関数 ダミーの更新通知を送信　カメラ未接続の状態でテストする場合に使用
    qDebug() << "port="<<port;
}

/*          addSubCam
 * @param   ipaddr 追加するSubCamのIPアドレス
 */
Q_INVOKABLE void Godzilla::addSubCam(const QString ipaddr)
{
    _subcam.append(new SubCam(this, ipaddr));
    qDebug() << "ip="<<ipaddr;
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
    int temp_pan, temp_tilt, temp_zoom;
    unsigned short temp_focus;
//    _lensInfo.pan = (int(recvData[2])<<16) + 0x0000FF00&(recvData[3]<<8) + recvData[4];
    temp_pan = static_cast<int>((recvData[2]<<16) | (0x0000FF00&(recvData[3]<<8)) | (0x000000FF&(recvData[4])));
    temp_tilt = static_cast<int>((recvData[5]<<16) | (0x0000FF00&(recvData[6]<<8)) | (0x000000FF&(recvData[7])));
    temp_zoom = static_cast<int>((recvData[20]<<16) | (0x0000FF00&(recvData[21]<<8)) | (0x000000FF&(recvData[22])));
    temp_focus = static_cast<unsigned short>((recvData[23]<<16) | (0x0000FF00&(recvData[24]<<8)) | (0x000000FF&(recvData[25])));
    _lensInfo.iris = static_cast<int>((0x0000FF00&(recvData[26]<<8)) | (0x000000FF&(recvData[27])));//とりあえず使わないので放置

    _lensInfo.pan = double(temp_pan)/0x00008000;//Free-Dの値を角度(°)へ変換
    _lensInfo.tilt = double(temp_tilt)/0x00008000;//Free-Dの値を角度(°)へ変換
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
 * @brief   Focus値から距離を算出(ミリメートル)
 * @param	フォーカンス値(0x555～0xFFF)
 * @return  正常終了 true, 異常終了 false
 */
bool Godzilla::calcDistFromFucus(unsigned short awFocus)
{
	unsigned short	dist_ret;
	unsigned short	dist_tbl, focus_tbl;
	unsigned short	dist_tbl_next, focus_tbl_next;
	unsigned char	cnt;
    unsigned char	cnt_approx = 0;
	const unsigned char	cnt_max = TABLE_FOCUST_DIST_MAX_C101;
	
	/* テーブル内の近似値を検索		*/
	for(cnt = 0; cnt < cnt_max; cnt++){
		focus_tbl		= table_FocusDist_C101[cnt][0];
		if(focus_tbl > awFocus){
			cnt_approx	= cnt;
			break;
		}
	}
	
	focus_tbl		= table_FocusDist_C101[cnt_approx][0];
	dist_tbl		= table_FocusDist_C101[cnt_approx][1];
	focus_tbl_next	= table_FocusDist_C101[cnt_approx+1][0];
	dist_tbl_next	= table_FocusDist_C101[cnt_approx+1][1];
	
	/* 被写体距離の線形補間計算	*/
	dist_ret	= dist_tbl + (dist_tbl_next - dist_tbl) * (awFocus - focus_tbl) / (focus_tbl_next - focus_tbl);
	
    _lensInfo.focus	= double(dist_ret);
    return true;
}

/*          parseUpdateNotice
 * @brief   Focus値から距離を算出(ミリメートル)
 * @param
 * @return  正常終了 true, 異常終了 false
 */
bool Godzilla::calcTargetPosi()
{
    _TargetPosi.x = _lensInfo.focus * cos(_lensInfo.tilt/180*M_PI) * cos(_lensInfo.pan/180*M_PI);
    _TargetPosi.y = _lensInfo.focus * cos(_lensInfo.tilt/180*M_PI) * sin(_lensInfo.pan/180*M_PI);
    _TargetPosi.z = _lensInfo.focus * sin(_lensInfo.tilt/180*M_PI);
    qDebug() << "Yposi:" << _TargetPosi.y;
    qDebug() << "Zposi:" << _TargetPosi.z;
    return true;
}
