#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <iostream>
#include <cstring>
#include <string>
#include "typechange.h"

using namespace::std;
class Thread : public QThread
{
    Q_OBJECT
public:
    Thread();
    void setCMD(string message);
    void stoped();
    TypeChange TYPE;
protected:
    void run();
    void doCMD();

private:
    string messageStr;
    volatile bool stopped;
};
#endif // THREAD_H
