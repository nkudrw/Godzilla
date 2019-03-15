#include "godzilla.h"

#include <QDebug>

Godzilla::Godzilla(QObject *parent) : QObject(parent)
{
    _mainCamPTZData.clear();
}

void Godzilla::calcSubCamPTZData(QByteArray recvData)
{
    _mainCamPTZData = recvData;
    qDebug() << "mainCamPTZData: " << _mainCamPTZData;
}
