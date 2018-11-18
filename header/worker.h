/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.10

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_WORKER_H
#define HERORM2019_WORKER_H

#include <iostream>
#include <vector>

#include "timer.h"

class Worker {
protected:
    Timer timer;
public:
    Worker();
    ~Worker();
};


#endif //HERORM2019_WORKER_H
