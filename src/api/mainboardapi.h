#ifndef MAINBOARDAPI_H
#define MAINBOARDAPI_H

#include <QObject>
#include <QVector>
#include <QDebug>

#include "config.h"
#include "winterface-api.h"


class MainboardAPI : public QObject
{
    Q_OBJECT

public:

    MainboardAPI();
    ~MainboardAPI();

    WINTP mb;
    bool CONNECTED = true;

    QVector<int> states;
    bool flag_switch;
    bool flag_led;
    bool flag_turbine;

    void setData(QVector<int> sync_states);
    void stateChange(bool switch_state, bool led_state,bool turbine_state);

signals:

    void finished();

public slots:

    void onMainboardAPI();
};

#endif // MAINBOARDAPI_H
