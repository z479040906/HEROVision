/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/

#include "armorpreprocessor.h"

ArmorPreprocessor::ArmorPreprocessor() {

}

ArmorPreprocessor::~ArmorPreprocessor() {

}

void ArmorPreprocessor::run(vector<Frame> &row_image_buffer,
                            vector<Mat> &preprocessed_buffer) {
    timer.start();
    //TODO:START

    //TODO:END
    cout<<"armor_preprocessor running time:"<<timer.getTime()<<endl;
    timer.stop();
}