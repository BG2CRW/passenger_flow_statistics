#include "xml.h"
#include "mainwindow.h"

TypeChange TYPE;

int XmlContainer::writeXml(struct Camera_config *config_struct)
{
    QFile file("config.xml");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
            writer.writeStartElement("Config");
                writer.writeStartElement("Camera0");
                    writer.writeTextElement("IP", TYPE.stringToChar(config_struct[0].IPCamera,sizeof( config_struct[0].IPCamera)));
                    writer.writeTextElement("Port", QString::number(config_struct[0].PortCamera, 10));
                    writer.writeTextElement("User", TYPE.stringToChar(config_struct[0].admin,sizeof( config_struct[0].admin)));
                    writer.writeTextElement("Code", TYPE.stringToChar(config_struct[0].code,sizeof( config_struct[0].code)));
                    writer.writeTextElement("Threshold", QString::number(config_struct[0].sense, 10));
                    writer.writeTextElement("Bound1x", QString("%1").arg(config_struct[0].x[0]));
                    writer.writeTextElement("Bound1y", QString("%1").arg(config_struct[0].x[1]));
                    writer.writeTextElement("Bound2x", QString("%1").arg(config_struct[0].x[2]));
                    writer.writeTextElement("Bound2y", QString("%1").arg(config_struct[0].x[3]));
                    writer.writeTextElement("Dir_in1x", QString("%1").arg(config_struct[0].dx[0]));
                    writer.writeTextElement("Dir_in1y", QString("%1").arg(config_struct[0].dx[1]));
                    writer.writeTextElement("Dir_in2x", QString("%1").arg(config_struct[0].dx[2]));
                    writer.writeTextElement("Dir_in2y", QString("%1").arg(config_struct[0].dx[3]));
                    writer.writeTextElement("setTimeHour",QString::number(config_struct[0].hour, 10));
                    writer.writeTextElement("setTimeMin", QString::number(config_struct[0].min, 10));
                    writer.writeTextElement("SocketClientIP", TYPE.stringToChar(config_struct[0].IPCore,sizeof( config_struct[0].IPCore)));
                    writer.writeTextElement("CorePath", TYPE.stringToChar(config_struct[0].corePath,100));
                    writer.writeTextElement("SavePicFlag", QString::number(config_struct[0].SavePicFlag, 10));
                    writer.writeTextElement("SavePicPrefix", TYPE.stringToChar(config_struct[0].SavePicPrefix,sizeof( config_struct[0].SavePicPrefix)));
                    writer.writeTextElement("SavePicPath", TYPE.stringToChar(config_struct[0].SavePicPath,sizeof( config_struct[0].SavePicPath)));
                    writer.writeTextElement("Order", QString::number(config_struct[0].order, 10));
                 writer.writeEndElement();

                 writer.writeStartElement("Camera1");
                     writer.writeTextElement("IP",TYPE.stringToChar(config_struct[1].IPCamera,sizeof( config_struct[1].IPCamera)));
                     writer.writeTextElement("Port", QString::number(config_struct[1].PortCamera, 10));
                     writer.writeTextElement("User", TYPE.stringToChar(config_struct[1].admin,sizeof( config_struct[1].admin)));
                     writer.writeTextElement("Code", TYPE.stringToChar(config_struct[1].code,sizeof( config_struct[1].code)));
                     writer.writeTextElement("Threshold", QString::number(config_struct[1].sense, 10));
                     writer.writeTextElement("Bound1x", QString("%1").arg(config_struct[1].x[0]));
                     writer.writeTextElement("Bound1y", QString("%1").arg(config_struct[1].x[1]));
                     writer.writeTextElement("Bound2x", QString("%1").arg(config_struct[1].x[2]));
                     writer.writeTextElement("Bound2y", QString("%1").arg(config_struct[1].x[3]));
                     writer.writeTextElement("Bound3x", QString("%1").arg(config_struct[1].x[4]));
                     writer.writeTextElement("Bound3y", QString("%1").arg(config_struct[1].x[5]));
                     writer.writeTextElement("Bound4x", QString("%1").arg(config_struct[1].x[6]));
                     writer.writeTextElement("Bound4y", QString("%1").arg(config_struct[1].x[7]));
                     writer.writeTextElement("Bound5x", QString("%1").arg(config_struct[1].x[8]));
                     writer.writeTextElement("Bound5y", QString("%1").arg(config_struct[1].x[9]));
                     writer.writeTextElement("Bound6x", QString("%1").arg(config_struct[1].x[10]));
                     writer.writeTextElement("Bound6y", QString("%1").arg(config_struct[1].x[11]));
                     writer.writeTextElement("Bound7x", QString("%1").arg(config_struct[1].x[12]));
                     writer.writeTextElement("Bound7y", QString("%1").arg(config_struct[1].x[13]));
                     writer.writeTextElement("Bound8x", QString("%1").arg(config_struct[1].x[14]));
                     writer.writeTextElement("Bound8y", QString("%1").arg(config_struct[1].x[15]));
                     writer.writeTextElement("Bound9x", QString("%1").arg(config_struct[1].x[16]));
                     writer.writeTextElement("Bound9y", QString("%1").arg(config_struct[1].x[17]));
                     writer.writeTextElement("Bound10x", QString("%1").arg(config_struct[1].x[18]));
                     writer.writeTextElement("Bound10y", QString("%1").arg(config_struct[1].x[19]));

                     writer.writeTextElement("Dir_in1x", QString("%1").arg(config_struct[1].dx[0]));
                     writer.writeTextElement("Dir_in1y", QString("%1").arg(config_struct[1].dx[1]));
                     writer.writeTextElement("Dir_in2x", QString("%1").arg(config_struct[1].dx[2]));
                     writer.writeTextElement("Dir_in2y", QString("%1").arg(config_struct[1].dx[3]));
                     writer.writeTextElement("Dir_in3x", QString("%1").arg(config_struct[1].dx[4]));
                     writer.writeTextElement("Dir_in3y", QString("%1").arg(config_struct[1].dx[5]));
                     writer.writeTextElement("Dir_in4x", QString("%1").arg(config_struct[1].dx[6]));
                     writer.writeTextElement("Dir_in4y", QString("%1").arg(config_struct[1].dx[7]));
                     writer.writeTextElement("Dir_in5x", QString("%1").arg(config_struct[1].dx[8]));
                     writer.writeTextElement("Dir_in5y", QString("%1").arg(config_struct[1].dx[9]));
                     writer.writeTextElement("Dir_in6x", QString("%1").arg(config_struct[1].dx[10]));
                     writer.writeTextElement("Dir_in6y", QString("%1").arg(config_struct[1].dx[11]));
                     writer.writeTextElement("Dir_in7x", QString("%1").arg(config_struct[1].dx[12]));
                     writer.writeTextElement("Dir_in7y", QString("%1").arg(config_struct[1].dx[13]));
                     writer.writeTextElement("Dir_in8x", QString("%1").arg(config_struct[1].dx[14]));
                     writer.writeTextElement("Dir_in8y", QString("%1").arg(config_struct[1].dx[15]));
                     writer.writeTextElement("Dir_in9x", QString("%1").arg(config_struct[1].dx[16]));
                     writer.writeTextElement("Dir_in9y", QString("%1").arg(config_struct[1].dx[17]));
                     writer.writeTextElement("Dir_in10x", QString("%1").arg(config_struct[1].dx[18]));
                     writer.writeTextElement("Dir_in10y", QString("%1").arg(config_struct[1].dx[19]));

                     writer.writeTextElement("setTimeHour",QString::number(config_struct[1].hour, 10));
                     writer.writeTextElement("setTimeMin", QString::number(config_struct[1].min, 10));
                     writer.writeTextElement("SocketClientIP", TYPE.stringToChar(config_struct[1].IPCore,sizeof( config_struct[1].IPCore)));
                     writer.writeTextElement("CorePath", TYPE.stringToChar(config_struct[1].corePath,100));
                     writer.writeTextElement("SavePicFlag", QString::number(config_struct[1].SavePicFlag, 10));
                     writer.writeTextElement("SavePicPrefix", TYPE.stringToChar(config_struct[1].SavePicPrefix,sizeof( config_struct[1].SavePicPrefix)));
                     writer.writeTextElement("SavePicPath", TYPE.stringToChar(config_struct[1].SavePicPath,sizeof( config_struct[1].SavePicPath)));
                     writer.writeTextElement("Order", QString::number(config_struct[1].order, 10));
                  writer.writeEndElement();

                  writer.writeStartElement("Camera2");
                      writer.writeTextElement("IP", TYPE.stringToChar(config_struct[2].IPCamera,sizeof( config_struct[2].IPCamera)));
                      writer.writeTextElement("Port", QString::number(config_struct[2].PortCamera, 10));
                      writer.writeTextElement("User", TYPE.stringToChar(config_struct[2].admin,sizeof( config_struct[2].admin)));
                      writer.writeTextElement("Code", TYPE.stringToChar(config_struct[2].code,sizeof( config_struct[2].code)));
                      writer.writeTextElement("Threshold", QString::number(config_struct[2].sense, 10));
                      writer.writeTextElement("Bound1x", QString("%1").arg(config_struct[2].x[0]));
                      writer.writeTextElement("Bound1y", QString("%1").arg(config_struct[2].x[1]));
                      writer.writeTextElement("Bound2x", QString("%1").arg(config_struct[2].x[2]));
                      writer.writeTextElement("Bound2y", QString("%1").arg(config_struct[2].x[3]));
                      writer.writeTextElement("Dir_in1x", QString("%1").arg(config_struct[2].dx[0]));
                      writer.writeTextElement("Dir_in1y", QString("%1").arg(config_struct[2].dx[1]));
                      writer.writeTextElement("Dir_in2x", QString("%1").arg(config_struct[2].dx[2]));
                      writer.writeTextElement("Dir_in2y", QString("%1").arg(config_struct[2].dx[3]));
                      writer.writeTextElement("setTimeHour",QString::number(config_struct[2].hour, 10));
                      writer.writeTextElement("setTimeMin", QString::number(config_struct[2].min, 10));
                      writer.writeTextElement("SocketClientIP", TYPE.stringToChar(config_struct[2].IPCore,sizeof( config_struct[2].IPCore)));
                      writer.writeTextElement("CorePath", TYPE.stringToChar(config_struct[2].corePath,100));
                      writer.writeTextElement("SavePicFlag", QString::number(config_struct[2].SavePicFlag, 2));
                      writer.writeTextElement("SavePicPrefix", TYPE.stringToChar(config_struct[2].SavePicPrefix,sizeof( config_struct[2].SavePicPrefix)));
                      writer.writeTextElement("SavePicPath", TYPE.stringToChar(config_struct[2].SavePicPath,sizeof( config_struct[2].SavePicPath)));
                      writer.writeTextElement("Order", QString::number(config_struct[2].order, 10));
                   writer.writeEndElement();


            writer.writeEndElement();
        writer.writeEndElement();
        file.close();
    }
    return 0;
}

