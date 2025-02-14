#ifndef VELOSLIDER_H
#define VELOSLIDER_H

#include <QObject>
#include <QWidget>
#include <QStyleOptionSlider>
#include <QFontDatabase>
#include <QSizePolicy>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QStyle>
#include <QLayout>
#include <QTimer>
#include <QVector>
#include <QLabel>

#include "fonts.h"
#include "config.h"
#include "style_config.h"

class veloSlider : public QWidget
{
    Q_OBJECT
public:

    /**
     * @brief Initialisiert den benutzerdefinierten Slider mit Farbschema, Bereich und Intervall.
     *
     * Diese Methode wird verwendet, um den Slider mit spezifischen Farben, einem Bereich für die
     * Minimal- und Maximalwerte sowie einem Intervall für die Tick-Anzeige zu initialisieren.
     *
     * @param parent Ein Zeiger auf das übergeordnete Widget.
     * @param color  Ein QVector mit QRgb-Werten, die die Farben des Sliders definieren.
     *               - `color[0]`: Farbe für den Neutralwert.
     *               - `color[1]`: Farbe für verblassenden Wert.
     *               - `color[2]`: Farbe für Zielwert.
     *               - `color[3]`: Farbe für Reckteck.
     * @param range  Der maximale absolute Bereich des Sliders (z. B. `-range` bis `+range`).
     * @param intervall Das Intervall zwischen den Ticks (Schritte auf dem Slider).
     * @param scale für die Schrittweite der Rampe.
     */

    explicit veloSlider(QWidget *parent,QVector<QRgb> color, int range, int intervall, int scale, QString text);


private:

    QSlider* slider;
    QLabel* label;
    QTimer* rampTimer;
    QTimer* colorTimer;

    QHBoxLayout* layout;

    QString sliderStyle = VELO_SLIDER_STYLE;

    QVector<QRgb> sliderColor;
    Fonts customfont;
    QString labelText;


    int range;

    int colorTime = 1;

    int r_timer = 0;
    int g_timer = 0;
    int b_timer = 0;

    int r_tmp = 0;
    int g_tmp = 0;
    int b_tmp = 0;

    int ramp_time_delta;

    int max_pos = 0;
    int min_pos = 0;
    int zero_off = 0;
    int ramp_off = 0;
    int man_off_y = 10;
    int man_off_x = 3;

    int ramp_slider_value = 0;
    int scale_factor = 25;

    const int rect_width = 9;
    const int rect_height = 45;

    const int min_width = 350;
    const int min_height = 100;

    int ramp_time = TRAIN_DEFAULT_TIME;
    int speed = TRAIN_DEFAULT_SPEED;

signals:

    void sendRampPaintEvent();
    void sendScalePaintEvent();
    void sendTimeValueChanged();

    void sendTimeSpeed(int time, int speed);

public slots:

    void onStopButton();
    void onTimeValue(int time);

private slots:

    void onValueChanged();

    void onTimer();
    void onColorTimer();

    void onScalePaintEvent();
    void onRampPaintEvent();

protected:

    void paintEvent(QPaintEvent* event) override;

};

#endif // VELOSLIDER_H

