/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/

#include "stereosolver.h"

StereoSolver::StereoSolver() {
    base_length=0.0;
    focus_distance=0.0;
    ptz_pitch=0.0;
    isStereo=true;
    ptz2camera_trans=Mat::zeros(4,4,CV_32FC1);
    ptz2camera_trans.at<double>(0,0)=1.0;
    ptz2camera_trans.at<double>(1,1)=1.0;
    ptz2camera_trans.at<double>(2,2)=1.0;
    ptz2camera_trans.at<double>(3,3)=1.0;
};

StereoSolver::~StereoSolver() {

}

void StereoSolver::init(char *stereo_config_filename) {
    FileStorage filestorage(stereo_config_filename,FileStorage::READ);
    filestorage["pixel_scale"]>>pixel_scale;
    filestorage["camera_matrix"]>>camera_matrix;
    filestorage["distortion_coeff"]>>distortion_coeff;
    filestorage["base_length"]>>base_length;
    filestorage["focus_distance"]>>focus_distance;
    filestorage["ptz2camera_trans"]>>ptz2camera_trans;
}

void StereoSolver::run(vector<RotatedRect> &armors_left,
                       vector<RotatedRect> &armors_right,
                       vector<Armor> &armor_with_position) {
    timer.start();
    //TODO:START
    Armor temp_armor;
    vector<RotatedRect>::const_iterator it_left,it_right;
    for(it_left=armors_left.begin(),it_right=armors_right.begin();
        it_left!=armors_left.end()||it_right!=armors_right.end();
        ++it_left,++it_right){
        if(isStereo) {
            if (!isOne(*it_left, *it_right)) continue;
            Point2f left,right;
            left.x=((*it_left).center.x-320)*pixel_scale;
            left.y=((*it_left).center.y-240)*pixel_scale;
            right.x=((*it_right).center.x-320)*pixel_scale;
            right.y=((*it_right).center.y-240)*pixel_scale;
            solve(left, right, temp_armor);
        }else {
            vector<Point2f> target_corners;
            getArmorCorners(*it_left,target_corners);

        }
        armor_with_position.push_back(temp_armor);
    }
    //TODO:END
    cout<<"stereo_solver running time:"<<timer.getTime()<<endl;
    timer.stop();
}

void StereoSolver::setPtzPitch(double input_ptz_pitch) {
    this->ptz_pitch=input_ptz_pitch;
}

inline void StereoSolver::solve(Point2f left_center,
                                Point2f right_center,
                                Armor &armor){
    Mat camera_position=Mat::ones(4,1,CV_64FC1);
    Mat ptz_position=Mat::zeros(4,1,CV_64FC1);
    camera_position.at<double>(2, 0) = base_length * focus_distance / fabs(left_center.x - right_center.x);
    camera_position.at<double>(0, 0) = base_length * left_center.x / fabs(left_center.x - right_center.x);
    camera_position.at<double>(1, 0) = base_length * left_center.y / fabs(left_center.x - right_center.x);
    cout<<"CP_xyx:"<<endl
        <<camera_position.at<double>(0, 0)<<endl
        <<camera_position.at<double>(1, 0)<<endl
        <<camera_position.at<double>(2, 0)<<endl;
    ptz_position = ptz2camera_trans * camera_position;
    armor.x = ptz_position.at<double>(0, 0);
    armor.y = ptz_position.at<double>(1, 0);
    armor.z = ptz_position.at<double>(2, 0);
}

bool StereoSolver::isOne(RotatedRect left, RotatedRect right) {
    bool result=true;

    return result;
}

void StereoSolver::getArmorCorners(const cv::RotatedRect &rect, vector<Point2f> &target2d) {
    Point2f vertices[4];
    rect.points(vertices);
    Point2f left_up, left_down, right_up, right_down;
    sort(vertices, vertices + 4, [](const Point2f &p1, const Point2f &p2) { return p1.x < p2.x; });
    if (vertices[0].y < vertices[1].y) {
        left_up = vertices[0];
        left_down = vertices[1];
    } else {
        left_up = vertices[1];
        left_down = vertices[0];
    }
    if (vertices[2].y < vertices[3].y) {
        right_up = vertices[2];
        right_down = vertices[3];
    } else {
        right_up = vertices[3];
        right_down = vertices[2];
    }

    target2d.clear();
    target2d.push_back(left_up);
    target2d.push_back(right_up);
    target2d.push_back(right_down);
    target2d.push_back(left_down);
}

void StereoSolver::solvePnP4Points(const std::vector<cv::Point2f> &points2d, cv::Mat &rotate_matrix, cv::Mat &trans) {
    if (armor_width < 10e-5 || armor_height < 10e-5) {
        rotate_matrix = Mat::eye(3, 3, CV_64FC1);
        trans = Mat::zeros(3, 1, CV_64FC1);
        return;
    }
    vector<Point3f> point3d;
    double half_x = armor_width / 2.0;
    double half_y = armor_height / 2.0;

    point3d.push_back(Point3f(-half_x, -half_y, 0));
    point3d.push_back(Point3f(half_x, -half_y, 0));
    point3d.push_back(Point3f(half_x, half_y, 0));
    point3d.push_back(Point3f(-half_x, half_y, 0));

    Mat rotate_vector;
    solvePnP(point3d, points2d, camera_matrix, distortion_coeff, rotate_vector, trans);
    Rodrigues(rotate_vector, rotate_matrix);
}