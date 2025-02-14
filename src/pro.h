#include <QApplication>
#include <QFontDatabase>

#include "turbinecontrol.h"
#include "traincontrol.h"
#include "ledcontrol.h"
#include "switchcontrol.h"
#include "apihandler.h"

#include "config.h"

class MainWindow : public QMainWindow{

Q_OBJECT

public:

    MainWindow(QApplication* app);
    ~MainWindow();

private:

    void screenGeometry();

    Traincontrol* wTraincontrol1;
    Traincontrol* wTraincontrol2;

    Ledcontrol* wLedcontrol1;
    Ledcontrol* wLedcontrol2;

    Switchcontrol* wSwitchcontrol;

    Turbincontrol* wTurbincontrol;

    ApiHandler* oApiHandler;

    QHBoxLayout *trainlayout;
    QWidget* centralWidget;
    QVBoxLayout *ledlayout;
    QVBoxLayout *switchlayout;
    QHBoxLayout *mainLayout;

    QSize MainWindowSize;
    QPoint MainWindowPos;

    QRect Resolution;

public slots:
    void handleSubWindow(QWidget* Identifier);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
};

