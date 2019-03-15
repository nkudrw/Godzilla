#include "udpreciever.h"

#include <QDebug>

#include "godzilla.h"

UdpReciever::UdpReciever(QObject *parent, quint16 port) : QObject(parent)
{
    // create a QUDP socket
    _socket = new QUdpSocket(this);

    // bind to an address and port
    _socket -> bind(QHostAddress::AnyIPv4, port); // アドレスは何に設定？？

    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}


// テスト用関数
void UdpReciever::HelloUDP()
{
    QByteArray Data;
    Data.append("Hello from UDP");

    _socket -> writeDatagram(Data, QHostAddress::Broadcast, 1234);
}

void UdpReciever::readyRead()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(static_cast<int>(_socket->pendingDatagramSize()));

    QHostAddress sender;
    quint16 senderPort;

    _socket -> readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;

    Godzilla *parent = static_cast<Godzilla*>(this->parent());
    parent->emitRecvDataSignal(buffer);
}
