/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.9

 Detail:
 *****************************************************************************/

 //TODO:完成主体框架的流程，加入插值部分。

#include "workspace.h"

Workspace::Workspace() {
    //TODO
}

Workspace::~Workspace() {
    //TODO
}

bool Workspace::init(char *mono_camera_name) {
    //TODO
//    stereo_camera = new StereoCamera(stereo_camera_left,stereo_camera_right);
    mono_camera = new MonoCamera(mono_camera_name);
    return true;
}

bool Workspace::init(char *stereo_camera_left,char *stereo_camera_right,char *mono_camera_name) {
    //TODO
//    stereo_camera = new StereoCamera(stereo_camera_left,stereo_camera_right);
    mono_camera = new MonoCamera(mono_camera_name);
    return true;
}

bool Workspace::config(char *solver_config_filename,
                       char *armor_param_filename,
                       char *rune_config_filename) {
    FileStorage filestorage(solver_config_filename,FileStorage::READ);
//    filestorage["camera_matrix_left"]>>camera_matrix_left;
//    filestorage["distortion_coeff_left"]>>distortion_coeff_left;
//    filestorage["camera_matrix_right"]>>camera_matrix_right;
//    filestorage["distortion_coeff_right"]>>distortion_coeff_right;
    filestorage["camera_matrix"]>>camera_matrix_mono;
    filestorage["distortion_coeff"]>>distortion_coeff_mono;
    armor_preprocessor.init(armor_param_filename);
//    stereo_camera->init(stereo_config_filename);
    mono_camera->init(solver_config_filename);
    armor_finder.init(armor_param_filename);
    angle_solver.init(solver_config_filename);
//    rune_object.init(rune_config_filename);
}

bool Workspace::image_receiving_thread_func() {
    //TODO

    while(true){
//        if(row_image_buffer_right.size()!=row_image_buffer_left.size()){
//            row_image_buffer_left.clear();
//            row_image_buffer_right.clear();
//        }
//        if(row_image_buffer_left.size()<row_image_buffer_stereo_maxsize) {
//            row_image_buffer_left.push_back(stereo_camera->getImageLeft());
//        }
//        if(row_image_buffer_right.size()<row_image_buffer_stereo_maxsize){
//            row_image_buffer_right.push_back(stereo_camera->getImageRight());
//        }
        if(raw_image_buffer_mono.size()<raw_image_buffer_mono_maxsize) {
            raw_image_buffer_mono.push(mono_camera->getImage());
        }
    }
//    return true;
}

bool Workspace::image_processing_thread_func() {
    Frame current_frame;
    while(true){
        if(!raw_image_buffer_mono.empty()){
            current_frame=raw_image_buffer_mono.front();
            raw_image_buffer_mono.pop();
            armor_preprocessor.run(current_frame,
                                   preprocessed_image_mono,
                                   camera_matrix_mono,
                                   distortion_coeff_mono);
            contours_finder.run(preprocessed_image_mono,lightbars);
            armor_finder.run(lightbars,armors,false);
            angle_solver.run(armors,target);
            predictor.run(target);
            //TODO:给预测器增加发送队列的参数
        }else{
            continue;
        }
    }

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
    //TODO：增加数据的处理和发送
    while(true){

    }
    return true;
}

void Workspace::setPtzAngle(int angle) {
    ptz_angle=angle;
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

//void Workspace::image_processing_step1() {
//    armor_preprocessor.run(row_image_buffer_left,
//                           preprocessed_buffer_left,
//                           camera_matrix_left,
//                           distortion_coeff_left);
//    armor_preprocessor.run(row_image_buffer_right,
//                           preprocessed_buffer_right,
//                           camera_matrix_right,
//                           distortion_coeff_right);
//    contours_finder.run(preprocessed_buffer_left,contours_left);
//    contours_finder.run(preprocessed_buffer_right,contours_right);
//    armor_finder.run(contours_left,armors_left,true);
//    armor_finder.run(contours_right,armors_right,true);
//}
//
//void Workspace::image_processing_step2() {
//    stereo_solver.run(armors_left,armors_right,armor_with_position);
//}
//
//void Workspace::image_processing_step3() {
//    target_selector.run(armor_with_position,target);
//    predictor.run(target/*,signal_queue*/);
//}
//
//bool Workspace::processing_loop() {
//    //TODO:we need to fill the function to let the assembly line work
//    //there will be several threads to be every part of the assembly line
//    return true;
//}