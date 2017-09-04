#include <cstdio>
    #include"iostream"
    #include <cstring>

    #include "HCNetSDK.h"
    #include "PlayM4.h"

    #include "Higo_SSD_lib.h"
    #include"trackpoint.h"
    #include "comparision.h"

    #include <opencv2/tracking.hpp>
    #include <opencv2/videoio.hpp>
    #include <opencv2/core/utility.hpp>
    #include <opencv2/highgui.hpp>
    #include <cstring>

    #include <iomanip>
    #include <fstream>
    #include <stdlib.h>
    #include <stdio.h>

    #include <opencv2/opencv.hpp>
    #include <opencv2/core/core.hpp>
    #include <opencv2/highgui/highgui.hpp>
    #include <opencv2/imgproc/imgproc.hpp>

    #include "cv.h"
    #include "highgui.h"
    #include <time.h>
	#include <unistd.h>

    #define WIDTH 960
    #define HEIGHT 540
    #define USECOLOR 1

    #define WIDTH 960
    #define HEIGHT 540
    #define OBJECTCAPACITY 30

    using namespace std;
    using namespace cv;
    int iPicNum=0;//Set channel NO.
    int nPort=-1;
    HWND hWnd=NULL;
///时刻保证两个量中一个为1一个为0
    int testpic=1;///统计主函数是否已经处理完图像,1表示已经处理完，回调函数可以读入
    int testpicread=0;///统计回调函数是否执行完成，1表示执行完成，可以调用主函数
    Mat frame;///用来接收操作的图像
///**************************************************************
    ///人数统计全局参数
    int nums = 0;      /// 现在画面内人数
    int old_nums=0;    /// 上一帧画面内人数
    Object object[OBJECTCAPACITY];
    Object old_object[OBJECTCAPACITY];
    unsigned int idgo=0;        ///用于id的增长
    double thre;

    string itos(int i) // 将int 转换成string
    {
        stringstream s;
        s << i;
        return s.str();
    }

    void change_id(Object *objectNew,Object *objectOld,int numsNew,int numsOld,trackset &tracks,unsigned int &idgo,float *prameters,int &in_nums,int &out_nums)
    {
    comparision con;
    con.setThreshold(thre);
    con.change_id(objectNew,objectOld,numsNew,numsOld,tracks,idgo,prameters,in_nums,out_nums);
    //con.AddToTrackset(tracks);
    }

