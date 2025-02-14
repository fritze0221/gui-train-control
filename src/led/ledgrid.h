#ifndef GRIDLED_H
#define GRIDLED_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QDebug>
#include <QMainWindow>
#include <QResizeEvent>
#include <QGridLayout>
#include <QMouseEvent>

#include "style_config.h"

class ledGrid : public QWidget{
    Q_OBJECT


public:

    ledGrid(QWidget* parent,int num,QVector<QRgb> color);

private:

    QVector<QSlider*> Slider;
    QGridLayout *grid;

    QString sliderStyle =LED_GRID_SLIDER_STYLE;

    QVector<QRgb> sliderColor;

    int size;
    const int bRESET = 0;
    const int bALL = 1;
    QVector<int> cur_value;

signals:

    void sendIndexState(QVector<int> states);

public slots:

    void onResetButtonClicked();
    void onAllButtonClicked();

private slots:
    void onSliderPressed(int sliderIndex);
    void onSliderReleased(int sliderIndex);


};


#endif // LEDGRID_H
