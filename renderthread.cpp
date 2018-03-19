#include "renderthread.h"
#include "global.h"
#include "xmlhtml/Resource.h"
#include "xmlhtml/GrxaHostCheck.h"
#include "xmlhtml/CheckResultResouce.h"
#include "xmlhtml/result2html.h"
#include "xmlhtml/result2xml.h"
#include "checkhistory.h"
#include "clientmodule.h"
#include "WriteHtmlDll.h"
//#include "checkresultfromserver.h"
#include "testdirscan.h"
#include <QDir>
#include <QMessageBox>
#include <QSettings>
#include <QDomDocument>
#include <QDebug>
#include <QApplication>
#include <QLibrary>
#include <QSettings>
#include <QDateTime>
#include <QProcess>
#include <vector>
#include <QTextCodec>
#include <string>
#include <QDesktopServices>

typedef int (*SrchDiskExProcCallback)(void *pPara, void *pReserved);

typedef void (CALLMODE* SHOWPROGRESS)(int,__int64,__int64);
typedef void (CALLMODE* SETDATA)(vector<wstring>*,const WCHAR*);//不能在DLL赋值，需要回调（在主程序中赋值，否则，析构函数中释放会有问题）。
typedef void (CALLMODE* CHECKOVER)(int size,PCHECK_PARAM pCheckParam);//size 检查项目数,pCheckParam 检查项目存放结果数组


RenderThread::RenderThread(QObject *parent) : QThread(parent)
{
    stopped = false;
    qInstallMessageHandler(outputMessage);
    qDebug() << "RenderThread::RenderThread()";
}

RenderThread::~RenderThread()
{
    qDebug() << "RenderThread::~RenderThread()";
}

void RenderThread::test()
{
    stopped = false;
    start(HighestPriority);
}

void RenderThread::stop()
{
    stopped = true;
}


bool Write2Xml(char *szXml)
{
    char *pXmlResult;
    int xmlResultLen;
    if (0 == WriteDjjcResult2Memory(E_TP_WINDOWS, &pXmlResult, xmlResultLen))
    {
        FILE *pf = fopen(szXml, "w");
        fwrite(pXmlResult, 1, xmlResultLen, pf);
        fclose(pf);

        FreeMemoryBuf(&pXmlResult);
        return true;
    }

    return false;
}

bool isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
      return true;
    }
    else
    {
       bool ok = dir.mkpath(fullPath);//创建多级目录
       return ok;
    }
}


//int RenderThread::CallBackFunc(void *pPara, void *pReserved)     //检查文件内容的回调
//{
//    Q_UNUSED(pPara);
//    Q_UNUSED(pReserved);
//    isChecked=1;
//    return 0;
//}

void copyResult(vector<wstring>& result,int type)
{
    if(type==QCHECK_USB)
    {
        usbResList.clear();
        for(int i=0;i<(int)result.size();i++)
        {
            WCHAR* wsz=(WCHAR*)result[i].c_str();
            QString strWsz = QString::fromWCharArray(wsz);
            usbResList.append(strWsz);
        }
    }
    else if(type==QCHECK_INTERNET)
    {
        internetResList.clear();
        for(int i=0;i<(int)result.size();i++)
        {
            WCHAR* wsz=(WCHAR*)result[i].c_str();
            QString strWsz = QString::fromWCharArray(wsz);
            internetResList.append(strWsz);
        }
    }
    else if(type==QCHECK_FILE_OPEND)
    {
        wjczResList.clear();
        for(int i=0;i<(int)result.size();i++)
        {
            WCHAR* wsz=(WCHAR*)result[i].c_str();
            QString strWsz = QString::fromWCharArray(wsz);
            wjczResList.append(strWsz);
        }
    }
}

void CALLMODE CheckOver(int nItems,PCHECK_PARAM pCheckParam)   //深度检查回调函数
{
    qDebug()<<"deepTask finish";
    for(int i=0;i<nItems;i++)
    {
        if(pCheckParam[i].type==QCHECK_USB)
        {
            ifUsbFinish = true;
        }
        else if(pCheckParam[i].type==QCHECK_INTERNET)
        {
            ifIntFinish = true;
        }
        else if(pCheckParam[i].type==QCHECK_FILE_OPEND)
        {
            wjczFinish = true;
        }
        if(pCheckParam)
        {
            if(pCheckParam[i].pVectorResult)
            {
                copyResult(*pCheckParam[i].pVectorResult,pCheckParam[i].type);
                delete pCheckParam[i].pVectorResult;
            }
            if(pCheckParam[i].pVectorParam)
            {
                delete pCheckParam[i].pVectorParam;//赋值时，new 单个对象。
            }
        }
    }
    ifDeepFinish = true;

    if(ifDeep==1&&haveSensTask==false)
    {
        //生成报告
        QString localPath_2 = qApp->applicationDirPath();
        localPath_2 += "/report";
        isDirExist(localPath_2);
        if(!ifFromServer)
        {
            localPath_2 += QString("/myxml.xml");
        }
        else
        {
            localPath_2 += QString("/myxmlfromserver.xml");
        }
        QByteArray ba_2 = localPath_2.toLatin1();
        char *c_str_2 = ba_2.data();
        Write2Xml(c_str_2);

        QString localPath_3 = qApp->applicationDirPath();
        localPath_3 += "/report";
        if(!ifFromServer)
        {
            localPath_3 += "/myhtml.html";
        }
        else
        {
            localPath_3 += "/myhtmlfromserver.html";
        }
//        QByteArray ba_3 = localPath_3.toLatin1();
//        char *c_str_3 = ba_3.data();
//        WriteHtml(c_str_3);

        qDebug()<<"CheckOver id:"<<id;
        NtCrsSntdFele(c_str_2,id);
        isChecked = 1;
        ifFromServer = false;
    }
    else if(ifDeep==1&&haveSensTask==true)    //有敏感词检查任务
    {
        ifDeepFinish = true;
    }
    else
    {
        isChecked = 1;
    }

}

void CALLMODE SetDataW(vector<wstring>* pVector,const WCHAR* pData)
{
    if(pVector)
    {
        pVector->push_back(pData);
    }
}


void CALLMODE ShowProgress(int index,__int64 totalSize,__int64 currentSize)
{
    gTotalSize = totalSize;
    gCurrSize = currentSize;
    Q_UNUSED(index);
}

void writeSettingFile()
{
    QString localPath = qApp->applicationDirPath();
    localPath+="\\config.ini";
    QSettings settings(localPath,QSettings::IniFormat);
    settings.setIniCodec("utf-8");
    settings.beginGroup("result");

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");

    settings.setValue("time",current_date);
    QString strDengb,strWl,strUsb,strAll;
    int all = 0;
    strDengb = QString("不合规");
    all++;
    if(CheckResultResouce::pFirefoxHistory!=NULL||CheckResultResouce::pChromeHistory!=NULL)
    {
        strWl = QString("有");
        all++;
    }
    else
    {
        strWl = QString("没有");
    }
    if(CheckResultResouce::pUsbHistory!=NULL)
    {
        strUsb = QString("有");
        all++;
    }
    else
    {
        strUsb = QString("没有");
    }
    strAll = QString::number(all,10);
    settings.setValue("hegui",strDengb);
    settings.setValue("wailian",strWl);
    settings.setValue("usb",strUsb);
    settings.setValue("all",strAll);
    settings.endGroup();
}

