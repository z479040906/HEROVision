/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.9

 Detail:
 *****************************************************************************/

#include "workspace.h"

Workspace::Workspace() {
}

Workspace::~Workspace() {
}

bool Workspace::init(char *mono_camera_name) {
//    stereo_camera = new StereoCamera(stereo_camera_left,stereo_camera_right);
    mono_camera = new MonoCamera(mono_camera_name);
    return true;
}

bool Workspace::init(char *stereo_camera_left,char *stereo_camera_right,char *mono_camera_name) {
    stereo_camera = new StereoCamera(stereo_camera_left,stereo_camera_right);
    mono_camera = new MonoCamera(mono_camera_name);
    return true;
}

bool Workspace::config(char *serialport_name,
                       char *solver_config_filename,
                       char *armor_param_filename,
                       char *other_param_filename,
                       char *rune_config_filename) {
    FileStorage filestorage(solver_config_filename,FileStorage::READ);
    filestorage["camera_matrix"]>>camera_matrix_mono;
    filestorage["distortion_coeff"]>>distortion_coeff_mono;
    serialport.init_usart(serialport_name);
    armor_preprocessor.init(armor_param_filename);
    mono_camera->init(solver_config_filename);
    armor_finder.init(armor_param_filename);
    angle_solver.init(solver_config_filename);
    predictor.init(other_param_filename);
//    rune_object.init(rune_config_filename);
}

bool Workspace::image_receiving_thread_func() {
    while(true){
        if(raw_image_buffer_mono.size()<raw_image_buffer_mono_maxsize) {
            raw_image_buffer_mono.push(mono_camera->getImage());
        }
    }
    return true;
}

bool Workspace::image_processing_thread_func() {
    Frame current_frame;
    while(true){
        if(!raw_image_buffer_mono.empty()){
            if(work_mode==MODE::ARMOR_BLUE||work_mode==MODE::ARMOR_RED) {
                current_frame = raw_image_buffer_mono.front();
                raw_image_buffer_mono.pop();
                armor_preprocessor.run(current_frame,
                                       preprocessed_image_mono,
                                       camera_matrix_mono,
                                       distortion_coeff_mono);
                contours_finder.run(preprocessed_image_mono, lightbars);
                armor_finder.run(lightbars, armors, false);
                angle_solver.run(armors, target);
                predictor.run(target,signal_queue,false);
            }else if(work_mode==MODE::RUNE_SMALL){
                //TODO:加入小神符代码
            }else if(work_mode==MODE::RUNE_LARGE){
                //TODO:加入大神符代码
            }
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
    //TODO:加入看门狗通信
    while(true){
        serialport.praseDataFromCar();
        setPtzAngle(serialport.getAnglePitch());
        setMode(serialport.getMode());
        if(!signal_queue.empty()) {
            serialport.sendXYZ(signal_queue.front());
            signal_queue.pop();
        }
    }
    return false;
}

void Workspace::setPtzAngle(int angle) {
    ptz_angle=angle;
}

void Workspace::setMode(int mode){
    if(mode==work_mode){
        return;
    }
    switch(mode){
        case SerialPort::ARMOR_MODE:
            work_mode=MODE::ARMOR_BLUE;
            break;
        case SerialPort::SMALL_RUNE_MODE:
            work_mode=MODE::RUNE_SMALL;
            break;
        case SerialPort::BIG_RUNE_MODE:
            work_mode=MODE::RUNE_LARGE;
            break;
        default:
            work_mode=WAITING;
    }
}