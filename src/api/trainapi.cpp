#include "trainapi.h"

TrainAPI::TrainAPI(int train_id)
    :train_id(train_id)
{

    if(train_id == TRAIN_1){

        if(TEST){

            train = connection_init(DUMMY_B, TRAIN_PORT_B);

        }

        else{

            train = connection_init(TRAIN_B, TRAIN_PORT_B);

        }

    }

    else{

        if(TEST){

            train = connection_init(DUMMY_Y, TRAIN_PORT_Y);

        }
        else{

            train = connection_init(TRAIN_Y, TRAIN_PORT_Y);

        }

    }

}

void TrainAPI::setData(int set_time, int set_speed)
{

    speed = set_speed;
    time = set_time;

}

void TrainAPI::onTrainAPI(){

    handleConnection();

}



void TrainAPI::handleConnection(){


    if(speed >= 0)  train_setDirection(train,FORWARD);
    if(speed < 0) train_setDirection(train, BACKWARD);

    true_speed = ((float)TRAIN_MAX_SPEED/(float)VELO_RANGE)*(float)abs(speed);

    if(MODULE_RAMP && time != 0){

        train_setRamp(train, true_speed,time);

    }
    else{

        train_setSpeed(train, true_speed);
    }


    emit finished();
}




TrainAPI::~TrainAPI(){



}
