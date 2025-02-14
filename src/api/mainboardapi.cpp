#include "mainboardapi.h"

MainboardAPI::MainboardAPI()
{
    if(TEST)  mb  = connection_init(DUMMY_MB, MB_PORT);
    else{

        mb = connection_init(MB,MB_PORT);
    }

    if(mb->check == -1) CONNECTED = false;

}


void MainboardAPI::onMainboardAPI(){

    if(!CONNECTED){

        if(TEST)  mb  = connection_init(DUMMY_MB, MB_PORT);
        else{

            qDebug() << "Connect to Mainboard ...";
            mb = connection_init(MB,MB_PORT);
        }

        if(mb->check != -1) CONNECTED = true;


    }
    if(CONNECTED){

        if(flag_switch){

            if(states[HOUSE_1_LED+HOUSE_2_LED+1] == 0){

                mainboard_setWeiche( mb, 1, 0 ); // 0 .. 1
                mainboard_setWeiche( mb, 0, 0 ); // 0 .. 1

            }
            else{

                mainboard_setWeiche( mb, 1, 1 ); // 0 .. 1
                mainboard_setWeiche( mb, 0, 1 ); // 0 .. 1

            }

        }

        if(flag_led){


            for(int i = 0;i < HOUSE_1_LED+HOUSE_2_LED;i++){

                qDebug() << states[i];

                if(states[i] == 0){

                    mainboard_setLed(mb,i,0);

                }
                else{

                    mainboard_setLed(mb,i,4096);

                }

            }

        }

        if(flag_turbine){

            if(states[HOUSE_1_LED+HOUSE_2_LED] == 0){

                mainboard_setLed(mb,HOUSE_1_LED+HOUSE_2_LED,0);

            }
            else{

                mainboard_setLed(mb,HOUSE_1_LED+HOUSE_2_LED,800);


            }

        }



        mainboard_writeLed(mb);


    }

    emit finished();

}

void MainboardAPI::setData(QVector<int> sync_states){

    states.resize(sync_states.size());

    for(int i = 0;i < sync_states.size();i++){

        states[i] = sync_states[i];

    }

}

void MainboardAPI::stateChange(bool switch_state, bool led_state, bool turbine_state){

    flag_switch = switch_state;
    flag_led = led_state;
    flag_turbine = turbine_state;

}

MainboardAPI::~MainboardAPI(){

    if(CONNECTED){

        qDebug() << "MB CLOSE";
        connection_close(mb);

    }
}