int XmlContainer::readXml(struct Camera_config *read_struct)
{
    QDomDocument doc;
    QFile file("config.xml");
    QString error = "";
    bool ok;
    int row = 0, column = 0;
    if (!file.open(QIODevice::ReadOnly))
    {
        return -2;
    }

    if(!doc.setContent(&file, false, &error, &row, &column))
    {
        qDebug() << "parse file failed:" << row << "---" << column <<":" <<error;
        file.close();
        return -1;
    }

    file.close();
    QDomElement root = doc.documentElement();
    QDomNode node = root.firstChildElement();
    while(!node.isNull()) {
       QDomElement element = node.toElement(); // try to convert the node to an element.
       if(!element.isNull())
       {
                               if (element.tagName() == "Camera0")
                               {
                                    QDomNodeList list = element.childNodes();
                                    for(int index = 0; index < list.count(); index++)
                                    {
                                        QDomNode list_node = list.item(index);
                                        QDomElement list_element = list_node.toElement();
                                       if (list_element.tagName() =="IP") {
                                            read_struct[0].IPCamera=list_element.text().toStdString();
                                        }
                                       if (list_element.tagName() =="Port") {
                                           read_struct[0].PortCamera=list_element.text().toInt(&ok,10);
                                        }
                                       if (list_element.tagName() =="User") {
                                            read_struct[0].admin=list_element.text().toStdString();
                                        }
                                       if (list_element.tagName() =="Code") {
                                            read_struct[0].code=list_element.text().toStdString();
                                        }
                                       if (list_element.tagName() =="Threshold") {
                                           read_struct[0].sense=list_element.text().toInt(&ok,10);
                                        }
                                       if (list_element.tagName() =="SocketClientIP") {
                                            read_struct[0].IPCore=list_element.text().toStdString();
                                        }
                                       if (list_element.tagName() =="CorePath") {
                                            read_struct[0].corePath=list_element.text().toStdString();
                                        }
                                       if (list_element.tagName() =="SavePicFlag") {
                                           read_struct[0].SavePicFlag=list_element.text().toInt(&ok,10);
                                        }
                                       if (list_element.tagName() =="SavePicPrefix") {
                                            read_struct[0].SavePicPrefix=list_element.text().toStdString();
                                        }
                                       if (list_element.tagName() =="SavePicPath") {
                                            read_struct[0].SavePicPath=list_element.text().toStdString();
                                        }
                                       if (list_element.tagName() =="setTimeHour") {
                                            read_struct[0].hour=list_element.text().toInt(&ok,10);
                                        }
                                       if (list_element.tagName() =="setTimeMin") {
                                            read_struct[0].min=list_element.text().toInt(&ok,10);
                                        }
                                       if (list_element.tagName() =="Bound1x")        read_struct[0].x[0]=list_element.text().toFloat();
                                       if (list_element.tagName() =="Bound1y")        read_struct[0].x[1]=list_element.text().toFloat();
                                       if (list_element.tagName() =="Bound2x")        read_struct[0].x[2]=list_element.text().toFloat();
                                       if (list_element.tagName() =="Bound2y")        read_struct[0].x[3]=list_element.text().toFloat();
                                       if (list_element.tagName() =="Dir_in1x")         read_struct[0].dx[0]=list_element.text().toFloat();
                                       if (list_element.tagName() =="Dir_in1y")         read_struct[0].dx[1]=list_element.text().toFloat();
                                       if (list_element.tagName() =="Dir_in2x")         read_struct[0].dx[2]=list_element.text().toFloat();
                                       if (list_element.tagName() =="Dir_in2x")         read_struct[0].dx[3]=list_element.text().toFloat();

                                       if (list_element.tagName() =="Order") {
                                            read_struct[0].order=list_element.text().toInt(&ok,10);
                                        }


                                    }
                               }
                               if (element.tagName() == "Camera1")
                               {
                                    QDomNodeList list = element.childNodes();
                                    for(int index = 0; index < list.count(); index++)
                                    {
                                        QDomNode list_node = list.item(index);
                                        QDomElement list_element = list_node.toElement();
                                        if (list_element.tagName() =="IP") {
                                             read_struct[1].IPCamera=list_element.text().toStdString();
                                         }
                                        if (list_element.tagName() =="Port") {
                                            read_struct[1].PortCamera=list_element.text().toInt(&ok,10);
                                         }
                                        if (list_element.tagName() =="User") {
                                             read_struct[1].admin=list_element.text().toStdString();
                                         }
                                        if (list_element.tagName() =="Code") {
                                             read_struct[1].code=list_element.text().toStdString();
                                         }
                                        if (list_element.tagName() =="Threshold") {
                                            read_struct[1].sense=list_element.text().toInt(&ok,10);
                                         }
                                        if (list_element.tagName() =="SocketClientIP") {
                                             read_struct[1].IPCore=list_element.text().toStdString();
                                         }
                                        if (list_element.tagName() =="CorePath") {
                                             read_struct[1].corePath=list_element.text().toStdString();
                                         }
                                        if (list_element.tagName() =="SavePicFlag") {
                                            read_struct[1].SavePicFlag=list_element.text().toInt(&ok,10);
                                         }
                                        if (list_element.tagName() =="SavePicPrefix") {
                                             read_struct[1].SavePicPrefix=list_element.text().toStdString();
                                         }
                                        if (list_element.tagName() =="SavePicPath") {
                                             read_struct[1].SavePicPath=list_element.text().toStdString();
                                         }
                                        if (list_element.tagName() =="setTimeHour") {
                                             read_struct[1].hour=list_element.text().toInt(&ok,10);
                                         }
                                        if (list_element.tagName() =="setTimeMin") {
                                             read_struct[1].min=list_element.text().toInt(&ok,10);
                                         }
                                        if (list_element.tagName() =="Bound1x")        read_struct[1].x[0]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound1y")        read_struct[1].x[1]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound2x")        read_struct[1].x[2]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound2y")        read_struct[1].x[3]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound3x")        read_struct[1].x[4]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound3y")        read_struct[1].x[5]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound4x")        read_struct[1].x[6]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound4y")        read_struct[1].x[7]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound5x")        read_struct[1].x[8]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound5y")        read_struct[1].x[9]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound6x")        read_struct[1].x[10]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound6y")        read_struct[1].x[11]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound7x")        read_struct[1].x[12]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound7y")        read_struct[1].x[12]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound8x")        read_struct[1].x[14]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound8y")        read_struct[1].x[15]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound9x")        read_struct[1].x[16]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound9y")        read_struct[1].x[17]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound10x")        read_struct[1].x[18]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Bound10y")        read_struct[1].x[19]=list_element.text().toFloat();

                                        if (list_element.tagName() =="Dir_in1x")         read_struct[1].dx[0]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in1y")         read_struct[1].dx[1]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in2x")         read_struct[1].dx[2]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in2x")         read_struct[1].dx[3]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in3x")         read_struct[1].dx[4]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in3y")         read_struct[1].dx[5]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in4x")         read_struct[1].dx[6]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in4x")         read_struct[1].dx[7]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in5x")         read_struct[1].dx[8]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in5y")         read_struct[1].dx[9]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in6x")         read_struct[1].dx[10]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in6x")         read_struct[1].dx[11]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in7x")         read_struct[1].dx[12]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in7y")         read_struct[1].dx[13]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in8x")         read_struct[1].dx[14]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in8x")         read_struct[1].dx[15]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in9x")         read_struct[1].dx[16]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in9y")         read_struct[1].dx[17]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in10x")         read_struct[1].dx[18]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Dir_in10x")         read_struct[1].dx[319]=list_element.text().toFloat();
                                        if (list_element.tagName() =="Order") {
                                             read_struct[1].order=list_element.text().toInt(&ok,10);
                                         }
                                    }
                               }
                                           if (element.tagName() == "Camera2")
                                           {
                                                QDomNodeList list = element.childNodes();
                                                for(int index = 0; index < list.count(); index++)
                                                {
                                                    QDomNode list_node = list.item(index);
                                                    QDomElement list_element = list_node.toElement();
                                                    if (list_element.tagName() =="IP") {
                                                         read_struct[2].IPCamera=list_element.text().toStdString();
                                                     }
                                                    if (list_element.tagName() =="Port") {
                                                        read_struct[2].PortCamera=list_element.text().toInt(&ok,10);
                                                     }
                                                    if (list_element.tagName() =="User") {
                                                         read_struct[2].admin=list_element.text().toStdString();
                                                     }
                                                    if (list_element.tagName() =="Code") {
                                                         read_struct[2].code=list_element.text().toStdString();
                                                     }
                                                    if (list_element.tagName() =="Threshold") {
                                                        read_struct[2].sense=list_element.text().toInt(&ok,10);
                                                     }
                                                    if (list_element.tagName() =="SocketClientIP") {
                                                         read_struct[2].IPCore=list_element.text().toStdString();
                                                     }
                                                    if (list_element.tagName() =="CorePath") {
                                                         read_struct[2].corePath=list_element.text().toStdString();
                                                     }
                                                    if (list_element.tagName() =="SavePicFlag") {
                                                        read_struct[2].SavePicFlag=list_element.text().toInt(&ok,10);
                                                     }
                                                    if (list_element.tagName() =="SavePicPrefix") {
                                                         read_struct[2].SavePicPrefix=list_element.text().toStdString();
                                                     }
                                                    if (list_element.tagName() =="SavePicPath") {
                                                         read_struct[2].SavePicPath=list_element.text().toStdString();
                                                     }
                                                    if (list_element.tagName() =="setTimeHour") {
                                                         read_struct[2].hour=list_element.text().toInt(&ok,10);
                                                     }
                                                    if (list_element.tagName() =="setTimeMin") {
                                                         read_struct[2].min=list_element.text().toInt(&ok,10);
                                                     }
                                                    if (list_element.tagName() =="Bound1x") {
                                                         read_struct[2].x[0]=list_element.text().toFloat();
                                                     }
                                                    if (list_element.tagName() =="Bound1y") {
                                                         read_struct[2].x[1]=list_element.text().toFloat();
                                                     }
                                                    if (list_element.tagName() =="Bound2x") {
                                                         read_struct[2].x[2]=list_element.text().toFloat();
                                                     }
                                                    if (list_element.tagName() =="Bound2y") {
                                                         read_struct[2].x[3]=list_element.text().toFloat();
                                                     }
                                                    if (list_element.tagName() =="Dir_in1x") {
                                                         read_struct[2].dx[0]=list_element.text().toFloat();
                                                     }
                                                    if (list_element.tagName() =="Dir_in1y") {
                                                         read_struct[2].dx[1]=list_element.text().toFloat();
                                                     }
                                                    if (list_element.tagName() =="Dir_in2x") {
                                                         read_struct[2].dx[2]=list_element.text().toFloat();
                                                     }
                                                    if (list_element.tagName() =="Dir_in2x") {
                                                         read_struct[2].dx[3]=list_element.text().toFloat();
                                                     }
                                                    if (list_element.tagName() =="Order") {
                                                         read_struct[2].order=list_element.text().toInt(&ok,10);
                                                     }
                                                }
                                           }

       }
       node = node.nextSibling();
    }
    return 0 ;
}
