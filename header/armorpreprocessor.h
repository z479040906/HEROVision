/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Hu Zheyu on 2018.10.19

 Detail:预处理部分采用的是多数开源战队的都使用的方案,主要两个函数ProcessInput和ProcessChannels
 分别是对输入图像进行处理和对分离的通道根据敌军颜色进行计算.函数run是对预处理模块的封装,以便于调用.
 *****************************************************************************/


#ifndef HERORM2019_ARMORPREPROCESSOR_H
#define HERORM2019_ARMORPREPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <vector>

#include "worker.h"

using namespace std;
using namespace cv;

typedef struct{
    Mat image;
    int frame_number=0;
}Frame;


class ArmorPreprocessor:Worker {
public:
private:
    bool if_initUndistort;
    Mat x_trans, y_trans;
    int enemy_color;
    int thres;
    Mat contour_thread_kernel;

public:
    ArmorPreprocessor();
    ~ArmorPreprocessor();
    void init(char *armor_param_filename);
    void run(vector<Frame> &row_image_buffer,
             vector<Frame> &preprocessed_buffer,
             const Mat &camera_matrix,
             const Mat &distortion_coeff);
private:

    void processInput(Mat &input,
                      Mat &binary,
                      const Mat &camera_matrix,
                      const Mat &distortion_coeff);//处理输入图像
    void processChannels(vector<Mat> &channels, Mat &binary);
    void adjustImage(Mat &img,const Mat &camera_matrix,const Mat &distortion_coeff);
};


#endif //HERORM2019_ARMORPREPROCESSOR_H