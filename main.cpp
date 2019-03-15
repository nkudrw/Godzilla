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
    god->createUdpSocket(1234); // 引数として受信ポート番号を指定
    god->createTcpSocket("192.168.0.10"); // 引数として送信先IPアドレスを指定

//    TcpSender *server = new TcpSender(god);
//    server->doConnect();

    return a.exec();
}
