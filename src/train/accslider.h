#ifndef ACCSLIDER_H
#define ACCSLIDER_H

#include <QObject>
#include <QWidget>
#include <QSlider>
#include <QLayout>
#include <QVector>
#include <QPainter>
#include <QEvent>
#include <QStyleOption>
#include <QLabel>
#include <QSpacerItem>

#include "fonts.h"
#include "config.h"
#include "style_config.h"

class accSlider : public QWidget
{
    Q_OBJECT
public:

    accSlider(QWidget *parent,const QVector<QRgb>& color, int range, int intervall,int scalefactor,QString text);

private:

    QSlider* slider;
    QLabel* label;

    QHBoxLayout* sliderlayout;
    QSpacerItem* spacer1;
    QSpacerItem* spacer2;

    QHBoxLayout* labellayout;
    QVBoxLayout* layout;

    QString sliderStyle = ACC_SLIDER_STYLE;

    QVector<QRgb> sliderColor;

    int range;
    int intervall;
    int scalefactor;
    int time = TRAIN_DEFAULT_TIME;

    Fonts customfont;
    QString labelText;

    const int min_width = 30;
    const int min_height = 100;
    const int man_off_x = 0;
    const int man_off_y = -6;


protected:

    void paintEvent(QPaintEvent *event) override;

signals:

    void sendTime(int time);

public slots:

    void onStopButton();

private slots:

    void onValueChanged();

};

#endif // ACCSLIDER_H
