#include "apihandler.h"

ApiHandler::ApiHandler(){

    init();

    server = new QLocalServer();
    server->removeServer("API");

    if (!server->listen("API")) {
        qDebug() << "Fehler: Server konnte nicht gestartet werden!";
    }

    connect(server, &QLocalServer::newConnection, this, &ApiHandler::onServerConnection);

    train_1 = new QProcess;
    train_2 = new QProcess;
    mb = new QProcess;

    QString train_1_path = "/home/urs/uni/cpp-gui/qt_project/build/Api-Build/train1";
    QString train_2_path = "/home/urs/uni/cpp-gui/qt_project/build/Api-Build/train2";
    QString mb_path = "/home/urs/uni/cpp-gui/qt_project/build/Api-Build/mainboard";

    train_1->start(train_1_path);
    train_2->start(train_2_path);
    mb->start(mb_path);

    connect(this, &ApiHandler::stateChange, this, &ApiHandler::onStateChange);

}

void ApiHandler::onTimeSpeedTrain(int time, int speed,int train_id){

    if(MODULE_TRAIN){


        if(train_id == TRAIN_1){

            train_1_states[0] = time;
            train_1_states[1] = speed;

            train_1_state_change = true;

        }

        if(train_id == TRAIN_2){

            train_2_states[0] = time;
            train_2_states[1] = speed;

            train_2_state_change = true;

        }

        emit stateChange();

    }
}

void ApiHandler::onIndexStateHouse(QVector<int> states, int house_id){


    if(MODULE_LED){

        updateMB(states, house_id);

        mb_state_change = true;
        emit stateChange();

    }
}

void ApiHandler::onSwitch(){

    if(MODULE_SWITCH){

        updateMB(SWITCH);

        mb_state_change = true;
        emit stateChange();
    }
}

void ApiHandler::onTurbin(){

    if(MODULE_TURBINE){

        updateMB(TURBINE);

        mb_state_change = true;
        emit stateChange();
    }
}

void ApiHandler::onStateChange(){

    if(train_1_state_change && (train_1_socket->state() == QLocalSocket::ConnectedState)){

        sendData(TRAIN_1);

        train_1_state_change = false;

    }

    if(train_2_state_change && (train_2_socket->state() == QLocalSocket::ConnectedState)){

        sendData(TRAIN_2);

        train_2_state_change = false;

    }

    if(mb_state_change && (mainboard_socket->state() == QLocalSocket::ConnectedState)){

        sendData(MAINBOARD);

        mb_state_change = false;

        mb_states[HOUSE_1_LED+HOUSE_2_LED+2] = 0;
        mb_states[HOUSE_1_LED+HOUSE_2_LED+3] = 0;
        mb_states[HOUSE_1_LED+HOUSE_2_LED+4] = 0;

    }



}



void ApiHandler::updateMB(QVector<int> states, int house_id){


    if(house_id == HOUSE_1){

        for(int i = 0;i < HOUSE_1_LED;i++){

            mb_states[i] = states[i];

        }

    }

    if(house_id == HOUSE_2){

        for(int i = 0;i < HOUSE_2_LED;i++){

            mb_states[i+HOUSE_1_LED] = states[i];

        }

    }

    mb_states[HOUSE_1_LED+HOUSE_2_LED+2] = 1;


}

void ApiHandler::updateMB(int identifier){

    if(identifier == TURBINE){

        int tmp = mb_states[HOUSE_1_LED+HOUSE_2_LED];

        if(tmp == 0){

            mb_states[HOUSE_1_LED+HOUSE_2_LED] = 1;
        }
        else{

            mb_states[HOUSE_1_LED+HOUSE_2_LED] = 0;
        }

        mb_states[HOUSE_1_LED+HOUSE_2_LED+3] = 1;

    }

    if(identifier == SWITCH){

        int tmp = mb_states[HOUSE_1_LED+HOUSE_2_LED+1];

        if(tmp == 0){

            mb_states[HOUSE_1_LED+HOUSE_2_LED+1] = 1;
        }
        else{

            mb_states[HOUSE_1_LED+HOUSE_2_LED+1] = 0;
        }

        mb_states[HOUSE_1_LED+HOUSE_2_LED+4] = 1;
    }
}

void ApiHandler::onServerConnection(){

    qDebug() << "New Connection";

    QLocalSocket* client = server->nextPendingConnection();

    tmp_client.append(client);

    int size = tmp_client.size();

    connect(client, &QLocalSocket::readyRead, this, [=](){onDataReceived(size-1);});
    connect(client, &QLocalSocket::errorOccurred, this, &ApiHandler::onErrorOccurred);

}

void ApiHandler::onDataReceived(int id){

    qDebug() << id;

    QByteArray data = tmp_client[id]->readAll();


    if(data.toInt() == TRAIN_1){

        train_1_socket = tmp_client[id];

        sendData(TRAIN_1);

        qDebug() << "Train 1 Connected";

    }

    if(data.toInt() == TRAIN_2){

        train_2_socket = tmp_client[id];

        sendData(TRAIN_2);

        qDebug() << "Train 2 Connected";

    }

    if(data.toInt() == MAINBOARD){

        mainboard_socket = tmp_client[id];

        qDebug() << "Mainboard Connected";

    }

}

void ApiHandler::sendData(int identifier){

    if(identifier == TRAIN_1){

        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out << train_1_states;

        if (train_1_socket->state() == QLocalSocket::ConnectedState) {

            train_1_socket->write(data);
            train_1_socket->flush();

        } else {
            qDebug() << "Fehler: Socket ist nicht verbunden!";
        }

    }

    if(identifier== TRAIN_2){

        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out << train_2_states;

        if (train_2_socket->state() == QLocalSocket::ConnectedState) {

            train_2_socket->write(data);
            train_2_socket->flush();

        } else {
            qDebug() << "Fehler: Socket ist nicht verbunden!";
        }

    }

    if(identifier== MAINBOARD){

        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out << mb_states;

        if (mainboard_socket->state() == QLocalSocket::ConnectedState) {

            mainboard_socket->write(data);
            mainboard_socket->flush();

        } else {
            qDebug() << "Fehler: Socket ist nicht verbunden!";
        }

    }

}

void ApiHandler::onErrorOccurred(QLocalSocket::LocalSocketError error)
{
    qDebug() << "Fehler im Kindprozess-Socket:" << error;
}

void ApiHandler::init(){

    train_1_states.resize(2);
    train_1_states[0] = 2000;
    train_1_states[1] = 0;

    train_2_states.resize(2);
    train_2_states[0] = 2000;
    train_2_states[1] = 0;

    mb_states.resize(HOUSE_1_LED+HOUSE_2_LED+5);

    for(int i = 0;i < mb_states.size();i++){

        mb_states[i] = 0;

    }

}

