/******************************************************************************
 Copyright© 2019 HITWH HERO-Robomaster Group

 Author:Ma Yuemeng on 2018.10.26

 Update:Zhou Yuxin on 2018.11.18

 Detail:

 *****************************************************************************/

#include "serialport.h"

SerialPort::SerialPort() {
    uart_mode = CLOSE_USART;
    fd_car = -1;
}

SerialPort::~SerialPort() {

}

void SerialPort::praseDataFromCar() {
    char buf[255] = { 0 };
    size_t bytes = 0;
    ioctl(fd_car, FIONREAD, &bytes);// bytes 串行端口输入缓冲区中的字节数
    if (bytes > 0 && bytes < 255)
        bytes = read(fd_car, buf, bytes);
    else if (bytes >= 255)
        bytes = read(fd_car, buf, 255);
    else
        return;

    praseData(buf, bytes);
}

void SerialPort::praseData(const char * data, int size) {//unpack data function
    if (size < 6)
        return;
    int start = 0;
    while (1) {

        if (start >= size - 5)
            return;

        if ((char)data[start] == (char)0xFF && (char)data[start + 1] == (char)0xfe && (char)data[start + 5] == (char)0xa5) {

            break;//the head and tail is right
        }
        ++start;
    }
    ++start;
    ++start;
    unsigned char check_byte = 0;
    for (int i = 0; i < 2; i++)
    {
        check_byte += data[start + i];//to calculate the check_byte
    }
    if ((unsigned char)check_byte != (unsigned char)data[start + 2])//check whether the data is right
        return;
    unsigned char cmd1 = (unsigned char)data[start];//save the right data in variables
    unsigned char pitch_angle = (unsigned char)data[start + 1];

    switch (cmd1) {
        case 0: {
            uart_mode = STATUS::OPEN_USART;//use usart to send the angle message
            break;
        }
        case 1: {
            uart_mode = STATUS::CLOSE_USART;//use can to send the angle message,stop the uart-send thread
            break;
        }
        case 2: {
            mode = MODE::ARMOR_MODE; //get into the armor mode
            break;
        }
        case 3: {
            mode = MODE::BIG_RUNE_MODE; //get into the big rune mode
            break;
        }
        case 4: {
            mode = MODE::SMALL_RUNE_MODE; //get into the small rune mode
            break;
        }
        default:
            //mode = ARMOR_MODE;	//data wrong,do nothing
            std::cout << "wrong!";
    }
    int a = 0;
    a |= (0x7f & pitch_angle);
    a = (0x80 & (pitch_angle)) == 0 ? a : a | 0xffffff80;
    angle_pitch = (int)a / 4.0;//get the pitch angle
    std::cout << "angle_pitch:" << angle_pitch << '\n';

    ++start;  // idx of FE
    if (start + 2< size) {
        praseData(data + start + 2, size - start - 2);
    }
}

void SerialPort::init_usart(const char * dev_name) {
    fd_car = openPort(dev_name);
    configurePort();
}
int SerialPort::openPort(const char * dev_name) {
    int fd; // file description for the serial port
    fd = open(dev_name, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) { // if open is unsucessful
        printf("open_port: Unable to open /dev/ttyS0. \n");
    }
    else {
        fcntl(fd, F_SETFL, 0);
        printf("port is open.\n");
    }
    return(fd);
}

void SerialPort::configurePort() {                      // configure the port
    struct termios port_settings;               // structure to store the port settings in
    cfsetispeed(&port_settings, B115200);       // set baud rates
    cfsetospeed(&port_settings, B115200);

    port_settings.c_cflag &= ~PARENB;           // set no parity, stop bits, data bits
    port_settings.c_cflag &= ~CSTOPB;			//set stop bits
    port_settings.c_cflag &= ~CSIZE;
    port_settings.c_cflag |= CS8;

    tcsetattr(fd_car, TCSANOW, &port_settings);     // apply the settings to the port
}

bool SerialPort::sendXYZ(double * xyz) {
    static unsigned char count = 0;
    count++;
    unsigned char send_bytes[] = { 0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0xA5 };
    if (NULL == xyz) {
        if (8 == write(fd_car, send_bytes, 8))  //Send data
            free(xyz);
            return true;
        return false;
    }

    short * data_ptr = (short *)(send_bytes + 2);
    data_ptr[0] = (short)xyz[0];//low_byte:send_bytes[2]  high_byte:send_bytes[3]
    data_ptr[1] = (short)xyz[1];//low_byte:send_bytes[4]  high_byte:send_bytes[5]
    //data_ptr[2] = (short)xyz[2];
    unsigned char check_byte = 0;
    send_bytes[6] = (unsigned char)count;
    for (int i = 0; i < 5; i++)
    {
        check_byte += send_bytes[2 + i];
    }

    send_bytes[7] = (unsigned char)check_byte;
    return true;
//    if (8 == write(fd, send_bytes, 8))      //Send data
//        return true;
//    return false;
}

bool SerialPort::sendData(int fd, char * data, int size, DATATYPE data_tpye) {
    unsigned char header[5];
    int * _size = (int *)header;
    _size[0] = size;
    unsigned char * _type = header + 4;
    _type[0] = data_tpye;
    if (5 != write(fd, header, 5)) {
        printf("send Data error\n");
        return false;
    }
    if (size == write(fd, data, size)) {
        printf("send Data success\n");
        return true;
    }
    return false;
}

int SerialPort::getMode() {
    return this->mode;
}

int SerialPort::getAnglePitch() {
    return this->angle_pitch;
}