///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ///解码回调 视频为YUV数据(YV12)，音频为PCM数据
    ///                 播放器通道号，解码后数据指针，解码后数据长度，*结构体指针 pFrameInfo*，两个保留
    void CALLBACK DecCBFun(int nPort,char * pBuf,int nSize,FRAME_INFO * pFrameInfo, void* nUser,int nReserved2)
    {
        if(testpic==0) ///主函数没有完成执行，不需要回调
            return;
        int clockdecodestart=clock();

        testpicread=0; ///图片还没有读进去
        long lFrameType = pFrameInfo->nType;
        ///int framenumber = pFrameInfo->dwFrameNum;

        if(lFrameType ==T_YV12)          ///调整显示的帧数
        {
            Mat dst(pFrameInfo->nHeight,pFrameInfo->nWidth,CV_8UC3);//这里nHeight为720,nWidth为1280,8UC3表示8bit uchar 无符号类型,3通道值
            Mat src(pFrameInfo->nHeight + pFrameInfo->nHeight/2,pFrameInfo->nWidth,CV_8UC1,(uchar*)pBuf);
            cvtColor(src,dst,CV_YUV2BGR_YV12);

            resize(dst,frame,Size(WIDTH,HEIGHT));
            dst.release();
            src.release();
            testpicread=1; ///读图完成，主函数可以执行
            testpic=0; ///主程序未完成
        }
        int clockdecodestop=clock();
        cout<<"decode time is: "<<clockdecodestop-clockdecodestart<<endl;
    }


    ///实时流回调
    ///               预览句柄，       RealPlay返回，   数据类型，   存放数据的缓冲区指针， 缓冲区大小， 用户数据
    void CALLBACK fRealDataCallBack(LONG lRealHandle,DWORD dwDataType,BYTE *pBuffer,DWORD dwBufSize,void *pUser)
    {
        int clockflowstart=clock();

        unsigned int dRet;
        switch (dwDataType)
        {
        case NET_DVR_SYSHEAD:    //系统头
            if(dwBufSize > 0)
            {
                ///打开流/  播放通道号，头文件数据，头文件长度，存放数据流的缓冲区大小
              if (!PlayM4_OpenStream(nPort,pBuffer,dwBufSize,1024*1024))
                {
                    dRet=PlayM4_GetLastError(nPort);
                    cout<<"OpenStream callback error is :"<<dRet<<endl;
                    break;
                }

                PlayM4_SetDecCBStream(nPort,1);            ///设置解码回调流为视频流
                PlayM4_ThrowBFrameNum(nPort,1);            ///每次丢掉1帧
                //PlayM4_SkipErrorData(nPort,1);             ///错帧后直接跳到下一帧解码
                PlayM4_SetDisplayBuf(nPort,1);             ///设置最大缓冲帧数

                //设置解码回调函数 只解码不显示
                ///播放通道号，解码回调函数指针
               if (!PlayM4_SetDecCallBackMend(nPort,DecCBFun,NULL))
                {
                    dRet=PlayM4_GetLastError(nPort);
                    cout<<"set decode callback error is :"<<dRet<<endl;
                    break;
                }
        ///打开视频解码/ 播放通道号，播放视频的窗口句柄
                if (!PlayM4_Play(nPort,hWnd))
                {
                    dRet=PlayM4_GetLastError(nPort);
                    cout<<"PlayM4_Play callback error is :"<<dRet<<endl;
                    break;
                }
            }
            break;

        case NET_DVR_STREAMDATA:   ///码流数据
            if (dwBufSize > 0 && nPort != -1)
            {
                ///返回1表示已经输入数据
                BOOL inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
                while (!inData)
                {
                    dRet=PlayM4_GetLastError(nPort);
                    usleep(10000);
                    inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
                    cout<<"码流读取 error is :"<<dRet<<endl;
                    ///cout << "PlayM4_InputData failed \n" << endl;
                }
            }
            break;
        }
        int clockflowstop=clock();
        cout<<"flow callback time is:"<<clockflowstop-clockflowstart<<endl;

    }

    void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
    {
        //char tempbuf[256] = {0};
        if(dwType==EXCEPTION_RECONNECT)
            printf("----------reconnect--------%d\n", (int)time(NULL));
    }

    int main()
    {
      // 初始化
      NET_DVR_Init();
      //设置连接时间与重连时间
      NET_DVR_SetConnectTime(2000, 1);
      NET_DVR_SetReconnect(10000, true);
///*************************************************************
      ///参数设置
      trackset Tracksets;///总的二维储存数组，按id顺序存储轨迹，在结束的轨迹末尾加上了点（-100000，-100000）用于判断轨迹是否终止
      HANDLE h_detect = NULL;
      const string model_file = "models/deploy.prototxt";
      const string weights_file = "models/VGG_VOCPeopleCount_SSD_people_300x300_iter_11871.caffemodel";

      char IP[13],admin1[10],code1[20];///设置端口的IP，用户名，密码
      int port=0;

      float point1_x,point1_y,point2_x,point2_y;
      float dir1_x,dir1_y,dir2_x,dir2_y;

      FILE *config;
      if((config=fopen("config.txt","r"))==NULL)
      {
        cout <<"no such file" << endl;
        return 0;      ////////////////////////////////////如果打不开直接关掉程序
      }
        fscanf(config,"Bound:%f,%f %f,%f\n",&point1_x,&point1_y,&point2_x,&point2_y);   ///读取边界
        fscanf(config,"Dir_in:%f,%f %f,%f\n",&dir1_x,&dir1_y,&dir2_x,&dir2_y);          ///读取向量
        fscanf(config,"threshold:%lf\n",&thre);
        fscanf(config,"IP:%s\n",IP);
        fscanf(config,"port:%d\n",&port);
        fscanf(config,"admin:%s\n",admin1);
        fscanf(config,"code:%s\n",code1);
        int i=0;
        for(;i!=10;i++)   ///用户名最多只能10个字符
        {
            if(admin1[i]=='\0')
                break;
        }
        i++;
        char *admin=new char[i];
        for(int j=0;j!=i;j++)
            admin[j]=admin1[j];
        for(i=0;i!=20;i++)  ///密码最多20个字符
        {
            if(code1[i]=='\0')
                break;
        }
        i++;       ///必须要把'\0'读进去
        char *code=new char[i];
        for(int j=0;j!=i;j++)
            code[j]=code1[j];

        dir1_y=(dir2_y-dir1_y)*HEIGHT;  dir1_x=(dir2_x-dir1_x)*WIDTH;                   ///得到最终的正方向向量x,y值
                                                                                       ///后面可以读第三行，设置一个感兴趣的画面区域进行检测
        fclose(config);
        cout <<point1_x <<" "<<point1_y<<" "<<point2_x<<" "<<point1_y<< endl;
        cout<<"threshold: "<<thre<<endl;
        //cout<<"IP: "<<IP<<endl;
        //cout<<"admin: "<<admin<<endl;
        //cout<<"code: "<<code<<endl;
      float prameters[6]={point1_x*WIDTH,point1_y*HEIGHT,point2_x*WIDTH,point2_y*HEIGHT,dir1_x,dir1_y};;///用于储存向量和门的参数

     long currentFrame =0;
     SSDDetectInit(&h_detect, model_file, weights_file, 0.6);
     std::vector<std::vector<int> >  detections;
     double t;
     for(int i=0;i<OBJECTCAPACITY;i++)
     {
        object[i].tracker = Tracker::create( "KCF" );
     }
     int r=50;
     //int count1,count2;
     int in_nums=0;
     int out_nums=0;

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      // 注册设备
      LONG lUserID;
      NET_DVR_DEVICEINFO_V30 struDeviceInfo;
      lUserID = NET_DVR_Login_V30(IP, (WORD)port, admin, code, &struDeviceInfo);
      nPort = 1;  ///设置视频通道

      PlayM4_SetStreamOpenMode(nPort,STREAME_REALTIME);

      if (lUserID < 0)
      {
           printf("Login error, %d\n", NET_DVR_GetLastError());
           NET_DVR_Cleanup();
           return 0;
      }

      //---------------------------------------
      //设置异常消息回调函数
      NET_DVR_SetExceptionCallBack_V30(0, NULL,g_ExceptionCallBack, NULL);
      //---------------------------------------
      //启动预览并设置回调数据流
      NET_DVR_CLIENTINFO ClientInfo;
      ClientInfo.lChannel = nPort;        //Channel number 设备通道号
      ClientInfo.hPlayWnd = NULL;     ///窗口为空,只解码不显示
      ClientInfo.lLinkMode = 0;       //Main Stream
      ClientInfo.sMultiCastIP = NULL;

      LONG lRealPlayHandle;

      namedWindow("IPCamera");
      ///时时浏览
      lRealPlayHandle = NET_DVR_RealPlay_V30(lUserID,&ClientInfo,fRealDataCallBack,NULL,TRUE);
      if (lRealPlayHandle<0)
      {
            printf("NET_DVR_RealPlay_V30 failed! Error number: %d\n",NET_DVR_GetLastError());
            return 0;
      }
        while(1)
        {
            if(waitKey(1)==1048586)
                break; ///按下回车
    if(testpicread==1) ///图片已经度进来了
    {
        int clockmainstart=clock();
  ///****************************************************************
        testpic=0; ///主程序还未完成
        if(currentFrame%13==0)
        {
            t = ((double)getTickCount() - t)/getTickFrequency();
            cout <<"Have ran for: "<<t<<endl;
            for(int i=0;i<OBJECTCAPACITY;i++)
            {
                object[i].tracker->clear();
                object[i].tracker = Tracker::create( "KCF" );
                object[i].id=0xffffffffffffffff;
            }
            SSDDetect(h_detect, frame, detections, nums);
            cout<<"正在读取第"<<currentFrame<<"帧(detecting)"<<endl;
            cout << "nums = "<< nums <<endl;
            for (int i = 0; i < detections.size(); ++i)
            {
                object[i].Target_x=(detections[i][0]+detections[i][2])/2;//x
                object[i].Target_y=(detections[i][1]+detections[i][3])/2;//y
                cout <<object[i].id << " :" ;
                cout << " " << object[i].Target_x<<","<<object[i].Target_y;
                cout << endl;
                cv::circle(frame,cv::Point (object[i].Target_x,object[i].Target_y),r,Scalar(0,0,255),2);
                object[i].roi=Rect2d(cv::Point(detections[i][0]+15,detections[i][1]+15),cv::Point(detections[i][2]-15,detections[i][3]-15));
                //object[i].id=i;
               //object[i].id=0xffffffffffffffff? object[i].id=idgo++ : object[i].id;
            }

            change_id(object,old_object,nums,old_nums,Tracksets,idgo,prameters,in_nums,out_nums); ///增加了参数，使用的总体矩阵和idgo全局变量

            for(int i=0;i<nums;i++)
            {
                object[i].tracker->init(frame,object[i].roi);
            }
            cout<<"init"<<endl;
            t = (double)getTickCount();
        }
        else
        {
            cout<<"正在读取第"<<currentFrame<<"帧(tracking)"<<endl;
            cout << "nums = "<< nums <<endl;
            for(int i=0;i<nums;i++)
            {
                object[i].tracker->update(frame,object[i].roi);

                rectangle(frame, object[i].roi, Scalar( 255, 0, 0 ), 2, 1 );
                object[i].Target_x=object[i].roi.x+object[i].roi.width/2; ///找出框的中心
                object[i].Target_y=object[i].roi.y+object[i].roi.height/2;

                Tracksets.addpoint(object[i].Target_x,object[i].Target_y,object[i].id+1);///第n条轨迹的id为n

                cout <<object[i].id<< " :" ;
                cout << " " << object[i].Target_x<<","<<object[i].Target_y;
                cout << endl;

                old_object[i].Target_x=object[i].Target_x;
                old_object[i].Target_y=object[i].Target_y;
                old_object[i].id=object[i].id;
            }
            old_nums=nums;
        }
        cv::line(frame,Point(WIDTH*point1_x,HEIGHT*point1_y),Point(WIDTH*point2_x,HEIGHT*point2_y),Scalar(0,0,0),2,8);
        cv::putText(frame,"Persons in:"+itos(in_nums),Point(WIDTH*0.75,HEIGHT*0.1),CV_FONT_HERSHEY_SIMPLEX,0.6,Scalar(255,255,255),2,2); // 显示字符
        cv::putText(frame,"Persons out:"+itos(out_nums),Point(WIDTH*0.75,HEIGHT*0.15),CV_FONT_HERSHEY_SIMPLEX,0.6,Scalar(255,255,255),2,2); // 显示字符

        for(int i=0;i!=nums;i++)///画线
            Tracksets.drawLine(object[i].id+1,frame);

  ///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                imshow("IPCamera",frame);
                currentFrame++;
                cout << "current frame is: " <<currentFrame<<endl;
                testpic=1;  ///主程序已经完成
                testpicread=0; ///图片还没有读进去
        int clockmainstop=clock();
        cout<<"main function time: "<<clockmainstop-clockmainstart<<endl;
    }
        }

      SSDDetectUnInit(h_detect);
      usleep(10);

      //fclose(fp);
      //---------------------------------------
      //关闭预览
      if(!NET_DVR_StopRealPlay(lRealPlayHandle))
      {
        printf("NET_DVR_StopRealPlay error! Error number: %d\n",NET_DVR_GetLastError());
        return 0;
      }
      else
      {
           printf("NET_DVR_StopRealPlay succeed!\n");
      }
      //注销用户

      PlayM4_CloseStream(nPort);
      PlayM4_FreePort(nPort);
      NET_DVR_Logout(lUserID);
      NET_DVR_Cleanup();

      return 0;
    }

