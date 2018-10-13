/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/


#ifndef HERORM2019_ARMORPREPROCESSOR_H
#define HERORM2019_ARMORPREPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <vector>

#include "worker.h"
#include "camera.h"

using namespace std;
using namespace cv;

class ArmorPreprocessor:Worker {
public:

private:

public:
    ArmorPreprocessor();
    ~ArmorPreprocessor();
    void run(vector<Frame> &row_image_buffer
            vector<Mat> &preprocessed_buffer);
private:

};


#endif //HERORM2019_ARMORPREPROCESSOR_H
