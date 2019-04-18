#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "godzilla.h"
#include "udpreciever.h"
#include "tcpsender.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engineMain;
    engineMain.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engineMain.rootObjects().isEmpty())
        return -1;

    QQmlApplicationEngine engineDebug;
    engineDebug.load(QUrl(QStringLiteral("qrc:/debug.qml")));
    if (engineDebug.rootObjects().isEmpty())
        return -1;

    Godzilla *god = new Godzilla();
    engineMain.rootContext()->setContextProperty("god", god); //QML側にクラスをセット
    engineDebug.rootContext()->setContextProperty("god", god); //QML側にクラスをセット
    //god->createUdpSocket(1234); // 引数として受信ポート番号を指定
    //god->addSubCam("192.168.0.32"); // 引数として送信先IPアドレスを指定

    return app.exec();
}
