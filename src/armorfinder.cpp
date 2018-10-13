/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.12

 Detail:
 *****************************************************************************/

#include "armorfinder.h"

ArmorFinder::ArmorFinder(){

}

ArmorFinder::~ArmorFinder(){

}

void ArmorFinder::init(char *armor_param_filename) {
    FileStorage filestorage(armor_param_filename,FileStorage::READ);
    //TODO:Loading parameters of armor.
}

void ArmorFinder::run(vector<vector<Point2f>> &contours,
                      vector<RotatedRect> &armors) {
    timer.start();
    //TODO:START

    //TODO:END
    cout<<"armor_finder running time:"<<timer.getTime()<<endl;
    timer.stop();
}
