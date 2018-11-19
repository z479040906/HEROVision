/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.9

 Update:Zhou Yuxin on 2018.11.18

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_WORKSPACE_H
#define HERORM2019_WORKSPACE_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <queue>
#include <thread>

#include "camera.h"
#include "worker.h"
#include "timer.h"
#include "anglesolver.h"
#include "armorpreprocessor.h"
#include "contoursfinder.h"
#include "armorfinder.h"
#include "anglesolver.h"
#include "predictor.h"
#include "serialport.h"


using namespace std;
using namespace cv;

class Workspace {
private:
    enum MODE{
        WAITING=0,
        ARMOR_RED=1,
        ARMOR_BLUE=2,
        RUNE_LARGE=3,
        RUNE_SMALL=4
    };

    ///status variables
    int ptz_angle;
    int work_mode;


    ///common variables
    //Rule rule;
    Timer timer;
    const int raw_image_buffer_stereo_maxsize=5;
    const int raw_image_buffer_mono_maxsize=5;
//    Mat camera_matrix_left;
//    Mat distortion_coeff_left;
//    Mat camera_matrix_right;
//    Mat distortion_coeff_right;
    Mat camera_matrix_mono;
    Mat distortion_coeff_mono;

    ///workers
    StereoCamera *stereo_camera;
    MonoCamera *mono_camera;
    SerialPort serialport;

    ///armor_detector
    ArmorPreprocessor armor_preprocessor;
    ContoursFinder contours_finder;
    ArmorFinder armor_finder;
    AngleSolver angle_solver;
//    ArmorTracker armor_tracker;
    Predictor predictor;
    /**

     ///rune_shootor
     RunePreprocessor rune_preprocessor;


     **/
    ///workfield
    queue<Frame> raw_image_buffer_mono;
    Frame preprocessed_image_mono;
    vector<RotatedRect> lightbars;
    vector<RotatedRect> armors;
    Armor target;
    queue<double*> signal_queue;


public:
    Workspace();
    ~Workspace();
    bool init(char *mono_camera_name);
    bool init(char *stereo_left,char *stereo_right,char *mono_camera_name);
    bool config(char *serialport_name,
                char *solver_config_filename,
                char *armor_finder_config_filename,
                char *other_param_filename,
                char *rune_config_filename);
    bool image_receiving_thread_func();
    bool image_processing_thread_func();
    bool message_communication_thread_func();
private:
    void setPtzAngle(int angle);
    void setMode(int mode);
//    bool processing_loop();
//    void image_processing_step1();
//    void image_processing_step2();
//    void image_processing_step3();
};


#endif //HERORM2019_WORKSPACE_H
