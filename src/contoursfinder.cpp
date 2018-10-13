/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/


#include "contoursfinder.h"

ContoursFinder::ContoursFinder() {

}

ContoursFinder::~ContoursFinder() {

}

void ContoursFinder::run(vector<Frame> &preprocessed_buffer,
                         vector<vector<Point2f>> &contours) {
    timer.start();
    //TODO:START

    //TODO:END
    cout<<"contours_finder running time:"<<timer.getTime()<<endl;
    timer.stop();
}