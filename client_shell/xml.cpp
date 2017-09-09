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
                     writer.writeTextElement("Dir_in1x", QString("%1").arg(config_struct[1].dx[0]));
                     writer.writeTextElement("Dir_in1y", QString("%1").arg(config_struct[1].dx[1]));
                     writer.writeTextElement("Dir_in2x", QString("%1").arg(config_struct[1].dx[2]));
                     writer.writeTextElement("Dir_in2y", QString("%1").arg(config_struct[1].dx[3]));
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
                                       if (list_element.tagName() =="Bound1x") {
                                            read_struct[0].x[0]=list_element.text().toFloat();
                                        }
                                       if (list_element.tagName() =="Bound1y") {
                                            read_struct[0].x[1]=list_element.text().toFloat();
                                        }
                                       if (list_element.tagName() =="Bound2x") {
                                            read_struct[0].x[2]=list_element.text().toFloat();
                                        }
                                       if (list_element.tagName() =="Bound2y") {
                                            read_struct[0].x[3]=list_element.text().toFloat();
                                        }
                                       if (list_element.tagName() =="Dir_in1x") {
                                            read_struct[0].dx[0]=list_element.text().toFloat();
                                        }
                                       if (list_element.tagName() =="Dir_in1y") {
                                            read_struct[0].dx[1]=list_element.text().toFloat();
                                        }
                                       if (list_element.tagName() =="Dir_in2x") {
                                            read_struct[0].dx[2]=list_element.text().toFloat();
                                        }
                                       if (list_element.tagName() =="Dir_in2x") {
                                            read_struct[0].dx[3]=list_element.text().toFloat();
                                        }
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
                                        if (list_element.tagName() =="Bound1x") {
                                             read_struct[1].x[0]=list_element.text().toFloat();
                                         }
                                        if (list_element.tagName() =="Bound1y") {
                                             read_struct[1].x[1]=list_element.text().toFloat();
                                         }
                                        if (list_element.tagName() =="Bound2x") {
                                             read_struct[1].x[2]=list_element.text().toFloat();
                                         }
                                        if (list_element.tagName() =="Bound2y") {
                                             read_struct[1].x[3]=list_element.text().toFloat();
                                         }
                                        if (list_element.tagName() =="Dir_in1x") {
                                             read_struct[1].dx[0]=list_element.text().toFloat();
                                         }
                                        if (list_element.tagName() =="Dir_in1y") {
                                             read_struct[1].dx[1]=list_element.text().toFloat();
                                         }
                                        if (list_element.tagName() =="Dir_in2x") {
                                             read_struct[1].dx[2]=list_element.text().toFloat();
                                         }
                                        if (list_element.tagName() =="Dir_in2x") {
                                             read_struct[1].dx[3]=list_element.text().toFloat();
                                         }
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
