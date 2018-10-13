/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.13

 Detail:
 *****************************************************************************/

#include "predictor.h"

Predictor::Predictor() {

}

Predictor::~Predictor() {

}

void Predictor::run(RotatedRect &target) {
    timer.start();
    //TODO:START
    //TODO:In this step,we need transform the target into a signal of CAN,
    //TODO:and push it into the queue of signals.

    //TODO:END
    cout<<"predictor running time:"<<timer.getTime()<<endl;
    timer.stop();
}
}