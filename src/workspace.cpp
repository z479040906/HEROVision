/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.9

 Detail:
 *****************************************************************************/

#include "workspace.h"

Workspace::Workspace() {
    //TODO
}

Workspace::~Workspace() {
    //TODO
}

bool Workspace::init(char *stereo_camera_left,char *stereo_camera_right,char *mono) {
    //TODO
    stereo_camera = new StereoCamera(stereo_camera_left,stereo_camera_right);
    mono_camera = new MonoCamera(mono);
    return true;
}

bool Workspace::config(char *stereo_config_filename,
                       char *mono_config_filename,
                       char *armor_param_filename,
                       char *rune_config_filename) {
    stereo_camera->init(stereo_config_filename);
    mono_camera->init(mono_config_filename);
    armor_finder.init(armor_param_filename);
//    rune_object.init(rune_config_filename);
}

bool Workspace::image_receiving_thread_func() {
    //TODO

    while(true){
        if(row_image_buffer_right.size()!=row_image_buffer_left.size()){
            row_image_buffer_left.clear();
            row_image_buffer_right.clear();
        }
        if(row_image_buffer_left.size()<row_image_buffer_stereo_maxsize) {
            row_image_buffer_left.push_back(stereo_camera->getImageLeft());
        }
        if(row_image_buffer_right.size()<row_image_buffer_stereo_maxsize){
            row_image_buffer_right.push_back(stereo_camera->getImageRight());
        }
        if(row_image_buffer_mono.size()<row_image_buffer_mono_maxsize) {
            row_image_buffer_mono.push_back(mono_camera->getImage());
        }
    }
    return true;
}

bool Workspace::image_processing_thread_func() {
    //TODO: Load several threads to process the image

    thread t1(&ArmorPreprocessor::run,armor_preprocessor,row_image_buffer_left,preprocessed_buffer_left);
    thread t2(&ArmorPreprocessor::run,armor_preprocessor,row_image_buffer_right,preprocessed_buffer_right);
    thread t3(&ContoursFinder::run,contours_finder,preprocessed_buffer_left,contours_left);
    thread t4(&ContoursFinder::run,contours_finder,preprocessed_buffer_right,contours_right);
    thread t5(&ArmorFinder::run,armor_finder,contours_left,armors_left);
    thread t6(&ArmorFinder::run,armor_finder,contours_right,armors_right);
    thread t7(&StereoSolver::run,stereo_solver,armors_left,armors_right,armor_with_position);
    thread t8(&TargetSelector::run,target_selector,armor_with_position,target);
    thread t9(&Predictor::run,predictor,target/*,signal_queue*/);
//    thread(&AngleSolver::run(),angle_solver);
//    thread(&TargetSelector::run(),target_selector);

//    while(true) {
//        this->timer.start();
//        processing_loop();
//        cout<<"processing_loop running time:"<<this->timer.restart()<<endl;
//    }
    return true;
}

bool Workspace::message_communication_thread_func(){
    //TODO
    while(true){

    }
    return true;
}

void Workspace::setPtzAngle(int angle) {

}

void Workspace::setMode(int mode){
    if(mode==work_mode){
        return;
    }
    switch(mode){
        case MODE::WAITING:
            work_mode=MODE::WAITING;
            break;
        case MODE::ARMOR_RED:
            work_mode=MODE::ARMOR_RED;
            break;
        case MODE::ARMOR_BLUE:
            work_mode=MODE::ARMOR_BLUE;
            break;
        case MODE::RUNE_SMALL:
            work_mode=MODE::RUNE_SMALL;
            break;
        case MODE::RUNE_LARGE:
            work_mode=MODE::RUNE_LARGE;
            break;
        default:
            work_mode=WAITING;
    }
}

bool Workspace::processing_loop() {
    //TODO:we need to fill the function to let the assembly line work
    //there will be several threads to be every part of the assembly line
    return true;
}