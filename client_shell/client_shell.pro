#-------------------------------------------------
#
# Project created by QtCreator 2017-02-22T21:20:45
#
#-------------------------------------------------

QT       += core gui
QT       +=xml
QT       += widgets printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client_shell
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        SocketMatTransmissionServer.cpp \
    config0.cpp \
    config1.cpp \
    config2.cpp \
    thread.cpp \
    SocketThread.cpp \
    typechange.cpp \
    xml.cpp \
    qcustomplot.cpp


HEADERS  += mainwindow.h\
            SocketMatTransmissionServer.h\
    config0.h \
    config1.h \
    config2.h \
    thread.h \
    SocketThread.h \
    typechange.h \
    xml.h \
    qcustomplot.h


FORMS    += mainwindow.ui \
    config0.ui \
    config1.ui \
    config2.ui

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so
