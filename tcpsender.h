#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QHostInfo>


class TcpSender : public QObject
{
    Q_OBJECT
public:
    explicit TcpSender(QObject *parent = nullptr, const QString dest = "192.168.0.10");
    void doConnect();
    void sendData(QByteArray sendCmd);

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *_socket;
    QHostAddress _ipAddr;
    QByteArray _ipAddrArray;
};

#endif // TCPSENDER_H
