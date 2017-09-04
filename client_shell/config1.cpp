#include "config1.h"
#include "ui_config1.h"
#include "mainwindow.h"
#include "xml.h"
extern Camera_config camera_conf[3];

XmlContainer configXml1;

int flag10=0;//开关  0：关闭程序    1：改状态
int flag11=0;//存图  0：不存     1：存
int flag12=0;//数据清零  0：不清零   1：清零
int flag13=0;//改线  0：不改线   1：改线

float old_x1[20],old_dx1[20];
Config1::Config1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config1)
{
    ui->setupUi(this);
    dispData();
}

Config1::~Config1()
{
    delete ui;
}

void Config1::on_pushButton_2_clicked()
{
    close();
}

void Config1::dispData()
{
    configXml1.readXml(camera_conf);
    ui->lineEdit_17->setText(QString::fromStdString(camera_conf[1].corePath));
    ui->lineEdit_15->setText(QString::fromStdString(camera_conf[1].admin));
    ui->lineEdit_14->setText(QString::fromStdString(camera_conf[1].code));
    ui->lineEdit_18->setText(QString::fromStdString(camera_conf[1].IPCore));
    ui->lineEdit_12->setText(QString::fromStdString(camera_conf[1].IPCamera));
    ui->lineEdit_19->setText(QString::fromStdString(camera_conf[1].SavePicPrefix));
    ui->lineEdit_20->setText(QString::fromStdString(camera_conf[1].SavePicPath));
    ui->lineEdit_13->setText(QString::number(camera_conf[1].PortCamera,10));
    ui->lineEdit_16->setText(QString::number(camera_conf[1].sense,10));
    ui->lineEdit_10->setText(QString::number(camera_conf[1].hour,10));
    ui->lineEdit_11->setText(QString::number(camera_conf[1].min,10));

    ui->lineEdit->setText(QString("%1").arg(camera_conf[1].x[0]));
    ui->lineEdit_2->setText(QString("%1").arg(camera_conf[1].x[1]));
    ui->lineEdit_3->setText(QString("%1").arg(camera_conf[1].x[2]));
    ui->lineEdit_4->setText(QString("%1").arg(camera_conf[1].x[3]));
    ui->lineEdit_5->setText(QString("%1").arg(camera_conf[1].x[4]));
    ui->lineEdit_6->setText(QString("%1").arg(camera_conf[1].x[5]));
    ui->lineEdit_9->setText(QString("%1").arg(camera_conf[1].x[6]));
    ui->lineEdit_21->setText(QString("%1").arg(camera_conf[1].x[7]));
    ui->lineEdit_24->setText(QString("%1").arg(camera_conf[1].x[8]));
    ui->lineEdit_25->setText(QString("%1").arg(camera_conf[1].x[9]));
    ui->lineEdit_26->setText(QString("%1").arg(camera_conf[1].x[10]));
    ui->lineEdit_27->setText(QString("%1").arg(camera_conf[1].x[11]));
    ui->lineEdit_30->setText(QString("%1").arg(camera_conf[1].x[12]));
    ui->lineEdit_31->setText(QString("%1").arg(camera_conf[1].x[13]));
    ui->lineEdit_32->setText(QString("%1").arg(camera_conf[1].x[14]));
    ui->lineEdit_33->setText(QString("%1").arg(camera_conf[1].x[15]));
    ui->lineEdit_36->setText(QString("%1").arg(camera_conf[1].x[16]));
    ui->lineEdit_37->setText(QString("%1").arg(camera_conf[1].x[17]));
    ui->lineEdit_38->setText(QString("%1").arg(camera_conf[1].x[18]));
    ui->lineEdit_39->setText(QString("%1").arg(camera_conf[1].x[19]));

    ui->lineEdit_7->setText(QString("%1").arg(camera_conf[1].dx[2]));
    ui->lineEdit_8->setText(QString("%1").arg(camera_conf[1].dx[3]));
    ui->lineEdit_22->setText(QString("%1").arg(camera_conf[1].dx[6]));//end
    ui->lineEdit_23->setText(QString("%1").arg(camera_conf[1].dx[7]));//end
    ui->lineEdit_28->setText(QString("%1").arg(camera_conf[1].dx[10]));
    ui->lineEdit_29->setText(QString("%1").arg(camera_conf[1].dx[11]));
    ui->lineEdit_34->setText(QString("%1").arg(camera_conf[1].dx[14]));//end
    ui->lineEdit_35->setText(QString("%1").arg(camera_conf[1].dx[15]));//end
    ui->lineEdit_40->setText(QString("%1").arg(camera_conf[1].dx[18]));
    ui->lineEdit_41->setText(QString("%1").arg(camera_conf[1].dx[19]));


    ui->checkBox->setChecked((bool)camera_conf[1].SavePicFlag);

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

void Config1::saveData()
{
    flag10=1;

    for(int i=0;i<20;i++)
    {
        old_x1[i]=camera_conf[1].x[i];
        old_dx1[i]=camera_conf[1].dx[i];
    }

    QString strText = ui->lineEdit->text();
    camera_conf[1].x[0]=strText.toFloat();//x1
    strText = ui->lineEdit_2->text();
    camera_conf[1].x[1]=strText.toFloat();//y1
    strText = ui->lineEdit_3->text();
    camera_conf[1].x[2]=strText.toFloat();//x2
    strText = ui->lineEdit_4->text();
    camera_conf[1].x[3]=strText.toFloat();//y2
    strText = ui->lineEdit_5->text();
    camera_conf[1].x[4]=strText.toFloat();
    strText = ui->lineEdit_6->text();
    camera_conf[1].x[5]=strText.toFloat();
    strText = ui->lineEdit_9->text();
    camera_conf[1].x[6]=strText.toFloat();
    strText = ui->lineEdit_21->text();
    camera_conf[1].x[7]=strText.toFloat();
    strText = ui->lineEdit_24->text();
    camera_conf[1].x[8]=strText.toFloat();
    strText = ui->lineEdit_25->text();
    camera_conf[1].x[9]=strText.toFloat();
    strText = ui->lineEdit_26->text();
    camera_conf[1].x[10]=strText.toFloat();
    strText = ui->lineEdit_27->text();
    camera_conf[1].x[11]=strText.toFloat();
    strText = ui->lineEdit_30->text();
    camera_conf[1].x[12]=strText.toFloat();
    strText = ui->lineEdit_31->text();
    camera_conf[1].x[13]=strText.toFloat();
    strText = ui->lineEdit_32->text();
    camera_conf[1].x[14]=strText.toFloat();
    strText = ui->lineEdit_33->text();
    camera_conf[1].x[15]=strText.toFloat();
    strText = ui->lineEdit_36->text();
    camera_conf[1].x[16]=strText.toFloat();
    strText = ui->lineEdit_37->text();
    camera_conf[1].x[17]=strText.toFloat();
    strText = ui->lineEdit_38->text();
    camera_conf[1].x[18]=strText.toFloat();
    strText = ui->lineEdit_39->text();
    camera_conf[1].x[19]=strText.toFloat();



    strText = ui->lineEdit_7->text();
    camera_conf[1].dx[2]=strText.toFloat();
    strText = ui->lineEdit_8->text();
    camera_conf[1].dx[3]=strText.toFloat();
    strText = ui->lineEdit_22->text();
    camera_conf[1].dx[6]=strText.toFloat();
    strText = ui->lineEdit_23->text();
    camera_conf[1].dx[7]=strText.toFloat();
    strText = ui->lineEdit_28->text();
    camera_conf[1].dx[10]=strText.toFloat();
    strText = ui->lineEdit_29->text();
    camera_conf[1].dx[11]=strText.toFloat();
    strText = ui->lineEdit_34->text();
    camera_conf[1].dx[14]=strText.toFloat();
    strText = ui->lineEdit_35->text();
    camera_conf[1].dx[15]=strText.toFloat();
    strText = ui->lineEdit_40->text();
    camera_conf[1].dx[18]=strText.toFloat();
    strText = ui->lineEdit_41->text();
    camera_conf[1].dx[19]=strText.toFloat();

    camera_conf[1].dx[0]=(camera_conf[1].x[0]+camera_conf[1].x[2])/2;
    camera_conf[1].dx[1]=(camera_conf[1].x[1]+camera_conf[1].x[3])/2;
    camera_conf[1].dx[4]=(camera_conf[1].x[4]+camera_conf[1].x[6])/2;
    camera_conf[1].dx[5]=(camera_conf[1].x[5]+camera_conf[1].x[7])/2;
    camera_conf[1].dx[8]=(camera_conf[1].x[8]+camera_conf[1].x[10])/2;
    camera_conf[1].dx[9]=(camera_conf[1].x[9]+camera_conf[1].x[11])/2;
    camera_conf[1].dx[12]=(camera_conf[1].x[12]+camera_conf[1].x[14])/2;
    camera_conf[1].dx[13]=(camera_conf[1].x[13]+camera_conf[1].x[15])/2;
    camera_conf[1].dx[16]=(camera_conf[1].x[16]+camera_conf[1].x[18])/2;
    camera_conf[1].dx[17]=(camera_conf[1].x[17]+camera_conf[1].x[19])/2;





    strText = ui->lineEdit_10->text();
    camera_conf[1].hour=(int)strText.toFloat();
    strText = ui->lineEdit_11->text();
    camera_conf[1].min=(int)strText.toFloat();

    strText = ui->lineEdit_16->text();
    camera_conf[1].sense=(int)strText.toFloat();

    strText = ui->lineEdit_12->text();
    camera_conf[1].IPCamera=strText.toStdString();

    strText = ui->lineEdit_13->text();
    camera_conf[1].PortCamera=(int)strText.toFloat();

    strText = ui->lineEdit_14->text();
    camera_conf[1].code=strText.toStdString();

    strText = ui->lineEdit_15->text();
    camera_conf[1].admin=strText.toStdString();

    strText = ui->lineEdit_17->text();
    camera_conf[1].corePath=strText.toStdString();

    strText = ui->lineEdit_18->text();
    camera_conf[1].IPCore=strText.toStdString();

    strText = ui->lineEdit_19->text();
    camera_conf[1].SavePicPrefix=strText.toStdString();

    strText = ui->lineEdit_20->text();
    camera_conf[1].SavePicPath=strText.toStdString();

    camera_conf[1].SavePicFlag=ui->checkBox->isChecked();

    if((camera_conf[1].x[0]!=old_x1[0])||(camera_conf[1].x[1]!=old_x1[1])||(camera_conf[1].x[2]!=old_x1[2])||(camera_conf[1].x[3]!=old_x1[3])||(camera_conf[1].dx[0]!=old_dx1[0])||(camera_conf[1].dx[1]!=old_dx1[1])||(camera_conf[1].dx[2]!=old_dx1[2])||(camera_conf[1].dx[3]!=old_dx1[3]))
    {
        flag12=1;
        flag13=1;
    }
    else
    {
        flag12=0;
        flag13=0;
    }
    if(ui->checkBox->isChecked()==1)
    {
        flag11=1;
    }
    if(ui->checkBox->isChecked()==0)
    {
        flag11=0;
    }
    camera_conf[1].order=flag13*8+flag12*4+flag11*2+flag10;

    configXml1.writeXml(camera_conf);
}

void Config1::on_pushButton_clicked()
{
    saveData();
    close();
}

void Config1::on_checkBox_clicked(bool checked)
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
