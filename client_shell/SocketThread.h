#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H
#include <QThread>
#include <iostream>
#include <cstring>
#include <string>
#include "SocketMatTransmissionServer.h"
#include <QTimer>
#include <QString>
#include <QApplication>
#include "typechange.h"
#include <QImage>
#include "xml.h"

using namespace::std;

class SocketThread : public QThread
{
    Q_OBJECT
public:
    SocketThread();
    void setCam(int camNumber);
    void setPort(int port);
    void stoped();
    void updateImage();
    cv::Mat img;
    TypeChange TYPE;
    int cameraNumber;
    int clientPORT;
    unsigned int in_num[5];
    unsigned int out_num[5];
    int lineNum;
    SocketMatTransmissionServer socketMat;
    void connectSocket(int port);
    void disconnectSocket();
signals:
    void UpdateSignal(QImage,int ,int );
protected:
    void run();

private:
    volatile bool stopped;


};

#endif // SOCKETTHREAD_H
