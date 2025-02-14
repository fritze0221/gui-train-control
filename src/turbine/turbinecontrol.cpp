#include "turbinecontrol.h"

Turbincontrol::Turbincontrol(QObject *parent)
{

    button = new modButton(this, buttonColor, "Turbine",1,false);

    connect(button, &modButton::sendButtonClicked, this, &Turbincontrol::sendAPITubin);

    layout = new QHBoxLayout();

    layout->addWidget(button);

    setLayout(layout);

}


void Turbincontrol::paintEvent(QPaintEvent* event){

    QColor color(backroudColor);
    QBrush brush(color);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rect = this->rect().adjusted(1, 1, -1, -1);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect, 15, 15);

}

