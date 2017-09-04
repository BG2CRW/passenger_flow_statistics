#include "thread.h"
#include <QDebug>
#include "mainwindow.h"
Thread::Thread()
{
    stopped = false;
}

void Thread::run()
{
    while(!stopped)
    {
        doCMD();
        //while(!stopped);
        while(1);
    }
    stopped = false;

}

void Thread::stoped()
{
    stopped = true;
    qDebug("thread");
}

void Thread::setCMD(string message)
{
    messageStr = message;
}

void Thread::doCMD()
{
    system(TYPE.stringToChar(messageStr,sizeof(messageStr)));
}

