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
  
using namespace cv;  
  
#define PACKAGE_NUM 2  
  
#define IMG_WIDTH  960 
#define IMG_HEIGHT 540 
  
#define BLOCKSIZE IMG_WIDTH*IMG_HEIGHT*3/PACKAGE_NUM  
  
struct recvBuf  
{ 
    int order; 
    char buf[BLOCKSIZE];  
    unsigned int in_num;
    unsigned int out_num;
    int flag;
    int threshold;
    int hour;int minute;int second;  
    float x1;float y1;float x2;float y2;
};  
  
class SocketMatTransmissionServer  
{  
public:  
    SocketMatTransmissionServer(void);  
    ~SocketMatTransmissionServer(void);  
    int sockConn;  
private:  
    struct recvBuf data;  
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
    int receive(cv::Mat& image,unsigned int& in_num,unsigned int& out_num);  
    int sender(int threshold,int hour,int minute,int second,float x1,float y1,float x2,float y2,int order=0);//order=0
    int sender(float x1,float y1,float x2,float y2);//order=1
    //int sender(int threshold,int hour,int minute,int second,int x1,int y1,int x2,int y2,int order=2);
    // 断开socket连接  
    void socketDisconnect(void);  
};  
  
#endif 
