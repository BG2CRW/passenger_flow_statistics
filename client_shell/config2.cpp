#include "config2.h"
#include "ui_config2.h"
#include "mainwindow.h"
#include "xml.h"
extern Camera_config camera_conf[3];

XmlContainer configXml2;

int flag20=0;//开关  0：关闭程序    1：改状态
int flag21=0;//存图  0：不存     1：存
int flag22=0;//数据清零  0：不清零   1：清零
int flag23=0;//改线  0：不改线   1：改线

float old_x2[20],old_dx2[20];

Config2::Config2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config2)
{
    ui->setupUi(this);
    dispData();
}

Config2::~Config2()
{
    delete ui;
}

void Config2::on_pushButton_2_clicked()
{
    close();
}

void Config2::dispData()
{
    configXml2.readXml(camera_conf);
    ui->lineEdit_17->setText(QString::fromStdString(camera_conf[2].corePath));
    ui->lineEdit_15->setText(QString::fromStdString(camera_conf[2].admin));
    ui->lineEdit_14->setText(QString::fromStdString(camera_conf[2].code));
    ui->lineEdit_18->setText(QString::fromStdString(camera_conf[2].IPCore));
    ui->lineEdit_12->setText(QString::fromStdString(camera_conf[2].IPCamera));
    ui->lineEdit_19->setText(QString::fromStdString(camera_conf[2].SavePicPrefix));
    ui->lineEdit_20->setText(QString::fromStdString(camera_conf[2].SavePicPath));
    ui->lineEdit_13->setText(QString::number(camera_conf[2].PortCamera,10));
    ui->lineEdit_16->setText(QString::number(camera_conf[2].sense,10));
    ui->lineEdit_10->setText(QString::number(camera_conf[2].hour,10));
    ui->lineEdit_11->setText(QString::number(camera_conf[2].min,10));
    ui->lineEdit->setText(QString("%1").arg(camera_conf[2].x[0]));
    ui->lineEdit_2->setText(QString("%1").arg(camera_conf[2].x[1]));
    ui->lineEdit_3->setText(QString("%1").arg(camera_conf[2].x[2]));
    ui->lineEdit_4->setText(QString("%1").arg(camera_conf[2].x[3]));
    ui->lineEdit_5->setText(QString("%1").arg(camera_conf[2].dx[0]));
    ui->lineEdit_6->setText(QString("%1").arg(camera_conf[2].dx[1]));
    ui->lineEdit_7->setText(QString("%1").arg(camera_conf[2].dx[2]));
    ui->lineEdit_8->setText(QString("%1").arg(camera_conf[2].dx[3]));


    ui->checkBox->setChecked((bool)camera_conf[2].SavePicFlag);

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

void Config2::saveData()
{
    flag20=1;

    for(int i=0;i<20;i++)
    {
        old_x2[i]=camera_conf[2].x[i];
        old_dx2[i]=camera_conf[2].dx[i];
    }
    QString strText = ui->lineEdit->text();
    camera_conf[2].x[0]=strText.toFloat();
    strText = ui->lineEdit_2->text();
    camera_conf[2].x[1]=strText.toFloat();

    strText = ui->lineEdit_3->text();
    camera_conf[2].x[2]=strText.toFloat();
    strText = ui->lineEdit_4->text();
    camera_conf[2].x[3]=strText.toFloat();

    strText = ui->lineEdit_5->text();
    camera_conf[2].dx[0]=strText.toFloat();
    strText = ui->lineEdit_6->text();
    camera_conf[2].dx[1]=strText.toFloat();

    strText = ui->lineEdit_7->text();
    camera_conf[2].dx[2]=strText.toFloat();
    strText = ui->lineEdit_8->text();
    camera_conf[2].dx[3]=strText.toFloat();

    strText = ui->lineEdit_10->text();
    camera_conf[2].hour=(int)strText.toFloat();
    strText = ui->lineEdit_11->text();
    camera_conf[2].min=(int)strText.toFloat();

    strText = ui->lineEdit_16->text();
    camera_conf[2].sense=(int)strText.toFloat();

    strText = ui->lineEdit_12->text();
    camera_conf[2].IPCamera=strText.toStdString();

    strText = ui->lineEdit_13->text();
    camera_conf[2].PortCamera=(int)strText.toFloat();

    strText = ui->lineEdit_14->text();
    camera_conf[2].code=strText.toStdString();

    strText = ui->lineEdit_15->text();
    camera_conf[2].admin=strText.toStdString();

    strText = ui->lineEdit_17->text();
    camera_conf[2].corePath=strText.toStdString();

    strText = ui->lineEdit_18->text();
    camera_conf[2].IPCore=strText.toStdString();

    strText = ui->lineEdit_19->text();
    camera_conf[2].SavePicPrefix=strText.toStdString();

    strText = ui->lineEdit_20->text();
    camera_conf[2].SavePicPath=strText.toStdString();

    camera_conf[2].SavePicFlag=ui->checkBox->isChecked();

    if((camera_conf[2].x[0]!=old_x2[0])||(camera_conf[2].x[1]!=old_x2[1])||(camera_conf[2].x[2]!=old_x2[2])||(camera_conf[2].x[3]!=old_x2[3])||(camera_conf[2].dx[0]!=old_dx2[0])||(camera_conf[2].dx[1]!=old_dx2[1])||(camera_conf[2].dx[2]!=old_dx2[2])||(camera_conf[2].dx[3]!=old_dx2[3]))
    {
        flag22=1;
        flag23=1;
    }
    else
    {
        flag22=0;
        flag23=0;
    }
    if(ui->checkBox->isChecked()==1)
    {
        flag21=1;
    }
    if(ui->checkBox->isChecked()==0)
    {
        flag21=0;
    }
    camera_conf[2].order=flag23*8+flag22*4+flag21*2+flag20;
    configXml2.writeXml(camera_conf);
}

void Config2::on_pushButton_clicked()
{
    saveData();
    close();
}

void Config2::on_checkBox_clicked(bool checked)
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
