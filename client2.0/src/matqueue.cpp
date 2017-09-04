#include "matqueue.h"
#include "titlefiles.h"
matqueue::matqueue()
{
    //ctor
}

int matqueue::queueclear()
{
    cv::Mat pic;
    for(int i=0;i!=queuesize;i++)
    {
        this->pop(pic);
    }
    queuesize=0;
    return 0;
}

int matqueue::push(cv::Mat& pic)
{
    if(pic.rows!=H||pic.cols!=W||pic.channels()!=C) ///input must be of request size & demension
    {
        std::cout<<"push picture's size is illegal."<<std::endl;
        return -1;
    }

    Node* pushnode = new Node;
    if(C==3)
        pushnode->img.create(H,W,CV_8UC3); ///必须先为Node申请足够大的空间
    else if(C==1)
    {
        pushnode->img.create(H,W,CV_8UC1);
    }
    else{;}
    ///size=0
    if(this->queuesize==0)
    {
	this->head=new Node;
        this->rear;
        pic.copyTo(this->head->img);
        this->rear=this->head;
    }
    else
    {
        pic.copyTo(pushnode->img);
        pushnode->post = this->head;
        this->head->pre=pushnode;
        this->head=pushnode;
    }
    queuesize++;
    return 0;
}
int matqueue::pop(cv::Mat& pic)
{
    ///size=0
    if(this->queuesize==0)///头为空
    {
        std::cout<<"queue is empty, pop failed."<<std::endl;
        return -1;
    }
    Node* popnode;
    popnode=this->rear;
    this->rear->img.copyTo(pic);
if(pic.rows!=H||pic.cols!=W||pic.channels()!=C)
{
	std::cout<<"pop ERROR"<<std::endl;
	return -1;
}
    this->rear = this->rear->pre;
    if(queuesize>1)
        this->rear->post = NULL;
    delete popnode;
    queuesize--;
    return 0;
}
