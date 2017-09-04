    #include"titlefiles.h"
    using namespace std;
    using namespace cv;
    #define debug 1  ///1为与主界面通信显示，0为本程序内现实
    #define vediodebug 1  ///1跑摄像头，0跑视频
    #define configdebug 1 ///1用config输入参数，0用main输入
    int LINENOW;          ///标出当前的线数
    SocketMatTransmissionClient socketMat;
    int nPort=-1;
    queue<Mat> q1,q2;  ///q1用于储存解码图像,q2储存完成图像
    float pointxy[LINEMAXNUM][4]; ///门的位置
    float dirxy[LINEMAXNUM][4];   ///方向点
    float dirx[LINEMAXNUM];float diry[LINEMAXNUM];///方向向量
    int stopthread=0;
    int hour=23;int minute=59;
    int key=0;
    double thre; ///用于输入匹配阈值
    int order=-1;
    unsigned int in_nums[LINEMAXNUM];
    unsigned int out_nums[LINEMAXNUM];
    char IP[13],admin1[10],code1[20];///设置端口的IP，用户名，密码,端口号
    int port=0;
    #if configdebug
    FILE *config;
    #endif // configdebug

///**************************************************************

    string itos(unsigned int i) // 将int 转换成string
    {
        stringstream s;
        s << i;
        return s.str();
    }
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ///解码回调 视频为YUV数据(YV12)，音频为PCM数据
    ///                 播放器通道号，解码后数据指针，解码后数据长度，*结构体指针 pFrameInfo*，两个保留
    void CALLBACK DecCBFun(int nPort,char * pBuf,int nSize,FRAME_INFO * pFrameInfo, void* nUser,int nReserved2)
    {
       // if(testpic==0) ///主函数没有完成执行，不需要回调
       //     return;
        cout<<"(callback)queue size is:"<<q1.size()<<endl;
        int clockdecodestart=clock();

       // testpicread=0; ///图片还没有读进去
        long lFrameType = pFrameInfo->nType;
        ///int framenumber = pFrameInfo->dwFrameNum;

        if(lFrameType ==T_YV12)          ///调整显示的帧数
        {
            Mat dst(pFrameInfo->nHeight,pFrameInfo->nWidth,CV_8UC3);//这里nHeight为720,nWidth为1280,8UC3表示8bit uchar 无符号类型,3通道值
            Mat src(pFrameInfo->nHeight + pFrameInfo->nHeight/2,pFrameInfo->nWidth,CV_8UC1,(uchar*)pBuf);
            cvtColor(src,dst,CV_YUV2BGR_YV12);

            resize(dst,dst,Size(WIDTH,HEIGHT));
            if(q1.size()<=5000)
                q1.push(dst);  ///将解吗的图片放入队列
  ///             cout<<"queue's size is :"<<q1.size()<<endl;
            dst.release();
            src.release();
         //   testpicread=1; ///读图完成，主函数可以执行
         //   testpic=0; ///主程序未完成
        }
        int clockdecodestop=clock();
        cout<<"decode time is: "<<clockdecodestop-clockdecodestart<<endl;   ///解码时间
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
                if (!PlayM4_Play(nPort,NULL))
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
                }
            }
            break;
        }
        int clockflowstop=clock();
        ///cout<<"flow callback time is:"<<clockflowstop-clockflowstart<<endl;  ///取流时间

    }

    void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
    {
        //char tempbuf[256] = {0};
        if(dwType==EXCEPTION_RECONNECT)
            printf("----------reconnect--------%d\n", (int)time(NULL));
    }

    ///222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222




    ///多线程，用于接受图片后的处理，相当于运算主体,
