/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Mark Chang on 2018.10.18

 Update:Zhou Yuxin on 2018.11.18

 Detail:Find the contours in  binary image which satisfy the size condition.
        target contours will be saved in final_found_contours.
 *****************************************************************************/


#include "contoursfinder.h"

ContoursFinder::ContoursFinder() {

}

ContoursFinder::~ContoursFinder() {

}

void ContoursFinder::run(Frame &preprocessed_buffer,
                         vector<RotatedRect> &contours) {
//    timer.start();
    Mat src_image=preprocessed_buffer.image;
    vector<Vec4i> hierarchy;
    vector<vector<Point2i>> temp_contours;
    contours.clear();
    findContours(src_image, temp_contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    vector<vector<Point2i>>::const_iterator it;
    for(it=temp_contours.begin();it!=temp_contours.end();++it){
        Rect temp_rect = cv::boundingRect(*it);
        if ((temp_rect.height<20)||  //too small
            (temp_rect.height > 40 && temp_rect.width > 0.6 * temp_rect.height + 0.5) ||  //too big
            (temp_rect.height <= 40 && temp_rect.width > 0.9 * temp_rect.height)) {  //too fat
            continue;
        }
#ifdef DEBUG_SHOW
        //        cvtColor(src_image,src_image,CV_GRAY2BGR);
//        Scalar color(0,255,0);
//		rectangle(src_image, temp_rect, color, 2);
#endif
        RotatedRect temp_rotatedrect = minAreaRect(*it);
        contours.push_back(temp_rotatedrect);
//        it++;
    }
#ifdef DEBUG_SHOW
    cout<<"contours:"<<contours.size()<<endl;
    cv::imshow("contours", src_image);
//	waitKey(0);
#endif
//    cout<<"contours_finder running time:"<<timer.getTime()<<endl;
//    timer.stop();
}