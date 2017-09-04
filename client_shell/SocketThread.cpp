#include <QDebug>
#include "mainwindow.h"
#include "SocketThread.h"

extern Camera_config camera_conf[3];

XmlContainer configxml;
SocketThread::SocketThread()
{
    stopped = false;
}

void SocketThread::run()
{
    configxml.readXml(camera_conf);
    while(!stopped)
    {

        qDebug()<<clientPORT;
        connectSocket(clientPORT);
        qDebug()<<stopped;
        while(!stopped)
        {
            updateImage();
            usleep(10000);
        }
    }

    qDebug("socketthread1");
    disconnectSocket();
    stopped = false;

}

void SocketThread::stoped()
{
    disconnectSocket();
    stopped = true;
    qDebug("socketthread");
}

void SocketThread::setCam(int camNumber)
{
    cameraNumber=camNumber;
}

void SocketThread::setPort(int port)
{
    clientPORT=port;
}

void SocketThread::updateImage()
{
    int order1=-1;
    lineNum=0;
    socketMat.receive(img,in_num,out_num,lineNum,order1);
    if(order1!=-1)
    {
        order1=-1;
        camera_conf[cameraNumber].order=-1;
    }


    if(img.data)
    {
        cvtColor(img, img, CV_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR
        QImage image = QImage((uchar*)(img.data), img.cols, img.rows, QImage::Format_RGB888);

        emit UpdateSignal(image,in_num[0],out_num[0]);
    }
    if(camera_conf[cameraNumber].order!=-1)
    qDebug()<<camera_conf[cameraNumber].order;
    socketMat.sender(camera_conf[cameraNumber].sense,camera_conf[cameraNumber].hour,camera_conf[cameraNumber].min,camera_conf[cameraNumber].x,
    camera_conf[cameraNumber].dx,TYPE.stringToChar(camera_conf[cameraNumber].IPCamera,13),TYPE.stringToChar(camera_conf[cameraNumber].admin,10),TYPE.stringToChar(camera_conf[cameraNumber].code,20),camera_conf[cameraNumber].PortCamera,camera_conf[cameraNumber].order);

}

void SocketThread::connectSocket(int port)
{
    if (socketMat.socketConnect(port) < 0)
    {
        QMessageBox::warning(NULL, "Warning", "相机未连接，\n请检查端口号后重连", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
    }
}

void SocketThread::disconnectSocket()
{
    socketMat.sender(camera_conf[cameraNumber].sense,camera_conf[cameraNumber].hour,camera_conf[cameraNumber].min,camera_conf[cameraNumber].x,
    camera_conf[cameraNumber].dx,TYPE.stringToChar(camera_conf[cameraNumber].IPCamera,13),TYPE.stringToChar(camera_conf[cameraNumber].admin,10),TYPE.stringToChar(camera_conf[cameraNumber].code,20),camera_conf[cameraNumber].PortCamera,0);
    socketMat.socketDisconnect();
}
