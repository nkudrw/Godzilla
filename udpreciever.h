#ifndef UDPRECIEVER_H
#define UDPRECIEVER_H

#include <QObject>
#include <QUdpSocket>

#include "mainwindow.h"
#include "godzilla.h"

class UdpReciever : public QObject
{
    Q_OBJECT
public:
    explicit UdpReciever(Godzilla *god);
    void HelloUDP();

public slots:
    void readyRead();

private:
    QUdpSocket *socket;
    Godzilla *_god;
};

#endif // UDPRECIEVER_H
