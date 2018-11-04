/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.13

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_PREDICTOR_H
#define HERORM2019_PREDICTOR_H

#include <opencv2/opencv.hpp>

#include "worker.h"

using namespace std;
using namespace cv;

class Predictor:Worker {
public:
private:
public:
    Predictor();
    ~Predictor();
    void run(Armor &target/**,queue<Signal> signal_queue**/);
private:
};


#endif //HERORM2019_PREDICTOR_H
