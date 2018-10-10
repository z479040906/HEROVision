/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.10

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_CAMERA_H
#define HERORM2019_CAMERA_H

#include <opencv2/opencv.hpp>
#include "RMVideoCapture.hpp"
#include "worker.h"

using namespace cv;

class MonoCamera:Worker{
public:

private:
    RMVideoCapture camera;
    int current_frame;
public:
    MonoCamera();
    ~MonoCamera();
    Mat getImage();
private:

};


class StereoCamera:Worker{
public:

private:
    RMVideoCapture camera_left;
    int exposure_time_left;
    int width_left;
    int height_left;
    int current_frame_left;

    RMVideoCapture camera_right;
    int exposure_time_right;
    int width_right;
    int height_right;
    int current_frame_right;
public:
    StereoCamera();
    ~StereoCamera();
    Mat getImageLeft();
    Mat getImageRight();
private:

};


#endif //HERORM2019_CAMERA_H
