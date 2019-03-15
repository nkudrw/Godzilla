#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>

#include "godzilla.h"
#include "udpreciever.h"
#include "tcpsender.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    w->show();

    Godzilla *god = new Godzilla();

    UdpReciever *client = new UdpReciever(god); // メインカメラからの更新通知受信用
    client->HelloUDP(); // テスト用関数 //削除予定

    TcpSender *server = new TcpSender(god);
    server->doConnect();

    return a.exec();
}
