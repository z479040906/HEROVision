/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Hu Zheyu on 2018.10.19

 Detail:主要方案为对输入图像转灰度,通道分离,二值化,然后根据敌军颜色通道对分离出的通道相减并膨胀运算,
 最后得到的结果与处理后的输入求交集.
 *****************************************************************************/

#include "armorpreprocessor.h"
//#define ADJUST

//TODO:增加GPU版的预处理代码

using namespace cv;

ArmorPreprocessor::ArmorPreprocessor() {
    if_initUndistort=true;
    thres=0;
    enemy_color=0;
}

ArmorPreprocessor::~ArmorPreprocessor() {

}

void ArmorPreprocessor::init(char *armor_param_filename){
    FileStorage filestorage(armor_param_filename,FileStorage::READ);
    filestorage["enemy_color"]>>enemy_color;
    filestorage["threshold"]>>thres;
    contour_thread_kernel = getStructuringElement(MORPH_ELLIPSE,Size(9,9));
}

void ArmorPreprocessor::run(vector<Frame> &row_image_buffer,
                            vector<Frame> &preprocessed_buffer,
                            const Mat &camera_matrix,
                            const Mat &distortion_coeff
) {
    timer.start();
    //TODO:START
    if (!(row_image_buffer.empty()))
    {
        for (int i=0;i<row_image_buffer.size();i++)
        {
            Frame temp=row_image_buffer.back();
            row_image_buffer.pop_back();
            Mat input=temp.image.clone();
            Mat binary;
            processInput(input, binary,camera_matrix,distortion_coeff);
            temp.image=binary.clone();
            preprocessed_buffer.push_back(temp);
        }
    }
    //TODO:END
    cout<<"armor_preprocessor running time:"<<timer.getTime()<<endl;
    timer.stop();
}

void ArmorPreprocessor::processInput(Mat &input,
                                     Mat &binary,
                                     const Mat &camera_matrix,
                                     const Mat &distortion_coeff)
{
    Mat processed_input;//对输入灰度化和二值化
    vector<Mat> channels;//通道分离
    split(input, channels);
    cvtColor(input,processed_input,CV_BGR2GRAY);
#ifdef ADJUST
    adjustImage(processed_input,camera_matrix,distortion_coeff);
#endif
    threshold(processed_input, processed_input, 100, 255, THRESH_BINARY );
    processChannels(channels,  binary);//对分离出的通道进行处理
    binary = binary & processed_input;
}

void ArmorPreprocessor::processChannels(vector<Mat> &channels, Mat &binary)
{
    if (enemy_color==0){
        subtract(channels[2], channels[0], binary);
        threshold(binary, binary, thres, 255, THRESH_BINARY);//enemy's color is red
    }else {
        subtract(channels[0], channels[2], binary);
        threshold(binary, binary, thres, 255, THRESH_BINARY);//enemy's color is blue
    }
    dilate(binary,binary,contour_thread_kernel);
}

void ArmorPreprocessor::adjustImage(Mat &img,
                                    const Mat &camera_matrix,
                                    const Mat &distortion_coeff)
{
    if (if_initUndistort) { // called once per calibration
        initUndistortRectifyMap(
                camera_matrix,  // computed camera matrix
                distortion_coeff,    // computed distortion matrix
                Mat(),     // optional rectification (none)
                Mat(),     // camera matrix to generate undistorted
                img.size(),
//            image.size(),  // size of undistorted
                CV_32FC1,      // type of output map
                x_trans, y_trans);   // the x and y mapping functions
        if_initUndistort= false;
    }
    remap(img, img, x_trans, y_trans, INTER_LINEAR);
}