/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/


#ifndef HERORM2019_MEASSAGESENDER_H
#define HERORM2019_MEASSAGESENDER_H

#include "worker.h"

using namespace std;

class MeassageSender:Worker {
public:
private:
public:
    MeassageSender();
    ~MeassageSender();
    void run(/**queue<Signal> &signal_queue**/);
private:
};


#endif //HERORM2019_MEASSAGESENDER_H
