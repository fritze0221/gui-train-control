
#include "mainboard_handle.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // QTextStream zum Lesen von stdin und Schreiben in stdout
    MainboardHandle* process = new MainboardHandle;

    QObject::connect(process, &MainboardHandle::sendQuit, &app, &QCoreApplication::quit);

    process->connectToServer(); 
    process->sendID();

    return app.exec();
}