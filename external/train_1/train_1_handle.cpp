#include "train_1_handle.h"

TrainHandle::TrainHandle()
{
    socket = new QLocalSocket(this);

   
    if(TEST){
        
        train = connection_init(DUMMY_B, TRAIN_PORT_B);
        
    }
    
    else{
        
        train = connection_init(TRAIN_B, TRAIN_PORT_B);
        
    }
    
    connect(socket, &QLocalSocket::connected, this, &TrainHandle::onConnected);
    connect(socket, &QLocalSocket::readyRead, this, &TrainHandle::onDataReceived);
    connect(socket, &QLocalSocket::errorOccurred, this, &TrainHandle::onErrorOccurred);
    
    connect(this, &TrainHandle::sendStartRoutie,this, &TrainHandle::onStartRoutine);
}


void TrainHandle::sendID()
{

    QByteArray id = QByteArray::number(TRAIN_1);

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

void TrainHandle::connectToServer()
{
    qDebug() << "Prozess versucht, sich mit dem Server zu verbinden...";
    socket->connectToServer("API");
}

void TrainHandle::onConnected()
{
    qDebug() << "Prozess erfolgreich mit dem Server verbunden!";
}

void TrainHandle::onDataReceived()
{

    QByteArray data = socket->readAll();  // Daten aus Socket holen
    QDataStream in(&data, QIODevice::ReadOnly);

    qint32 vectorSize = 0;
    in >> vectorSize;

    QVector<int> receivedVec;
    receivedVec.reserve(vectorSize);  

    for (qint32 i = 0; i < vectorSize; ++i) {
        qint32 num;
        in >> num;
        receivedVec.append(num);
    }

    for(int i = 0;i < vectorSize;i++){

        qDebug() << receivedVec[i];

    };  

    time = receivedVec[0];
    speed = receivedVec[1];

    emit sendStartRoutie();

}

void TrainHandle::onStartRoutine(){

    if(speed >= 0)  train_setDirection(train,FORWARD);
    if(speed < 0) train_setDirection(train, BACKWARD);

    int true_speed = ((float)TRAIN_MAX_SPEED/(float)VELO_RANGE)*(float)abs(speed);

    if(MODULE_RAMP && time != 0){

        train_setRamp(train, true_speed,time);

    }
    else{

        train_setSpeed(train, true_speed);
    }


}


void TrainHandle::onErrorOccurred(QLocalSocket::LocalSocketError error)
{
    qDebug() << "Fehler im Kindprozess-Socket:" << error;

    emit sendQuit();

    
}
