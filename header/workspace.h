/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.10.9

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_WORKSPACE_H
#define HERORM2019_WORKSPACE_H


class Workspace {
private:
    vector<int> camera_num;
public:
    Workspace();
    ~Workspace();
    bool init(char *config_filename);
    bool image_receiving_thread_func();
    bool image_processing_thread_func();
    bool message_litsener_thread_func();
private:

};


#endif //HERORM2019_WORKSPACE_H
