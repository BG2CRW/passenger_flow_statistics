#ifndef MATQUEUE_H
#define MATQUEUE_H
#include "opencv/cv.h"
#include "opencv2/core.hpp"
#include "iostream"
#include "titlefiles.h"
struct Node;
struct Node
{
    cv::Mat img;
    Node* pre;
    Node* post;
};
class matqueue
{
    public:
        matqueue();
        matqueue(int height,int width,int channel=3):H(height),W(width),C(channel)
        {
            //this->head=new Node;
            //this->rear=new Node;
            queuesize=0;
        }
        virtual ~matqueue()
        {
            ;
        }
        //getNext();
        int push(cv::Mat& pic);
        int pop(cv::Mat &pic);
        int getSize(){return queuesize;}
        int queueclear();
    protected:
    private:
        int H,W,C; //图片的高和宽
        Node* head;
        Node* rear;
        int queuesize;
};

#endif // MATQUEUE_H
