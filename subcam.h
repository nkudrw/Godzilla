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
    void recvMainCamData(const LensInfo mainCam);

signals:

public slots:

private:
    TcpSender *_tcp;
    LensInfo _mainCam;
    LensInfo _subCam;
    int _angle; //TODO:型修正（適切な型が分からなかったのでとりあえず全部int（六車））
    QByteArray _cmd;

    bool calcSubCamAngle();
    bool calcSubCamPTZ();
    QByteArray createCmdString();
};

#endif // SUBCAM_H
