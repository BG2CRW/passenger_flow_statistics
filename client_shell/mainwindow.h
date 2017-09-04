#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QCloseEvent>
#include <QMainWindow>
#include "SocketMatTransmissionClient.h"
#include "SocketMatTransmissionServer.h"
#include "opencv2/opencv.hpp"
#include <QtWidgets/QMainWindow>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <qfile.h>
#include <qtextstream.h>
#include <qdebug.h>
#include <opencv.hpp>
#include <string>
#include <iostream>
#include "config0.h"
#include "config1.h"
#include "config2.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "SocketThread.h"
#include "thread.h"
#include <string>
#include <cstring>
#include "typechange.h"
#include "xml.h"
#include "qcustomplot.h"

using namespace std;

namespace Ui {
class MainWindow;
}




class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void UpdateSlot0(QImage,int ,int);
    void UpdateSlot1(QImage,int ,int);
    void UpdateSlot2(QImage,int ,int);
    void writeLOG();
public:
    Camera_config camera_conf[3];
    QImage image0;
    QImage image1;
    QImage image2;
    QTimer timer;
    TypeChange type;
    void drawChart(int * NUM);
    void drawChartInit();
    void createBash(int i,int port);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void close();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_14_clicked();

private:
    Ui::MainWindow *ui;
    QTimer dataTimer;

    QLabel *imageLabel0;
    QLabel *imageLabel1;
    QLabel *imageLabel2;
    Config0 config0;
    Config1 config1;
    Config2 config2;
    SocketThread socketthreadA;
    SocketThread socketthreadB;
    SocketThread socketthreadC;
    Thread threadA;
    Thread threadB;
    Thread threadC;


protected:
    void closeEvent(QCloseEvent *event);

};



#endif // MAINWINDOW_H
