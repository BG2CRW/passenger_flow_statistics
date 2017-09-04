//  基于OpenCV和Socket的图像传输（接收）
#include "SocketMatTransmissionServer.h"

SocketMatTransmissionServer::SocketMatTransmissionServer(void)
{
	data.in_nums1=-1;data.in_nums2=-1;data.in_nums3=-1;data.in_nums4=-1;data.in_nums5=-1;
    data.out_nums1=-1;data.out_nums2=-1;data.out_nums3=-1;data.out_nums4=-1;data.out_nums5=-1;
}


SocketMatTransmissionServer::~SocketMatTransmissionServer(void)
{
}


int SocketMatTransmissionServer::socketConnect(int PORT)
{
int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);
//int flags=fcntl(server_sockfd,F_GETFL,0);              // Get socket flags
//fcntl(server_sockfd,F_SETFL,flags|O_NONBLOCK); //set no block

struct timeval timeout={4,0};///set over time 
setsockopt(server_sockfd,SOL_SOCKET,SO_SNDTIMEO,(char*)&timeout,sizeof(struct timeval));
setsockopt(server_sockfd,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));

struct sockaddr_in server_sockaddr;
server_sockaddr.sin_family = AF_INET;
server_sockaddr.sin_port = htons(PORT);
server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);


int on=1;  
if((setsockopt(server_sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)  
{  
    perror("setsockopt failed");  
    exit(EXIT_FAILURE);  
}  

if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
{
    perror("bind");
    return -1;
}

if(listen(server_sockfd,5) == -1)
{
    perror("listen");
    return -1;
}

struct sockaddr_in client_addr;
socklen_t length = sizeof(client_addr);

sockConn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
if(sockConn<0)
{
    perror("connect");
    return -1;
}
else
{
    printf("connect successful!\n");
    return 1;
}

close(server_sockfd);
}


void SocketMatTransmissionServer::socketDisconnect(void)
{
close(sockConn);
}

int SocketMatTransmissionServer::receive(cv::Mat& image,unsigned int* in_num,unsigned int* out_num,int& lineNum,int &order)
{
int returnflag = 0;
cv::Mat img(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, cv::Scalar(0));
needRecv = sizeof(recvBuf);
count = 0;
memset(&data,0,sizeof(data));

for (int i = 0; i < PACKAGE_NUM; i++)
{
    int pos = 0;
    int len0 = 0;

    while (pos < needRecv)
    {
        len0 = recv(sockConn, (char*)(&data) + pos, needRecv - pos, 0);
        if (len0 < 0)
        {
            printf("Server Recieve Data Failed!\n");
            break;
        }
        pos += len0;
    }

    count = count + data.flag;
    //std::cout<<count<<std::endl;

    int num1 = IMG_HEIGHT / PACKAGE_NUM * i;
    for (int j = 0; j < IMG_HEIGHT / PACKAGE_NUM; j++)
    {
        int num2 = j * IMG_WIDTH * 3;
        uchar* ucdata = img.ptr<uchar>(j + num1);
        for (int k = 0; k < IMG_WIDTH * 3; k++)
        {
            ucdata[k] = data.buf[num2 + k];
        }
    }

    if (data.flag == 2)
    {
        if (count == PACKAGE_NUM + 1)
        {
            image = img;
            returnflag = 1;
            count = 0;
        }
        else
        {
            count = 0;
            i = 0;
        }
    }
}

in_num[0]=data.in_nums1; in_num[1]=data.in_nums2; in_num[2]=data.in_nums3; in_num[3]=data.in_nums4; in_num[4]=data.in_nums5;
out_num[0]=data.out_nums1; out_num[1]=data.out_nums2; out_num[2]=data.out_nums3; out_num[3]=data.out_nums4; out_num[4]=data.out_nums5;
lineNum=data.lineNum;
order=data.order;
if(returnflag == 1)
    return 1;
else
    return -1;
}


int SocketMatTransmissionServer::sender(int threshold,int hour,int minute,float x[20],float dx[20],char IP[15],char admin1[10],char code1[20],int duankou,int order)
{
    data1.order=order;
    data1.threshold=threshold;
    data1.hour=hour;
    data1.minute=minute;

    data1.x11=x[0]; data1.y11=x[1]; data1.x12=x[2]; data1.y12=x[3];
    data1.x21=x[4]; data1.y21=x[5]; data1.x22=x[6]; data1.y22=x[7];
    data1.x31=x[8]; data1.y31=x[9]; data1.x32=x[10];data1.y32=x[11];
    data1.x41=x[12];data1.y41=x[13];data1.x42=x[14];data1.y42=x[15];
    data1.x51=x[16];data1.y51=x[17];data1.x52=x[18];data1.y52=x[19];

    data1.dx11=dx[0]; data1.dy11=dx[1]; data1.dx12=dx[2]; data1.dy12=dx[3];
    data1.dx21=dx[4]; data1.dy21=dx[5]; data1.dx22=dx[6]; data1.dy22=dx[7];
    data1.dx31=dx[8]; data1.dy31=dx[9]; data1.dx32=dx[10];data1.dy32=dx[11];
    data1.dx41=dx[12];data1.dy41=dx[13];data1.dx42=dx[14];data1.dy42=dx[15];
    data1.dx51=dx[16];data1.dy51=dx[17];data1.dx52=dx[18];data1.dy52=dx[19];

    for(int i=0;i!=15;i++)
        data1.IP[i]=IP[i];
    for(int i=0;i!=10;i++)
        data1.admin1[i]=admin1[i];
    for(int i=0;i!=20;i++)
        data1.code1[i]=code1[i];
    data1.duankou=duankou;

    if (send(sockConn, (char *)(&data1), sizeof(data1), 0) < 0)
    {
        printf("paramater send failed.\n");
        return -1;
    }
    return 1;
}

int SocketMatTransmissionServer::sender(float x[40])
{
    data1.order=1; //need expansion
    //data1.threshold=50;
    //data1.hour=23;
    //data1.minute=59;
    //data1.second=59;
    data1.x11=x[0]; data1.y11=x[1]; data1.x12=x[2]; data1.y12=x[3];
    data1.x21=x[4]; data1.y21=x[5]; data1.x22=x[6]; data1.y22=x[7];
    data1.x31=x[8]; data1.y31=x[9]; data1.x32=x[10];data1.y32=x[11];
    data1.x41=x[12];data1.y41=x[13];data1.x42=x[14];data1.y42=x[15];
    data1.x51=x[16];data1.y51=x[17];data1.x52=x[18];data1.y52=x[19];
    if (send(sockConn, (char *)(&data1), sizeof(data1), 0) < 0)
    {
        printf("paramater send failed.\n");
        return -1;
    }
    return 1;
}

int SocketMatTransmissionServer::sender(int order)
{
    data1.order=order;
    //data1.threshold=50;
    //data1.hour=23;
    //data1.minute=59;
    //data1.x1=-1;
    //data1.x2=-1;
    //data1.y1=-1;
    //data1.y2=-1;
    if (send(sockConn, (char *)(&data1), sizeof(data1), 0) < 0)
    {
        printf("close order send failed.\n");
        return -1;
    }
    return 1;
}
