#include "tcpsender.h"

#include <QDebug>

TcpSender::TcpSender(Godzilla *god)
{
    _god = god;
}

void TcpSender::doConnect()
{
    // create a QTCP socket
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "connecting...";

//    QHostAddress subCamAddr("192.168.0.10");
//    socket->connectToHost(subCamAddr, 80);
    socket->connectToHost("google.com", 80);

    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
    }
}

void TcpSender::connected()
{
    qDebug() << "connected...";

    socket->write("HEAD / HTTP/1.1\r\n\r\n\r\n\r\n");
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
    qDebug() << socket->readAll();
}

void TcpSender::sendData(QByteArray sendData)
{
    socket->write("HEAD / HTTP/1.1\r\n\r\n\r\n\r\n"); // テスト用
}

