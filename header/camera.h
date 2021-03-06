/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.10

 Update:Zhou Yuxin on 2018.11.18

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_CAMERA_H
#define HERORM2019_CAMERA_H

#include <opencv2/opencv.hpp>
#include "RMVideoCapture.hpp"
#include "worker.h"

using namespace cv;

typedef struct{
    Mat image;
    int frame_number=0;
}Frame;

class MonoCamera:Worker{
public:

private:
    RMVideoCapture *camera;
    int exposure_time;
    int frame_width;
    int frame_height;
    int current_frame;
    int frame_per_second;
public:
    MonoCamera(const char *device);
    ~MonoCamera();
    void init(char *mono_config_filename);
    Frame getImage();
    void setExposureTime(bool is_auto,int exposure_time);
private:

};


class StereoCamera:Worker{
public:

private:
    //left_param
    RMVideoCapture *camera_left;
    int exposure_time_left;
    int width_left;
    int height_left;
    int current_frame_left;

    //right_param
    RMVideoCapture *camera_right;
    int exposure_time_right;
    int width_right;
    int height_right;
    int current_frame_right;

    //common_param
    double base_length;
    double focus_distance;

public:
    StereoCamera(char *device_left, char *device_right);
    ~StereoCamera();
    void init(char *stereo_config_filename);
    Frame getImageLeft();
    Frame getImageRight();
    void setExposureTime(bool is_auto,int exposure_time);

private:

};


#endif //HERORM2019_CAMERA_H
