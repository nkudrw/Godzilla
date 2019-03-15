#include "godzilla.h"

#include <QDebug>

Godzilla::Godzilla(QObject *parent) : QObject(parent)
{
    _mainCamPTZData.clear();
    _tcp.clear();
    connect(this, SIGNAL(recvDataSignal(QByteArray)), this, SLOT(calcSubCamPTZData(QByteArray)));
}

void Godzilla::createUdpSocket(const quint16 port)
{
    _udp = new UdpReciever(this, port);
    _udp->HelloUDP(); // テスト用関数 //削除予定

}

void Godzilla::createTcpSocket(const QString dest)
{
    _tcp.append(new TcpSender(this, dest));
    _tcp.back()->doConnect();
}

void Godzilla::calcSubCamPTZData(QByteArray recvData)
{
    _mainCamPTZData = recvData;
    qDebug() << "mainCamPTZData: " << _mainCamPTZData;

    QByteArray tmp = "ndi_hx_support"; // テスト用 // 削除予定
    _tcp[0]->emitSendDataSignal(tmp); // テスト用 // 削除予定
}
