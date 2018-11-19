/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.11.12

 Detail:
 *****************************************************************************/

 //TODO:将卡尔曼滤波器类更新为滤波器类

#include "kalmanfilter.h"

RMKalmanFilter::RMKalmanFilter(){

}

RMKalmanFilter::~RMKalmanFilter(){

}

void RMKalmanFilter::init(double input_Q,double input_R){
    A=1;
    H=1;
    Q=input_Q;
    R=input_R;
    last_P=10;
    last_value=0;
}

double RMKalmanFilter::run(double measure_value){
    double predict_value=0.0,predict_P=0.0,kalman_gain;
    predict_value=A*last_value;
    predict_P=A*A*last_P+Q;
    kalman_gain=(H*predict_P)/(H*H*predict_P+R);
    last_value=predict_value+kalman_gain*(measure_value-H*predict_value);
    last_P=(1-H*kalman_gain)*predict_P;
    return last_value;
}
