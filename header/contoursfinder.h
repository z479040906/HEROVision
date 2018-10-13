/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_CONTOURSFINDER_H
#define HERORM2019_CONTOURSFINDER_H

#include <opencv2/opencv.hpp>
#include <vector>

#include "camera.h"
#include "worker.h"

using namespace std;
using namespace cv;


class ContoursFinder:Worker {
public:

private:

public:
    ContoursFinder();
    ~ContoursFinder();
    void run(vector<Frame> &preprocessed_buffer,
             vector<vector<Point2f>> &contours);
private:

};


#endif //HERORM2019_CONTOURSFINDER_H
