/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.9

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
#include "stereosolver.h"
#include "armorpreprocessor.h"
#include "contoursfinder.h"
#include "armorfinder.h"
#include "stereosolver.h"
#include "targetselector.h"
#include "predictor.h"


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
    const int row_image_buffer_stereo_maxsize=5;
    const int row_image_buffer_mono_maxsize=5;

    ///workers
    StereoCamera *stereo_camera;
    MonoCamera *mono_camera;

    ///armor_detector
    ArmorPreprocessor armor_preprocessor;
    ContoursFinder contours_finder;
    ArmorFinder armor_finder;
    StereoSolver stereo_solver;
    TargetSelector target_selector;
//    ArmorTracker armor_tracker;
    Predictor predictor;
    /**

     ///rune_shootor
     RunePreprocessor rune_preprocessor;


     **/
    ///workpart
    vector<Frame> row_image_buffer_mono;
    vector<Frame> row_image_buffer_left;
    vector<Frame> row_image_buffer_right;
    vector<Frame> preprocessed_buffer_mono;
    vector<Frame> preprocessed_buffer_left;
    vector<Frame> preprocessed_buffer_right;
    vector<vector<Point2f>> contours_left;
    vector<vector<Point2f>> contours_right;
    vector<RotatedRect> armors_left;
    vector<RotatedRect> armors_right;
    vector<Armor> armor_with_position;
    Armor target;
//    Position target_position;
//    queue<Position> history_position;
//    queue<Signal> signal_queue;


public:
    Workspace();
    ~Workspace();
    bool init(char *stereo_left,char *stereo_right,char *mono_camera);
    bool config(char *stereo_config_filename,
                char *mono_config_filename,
                char *armor_finder_config_filename,
                char *rune_config_filename)
    bool image_receiving_thread_func();
    bool image_processing_thread_func();
    bool message_communication_thread_func();
private:
    void setPtzAngle(int angle);
    void setMode(int mode);
    bool processing_loop();
};


#endif //HERORM2019_WORKSPACE_H
