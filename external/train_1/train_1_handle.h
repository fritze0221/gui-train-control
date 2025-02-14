#ifndef TRAIN1HANDLE_H
#define TRAIN1HANDLE_H

#include <QObject>
#include <QLocalSocket>
#include <QDataStream>
#include <QDebug>
#include <QVector>
#include <QCoreApplication>

#include "../../src/config/config.h"
#include "../api/src_winterface/winterface-api.h"


class TrainHandle : public QObject
{
    Q_OBJECT

public:
    explicit TrainHandle();
    void connectToServer();  // Verbindung zum Server aufbauen
    void sendID();

    int time = 0;
    int speed = 0;

    WINTP train;

private slots:
    void onConnected();
    void onDataReceived();
    void onErrorOccurred(QLocalSocket::LocalSocketError error);
    void onStartRoutine();

private:
    QLocalSocket *socket;

signals:

    void sendStartRoutie();
    void sendQuit();

    
};

#endif // CHILDPROCESS_H
