/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Mark Chang on 2018.10.18

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_CONTOURSFINDER_H
#define HERORM2019_CONTOURSFINDER_H

#include <opencv2/opencv.hpp>
#include <vector>

#include "armorpreprocessor.h"
#include "worker.h"

//#define DEBUG_SHOW

using namespace std;
using namespace cv;

class ContoursFinder:Worker {
public:
private:
public:
    ContoursFinder();
    ~ContoursFinder();
    void run(vector<Frame> &preprocessed_buffer,
             vector<RotatedRect> &contours);
private:

};


#endif //HERORM2019_CONTOURSFINDER_H
