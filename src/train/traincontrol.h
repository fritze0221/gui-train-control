#ifndef TRAINCONTROL_H
#define TRAINCONTROL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QPainterPath>
#include <QVector>

#include "modbutton.h"
#include "veloslider.h"
#include "accslider.h"
#include "infolabel.h"

#include "config.h"
#include "style_config.h"

class Traincontrol : public QWidget
{
    Q_OBJECT
public:
    explicit Traincontrol(QWidget *parent,int train_id);

    veloSlider* wVeloSlider;
    accSlider* wAccSlider;
    infoLabel* wInfoLabel;

    modButton* wStopButton;
    modButton* wApplyButton;

    QHBoxLayout* velolayout;
    QVBoxLayout* buttonlayout;
    QVBoxLayout* layout;

    QVector<QRgb> veloSliderColor = TRAIN_CONTROL_COLOR_VELO_SLIDER;
    QVector<QRgb> accSliderColor = TRAIN_CONTROL_COLOR_ACC_SLIDER;
    QVector<QRgb> stopButtonColor = TRAIN_CONTROL_COLOR_STOP_BUTTON;
    QRgb backroudColor;

    int time = 2000;
    int speed = 0;

    int train_id = -1;

signals:

    void sendAPITrain(int time,int speed, int train_id);

private slots:

    void onTimeSpeed(int time, int speed);

protected:

    void paintEvent(QPaintEvent *event) override;

};

#endif // TRAINCONTROL_H
