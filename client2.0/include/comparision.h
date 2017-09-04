#ifndef COMPARISION_H
#define COMPARISION_H

#include"titlefiles.h"

class comparision
{
    public:
        comparision();
        virtual ~comparision();
        //comparision& operator=(comparision& com);
        double Getdistance(cv::Point p1,cv::Point p2);//得到的距离为绝对值的和
        int change_id(Object *object1,Object *object,int& numsNew,int& numsOld,trackset &trackss,unsigned int &idgo,float prameters[][6],unsigned int *in_nums,unsigned int *out_nums,int LINENOW); //object1为检测值
        //void AddToTrackset(trackset &tracks);
        trackpoint Getf(){return f;}
        void setThreshold(double th)
        {
            dthreshold=th;
            return;
        }
        void DoorCross(cv::Point &head,cv::Point &tail,float parameters[][6],unsigned int *in_nums,unsigned int *out_nums,int LINENOW);
    protected:
    private:
        trackpoint f;///最后一版实际没有起作用，当作一个过渡变量使用，以后版本优化可去掉
        double dthreshold;///距离阈值
};
class dot//用来构成距离矩阵
{
public:
    dot(){dis=0.0;dotpra=0;}
    virtual ~dot(){}
    double dis;//距离
    int dotpra;//当这个值: 0 未处理 1 被采纳 2 消去
protected:
private:

};
#endif // COMPARISION_H
