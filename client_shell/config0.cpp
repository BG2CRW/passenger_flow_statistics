#include "config0.h"
#include "ui_config0.h"
#include "mainwindow.h"
#include "xml.h"
extern Camera_config camera_conf[3];

XmlContainer configXml0;

int flag00=0;//开关  0：关闭程序    1：改状态
int flag01=0;//存图  0：不存     1：存
int flag02=0;//数据清零  0：不清零   1：清零
int flag03=0;//改线  0：不改线   1：改线

float old_x0[20],old_dx0[20];
Config0::Config0(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config0)
{
    ui->setupUi(this);
    dispData();
}

Config0::~Config0()
{
    delete ui;
}

void Config0::on_pushButton_2_clicked()
{
    close();
}

void Config0::dispData()
{
    configXml0.readXml(camera_conf);
    ui->lineEdit_17->setText(QString::fromStdString(camera_conf[0].corePath));
    ui->lineEdit_15->setText(QString::fromStdString(camera_conf[0].admin));
    ui->lineEdit_14->setText(QString::fromStdString(camera_conf[0].code));
    ui->lineEdit_18->setText(QString::fromStdString(camera_conf[0].IPCore));
    ui->lineEdit_12->setText(QString::fromStdString(camera_conf[0].IPCamera));
    ui->lineEdit_19->setText(QString::fromStdString(camera_conf[0].SavePicPrefix));
    ui->lineEdit_20->setText(QString::fromStdString(camera_conf[0].SavePicPath));
    ui->lineEdit_13->setText(QString::number(camera_conf[0].PortCamera,10));
    ui->lineEdit_16->setText(QString::number(camera_conf[0].sense,10));
    ui->lineEdit_10->setText(QString::number(camera_conf[0].hour,10));
    ui->lineEdit_11->setText(QString::number(camera_conf[0].min,10));
    ui->lineEdit->setText(QString("%1").arg(camera_conf[0].x[0]));
    ui->lineEdit_2->setText(QString("%1").arg(camera_conf[0].x[1]));
    ui->lineEdit_3->setText(QString("%1").arg(camera_conf[0].x[2]));
    ui->lineEdit_4->setText(QString("%1").arg(camera_conf[0].x[3]));
    ui->lineEdit_5->setText(QString("%1").arg(camera_conf[0].dx[0]));
    ui->lineEdit_6->setText(QString("%1").arg(camera_conf[0].dx[1]));
    ui->lineEdit_7->setText(QString("%1").arg(camera_conf[0].dx[2]));
    ui->lineEdit_8->setText(QString("%1").arg(camera_conf[0].dx[3]));

    ui->checkBox->setChecked((bool)camera_conf[0].SavePicFlag);

    if(ui->checkBox->checkState()==1)
    {
            ui->lineEdit_19->setEnabled(true);
            ui->lineEdit_20->setEnabled(true);
    }
    if(ui->checkBox->checkState()==0)
    {
            ui->lineEdit_19->setEnabled(false);
            ui->lineEdit_20->setEnabled(false);
    }

}

void Config0::saveData()
{
    flag00=1;

    for(int i=0;i<20;i++)
    {
        old_x0[i]=camera_conf[0].x[i];
        old_dx0[i]=camera_conf[0].dx[i];
    }

    QString strText = ui->lineEdit->text();
    camera_conf[0].x[0]=strText.toFloat();

    strText = ui->lineEdit_2->text();
    camera_conf[0].x[1]=strText.toFloat();

    strText = ui->lineEdit_3->text();
    camera_conf[0].x[2]=strText.toFloat();
    strText = ui->lineEdit_4->text();
    camera_conf[0].x[3]=strText.toFloat();

    strText = ui->lineEdit_5->text();
    camera_conf[0].dx[0]=strText.toFloat();
    strText = ui->lineEdit_6->text();
    camera_conf[0].dx[1]=strText.toFloat();

    strText = ui->lineEdit_7->text();
    camera_conf[0].dx[2]=strText.toFloat();
    strText = ui->lineEdit_8->text();
    camera_conf[0].dx[3]=strText.toFloat();

    strText = ui->lineEdit_10->text();
    camera_conf[0].hour=(int)strText.toFloat();
    strText = ui->lineEdit_11->text();
    camera_conf[0].min=(int)strText.toFloat();

    strText = ui->lineEdit_16->text();
    camera_conf[0].sense=(int)strText.toFloat();

    strText = ui->lineEdit_12->text();
    camera_conf[0].IPCamera=strText.toStdString();

    strText = ui->lineEdit_13->text();
    camera_conf[0].PortCamera=(int)strText.toFloat();

    strText = ui->lineEdit_14->text();
    camera_conf[0].code=strText.toStdString();

    strText = ui->lineEdit_15->text();
    camera_conf[0].admin=strText.toStdString();

    strText = ui->lineEdit_17->text();
    camera_conf[0].corePath=strText.toStdString();

    strText = ui->lineEdit_18->text();
    camera_conf[0].IPCore=strText.toStdString();

    strText = ui->lineEdit_19->text();
    camera_conf[0].SavePicPrefix=strText.toStdString();

    strText = ui->lineEdit_20->text();
    camera_conf[0].SavePicPath=strText.toStdString();

    camera_conf[0].SavePicFlag=ui->checkBox->isChecked();

    if((camera_conf[0].x[0]!=old_x0[0])||(camera_conf[0].x[1]!=old_x0[1])||(camera_conf[0].x[2]!=old_x0[2])||(camera_conf[0].x[3]!=old_x0[3])||(camera_conf[0].dx[0]!=old_dx0[0])||(camera_conf[0].dx[1]!=old_dx0[1])||(camera_conf[0].dx[2]!=old_dx0[2])||(camera_conf[0].dx[3]!=old_dx0[3]))
    {
        flag02=1;
        flag03=1;
    }
    else
    {
        flag02=0;
        flag03=0;
    }
    if(ui->checkBox->isChecked()==1)
    {
        flag01=1;
    }
    if(ui->checkBox->isChecked()==0)
    {
        flag01=0;
    }
    camera_conf[0].order=flag03*8+flag02*4+flag01*2+flag00;
    configXml0.writeXml(camera_conf);
}

void Config0::on_pushButton_clicked()
{
    saveData();
    //qDebug()<<flag03<<flag02<<flag01<<flag00;
    close();
}

void Config0::on_checkBox_clicked(bool checked)
{
    if(checked==1)
    {
            ui->lineEdit_19->setEnabled(true);
            ui->lineEdit_20->setEnabled(true);
    }
    if(checked==0)
    {
            ui->lineEdit_19->setEnabled(false);
            ui->lineEdit_20->setEnabled(false);
    }
}
