/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/

#include "stereosolver.h"

StereoSolver::StereoSolver() {

}

StereoSolver::~StereoSolver() {

}

void StereoSolver::run(vector<RotatedRect> &armors,
                       vector<Armor> &armor_with_position) {
    timer.start();
    //TODO:START

    //TODO:END
    cout<<"armor_finder running time:"<<timer.getTime()<<endl;
    timer.stop();
}