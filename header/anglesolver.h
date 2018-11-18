/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_ANGLESOLVER_H
#define HERORM2019_ANGLESOLVER_H

#include <opencv2/opencv.hpp>
#include <vector>

#include "worker.h"

using namespace std;
using namespace cv;

typedef struct {
    double x=0;
    double y=0;
    double z=0;
    double yaw=0;
    double pitch=0;
    RotatedRect rect_left;
    RotatedRect rect_right;
}Armor;

class AngleSolver:Worker{
public:

private:
//    Timer timer;
    bool isStereo;
    int solve_algorithm;
    double base_length;
    double focus_distance;
    double ptz_pitch;
    double pixel_scale;
    Mat ptz2camera_trans;
    Mat camera_matrix;
    Mat distortion_coeff;

    //Armor Parameters
    double small_armor_width;
    double small_armor_height;
    double big_armor_width;
    double big_armor_height;

public:
    AngleSolver();
    ~AngleSolver();
    void init(const char *stereo_config_filename);
    void run(vector<RotatedRect> &armors,
             Armor &target);
    void run(vector<RotatedRect> &armors_left,
             vector<RotatedRect> &armors_right,
             vector<Armor> &armor_with_position);
    void setPtzPitch(double input_ptz_pitch);
private:
    void selectTarget(vector<Armor> &armor_with_position,Armor target);
    inline void solveMono(RotatedRect &rect,Armor &armor);
    inline void solveStereo(Point2f left_center,
                            Point2f right_center,
                            Armor &armor);
    inline bool isOne(RotatedRect left,RotatedRect right);
    void getArmorCorners(const RotatedRect &rect, vector<Point2f> &target2d);
    void solvePnP4Points(const vector<Point2f> &points2d,
                         Mat &rotate_matrix,
                         Mat &trans);
};


#endif //HERORM2019_ANGLESOLVER_H
