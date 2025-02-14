#include "ledcontrol.h"

Ledcontrol::Ledcontrol(QWidget *parent, int house_id,int led_num)
    :house_id(house_id)
{

    wLedGrid = new ledGrid(this, led_num, ledColor);

    wResetButton = new modButton(this, resetButtonColor, "Reset",0,false);
    wAllButton = new modButton(this, allButtonColor, "All", 0,false);

    connect(wResetButton, &modButton::sendButtonClicked, wLedGrid, &ledGrid::onResetButtonClicked);
    connect(wAllButton, &modButton::sendButtonClicked, wLedGrid, &ledGrid::onAllButtonClicked);

    connect(wLedGrid, &ledGrid::sendIndexState, this, &Ledcontrol::onIndexState);


    buttonlayout = new QHBoxLayout();

    buttonlayout->addWidget(wAllButton);
    buttonlayout->addWidget(wResetButton);

    layout = new QVBoxLayout();

    layout->addWidget(wLedGrid);
    layout->addLayout(buttonlayout);


    setMaximumSize(250,250);
    setLayout(layout);

}

void Ledcontrol::paintEvent(QPaintEvent* event){


    QColor color(backroudColor);
    QBrush brush(color);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rect = this->rect().adjusted(1, 1, -1, -1);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect, 15, 15);

}

void Ledcontrol::onIndexState(QVector<int> states){

    emit sendAPILed(states, house_id);

}

