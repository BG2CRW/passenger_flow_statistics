#include"titlefiles.h"
trackpoint::trackpoint()
{
    id=0;
    n=0;
}
trackpoint::~trackpoint()
{
}

void trackpoint::addpoint(int x,int y)//添加点
{

    cv::Point point(x,y);
    points.push_back(point);
    n=points.size();
}
void trackpoint::addpoint(cv::Point p)
{
    points.push_back(p);
    n=points.size();
}

cv::Point trackpoint::getPoint(int i)//得到轨迹上第n个点
{
    cv::Point ptemp;
    if(i<=0)
    {
        std::cout<<"wrong input of point number."<<std::endl;
        ptemp.x=0;
        ptemp.y=0;  //如果错误，就报错，并返回（0,0）
    }

    else
        ptemp=this->points[i-1];
    return ptemp;
}


////////////////trackset
trackset::trackset()
{
    n=0;
    headtracks=tracks.begin();
    tailtracks=tracks.end();
}
trackset::~trackset()
{
}
void trackset::addtrack(trackpoint track)//添加轨迹
{
    tracks.push_back(track);
    tailtracks=tracks.end();
    n=tracks.size();
}
void trackset::deletetrack(int tracknum)//删除轨迹
{
    if(tracknum<=0||tracknum>n||headtracks==tailtracks)
        return;
    std::vector<trackpoint>::iterator temp=tracks.begin();
    for(int i=0;i!=tracknum;i++)
        temp++;
    tracks.erase(temp-1);
    headtracks=tracks.begin();
    tailtracks=tracks.end();
    n=tracks.size();
}

void trackset::addpoint(int x,int y,int i)
{
    if(i<=0||i>n||headtracks==tailtracks)
        return;
    //cv::Point pointtemp=cv::Point(x,y);
    trackpoint tracktemp=this->tracks[i-1];
    tracktemp.addpoint(x,y);
    this->tracks[i-1]=tracktemp;
    n=tracks.size();
}

 void trackset::drawLine(int i,cv::Mat image)//画出第i条轨迹
 {
    if(i<=0||i>n||headtracks==tailtracks)
        return;
    cv::Point a,b;
    trackpoint tracktemp=this->tracks[i-1];
    if(tracktemp.getn()<2)
    {
        cout<<"点数太少，不能画线"<<i<<endl;
             return;//少于两个点不画图;

    }

    for(int j=0;j!=tracktemp.getn()-1;j++)
    {
        a=tracktemp.getPoint(j+1);b=tracktemp.getPoint(j+2);
        line(image,a,b,cv::Scalar(0,0,255));//画红线
    }
 }
