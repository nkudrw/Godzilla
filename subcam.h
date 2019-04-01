#ifndef SUBCAM_H
#define SUBCAM_H

#include <QObject>

#include "godtypedef.h"
#include "tcpsender.h"

class SubCam : public QObject
{
    Q_OBJECT

public:
    explicit SubCam(QObject *parent = nullptr, const QString dest = "192.168.0.10");
    void recvMainCamData(const LensInfo mainCam, const Location TagetPosi);

signals:

public slots:

private:
    TcpSender *_tcp;
    LensInfo _mainCam;
    LensInfo _subCam;
    int _angle; //TODO:型修正（適切な型が分からなかったのでとりあえず全部int（六車））
    QByteArray _cmd;
    Location   _TargetPosi;
    Location   _SubcamPosi;
    unsigned int _subcam_AWpan;

    bool calcSubCamAngle();
    bool calcSubCamPTZ();
    bool calcSubCamPosi();
    QByteArray createCmdString();
    bool num2ascii(unsigned int num, QByteArray &array, int length);
};

#endif // SUBCAM_H
