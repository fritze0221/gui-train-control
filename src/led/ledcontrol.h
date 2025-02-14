#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <QWidget>
#include <QPainter>
#include <QLayout>

#include "ledgrid.h"
#include "modbutton.h"

class Ledcontrol : public QWidget
{
    Q_OBJECT
public:
    explicit Ledcontrol(QWidget *parent,int house_id,int led_num);

private:

    ledGrid* wLedGrid;
    modButton* wResetButton;
    modButton* wAllButton;

    QHBoxLayout* buttonlayout;
    QVBoxLayout* layout;

    QVector<QRgb> ledColor = LED_CONTROL_COLOR_LED_GRID;
    QVector<QRgb> resetButtonColor = LED_CONTROL_COLOR_RESET_BUTTON;
    QVector<QRgb> allButtonColor = LED_CONTROL_COLOR_ALL_BUTTON;

    QRgb backroudColor = LED_CONTROL_COLOR_BACKGROUND;

    int house_id = -1;

signals:

    void sendAPILed(QVector<int> states, int house_id);

private slots:

    void onIndexState(QVector<int> states);

protected:

    void paintEvent(QPaintEvent* event) override;
};

#endif // LEDCONTROL_H
