#include "pro.h"

int main(int argc, char* argv[]){

    QApplication app(argc, argv);

    MainWindow mainWindow(&app);

    mainWindow.show();

    return app.exec();

}
