/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_STEREOSOLVER_H
#define HERORM2019_STEREOSOLVER_H

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

class StereoSolver:Worker {
public:

private:
    bool isStereo;
    double base_length;
    double focus_distance;
    double ptz_pitch;
    double pixel_scale;
    Mat ptz2camera_trans;
    Mat camera_matrix;
    Mat distortion_coeff;

    ///Armor Parameters
    double armor_width;
    double armor_height;

public:
    StereoSolver();
    ~StereoSolver();
    void init(char *stereo_config_filename);
    void run(vector<RotatedRect> &armors_left,
             vector<RotatedRect> &armors_right,
             vector<Armor> &armor_with_position);
    void setPtzPitch(double input_ptz_pitch);
private:
    inline void solve(Point2f left_center,
                      Point2f right_center,
                      Armor &armor);
    inline bool isOne(RotatedRect left,RotatedRect right);
    void getArmorCorners(const cv::RotatedRect &rect, vector<Point2f> &target2d);
    void solvePnP4Points(const std::vector<cv::Point2f> &points2d,
                         cv::Mat &rotate_matrix,
                         cv::Mat &trans);
};


#endif //HERORM2019_STEREOSOLVER_H
