/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_STEREOSOLVER_H
#define HERORM2019_STEREOSOLVER_H

#include <opencv2/opencv.hpp>
#include <vector>

#include "worker.h"

using namespace std;
using namespace cv;

typedef struct {
    int depth;
    int x;
    int y;
    double yaw;
    double pitch;
    RotatedRect rect_left;
    RotatedRect rect_right;
}Armor;

class StereoSolver:Worker {
public:

private:

public:
    StereoSolver();
    ~StereoSolver();
    void run(vector<RotatedRect> &armors_left,
             vector<RotatedRect> &armors_right,
             vector<Armor> &armor_with_position);
private:

};


#endif //HERORM2019_STEREOSOLVER_H
