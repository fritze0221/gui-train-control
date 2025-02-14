#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QObject>
#include <QDebug>
#include <QProcess>
#include <QCoreApplication>
#include <QLocalServer>
#include <QLocalSocket>

#include "config.h"
#include "winterface-config.h"


class ApiHandler : public QObject
{
    Q_OBJECT

public:

    ApiHandler();

private:

    QProcess* train_1;
    QProcess* train_2;
    QProcess* mb;

    QLocalServer *server;

    QVector<QLocalSocket*> tmp_client;

    QLocalSocket *train_1_socket;
    QLocalSocket *train_2_socket;
    QLocalSocket *mainboard_socket;

    QVector<int> train_1_states;
    QVector<int> train_2_states;
    QVector<int> mb_states;

    int SWITCH = 1;
    int TURBINE = 2;

    bool train_1_state_change = false;
    bool train_2_state_change = false;
    bool mb_state_change = false;

    void updateMB(QVector<int> states, int house_id);
    void updateMB(int identifier);

    void sendData(int identifier);

    void init();

    int client_counter = 0;

signals:

    void stateChange();

public slots:

    void onTimeSpeedTrain(int time,int speed, int train_id);
    void onIndexStateHouse(QVector<int> states, int house_id);
    void onSwitch();
    void onTurbin();

private slots:

    void onStateChange();

    void onServerConnection();
    void onDataReceived(int id);
    void onErrorOccurred(QLocalSocket::LocalSocketError error);

};

#endif // APIHANDLER_H