void* thread( void *arg )
{
    cout<<"thread 2 is on."<<endl;
    trackset Tracksets;///总的二维储存数组，按id顺序存储轨迹，在结束的轨迹末尾加上了点（-100000，-100000）用于判断轨迹是否终止

    const string model_file = "models/deploy.prototxt";
    const string weights_file = "models/VGG_VOCPeopleCount_SSD_people_300x300_iter_11871.caffemodel";

    int nums = 0;      /// 现在画面内人数
    int old_nums=0;    /// 上一帧画面内人数
    for(int i=0;i!=LINEMAXNUM;i++)
    {
        in_nums[i]=0;out_nums[i]=0;
    }

    Object object[OBJECTCAPACITY];
    Object old_object[OBJECTCAPACITY];
    unsigned int idgo=0;        ///用于id的增长
    HANDLE h_detect = NULL;

    long currentFrame =0;
    SSDDetectInit(&h_detect, model_file, weights_file, 0.6);
    std::vector<std::vector<int> >  detections;
    //double t;
    for(int i=0;i<OBJECTCAPACITY;i++)
    {
        object[i].tracker = Tracker::create( "KCF" );
    }
    int r=50;
    Mat frame;///用来接收操作的图

    float prameters[LINEMAXNUM][6];   ///point1_x,poin1_y,point2_x,point2_y,dir_x,dir_y
    LINENOW=0;
    for(int i=0;i!=LINEMAXNUM;i++)
    {
        prameters[i][0] = pointxy[i][0]*WIDTH;///用于储存向量和门的参数
        prameters[i][1] = pointxy[i][1]*HEIGHT;///用于储存向量和门的参数
        prameters[i][2] = pointxy[i][2]*WIDTH;///用于储存向量和门的参数
        prameters[i][3] = pointxy[i][3]*HEIGHT;///用于储存向量和门的参数
        prameters[i][4] = dirx[i];///用于储存向量和门的参数
        prameters[i][5] = diry[i];///用于储存向量和门的参数
        if(prameters[i][0]>=0)
            LINENOW++;
    }
comparision con; ///创建comparision类
con.setThreshold(thre);

while(stopthread==0)
{
    #if !debug
        key=waitKey(1); ///停止进程方式需要修改
    #endif
    if(key>0)
        break;

        #if debug
        {
            if(order==0) ///当收到改变参数命令。
            {
                LINENOW=0;
                for(int i=0;i!=LINEMAXNUM;i++)
                {
                    in_nums[i]=0;out_nums[i]=0;
                    prameters[i][0] = pointxy[i][0]*WIDTH;
                    prameters[i][1] = pointxy[i][1]*HEIGHT;
                    prameters[i][2] = pointxy[i][2]*WIDTH;
                    prameters[i][3] = pointxy[i][3]*HEIGHT;
                    prameters[i][4] = dirx[i];
                    prameters[i][5] = diry[i];
                    order=-1;
                    if(prameters[i][0]>=0)
                        LINENOW++;
                }
            }
        }
        #endif // debug

    cout<<"(main)queue size is:"<<q1.size()<<endl;
    while(q1.size()<=2){;}
            frame=q1.front();
            q1.pop();
        int clockmainstart=clock();
       // testpic=0; ///主程序还未完成

        if(currentFrame%5==0)
        {
            //t = ((double)getTickCount() - t)/getTickFrequency();
            //cout <<"Have ran for: "<<t<<endl;
            for(int i=0;i<OBJECTCAPACITY;i++)
            {
                object[i].tracker->clear();
                object[i].tracker = Tracker::create( "KCF" );
                object[i].id=0xffffffffffffffff;
            }
            SSDDetect(h_detect, frame, detections, nums);
            cout<<"正在读取第"<<currentFrame<<"帧(detecting)"<<endl;
            cout << "target nums = "<< nums <<endl;
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

            int reset=con.change_id(object,old_object,nums,old_nums,Tracksets,idgo,prameters,in_nums,out_nums,LINENOW); ///增加了参数，使用的总体矩阵和idgo全局变量

            if(!reset)///重置vector
            {
                Tracksets.tracksetclear();
            }
            time_t tt = time(NULL);
            tm* t= localtime(&tt);///得到系统时间
            if(t->tm_hour==23&&t->tm_min==59)///后面可以调节重置时间
            {
                idgo=0;
                for(int i=0;i!=LINEMAXNUM;i++)
                {
                    in_nums[i]=0;
                    out_nums[i]=0;
                }
                cout<<"all reset."<<endl;
            }

            for(int i=0;i<nums;i++)
            {
                object[i].tracker->init(frame,object[i].roi);
            }
            cout<<"init"<<endl;
            //t = (double)getTickCount();
        }
        else
        {
            cout<<"正在读取第"<<currentFrame<<"帧(tracking)"<<endl;
            cout << "nums = "<< nums <<endl;
            for(int i=0;i<nums;i++)
            {
                if(!object[i].tracker->update(frame,object[i].roi))
                {
                    if(abs(object[i].Target_x-WIDTH)<=10||abs(object[i].Target_y-HEIGHT)<=10)///如果跟踪到画面边缘
                    object[i].edge=1;
                }

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

        for(int i=0;i!=LINENOW;i++)
            cv::line(frame,Point(WIDTH*pointxy[i][0],HEIGHT*pointxy[i][1]),Point(WIDTH*pointxy[i][2],HEIGHT*pointxy[i][3]),Scalar(0,0,0),2,8);
        ///cv::putText(frame,"Persons in:"+itos(in_nums),Point(WIDTH*0.75,HEIGHT*0.1),CV_FONT_HERSHEY_SIMPLEX,0.6,Scalar(255,255,255),2,2); // 显示字符
        ///cv::putText(frame,"Persons out:"+itos(out_nums),Point(WIDTH*0.75,HEIGHT*0.15),CV_FONT_HERSHEY_SIMPLEX,0.6,Scalar(255,255,255),2,2); // 显示字符
        for(int i=0;i!=nums;i++)///画线
            Tracksets.drawLine(object[i].id+1,frame);

        #if debug
            q2.push(frame);
            cout<<"queue2 size:"<<q2.size()<<endl;
        #else
            imshow("client counting",frame);
        #endif // debug
        currentFrame++;
        cout << "current frame is: " <<currentFrame<<endl;
        int clockmainstop=clock();
        cout<<"main function time: "<<clockmainstop-clockmainstart<<endl;  ///客流统计时间

}

SSDDetectUnInit(h_detect);
    *(int*)arg = key;
    printf( "the clientcounting has been uninitialized.ASCII is：%d.\n", *(int*)arg);
    return arg;
}


///3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333
void* thread2( void *arg2 )
{
    Mat img;float xtest[4*LINEMAXNUM],dxtest[4*LINEMAXNUM];
    while(key<=0)
    {

    #if debug
    {
        while(q2.size()<2){;}
        img=q2.front();
        q2.pop();
        int transmitclock=clock();
        socketMat.transmit(img,in_nums,out_nums,LINENOW);
        int transmitclock1=clock();
        //cout<<"                                transmit time is:"<<transmitclock1-transmitclock<<endl; ///transmit的时间为0.1s级
            //cout<<"reansmit failed!"<<test<<endl;
        socketMat.get(order,(int&)thre,hour,minute,xtest,dxtest,IP,admin1,code1,port);
        int transmitclock2=clock();
        //cout<<"                                receive time is:"<<transmitclock2-transmitclock1<<endl; ///transmit的时间为0.1s级

        if(order==0)
        {
            LINENOW=0;
            for(int i=0;i!=LINEMAXNUM;i++)
            {
                pointxy[i][0]=xtest[0+4*i];pointxy[i][1]=xtest[1+4*i];pointxy[i][2]=xtest[2+4*i];pointxy[i][3]=xtest[3+4*i];
                dirxy[i][0]=dxtest[0+4*i];dirxy[i][1]=dxtest[1+4*i];dirxy[i][2]=dxtest[2+4*i];dirxy[i][3]=dxtest[3+4*i];
                if(pointxy[i][0]>=0)
                    LINENOW++;
            }
            if((config=fopen("config.txt","w"))==NULL)
            {
                cout <<"no such file" << endl;
                return 0;      ////////////////////////////////////如果打不开直接关掉程序
            }
            for(int i=0;i!=LINEMAXNUM;i++)
            {
                fprintf(config,"Bound:%f,%f %f,%f\n",pointxy[i][0],pointxy[i][1],pointxy[i][2],pointxy[i][3]);
                fprintf(config,"Dir_in:%f,%f %f,%f\n",dirxy[i][0],dirxy[i][1],dirxy[i][2],dirxy[i][3]);
            }
             fprintf(config,"threshold:%lf\n",thre);
             fprintf(config,"IP:%s\n",IP);                  ///后面还要能写入ip密码等
             fprintf(config,"port:%d\n",port);
             fprintf(config,"admin:%s\n",admin1);
             fprintf(config,"code:%s\n",code1);
             fclose(config);
             for(int i=0;i!=LINEMAXNUM;i++)
             {
                dirx[i]=(dirxy[i][3]-dirxy[i][1])*HEIGHT;
                diry[i]=(dirxy[i][2]-dirxy[i][0])*WIDTH;///得到最终的正方向向量x,y值
             }

        }
        else if(order==1)
            key=1;
        else{;}
    }
    #endif // debug
    }
   *(int*)arg2 = key;
    printf( "the clientcounting has been uninitialized.ASCII is：%d.\n", *(int*)arg2);
    return arg2;
}

    ///2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222

    int main(int argc, char* argv[])
    {
      // 初始化
      NET_DVR_Init();
      //设置连接时间与重连时间
      NET_DVR_SetConnectTime(2000, 1);
      NET_DVR_SetReconnect(10000, true);
///*************************************************************
      ///参数设置

      #if debug
        if (socketMat.socketConnect("127.0.0.1", 6666) < 0)
        {
            return 0;
        }
      #endif // debug

      #if configdebug
      if((config=fopen("config.txt","r"))==NULL)
      {
        cout <<"no such file" << endl;
        return 0;      ////////////////////////////////////如果打不开直接关掉程序
      }
      LINENOW=0;
    for(int i=0;i!=LINEMAXNUM;i++)
    {
        fscanf(config,"Bound:%f,%f %f,%f\n",&pointxy[i][0],&pointxy[i][1],&pointxy[i][2],&pointxy[i][3]);   ///读取边界
        fscanf(config,"Dir_in:%f,%f %f,%f\n",&dirxy[i][0],&dirxy[i][1],&dirxy[i][2],&dirxy[i][3]);          ///读取向量
        if(pointxy[i][0]>=0)
            LINENOW++;
    }
      fscanf(config,"threshold:%lf\n",&thre);
      fscanf(config,"IP:%s\n",IP);
      fscanf(config,"port:%d\n",&port);
      fscanf(config,"admin:%s\n",admin1);
      fscanf(config,"code:%s\n",code1);
      int ii=0;
      for(;ii!=10;ii++)   ///用户名最多只能10个字符
      {
        if(admin1[ii]=='\0')
            break;
      }
      ii++;
      char *admin=new char[ii];
      for(int j=0;j!=ii;j++)
        admin[j]=admin1[j];
      for(ii=0;ii!=20;ii++)  ///密码最多20个字符
      {
        if(code1[ii]=='\0')
            break;
      }
      ii++;       ///必须要把'\0'读进去
      char *code=new char[ii];
      for(int j=0;j!=ii;j++)
        code[j]=code1[j];
    for(int i=0;i!=LINENOW;i++)
    {
        dirx[i]=(dirxy[i][3]-dirxy[i][1])*HEIGHT;
        diry[i]=(dirxy[i][2]-dirxy[i][0])*WIDTH;///得到最终的正方向向量x,y值
    }

                                                                            ///后面可以读第三行，设置一个感兴趣的画面区域进行检测
      fclose(config);
      #else   ///如何在第一次将所有参数输入，如何保存上次的参数
      char* duankou;
      IP=argv[1];
      duankou=argv[2];
      admin=argv[3];
      code=argv[4];
      stringstream ss;
      ss<<duankou;
      ss>>port;
      #endif

        cout<<"threshold: "<<thre<<endl;
        //cout<<"IP: "<<IP<<endl;
        //cout<<"admin: "<<admin<<endl;
        //cout<<"code: "<<code<<endl;
///-------------------------------------------------------------
///多线程
  pthread_t th;
    int ret;
    int arg = 10;
    int *thread_ret = NULL;
    ///参数3为新线程函数，4为返回参数
    ///要求函数为形参和输出均为(void*)
    ret = pthread_create( &th, NULL, thread, &arg );
    if( ret != 0 )
    {
        printf( "Create thread error!\n");
        return -1;
    }
    else
    {
            cout<<"Create thread succeed!\n"<<endl;
    }

  pthread_t th2;
    int ret2;
    int arg2 = 10;
    int *thread_ret2 = NULL;
    ///参数3为新线程函数，4为返回参数
    ///要求函数为形参和输出均为(void*)
    ret2 = pthread_create( &th2, NULL, thread2, &arg2 );
    if( ret2 != 0 )
    {
        printf( "Create thread2 error!\n");
        return -1;
    }
    else
    {
            cout<<"Create thread2 succeed!\n"<<endl;
    }


///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if vediodebug ///跑监控
{
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
      ClientInfo.lChannel = nPort;    //Channel number 设备通道号
      ClientInfo.hPlayWnd = NULL;     ///窗口为空,只解码不显示
      ClientInfo.lLinkMode = 0;       //Main Stream
      ClientInfo.sMultiCastIP = NULL;

      LONG lRealPlayHandle;

      ///时时浏览
      lRealPlayHandle = NET_DVR_RealPlay_V30(lUserID,&ClientInfo,fRealDataCallBack,NULL,TRUE);
      if (lRealPlayHandle<0)
      {
            printf("NET_DVR_RealPlay_V30 failed! Error number: %d\n",NET_DVR_GetLastError());
            return 0;
      }
      usleep(10);

      while(1)
      {
        if(key>0)
            break;
      }

      //---------------------------------------
      //关闭预览
      stopthread=1;  ///向线程发送信号，跳出循环，执行uninitial。

    ///th为被等待线程，参量2存储被等待线程的返回值
    ///知道被等待线程执行完才执行下一个线程
    ///因为多线程函数传回来的是void*，
    ///必须设出thread_ret指针类型来确定长度。
    pthread_join( th, (void**)&thread_ret ); ///等待线程函数完毕
    if(*thread_ret!=0)
        printf( "thread_ret = %d.\n", *thread_ret );
      pthread_cancel(th); ///关闭线程1

    pthread_join( th2, (void**)&thread_ret2 ); ///等待线程函数完毕
    if(*thread_ret2!=0)
        printf( "thread_ret = %d.\n", *thread_ret2 );
      pthread_cancel(th2); ///关闭线程1


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

}
#else///跑视频
{
    string title;
    cout<<"Please input the full title of vidieo(for example: 5m3.mp4):"<<endl;
    cin>>title;
    const string position = "images/";
     VideoCapture capture(position+title);//打开视频文件：其实就是建立一个VideoCapture结构
     if(!capture.isOpened())//检测是否正常打开:成功打开时，isOpened返回ture
        cout<<"fail to open!"<<endl;
     long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);    //获取整个帧数
    cout<<"整个视频共"<<totalFrameNumber<<"帧"<<endl;
    long frameToStart = 0;//设置开始帧()
    capture.set( CV_CAP_PROP_POS_FRAMES,frameToStart);
    cout<<"从第"<<frameToStart<<"帧开始读"<<endl;
    int frameToStop = totalFrameNumber;//设置结束帧
    cout<<"结束帧为：第"<<frameToStop<<"帧"<<endl;
    double rate = 25;
    if(capture.get(CV_CAP_PROP_FPS)<50)
        rate = capture.get(CV_CAP_PROP_FPS);//获取帧率
    cout<<"帧率为:"<<rate<<endl;
    bool stop = false;//定义一个用来控制读取视频循环结束的变量
    Mat frame0,frameOrg0;//承载每一帧的图像

    while(1)
    {
        capture >> frameOrg0;
        cout << "get next frame." << endl;
        resize(frameOrg0,frame0,Size(WIDTH,HEIGHT),0,0,CV_INTER_LINEAR);
        q1.push(frame0);
        usleep(50000);
        if(debug)
            socketMat.get(key);
        if(key>0)
            break;
    }
         //---------------------------------------
      //关闭预览
      stopthread=1;  ///向线程发送信号，跳出循环，执行uninitial。

    ///th为被等待线程，参量2存储被等待线程的返回值
    ///知道被等待线程执行完才执行下一个线程
    ///因为多线程函数传回来的是void*，
    ///必须设出thread_ret指针类型来确定长度。
    pthread_join( th, (void**)&thread_ret ); ///等待线程函数完毕
    if(*thread_ret!=0)
        printf( "thread_ret = %d.\n", *thread_ret );


      pthread_cancel(th); ///关闭线程
}
#endif // vediodebug

#if debug
{
    socketMat.socketDisconnect();
}
#endif // debug

      return 0;
    }


