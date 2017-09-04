//  基于OpenCV和Socket的图像传输（发送）
#include "SocketMatTransmissionClient.h"
#include"titlefiles.h"
SocketMatTransmissionClient::SocketMatTransmissionClient(void)
{
}


SocketMatTransmissionClient::~SocketMatTransmissionClient(void)
{
}


int SocketMatTransmissionClient::socketConnect(const char* IP, int PORT)
{
    struct sockaddr_in servaddr;

    if ((sockClient = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }
    ///int flags = fcntl(sockClient, F_GETFL, 0);                    ///设置非阻塞
    ///fcntl(sockClient, flags|O_NONBLOCK);

struct timeval timeout={4,0};///set over time 
setsockopt(sockClient,SOL_SOCKET,SO_SNDTIMEO,(char*)&timeout,sizeof(struct timeval));
setsockopt(sockClient,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));

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
    return 1;
}


void SocketMatTransmissionClient::socketDisconnect(void)
{
close(sockClient);
}

int SocketMatTransmissionClient::transmit(cv::Mat image,unsigned int *in_num,unsigned int *out_num,int lineNum,int order)
{
    //int clock1=clock();
    data.in_nums1=in_num[0]; data.in_nums2=in_num[1]; data.in_nums3=in_num[2]; data.in_nums4=in_num[3]; data.in_nums5=in_num[4];
    data.out_nums1=out_num[0]; data.out_nums2=out_num[1]; data.out_nums3=out_num[2]; data.out_nums4=out_num[3]; data.out_nums5=out_num[4];
    data.lineNum=lineNum;
    data.order=order;
    //int clock2=clock();

    //cout<<"                            give scale time: "<<clock2-clock1<<endl;
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
       // int clock3=clock();
       // cout<<"                             picture package time: "<<clock3-clock2<<endl;
        if (send(sockClient, (char *)(&data), sizeof(data), 0) < 0)
        {
            printf("send image error: %s(errno: %d)\n", strerror(errno), errno);
            return -1;
        }
       // int clock4=clock();
       // cout<<"                           send time is: "<<clock4-clock3<<endl;
    }
    return 1;
}

int SocketMatTransmissionClient::get(int& order,int& threshold,int& hour,int& minute,float x[20],float dx[20],char IP[15],char admin1[10],char code1[20],int& duankou)
{
    needRecv = sizeof(recvBuf);
    int pos = 0;
    int len0 = 0;

    while (pos < needRecv)
    {
        len0 = recv(sockClient, (char*)(&data1) + pos, needRecv - pos, 0);
        if (len0 < 0)
        {
            printf("Server Recieve Data Failed!\n");
            break;
        }
        pos += len0;
    }
    order=data1.order;
    threshold=data1.threshold;
    hour=data1.hour;
    minute=data1.minute;
    duankou=data1.duankou;

    for(int i=0;i!=15;i++)
        IP[i]=data1.IP[i];
    for(int i=0;i!=10;i++)
        admin1[i]=data1.admin1[i];
    for(int i=0;i!=20;i++)
       code1[i]=data1.code1[i];

    x[0]=data1.x11;  x[1]=data1.y11;  x[2]=data1.x12;  x[3]=data1.y12;
    x[4]=data1.x21;  x[5]=data1.y21;  x[6]=data1.x22;  x[7]=data1.y22;
    x[8]=data1.x31;  x[9]=data1.y31;  x[10]=data1.x32; x[11]=data1.y32;
    x[12]=data1.x41; x[13]=data1.y41; x[14]=data1.x42; x[15]=data1.y42;
    x[16]=data1.x51; x[17]=data1.y51; x[18]=data1.x52; x[19]=data1.y52;

    dx[0]=data1.dx11;  dx[1]=data1.dy11;  dx[2]=data1.dx12;  dx[3]=data1.dy12;
    dx[4]=data1.dx21;  dx[5]=data1.dy21;  dx[6]=data1.dx22;  dx[7]=data1.dy22;
    dx[8]=data1.dx31;  dx[9]=data1.dy31;  dx[10]=data1.dx32; dx[11]=data1.dy32;
    dx[12]=data1.dx41; dx[13]=data1.dy41; dx[14]=data1.dx42; dx[15]=data1.dy42;
    dx[16]=data1.dx51; dx[17]=data1.dy51; dx[18]=data1.dx52; dx[19]=data1.dy52;
    //need a judgement with order.
    return 1;
}
int SocketMatTransmissionClient::get(int& key)
{
    needRecv = sizeof(recvBuf);
    int pos = 0;
    int len0 = 0;

    while (pos < needRecv)
    {
        len0 = recv(sockClient, (char*)(&data1) + pos, needRecv - pos, 0);
        if (len0 < 0)
        {
            printf("Server Recieve Data Failed!\n");
            break;
        }
        pos += len0;
    }
    if(data1.order==2)
        key=2;
    return 1;


}
