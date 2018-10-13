/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.10

 Detail:
 *****************************************************************************/

#include "timer.h"

using namespace cv;

Timer::Timer() {
    time_start=0.0;
    time_end=0.0;
    timer_status=STANDBY;
}

Timer::~Timer() {

}

void Timer::start() {
    time_start=getTickCount();
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
    assert(timer_status==RUNNING);
    time_end=getTickCount();
    return (time_end-time_start)*1000/getCPUTickCount();
}