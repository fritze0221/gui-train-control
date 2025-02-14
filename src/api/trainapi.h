#ifndef TRAINAPI_H
#define TRAINAPI_H

#include <QObject>
#include <QDebug>
#include <QThread>

#include "config.h"
#include "winterface-api.h"


class TrainAPI : public QThread
{
    Q_OBJECT

public:

    TrainAPI(int train_id);
    ~TrainAPI();

    WINTP train;

    void setData(int set_time, int set_speed);
    void handleConnection();

private:

    int speed;
    int time;
    int train_id;

    int direction;
    int true_speed;

signals:

    void finished();

public slots:

    void onTrainAPI();

};

#endif // TRAINAPI_H
