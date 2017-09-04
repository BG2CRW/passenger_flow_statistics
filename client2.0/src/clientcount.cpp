#include "clientcount.h"

#include <opencv2/opencv.hpp>
#include <iostream>

#include "Higo_SSD_lib.h"
#include"trackpoint.h"
#include "comparision.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <cstring>

#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 960
#define HEIGHT 540
#define OBJECTCAPACITY 30
/*int nums = 0;
int old_nums=0;

Object object[OBJECTCAPACITY];
Object old_object[OBJECTCAPACITY];
unsigned int idgo=0;        ///用于id的增长
double thre;

void change_id(Object *objectNew,Object *objectOld,int numsNew,int numsOld,trackset &tracks,unsigned int &idgo,float *prameters,int &in_nums,int &out_nums)
{
    comparision con;
    con.setThreshold(thre);
    con.change_id(objectNew,objectOld,numsNew,numsOld,tracks,idgo,prameters,in_nums,out_nums);
    //con.AddToTrackset(tracks);
}
string itos(int i) // 将int 转换成string
{
    stringstream s;
    s << i;
    return s.str();
}
*/
clientcount::clientcount()
{

}

clientcount::~clientcount()
{

}
void clientcount::GetCount(Mat &img)
{
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
        return;      ////////////////////////////////////如果打不开直接关掉程序
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

}
