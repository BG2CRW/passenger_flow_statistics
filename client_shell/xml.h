#ifndef XML_H
#define XML_H
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include "typechange.h"
#include <QString>
struct Camera_config
{
    float x[20];
    float dx[20];

    int hour,min;

    int order;//-1: normal   0:change all para   1 : shutdown   2:change line   3:close save   4:open save
    string IPCamera;
    int PortCamera;
    string admin;
    string code;

    string IPCore;
    string corePath;
    int sense;
    int SavePicFlag;
    string SavePicPrefix;
    string SavePicPath;
};

class XmlContainer
{
public:
     int readXml(struct Camera_config *read_struct);
     int writeXml(struct Camera_config *config_struct);

};

#endif // XML_H
