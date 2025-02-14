#include "switchcontrol.h"

Switchcontrol::Switchcontrol(QWidget *parent)
{

    wInnerButton = new modButton(this, innerButtonColor,"Inner",1,true);
    wOuterButton = new modButton(this, outerButtonColor, "Outer", 1,false);

    connect(wInnerButton, &modButton::sendSwitchSignal, wOuterButton, &modButton::onSwitchSignal);
    connect(wOuterButton, &modButton::sendSwitchSignal, wInnerButton, &modButton::onSwitchSignal);

    connect(wInnerButton, &modButton::sendSwitchSignal, this, &Switchcontrol::sendAPISwitch);
    connect(wOuterButton, &modButton::sendSwitchSignal, this, &Switchcontrol::sendAPISwitch);


    layout = new QHBoxLayout();

    layout->addWidget(wInnerButton);
    layout->addWidget(wOuterButton);

    setLayout(layout);

}

void Switchcontrol::paintEvent(QPaintEvent* event){


    QColor color(backroudColor);
    QBrush brush(color);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rect = this->rect().adjusted(1, 1, -1, -1);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect, 15, 15);

}
