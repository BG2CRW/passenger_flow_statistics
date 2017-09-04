//  基于OpenCV和Socket的图像传输（发送）
#ifndef __SOCKETMATTRANSMISSIONCLIENT_H__
#define __SOCKETMATTRANSMISSIONCLIENT_H__
#include"titlefiles.h"
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
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

//待传输图像默认大小为 640*480，可修改
#define IMG_WIDTH 960   // 需传输图像的宽
#define IMG_HEIGHT 540  // 需传输图像的高
#define PACKAGE_NUM 2
//默认格式为CV_8UC3
#define BUFFER_SIZE IMG_WIDTH*IMG_HEIGHT*3/PACKAGE_NUM

struct sentBuf
{
    int flag;
	char buf[BUFFER_SIZE];
    float in_nums1;float in_nums2;float in_nums3;float in_nums4;float in_nums5;
    float out_nums1;float out_nums2;float out_nums3;float out_nums4;float out_nums5;
    int lineNum;
    int order;
};
struct recvBuf
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

class SocketMatTransmissionClient
{
public:
SocketMatTransmissionClient(void);
~SocketMatTransmissionClient(void);

private:
int sockClient;
struct sentBuf data;  ///传播的数据组
struct recvBuf data1;
int needRecv;
public:

// 打开socket连接
// params : IP      服务器的ip地址
//          PORT    传输端口
// return : -1      连接失败
//          1       连接成功
int socketConnect(const char* IP, int PORT);


// 传输图像
// params : image 待传输图像
// return : -1      传输失败
//          1       传输成功

///transmit说明：
///若画线数量少于5时，后面的in_num和out_num都赋值-1
int transmit(cv::Mat image,unsigned int *in_num,unsigned int *out_num,int lineNum,int order);
int get(int& order,int& threshold,int& hour,int& minute,float x[20],float dx[20],char IP[15],char admin1[10],char code1[20],int& duankou);
int get(int& key);

// 断开socket连接
void socketDisconnect(void);
};

#endif
