//  基于OpenCV和Socket的图像传输（接收）
#ifndef __SOCKETMATTRANSMISSIONSEVER_H__
#define __SOCKETMATTRANSMISSIONSEVER_H__

#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "iostream"
#include "sstream"

#include <sys/time.h>
#include <netdb.h>
#include <fcntl.h>

using namespace cv;

#define PACKAGE_NUM 2

#define IMG_WIDTH  960
#define IMG_HEIGHT 540

#define BLOCKSIZE IMG_WIDTH*IMG_HEIGHT*3/PACKAGE_NUM

struct recvBuf
{
    int flag;
    char buf[BLOCKSIZE];
    float in_nums1;float in_nums2;float in_nums3;float in_nums4;float in_nums5;
    float out_nums1;float out_nums2;float out_nums3;float out_nums4;float out_nums5;
    int lineNum;
    int order;
};
struct sentBuf
{
    int order;
    int threshold;
    int hour;int minute;
    float x11;float y11;float x12;float y12;
    float x21;float y21;float x22;float y22;
    float x31;float y31;float x32;float y32;
    float x41;float y41;float x42;float y42;
    float x51;float y51;float x52;float y52;

    float dx11;float dy11;float dx12;float dy12;
    float dx21;float dy21;float dx22;float dy22;
    float dx31;float dy31;float dx32;float dy32;
    float dx41;float dy41;float dx42;float dy42;
    float dx51;float dy51;float dx52;float dy52;
    char IP[15],admin1[10],code1[20];///设置端口的IP，用户名，密码
    int duankou;
};


class SocketMatTransmissionServer
{
public:
    SocketMatTransmissionServer(void);
    ~SocketMatTransmissionServer(void);
    int sockConn;
private:
    struct recvBuf data;
    struct sentBuf data1;
    int needRecv;
    int count;

public:

    // 打开socket连接
    // params : PORT    传输端口
    // return : -1      连接失败
    //          1       连接成功
    int socketConnect(int PORT);


    // 传输图像
    // params : image   待接收图像
    //      image   待接收图像
    // return : -1      接收失败
    //          1       接收成功
    /*receive说明：
    接收到的数据为-1表示没有这条线
    */
    int receive(cv::Mat& image,unsigned int* in_num,unsigned int* out_num,int& lineNum,int &order);
    /*sender说明：
    float x和float dx每4个数为一组，对应每条线的point1_x,point1_y,point2_x,point2_y以及dir1_x,dir1_y,dir2_x,dir2_y，共对应五条线和五个方向向量。
    如果输入的线数少于五条，后后面的x[i]和dx[i]都要赋值-1.
    */
    int sender(int threshold,int hour,int minute,float x[20],float dx[20],char IP[15],char admin1[10],char code1[20],int duankou,int order=0);///order=0，全部发送&stop the program.
    int sender(float x[40]);///order=1，发送划线, need expansion!
    int sender(int order=-1);///order=-1,keep the heart beat. order=1, stop the system.
    //int sender(int threshold,int hour,int minute,int second,int x1,int y1,int x2,int y2,int order=2);

    // 断开socket连接
    void socketDisconnect(void);
};

#endif
