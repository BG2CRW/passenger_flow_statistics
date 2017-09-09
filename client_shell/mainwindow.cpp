#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SocketMatTransmissionClient.h"
#include "SocketMatTransmissionServer.h"
#include <QDebug>
using namespace cv;

unsigned int in_num0[5];
unsigned int out_num0[5];
unsigned int in_num1[5];
unsigned int out_num1[5];
unsigned int in_num2[5];
unsigned int out_num2[5];
int num[6]={0};
int old_num[6]={0};
int lineNum=0;
int PORT=6000;
Camera_config camera_conf[3];
XmlContainer configXml;
string logName;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    //设置显示视频用的Label
    imageLabel0 = new QLabel(this);
    imageLabel1 = new QLabel(this);
    imageLabel2 = new QLabel(this);

    configXml.readXml(camera_conf);
    drawChartInit();
    connect(&timer,SIGNAL(timeout()),this,SLOT(writeLOG()));
    timer.start(1800000);//60000/min
    drawChart(num);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::drawChartInit()
{
    ui->qCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);

    ui->qCustomPlot->addGraph(); // blue line
    ui->qCustomPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->qCustomPlot->addGraph(); // red line
    ui->qCustomPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m");
    ui->qCustomPlot->xAxis->setTicker(timeTicker);
    ui->qCustomPlot->axisRect()->setupFullAxesBox();
    ui->qCustomPlot->yAxis->setRange(0, 10);
    //ui->qCustomPlot->yAxis->setTickStep(1);
    //ui->qCustomPlot->yAxis->setAutoTickStep(false);//设置轴刻度的一跳为1
    //ui->qCustomPlot->yAxis->setSubTickLength(0);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->qCustomPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->qCustomPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->qCustomPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->qCustomPlot->yAxis2, SLOT(setRange(QCPRange)));


    ui->qCustomPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);

    ui->qCustomPlot_2->addGraph(); // blue line
    ui->qCustomPlot_2->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->qCustomPlot_2->addGraph(); // red line
    ui->qCustomPlot_2->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    ui->qCustomPlot_2->xAxis->setTicker(timeTicker);
    ui->qCustomPlot_2->axisRect()->setupFullAxesBox();
    ui->qCustomPlot_2->yAxis->setRange(0, 10);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->qCustomPlot_2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->qCustomPlot_2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->qCustomPlot_2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->qCustomPlot_2->yAxis2, SLOT(setRange(QCPRange)));

    ui->qCustomPlot_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);

    ui->qCustomPlot_3->addGraph(); // blue line
    ui->qCustomPlot_3->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->qCustomPlot_3->addGraph(); // red line
    ui->qCustomPlot_3->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    ui->qCustomPlot_3->xAxis->setTicker(timeTicker);
    ui->qCustomPlot_3->axisRect()->setupFullAxesBox();
    ui->qCustomPlot_3->yAxis->setRange(0, 10);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->qCustomPlot_3->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->qCustomPlot_3->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->qCustomPlot_3->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->qCustomPlot_3->yAxis2, SLOT(setRange(QCPRange)));
}

void MainWindow::createBash(int i,int port)
{
    QTime time(QTime::currentTime());
    FILE *fp;
    string name="client_shell"+type.itos(i)+".sh";
    fp = fopen(name.c_str(),"w");
    fprintf(fp,"%s","#!bin/bash\n");
    fprintf(fp,"%s","#client_shell.sh\n");
    fprintf(fp,"%s","sleep 1\n");
    fprintf(fp,"%s","export LD_LIBRARY_PATH=\"/home/higo/client2.0/HCNetSDKCom\"\n");
        //fprintf(fp,"script -a record.txt\n");
    string path="cd "+camera_conf[i].corePath+"\n";
    fprintf(fp,"%s",path.c_str());
    //fprintf(fp,"ls\n");
    string cmd="./client "+camera_conf[i].IPCamera+" "+type.itos(camera_conf[i].PortCamera)+" "+camera_conf[i].admin+" "+camera_conf[i].code+" "+camera_conf[i].IPCore+" "+type.itos(port)+" "+camera_conf[i].SavePicPath+" "+camera_conf[i].SavePicPrefix+"\n";
    fprintf(fp,"%s",cmd.c_str());
    //fprintf(fp,"exit\n");
    fprintf(fp,"%s","#sleep 10\n");

    fclose(fp);
}