inline QString UTF82GBK(const QString &inStr)
{
    QTextCodec *gbk = QTextCodec::codecForName("GB2312");
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

    QString utf2gbk = gbk->toUnicode(inStr.toLocal8Bit());
    return utf2gbk;
}

std::string ConvertUtf8ToGBK(std::string strUtf8)
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

void analyzeTask(char *taskConf,int &ifDeep)
{
    ifDeep = 0;
    QString strCmd;
    if(taskConf)
    {
        strCmd = QString::fromLocal8Bit(taskConf);     //将来会改成从服务端接收到的指令
    }
    else
    {
        qWarning()<<"taskConf is NULL!";
        return;
    }
    ifHgFinish = false;
    QStringList cmdList = strCmd.split(",");
    if(!cmdList.isEmpty())
    {
        HostCheckUnInit();
        QString localPath = qApp->applicationDirPath();
        localPath+="/config/grxalog.grxa";
        QByteArray ba = localPath.toLatin1();
        char *c_str2 = ba.data();
        if (!HostCheckInit(c_str2))
        {
            qWarning()<<"HostCheckInit error";
            ifHgFinish = true;
            return;
        }
        //注：以下检查为生成xml文档需要，如果去掉可能导致生成xml时程序崩溃！
        CheckResultResouce::pSnmpService = NULL;

        // 审计策略
        CheckResultResouce::pAuditPolicy = NULL;
        CheckResultResouce::auditNum = 0;
        // 系统访问策略
        CheckResultResouce::pSystemAccess = NULL;
        CheckResultResouce::systemNum = 0;

        // 用户权利指派
        CheckResultResouce::pUserRightsAssignments = NULL;

        CheckResultResouce::pOsVersion = NULL;

        CheckResultResouce::pUsbHistory = NULL;

        CheckResultResouce::pIeHistory = NULL;

        CheckResultResouce::pFirefoxHistory = NULL;

        CheckResultResouce::pChromeHistory = NULL;

        CheckResultResouce::pSystemDefectInfo = NULL;

        CheckResultResouce::pRunItems = NULL;

        CheckResultResouce::pPolicyBuf = NULL;

        CheckResultResouce::pGroupPolicy = NULL;
        CheckResultResouce::groupPolicyNum = 0;

        CheckResultResouce::pUserInfo = NULL;
        CheckResultResouce::usersNum = 0;
        CheckResultResouce::pShareInfo = NULL;
        CheckResultResouce::shareNum = 0;

        CheckResultResouce::pServiceStatus = NULL;
        CheckResultResouce::servicesNum =0;

        CheckResultResouce::computerName = 0;

        CheckResultResouce::pSoft = NULL;
        CheckResultResouce::softNum =0;

        CheckResultResouce::pProcess = NULL;
        CheckResultResouce::processNum = 0;

        CheckResultResouce::pAntivirusSoft = NULL;
        CheckResultResouce::antivirusSoftNum = 0;
        CheckResultResouce::pBootTime = NULL;

        CheckResultResouce::pBiosInfo = NULL;

        CheckResultResouce::pLogicDrives = NULL;
        CheckResultResouce::logicDrivesNum = 0;
        CheckResultResouce::pDrivesRights = NULL;
        CheckResultResouce::drivesRightsNum = 0;
        CheckResultResouce::pSystemRights = NULL;
        CheckResultResouce::systemRightsNum = 0;
        CheckResultResouce::pCpuInfo = NULL;

        CheckResultResouce::pHardDisk = NULL;
        CheckResultResouce::diskNum = 0;
        CheckResultResouce::pBoardInfo = NULL;

        CheckResultResouce::pDisplayCard = NULL;
        CheckResultResouce::pMemory = NULL;
        CheckResultResouce::pAudio = NULL;

        CheckResultResouce::pNetwork = NULL;
        CheckResultResouce::netcardNum = 0;
        CheckResultResouce::pSecurityOpt = NULL;
        CheckResultResouce::secOptionsNum = 0;
        CheckResultResouce::pRegistrySets = NULL;
        CheckResultResouce::regOptionsNum = 0;

        CheckResultResouce::pEventlogs = NULL;
        CheckResultResouce::eventlogNum = 0;

        CheckResultResouce::pPortInfo = NULL;

        CheckResultResouce::pDtckResults = NULL;

        // 密码策略
        CheckResultResouce::pDtPwdPolicy = NULL;

        // 审核策略
        CheckResultResouce::pDtAuditPolicy = NULL;

        // 访问控制策略
        CheckResultResouce::pDtAccLockPolicy = NULL;
        // 用户权限分配
        CheckResultResouce::pDtUserRightAssignment = NULL;

        // 自动登录
        CheckResultResouce::pDtAutoAdminLogin = NULL;

        // 驱动器自动运行
        CheckResultResouce::pDtDriverAutoOperation = NULL;

        // dump文件
        CheckResultResouce::pDtMakeDumpFile = NULL;

        // 网络连接
        CheckResultResouce::pDtNetConnect = NULL;

        // 组策略
        CheckResultResouce::pDtGroupPolicy = NULL;

        //正在获取操作系统版本
        CheckResultResouce::pOsVersion = NULL;
        CheckResultResouce::pOsVersion = GetOsVersionInfo();

        //获取用户信息
        CheckResultResouce::pUserInfo = NULL;
        CheckResultResouce::usersNum = GetNetUsers(&CheckResultResouce::pUserInfo);

        //共享信息
        CheckResultResouce::pShareInfo = NULL;
        CheckResultResouce::shareNum = 0;
        CheckResultResouce::shareNum = GetNetshare(&CheckResultResouce::pShareInfo);

        //服务
        CheckResultResouce::pServiceStatus = NULL;
        CheckResultResouce::servicesNum = GetServices(&CheckResultResouce::pServiceStatus);

        //补丁
        CheckResultResouce::pSystemDefectInfo = NULL;
        CheckResultResouce::pSystemDefectInfo = GetHotfixesInfoWUAInstall();

        //启动项
        CheckResultResouce::pRunItems = NULL;

        if(cmdList.contains(QString("hgjc")))   //合规检查
        {
           ifPolicyXml = true;

           CheckResultResouce::pSoft = NULL;
           CheckResultResouce::softNum = GetSoftWareInfo(&CheckResultResouce::pSoft);
           CheckResultResouce::pProcess = NULL;
           CheckResultResouce::processNum = GetProcessInfo(&CheckResultResouce::pProcess);
           // 杀毒软件，是从软件列表中筛选的，状态是从进程中获取，需要先获取已安装的软件和进程
           CheckResultResouce::pAntivirusSoft = NULL;
           CheckResultResouce::antivirusSoftNum = GetViruslibraryUupdateTime(CheckResultResouce::pSoft, CheckResultResouce::softNum,
                                                                         CheckResultResouce::pProcess,CheckResultResouce::processNum,
                                                                         &CheckResultResouce::pAntivirusSoft);

           //共享文件
           CheckResultResouce::pShareInfo = NULL;
           CheckResultResouce::shareNum = 0;
           CheckResultResouce::shareNum = GetNetshare(&CheckResultResouce::pShareInfo);

           // 审计策略
           CheckResultResouce::pAuditPolicy =NULL;
           CheckResultResouce::auditNum = 0;
           GetAuditPolicy(&CheckResultResouce::pAuditPolicy, CheckResultResouce::auditNum);
           // 系统访问策略
           CheckResultResouce::pSystemAccess = NULL;
           CheckResultResouce::systemNum = 0;
           GetSystemAccessPolicy(&CheckResultResouce::pSystemAccess, CheckResultResouce::systemNum);
           // 用户权利指派
           CheckResultResouce::pUserRightsAssignments=NULL;
           CheckResultResouce::userRightsNum=0;
           GetUserRightsAssignment(&CheckResultResouce::pUserRightsAssignments, CheckResultResouce::userRightsNum);

           CheckResultResouce::pOsVersion=NULL;
           CheckResultResouce::pOsVersion = GetOsVersionInfo();

           // 密码策略及账号锁定
           CheckResultResouce::pPolicyBuf=NULL;
           CheckResultResouce::pPolicyBuf = GetSecurityPolicy();

           // 组策略
           CheckResultResouce::groupPolicyNum =0;
           CheckResultResouce::pGroupPolicy=NULL;
           CheckResultResouce::groupPolicyNum = GetGroupPolicyResult(&CheckResultResouce::pGroupPolicy);

           // 服务
           CheckResultResouce::servicesNum=0;
           CheckResultResouce::pServiceStatus=NULL;
           CheckResultResouce::servicesNum = GetServices(&CheckResultResouce::pServiceStatus);

           // 系统安装时间

           CheckResultResouce::osInstallTime = GetOsTimeInfo();

           //主机名

           CheckResultResouce::computerName = GetNameOfComputer();

           //安全选项
           CheckResultResouce::pSecurityOpt=NULL;
           CheckResultResouce::secOptionsNum=0;
           CheckResultResouce::secOptionsNum = GetSecurityOptionsValue(&CheckResultResouce::pSecurityOpt);

           // 等保检查项
           CheckResultResouce::pDtckResults=NULL;
           CheckResultResouce::pDtckResults = GetDtckResults();

           // 密码策略
           CheckResultResouce::pDtPwdPolicy=NULL;
           CheckResultResouce::pDtPwdPolicy = GetDtckResultsPwdPolicy();

           // 审核策略
           CheckResultResouce::pDtAuditPolicy=NULL;
           CheckResultResouce::pDtAuditPolicy = GetDtckResultsAuditPolicy();

           // 访问控制策略
           CheckResultResouce::pDtAccLockPolicy =NULL;
           CheckResultResouce::pDtAccLockPolicy = GetDtckResultsAccLockPolicy();

           // 用户权限分配
           CheckResultResouce::pDtUserRightAssignment=NULL;
           CheckResultResouce::pDtUserRightAssignment = GetDtckResultsUserRightAssignment();

           // 自动登录
           CheckResultResouce::pDtAutoAdminLogin=NULL;
           CheckResultResouce::pDtAutoAdminLogin = GetDtckResultsAutoAdminLogin();

           // 驱动器自动运行
           CheckResultResouce::pDtDriverAutoOperation=NULL;
           CheckResultResouce::pDtDriverAutoOperation = GetDtckResultsDriverAutoOperation();

           // dump文件
           CheckResultResouce::pDtMakeDumpFile=NULL;
           CheckResultResouce::pDtMakeDumpFile = GetDtckResultsMakeDumpFile();

           // 网络连接
           CheckResultResouce::pDtNetConnect=NULL;
           CheckResultResouce::pDtNetConnect = GetDtckResultsNetConnect();

           // 组策略
           CheckResultResouce::pDtGroupPolicy=NULL;
           CheckResultResouce::pDtGroupPolicy = GetDtckResultsGroupPolicy();
        }
        if(cmdList.contains(QString("wgwl-usb1")))
        {
            CheckResultResouce::pUsbHistory = NULL;
            CheckResultResouce::pUsbHistory = GetUsbUseHistory();

        }
        if(cmdList.contains(QString("wgwl-llq1")))
        {
            CheckResultResouce::pIeHistory = NULL;
            CheckResultResouce::pIeHistory = GetIeAccessHistory();
            CheckResultResouce::pFirefoxHistory = NULL;
            CheckResultResouce::pFirefoxHistory = GetFirefoxHistory();
            CheckResultResouce::pChromeHistory = NULL;
            CheckResultResouce::pChromeHistory = GetChromeHistory();
        }
        if(cmdList.contains(QString("mgxx")))   //敏感信息检查
        {
            haveSensTask = true;
            ifSens = 1;
            DbTaskScanDisk tExt;
            memset(&tExt, 0, sizeof(tExt));
            tExt.nID = 1001;
#ifdef DEBUGTEST
            strcpy(tExt.strDir,"D:\\test");
            strcpy(tExt.strKeys,"核武器;十八大;金正恩;奥巴马;泄密;测试;飞虎队;中国政府;抢劫;暴力;游行示威;西藏;东突组织;基地组织;钓鱼岛;南海;楼市;利息;信息系统;密钥;漏洞");
#else
            QString qDir = keyWordList[1];
//            QString qDir = "D:\\test";
            QString qKeys = keyWordList[0];
            std::string cKeys = qKeys.toStdString();
            cKeys = ConvertUtf8ToGBK(cKeys);
            qKeys = QString::fromStdString(cKeys);
            qKeys += ";核武器;十八大;金正恩;奥巴马;泄密;飞虎队;中国政府;抢劫;暴力;游行示威;西藏;东突组织;基地组织;钓鱼岛;南海;";
//            qDebug()<<"before keyword is: "<<qKeys;
            QByteArray ba = qDir.toLocal8Bit();
            char *mid_1 = ba.data();
            strcpy(tExt.strDir,mid_1);
            QByteArray ba_3 = qKeys.toLocal8Bit();
            char *mid_2 = ba_3.data();
//            qDebug()<<"keyword is: "<<mid_2;
            strcpy(tExt.strKeys,mid_2);
            keyWordList.clear();
#endif

            QString strPath = qApp->applicationDirPath();
            strPath +="\\sssens\\TestS.exe";

            QString tmpPath = QString(strPath);

            bool ok = QProcess::startDetached(tmpPath,QStringList());
            //bool bret = true;
            if (ok)
            {
                TxHead txhead;
                memset(&txhead, 0, sizeof(txhead));
                txhead.m_uDstApp = APP_SEARCHDISK;
                txhead.m_uMsgLen = sizeof(DbTaskScanDisk);
                txhead.m_uMsgType = MS_SEARCHDISK_BEGIN;

                char buffer[0xffff] = {0};
                memcpy(buffer, &txhead, sizeof(TxHead));
                memcpy(buffer + sizeof(TxHead), &tExt, sizeof(DbTaskScanDisk));
                USHORT len = sizeof(TxHead) + sizeof(DbTaskScanDisk);
                g_tTestDirScan.PushDataToApp(APP_SEARCHDISK, buffer, len, true);
            }
        }
        if(cmdList.contains(QString("zdxx")))
        {
            // snmp
            CheckResultResouce::pSnmpService = NULL;
            CheckResultResouce::pSnmpService = GetSnmpInfo();
            // 审计策略
            CheckResultResouce::pAuditPolicy = NULL;
            CheckResultResouce::auditNum = 0;
            GetAuditPolicy(&CheckResultResouce::pAuditPolicy, CheckResultResouce::auditNum);
            // 系统访问策略
            CheckResultResouce::pSystemAccess = NULL;
            CheckResultResouce::systemNum = 0;
            GetSystemAccessPolicy(&CheckResultResouce::pSystemAccess, CheckResultResouce::systemNum);
            // 用户权利指派
            CheckResultResouce::pUserRightsAssignments = NULL;
            CheckResultResouce::userRightsNum = 0;
            GetUserRightsAssignment(&CheckResultResouce::pUserRightsAssignments, CheckResultResouce::userRightsNum);
//            GetSecEditItemResult2(&CheckResultResouce::pAuditPolicy, CheckResultResouce::auditNum,
//                                &CheckResultResouce::pSystemAccess, CheckResultResouce::systemNum);

            int m = sizeof(CheckResultResouce::szDns);
            memset(CheckResultResouce::szDns,0,512);
            GetDNSInfo(CheckResultResouce::szDns,m);
            qDebug()<<"GetDNSInfo return:"<<m;

            CheckResultResouce::pSystemDefectInfo = NULL;
            CheckResultResouce::pSystemDefectInfo = GetHotfixesInfoWUAInstall();
            CheckResultResouce::pRunItems = NULL;
            CheckResultResouce::pRunItems = GetRunItemsInfo();
            CheckResultResouce::pPolicyBuf = NULL;
            CheckResultResouce::pPolicyBuf = GetSecurityPolicy();
            CheckResultResouce::pGroupPolicy = NULL;
            CheckResultResouce::groupPolicyNum = GetGroupPolicyResult(&CheckResultResouce::pGroupPolicy);
//            scanProject = QString("正在获取用户权利指派");
//            CheckResultResouce::userRightsNum = GetUserRightsAssignments(&CheckResultResouce::pUserRightsAssignments);
            CheckResultResouce::pShareInfo = NULL;
            CheckResultResouce::shareNum = 0;
            CheckResultResouce::shareNum = GetNetshare(&CheckResultResouce::pShareInfo);
            CheckResultResouce::pServiceStatus = NULL;
            CheckResultResouce::servicesNum = GetServices(&CheckResultResouce::pServiceStatus);
            CheckResultResouce::osInstallTime = GetOsTimeInfo();
            CheckResultResouce::computerName = NULL;
            CheckResultResouce::computerName = GetNameOfComputer();
            CheckResultResouce::pSoft = NULL;
            CheckResultResouce::softNum = GetSoftWareInfo(&CheckResultResouce::pSoft);
            CheckResultResouce::pProcess = NULL;
            CheckResultResouce::processNum = GetProcessInfo(&CheckResultResouce::pProcess);
            // 杀毒软件，是从软件列表中筛选的，状态是从进程中获取，需要先获取已安装的软件和进程
            CheckResultResouce::pAntivirusSoft = NULL;
            CheckResultResouce::antivirusSoftNum = GetViruslibraryUupdateTime(CheckResultResouce::pSoft, CheckResultResouce::softNum,
                                                                          CheckResultResouce::pProcess,CheckResultResouce::processNum,
                                                                          &CheckResultResouce::pAntivirusSoft);
            CheckResultResouce::pBootTime = NULL;
            CheckResultResouce::pBootTime = GetSysBootTime();
            CheckResultResouce::pBiosInfo = NULL;
            CheckResultResouce::pBiosInfo = GetBiosInfo();
            CheckResultResouce::pLogicDrives = NULL;
            CheckResultResouce::logicDrivesNum = GetLogicalDrivesInfo(&CheckResultResouce::pLogicDrives);
            CheckResultResouce::pDrivesRights = NULL;
            CheckResultResouce::drivesRightsNum = GetDrivesAccountRights(&CheckResultResouce::pDrivesRights);
            CheckResultResouce::pSystemRights = NULL;
            CheckResultResouce::systemRightsNum = GetSystemAccountRights(&CheckResultResouce::pSystemRights);
            CheckResultResouce::pCpuInfo = NULL;
            CheckResultResouce::pCpuInfo = GetCPUInfo();
            CheckResultResouce::pHardDisk = NULL;
            CheckResultResouce::diskNum = GetHardDiskInfo(&CheckResultResouce::pHardDisk);
            CheckResultResouce::pBoardInfo = NULL;
            CheckResultResouce::pBoardInfo = GetBoardInfo();
            CheckResultResouce::pDisplayCard = NULL;
            CheckResultResouce::pDisplayCard = GetDisplayInfo();
            CheckResultResouce::pMemory = NULL;
            CheckResultResouce::pMemory = GetMemoryInfo();
            CheckResultResouce::pAudio = NULL;
            CheckResultResouce::pAudio = GetAudioInfo();
            CheckResultResouce::pNetwork = NULL;
            CheckResultResouce::netcardNum = GetNetworkCardInfo(&CheckResultResouce::pNetwork);
            CheckResultResouce::pSecurityOpt = NULL;
            CheckResultResouce::secOptionsNum = GetSecurityOptionsValue(&CheckResultResouce::pSecurityOpt);
            CheckResultResouce::pRegistrySets = NULL;
            CheckResultResouce::regOptionsNum = GetRegistrySetsOptionsValue(&CheckResultResouce::pRegistrySets);
            CheckResultResouce::pEventlogs = NULL;
            CheckResultResouce::eventlogNum = GetEventlogsOptionsValue(&CheckResultResouce::pEventlogs);
            CheckResultResouce::pPortInfo = NULL;
            CheckResultResouce::pPortInfo = GetPort();
        }
        if(cmdList.contains(QString("bdxx")))
        {
            //补丁信息
            CheckResultResouce::pSystemDefectInfo = NULL;
            CheckResultResouce::pSystemDefectInfo = GetHotfixesInfoWUAInstall();
        }
        int num = 0;
        if(cmdList.contains(QString("wgwl-usb2")))
        {
            num++;
            ifDeep=1;
            ifDeepFinish = false;
        }
        if(cmdList.contains(QString("wgwl-llq2")))
        {
            num++;
            ifDeep=1;
            ifDeepFinish = false;
        }
        if(num==1)
        {
            if(cmdList.contains(QString("wgwl-usb2")))
            {
                PCHECK_PARAM pCP=new CHECK_PARAM;
                memset(pCP,0,sizeof(CHECK_PARAM));

                pCP->type=QCHECK_USB;
                pCP->pVectorResult=new vector<wstring>();
                pCP->pVectorParam=NULL;
                CheckOneWDeep(1,pCP,CheckOver,SetDataW,ShowProgress,TRUE);
            }
            else
            {
                PCHECK_PARAM pCP=new CHECK_PARAM;
                memset(pCP,0,sizeof(CHECK_PARAM));

                pCP->type=QCHECK_INTERNET;
                pCP->pVectorResult=new vector<wstring>();
                pCP->pVectorParam=NULL;
                CheckOneWDeep(1,pCP,CheckOver,SetDataW,ShowProgress,TRUE);
            }
        }
        else if(num==2)
        {
            PCHECK_PARAM pCP=new CHECK_PARAM[2];
            memset(pCP,0,sizeof(CHECK_PARAM)*2);

            pCP[0].type=QCHECK_USB;
            pCP[0].pVectorResult=new vector<wstring>();
            pCP[0].pVectorParam=NULL;

            pCP[1].type=QCHECK_INTERNET;
            pCP[1].pVectorResult=new vector<wstring>();
            pCP[1].pVectorParam=NULL;

            CheckOneWDeep(2,pCP,CheckOver,SetDataW,ShowProgress,TRUE);
        }
    }
    ifHgFinish = true;
}

