//  基于OpenCV和Socket的图像传输（发送） 
#include "SocketMatTransmissionClient.h"  

SocketMatTransmissionClient::SocketMatTransmissionClient(void)  
{  
}  


SocketMatTransmissionClient::~SocketMatTransmissionClient(void)  
{  
}  


int SocketMatTransmissionClient::socketConnect(const char* IP, int PORT)  
{  
struct sockaddr_in    servaddr;  

if ((sockClient = socket(AF_INET, SOCK_STREAM, 0)) < 0)   
{  
    printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);  
    return -1;  
}  

memset(&servaddr, 0, sizeof(servaddr));  
servaddr.sin_family = AF_INET;  
servaddr.sin_port = htons(PORT);  
if (inet_pton(AF_INET, IP, &servaddr.sin_addr) <= 0)   
{  
    printf("inet_pton error for %s\n", IP);  
    return -1;  
}  

if (connect(sockClient, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)   
{  
    printf("connect error: %s(errno: %d)\n", strerror(errno), errno);  
    return -1;  
}  
else   
{  
    printf("connect successful!\n");  
}  
}  


void SocketMatTransmissionClient::socketDisconnect(void)  
{  
close(sockClient);  
}  

int SocketMatTransmissionClient::transmit(cv::Mat image,unsigned int in_num,unsigned int out_num)  
{
    data.in_num=in_num;
    data.out_num=out_num;
    data.order=-1;
    data.threshold=50;
    data.hour=23;data.minute=59;data.second=59;
    data.x1=1;data.x2=-1;data.y1=-1;data.y2=-1;
    if (image.empty())  
    {  
        printf("empty image\n\n");  
        return -1;  
    }  

    if(image.cols != IMG_WIDTH || image.rows != IMG_HEIGHT || image.type() != CV_8UC3)  
    {  
        printf("the image must satisfy : cols == IMG_WIDTH（%d）  rows == IMG_HEIGHT（%d） type == CV_8UC3\n\n", IMG_WIDTH, IMG_HEIGHT);  
        return -1;  
    }  

    for(int k = 0; k < PACKAGE_NUM; k++)   //package num=2
    {  
        int num1 = IMG_HEIGHT / PACKAGE_NUM * k;  
        for (int i = 0; i < IMG_HEIGHT / PACKAGE_NUM; i++)  
        {  
            int num2 = i * IMG_WIDTH * 3;  
            uchar* ucdata = image.ptr<uchar>(i + num1);  
            for (int j = 0; j < IMG_WIDTH * 3; j++)  
            {  
                data.buf[num2 + j] = ucdata[j];  
            }  
        }  

        if(k == PACKAGE_NUM - 1)  
            data.flag = 2;  
        else  
            data.flag = 1;  

        if (send(sockClient, (char *)(&data), sizeof(data), 0) < 0)  
        {  
            printf("send image error: %s(errno: %d)\n", strerror(errno), errno);  
            return -1;  
        }  
    }  
}  


int SocketMatTransmissionClient::get(int& order,int& threshold,int& hour,int& minute,int& second,int& x1,int& y1,int& x2,int& y2)  
{
    if (recv(sockClient, (char*)&data,sizeof(data) , 0) < 0)  
    {  
        printf("paramater receive Failed!\n");  
        return -1;  
    }
    order=data.order;
    threshold=data.threshold;
    hour=data.hour;
    minute=data.minute;
    second=data.second;
    x1=data.x1;x2=data.x2;y1=data.y1;y2=data.y2;

    //need a judgement with order.
    return 1;  
}