#include "accslider.h"

accSlider::accSlider(QWidget *parent,const QVector<QRgb>& color, int range, int intervall,int scalefactor, QString text)
    :QWidget(parent), range(range), intervall(intervall), scalefactor(scalefactor), labelText(text)
{

    sliderColor << color;

    slider = new QSlider(Qt::Vertical,this);

    label = new QLabel(text);
    label->setFont(customfont);

    QSizePolicy policy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    slider->setSizePolicy(policy);
    slider->setMinimum(0);
    slider->setMaximum(range);
    slider->setTickInterval(intervall);
    slider->setStyleSheet(sliderStyle.arg(qRed(sliderColor[0])).arg(qGreen(sliderColor[0])).arg(qBlue(sliderColor[0])));
    slider->setMinimumSize(min_width,min_height);


    connect(slider, &QSlider::valueChanged, this, &accSlider::onValueChanged);

    sliderlayout = new QHBoxLayout();

    spacer1 = new QSpacerItem(40,0);

    sliderlayout->addSpacerItem(spacer1);
    sliderlayout->addWidget(slider);

    labellayout = new QHBoxLayout();

    spacer2 = new QSpacerItem(40,0);

    labellayout->addSpacerItem(spacer2);
    labellayout->addWidget(label);

    layout = new QVBoxLayout();

    layout->addLayout(labellayout);
    layout->addLayout(sliderlayout);

    setLayout(layout);

}

void accSlider::paintEvent(QPaintEvent *event)
{
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

    int sliderHeight = sliderRect.height();
    int availableHeight = slider->height() - sliderHeight;

    QFontMetrics fm = painter.fontMetrics();

    for (int i = 0; i <= numTicks; ++i) {
        int value = sliderMax - i * tickInterval; // Werte umkehren: Maximalwert oben
        double ratio = static_cast<double>(i) / numTicks; // Verhältnis bleibt gleich



        // Text zeichnenhorizontalAdvance

        if(i == 0){

            int fontWidth = fm.horizontalAdvance("Max"); // Breite eines Zeichens (z. B. "0")

            // Berechnung der Y-Position: Invertiert (Max oben, Min unten)
            int y = slider->y() + sliderHeight / 2 + static_cast<int>(ratio * availableHeight) - man_off_y;
            int x = slider->x() - fontWidth - man_off_x;

            painter.drawText(QPoint(x, y), "Max");
        }
        else if(i == numTicks){

            int fontWidth = fm.horizontalAdvance("Min"); // Breite eines Zeichens (z. B. "0")

            // Berechnung der Y-Position: Invertiert (Max oben, Min unten)
            int y = slider->y() + sliderHeight / 2 + static_cast<int>(ratio * availableHeight) - man_off_y;
            int x = slider->x() - fontWidth - man_off_x;

            painter.drawText(QPoint(x, y), "Min");

        }
        else{
            int fontWidth = fm.horizontalAdvance( QString::number((double)value/((double)scalefactor))); // Breite eines Zeichens (z. B. "0")

            // Berechnung der Y-Position: Invertiert (Max oben, Min unten)
            int y = slider->y() + sliderHeight / 2 + static_cast<int>(ratio * availableHeight) - man_off_y;
            int x = slider->x() - fontWidth - man_off_x;

            painter.drawText(QPoint(x, y ), QString::number((double)value/((double)scalefactor)));

        }

    }

}

void accSlider::onValueChanged(){

    emit sendTime((-((double)time/(double)range)*(double)slider->value() +  time));

}

void accSlider::onStopButton(){

    slider->setValue(range);

}