//void RenderThread::report_slot()
//{
//    if(isChecked==1)
//    {
//        //生成报告
//        QString localPath_2 = qApp->applicationDirPath();
//        localPath_2 += "/report";
//        isDirExist(localPath_2);
//        localPath_2 += QString("/%1.xml").arg(id);
//        QByteArray ba_2 = localPath_2.toLatin1();
//        char *c_str_2 = ba_2.data();
//        Write2Xml(c_str_2);

////        QString localPath_3 = qApp->applicationDirPath();
////        localPath_3 += "/report";
////        localPath_3 += "/myhtml.html";
////        QByteArray ba_3 = localPath_3.toLatin1();
////        char *c_str_3 = ba_3.data();
////        WriteHtml(c_str_3);

//        NtCrsSntdFele(c_str_2,id);
//    }
//}

void RenderThread::run()
{
    while(!stopped)
    {
        isChecked=0;
        if(num==0)     //获取系统补丁
        {
            ReleaseHotfixesInfoWUA();
            QString localPath = qApp->applicationDirPath();
            localPath+="/config/grxalog.grxa";
            QByteArray ba = localPath.toLatin1();
            char *c_str2 = ba.data();
            if (!HostCheckInit(c_str2))
            {
                qWarning()<<"HostCheckInit error";
                isChecked=1;
                return;
            }
            CheckResultResouce::pSystemDefectInfo = GetHotfixesInfoWUAInstall();
            isChecked=1;     
            break;
        }
        else if(num==1)   //获取已安装程序
        {
            //HostCheckUnInit();
            QString localPath = qApp->applicationDirPath();
            localPath+="/config/grxalog.grxa";
            QByteArray ba = localPath.toLatin1();
            char *c_str2 = ba.data();
            if (!HostCheckInit(c_str2))
            {
                qWarning()<<"HostCheckInit error";
                isChecked=1;
                return;
            }
            CheckResultResouce::softNum = GetSoftWareInfo(&CheckResultResouce::pSoft);
            isChecked=1;

            break;
        }
        else if(num==2)   //获取硬件信息
        {
            //HostCheckUnInit();
            QString localPath = qApp->applicationDirPath();
            localPath+="/config/grxalog.grxa";
            QByteArray ba = localPath.toLatin1();
            char *c_str2 = ba.data();
            if (!HostCheckInit(c_str2))
            {
                qWarning()<<"HostCheckInit error";
                isChecked=1;
                return;
            }
            CheckResultResouce::pCpuInfo = GetCPUInfo();
            CheckResultResouce::diskNum = GetHardDiskInfo(&CheckResultResouce::pHardDisk);
            CheckResultResouce::pBoardInfo = GetBoardInfo();
            CheckResultResouce::pDisplayCard = GetDisplayInfo();
            CheckResultResouce::pMemory = GetMemoryInfo();
            CheckResultResouce::pAudio = GetAudioInfo();
            CheckResultResouce::netcardNum = GetNetworkCardInfo(&CheckResultResouce::pNetwork);
            isChecked=1;

            break;
        }
        else if(num==3)  //获取共享目录
        {
            ReleaseNetshare();
            QString localPath = qApp->applicationDirPath();
            localPath+="/config/grxalog.grxa";
            QByteArray ba = localPath.toLatin1();
            char *c_str2 = ba.data();
            if (!HostCheckInit(c_str2))
            {
                qWarning()<<"HostCheckInit error";
                isChecked=1;
                return;
            }
            CheckResultResouce::pShareInfo = NULL;
            CheckResultResouce::shareNum = 0;
            CheckResultResouce::shareNum = GetNetshare(&CheckResultResouce::pShareInfo);
            isChecked=1;

            break;
        }
        else if(num==4)  //系统配置
        {
//            HostCheckUnInit();
            QString localPath = qApp->applicationDirPath();
            localPath+="/config/grxalog.grxa";
            QByteArray ba = localPath.toLatin1();
            char *c_str2 = ba.data();
            if (!HostCheckInit(c_str2))
            {
                qWarning()<<"HostCheckInit error";
                isChecked=1;
                return;
            }
            CheckResultResouce::secOptionsNum = GetSecurityOptionsValue(&CheckResultResouce::pSecurityOpt);
            isChecked=1;

            break;
        }
        else if(num==5)  //违规外联
        {
            ReleaseIeAccessHistory();
            ReleaseFireFoxHistory();
            ReleaseChromeHistory();
            QString localPath = qApp->applicationDirPath();
            localPath+="/config/grxalog.grxa";
            QByteArray ba = localPath.toLatin1();
            char *c_str2 = ba.data();
            if (!HostCheckInit(c_str2))
            {
                qWarning()<<"HostCheckInit error";
                isChecked=1;
                return;
            }
            CheckResultResouce::pIeHistory = GetIeAccessHistory();
            CheckResultResouce::pFirefoxHistory = GetFirefoxHistory();
            CheckResultResouce::pChromeHistory = GetChromeHistory();
            isChecked=1;
            break;
        }
        else if(num==6)    //移动介质
        {
            ReleaseUsbUseHistory();
            QString localPath = qApp->applicationDirPath();
            localPath+="/config/grxalog.grxa";
            QByteArray ba = localPath.toLatin1();
            char *c_str2 = ba.data();
            if (!HostCheckInit(c_str2))
            {
                qWarning()<<"HostCheckInit error";
                isChecked=1;
                return;
            }
            CheckResultResouce::pUsbHistory = GetUsbUseHistory();
            isChecked=1;
            break;
        }
        else if(num==21)    //等保检查
        {
            ReleaseDtckResults();
            QString localPath = qApp->applicationDirPath();
            localPath+="/config/grxalog.grxa";
            QByteArray ba = localPath.toLatin1();
            char *c_str2 = ba.data();
            if (!HostCheckInit(c_str2))
            {
                qWarning()<<"HostCheckInit error";
                isChecked=1;
                return;
            }
//            CheckResultResouce::pDtckResults = GetDtckResults();
            CheckResultResouce::pSoft = NULL;
            CheckResultResouce::softNum = GetSoftWareInfo(&CheckResultResouce::pSoft);
            CheckResultResouce::pProcess = NULL;
            CheckResultResouce::processNum = GetProcessInfo(&CheckResultResouce::pProcess);
            // 杀毒软件，是从软件列表中筛选的，状态是从进程中获取，需要先获取已安装的软件和进程
            CheckResultResouce::pAntivirusSoft = NULL;
            CheckResultResouce::antivirusSoftNum = GetViruslibraryUupdateTime(CheckResultResouce::pSoft, CheckResultResouce::softNum,
                                                                          CheckResultResouce::pProcess,CheckResultResouce::processNum,
                                                                          &CheckResultResouce::pAntivirusSoft);

            //共享文件
            CheckResultResouce::pShareInfo = NULL;
            CheckResultResouce::shareNum = 0;
            CheckResultResouce::shareNum = GetNetshare(&CheckResultResouce::pShareInfo);

            // 审计策略
            CheckResultResouce::pAuditPolicy =NULL;
            CheckResultResouce::auditNum = 0;
            GetAuditPolicy(&CheckResultResouce::pAuditPolicy, CheckResultResouce::auditNum);
            // 系统访问策略
            CheckResultResouce::pSystemAccess = NULL;
            CheckResultResouce::systemNum = 0;
            GetSystemAccessPolicy(&CheckResultResouce::pSystemAccess, CheckResultResouce::systemNum);
            // 用户权利指派
            CheckResultResouce::pUserRightsAssignments=NULL;
            CheckResultResouce::userRightsNum=0;
            GetUserRightsAssignment(&CheckResultResouce::pUserRightsAssignments, CheckResultResouce::userRightsNum);

            CheckResultResouce::pOsVersion=NULL;
            CheckResultResouce::pOsVersion = GetOsVersionInfo();

            // 密码策略及账号锁定
            CheckResultResouce::pPolicyBuf=NULL;
            CheckResultResouce::pPolicyBuf = GetSecurityPolicy();

            // 组策略
            CheckResultResouce::groupPolicyNum =0;
            CheckResultResouce::pGroupPolicy=NULL;
            CheckResultResouce::groupPolicyNum = GetGroupPolicyResult(&CheckResultResouce::pGroupPolicy);

            // 服务
            CheckResultResouce::servicesNum=0;
            CheckResultResouce::pServiceStatus=NULL;
            CheckResultResouce::servicesNum = GetServices(&CheckResultResouce::pServiceStatus);

            // 系统安装时间

            CheckResultResouce::osInstallTime = GetOsTimeInfo();

            //主机名

            CheckResultResouce::computerName = GetNameOfComputer();

            //安全选项
            CheckResultResouce::pSecurityOpt=NULL;
            CheckResultResouce::secOptionsNum=0;
            CheckResultResouce::secOptionsNum = GetSecurityOptionsValue(&CheckResultResouce::pSecurityOpt);

            // 等保检查项
            CheckResultResouce::pDtckResults=NULL;
            CheckResultResouce::pDtckResults = GetDtckResults();

            // 密码策略
            CheckResultResouce::pDtPwdPolicy=NULL;
            CheckResultResouce::pDtPwdPolicy = GetDtckResultsPwdPolicy();

            // 审核策略
            CheckResultResouce::pDtAuditPolicy=NULL;
            CheckResultResouce::pDtAuditPolicy = GetDtckResultsAuditPolicy();

            // 访问控制策略
            CheckResultResouce::pDtAccLockPolicy =NULL;
            CheckResultResouce::pDtAccLockPolicy = GetDtckResultsAccLockPolicy();

            // 用户权限分配
            CheckResultResouce::pDtUserRightAssignment=NULL;
            CheckResultResouce::pDtUserRightAssignment = GetDtckResultsUserRightAssignment();

            // 自动登录
            CheckResultResouce::pDtAutoAdminLogin=NULL;
            CheckResultResouce::pDtAutoAdminLogin = GetDtckResultsAutoAdminLogin();

            // 驱动器自动运行
            CheckResultResouce::pDtDriverAutoOperation=NULL;
            CheckResultResouce::pDtDriverAutoOperation = GetDtckResultsDriverAutoOperation();

            // dump文件
            CheckResultResouce::pDtMakeDumpFile=NULL;
            CheckResultResouce::pDtMakeDumpFile = GetDtckResultsMakeDumpFile();

            // 网络连接
            CheckResultResouce::pDtNetConnect=NULL;
            CheckResultResouce::pDtNetConnect = GetDtckResultsNetConnect();

            // 组策略
            CheckResultResouce::pDtGroupPolicy=NULL;
            CheckResultResouce::pDtGroupPolicy = GetDtckResultsGroupPolicy();
            isChecked=1;
            break;
        }
        else if(num==11)   //文件内容检查
        {
            DbTaskScanDisk tExt;
            memset(&tExt, 0, sizeof(tExt));
            tExt.nID = 1001;
            int mCount = keyWordList.count();
            QString qDir;
            QString qKeys;
            if(mCount==2)
            {
                qDir = keyWordList[1];
//                qDir = "D:\\test";
                qKeys = keyWordList[0];
                qKeys += ";核武器;十八大;金正恩;奥巴马;泄密;飞虎队;中国政府;抢劫;暴力;游行示威;西藏;东突组织;基地组织;钓鱼岛;南海;";
                qKeys.replace("；",";");
                qKeys.replace(";;",";");
            }
            else
            {
                qDir = "C:\\";
                qKeys = "核武器;十八大;金正恩;奥巴马;泄密;飞虎队;中国政府;抢劫;暴力;游行示威;西藏;东突组织;基地组织;钓鱼岛;南海;";
            }
            QByteArray ba = qDir.toLocal8Bit();
            char *mid_1 = ba.data();
            strcpy(tExt.strDir,mid_1);
            QByteArray ba_3 = qKeys.toLocal8Bit();
            char *mid_2 = ba_3.data();
            strcpy(tExt.strKeys,mid_2);
            keyWordList.clear();

            QString strPath = qApp->applicationDirPath();
            strPath +="\\sssens\\TestS.exe";

            QString tmpPath = QString(strPath);

//            QByteArray ba_2 = tmpPath.toLocal8Bit();
//            char *cTemp = ba_2.data();

//            STARTUPINFOA stinfo = {sizeof(stinfo)};
//            PROCESS_INFORMATION	procinfo;

            // 临时出来文件名和目录

//            bool bret = CreateProcessA(cTemp, NULL , NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &stinfo, &procinfo);

            bool ok = QProcess::startDetached(tmpPath,QStringList());
            //bool bret = true;
            if (ok)
            {
                TxHead txhead;
                memset(&txhead, 0, sizeof(txhead));
                txhead.m_uDstApp = APP_SEARCHDISK;
                txhead.m_uMsgLen = sizeof(DbTaskScanDisk);
                txhead.m_uMsgType = MS_SEARCHDISK_BEGIN;

                char buffer[0xffff] = {0};
                memcpy(buffer, &txhead, sizeof(TxHead));
                memcpy(buffer + sizeof(TxHead), &tExt, sizeof(DbTaskScanDisk));
                USHORT len = sizeof(TxHead) + sizeof(DbTaskScanDisk);
                g_tTestDirScan.PushDataToApp(APP_SEARCHDISK, buffer, len, true);
            }
            else
            {
            }
            break;
        }
        else if(num==12)    //USB深度检查
        {
            if(IsDoing())
            {
                qWarning()<<"usb deep check is running!";
                isChecked=1;
                return;
            }
            else
            {
                PCHECK_PARAM pCP=new CHECK_PARAM;
                memset(pCP,0,sizeof(CHECK_PARAM));

                pCP->type=QCHECK_USB;
                pCP->pVectorResult=new vector<wstring>();
                pCP->pVectorParam=NULL;

                CheckOneWDeep(1,pCP,CheckOver,SetDataW,ShowProgress,FALSE);
                break;
            }
        }
        else if(num==13)     //违规外联深度检查
        {
            if(IsDoing())
            {
                qWarning()<<"usb deep check is running!";
                isChecked=1;
                return;
            }
            else
            {
                PCHECK_PARAM pCP=new CHECK_PARAM;
                memset(pCP,0,sizeof(CHECK_PARAM));

                pCP->type=QCHECK_INTERNET;
                pCP->pVectorResult=new vector<wstring>();
                pCP->pVectorParam=NULL;

                CheckOneWDeep(1,pCP,CheckOver,SetDataW,ShowProgress,FALSE);
                break;
            }
        }
        else if(num==14)     //文件操作轻度检查
        {
            vector<wstring> result;
            CHECK_PARAM cp={0};

            cp.type=QCHECK_FILE_OPEND;
            cp.pVectorResult=&result;
            cp.pVectorParam=NULL;

            CheckOneW(1,&cp,SetDataW);
            copyResult(*cp.pVectorResult,cp.type);

            isChecked = 1;
            break;
        }
        else if(num==15)    //文件操作深度检查
        {
            if(IsDoing())
            {
                qWarning()<<"usb deep check is running!";
                isChecked=1;
                return;
            }
            else
            {
                PCHECK_PARAM pCP=new CHECK_PARAM;
                memset(pCP,0,sizeof(CHECK_PARAM));

                pCP->type=QCHECK_FILE_OPEND;
                pCP->pVectorResult=new vector<wstring>();
                pCP->pVectorParam=NULL;

                CheckOneWDeep(1,pCP,CheckOver,SetDataW,ShowProgress,FALSE);
                break;
            }
        }
        else if(num==77)
        {
            CheckStop();
            break;
        }
        else if(num==888)
        {
            QString localPath = qApp->applicationDirPath();
            localPath+="/report/myhtml.html";
            QString webStr = "file:///"+localPath;
            QDesktopServices::openUrl(QUrl(webStr));
            isChecked=1;
            break;
        }
        else if(num==99)    //全部扫描
        {
            HostCheckUnInit();
            QString localPath = qApp->applicationDirPath();
            localPath+="/config/grxalog.grxa";
            QByteArray ba = localPath.toLatin1();
            char *c_str2 = ba.data();
            if (!HostCheckInit(c_str2))
            {
                qWarning()<<"HostCheckInit error";
                isChecked=1;
                return;
            }
            // snmp
            scanProject = QString("正在获取SNMP");
            CheckResultResouce::pSnmpService = NULL;
            CheckResultResouce::pSnmpService = GetSnmpInfo();

            scanProject = QString("正在获取组策略");
            // 审计策略
            CheckResultResouce::pAuditPolicy = NULL;
            GetAuditPolicy(&CheckResultResouce::pAuditPolicy, CheckResultResouce::auditNum);
            // 系统访问策略
            CheckResultResouce::pSystemAccess = NULL;
            GetSystemAccessPolicy(&CheckResultResouce::pSystemAccess, CheckResultResouce::systemNum);
            // 用户权利指派
            CheckResultResouce::pUserRightsAssignments = NULL;
            GetUserRightsAssignment(&CheckResultResouce::pUserRightsAssignments, CheckResultResouce::userRightsNum);
//            GetSecEditItemResult2(&CheckResultResouce::pAuditPolicy, CheckResultResouce::auditNum,
//                                &CheckResultResouce::pSystemAccess, CheckResultResouce::systemNum);
            scanProject = QString("正在获取操作系统版本");
            CheckResultResouce::pOsVersion = NULL;
            CheckResultResouce::pOsVersion = GetOsVersionInfo();
            scanProject = QString("正在获取DNS信息");
            int m = sizeof(CheckResultResouce::szDns);
            GetDNSInfo(CheckResultResouce::szDns,m);
//            qDebug()<<"GetDNSInfo return:"<<m;

            scanProject = QString("正在获取USB使用记录");
            CheckResultResouce::pUsbHistory = NULL;
            CheckResultResouce::pUsbHistory = GetUsbUseHistory();
            scanProject = QString("正在获取IE历史记录");
            CheckResultResouce::pIeHistory = NULL;
            CheckResultResouce::pIeHistory = GetIeAccessHistory();
            scanProject = QString("正在获取Firefox历史记录");
            CheckResultResouce::pFirefoxHistory = NULL;
            CheckResultResouce::pFirefoxHistory = GetFirefoxHistory();
            scanProject = QString("正在获取Chrome历史记录");
            CheckResultResouce::pChromeHistory = NULL;
            CheckResultResouce::pChromeHistory = GetChromeHistory();
            scanProject = QString("正在获取系统补丁");
            CheckResultResouce::pSystemDefectInfo = NULL;
            CheckResultResouce::pSystemDefectInfo = GetHotfixesInfoWUAInstall();
            scanProject = QString("正在获取启动项信息");
            CheckResultResouce::pRunItems = NULL;
            CheckResultResouce::pRunItems = GetRunItemsInfo();
            scanProject = QString("正在获取密码策略");
            CheckResultResouce::pPolicyBuf = NULL;
            CheckResultResouce::pPolicyBuf = GetSecurityPolicy();
            scanProject = QString("正在获取组策略");
            CheckResultResouce::pGroupPolicy = NULL;
            CheckResultResouce::groupPolicyNum = GetGroupPolicyResult(&CheckResultResouce::pGroupPolicy);
//            scanProject = QString("正在获取用户权利指派");
//            CheckResultResouce::userRightsNum = GetUserRightsAssignments(&CheckResultResouce::pUserRightsAssignments);
            scanProject = QString("正在获取账户信息");
            CheckResultResouce::pUserInfo = NULL;
            CheckResultResouce::usersNum = GetNetUsers(&CheckResultResouce::pUserInfo);
            scanProject = QString("正在获取系统共享文件");
            CheckResultResouce::pShareInfo = NULL;
            CheckResultResouce::shareNum = 0;
            CheckResultResouce::shareNum = GetNetshare(&CheckResultResouce::pShareInfo);
            scanProject = QString("正在获取系统服务");
            CheckResultResouce::pServiceStatus = NULL;
            CheckResultResouce::servicesNum = GetServices(&CheckResultResouce::pServiceStatus);
            scanProject = QString("正在获取系统安装时间");
            CheckResultResouce::osInstallTime = GetOsTimeInfo();
            scanProject = QString("正在获取主机名");
            CheckResultResouce::computerName = GetNameOfComputer();
            scanProject = QString("正在获取系统已安装的软件");
            CheckResultResouce::pSoft = NULL;
            CheckResultResouce::softNum = GetSoftWareInfo(&CheckResultResouce::pSoft);
            scanProject = QString("正在获取运行的进程");
            CheckResultResouce::pProcess = NULL;
            CheckResultResouce::processNum = GetProcessInfo(&CheckResultResouce::pProcess);
            scanProject = QString("正在获取安装的杀毒软件信息");
            // 杀毒软件，是从软件列表中筛选的，状态是从进程中获取，需要先获取已安装的软件和进程
            CheckResultResouce::pAntivirusSoft = NULL;
            CheckResultResouce::antivirusSoftNum = GetViruslibraryUupdateTime(CheckResultResouce::pSoft, CheckResultResouce::softNum,
                                                                          CheckResultResouce::pProcess,CheckResultResouce::processNum,
                                                                          &CheckResultResouce::pAntivirusSoft);

            scanProject = QString("正在获取已开机时间启动时间");
            CheckResultResouce::pBootTime = NULL;
            CheckResultResouce::pBootTime = GetSysBootTime();
            scanProject = QString("正在获取BIOS信息");
            CheckResultResouce::pBiosInfo = NULL;
            CheckResultResouce::pBiosInfo = GetBiosInfo();
            scanProject = QString("正在获取磁盘分区信息");
            CheckResultResouce::pLogicDrives = NULL;
            CheckResultResouce::logicDrivesNum = GetLogicalDrivesInfo(&CheckResultResouce::pLogicDrives);
            scanProject = QString("正在获取磁盘权限信息");
            CheckResultResouce::pDrivesRights = NULL;
            CheckResultResouce::drivesRightsNum = GetDrivesAccountRights(&CheckResultResouce::pDrivesRights);
            scanProject = QString("正在获取系统文件权限信息");
            CheckResultResouce::pSystemRights = NULL;
            CheckResultResouce::systemRightsNum = GetSystemAccountRights(&CheckResultResouce::pSystemRights);
            scanProject = QString("正在获取CPU信息");
            CheckResultResouce::pCpuInfo = NULL;
            CheckResultResouce::pCpuInfo = GetCPUInfo();
            scanProject = QString("正在获取硬盘信息");
            CheckResultResouce::pHardDisk = NULL;
            CheckResultResouce::diskNum = GetHardDiskInfo(&CheckResultResouce::pHardDisk);
//            qDebug()<<"disk number is: "<<CheckResultResouce::diskNum;
            scanProject = QString("正在获取主板信息");
            CheckResultResouce::pBoardInfo = NULL;
            CheckResultResouce::pBoardInfo = GetBoardInfo();
            scanProject = QString("正在获取显卡信息");
            CheckResultResouce::pDisplayCard = NULL;
            CheckResultResouce::pDisplayCard = GetDisplayInfo();
            scanProject = QString("正在获取内存信息");
            CheckResultResouce::pMemory = NULL;
            CheckResultResouce::pMemory = GetMemoryInfo();
            scanProject = QString("正在获取声卡信息");
            CheckResultResouce::pAudio = NULL;
            CheckResultResouce::pAudio = GetAudioInfo();
            scanProject = QString("正在获取网卡信息");
            CheckResultResouce::pNetwork = NULL;
            CheckResultResouce::netcardNum = GetNetworkCardInfo(&CheckResultResouce::pNetwork);
            scanProject = QString("正在获取安全选项");
            CheckResultResouce::pSecurityOpt = NULL;
            CheckResultResouce::secOptionsNum = GetSecurityOptionsValue(&CheckResultResouce::pSecurityOpt);
            scanProject = QString("正在获取注册表设置");
            CheckResultResouce::pRegistrySets = NULL;
            CheckResultResouce::regOptionsNum = GetRegistrySetsOptionsValue(&CheckResultResouce::pRegistrySets);
            scanProject = QString("正在获取windows日志信息");
            CheckResultResouce::pEventlogs = NULL;
            CheckResultResouce::eventlogNum = GetEventlogsOptionsValue(&CheckResultResouce::pEventlogs);
            scanProject = QString("正在获取活动端口");
            CheckResultResouce::pPortInfo = NULL;
            CheckResultResouce::pPortInfo = GetPort();
            scanProject = QString("正在进行等保检查");
            CheckResultResouce::pDtckResults = NULL;
            CheckResultResouce::pDtckResults = GetDtckResults();
            ifPolicyXml = true;
            // 密码策略
            CheckResultResouce::pDtPwdPolicy = NULL;
            CheckResultResouce::pDtPwdPolicy = GetDtckResultsPwdPolicy();

            // 审核策略
            CheckResultResouce::pDtAuditPolicy = NULL;
            CheckResultResouce::pDtAuditPolicy = GetDtckResultsAuditPolicy();

            // 访问控制策略
            CheckResultResouce::pDtAccLockPolicy = NULL;
            CheckResultResouce::pDtAccLockPolicy = GetDtckResultsAccLockPolicy();

            // 用户权限分配
            CheckResultResouce::pDtUserRightAssignment = NULL;
            CheckResultResouce::pDtUserRightAssignment = GetDtckResultsUserRightAssignment();

            // 自动登录
            CheckResultResouce::pDtAutoAdminLogin = NULL;
            CheckResultResouce::pDtAutoAdminLogin = GetDtckResultsAutoAdminLogin();

            // 驱动器自动运行
            CheckResultResouce::pDtDriverAutoOperation = NULL;
            CheckResultResouce::pDtDriverAutoOperation = GetDtckResultsDriverAutoOperation();

            // dump文件
            CheckResultResouce::pDtMakeDumpFile = NULL;
            CheckResultResouce::pDtMakeDumpFile = GetDtckResultsMakeDumpFile();

            // 网络连接
            CheckResultResouce::pDtNetConnect = NULL;
            CheckResultResouce::pDtNetConnect = GetDtckResultsNetConnect();

            // 组策略
            CheckResultResouce::pDtGroupPolicy = NULL;
            CheckResultResouce::pDtGroupPolicy = GetDtckResultsGroupPolicy();

            //写配置文件
            writeSettingFile();

            //生成报告
            QString localPath_2 = qApp->applicationDirPath();
            localPath_2 += "/report";
            isDirExist(localPath_2);
            localPath_2 += "/myxml.xml";
            QByteArray ba_2 = localPath_2.toLatin1();
            char *c_str_2 = ba_2.data();
            Write2Xml(c_str_2);

            QString localPath_3 = qApp->applicationDirPath();
            localPath_3 += "/report";
            isDirExist(localPath_3);
            localPath_3 += "/myhtml.html";
            QByteArray ba_3 = localPath_3.toLatin1();
            char *c_str_3 = ba_3.data();
            WriteHtml(c_str_3);

//            HostCheckUnInit();
            isChecked=1;
            break;
        }
        else if(num==100)    //接收到服务器发来的指令
        {
            if(!fileVector.empty())
            {               
                TaskInfo mTask;
                mTask = fileVector[0];
                int taskCode = mTask.nKind;
                switch (taskCode)
                {
                case NET_MSG_UP_LOGCUR:   //上传日志文件
                {
                    id = mTask.pTransF->nID;
                    QString localPath_2 = qApp->applicationDirPath();
                    localPath_2+="/log.txt";
                    QByteArray ba_2 = localPath_2.toLocal8Bit();
                    char *c_str_2 = ba_2.data();
                    qDebug()<<"上传日志文件 id:"<<id;
                    NtCrsSntdFele(c_str_2, id);
                    isChecked = 1;
                    break;
                }
                case NET_MSG_DISK_DIR_SCAN:    //暂定为扫描任务
                {
                    ifFromServer=true;
                    id = mTask.pTransF->nID;
//                    qDebug()<<"NET_MSG_DISK_DIR_SCAN id :"<<id<<"nId:"<<mTask.pTransF->nID;
                    ifDeep = 0;       //是否有深度检查任务
                    ifSens = 0;
                    char *pTask = new char[256];
                    my_strcpy_s(pTask,280,mTask.pTransF->strDir);
                    analyzeTask(pTask,ifDeep);
                    if(pTask)
                    {
                        delete []pTask;
                        pTask = NULL;
                    }
                    if(ifDeep==0&&ifSens==0)    //没有深度检查任务
                    {
                        //生成报告
                        QString localPath_2 = qApp->applicationDirPath();
                        localPath_2 += "/report";
                        isDirExist(localPath_2);
                        localPath_2 += QString("/myxmlfromserver.xml");
                        QByteArray ba_2 = localPath_2.toLatin1();
                        char *c_str_2 = ba_2.data();
                        qDebug()<<"no deep and sens task update,id:"<<id;
                        Write2Xml(c_str_2);
                        NtCrsSntdFele(c_str_2, id);
                        isChecked=1;

//                        QString localPath_3 = qApp->applicationDirPath();
//                        localPath_3 += "/report";
//                        localPath_3 += "/myhtmlfromserver.html";
//                        QByteArray ba_3 = localPath_3.toLatin1();
//                        char *c_str_3 = ba_3.data();
//                        WriteHtml(c_str_3);
                        ifFromServer=false;
                    }
                    break;
                }
                default:
                    break;
                }
                int mSize = fileVector.size();
                if(mSize>0)
                {
                    if(mTask.pTransF)
                    {
                        delete mTask.pTransF;
                        mTask.pTransF = NULL;
                    }
                    vector<TaskInfo>::iterator k = fileVector.begin();
                    fileVector.erase(k);
                }
                if(ifDeep==0&&ifSens==0)
                {
                    isChecked=1;
                }
                break;
            }
            isChecked=1;
            break;
        }
    }
}
