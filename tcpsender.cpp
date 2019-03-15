#include "tcpsender.h"

#include <QDebug>

TcpSender::TcpSender(QObject *parent, const QString dest) : QObject (parent)
{
    _ipAddr.setAddress(dest);
    _ipAddrArray = dest.toUtf8();
}

void TcpSender::doConnect()
{
    // create a QTCP socket
    _socket = new QTcpSocket(this);

    connect(_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(_socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(this, SIGNAL(sendDataSignal(QByteArray)), this, SLOT(sendData(QByteArray)));

    qDebug() << "connecting...";

    _socket->connectToHost(_ipAddr, 80);
//    _socket->connectToHost("google.com", 80);

    if(!_socket->waitForConnected(5000)) {
        qDebug() << "Tcpsender Error: " << _socket->errorString();
    }
}

void TcpSender::connected()
{
    qDebug() << "connected...";
}

void TcpSender::disconnected()
{
    qDebug() << "disconnected...";
}

void TcpSender::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void TcpSender::readyRead()
{
    qDebug() << "reading...";

    // read the data from the socket
    qDebug() << _socket->readAll();
}

void TcpSender::sendData(QByteArray sendCmd)
{
    QByteArray sendData; // TODO:中身の仕様確認必要(Connection: closeでReplyが返ってくる)
    sendData.append("GET /cgi-bin/" + sendCmd + " HTTP/1.1\r\n");
    sendData.append("Connection: Keep_Alive\r\n");
    sendData.append("Host: " + _ipAddrArray + "\r\n");
    sendData.append("Accept: */*\r\n\r\n");

    _socket->write(sendData);
}

