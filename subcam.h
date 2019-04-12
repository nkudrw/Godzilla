#ifndef SUBCAM_H
#define SUBCAM_H

#include <QObject>

#include "godtypedef.h"
#include "tcpsender.h"

class SubCam : public QObject
{
    Q_OBJECT

public:
    explicit SubCam(QObject *parent = nullptr,
                    const QString dest = "192.168.0.10",
                    double x = 0,
                    double y = 1000,
                    double z = 0,
                    double angle = 0);
    LensInfo getSubCamLensInfo();
    void setSubCamPosi(double x, double y, double z, double angle);
    void recvMainCamData(const LensInfo mainCam, const Location TagetPosi);

signals:

public slots:

private:
    TcpSender *_tcp;
    LensInfo _mainCamLensInfo;
    LensInfo _subCamLensInfo;
    QByteArray _cmd;
    Location   _targetPosi;
    Location   _subCamPosi;
    unsigned short _subCam_AWpan;
    unsigned short _subCam_AWtilt;
    unsigned short _subCam_AWzoom;

    bool calcSubCamAngle();
    bool calcSubCamPTZ();
    QByteArray createCmdStrAPC();
    QByteArray createCmdStrAXZ();
    bool num2ascii(unsigned int num, QByteArray &array, int length);
};

#endif // SUBCAM_H