void MainWindow::drawChart(int *NUM)
{
        QTime time(QTime::currentTime());
        double key=(time.hour()*3600.0+time.minute()*60.0+time.second())/1.0;
        // add data to lines:
        ui->qCustomPlot->graph(0)->addData(key, NUM[0]);
        ui->qCustomPlot->graph(1)->addData(key, NUM[1]);
        // rescale value (vertical) axis to fit the current data:
        ui->qCustomPlot->graph(0)->rescaleValueAxis();
        ui->qCustomPlot->graph(1)->rescaleValueAxis(true);

        ui->qCustomPlot->xAxis->setRange(key, 18000, Qt::AlignRight);//five hours/page
        ui->qCustomPlot->replot();

        ui->qCustomPlot_2->graph(0)->addData(key, NUM[2]);
        ui->qCustomPlot_2->graph(1)->addData(key, NUM[3]);
        // rescale value (vertical) axis to fit the current data:
        ui->qCustomPlot_2->graph(0)->rescaleValueAxis();
        ui->qCustomPlot_2->graph(1)->rescaleValueAxis(true);

        ui->qCustomPlot_2->xAxis->setRange(key, 18000, Qt::AlignRight);
        ui->qCustomPlot_2->replot();


        ui->qCustomPlot_3->graph(0)->addData(key, NUM[4]);
        ui->qCustomPlot_3->graph(1)->addData(key, NUM[5]);
        // rescale value (vertical) axis to fit the current data:
        ui->qCustomPlot_3->graph(0)->rescaleValueAxis();
        ui->qCustomPlot_3->graph(1)->rescaleValueAxis(true);

        ui->qCustomPlot_3->xAxis->setRange(key, 18000, Qt::AlignRight);
        ui->qCustomPlot_3->replot();
}

void MainWindow::writeLOG()
{
    int dNum[6];
    num[0]=(int)ui->lineEdit->text().toFloat();
    num[1]=(int)ui->lineEdit_2->text().toFloat();
    num[2]=(int)ui->lineEdit_3->text().toFloat();
    num[3]=(int)ui->lineEdit_4->text().toFloat();
    num[4]=(int)ui->lineEdit_5->text().toFloat();
    num[5]=(int)ui->lineEdit_6->text().toFloat();
    for(int i=0;i<6;i++)
    {
        dNum[i]=num[i]-old_num[i];
        old_num[i]=num[i];
    }
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式
    QString str1 = time.toString("yyyy-MM-dd"); //设置显示格式
    logName="report"+str1.toStdString()  +".log";
    QByteArray ba = str.toLatin1();
    FILE *fp;
    fp=fopen(logName.c_str(),"a+");
    fprintf(fp,"%s\t%d\t%d\t%d\t%d\t%d\t%d\t\n",  ba.data(),dNum[0],dNum[1],dNum[2],dNum[3],dNum[4],dNum[5]);
    fclose(fp);

    drawChart(dNum);

}

void MainWindow::UpdateSlot0(QImage img,int num0,int num1)
{
    image0=img;

    QString str1 = QString::number(num0);
    QString str2 = QString::number(num1);
    ui->lineEdit->setText(str1);
    ui->lineEdit_2->setText(str2);

    imageLabel0->setPixmap(QPixmap::fromImage(image0));
    imageLabel0->resize(image0.size());
    imageLabel0->show();

}

void MainWindow::UpdateSlot1(QImage img,int num0,int num1)
{
    image1=img;

    QString str1 = QString::number(num0);
    QString str2 = QString::number(num1);
    ui->lineEdit_3->setText(str1);
    ui->lineEdit_4->setText(str2);

    imageLabel1->setPixmap(QPixmap::fromImage(image1));
    imageLabel1->resize(image0.size());
    imageLabel1->show();

}

void MainWindow::UpdateSlot2(QImage img,int num0,int num1)
{
    image2=img;

    QString str1 = QString::number(num0);
    QString str2 = QString::number(num1);
    ui->lineEdit_5->setText(str1);
    ui->lineEdit_6->setText(str2);

    imageLabel2->setPixmap(QPixmap::fromImage(image2));
    imageLabel2->resize(image2.size());
    imageLabel2->show();

}

void MainWindow::on_pushButton_clicked()//camera0 EXIT
{
    threadA.stoped();
    socketthreadA.stoped();
    threadB.stoped();
    socketthreadB.stoped();
    threadC.stoped();
    socketthreadC.stoped();
    close();
}

void MainWindow::on_pushButton_8_clicked()
{
    threadA.stoped();
    socketthreadA.stoped();
    threadB.stoped();
    socketthreadB.stoped();
    threadC.stoped();
    socketthreadC.stoped();
     close();
}

