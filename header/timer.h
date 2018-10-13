/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.10

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_TIMER_H
#define HERORM2019_TIMER_H

#include <opencv2/opencv.hpp>

class Timer {
private:
    enum{
        STANDBY,
        RUNNING
    };
    double time_start;
    double time_end;
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
