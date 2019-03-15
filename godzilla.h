#ifndef GODZILLA_H
#define GODZILLA_H

#include <QObject>
#include <QVector>

//class UdpReciever;

#include "udpreciever.h"
#include "tcpsender.h"

class Godzilla : public QObject
{
    Q_OBJECT
public:
    explicit Godzilla(QObject *parent = nullptr);
    void createUdpSocket(const quint16 port = 1234);
    void createTcpSocket(const QString dest);

signals:
    void recvDataSignal(QByteArray recvData);

public slots:
    void emitRecvDataSignal(QByteArray recvData)
    {
        emit recvDataSignal(recvData);
    }

    void calcSubCamPTZData(QByteArray recvData);

private:
    QByteArray _mainCamPTZData; // 受信したMainCamのPTZデータ
    UdpReciever *_udp;
    QVector<TcpSender*> _tcp;
};

#endif // GODZILLA_H