void MainWindow::on_pushButton_9_clicked()
{
    threadA.stoped();
    socketthreadA.stoped();
    threadB.stoped();
    socketthreadB.stoped();
    threadC.stoped();
    socketthreadC.stoped();
    close();
}

void MainWindow::on_pushButton_10_clicked()
{
    threadA.stoped();
    socketthreadA.stoped();
    threadB.stoped();
    socketthreadB.stoped();
    threadC.stoped();
    socketthreadC.stoped();
    close();
}

void MainWindow::on_pushButton_11_clicked()
{
    config0.show();
}

void MainWindow::on_pushButton_12_clicked()
{
    config1.show();
}

void MainWindow::on_pushButton_13_clicked()
{
    config2.show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    threadA.stoped();
    threadA.wait();
    socketthreadA.stoped();
    socketthreadA.wait();
    threadB.stoped();
    threadB.wait();
    socketthreadB.stoped();
    socketthreadB.wait();
    threadC.stoped();
    threadC.wait();
    socketthreadC.stoped();
    socketthreadC.wait();
    event->accept();
}


void MainWindow::close()
{
    exit(0);
}
void MainWindow::on_pushButton_2_clicked()//open_camera0
{
    threadA.setCMD("gnome-terminal -x bash -c \"sh client_shell0.sh\"");
    socketthreadA.setCam(0);
    socketthreadA.setPort(PORT);
    createBash(0,PORT);
    PORT++;
    if(!threadA.isRunning())
    {
        threadA.start();
    }
    if(!socketthreadA.isRunning())
    {
        socketthreadA.start();
    }
    connect(&socketthreadA, SIGNAL(UpdateSignal(QImage,int,int)),  this, SLOT(UpdateSlot0(QImage,int,int)));

    ui->verticalLayout->addWidget(imageLabel0);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(true);

}

void MainWindow::on_pushButton_6_clicked()//open camera1
{
    threadB.setCMD("gnome-terminal -x bash -c \"sh client_shell1.sh\"");
    socketthreadB.setCam(1);
    socketthreadB.setPort(PORT);
    createBash(1,PORT);
    PORT++;
    if(!threadB.isRunning())
    {
        threadB.start();
    }

    if(!socketthreadB.isRunning())
    {
        socketthreadB.start();
    }

    connect(&socketthreadB, SIGNAL(UpdateSignal(QImage,int,int)),  this, SLOT(UpdateSlot1(QImage,int,int)));

    ui->verticalLayout_2->addWidget(imageLabel1);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(true);
}

void MainWindow::on_pushButton_4_clicked()//open camera2
{
    threadC.setCMD("gnome-terminal -x bash -c \"sh client_shell2.sh\"");
    socketthreadC.setCam(2);
    socketthreadC.setPort(PORT);
    createBash(2,PORT);
    PORT++;
    if(!threadC.isRunning())
    {
        threadC.start();
    }
    if(!socketthreadC.isRunning())
    {
        socketthreadC.start();
    }
    connect(&socketthreadC, SIGNAL(UpdateSignal(QImage,int,int)),  this, SLOT(UpdateSlot2(QImage,int,int)));

    ui->verticalLayout_3->addWidget(imageLabel2);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(true);
}

void MainWindow::on_pushButton_3_clicked()//close_camera0
{
    socketthreadA.stoped();
    threadA.stoped();
    //socketthreadA.wait();
    //threadA.wait();
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
}


void MainWindow::on_pushButton_7_clicked()//close camera1
{
    socketthreadB.stoped();
    threadB.stoped();
    //threadB.wait();
    //socketthreadB.wait();

    ui->pushButton_7->setEnabled(false);
    ui->pushButton_6->setEnabled(true);
}

void MainWindow::on_pushButton_5_clicked()//close camera2
{
    socketthreadC.stoped();
    threadC.stoped();


    //threadC.wait();
    //socketthreadC.wait();

    ui->pushButton_5->setEnabled(false);
    ui->pushButton_4->setEnabled(true);
}

void MainWindow::on_pushButton_14_clicked()
{
    Thread *openGedit=new Thread;//gnome-terminal -x bash -c "gedit report.log"
    string gedit_cmd="gnome-terminal -x bash -c \"gedit "+logName+"\"";
    openGedit->setCMD(gedit_cmd.c_str());
    if(!openGedit->isRunning())
    {
        openGedit->start();
    }
}
