/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.13

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_PREDICTOR_H
#define HERORM2019_PREDICTOR_H

#include <opencv2/opencv.hpp>

#include "worker.h"
//#define PI 3.14159265
using namespace std;
using namespace cv;
//angle_solve section will be put in another file 
//the prediction is just to offset the influence of gravity
class Predictor:Worker {
public:
private:
public:
    Predictor();
    ~Predictor();
	void init(char *param_filename);
    void run(const Armor &targer,
			   queue<double*> signal_queue,
			   bool isBigBullet);
    void setPitchAngle(const double input_pitch_angle);
private:
	const double PI=3.14159265897932;
	double theta, alpha, alpha_min, theta_max, theta_min;//from theta to theta_max, find the ideal alpha-->alpha_min
    double pitch_angle;
	double bullet_speed;
	double history_yaw[3],history_pitch[3];
	double x_;
	double y_;
	double bullet_mass;
	double small_bullet_mass;
	double big_bullet_mass;
	double k_;
	double gravity;
	double air_viscosity;
	double find_alpha(double v, double x, double y);
	double find_real_alpha(double v, double x, double y);
	void test_input();//change the para for test(input para from keyboard)
	float test_offset_air_friction();
	double find_noair_alpha(double v, double x, double y);
	double* interpolation(double *current_data);
};


#endif //HERORM2019_PREDICTOR_H
