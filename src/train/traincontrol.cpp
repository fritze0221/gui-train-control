#include "traincontrol.h"

Traincontrol::Traincontrol(QWidget*parent ,int train_id)
    :train_id(train_id), QWidget(parent)
{

    wVeloSlider = new veloSlider(this,veloSliderColor,VELO_RANGE,VELO_INTERVAL,VELO_SCALE,"Speed");
    wAccSlider = new accSlider(this, accSliderColor,ACC_RANGE,ACC_INTERVAL,ACC_SCALE,"Acc");

    wStopButton = new modButton(this,stopButtonColor,"Stop",0,false);

    connect(wAccSlider,&accSlider::sendTime, wVeloSlider, &veloSlider::onTimeValue);
    connect(wStopButton,&modButton::sendButtonClicked, wVeloSlider, &veloSlider::onStopButton);
    connect(wStopButton, &modButton::sendButtonClicked, wAccSlider, &accSlider::onStopButton);

    connect(wVeloSlider, &veloSlider::sendTimeSpeed,this, &Traincontrol::onTimeSpeed);

    velolayout = new QHBoxLayout();

    velolayout->addWidget(wAccSlider);
    velolayout->addWidget(wVeloSlider);

    buttonlayout = new QVBoxLayout();

    buttonlayout->addWidget(wStopButton);

    layout = new QVBoxLayout();

    layout->addLayout(velolayout);
    layout->addLayout(buttonlayout);

    setLayout(layout);
}

void Traincontrol::onTimeSpeed(int time_t,int speed_t){

    time = time_t;
    speed = speed_t;

    sendAPITrain(time_t, speed_t, train_id);

}

void Traincontrol::paintEvent(QPaintEvent* event){

    QColor color(backroudColor);
    QBrush brush(color);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rect = this->rect().adjusted(1, 1, -1, -1);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect, 15, 15);

}


