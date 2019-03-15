#include "udpreciever.h"

#include <QDebug>

UdpReciever::UdpReciever(Godzilla *god)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);

    // bind to an address and port
    socket -> bind(QHostAddress::AnyIPv4, 1234); // アドレスは何に設定？？

    _god = god;

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(_god, SIGNAL(recvDataSignal(QByteArray)), _god, SLOT(calcSubCamPTZData(QByteArray)));
}


// テスト用関数
void UdpReciever::HelloUDP()
{
    QByteArray Data;
    Data.append("Hello from UDP");

    socket -> writeDatagram(Data, QHostAddress::Broadcast, 1234);
}

void UdpReciever::readyRead()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(static_cast<int>(socket->pendingDatagramSize()));

    QHostAddress sender;
    quint16 senderPort;

    socket -> readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;

    _god->emitRecvDataSignal(buffer);
}
