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

    bool parseUpdateNotice(QByteArray recvData);
    bool calcDistFromFucus();

};

#endif // GODZILLA_H
