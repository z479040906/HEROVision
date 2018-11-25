/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Wang Xiaoyan & Song Haodi

 Detail:Through the armor of the aspect ratio, the angle between the diagonal
        of the lightbar and the two light bars, the angle of the two lightbars
        screened out the armor.
 *****************************************************************************/

#include "armorfinder.h"

using namespace std;
using namespace cv;


ArmorFinder::ArmorFinder() {

}

ArmorFinder::~ArmorFinder() {

}

void ArmorFinder::init(const char* armor_param_filename) {
  FileStorage filestorage(armor_param_filename, FileStorage::READ);
  filestorage["big_armor_ratio"] >> big_armor_ratio;
  filestorage["small_armor_ratio"] >> small_armor_ratio;
  filestorage["ratio_cardinality"] >> ratio_cardinality;
  filestorage["vertical_cardinality"] >> vertical_cardinality;
  filestorage["angle_cardinality"] >> angle_cardinality;
//  delete &filestorage;
}

void ArmorFinder::run(vector<RotatedRect> &contours,
                      vector<RotatedRect> &armors,
                      bool armor_size)
{
  Timer timer;
  timer.start();

  if(contours.empty()||contours.size()==1) return;
  //TODO:需要在这加入一个判断数组是否为空的语句块

  for(int i=0; i<contours.size(); i++) {
    contours[i] = adjustRotatedRect(contours[i]);//guarantee width is greater than height
    cout<<contours[i].angle<<endl;
  }

  Point2f vertices1[4]; //vertices of rotated rect
  Point2f center1, center2; //center of rotated rect
  double line1[3], line2[3];
  vector<double> score; //total score
  vector<int> subscript; //the corresponding subscript of total score
  double s; //current score
  for(int i=0; i<contours.size()-1; i++) {
    center1 = contours[i].center;
    contours[i].points(vertices1);
    line_calc(line1, vertices1[0], vertices1[2]);

    for(int j=i+1; j<contours.size(); j++) {
      s = 0.0;

      center2 = contours[j].center;
      double w_armor = dist_dot2dot(center1, center2); //the width of armor
      double h_armor = (contours[i].size.width + contours[j].size.width) / 2; //the height of armor
      double cur_ratio = w_armor / h_armor;

      if(cur_ratio< 6 * ratio_cardinality && cur_ratio>0.5 * ratio_cardinality) {
          if (armor_size)
              s += ratio_cardinality * fabs(small_armor_ratio - cur_ratio); //the score of ratio
          else
              s += ratio_cardinality * fabs(big_armor_ratio - cur_ratio); //the score of ratio

          line_calc(line2, center1, center2);
          double cur_angle = angle_line2line(line1, line2);
          s += vertical_cardinality * fabs(85.0 - cur_angle); //the score of vertical angle

          s += angle_cardinality * fabs(contours[i].angle - contours[j].angle); //the score of angle

          score.push_back(s); //current score
          subscript.push_back(i); //subscript
          subscript.push_back(j); //subscript
      }else{
          continue;
      }
    }
  }

  if(subscript.size()>=2) { //Determines whether the array crosses the bounds
      double min_score = 999999.9, cnt = 0;
      for (int i = 0; i < score.size(); i++) {
          if (min_score > score[i]) {
              min_score = score[i];
              cnt = i;
          }
      }

      vector<Point2f> armor_v; //vertices of armor
      Point2f vertices2[4];
      contours[subscript[cnt * 2]].points(vertices1);
      contours[subscript[cnt * 2 + 1]].points(vertices2);
      for (int i = 0; i < 4; i++) {
          armor_v.push_back(vertices1[i]);
          armor_v.push_back(vertices2[i]);
      }
      RotatedRect armor = minAreaRect(armor_v);
      armors.push_back(armor);
  }
  cout<<"armor_finder running time:"<<timer.getTime()<<endl;
  timer.stop();

  // imshow("src", src);
//  waitKey(0);
}

RotatedRect ArmorFinder::adjustRotatedRect(RotatedRect& rect)
{
  Size2f s = rect.size;
  if(s.width < s.height) {
    return RotatedRect(rect.center, Size2f(s.height, s.width), (rect.angle+90));
  }
  return rect;
}

double ArmorFinder::dist_dot2dot(Point2f dot, Point2f dot_)
{
  return sqrt((dot_.x-dot.x)*(dot_.x-dot.x) + (dot_.y-dot.y)*(dot_.y-dot.y));
}

void ArmorFinder::line_calc(double line[], Point2f dot, Point2f dot_)
{
  line[0] = dot.y - dot_.y;
  line[1] = dot_.x - dot.x;
  line[2] = dot.x * dot_.y - dot_.x * dot.y;
}

double ArmorFinder::angle_line2line(double line[], double line_[])
{
  double m = line[0]*line_[0] + line[1]*line_[1];
  double n = sqrt(line[0]*line[0]+line[1]*line[1]) * sqrt(line_[0]*line_[0]+line_[1]*line_[1]);
  double cos_theta = m / n;
  double theta = acos(cos_theta) * 180 / 3.141592654;
  if(theta < 90.0)  return theta;
  else  return (180.0 - theta);
}
