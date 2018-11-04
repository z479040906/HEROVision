/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Wang Xiaoyan & Song Haodi

 Detail:This class is used for the identification of the armor.
 *****************************************************************************/

#ifndef HERORM2019_ARMORFINDER_H
#define HERORM2019_ARMORFINDER_H

#include <opencv2/opencv.hpp>
#include <vector>

#include "timer.h"

using namespace std;
using namespace cv;

class ArmorFinder {
public:
    ArmorFinder();
    ~ArmorFinder();
    void init(const char *armor_param_filename);
    void run(vector<RotatedRect> &contours,
             vector<RotatedRect> &armors,
             bool armor_size); //armor_size: big armor(0) or small armor(1)
private:
    /**
     * @breif adjust the rotatedrect, make sure its width is greater than height
     * @param rect rotatedrect
     * @return adjusted rect
     */
    cv::RotatedRect adjustRotatedRect(cv::RotatedRect& rect);
    /**
     * @breif calculate the distance between two dots
     * @param dot one dot
     * @param dot_ another dot
     * @return distance
     */
    double dist_dot2dot(cv::Point2f dot, cv::Point2f dot_);
    /**
     * @breif calculate the line determined by two dots
     * @param line the A, B, C parameter of a line(Ax + By + C = 0)
     * @param dot one dot
     * @param dot_ another dot
     * @return None
     */
    void line_calc(double line[], cv::Point2f dot, cv::Point2f dot_);
    /**
     * @breif calculate the angle between two lines
     * @param line one line
     * @param line_ another line
     * @return angle
     */
    double angle_line2line(double line[], double line_[]);

public:

private:
    double big_armor_ratio;
    double small_armor_ratio; //armor aspect ratio
    double ratio_cardinality, vertical_cardinality, angle_cardinality; //cardinal numbers
};


#endif //HERORM2019_ARMORFINDER_H
