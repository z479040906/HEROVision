/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.9

 Detail:This file is the entrance of the project,we define the main function in
 this file.This file consists of three threads,they are image receiving thread,
 image processing thread and massage listener.The whole project is devided into
 three threads and runs all the time.
 *****************************************************************************/
#include <opencv2/opencv.hpp>
#include <thread>

#include "RMVideoCapture.hpp"
#include "workspace.h"

using namespace cv;

int main(int argc,char **argv) {
//    char *armor_config_filename = static_cast<char*>("../param/armor_config.xml");
//    char *rune_config_filename = static_cast<char*>("../param/rune_config.xml");
//    char *rune_config_filename = NULL;
    Workspace workspace;
    workspace.init("/dev/video0","/dev/video1","/dev/video2");
    workspace.config("../param/stereo_config.xml",
                     "../param/mono_config.xml",
                     "../param/armor_param.xml",
                     "../param/rune_param.xml");
    std::thread image_receiving_thread(
            &Workspace::image_receiving_thread_func,
            workspace);
    std::thread image_processing_thread(
            &Workspace::image_processing_thread_func,
            workspace);
    std::thread message_communication_thread(
            &Workspace::message_communication_thread_func,
            workspace);
    image_receiving_thread.join();
    image_processing_thread.join();
    message_communication_thread.join();
    return 0;
}
