/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.13

 Detail:
 *****************************************************************************/

#include "anglesolver.h"
#include "predictor.h"

Predictor::Predictor() {
	small_bullet_mass = 0.0029;
	big_bullet_mass = 0.042;
	k_ = 0.5;
	gravity = 9.8;
	air_viscosity = 0.0018315;
	bullet_mass=15;
}

Predictor::~Predictor() {

}

void Predictor::init(char *param_filename) {//init the para
    FileStorage filestorage(param_filename,FileStorage::READ);
    filestorage["small_bullet_mass"]>>small_bullet_mass;
    filestorage["big_bullet_mass"]>>big_bullet_mass;
    filestorage["k_"]>>k_;
    filestorage["gravity"]>>gravity;
    filestorage["air_viscosity"]>>air_viscosity;
}

void Predictor::run(const Armor &target,queue<double*> signal_queue,bool isBigBullet) {
    timer.start();
    //TODO:START
    //TODO:In this step,we need transform the target into a signal of CAN,
    //TODO:and push it into the queue of signals.
	double distance_x_y = 9999;
	double min_distance = 9999;
	double signal[2]={0.0};
//	test_input();
    signal[0]=atan(target.x/target.z);
    if(!isBigBullet){
        bullet_mass=big_bullet_mass;
    } else {
        bullet_mass=small_bullet_mass;
    }
	x_ = target.z;	//in Armor,z is distance,y's positive direction is down
    y_ = -target.y;
	theta = atan(y_ / x_);
	theta_max = ((theta + 0.40) < (PI / 2)) ? (theta + 0.40) : (PI / 2);
	//theta_min = ((theta - 0.40) > 0) ? (theta + 0.40) : 0;
	for (alpha = theta; alpha < theta_max; alpha += 0.01)//弧度制
	{
		//distance_x_y=find_noair_alpha(float v, float x, float y);j//无空气阻力
		distance_x_y = find_real_alpha(bullet_speed, x_, y_);
		if (distance_x_y < min_distance)
		{
			min_distance = distance_x_y;
			alpha_min = alpha;
		}
		else;

	}
	cout << "alpha_min = " << alpha_min / PI * 180 << endl;
	cout << "theta = " << theta / PI * 180 << endl;
	cout << "min_distance = " << min_distance << endl;

    //TODO:END
    cout<<"predictor running time:"<<timer.getTime()<<endl;
    timer.stop();
	signal[1] = alpha_min / PI * 180;
	signal_queue.push(signal);
	for(int i=0;i<3;i++){
//		signal_queue.push(interpolation())
	}
}
double Predictor::find_alpha(double v, double x, double y)
{
	double t1, t2, t1_sqrt_pre, t2_sqrt_pre;
	double distance_x_y;
	float vx, vy;
	float air_a;
	vx = v*cos(alpha);
	vy = v*sin(alpha);
	cout << "vx = " << vx << "vy = " << vy << endl;
	air_a = k_ / bullet_mass;
	t1_sqrt_pre = vx*vx - 2 * air_a*x*vx*vx;
	t2_sqrt_pre = vy*vy + 2 * y*(gravity + air_a*vy*vy);

	if ((t1_sqrt_pre > 0) && (t2_sqrt_pre > 0))
	{
		t1_sqrt_pre = sqrt(t1_sqrt_pre);
		t2_sqrt_pre = sqrt(t2_sqrt_pre);
	}
	else
	{
		cout << "error!! squr(number),number < 0" << endl;
	}
	cout << "t1_sqrt_pre = " << t1_sqrt_pre << endl;
	cout << "t2_sqrt_pre = " << t2_sqrt_pre << endl;
	t1 = (vx - t1_sqrt_pre) / (air_a*vx*vx);//t1的时间计算绝对有问题
	t2 = (vy + t2_sqrt_pre) / (gravity + air_a*vy*vy);
	distance_x_y = abs(t1 - t2);
	cout << "alpha = " << alpha / PI * 180 << endl;
	cout << "theta = " << theta / PI * 180 << endl;
	cout << "t1 = " << t1 << endl;
	cout << "t2 = " << t2 << endl;
	cout << "t1 - t2 = " << distance_x_y << endl;
	return distance_x_y;
}
double Predictor::find_real_alpha(double v, double x, double y)
{
	float vx, vy;
	double distance_x_y = 9999;
	double k_x, y_to_theta, ln_value, squre_mbg;
	vx = v*cos(alpha);
	vy = v*sin(alpha);
	//cout << "vx = "<<vx << endl;

	k_x = (air_viscosity*x) / (bullet_mass*vx);
	//cout << "k_x = " << k_x << endl;
	if ((1 - k_x) > 0)
		ln_value = log(1 - k_x);
	else
	{
		ln_value = log(k_x - 1);
		cout << "error!! the log error under 00000000!" << endl;
	}
	squre_mbg = (bullet_mass*bullet_mass*gravity) / (air_viscosity*air_viscosity);
	y_to_theta = (squre_mbg + bullet_mass*vy / air_viscosity)*k_x + squre_mbg*ln_value;
	distance_x_y = abs(y - y_to_theta) * 100;
	return distance_x_y;
}
void Predictor::test_input()
{

	cout << "please input the para v :" << endl;
	cin >> bullet_speed;
	cout << "please input the para x :" << endl;
	cin >> x_;
	cout << "please input the para y :" << endl;
	cin >> y_;
	cout << "please input the para k :" << endl;
	cin >> k_;
	cout << "please input the para m :" << endl;
	cin >> bullet_mass;
	k_ = 147.537 / 1000000;
	bullet_mass = 0.0029;
	/*cout << "v = " << v << endl;
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;*/
	cout << "k = " << k_ << endl;
	cout << "m = " << bullet_mass << endl;
	
	//theta = theta / PI * 180;
	cout << "theta = " << theta << endl;

}
//to find the fittest angle alpha 
//call method: alpha+k*offset_angle; 
//after call this function,offset_angle is a contest value.
//k is a bool variable,decide whether use this offset.
float Predictor::test_offset_air_friction(){//this function is for test 
	float offset_angle = 0;
	char key = cvWaitKey(20);
	if (key == 'w')
		offset_angle += 0.1;
	if (key == 's')
		offset_angle -= 0.1;
	return offset_angle;
}

double Predictor::find_noair_alpha(double v, double x, double y) {

	float vx, vy;
	double distance_x_y = 9999;
	double fenmu;

	vx = v * cos(alpha);
	vy = v * sin(alpha);
	fenmu = vx*vx;
	distance_x_y = x*tan(alpha) - gravity * x*0.5 / fenmu - y;
	distance_x_y = abs(distance_x_y);
	return distance_x_y;
}

double* Predictor::interpolation(double *current_data) {
	double *temp_data;
	double d2[2];
	double delta_d;
	double next_k;
	d2[0]=history_yaw[2]/history_yaw[1]-history_yaw[1]/history_yaw[0];
	d2[1]=current_data[0]/history_yaw[2]-history_yaw[2]/history_yaw[1];
	delta_d=d2[1]+d2[0]/2.0;
	next_k=current_data[0]/history_yaw[2]+delta_d;
	temp_data[0]=current_data[0]*next_k;
	d2[0]=history_pitch[2]/history_pitch[1]-history_pitch[1]/history_pitch[0];
	d2[1]=current_data[1]/history_pitch[2]-history_pitch[2]/history_pitch[1];
	delta_d=d2[1]+d2[0]/2.0;
	next_k=current_data[1]/history_pitch[2]+delta_d;
	temp_data[1]=current_data[1]*next_k;
	return temp_data;
}