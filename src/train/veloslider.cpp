#include "veloslider.h"

veloSlider::veloSlider(QWidget *parent, QVector<QRgb> color, int range, int intervall,int scale,QString text)
    : QWidget{parent}, range(range),scale_factor(scale),labelText(text)
{
    sliderColor << color;

    r_timer = qRed(sliderColor[0]);
    g_timer = qGreen(sliderColor[0]);
    b_timer = qBlue(sliderColor[0]);

    rampTimer = new QTimer(this);
    colorTimer = new QTimer(this);

    slider = new QSlider(Qt::Horizontal);
    label = new QLabel(text);

    label->setFont(customfont);

    QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    slider->setSizePolicy(policy);

    slider->setMinimum(-range);
    slider->setMaximum(range);
    slider->setTickInterval(intervall);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setStyleSheet(sliderStyle.arg(qRed(sliderColor[0])).arg(qGreen(sliderColor[0])).arg(qBlue(sliderColor[0])).arg(qRed(sliderColor[0])).arg(qGreen(sliderColor[0])).arg(qBlue(sliderColor[0])));

    connect(slider, &QSlider::valueChanged, this, &veloSlider::onValueChanged);
    connect(this, &veloSlider::sendTimeValueChanged, this, &veloSlider::onValueChanged);

    connect(rampTimer, &QTimer::timeout, this, &veloSlider::onTimer);
    connect(colorTimer, &QTimer::timeout, this, &veloSlider::onColorTimer);

    connect(this, &veloSlider::sendRampPaintEvent, this, &veloSlider::onRampPaintEvent);
    connect(this, &veloSlider::sendScalePaintEvent, this, &veloSlider::onScalePaintEvent);

    connect(slider, &QSlider::valueChanged, this, [=](){sendTimeSpeed(ramp_time, slider->value());});
    connect(this, &veloSlider::sendTimeValueChanged, this, [=](){sendTimeSpeed(ramp_time, speed);});

    layout = new QHBoxLayout();

    layout->addWidget(slider);
    layout->addWidget(label);

    setLayout(layout);
    setMinimumSize(min_width,min_height);
}

void veloSlider::paintEvent(QPaintEvent* event) {
    emit sendScalePaintEvent();
    emit sendRampPaintEvent();
}

void veloSlider::onScalePaintEvent() {
    QPainter painter(this);

    painter.setFont(customfont);
    painter.setPen(Qt::white);

    int sliderMin = slider->minimum();
    int sliderMax = slider->maximum();
    int tickInterval = slider->tickInterval();
    int numTicks = (sliderMax - sliderMin) / tickInterval;

    QStyleOptionSlider opt;
    opt.initFrom(slider);
    opt.rect = slider->geometry();
    opt.minimum = slider->minimum();
    opt.maximum = slider->maximum();
    opt.tickPosition = slider->tickPosition();
    opt.tickInterval = slider->tickInterval();
    opt.orientation = slider->orientation();

    opt.upsideDown = (slider->orientation() == Qt::Horizontal) ?
                         (slider->invertedAppearance() != (slider->layoutDirection() == Qt::RightToLeft)) :
                         (!slider->invertedAppearance());

    QRect sliderRect = slider->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, slider);

    int sliderWidth = sliderRect.width();
    int availableWidth = slider->width() - sliderWidth;

    QFontMetrics fm = painter.fontMetrics();
    int fontHeight = fm.height();

    for (int i = 0; i <= numTicks; ++i) {
        int value = sliderMin + i * tickInterval;
        double ratio = static_cast<double>(value - sliderMin) / (sliderMax - sliderMin);
        int x = slider->x() + sliderWidth / 2 + static_cast<int>(ratio * availableWidth) - fm.horizontalAdvance(QString::number(value)) / 2;
        int y = slider->y() + slider->height() + fontHeight + man_off_y;

        painter.drawText(QPoint(x, y), QString::number(value));

        if (i == 0) min_pos = x;
        if (i == numTicks) max_pos = x;
        if (i == numTicks / 2) zero_off = x - sliderWidth / 2;
    }
}

void veloSlider::onRampPaintEvent() {
    QPainter painter(this);

    QBrush brush(sliderColor[3]);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    ramp_off = static_cast<double>(max_pos - min_pos) / (2 * scale_factor*range) * (ramp_slider_value);

    int x = (width() - label->width() - man_off_x - rect_width) / 2 + ramp_off;
    int y = (height() - rect_height) / 2;

    painter.drawRect(x, y, rect_width, rect_height);
}

