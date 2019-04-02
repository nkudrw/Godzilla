#include "udpreciever.h"

#include <unistd.h>
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
void UdpReciever::sendDummyData()
{
    // ダミーの更新通知（カメラID:FF, Pan:175°, Tilt:-30°,　Flip:1,  Zoom:555 ,Focus:FFF ,Iris:555）
    char testData[] = {
        '\xd1', '\xff', '\x57', '\x80', '\x00', '\xf1', '\x00', '\x00',
        '\x5a', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x05', '\x55', '\x00',
        '\x0f', '\xff', '\x05', '\x55', '\x8c'
    };

    QByteArray Data = QByteArray::fromRawData(testData, sizeof(testData));


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

    // デバッグ用　更新通知の受信60回に1回だけ処理
    static int i = 0;
    ++i;
    if(i > 60) {
        qDebug() << "Message from: " << sender.toString();
        qDebug() << "Message port: " << senderPort;
        qDebug() << "Message: " << buffer.toHex(0);

        Godzilla *parent = static_cast<Godzilla*>(this->parent());
        parent->recvUpdateNotice(buffer);
        i = 0;
    }
}
