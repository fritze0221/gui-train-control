#ifndef SWITCHCONTROL_H
#define SWITCHCONTROL_H

#include <QWidget>
#include <QPainter>
#include <QLayout>
#include <QVector>

#include "modbutton.h"
#include "style_config.h"

class Switchcontrol : public QWidget
{
    Q_OBJECT
public:
    explicit Switchcontrol(QWidget *parent);

private:


    modButton* wInnerButton;
    modButton* wOuterButton;

    QHBoxLayout* layout;

    QVector<QRgb> innerButtonColor = SWITCH_CONTROL_COLOR_INNER_BUTTON;
    QVector<QRgb> outerButtonColor = SWITCH_CONTROL_COLOR_OUTER_BUTTON;
    QRgb backroudColor = SWITCH_CONTROL_COLOR_BACKGROUND;


signals:

    void sendAPISwitch();

protected:

    void paintEvent(QPaintEvent* event) override;
};

#endif // SWITCHCONTROL_H
