/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.10

 Detail:
 *****************************************************************************/
#include <iostream>

#include "timer.h"

using namespace std;
using namespace cv;

Timer::Timer() {
    time_start=0;
    time_end=0;
    timer_status=STANDBY;
}

Timer::~Timer() {

}

void Timer::start() {
    time_start=clock();
    timer_status=RUNNING;
}

double Timer::restart() {
    double temp_time=getTime();
    time_start=getTickCount();
    return temp_time;
}

void Timer::stop() {
    time_start=0.0;
    timer_status=STANDBY;
}

inline double Timer::getTime() {
    double delta_time;
    assert(timer_status==RUNNING);
    time_end=clock();
    delta_time= static_cast<double>(time_end-time_start);
    return delta_time*1000.0/CLOCKS_PER_SEC;
}