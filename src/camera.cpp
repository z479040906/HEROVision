/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.10

 Update:Zhou Yuxin on 2018.11.18

 Detail:
 *****************************************************************************/

#include <camera.h>
#include <armorpreprocessor.h>
#include "camera.h"

MonoCamera::MonoCamera(const char *device) {
    camera=new RMVideoCapture(device);
    camera->info();
    current_frame=0;
}

MonoCamera::~MonoCamera() {
    delete camera;
}

void MonoCamera::init(char *mono_config_filename) {
    FileStorage filestorage(mono_config_filename,FileStorage::READ);
    filestorage["exposure_time"]>>exposure_time;
    filestorage["frame_width"]>>frame_width;
    filestorage["frame_height"]>>frame_height;
    filestorage["frame_per_second"]>>frame_per_second;
    camera->setExposureTime(false,exposure_time);
    camera->setVideoFPS(frame_per_second);
    camera->changeVideoFormat(frame_width,frame_height);
}

Frame MonoCamera::getImage() {
    Frame frame_temp;
    *camera>>frame_temp.image;
    frame_temp.frame_number=current_frame++;
    return frame_temp;
}

void MonoCamera::setExposureTime(bool is_auto, int exposure_time) {
    this->exposure_time=exposure_time;
    camera->setExposureTime(is_auto,exposure_time);
}

StereoCamera::StereoCamera(char *device_left, char *device_right) {
    camera_left=new RMVideoCapture(device_left);
    camera_right=new RMVideoCapture(device_right);
    current_frame_left=0;
    current_frame_right=0;
}

StereoCamera::~StereoCamera() {

}

void StereoCamera::init(char *stereo_config_filename) {
    FileStorage filestorage(stereo_config_filename,FileStorage::READ);
    filestorage["exposure_time_left"]>>exposure_time_left;
    filestorage["width_left"]>>width_left;
    filestorage["height_left"]>>height_left;
    camera_left->setExposureTime(false,exposure_time_left);
    filestorage["exposure_time_right"]>>exposure_time_right;
    filestorage["width_right"]>>width_right;
    filestorage["height_right"]>>height_right;
    camera_right->setExposureTime(false,exposure_time_right);
}

inline Frame StereoCamera::getImageLeft() {
    Frame frame_temp;
    *camera_left>>frame_temp.image;
    frame_temp.frame_number=camera_left->getFrameCount();
    return frame_temp;
}

inline Frame StereoCamera::getImageRight() {
    Frame frame_temp;
    *camera_right>>frame_temp.image;
    frame_temp.frame_number=camera_right->getFrameCount();
    return frame_temp;
}

void StereoCamera::setExposureTime(bool is_auto, int exposure_time) {
    this->exposure_time_left=exposure_time;
    this->exposure_time_right=exposure_time;
    camera_left->setExposureTime(is_auto,exposure_time_left);
    camera_right->setExposureTime(is_auto,exposure_time_right);
}