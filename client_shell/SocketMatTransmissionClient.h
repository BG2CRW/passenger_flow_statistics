//  基于OpenCV和Socket的图像传输（发送） 
#ifndef __SOCKETMATTRANSMISSIONCLIENT_H__  
#define __SOCKETMATTRANSMISSIONCLIENT_H__  

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

using namespace cv;  

//待传输图像默认大小为 640*480，可修改  
#define IMG_WIDTH 960   // 需传输图像的宽  
#define IMG_HEIGHT 540  // 需传输图像的高  
#define PACKAGE_NUM 2  
//默认格式为CV_8UC3  
#define BUFFER_SIZE IMG_WIDTH*IMG_HEIGHT*3/PACKAGE_NUM  

struct sentbuf  
{ 
	int order; 
	char buf[BUFFER_SIZE];
	unsigned int in_num;
	unsigned int out_num;  
	int flag;  
    int threshold;
    int hour;int minute;int second;  
    int x1;int y1;int x2;int y2;
};

class SocketMatTransmissionClient  
{  
public:  
SocketMatTransmissionClient(void);  
~SocketMatTransmissionClient(void);  

private:  
int sockClient;  
struct sentbuf data;  ///传播的数据组 
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
int transmit(cv::Mat image,unsigned int in_num,unsigned int out_num);  
int get(int& order,int& threshold,int& hour,int& minute,int& second,int& x1,int& y1,int& x2,int& y2);

// 断开socket连接  
void socketDisconnect(void);  
};  

#endif  
