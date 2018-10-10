/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.10

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_TIMER_H
#define HERORM2019_TIMER_H

#include <opencv2/opencv.hpp>

class Timer {
public:
    Timer();
    ~Timer();
    bool start();
    double restart();
    void stop();
    double getTime();
private:
    double time_start;
    double time_end;
};


#endif //HERORM2019_TIMER_H
