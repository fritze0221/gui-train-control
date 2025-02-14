#include "ledgrid.h"

ledGrid::ledGrid(QWidget *parent,int num, QVector<QRgb> color)
    : size(num)
{
    sliderColor << color;

    Slider.resize(num);
    cur_value.resize(num);

    grid = new QGridLayout;

    int j = 0;
    int k = 0;

    for (int i = 0; i < num; i++)
    {

        cur_value[i] = 0;

        Slider[i] = new QSlider(Qt::Horizontal);
        Slider[i]->setMaximum(1);
        Slider[i]->setMinimum(0);
        Slider[i]->setTickPosition(QSlider::TicksBelow);
        Slider[i]->setTickInterval(1);
        Slider[i]->setStyleSheet(sliderStyle.arg(qRed(sliderColor[2])).arg(qGreen(sliderColor[2])).arg(qBlue(sliderColor[2])).arg(qRed(sliderColor[3])).arg(qGreen(sliderColor[3])).arg(qBlue(sliderColor[3])));
        Slider[i]->setValue(cur_value[i]);

        Slider[i]->setTracking(false); // Optional: keine sofortige Änderungen am Wert; // Optional: um Interaktion komplett zu verhindern

        connect(Slider[i], &QSlider::sliderPressed, this, [=]()
                { onSliderPressed(i); });

        connect(Slider[i], &QSlider::sliderReleased, this, [=]()
                { onSliderReleased(i); });



        grid->addWidget(Slider[i], j, k);

        k++;

        if (k == 3)
        {

            k = 0;
            j++;
        }
    }


    setLayout(grid);
}

void ledGrid::onResetButtonClicked()
{

    for (int i = 0; i < size; i++){

        Slider[i]->setValue(0);
        cur_value[i] = 0;

        Slider[i]->setStyleSheet(sliderStyle.arg(qRed(sliderColor[2])).arg(qGreen(sliderColor[2])).arg(qBlue(sliderColor[2])).arg(qRed(sliderColor[3])).arg(qGreen(sliderColor[3])).arg(qBlue(sliderColor[3])));

    }

    emit sendIndexState(cur_value);


}

void ledGrid::onAllButtonClicked()
{

    for (int i = 0; i < size; i++){

        Slider[i]->setValue(1);
        cur_value[i] = 1;


        Slider[i]->setStyleSheet(sliderStyle.arg(qRed(sliderColor[0])).arg(qGreen(sliderColor[0])).arg(qBlue(sliderColor[0])).arg(qRed(sliderColor[1])).arg(qGreen(sliderColor[1])).arg(qBlue(sliderColor[1])));
    }

    emit sendIndexState(cur_value);

}

void ledGrid::onSliderPressed(int sliderIndex)
{

    bool lock = true;

    if ((cur_value[sliderIndex] == 1) && lock){
        Slider[sliderIndex]->setStyleSheet(sliderStyle.arg(qRed(sliderColor[2])).arg(qGreen(sliderColor[2])).arg(qBlue(sliderColor[2])).arg(qRed(sliderColor[3])).arg(qGreen(sliderColor[3])).arg(qBlue(sliderColor[3])));

        cur_value[sliderIndex] = 0;

        Slider[sliderIndex]->setValue(cur_value[sliderIndex]);

        lock = false;
    }

    if ((cur_value[sliderIndex] == 0) && lock){
        Slider[sliderIndex]->setStyleSheet(sliderStyle.arg(qRed(sliderColor[0])).arg(qGreen(sliderColor[0])).arg(qBlue(sliderColor[0])).arg(qRed(sliderColor[1])).arg(qGreen(sliderColor[1])).arg(qBlue(sliderColor[1])));

        cur_value[sliderIndex] = 1;

        Slider[sliderIndex]->setValue(cur_value[sliderIndex]);

        lock = false;

    }

    emit sendIndexState(cur_value);

}

void ledGrid::onSliderReleased(int sliderIndex){

    Slider[sliderIndex]->setValue(cur_value[sliderIndex]);

}


