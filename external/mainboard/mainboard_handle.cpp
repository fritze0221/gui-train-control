#include "mainboard_handle.h"

MainboardHandle::MainboardHandle()
{
    socket = new QLocalSocket(this);

   
    if(TEST){
        
        mainboard = connection_init(DUMMY_MB, MB_PORT);
        
    }
    
    else{
        
        mainboard = connection_init(MB, MB_PORT);
        
    }
    
    connect(socket, &QLocalSocket::connected, this, &MainboardHandle::onConnected);
    connect(socket, &QLocalSocket::readyRead, this, &MainboardHandle::onDataReceived);
    connect(socket, &QLocalSocket::errorOccurred, this, &MainboardHandle::onErrorOccurred);
    
    connect(this, &MainboardHandle::sendStartRoutie,this, &MainboardHandle::onStartRoutine);
}


void MainboardHandle::sendID()
{

    QByteArray id = QByteArray::number(MAINBOARD);

    if (socket->state() == QLocalSocket::ConnectedState)
    {
        qDebug() << "Socket verbunden, sende Daten...";
        socket->write(id);
        socket->flush();
    }
    else
    {
        qDebug() << "Fehler: Socket ist nicht verbunden!";
    }
}

void MainboardHandle::connectToServer()
{
    qDebug() << "Prozess versucht, sich mit dem Server zu verbinden...";
    socket->connectToServer("API");
}

void MainboardHandle::onConnected()
{
    qDebug() << "Prozess erfolgreich mit dem Server verbunden!";
}

void MainboardHandle::onDataReceived()
{

    QByteArray data = socket->readAll();  // Daten aus Socket holen
    QDataStream in(&data, QIODevice::ReadOnly);

    qint32 vectorSize = 0;
    in >> vectorSize;

    receivedVec.reserve(vectorSize);  

    for (qint32 i = 0; i < vectorSize; ++i) {
        qint32 num;
        in >> num;
        receivedVec[i] = num;
    }

    qDebug() << receivedVec;

    emit sendStartRoutie();

}

void MainboardHandle::onStartRoutine(){

        if(receivedVec[HOUSE_1_LED+HOUSE_2_LED+2]){
            
            qDebug() << "LED";
            
            for(int i = 0;i < HOUSE_1_LED+HOUSE_2_LED;i++){
                                
                if(receivedVec[i] == 0){
                    
                    mainboard_setLed(mainboard,i,0);
                    
                }
                else{
                    
                    mainboard_setLed(mainboard,i,4096);
                    
                }
                
            }
            
        }
   

        if(receivedVec[HOUSE_1_LED+HOUSE_2_LED+3]){
            
            qDebug() << "Turbine";

            if(receivedVec[HOUSE_1_LED+HOUSE_2_LED] == 0){
                
                mainboard_setLed(mainboard,HOUSE_1_LED+HOUSE_2_LED,0);
                
            }
            else{
                
                mainboard_setLed(mainboard,HOUSE_1_LED+HOUSE_2_LED,800);
                
                
            }
            
        }

        mainboard_writeLed(mainboard);

        if(receivedVec[HOUSE_1_LED+HOUSE_2_LED+4]){
            
            qDebug() << "Switch";   

            if(receivedVec[HOUSE_1_LED+HOUSE_2_LED+1] == 0){
                
                mainboard_setWeiche( mainboard, 1, 0 ); // 0 .. 1
                mainboard_setWeiche( mainboard, 0, 0 ); // 0 .. 1
                
            }
            else{
                
                mainboard_setWeiche( mainboard, 1, 1 ); // 0 .. 1
                mainboard_setWeiche( mainboard, 0, 1 ); // 0 .. 1
                
            }
            
        }
        
        
        


}


void MainboardHandle::onErrorOccurred(QLocalSocket::LocalSocketError error)
{
    qDebug() << "Fehler im Kindprozess-Socket:" << error;

    emit sendQuit();
    
}
