#include "xmlresolution.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QApplication>

XmlResolution::XmlResolution()
{

}

//bool isDirExist(QString fullPath)
//{
//    QDir dir(fullPath);
//    if(dir.exists())
//    {
//      return true;
//    }
//    else
//    {
//       bool ok = dir.mkpath(fullPath);//创建多级目录
//       return ok;
//    }
//}

void XmlResolution::xml(QString scanRes)
{
    QDomDocument doc;
    QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    QDomElement res = doc.createElement("result");   //添加子节点
    doc.appendChild(res);
    //任务信息
    QDomElement scheme = doc.createElement("scheme");
    res.appendChild(scheme);
    QDomElement task = doc.createElement("task_info");
    task.setAttribute("taskcode","1_1");     //设置子节点的属性和值
    scheme.appendChild(task);
    //主机信息
    QDomElement hostInfo = doc.createElement("host_info");
    res.appendChild(hostInfo);

    QDomElement hostname = doc.createElement("hostname");
    QDomText text_1 = doc.createTextNode(scanRes);
    hostname.appendChild(text_1);
    hostInfo.appendChild(hostname);

    QDomElement sysOs = doc.createElement("os");
    QDomText text_2 = doc.createTextNode(QString("Windows 7 32位"));
    sysOs.appendChild(text_2);
    hostInfo.appendChild(sysOs);

    QString localPath = qApp->applicationDirPath();
    localPath += "/xmlreport/";
//    isDirExist(localPath);
    localPath += "test.xml";
    QFile file(localPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate |QIODevice::Text))
    {
        qWarning()<<"open file fail ";
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    doc.save(out,4,QDomNode::EncodingFromTextStream);
    file.close();
}
