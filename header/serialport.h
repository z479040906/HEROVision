/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Zhou Yuxin on 2018.11.4

 Detail:
 *****************************************************************************/

#ifndef HERORM2019_SERIALPORT_H
#define HERORM2019_SERIALPORT_H

#include <opencv2/opencv.hpp>
#include <sys/ioctl.h>
#include <cmath>
#include <cstdio>      // standard input / output functions
#include <cstring>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <cerrno>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

#include "worker.h"
#include "serial.h"

//#define CLOSE_USART 0
//#define OPEN_USART 1
//#define ARMOR_MODE 0//装甲模式
//#define BIG_RUNE_MODE 1//神符模式
//#define SMALL_RUNE_MODE 2//神符模式

using namespace std;
using namespace cv;

class SerialPort:Worker {
public:
    enum MODE{
        ARMOR_MODE=0,//装甲模式
        BIG_RUNE_MODE=1,//神符模式
        SMALL_RUNE_MODE=2//神符模式
    };
private:
    int uart_mode;
    int mode;
    int angle_pitch;
    int fd_car;
    enum STATUS{
        CLOSE_USART=0,
        OPEN_USART=1
    };
public:
    SerialPort();
    ~SerialPort();
    void praseDataFromCar();//reading function
    bool sendXYZ(double * xyz);//sending function
    void init_usart(const char * dev_name);
    int getMode();
    int getAnglePitch();
private:
    ///read
    void praseData(const char * data, int size);

    ///send
    int openPort(const char * dev_name);
    void configurePort();
    bool sendData(int fd, char * data, int size, DATATYPE data_tpye);
};


#endif //HERORM2019_SERIALPORT_H
