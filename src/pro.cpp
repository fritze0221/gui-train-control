#include "pro.h"

MainWindow::MainWindow(QApplication* app)
{

    oApiHandler = new ApiHandler();

    wTraincontrol1 = new Traincontrol(this,TRAIN_1);
    wTraincontrol2 = new Traincontrol(this, TRAIN_2);

    wLedcontrol1 = new Ledcontrol(this, HOUSE_1, HOUSE_1_LED);
    wLedcontrol2 = new Ledcontrol(this, HOUSE_2, HOUSE_2_LED);

    wSwitchcontrol = new Switchcontrol(this);

    wTurbincontrol = new Turbincontrol(this);

    connect(wTraincontrol1, &Traincontrol::sendAPITrain, oApiHandler, &ApiHandler::onTimeSpeedTrain);
    connect(wTraincontrol2, &Traincontrol::sendAPITrain, oApiHandler, &ApiHandler::onTimeSpeedTrain);

    connect(wSwitchcontrol, &Switchcontrol::sendAPISwitch, oApiHandler, &ApiHandler::onSwitch);

    connect(wTurbincontrol, &Turbincontrol::sendAPITubin, oApiHandler, &ApiHandler::onTurbin);

    connect(wLedcontrol1, &Ledcontrol::sendAPILed, oApiHandler, &ApiHandler::onIndexStateHouse);
    connect(wLedcontrol2, &Ledcontrol::sendAPILed, oApiHandler, &ApiHandler::onIndexStateHouse);

    connect(this, &MainWindow::destroyed, app, &QApplication::quit);

    centralWidget = new QWidget(this);

    trainlayout = new QHBoxLayout();

    trainlayout->addWidget(wTraincontrol1);
    trainlayout->addWidget(wTraincontrol2);

    ledlayout = new QVBoxLayout();

    ledlayout->addWidget(wLedcontrol1);
    ledlayout->addWidget(wLedcontrol2);
    ledlayout->addWidget(wTurbincontrol);

    switchlayout = new QVBoxLayout();

    switchlayout->addWidget(wSwitchcontrol);
    switchlayout->addLayout(trainlayout);

    mainLayout = new QHBoxLayout;

    mainLayout->addLayout(ledlayout);
    mainLayout->addLayout(switchlayout);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    setWindowTitle("Control Panel");

}

void MainWindow::screenGeometry(){


    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {

        Resolution = screen->geometry();
        int width = Resolution.width();
        int height = Resolution.height();

        qDebug() << "Bildschirmauflösung:" << width << "x" << height;
    } else {
        qWarning() << "Kein Bildschirm gefunden.";
    }


}

void MainWindow::handleSubWindow(QWidget* Identifier){

    if(!Identifier->isVisible()){ 

        Identifier->show();
        Identifier->move(MainWindowPos + QPoint(MainWindowSize.width(),0));
    }
    

    else{

        Identifier->close();

    }

}

void MainWindow::resizeEvent(QResizeEvent *event){

    QWidget::resizeEvent(event);

    MainWindowSize = event->size();

}

void MainWindow::moveEvent(QMoveEvent *event){

    QMainWindow::moveEvent(event);

    MainWindowPos = event->pos();

}

MainWindow::~MainWindow(){

    delete oApiHandler;

}


