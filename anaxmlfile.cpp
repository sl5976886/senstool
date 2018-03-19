#include "anaxmlfile.h"
#include "global.h"
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include <QTextCodec>
#include <string>

AnaXmlFile::AnaXmlFile()
{
    qInstallMessageHandler(outputMessage);
}

std::string ConvertUtf8ToGBK2(std::string strUtf8)
{
    std::string strGBK;
    int len=MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, NULL,0);
    wchar_t * wszGBK = new wchar_t[len];
    memset(wszGBK,0,len);
    MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, wszGBK, len);

    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
    char *szGBK=new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte (CP_ACP, 0, wszGBK, -1, szGBK, len, NULL,NULL);

    strGBK = szGBK;
    delete[] szGBK;
    delete[] wszGBK;
    return strGBK;
}

void AnaXmlFile::anaXml(QString filePath)
{
    QDomDocument doc;
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qWarning()<<"analyze xml error!";
        return;
    }
    doc.setContent(&file);
    file.close();
    QDomElement docElem = doc.documentElement();
    QDomElement sensElement = docElem.firstChildElement();
    QDomNodeList nodeswitch=sensElement.elementsByTagName("item");
    SensRes mRes;
    sensResList.clear();
    for(int i=0;i<nodeswitch.count();i++)
    {
        QDomNode node = nodeswitch.item(i);
        QDomElement elemnodeswitch=node.toElement();
        //xml文件为uft8编码时，需要用qUtf8Printable函数确保中文不乱码
        QString strFile = qUtf8Printable(elemnodeswitch.attribute("filepath"));
        QString strKey = qUtf8Printable(elemnodeswitch.attribute("key"));
        mRes.filePath = strFile;
        mRes.keyWord = strKey;
        sensResList.append(mRes);
    }
}
