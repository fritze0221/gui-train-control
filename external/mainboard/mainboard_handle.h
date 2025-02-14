#ifndef MAINBOARDHANDLE_H
#define MAINBOARDHANDLE_H

#include <QObject>
#include <QLocalSocket>
#include <QDataStream>
#include <QDebug>
#include <QVector>
#include <QCoreApplication>

#include "../../src/config/config.h"
#include "../api/src_winterface/winterface-api.h"


class MainboardHandle : public QObject
{
    Q_OBJECT

public:
    explicit MainboardHandle();
    void connectToServer();  // Verbindung zum Server aufbauen
    void sendID();

    QVector<int> receivedVec;
    WINTP mainboard;

private slots:
    void onConnected();
    void onDataReceived();
    void onErrorOccurred(QLocalSocket::LocalSocketError error);
    void onStartRoutine();


private:
    QLocalSocket *socket;

signals:

    void sendQuit();
    void sendStartRoutie();

    
};

#endif // MAINBOARDHANDLE_H
