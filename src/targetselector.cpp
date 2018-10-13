/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/


#include "targetselector.h"

TargetSelector::TargetSelector() {

}

TargetSelector::~TargetSelector() {

}

void TargetSelector::run(vector<Armor> &armor_with_position,
                         RotatedRect &target) {
    timer.start();
    //TODO:START

    //TODO:END
    cout<<"target_selector running time:"<<timer.getTime()<<endl;
    timer.stop();
}