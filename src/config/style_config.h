#include <QRgb>
#include <QVector>



#define MOD_BUTTON_STYLE R"(
                QPushButton {
                    background-color: rgb(%1,%2,%3); /* Heller Hintergrund für den Button */
                    border: 4px solid rgb(%4,%5,%6); /* Auffälliger blauer Rahmen */
                    border-radius: 8px; /* Abgerundete Ecken */
                    height: 20 px;
                }
                )"

#define LED_GRID_SLIDER_STYLE  R"(
                QSlider::groove:horizontal {
                height: 6px;
                background: transparent;
                margin: 8px;
                border: 1px solid #c17d08;
                border-radius: 12px;
                }

                QSlider::sub-page:horizontal {
                background: rgb(%1,%2,%3);
                height: 6px;
                border-radius: 12px;
                }

                QSlider::add-page:horizontal {
                background: rgb(%4, %5, %6);
                height: 10px;
                border-radius: 12px;
                }

                QSlider::handle:horizontal {
                background: transparent;
                margin: -10px;
                border: 1px solid transparent;
                border-radius: 5px;
                }
            )";

#define ACC_SLIDER_STYLE R"(
                QSlider::groove:vertical {
                width: 6px;
                background: transparent;
                margin: 8px;
                border: 1px solid #c17d08;
                border-radius: 12px;
                }

                QSlider::sub-page:vertical {
                background: rgb(%1,%2,%3);
                width: 6px;
                border-radius: 12px;
                }

                QSlider::add-page:vertical {
                background: rgb(232, 218, 218);
                width: 10px;
                border-radius: 12px;
                }

                QSlider::handle:vertical {
                background: transparent;
                margin: -10px;
                border: 1px solid transparent;
                border-radius: 5px;
                }
            )"

#define VELO_SLIDER_STYLE R"(
                QSlider::groove:horizontal {
                height: 6px;
                background: transparent;
                margin: 8px;
                border: 1px solid #c17d08;
                border-radius: 12px;
                }

                QSlider::sub-page:horizontal {
                background: rgb(%1,%2,%3);
                height: 6px;
                border-radius: 12px;
                }

                QSlider::add-page:horizontal {
                background: rgb(%4, %5, %6);
                height: 10px;
                border-radius: 12px;
                }

                QSlider::handle:horizontal {
                background: transparent;
                margin: -10px;
                border: 1px solid transparent;
                border-radius: 5px;
                }
            )"

//LEDCONTROL

#define LED_CONTROL_COLOR_LED_GRID { qRgb(214, 51, 21), qRgb(21, 21, 54), qRgb(55, 47, 147), qRgb(21, 21, 141) }

#define LED_CONTROL_COLOR_RESET_BUTTON { qRgb(12,23,123), qRgb(112,21,21), qRgb(112,21,21), qRgb(12,23,123) }

#define LED_CONTROL_COLOR_ALL_BUTTON { qRgb(12,23,123), qRgb(112,21,21), qRgb(112,21,21), qRgb(12,23,123) }

#define LED_CONTROL_COLOR_BACKGROUND qRgb(89,89,89)

//SWITCHCONTROL

#define SWITCH_CONTROL_COLOR_INNER_BUTTON { qRgb(31,131,13), qRgb(12,12,43), qRgb(123,112,32), qRgb(123,57,23) }

#define SWITCH_CONTROL_COLOR_OUTER_BUTTON { qRgb(31,131,13), qRgb(12,12,43), qRgb(123,112,32), qRgb(123,34,32) }

#define SWITCH_CONTROL_COLOR_BACKGROUND qRgb(89,89,89)

//TRAINCONTROL

#define TRAIN_CONTROL_COLOR_VELO_SLIDER  { qRgb(110, 144, 212), qRgb(255, 255, 255), qRgb(110, 144, 212), qRgb(57, 61, 48) }

#define TRAIN_CONTROL_COLOR_ACC_SLIDER { qRgb(173, 101, 114) }

#define TRAIN_CONTROL_COLOR_STOP_BUTTON { qRgb(242, 46, 46), qRgb(240, 91, 91), qRgb(173, 26, 26), qRgb(186, 74, 74) }

#define TRAIN_1_CONTROL_COLOR_BACKGROUND qRgb(138, 44, 72)

#define TRAIN_2_CONTROL_COLOR_BACKGROUND qRgb(140, 204, 20)

//TURBINECONTROL

#define TURBINE_CONTROL_COLOR_BUTTON_COLOR { qRgb(12,23,123), qRgb(112,21,21), qRgb(112,21,21), qRgb(12,23,123) }

#define TURBINE_CONTROL_COLOR_BACKGROUND qRgb(89,89,89)
