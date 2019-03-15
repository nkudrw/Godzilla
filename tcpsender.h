#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>

#include "mainwindow.h"
#include "godzilla.h"

class TcpSender : public QObject
{
    Q_OBJECT
public:
    explicit TcpSender(Godzilla *god);

    void doConnect();

signals:
    void sendDataSignal(QByteArray sendData);

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

    void emitSendDataSignal(QByteArray sendData)
    {
        emit sendDataSignal(sendData);
    }

    void sendData(QByteArray sendData);

private:
    QTcpSocket *socket;
    Godzilla *_god;
};

#endif // TCPSENDER_H
