/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.9

 Detail:This file is the entrance of the project,we define the main function in
 this file.This file consists of three threads,they are image receiving thread,
 image processing thread and massage listener.The whole project is devided into
 three threads and runs all the time.
 *****************************************************************************/
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>

#include "RMVideoCapture.hpp"
#include "workspace.h"

using namespace cv;

int main() {
    char *config_file_name = "../param/param_config.xml";
    Workspace workspace;
    workspace.init(config_file_name);
    std::thread image_receiving_thread(&Workspace::image_receiving_thread_func,workspace);
    std::thread image_processing_thread(&Workspace::image_processing_thread_func,workspace);
    std::thread image_listener_thread(&Workspace::message_litsener_thread_func,workspace);
    image_listener_thread.join();
    image_processing_thread.join();
    image_listener_thread.join();
    return 0;
}
