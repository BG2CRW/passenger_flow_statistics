
#ifndef TRACKPOINT_H
#define TRACKPOINT_H

#include"titlefiles.h"
#include <opencv/cv.h>
#include <opencv2/tracking.hpp>

using namespace std;
using namespace cv;

class trackpoint//////////储存每条路径上的点
{             //也涌来表示每图上各个点的数组
    public:
        trackpoint();
        virtual ~trackpoint();
        void addpoint(int x,int y);//轨迹上添加一个点
        void addpoint(cv::Point p);
        cv::Point getPoint(int i);//得到轨迹上第n个点
        int getn(){return n;}//返回轨迹上的点数
        bool isEmpty()
        {
            bool x=false;
            if(n==0)
                x=true;
            return x;
        }
        void trackpointclear()
        {
            vector<cv::Point> (points).swap(points);
        }
        unsigned int id;
    private:
        int n;

        std::vector<cv::Point> points;//记录一条轨迹上的点


};
class trackset//////////储存所有萃轨迹
{
    public:
        trackset();
        virtual ~trackset();
        void addtrack(trackpoint track);//添加第tracknum条轨迹（tracknum从1开始）
        void deletetrack(int tracknum);//删除第tracknum条轨迹（tracknum从0开始）
        int Getn() {return n;}     //得到轨迹数
        int getn(int i) {return tracks[i-1].getn();}    //得到第i条轨迹的点数,i从1开始
        trackpoint getTrackpoint(int i){return tracks[i-1];}        //得到第n条轨迹的trckpoint，n从1开始

        void addpoint(int x,int y,int i);//在第i条轨迹上加点
        void drawLine(int n,cv::Mat image);//画出第i条轨迹，（从1开始）
        void tracksetclear()
        {//vector<string>(v).swap(v);
	    std::vector<trackpoint> tracks1;
            tracks.swap(tracks1);
            headtracks=tracks.begin();
            tailtracks=tracks.end();
	    n=tracks.size();
        }
        bool isEmpty()
        {
            bool x=false;
            if(tracks.size()==0)
                x=true;
            return x;
        }
    private:
        std::vector<trackpoint> tracks;//轨迹的数组
        std::vector<trackpoint>::iterator headtracks;
        std::vector<trackpoint>::iterator tailtracks;
        int n;//轨迹条数
};


class Object
{
    public:
        Object()
        {
            id=0xffffffffffffffff;
            Target_x=0;
            Target_y=0;
                edge=0;
        }
        virtual ~Object() {}
    unsigned long int id;
    int edge;  ///为0表示跟踪正常，为1表示到达画面边缘，目标留在原地,2表示目标跟踪丢失，3表示没有被检测出来
    Ptr<Tracker> tracker;
    Rect2d roi;
    int Target_x;  ///每个框的中心点
    int Target_y;  ///每个框的中心点


    protected:
    private:
};


#endif // TRACKPOINT_H
