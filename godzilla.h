#ifndef GODZILLA_H
#define GODZILLA_H

#include <QObject>

class Godzilla : public QObject
{
    Q_OBJECT
public:
    explicit Godzilla(QObject *parent = nullptr);

signals:
    void recvDataSignal(QByteArray recvData);

public slots:
    void emitRecvDataSignal(QByteArray recvData)
    {
        emit recvDataSignal(recvData);
    }

    void calcSubCamPTZData(QByteArray recvData);

private:
    QByteArray _mainCamPTZData; // 受信したMainCamのPTZデータ

};

#endif // GODZILLA_H
