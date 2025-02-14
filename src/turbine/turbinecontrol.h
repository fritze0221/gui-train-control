#ifndef TURBINCONTROL_H
#define TURBINCONTROL_H

#include <QWidget>
#include <QPainter>
#include <QLayout>

#include "modbutton.h"

class Turbincontrol : public QWidget
{
    Q_OBJECT
public:
    explicit Turbincontrol(QObject *paren);

    modButton* button;

    QHBoxLayout* layout;


private:

    QVector<QRgb> buttonColor = TURBINE_CONTROL_COLOR_BUTTON_COLOR;

    QRgb backroudColor = TURBINE_CONTROL_COLOR_BACKGROUND;

protected:

    void paintEvent(QPaintEvent* event) override;

signals:

    void sendAPITubin();
};

#endif // TURBINCONTROL_H
