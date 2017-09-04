#include"titlefiles.h"

comparision::comparision()
{

}
comparision::~comparision()
{

}

 double comparision::Getdistance(cv::Point p1,cv::Point p2)
 {
     double distance=0;
     double dx=0,dy=0;
     dx=abs(p1.x-p2.x);  dy=abs(p1.y-p2.y);
     distance = dx+dy;//直接用平方
     return distance;
 }

int comparision::change_id(Object *object1,Object *object,int& numsNew,int& numsOld,trackset &trackss,
unsigned int &idgo,float prameters[][6],unsigned int *in_nums,unsigned int *out_nums,int LINENOW)
{
    //std::cout<<"old:"<<object[0].id<<std::endl;
    if(object[0].id==0xffffffffffffffff&&trackss.isEmpty())///初始化的时候直接用object
    {
        //std::cout<<"reset all."<<std::endl;
        for(int i=0;i!=numsNew;i++)
        {
            trackpoint trackpointtemp;
            trackpointtemp.addpoint(object1[i].Target_x,object1[i].Target_y);
            trackpointtemp.id=i;
            object1[i].id=i;
            trackss.addtrack(trackpointtemp);
        }
        idgo=numsNew;
        if(numsNew!=0)  ///当检测点数不为零
            ///std::cout<<"track set initialization."<<std::endl;
        return 1;
    }

    //cout<<"numnew: "<<numsNew<<endl;
    //cout<<"numold: "<<numsOld<<endl;

    if(numsNew==0&&numsOld==0)
        return 0;                      ///返回0代表此次匹配完全没有人

    trackpoint a;///储存本次的检测点，a[i] ~ Object[i]
    trackpoint b;///储存跟踪
    for(int i=0;i!=numsNew;i++)//读取检测
    {
        a.addpoint(object1[i].Target_x,object1[i].Target_y);
    }
    for(int i=0;i!=numsOld;i++)//读取跟踪
    {
        if(object[i].edge==0||object[i].edge==3)///如果跟踪正常(包括正常和上次未检测到)，不是到达画面边缘或者跟丢，入列
            b.addpoint(object[i].Target_x,object[i].Target_y);
        if(object[i].edge==1)///到达边沿
        {
        	///对轨迹进行进出门判断。
           trackpoint outdir = trackss.getTrackpoint(object[i].id+1);
           cv::Point outhead=outdir.getPoint(1);///得到轨迹首尾点
           cv::Point outtail=outdir.getPoint(outdir.getn());
           //bool count1=true;///用于判断是否计入
           ///看首尾是否在检测的线两边
           DoorCross(outhead,outtail,prameters,in_nums,out_nums,LINENOW);
	cout<<"edge=1: "<<in_nums[0]<<" in,"<<out_nums[0]<<" out"<<endl;
        }
    }

    int x=a.getn();///检测点个数,也是匹配矩阵的行数
    int y=b.getn();///跟踪点个数，列

    dot **cmpmatrix = new dot*[x];//得到一个对应位置点距离的矩阵

    //std::cout<<"\nmatrix:"<<std::endl;
    for(int i=0;i!=x;i++)//行数=检测点数
    {
        cmpmatrix[i] = new dot[y];
        for(int j=0;j!=y;j++)//列数=跟踪点数
        {
            cmpmatrix[i][j].dis=Getdistance(a.getPoint(i+1),b.getPoint(j+1));//得到距离矩阵
            //std::cout<<cmpmatrix[i][j].dis<<" ";
        }
        //std::cout<<std::endl;
    }
    // std::cout<<std::endl;

    std::vector<int> tempp;//存储已使用的跟踪点的序号
    std::vector<int> tempq;//存储已使用的检测点的序号
    //第一次遍历，得到吻合点

    for(int k=0;k!=y;k++)//k为列号,最多有y个最适合的点，y=跟踪点
   {
       double temp=dthreshold;
       int tempnx=-1,tempny=-1;
       for(int i=0;i!=x;i++)///行
       {
           for(int j=0;j!=y;j++)///列
           {
               if(cmpmatrix[i][j].dis<temp&&cmpmatrix[i][j].dotpra==0)
                {
                    temp=cmpmatrix[i][j].dis;
                    tempnx=i;
                    tempny=j;

                }
           }
       }

       //std::cout<<"matrix pra:"<<std::endl;
       for(int i=0;i!=x;i++)
       {
           for(int j=0;j!=y;j++)
           {
               //std::cout<<cmpmatrix[i][j].dotpra<<" ";
           }
           //std::cout<<std::endl;
       }
		if(tempny!=-1&&tempnx!=-1)///存在小于阈值且尚未标定的点
		{
		     for(int i=0;i!=x;i++)
		        cmpmatrix[i][tempny].dotpra=2; ///与最值同行列的标为2
		     for(int j=0;j!=y;j++)
		        cmpmatrix[tempnx][j].dotpra=2;
		    cmpmatrix[tempnx][tempny].dotpra=1;///最值标为1
		    tempp.push_back(tempny);                 ///存储已经使用的跟踪点的序号
		    tempq.push_back(tempnx);                ///存储已经使用的检测点的序号,tempp tempq相同位置的序号的对应的
		    object1[tempnx].id=object[tempny].id;  ///将匹配跟踪点id给检测点
		       //f.addpoint(a.getPoint(tempnx+1));
		}
   }

   for(int i=0;i!=numsNew;i++)///将匹配上的检测点按id加入总的轨迹数组
   {
       if(object1[i].id!=0xffffffffffffffff)
        trackss.addpoint(object1[i].Target_x,object1[i].Target_y,object1[i].id+1);
   }

   ///第二次匹配，处理未匹配的点
   bool tempb=false; 
   for(int i=0;i!=y;i++)   ///未处理的跟踪点
   {
       tempb=false;
       for(int j=0;j!=tempp.size();j++)
       {
           if(i==tempp[j])///跟踪点已经匹配
           {
               tempb=true;
               //f.addpoint(a.getPoint(tempq[j]+1));///匹配点直接放在后面
           }
       }
       if(!tempb)///跟踪点没有匹配
       {
           if(object[i].edge==0) ///没有检测到的edge=0的点直接放object1后面
           {
                object1[numsNew].Target_x=object[i].Target_x;
                object1[numsNew].Target_y=object[i].Target_y;
                object1[numsNew].id=object[i].id;
                object[numsNew].roi=Rect2d(cv::Point(object[i].Target_x-30,object[i].Target_y-30),cv::Point(object[i].Target_x+30,object[i].Target_y+30));
                object1[numsNew].edge=3;
                numsNew++;
		std::cout<<"numsNew increased. is: "<<numsNew<<std::endl;
           }
	else{
           ///对未匹配的轨迹进行进出门判断。include edge=3
           trackpoint dir = trackss.getTrackpoint(object[i].id+1);
           cv::Point head=dir.getPoint(1);///得到轨迹首尾点
           cv::Point tail=dir.getPoint(dir.getn());
           //bool count1=true;///用于判断是否计入
           ///看首尾是否在检测的线两边
           DoorCross(head,tail,prameters,in_nums,out_nums,LINENOW);
	cout<<"edge=3: "<<in_nums[0]<<" in,"<<out_nums[0]<<" out"<<endl;

       }
   }
}
   for(int i=0;i!=x;i++)   ///未处理的检测点
    {
        tempb=false;
        for(int j=0;j!=tempq.size();j++)
        {
            if(i==tempq[j])
                tempb=true;
        }

        if(!tempb)//若检测点前面没有取到
        {
            //f.addpoint(a.getPoint(i+1).x,a.getPoint(i+1).y);
            object1[i].id=idgo++;           ///给新检测的点分配id

            ///std::cout<<"Object"<<i<<" 's id:"<<object1[i].id<<std::endl;
            trackpoint trackpointtemp;
            trackpointtemp.addpoint(object1[i].Target_x,object1[i].Target_y);
            trackpointtemp.id=object1[i].id;
            trackss.addtrack(trackpointtemp);

           /* std::///cout<<"3th trackpoint:";
            for(int i=0;i!=trackpointtemp.getn();i++)
                std::///cout<<trackpointtemp.getPoint(i+1).x<<","<<trackpointtemp.getPoint(i+1).y;
            std::///cout<<std::endl;*/
        }
    }
	/*std::cout<<"最终匹配结果："<<std::endl;
	for(int i=0;i!=numsNew;i++)
		std::cout<<"Object"<<i<<" 's id:"<<object1[i].id<<std::endl;*/
    for(int i=0;i!=x;i++)
        delete[] cmpmatrix[i];
    delete[] cmpmatrix;
    return 1;
}

