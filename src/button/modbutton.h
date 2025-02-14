#ifndef MODBUTTON_H
#define MODBUTTON_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QStyleOptionSlider>
#include <QFontDatabase>
#include <QSizePolicy>
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QStyle>


#include "fonts.h"
#include "style_config.h"


class modButton : public QWidget
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
     *               - `color[0]`: Farbe für den Button (released).
     *               - `color[1]`: Farbe für den Buttonrand (released).
     *               - `color[2]`: Farbe für den Button (pushed).
     *               - `color[3]`: Farbe für den Buttonrand (pushed) .
     * @param text Buttontext.
     * @param mode
     *      - 0 : pressed
     *      - 1 : clicked
     * @param start_cond
     *      - true clicked
     *      - false not clicked
     */


    modButton(QWidget *parent, QVector<QRgb> color, QString text, int mode,bool start_cond);


    QPushButton* button;
    QTimer* buttonTimer;

private:

    int r_tmp = 0;
    int g_tmp = 0;
    int b_tmp = 0;

    QVector<QRgb> ButtonColor;
    QString ButtonText;

    bool clicked_state = true;

    QString buttonStyle = MOD_BUTTON_STYLE;


public slots:

    void onSwitchSignal();

signals:

    void sendButtonClicked();

    void sendSwitchSignal();

private slots:

    void onButtonReleased();
    void onButtonPressed();

    void onButtonClicked();


};

#endif // MODBUTTON_H
