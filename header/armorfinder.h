/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_ARMORFINDER_H
#define HERORM2019_ARMORFINDER_H

#include <opencv2/opencv.hpp>
#include <vector>

#include "worker.h"

using namespace std;
using namespace cv;

class ArmorFinder:Worker {
public:

private:

public:
    ArmorFinder();
    ~ArmorFinder();
    void init(char *armor_param_filename);
    void run(vector<vector<Point2f>> &contours,
             vector<RotatedRect> &armors);
private:

};


#endif //HERORM2019_ARMORFINDER_H
