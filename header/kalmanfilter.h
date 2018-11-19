/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.11.12

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_RMKALMANFILTER_H
#define HERORM2019_RMKALMANFILTER_H


#include "worker.h"

class RMKalmanFilter:Worker {
public:
private:
    double A;
    double H;
    double Q;
    double R;
    double last_P;
    double last_value;
public:
    RMKalmanFilter();
    ~RMKalmanFilter();
    void init(double input_Q,double input_R);
    double run(double measure_value);
private:
    
};
#endif // HERORM2019_KALMANFILTER_H