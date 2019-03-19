#ifndef UDPRECIEVER_H
#define UDPRECIEVER_H

#include <QObject>
#include <QUdpSocket>

#include "mainwindow.h"

class UdpReciever : public QObject
{
    Q_OBJECT
public:
    explicit UdpReciever(QObject *parent = nullptr, quint16 port = 1234);
    void sendDummyData();

public slots:
    void readyRead();

private:
    QUdpSocket *_socket;
};

#endif // UDPRECIEVER_H