void veloSlider::onValueChanged() {
    double value = slider->value();

    speed = value;

    int abs_value = std::abs(value);

    r_tmp = ((qRed(sliderColor[2]) - (double)qRed(sliderColor[0])) / ((double)range)) * abs_value + qRed(sliderColor[0]);
    g_tmp = ((qGreen(sliderColor[2]) - (double)qGreen(sliderColor[0])) / ((double)range)) * abs_value + qGreen(sliderColor[0]);
    b_tmp = ((qBlue(sliderColor[2]) - (double)qBlue(sliderColor[0])) / ((double)range)) * abs_value + qBlue(sliderColor[0]);

    if(value != 0){

        static int value_state = 0;

        if (value > 0) {

            if(value_state == -1){

                r_timer = r_tmp;
                g_timer = g_tmp;
                b_timer = b_tmp;

            }

            slider->setStyleSheet(sliderStyle.arg(r_tmp).arg(g_tmp).arg(b_tmp).arg(r_timer).arg(g_timer).arg(b_timer));

            value_state = 1;
        }

        if (value < 0) {

            if(value_state == 1){

                r_timer = r_tmp;
                g_timer = g_tmp;
                b_timer = b_tmp;

            }

            slider->setStyleSheet(sliderStyle.arg(r_timer).arg(g_timer).arg(b_timer).arg(r_tmp).arg(g_tmp).arg(b_tmp));

            value_state = -1;

        }


        if(((r_timer != qRed(sliderColor[1])) || (g_timer != qGreen(sliderColor[1])) || (b_timer != qBlue(sliderColor[1])))){

            colorTimer->setInterval(colorTime);
            colorTimer->start();
        }
    }

    else {

        r_timer = qRed(sliderColor[0]);
        g_timer = qGreen(sliderColor[0]);
        b_timer = qBlue(sliderColor[0]);

        slider->setStyleSheet(sliderStyle.arg(r_tmp).arg(g_tmp).arg(b_tmp).arg(r_tmp).arg(g_tmp).arg(b_tmp));

        colorTimer->stop();

    }



    if (ramp_slider_value != scale_factor*slider->value()) {

        ramp_time_delta = ramp_time / scale_factor;

    } else {

        ramp_time_delta = ramp_time;

    }

    if(ramp_time_delta != 0){

        rampTimer->setInterval(ramp_time_delta);
        rampTimer->start();

    }
    else{

        ramp_slider_value = scale_factor*slider->value();
        repaint();

    }

}

void veloSlider::onTimer() {
    if (ramp_slider_value != scale_factor*slider->value()) {

        if (ramp_slider_value < (scale_factor*slider->value())){

            ramp_slider_value++;

        }
        else{

            ramp_slider_value--;

        }

        rampTimer->setInterval(ramp_time_delta);
        rampTimer->start();

        repaint();
    }
}

void veloSlider::onStopButton(){

    ramp_time = 0;
    slider->setValue(0);
    ramp_slider_value = 0;
    repaint();

}

void veloSlider::onTimeValue(int time){

    ramp_time = time;

    emit sendTimeValueChanged();

}

void veloSlider::onColorTimer(){

    if(r_timer > qRed(sliderColor[1])) r_timer--;
    else{ r_timer++; }

    if(g_timer > qGreen(sliderColor[1])) g_timer--;
    else{ g_timer++; };

    if(b_timer > qBlue(sliderColor[1])) b_timer--;
    else{  b_timer++; };


    r_timer = qBound(0, r_timer, 255);
    g_timer = qBound(0, g_timer, 255);
    b_timer = qBound(0, b_timer, 255);

    int value = slider->value();

    if (value > 0) {

        slider->setStyleSheet(sliderStyle.arg(r_tmp).arg(g_tmp).arg(b_tmp).arg(r_timer).arg(g_timer).arg(b_timer));

    }

    if (value < 0) {


        slider->setStyleSheet(sliderStyle.arg(r_timer).arg(g_timer).arg(b_timer).arg(r_tmp).arg(g_tmp).arg(b_tmp));

    }

    if((value != 0) && ((r_timer != qRed(sliderColor[1])) || (g_timer != qGreen(sliderColor[1])) || (b_timer != qBlue(sliderColor[1])))){


        colorTimer->setInterval(colorTime);
        colorTimer->start();

    }

}

