#include "mainwindow.h"
#include <QApplication>
#include <SingleApplication.h>
#include <QtDesigner/QDesignerExportWidget>
#include <QDir>
#include <QDebug>
#include <QSettings>
#include "ringsmapprogressbar.h"
#include "global.h"

int paraseCmd()
{
    QStringList arguments = QCoreApplication::arguments();
    int count = arguments.count();
    QString strArg;
    if(count<2)
    {
        qWarning()<<"arguments num error";
        return -1;
    }
    else
    {
        strArg = arguments[1];
    }
    if(strArg==QString("-grxaStart"))
    {
        return 0;
    }
    if(strArg==QString("-grhide"))
    {
        ifHide = true;
        return 1;
    }
    else
    {
        qWarning()<<"arguments error:"<<strArg;
        return -1;
    }
}

//bool writeStart()
//{
//    QString localPath = qApp->applicationDirPath();
//    localPath+="\\config.ini";
//    QSettings settings(localPath,QSettings::IniFormat);
//    settings.setIniCodec("utf-8");
//    settings.beginGroup("start");
//    settings.setValue("run","true");
//}

int main(int argc, char *argv[])
{
    if (QSysInfo::windowsVersion() == QSysInfo::WV_XP) {
      // 为了支持XP
      SingleApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    }
    SingleApplication ::addLibraryPath("./plugins");
    SingleApplication  a(argc,argv,true);
    if(paraseCmd()==-1)
    {
        return 0;
    }
    if(a.isSecondary())
    {
        a.sendMessage("test");
        qDebug()<<"send message";
        return 0;
    }
    MainWindow w;
    qInstallMessageHandler(outputMessage);
    QObject::connect(
        &a,
        SIGNAL(receivedMessage(quint32,QByteArray)),
        &w,
        SLOT(sltMessageReceived(quint32,QByteArray))
    );
//    QApplication::addLibraryPath("./plugins");
//    QApplication a(argc, argv);
//    MainWindow w;
    if(paraseCmd()==0)
    {
       w.show();
    }
    return a.exec();
}
