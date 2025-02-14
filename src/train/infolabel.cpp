#include "infolabel.h"

infoLabel::infoLabel(QWidget *parent,QVector<QRgb>color, QString text)
    : labelText(text)
{

    labelColor << color;

    label = new QLabel(text);
    label->setFont(customfont);

    label->setStyleSheet(labelStyle.arg(qRed(labelColor[0])).arg(qGreen(labelColor[0])).arg(qBlue(labelColor[0])));
    label->setFixedHeight(50);

    layout = new QVBoxLayout();

    layout->addWidget(label);

    setLayout(layout);


}

