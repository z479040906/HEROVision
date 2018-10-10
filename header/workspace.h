/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.9

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_WORKSPACE_H
#define HERORM2019_WORKSPACE_H

#include <opencv2/opencv.hpp>
#include <vector>

#include "camera.h"

using namespace std;
using namespace cv;

class Workspace {
private:
    enum MODE{
        ARMOR_RED,
        ARMOR_BLUE,
        RUNE_LARGE,
        RUNE_SMALL
    };

    StereoCamera stereo_camera;
    MonoCamera mono_camera;


public:
    Workspace();
    ~Workspace();
    bool init(char *armor_config_filename,char *rune_config_filename);
    bool image_receiving_thread_func();
    bool image_processing_thread_func();
    bool message_listener_thread_func();
private:

};


#endif //HERORM2019_WORKSPACE_H
