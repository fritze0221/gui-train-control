
#include "train_2_handle.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // QTextStream zum Lesen von stdin und Schreiben in stdout
    TrainHandle* child = new TrainHandle;

    QObject::connect(child, &TrainHandle::sendQuit, &app, &QCoreApplication::quit);

    child->connectToServer(); 
    child->sendID();


    return app.exec();
}