/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.10

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_TIMER_H
#define HERORM2019_TIMER_H

#include <opencv2/opencv.hpp>
//#include <time.h>

class Timer {
private:
    enum{
        STANDBY,
        RUNNING
    };
    clock_t time_start;
    clock_t time_end;
    int8_t timer_status;
public:
    Timer();
    ~Timer();
    void start();
    double restart();
    void stop();
    inline double getTime();
};


#endif //HERORM2019_TIMER_H