void comparision::DoorCross(cv::Point &head,cv::Point &tail,float parameters[][6],unsigned int *in_nums,unsigned int *out_nums,int LINENOW)
{
  bool count1=true;///用于判断是否计入
   ///看首尾是否在检测的线两边
   for(int i=0;i!=LINENOW;i++)
   {
       //float parameters[i][0]=prameters[0],parameters[i][1]=prameters[1],parameters[i][2]=prameters[2],parameters[i][3]=prameters[3],parameters[i][4]=prameters[4],parameters[i][5]=prameters[5];
       if(parameters[i][0]==parameters[i][2])///检测线（门）为纵贯线
       {
           if(head.x==tail.x)///轨迹为纵贯线不行
            count1=false;
           else ///轨迹为其他，必须两端在检测线两边
           {
               if((head.x-parameters[i][0])*(tail.x-parameters[i][0])>=-10)///流出余量，两个点离门太进的不计入
                count1=false;
           }
       }
       else if(parameters[i][1]==parameters[i][3])///检测线为横线
       {
           if(head.y==tail.y)
            count1=false;
           else
           {
               if((head.y-parameters[i][1])*(tail.y-parameters[i][1])>=-10)
                count1=false;
           }
       }
       else///检测线为一般
       {
           float kk1=(parameters[i][3]-parameters[i][1])/(parameters[i][2]-parameters[i][0]); ///k1
           float bb1=parameters[i][1]-kk1*parameters[i][0];  ///b1
           float xx=0,yy=0;///交点坐标
           ///通过求出直线交点位置是否在轨迹首尾相连的线段上判断
           if(head.x==tail.x)///轨迹为纵贯线
           {
                yy=kk1*head.x+bb1;
                if((head.y-yy)*(tail.y-yy)>=0)///线段两端点不在检测线两侧
                    count1=false;
           }
           else if(head.y==tail.y)///轨迹为横线
           {
                xx=(head.y-bb1)/kk1;
                if((head.x-xx)*(tail.x-xx)>=-10)
                    count1=false;
           }
           else///一般情况
           {
                float kk2=(head.y-tail.y)/(head.x-tail.x);
                float bb2=head.y-kk2*head.x;
                xx=(bb2-bb1)/(kk1-kk2);
                if((head.x-xx)*(tail.x-xx)>=-10)///只需要验证x坐标
                    count1=false;
           }
       }
       if(count1)
       {
           float directx=tail.x-head.x;
           float directy=tail.y-head.y;
           if(directx*parameters[i][4]+directy*parameters[i][5]>0)
            in_nums[i]++;
           else if(directx*parameters[i][4]+directy*parameters[i][5]<0)
            out_nums[i]++;
           else{;}
       }
   }
}

