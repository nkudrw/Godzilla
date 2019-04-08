#ifndef GODZILLA_H
#define GODZILLA_H

#include <QObject>
#include <QVector>

#include "godtypedef.h"
#include "udpreciever.h"
#include "subcam.h"

class Godzilla : public QObject
{
    Q_OBJECT
public:
    explicit Godzilla(QObject *parent = nullptr);
    void createUdpSocket(const quint16 port = 1234);
    void addSubCam(const QString ipaddr);
    void recvUpdateNotice(QByteArray recvData);

private:
    QByteArray _mainCamPTZData; // 受信したMainCamのPTZデータ
    UdpReciever *_udp;
    QVector<SubCam*> _subcam;
    LensInfo   _lensInfo;
    Location   _TargetPosi;

    bool parseUpdateNotice(QByteArray recvData);
    bool calcDistFromFucus(unsigned short awFocus);
    bool calcTargetPosi();

};

/* C101用被写体距離テーブル*/
#define TABLE_FOCUST_DIST_MAX_C101	19
const unsigned short table_FocusDist_C101[TABLE_FOCUST_DIST_MAX_C101][2] = 
{
/* 	FOCUS値,	被写体距離[mm]	*/
	{0x555,		30},		/* 1	*/
	{0x555,		50},		/* 2	*/
	{0x782,		400},		/* 3	*/
	{0x977,		950},		/* 4	*/
	{0x9AF,		1000},		/* 5	*/
	{0x9E7,		1050},		/* 6	*/
	{0xA43,		1150},		/* 7	*/
	{0xAB3,		1300},		/* 8	*/
	{0xB35,		1500},		/* 9	*/
	{0xBA4,		1700},		/* 10	*/
	{0xC39,		2000},		/* 11	*/
	{0xCCD,		2500},		/* 12	*/
	{0xD3D,		3000},		/* 13	*/
	{0xDF7,		4200},		/* 14	*/
	{0xE8B,		6250},		/* 15	*/
	{0xF20,		12500},		/* 16	*/
	{0xFB4,		35000},		/* 17	*/
	{0xFFF,		50000}		/* 18	*/

};


#endif // GODZILLA_H
