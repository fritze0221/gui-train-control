#ifndef INFOLABEL_H
#define INFOLABEL_H

#include <QWidget>
#include <QLabel>
#include <QLayout>

#include "fonts.h"

class infoLabel : public QWidget
{
    Q_OBJECT
public:
    explicit infoLabel(QWidget *parent,QVector<QRgb>color, QString text);


private:


    QLabel* label;

    QVBoxLayout* layout;

    Fonts customfont;

    QVector<QRgb> labelColor;

    QString labelText;

    QString labelStyle = R"(
    QLabel {
        background-color: transparent; /* Transparenter Hintergrund */
        border: 3px solid rgb(%1,%2,%3); /* Schwarzer Rahmen mit 3px Breite */
        border-radius: 10px; /* Leicht abgerundete Ecken */
        padding: 8px; /* Innenabstand, um Text vom Rahmen fernzuhalten */
        text-align: center; /* Zentrierter Text */
    }
    )";



signals:
};

#endif // INFOLABEL_H
