/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_TARGETSELECTOR_H
#define HERORM2019_TARGETSELECTOR_H

#include <opencv2/opencv.hpp>
#include <vector>

#include "worker.h"
#include "stereosolver.h"

using namespace std;
using namespace cv;

class TargetSelector:Worker {
public:
private:
public:
    TargetSelector();
    ~TargetSelector();
    void run(vector<Armor> &armor_with_position,
             Armor &target);
private:
};


#endif //HERORM2019_TARGETSELECTOR_H
