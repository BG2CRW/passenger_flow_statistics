/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *Tab;
    QWidget *CameraPage0;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_11;
    QLabel *label_7;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_12;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEdit_13;
    QLineEdit *lineEdit_14;
    QLabel *label_10;
    QLabel *label_11;
    QWidget *CameraPage1;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_12;
    QLabel *label_3;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_4;
    QLineEdit *lineEdit_15;
    QLineEdit *lineEdit_16;
    QLineEdit *lineEdit_17;
    QLineEdit *lineEdit_18;
    QLineEdit *lineEdit_19;
    QLineEdit *lineEdit_20;
    QLineEdit *lineEdit_21;
    QLineEdit *lineEdit_22;
    QWidget *CameraPage2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_9;
    QPushButton *pushButton_13;
    QLabel *label_5;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_6;
    QLineEdit *lineEdit_23;
    QLineEdit *lineEdit_24;
    QLineEdit *lineEdit_25;
    QLineEdit *lineEdit_26;
    QLineEdit *lineEdit_27;
    QLineEdit *lineEdit_28;
    QLineEdit *lineEdit_29;
    QLineEdit *lineEdit_30;
    QWidget *Analysis;
    QPushButton *pushButton_10;
    QCustomPlot *qCustomPlot;
    QCustomPlot *qCustomPlot_2;
    QCustomPlot *qCustomPlot_3;
    QPushButton *pushButton_14;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(994, 772);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Tab = new QTabWidget(centralWidget);
        Tab->setObjectName(QStringLiteral("Tab"));
        Tab->setGeometry(QRect(10, 0, 971, 711));
        CameraPage0 = new QWidget();
        CameraPage0->setObjectName(QStringLiteral("CameraPage0"));
        CameraPage0->setEnabled(true);
        CameraPage0->setAutoFillBackground(false);
        verticalLayoutWidget = new QWidget(CameraPage0);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 951, 551));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(CameraPage0);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(90, 600, 91, 27));
        label = new QLabel(CameraPage0);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 600, 67, 16));
        lineEdit_2 = new QLineEdit(CameraPage0);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(90, 630, 91, 27));
        label_2 = new QLabel(CameraPage0);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 630, 67, 17));
        pushButton_3 = new QPushButton(CameraPage0);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(650, 630, 99, 27));
        pushButton_2 = new QPushButton(CameraPage0);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(650, 590, 99, 27));
        pushButton = new QPushButton(CameraPage0);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(790, 630, 99, 27));
        pushButton_11 = new QPushButton(CameraPage0);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setGeometry(QRect(790, 590, 99, 27));
        label_7 = new QLabel(CameraPage0);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(120, 580, 31, 16));
        lineEdit_7 = new QLineEdit(CameraPage0);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(190, 600, 91, 27));
        lineEdit_8 = new QLineEdit(CameraPage0);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(190, 630, 91, 27));
        lineEdit_9 = new QLineEdit(CameraPage0);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        lineEdit_9->setGeometry(QRect(290, 600, 91, 27));
        lineEdit_10 = new QLineEdit(CameraPage0);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));
        lineEdit_10->setGeometry(QRect(290, 630, 91, 27));
        lineEdit_11 = new QLineEdit(CameraPage0);
        lineEdit_11->setObjectName(QStringLiteral("lineEdit_11"));
        lineEdit_11->setGeometry(QRect(390, 600, 91, 27));
        lineEdit_12 = new QLineEdit(CameraPage0);
        lineEdit_12->setObjectName(QStringLiteral("lineEdit_12"));
        lineEdit_12->setGeometry(QRect(390, 630, 91, 27));
        label_8 = new QLabel(CameraPage0);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(220, 580, 31, 16));
        label_9 = new QLabel(CameraPage0);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(320, 580, 31, 16));
        lineEdit_13 = new QLineEdit(CameraPage0);
        lineEdit_13->setObjectName(QStringLiteral("lineEdit_13"));
        lineEdit_13->setGeometry(QRect(490, 600, 91, 27));
        lineEdit_14 = new QLineEdit(CameraPage0);
        lineEdit_14->setObjectName(QStringLiteral("lineEdit_14"));
        lineEdit_14->setGeometry(QRect(490, 630, 91, 27));
        label_10 = new QLabel(CameraPage0);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(420, 580, 31, 16));
        label_11 = new QLabel(CameraPage0);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(520, 580, 31, 16));
        Tab->addTab(CameraPage0, QString());
        CameraPage1 = new QWidget();
        CameraPage1->setObjectName(QStringLiteral("CameraPage1"));
        verticalLayoutWidget_2 = new QWidget(CameraPage1);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 951, 551));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit_3 = new QLineEdit(CameraPage1);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(90, 600, 91, 27));
        lineEdit_4 = new QLineEdit(CameraPage1);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(90, 630, 91, 27));
        pushButton_6 = new QPushButton(CameraPage1);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(650, 590, 99, 27));
        pushButton_7 = new QPushButton(CameraPage1);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(650, 630, 99, 27));
        pushButton_8 = new QPushButton(CameraPage1);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(790, 630, 99, 27));
        pushButton_12 = new QPushButton(CameraPage1);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(790, 590, 99, 27));
        label_3 = new QLabel(CameraPage1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 630, 67, 17));
        label_12 = new QLabel(CameraPage1);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(520, 580, 31, 16));
        label_13 = new QLabel(CameraPage1);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(420, 580, 31, 16));
        label_14 = new QLabel(CameraPage1);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(220, 580, 31, 16));
        label_15 = new QLabel(CameraPage1);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(120, 580, 31, 16));
        label_16 = new QLabel(CameraPage1);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(320, 580, 31, 16));
        label_4 = new QLabel(CameraPage1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 600, 67, 16));
        lineEdit_15 = new QLineEdit(CameraPage1);
        lineEdit_15->setObjectName(QStringLiteral("lineEdit_15"));
        lineEdit_15->setGeometry(QRect(390, 600, 91, 27));
        lineEdit_16 = new QLineEdit(CameraPage1);
        lineEdit_16->setObjectName(QStringLiteral("lineEdit_16"));
        lineEdit_16->setGeometry(QRect(190, 600, 91, 27));
        lineEdit_17 = new QLineEdit(CameraPage1);
        lineEdit_17->setObjectName(QStringLiteral("lineEdit_17"));
        lineEdit_17->setGeometry(QRect(290, 630, 91, 27));
        lineEdit_18 = new QLineEdit(CameraPage1);
        lineEdit_18->setObjectName(QStringLiteral("lineEdit_18"));
        lineEdit_18->setGeometry(QRect(290, 600, 91, 27));
        lineEdit_19 = new QLineEdit(CameraPage1);
        lineEdit_19->setObjectName(QStringLiteral("lineEdit_19"));
        lineEdit_19->setGeometry(QRect(390, 630, 91, 27));
        lineEdit_20 = new QLineEdit(CameraPage1);
        lineEdit_20->setObjectName(QStringLiteral("lineEdit_20"));
        lineEdit_20->setGeometry(QRect(490, 600, 91, 27));
        lineEdit_21 = new QLineEdit(CameraPage1);
        lineEdit_21->setObjectName(QStringLiteral("lineEdit_21"));
        lineEdit_21->setGeometry(QRect(490, 630, 91, 27));
        lineEdit_22 = new QLineEdit(CameraPage1);
        lineEdit_22->setObjectName(QStringLiteral("lineEdit_22"));
        lineEdit_22->setGeometry(QRect(190, 630, 91, 27));
        Tab->addTab(CameraPage1, QString());
        CameraPage2 = new QWidget();
        CameraPage2->setObjectName(QStringLiteral("CameraPage2"));
        verticalLayoutWidget_3 = new QWidget(CameraPage2);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 10, 951, 551));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        lineEdit_5 = new QLineEdit(CameraPage2);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(90, 600, 91, 27));
        lineEdit_6 = new QLineEdit(CameraPage2);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(90, 630, 91, 27));
        pushButton_4 = new QPushButton(CameraPage2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(650, 590, 99, 27));
        pushButton_5 = new QPushButton(CameraPage2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(650, 630, 99, 27));
        pushButton_9 = new QPushButton(CameraPage2);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(790, 630, 99, 27));
        pushButton_13 = new QPushButton(CameraPage2);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setGeometry(QRect(790, 590, 99, 27));
        label_5 = new QLabel(CameraPage2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 630, 67, 17));
        label_17 = new QLabel(CameraPage2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(520, 580, 31, 16));
        label_18 = new QLabel(CameraPage2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(420, 580, 31, 16));
        label_19 = new QLabel(CameraPage2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(220, 580, 31, 16));
        label_20 = new QLabel(CameraPage2);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(120, 580, 31, 16));
        label_21 = new QLabel(CameraPage2);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(320, 580, 31, 16));
        label_6 = new QLabel(CameraPage2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 600, 67, 16));
        lineEdit_23 = new QLineEdit(CameraPage2);
        lineEdit_23->setObjectName(QStringLiteral("lineEdit_23"));
        lineEdit_23->setGeometry(QRect(390, 600, 91, 27));
        lineEdit_24 = new QLineEdit(CameraPage2);
        lineEdit_24->setObjectName(QStringLiteral("lineEdit_24"));
        lineEdit_24->setGeometry(QRect(190, 600, 91, 27));
        lineEdit_25 = new QLineEdit(CameraPage2);
        lineEdit_25->setObjectName(QStringLiteral("lineEdit_25"));
        lineEdit_25->setGeometry(QRect(290, 630, 91, 27));
        lineEdit_26 = new QLineEdit(CameraPage2);
        lineEdit_26->setObjectName(QStringLiteral("lineEdit_26"));
        lineEdit_26->setGeometry(QRect(290, 600, 91, 27));
        lineEdit_27 = new QLineEdit(CameraPage2);
        lineEdit_27->setObjectName(QStringLiteral("lineEdit_27"));
        lineEdit_27->setGeometry(QRect(390, 630, 91, 27));
        lineEdit_28 = new QLineEdit(CameraPage2);
        lineEdit_28->setObjectName(QStringLiteral("lineEdit_28"));
        lineEdit_28->setGeometry(QRect(490, 600, 91, 27));
        lineEdit_29 = new QLineEdit(CameraPage2);
        lineEdit_29->setObjectName(QStringLiteral("lineEdit_29"));
        lineEdit_29->setGeometry(QRect(490, 630, 91, 27));
        lineEdit_30 = new QLineEdit(CameraPage2);
        lineEdit_30->setObjectName(QStringLiteral("lineEdit_30"));
        lineEdit_30->setGeometry(QRect(190, 630, 91, 27));
        Tab->addTab(CameraPage2, QString());
        Analysis = new QWidget();
        Analysis->setObjectName(QStringLiteral("Analysis"));
        pushButton_10 = new QPushButton(Analysis);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(790, 630, 99, 27));
        qCustomPlot = new QCustomPlot(Analysis);
        qCustomPlot->setObjectName(QStringLiteral("qCustomPlot"));
        qCustomPlot->setGeometry(QRect(20, 30, 441, 251));
        qCustomPlot_2 = new QCustomPlot(Analysis);
        qCustomPlot_2->setObjectName(QStringLiteral("qCustomPlot_2"));
        qCustomPlot_2->setGeometry(QRect(500, 30, 441, 251));
        qCustomPlot_3 = new QCustomPlot(Analysis);
        qCustomPlot_3->setObjectName(QStringLiteral("qCustomPlot_3"));
        qCustomPlot_3->setGeometry(QRect(20, 310, 441, 251));
        pushButton_14 = new QPushButton(Analysis);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setGeometry(QRect(650, 630, 99, 27));
        Tab->addTab(Analysis, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 994, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        Tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\256\242\346\265\201\347\273\237\350\256\241 v1.0", 0));
        lineEdit->setText(QApplication::translate("MainWindow", "0", 0));
        label->setText(QApplication::translate("MainWindow", "\350\277\233\345\205\245\344\272\272\346\225\260", 0));
        lineEdit_2->setText(QApplication::translate("MainWindow", "0", 0));
        label_2->setText(QApplication::translate("MainWindow", "\347\246\273\345\274\200\344\272\272\346\225\260", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "\346\226\255\345\274\200\347\233\270\346\234\272", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245\347\233\270\346\234\272", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0));
        pushButton_11->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0));
        label_7->setText(QApplication::translate("MainWindow", "\347\272\2771", 0));
        lineEdit_7->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_8->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_9->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_10->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_11->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_12->setText(QApplication::translate("MainWindow", "0", 0));
        label_8->setText(QApplication::translate("MainWindow", "\347\272\2772", 0));
        label_9->setText(QApplication::translate("MainWindow", "\347\272\2773", 0));
        lineEdit_13->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_14->setText(QApplication::translate("MainWindow", "0", 0));
        label_10->setText(QApplication::translate("MainWindow", "\347\272\2774", 0));
        label_11->setText(QApplication::translate("MainWindow", "\347\272\2775", 0));
        Tab->setTabText(Tab->indexOf(CameraPage0), QApplication::translate("MainWindow", "Camera_0", 0));
        lineEdit_3->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_4->setText(QApplication::translate("MainWindow", "0", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245\347\233\270\346\234\272", 0));
        pushButton_7->setText(QApplication::translate("MainWindow", "\346\226\255\345\274\200\347\233\270\346\234\272", 0));
        pushButton_8->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0));
        pushButton_12->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0));
        label_3->setText(QApplication::translate("MainWindow", "\347\246\273\345\274\200\344\272\272\346\225\260", 0));
        label_12->setText(QApplication::translate("MainWindow", "\347\272\2775", 0));
        label_13->setText(QApplication::translate("MainWindow", "\347\272\2774", 0));
        label_14->setText(QApplication::translate("MainWindow", "\347\272\2772", 0));
        label_15->setText(QApplication::translate("MainWindow", "\347\272\2771", 0));
        label_16->setText(QApplication::translate("MainWindow", "\347\272\2773", 0));
        label_4->setText(QApplication::translate("MainWindow", "\350\277\233\345\205\245\344\272\272\346\225\260", 0));
        lineEdit_15->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_16->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_17->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_18->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_19->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_20->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_21->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_22->setText(QApplication::translate("MainWindow", "0", 0));
        Tab->setTabText(Tab->indexOf(CameraPage1), QApplication::translate("MainWindow", "Camera_1", 0));
        lineEdit_5->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_6->setText(QApplication::translate("MainWindow", "0", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245\347\233\270\346\234\272", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "\346\226\255\345\274\200\347\233\270\346\234\272", 0));
        pushButton_9->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0));
        pushButton_13->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0));
        label_5->setText(QApplication::translate("MainWindow", "\347\246\273\345\274\200\344\272\272\346\225\260", 0));
        label_17->setText(QApplication::translate("MainWindow", "\347\272\2775", 0));
        label_18->setText(QApplication::translate("MainWindow", "\347\272\2774", 0));
        label_19->setText(QApplication::translate("MainWindow", "\347\272\2772", 0));
        label_20->setText(QApplication::translate("MainWindow", "\347\272\2771", 0));
        label_21->setText(QApplication::translate("MainWindow", "\347\272\2773", 0));
        label_6->setText(QApplication::translate("MainWindow", "\350\277\233\345\205\245\344\272\272\346\225\260", 0));
        lineEdit_23->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_24->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_25->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_26->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_27->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_28->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_29->setText(QApplication::translate("MainWindow", "0", 0));
        lineEdit_30->setText(QApplication::translate("MainWindow", "0", 0));
        Tab->setTabText(Tab->indexOf(CameraPage2), QApplication::translate("MainWindow", "Camera_2", 0));
        pushButton_10->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0));
        pushButton_14->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\346\212\245\345\221\212", 0));
        Tab->setTabText(Tab->indexOf(Analysis), QApplication::translate("MainWindow", "Analysis", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
