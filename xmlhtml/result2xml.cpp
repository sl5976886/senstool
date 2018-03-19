// djjc.cpp : 定义 DLL 应用程序的导出函数。
//

//#include "../GrxaHostCheck/stdafx.h"
#include <time.h>
#include "result2xml.h"
#include "CheckResultResouce.h"
#include "txt.h"
#include "global.h"
//#include "checkresultfromserver.h"
#include <stdio.h>
#include <string>
#include <QByteArray>
#include <QDebug>

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif

#define STRFILEVER       "2.1.16.1139"

// 唯一的应用程序对象

using namespace std;

//#define XML_HEADER "<?xml version=\"1.0\" encoding=\"GB2312\" ?>" // XML文件头的定义
#define XML_HEADER "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" // XML文件头的定义
#define SAFE_DELETE(x) {if(x) delete x; x=NULL;} // 安全删除new分配出来的变量空间
#define SAFE_DELETE_ARRAY(x) {if(x) delete[] x; x=NULL;} // 安全删除new分配出来的数组空间


void    InsertHostInfo(TiXmlElement *pElmParent);
void    InsertItems(TiXmlElement* pElmParent);
BOOL    CreateCustomUid(char szBuf, int iBufLen, int iUidLen=36);

BOOL    InsertLevelResult(TiXmlElement *pElmItems, CHECK_RESULT_GUID *pCheckResultGuid, int iGuidNum);

static void StorageCapacity2Str(DWORDLONG storageCapacity, char szBuf[64])
{
    if (storageCapacity > 1024*1024*1024)
    {
        sprintf(szBuf, "%.2llfG", storageCapacity*1.0/(1024*1024*1024));
    }
    else if (storageCapacity > 1024*1024)
    {
        sprintf(szBuf, "%.2llfM", storageCapacity*1.0/(1024*1024));
    }
    else if (storageCapacity > 1024)
    {
        sprintf(szBuf, "%.2llfK", storageCapacity*1.0/(1024));
    }
    else
    {
        sprintf(szBuf, "%uM", storageCapacity);
    }
}

int     WriteDjjcResult2Memory(int iToolNum, char **pResult, int &len)
{
    qInstallMessageHandler(outputMessage);
    TiXmlDeclaration Declaration( "1.0","GB2312", "yes" ); // 建立XML头结构

    int iRt = -1;
    TiXmlDocument xmlDoc;
    xmlDoc.InsertEndChild( Declaration ); // 把XML头结构插入当前文档

    // 建立根节点
    TiXmlElement xmlRoot("result");

    // 插入描述
    InsertHead(xmlRoot, (EToolType)iToolNum);
    //host_info
//    InsertHostInfo(&xmlRoot);   //与下面重复

    // 插入子项
    InsertItems(&xmlRoot);
    ifPolicyXml = false;

    InsertAllItems(xmlRoot);
#ifdef DEBUGLOG
    qDebug()<<"InsertAllItems";
#endif

    xmlDoc.InsertEndChild( xmlRoot );

    TiXmlPrinter printer;
    printer.SetIndent( "\t" );
    xmlDoc.Accept( &printer );
    len = printer.Size();
    if (len > 0)
    {
        *pResult = new char[len];
        if (NULL != (*pResult))
        {
            memcpy(*pResult, printer.CStr(), len);
            iRt = 0;
        }
    }
    qDebug()<<"xml finish";
// 	xmlRoot.Clear();
// 	xmlDoc.Clear();

    return iRt;
}

void    FreeMemoryBuf(char **pResult)
{
    if (*pResult)
    {
        delete *pResult;
        *pResult = NULL;
    }
}

BOOL    CreateCustomUid(char *pszBuf, int iBufLen, int iUidLen)
{
    char caBuf[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz~!@#$%^&*()_+-=<>?{}|[]";
    int randLen = strlen(caBuf);
    int i=0;

    iBufLen -= 1;
    if ((iBufLen < 1) || (iUidLen < 1) || (iBufLen < iUidLen))
        return FALSE;

    //randLen = (iBufLen>64) ? 64:iBufLen;
    srand(time(NULL));
    while(i < iUidLen)
    {
        pszBuf[i++] = caBuf[rand()%randLen];
    }
    pszBuf[i] = 0;

    return TRUE;
}

BOOL    InsertHead(TiXmlElement &elmParent, int iToolNum)
{
//     -<scheme>
//         <tool_info
//         toolversion="V2.0.0.0"
//         toolcategory="001"
//         toolname="Windows主机配置检查工具"
//         toolcode="CpHostAudit.exe"
//         corpname="江苏国瑞信安科技有限公司"
//         corpcode="JSGRXAKJYXGS"/>
//
//         <task_info
//         sag=""
//         grade=" "
//         username=""
//         unitname=""
//         taskname=""
//         taskcode=""/>
//
//         <operation_info
//         dest_hostname="sagara-PC"
//         dest_mac="00-ff-85-ee-5d-1f;78-2b-cb-9a-cc-4c;"
//         dest_ip="0.0.0.0;172.18.7.220;"
//         src_hostname="sagara-PC"
//         src_mac="00-ff-85-ee-5d-1f;78-2b-cb-9a-cc-4c;"
//         src_ip="0.0.0.0;172.18.7.220;"
//         src_os="Microsoft Windows 7 Ultimate Edition Service Pack 1"
//         stamp="2013-11-18 17:30:47"/>
//     </scheme>

    char szCorpName[] = "";
    char szCorpCode[] = "";

    struct  T_TOOLNAME_INFO
    {
        int  iToolNum;
        char szToolName[128];
        char szVersion[32];
        char szToolCode[128];
    };

    T_TOOLNAME_INFO toolInfo[] =
    {
        {1,  "windows主机配置检查工具",   "V2.0.0.0", "WindowsHost.exe"},
        {2,  "linux主机配置检查工具",     "V2.0.0.0", ""},
        {3,  "病毒检查工具",              "V2.0.0.0", ""},
        {4,  "木马检查工具",              "V2.0.0.0", ""},
        {5,  "网络设备配置检查工具",      "V2.0.0.0", ""},
        {6,  "网站恶意代码检查工具",      "V2.0.0.0", ""},
        {7,  "保留，以便后续扩充使用",    "V2.0.0.0", ""},
        {8,  "安全设备配置检查工具",      "V2.0.0.0", ""},
        {9,  "弱口令检查工具",            "V2.0.0.0", ""},
        {10, "SQL注入验证检查工具",       "V2.0.0.0", ""},
        {11, "系统漏洞扫描工具",          "V2.0.0.0", ""},
        {12, "网站安全检查工具",          "V2.0.0.0", ""},
        {13, "数据库安全检查工具",        "V2.0.0.0", ""},
    };

    char szBuf[256];
    int index = 0;

    if ((iToolNum > 13) || (iToolNum < 0))
        return FALSE;

    index = iToolNum;

    TiXmlElement xmlScheme( "scheme" );

    //         <tool_info
    //         toolversion="V2.0.0.0"
    //         toolcategory="001"
    //         toolname="Windows主机配置检查工具"
    //         toolcode="CpHostAudit.exe"
    //         corpname="江苏国瑞信安科技有限公司"
    //         corpcode="JSGRXAKJYXGS"/>
    TiXmlElement xmlToolInfo( "tool_info" );
    char strHostId[96] = { 0 };
    itoa(hostId,strHostId,10);
    xmlToolInfo.SetAttribute("corpcode",     strHostId);
    xmlToolInfo.SetAttribute("corpname",     szCorpName);
    xmlToolInfo.SetAttribute("toolcode",     "");
    xmlToolInfo.SetAttribute("toolname",     "");
    sprintf(szBuf, "%03d", toolInfo[index].iToolNum);
    xmlToolInfo.SetAttribute("toolcategory", "");
    sprintf(szBuf, "V%s", STRFILEVER);
    xmlToolInfo.SetAttribute("toolversion",  ""/*toolInfo[index].szVersion*/);
    xmlScheme.InsertEndChild(xmlToolInfo);

    //         <task_info
    //         sag=""
    //         grade=" "
    //         username=""
    //         unitname=""
    //         taskname=""
    //         taskcode=""/>
    TiXmlElement xmlTaskInfo( "task_info" );
    xmlTaskInfo.SetAttribute("taskcode", id);
    xmlTaskInfo.SetAttribute("taskname", "");
    xmlTaskInfo.SetAttribute("unitname", "");
    xmlTaskInfo.SetAttribute("username", "");
    xmlTaskInfo.SetAttribute("grade",    "");
    xmlTaskInfo.SetAttribute("sag",      "");
    xmlScheme.InsertEndChild(xmlTaskInfo);

    //         <operation_info
    //         dest_hostname="sagara-PC"
    //         dest_mac="00-ff-85-ee-5d-1f;78-2b-cb-9a-cc-4c;"
    //         dest_ip="0.0.0.0;172.18.7.220;"
    //         src_hostname="sagara-PC"
    //         src_mac="00-ff-85-ee-5d-1f;78-2b-cb-9a-cc-4c;"
    //         src_ip="0.0.0.0;172.18.7.220;"
    //         src_os="Microsoft Windows 7 Ultimate Edition Service Pack 1"
    //         stamp="2013-11-18 17:30:47"/>
    char szMac[512] = "";
    char szIp[512]  = "";

    for (int i=0; i<CheckResultResouce::netcardNum; i++)
    {
        NetworkCardInfo *pNetcard = CheckResultResouce::pNetwork;
        strcat(szMac, pNetcard[i].MACAddress);
        strcat(szMac, ";");

        strcat(szIp, pNetcard[i].IPAddress);
        strcat(szIp, ";");
    }

    TiXmlElement xmlOperationInfo( "operation_info" );
    xmlOperationInfo.SetAttribute("stamp",           "");

    OsVersionInfo *pOsVersion = CheckResultResouce::pOsVersion;
    if (pOsVersion)
        sprintf(szBuf, "%s %s", pOsVersion->systemName, pOsVersion->CSDVersion);
    else
        sprintf(szBuf, "未知");
    xmlOperationInfo.SetAttribute("src_os",          szBuf);
    xmlOperationInfo.SetAttribute("src_ip",          szIp);
    xmlOperationInfo.SetAttribute("src_mac",         szMac);

    char *pHostName = CheckResultResouce::computerName;
    if (NULL == pHostName)
        pHostName = "";
    xmlOperationInfo.SetAttribute("src_hostname",    pHostName);
    xmlOperationInfo.SetAttribute("dest_ip",         szIp);
    xmlOperationInfo.SetAttribute("dest_mac",        szMac);
    xmlOperationInfo.SetAttribute("dest_hostname",   pHostName);

    xmlScheme.InsertEndChild(xmlOperationInfo);

    elmParent.InsertEndChild( xmlScheme );

    return TRUE;
}


VOID InsertStandardItems(TiXmlElement &xmlElements, DtckResults* pDtckResults)
{
    //获取主机所有检查项

    TiXmlElement xmlCheckPointName = TiXmlElement("results");
    TiXmlElement xmlCheckItem("item");

    while (NULL != pDtckResults)
    {
        DtckResult &result = pDtckResults->result;
        pDtckResults = pDtckResults->pNext;

        xmlCheckItem = TiXmlElement("item");

        xmlCheckItem.SetAttribute("检查项",   result.strCkPoint);
        xmlCheckItem.SetAttribute("检查结果", result.strResult);
        xmlCheckItem.SetAttribute("参考标准", result.strComment);
        xmlCheckPointName.InsertEndChild(xmlCheckItem);
    }
    xmlElements.InsertEndChild(xmlCheckPointName);
}
VOID InsertUSBItems(TiXmlElement &xmlElements, USBHISTORY* pUsbHis)
{
    //USB
    TiXmlElement xmlCheckPointName = TiXmlElement("usb_historys");
    TiXmlElement xmlCheckItem("item");

    while (NULL != pUsbHis)
    {
        USBHISTORY &usbHistory = *pUsbHis;
        pUsbHis = pUsbHis->pNext;

        xmlCheckItem = TiXmlElement("item");

        xmlCheckItem.SetAttribute("描述",     usbHistory.caDeviceDesc);
        xmlCheckItem.SetAttribute("设备类型", usbHistory.caService);
        xmlCheckItem.SetAttribute("创建时间", usbHistory.caCreateTime);
        xmlCheckItem.SetAttribute("修改时间", usbHistory.caUpdateTime);
        xmlCheckPointName.InsertEndChild(xmlCheckItem);
    }
    xmlElements.InsertEndChild(xmlCheckPointName);
}

VOID InsertDeepUSBItems(TiXmlElement &elmParent)
{
    TiXmlElement xmlCheckPointName = TiXmlElement("usb_deep_historys");
    TiXmlElement xmlCheckItem("item");
    QStringList mList;
    QString strModel,strTime,strId,strBz;
    QString mRes;
    int count=0;
    for(int i=0;i<usbResList.count();i++)
    {
        mRes = usbResList[i];
        mList = mRes.split("|");
        int len = mList.count();
        if(len<4)
        {
//            qWarning()<<"usb result fault!";
        }
        else
        {
            strModel = mList[0];
            strTime = mList[1];
            strId = mList[2];
            strBz = mList[3];

            QByteArray ba = strModel.toLocal8Bit();
            char *c_model = ba.data();
            QByteArray ba_2 = strTime.toLocal8Bit();
            char *c_time = ba_2.data();
            QByteArray ba_3 = strId.toLocal8Bit();
            char *c_id = ba_3.data();
            QByteArray ba_4 = strBz.toLocal8Bit();
            char *c_bz = ba_4.data();

            xmlCheckItem = TiXmlElement("item");
            //"检查模式|时间|ID|备注"
            xmlCheckItem.SetAttribute("检查模式",c_model);
            xmlCheckItem.SetAttribute("时间",c_time);
            xmlCheckItem.SetAttribute("ID",c_id);
            xmlCheckItem.SetAttribute("备注",c_bz);
            xmlCheckPointName.InsertEndChild(xmlCheckItem);
            mList.clear();
            count++;
            if(count>=100)
            {
                break;
            }
        }
    }
    elmParent.InsertEndChild(xmlCheckPointName);
}

VOID InsertDeepBrowserItems(TiXmlElement &elmParent)
{
    TiXmlElement xmlCheckPointName = TiXmlElement("browser_deep_historys");
    TiXmlElement xmlCheckItem("item");
    QString mRes;
    QStringList mList;
    QString strModel,strTime,strId,strBz;
    int count=0;
    for(int i=0;i<internetResList.count();i++)
    {
        mRes = internetResList[i];
        mList = mRes.split("|");
        int len = mList.count();
        if(len<4)
        {
//            qWarning()<<"usb result fault!";
        }
        else
        {
            //工具类型|时间|URL|title
            strModel = mList[0];
            strTime = mList[1];
            strId = mList[2];
            strBz = mList[3];

            QByteArray ba = strModel.toLocal8Bit();
            char *c_model = ba.data();
            QByteArray ba_2 = strTime.toLocal8Bit();
            char *c_time = ba_2.data();
            QByteArray ba_3 = strId.toLocal8Bit();
            char *c_id = ba_3.data();
            QByteArray ba_4 = strBz.toLocal8Bit();
            char *c_bz = ba_4.data();

            xmlCheckItem = TiXmlElement("item");
            //工具类型|时间|URL|title
            xmlCheckItem.SetAttribute("工具类型",c_model);
            xmlCheckItem.SetAttribute("时间",c_time);
            xmlCheckItem.SetAttribute("URL",c_id);
            xmlCheckItem.SetAttribute("title",c_bz);
            xmlCheckPointName.InsertEndChild(xmlCheckItem);
            mList.clear();
            count++;
            if(count>=100)
            {
                break;
            }
        }
    }
    elmParent.InsertEndChild(xmlCheckPointName);
}

VOID InsertSensItems(TiXmlElement &elmParent)
{
    TiXmlElement xmlCheckPointName = TiXmlElement("sensTask");
    TiXmlElement xmlCheckItem("item");
    SensRes mRes;
    QList<SensRes>::iterator it;
    int count=0;
    for(it=sensResList.begin();it!=sensResList.end();it++)
    {
        mRes = *it;
        QString strPath = mRes.filePath;
        QString strKey = mRes.keyWord;

        QByteArray ba = strPath.toLocal8Bit();
        char *c_path = ba.data();
        QByteArray ba_2 = strKey.toLocal8Bit();
        char *c_key = ba_2.data();

        xmlCheckItem = TiXmlElement("item");
        xmlCheckItem.SetAttribute("file_path",c_path);
        xmlCheckItem.SetAttribute("key_word",c_key);
        xmlCheckPointName.InsertEndChild(xmlCheckItem);
        count++;
        if(count>=500)
        {
            break;
        }
    }
    elmParent.InsertEndChild(xmlCheckPointName);
    sensResList.clear();
}

VOID InsertBrowserItems(TiXmlElement &xmlElements, IeVisitHistory *pHistoryIE, FireFoxHistory *pFirefoxHis, ChromeHistory *pChromeHis)
{
    //浏览记录
    char buffer[4096];

    TiXmlElement xmlCheckPointName = TiXmlElement("browser_historys");
    TiXmlElement xmlCheckItem("item");
    TiXmlElement xmlBrowserHistorys("InternetExplorer");

    while(NULL != pHistoryIE)
    {
        IeVisitHistory &ieHistory = *pHistoryIE;
        pHistoryIE = pHistoryIE->pNext;

        //char *pErrUrl =  "javascript:void(function(){document.open();document.write(\"<!DOCTYPE html><html xmlns='http://www.w3.org/1999/xhtml' class='view' ><head><style type='text/css'>.view{padding:0;word-wrap:break-word;cursor:text;height:90%;}body{margin:8px;font-family:sans-serif;font-size:16px;}p{margin:5px 0;}</style><link rel='stylesheet' type='text/css' href='/wenda/js/ueditor/themes/iframe.css'/></head><body class='view' ></body><script type='text/javascript' defer='defer' id='_initialScript'>setTimeout(function(){editor =";
        char *pIeUrl = ieHistory.IeUrl;

        if (!strncmp(pIeUrl, "javascript", 10))
        {
            int j = 0;
            int iUrlLen = strlen(pIeUrl);
            for (int i = 0; i < iUrlLen; i++)
            {
                if ((j+3)> 1023)
                    break;

                if (pIeUrl[i] == '<')
                {
                    strncpy(buffer+j, "&lt", 3);
                    j = j+3;
                }
                else if (pIeUrl[i] == '>')
                {
                    strncpy(buffer+j, "&gt", 3);
                    j = j+3;
                }
                else
                {
                    buffer[j] = pIeUrl[i];
                    j++;
                }
            }
            buffer[j] = 0;
            pIeUrl = buffer;
        }

        xmlCheckItem.SetAttribute("URL",        pIeUrl);
        xmlCheckItem.SetAttribute("标题",       ieHistory.IeTitle);
        xmlCheckItem.SetAttribute("访问时间",   ieHistory.visitTime);
        xmlBrowserHistorys.InsertEndChild(xmlCheckItem);
    }
    xmlCheckPointName.InsertEndChild(xmlBrowserHistorys);

    xmlBrowserHistorys = TiXmlElement("FireFox");
    while (NULL != pFirefoxHis)
    {
        FireFoxHistory &firefox = *pFirefoxHis;
        pFirefoxHis = pFirefoxHis->pNext;

        xmlCheckItem.SetAttribute("URL",        firefox.fireFoxUrl);
        xmlCheckItem.SetAttribute("标题",       firefox.fireFoxTitle);
        xmlCheckItem.SetAttribute("访问时间",   firefox.fireFoxVisitTime);
        xmlBrowserHistorys.InsertEndChild(xmlCheckItem);

    }
    xmlCheckPointName.InsertEndChild(xmlBrowserHistorys);

    xmlBrowserHistorys = TiXmlElement("Chrome");
    while (NULL != pChromeHis)
    {
        ChromeHistory &chrome = *pChromeHis;
        pChromeHis = pChromeHis->pNext;

        xmlCheckItem.SetAttribute("URL",        chrome.chromeUrl);
        xmlCheckItem.SetAttribute("标题",       chrome.chromeTitle);
        xmlCheckItem.SetAttribute("访问时间",   chrome.chromeVisitTime);
        xmlBrowserHistorys.InsertEndChild(xmlCheckItem);

    }
    xmlCheckPointName.InsertEndChild(xmlBrowserHistorys);

    xmlElements.InsertEndChild(xmlCheckPointName);
}

VOID InsertSystemOs(TiXmlElement &xmlElements, OsVersionInfo *pOsVersion, time_t osInstallTime, char *pHostName, char *pBootTime, char *pBiosParameterValue)
{
    OsVersionInfo os;
    if (NULL == pOsVersion)
    {
        ZeroMemory(&os, sizeof(os));
    }

    OsVersionInfo *pTmpOs = pOsVersion;
    if (NULL == pTmpOs)
        pTmpOs = &os;

    TiXmlElement xmlCheckPointName = TiXmlElement("os");
    TiXmlElement xmlCheckItem = TiXmlElement("host_name");
    if (pHostName)
        xmlCheckItem.InsertEndChild(TiXmlText(pHostName));
    else
    {
        xmlCheckItem.InsertEndChild(TiXmlText(""));
    }
    xmlCheckPointName.InsertEndChild(xmlCheckItem);

    xmlCheckItem = TiXmlElement("system_name");
    xmlCheckItem.InsertEndChild(TiXmlText(pTmpOs->systemName));
    xmlCheckPointName.InsertEndChild(xmlCheckItem);

    xmlCheckItem = TiXmlElement("os_version");
    char szBuf[128];
    sprintf(szBuf, "%s.%s.%s", pTmpOs->majorVersion, pTmpOs->MinorVersion, pTmpOs->buildNumber);
    xmlCheckItem.InsertEndChild(TiXmlText(szBuf));
    xmlCheckPointName.InsertEndChild(xmlCheckItem);

    xmlCheckItem = TiXmlElement("os_install_time");
    tm *pt = localtime(&osInstallTime);
    if (pt)
    {
        //tm结构体存储的是从1900年开始的时间，月份为0-11
        sprintf(szBuf, "%d/%d/%d %d:%d:%d", pt->tm_year+1900, pt->tm_mon+1, pt->tm_mday, pt->tm_hour, pt->tm_min, pt->tm_sec);
    }
    else
        strcpy(szBuf, "未知");
    xmlCheckItem.InsertEndChild(TiXmlText(szBuf));
    xmlCheckPointName.InsertEndChild(xmlCheckItem);

    xmlCheckItem = TiXmlElement("system_path");
    char *pSystemRoot = getenv("systemroot");
    if (!pSystemRoot)
        pSystemRoot = "未知";
    xmlCheckItem.InsertEndChild(TiXmlText(pSystemRoot));
    xmlCheckPointName.InsertEndChild(xmlCheckItem);

    xmlCheckItem = TiXmlElement("host_name");
    if (NULL != pHostName)
        xmlCheckItem.InsertEndChild(TiXmlText(pHostName));
    else
        xmlCheckItem.InsertEndChild(TiXmlText(""));
    xmlCheckPointName.InsertEndChild(xmlCheckItem);

    xmlCheckItem = TiXmlElement("start_time");
    if (NULL != pBootTime)
        xmlCheckItem.InsertEndChild(TiXmlText(pBootTime));
    else
        xmlCheckItem.InsertEndChild(TiXmlText(""));
    xmlCheckPointName.InsertEndChild(xmlCheckItem);

    xmlCheckItem = TiXmlElement("BIOS");

    if(NULL != pBiosParameterValue)
        xmlCheckItem.InsertEndChild(TiXmlText(pBiosParameterValue));
    else
        xmlCheckItem.InsertEndChild(TiXmlText(""));
    xmlCheckPointName.InsertEndChild(xmlCheckItem);

    xmlElements.InsertEndChild(xmlCheckPointName);
}
VOID InsertSoftwares(TiXmlElement &xmlElements, SoftwareInfo *pSoftware, int softNum)
{
    //软件
    TiXmlElement xmlCheckPointName = TiXmlElement("softwares");
    TiXmlElement xmlCheckItem("item");

    for (int i=0; i<softNum; i++)
    {
        SoftwareInfo &software = pSoftware[i];

        if ( (0 == software.m_displayname[0])
            && (0 == software.m_displayversion[0]) )
            continue;

        xmlCheckItem.SetAttribute("名称", software.m_displayname);
        xmlCheckItem.SetAttribute("类型", software.szSoftType);
        xmlCheckItem.SetAttribute("版本", software.m_displayversion);
        xmlCheckItem.SetAttribute("安装时间", software.m_displaytime);
        xmlCheckItem.SetAttribute("路径", software.szInstallLocation);
        xmlCheckPointName.InsertEndChild(xmlCheckItem);
    }
    xmlElements.InsertEndChild(xmlCheckPointName);
}

VOID InsertProcess(TiXmlElement &xmlElements, ProcessInfo* pProcess, int processNum)
{
    TiXmlElement xmlCheckPointName = TiXmlElement("process");
    TiXmlElement xmlCheckItem("item");

    for(int i = 0; i < processNum; i++)
    {
        ProcessInfo &process = pProcess[i];

        xmlCheckItem.SetAttribute("名称", process.proName);
        xmlCheckItem.SetAttribute("PID", process.processid);
        xmlCheckItem.SetAttribute("路径", process.path);
        xmlCheckPointName.InsertEndChild(xmlCheckItem);
    }
    xmlElements.InsertEndChild(xmlCheckPointName);
}

VOID InsertSnmp(TiXmlElement &xmlElements, SNMPService *pSnmpService)
{
    TiXmlElement xmlCheckPointName = TiXmlElement("SNMP");
    TiXmlElement xmlCheckItem("item");

    if (pSnmpService)
    {
        RegistryValueInfo *pRV = pSnmpService->pRegistrValues;
        while (pRV)
        {
            xmlCheckItem.SetAttribute("community", pRV->communities);
            xmlCheckPointName.InsertEndChild(xmlCheckItem);

            pRV = pRV->pNext;
        }
    }
    xmlElements.InsertEndChild(xmlCheckPointName);
}

VOID InsertServices(TiXmlElement &xmlElements, SERVICE_STATUS_INFO1 *pServiceStatus, int serviceNum)
{
    if(pServiceStatus==NULL)
    {
        return;
    }
    TiXmlElement xmlCheckPointName = TiXmlElement("services");
    TiXmlElement xmlCheckItem("item");

    DWORD   dwStartType       = SERVICE_STATT_TYPE_NUM;
    CHAR    *lpBinaryPathName = NULL;

    CHAR *szServiceStatus[] = {
        "未知",       //"UNKNOWN",
        "停止",       //"STOPPED", // 1
        "启动",       //"START_PENDING", // 2
        "停止",       //"STOP_PENDING", // 3
        "启动",      //"RUNNING", // 4
        "暂停",       //"CONTINUE_PENDING", // 5
        "暂停",       //"PAUSE_PENDING", // 6
        "暂停",       //"PAUSED" // 7
    };

    CHAR *szServiceStartType[] = {
        "自动",   //"BOOT_START", // 0
        "自动",   //"SYSTEM_START", // 1
        "自动",   //"AUTO_START", // 2
        "手动",   //"DEMAND_START", // 3
        "禁用",   //"DISABLED", // 4
        "未知",   //"UNKNOWN",  // 5
    };

    struct ServiceRiskLevel
    {
        char szServiceName[64];
        char szRiskLevel[16];
    };
    ServiceRiskLevel    svRiskLevel[] =
    {
        { "Clipbook",           "高风险" },
        { "talk",               "高风险" },
        { "ntalk",              "高风险" },
        { "pop-2",              "高风险" },
        { "sendmail",           "高风险" },
        { "TaskScheduler",      "高风险" },
        { "PrintSpooler",       "高风险" },
        { "TermService",        "高风险" },
        { "RemoteRegistry",     "高风险" },
        { "TlntSvr",            "高风险" },
        { "EventSystem",        "高风险" },
        { "WerSvc",             "高风险" },
        { "ERSvc",              "高风险" },
        { "ClipSrv",            "高风险" },
        { "Alerter",            "高风险" },
        { "Messenger",          "高风险" },
        { "IISADMIN",           "存在风险" },
        { "W3SVC",              "存在风险" },
        { "Schedule",           "低风险" },
        { "Spooler",            "存在风险" },
    };

    char *pRiskLevel;
    for (int i=0; i<serviceNum; i++)
    {
        ENUM_SERVICE_STATUS_PROCESSA& serviceStatusInfo  = pServiceStatus[i].serviceStatusInfo;
        QUERY_SERVICE_CONFIGA& queryServiceConfig = pServiceStatus[i].serviceConfig;

        if (queryServiceConfig.dwStartType < SERVICE_STATT_TYPE_NUM)
        {
            dwStartType = queryServiceConfig.dwStartType;
            lpBinaryPathName = queryServiceConfig.lpBinaryPathName;
        }
        else
        {
            dwStartType = SERVICE_STATT_TYPE_NUM;
            lpBinaryPathName = "";
        }

        BOOL bFind = FALSE;
        int icmpNum = sizeof(svRiskLevel)/sizeof(svRiskLevel[0]);
        int j=0;
        for (j=0; j< icmpNum; j++)
        {
            if (0 == stricmp(serviceStatusInfo.lpServiceName, svRiskLevel[j].szServiceName))
            {
                bFind = TRUE;
                break;
            }
        }

        xmlCheckItem.SetAttribute("名称", serviceStatusInfo.lpDisplayName);
        xmlCheckItem.SetAttribute("服务名", serviceStatusInfo.lpServiceName);
        xmlCheckItem.SetAttribute("状态", szServiceStatus[serviceStatusInfo.ServiceStatusProcess.dwCurrentState]);
        xmlCheckItem.SetAttribute("启动类型", szServiceStartType[dwStartType]);

        if (bFind)
        {
            pRiskLevel = svRiskLevel[j].szRiskLevel;
        }
        else
        {
            pRiskLevel = "一般风险";
        }

        xmlCheckItem.SetAttribute("风险等级", pRiskLevel);
        xmlCheckItem.SetAttribute("路径", lpBinaryPathName);
        xmlCheckPointName.InsertEndChild(xmlCheckItem);
    }
    xmlElements.InsertEndChild(xmlCheckPointName);
}

VOID InsertDiskPartitions(TiXmlElement &elmParent, LogicalDrivesInfo* pLogicDrives, int drivesNum)
{
    //分区
    TiXmlElement xmlDivName = TiXmlElement("disk_partitions");
    TiXmlElement xmlItem("item");

    for (int i = 0; i < drivesNum; i++)
    {
        xmlItem.SetAttribute("盘符", pLogicDrives[i].name);
        xmlDivName.InsertEndChild(xmlItem);
    }
    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertRights(TiXmlElement &elmParent, char *pName, DrivesAccountRights *pRights, int rightsNum)
{
    //磁盘权限
    TiXmlElement xmlDivName = TiXmlElement(pName);
    TiXmlElement xmlItem("item");

    DrivesAccountRights* pDrivesRights = pRights;

    //关于ACCESS_MASK中各个位代表的含义请参考MSDN
    //     string filedesc[] =
    //     {   "FILE_READ_DATA", "FILE_WRITE_DATA", "FILE_APPEND_DATA", "FILE_READ_EA",
    //
    //     "FILE_WRITE_EA", "FILE_EXECUTE", "FILE_DELETE_CHILD", "FILE_READ_ATTRIBUTES",
    //
    //     "FILE_WRITE_ATTRIBUTES", " ", " ", " ",
    //
    //     " ", " ", " ", " ",
    //
    //     "DELETE ", "READ_CONTROL", "WRITE_DAC", "WRITE_OWNER",
    //
    //     "SYNCHRONIZE ", " ", " "," ",
    //
    //     "ACCESS_SYSTEM_SECURITY", "MAXIMUM_ALLOWED", " "," ",
    //
    //     "GENERIC_ALL", "GENERIC_EXECUTE", "GENERIC_WRITE","GENERIC_READ"};
    string filedesc[] =
    {
        "列出文件夹/读取数据", "创建文件/写入数据", "创建文件夹/附加数据", "读取扩展属性",

        "写入扩展属性", "遍历文件夹/执行文件", "删除子文件夹及文件", "读取属性",

        "写入属性", " ", " ", " ",

        " ", " ", " ", " ",

        "删除 ", "读取权限", "写访问DACL", "写入所有者的权限",

        "同步访问 ", " ", " "," ",

        "访问系统安全", "最大允许访问", " "," ",

        "完全控制", "执行", "写入","读取"
    };

    string rights[] = {"允许", "拒绝"};

    char szRights[4096];
    string sRights;
    for (int i = 0; i < rightsNum; i++)
    {
        DrivesAccountRights &typeRights = pDrivesRights[i];

        xmlItem.SetAttribute("路径", typeRights.strDriveName);

        AccountRights *pAccountRt = pDrivesRights[i].pAccountRt;
        sRights = "";
        while(pAccountRt && (pAccountRt->valid))
        {
            AccountRights &accountRt = *pAccountRt;
            sRights += "account=";
            sRights += accountRt.strAccount;

            for (int i = 0; i < 32; i++)
            {
                int nTmpRight = pAccountRt->arrRights[i];
                if (nTmpRight != 0)
                {
                    sRights += filedesc[i] + rights[nTmpRight-1];
                }
            }
            sRights += "|||\n";

            pAccountRt = pAccountRt->pNext;
        }
        xmlItem.SetAttribute("权限", sRights.c_str());
        xmlDivName.InsertEndChild(xmlItem);
    }
    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertDiskRights(TiXmlElement &elmParent, DrivesAccountRights *pRights, int rightsNum)
{
    InsertRights(elmParent, "disk_rights", pRights, rightsNum);
}

VOID InsertSystemRights(TiXmlElement &elmParent, DrivesAccountRights *pRights, int rightsNum)
{
    InsertRights(elmParent, "system_rights", pRights, rightsNum);
}

VOID InsertCPUs(TiXmlElement &elmParent, CpuInfo *pCpuinfo)
{
    //cpu
    TiXmlElement xmlDivName = TiXmlElement("cpu");
    TiXmlElement xmlItem("item");

    if (pCpuinfo)
    {
        CpuInfo &cpuinfo = *pCpuinfo;

        xmlItem.SetAttribute("描述", cpuinfo.brand);
        xmlItem.SetAttribute("序列号", cpuinfo.factoryNumber);
        xmlItem.SetAttribute("型号", cpuinfo.model);
        xmlItem.SetAttribute("主频", cpuinfo.parameterValue);
        xmlItem.SetAttribute("CPU数", cpuinfo.dwNumberOfCpu);
        xmlItem.SetAttribute("核数", cpuinfo.dwNumberOfProcessors);
        xmlDivName.InsertEndChild(xmlItem);
    }
    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertHardDisks(TiXmlElement &elmParent, HardDiskInfo* pHardDisk, int diskNum)
{
    //硬盘
    TiXmlElement xmlDivName = TiXmlElement("hard_disk");
    TiXmlElement xmlItem("item");

    for (int i = 0; i < diskNum; i++)
    {
        HardDiskInfo &hardDisk = pHardDisk[i];

        xmlItem.SetAttribute("描述",    hardDisk.brand);
        xmlItem.SetAttribute("序列号",  hardDisk.factoryNumber);
        char buf[64];
        StorageCapacity2Str(hardDisk.captacity, buf);
        xmlItem.SetAttribute("显存大小",    buf);
        xmlItem.SetAttribute("大小",    buf);
        xmlItem.SetAttribute("型号",    hardDisk.model);
        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertBoard(TiXmlElement &elmParent, MainBoardInfo *pBoardInfo)
{
    //主板
    TiXmlElement xmlDivName = TiXmlElement("board");
    TiXmlElement xmlItem("item");

    if (pBoardInfo)
    {
        MainBoardInfo &boardInfo = *pBoardInfo;

        xmlItem.SetAttribute("描述",    boardInfo.brand);
        xmlItem.SetAttribute("序列号",  boardInfo.factoryNumber);
        xmlItem.SetAttribute("型号",    boardInfo.model);
        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}


VOID InsertMemorys(TiXmlElement &elmParent, MemoryInfo* pMemory)
{
    //内存信息
    TiXmlElement xmlDivName = TiXmlElement("memory");
    TiXmlElement xmlItem("item");

    if (pMemory)
    {
        MemoryInfo &memory = *pMemory;

        char buf[64];
        sprintf(buf, "%u%%", memory.dwMemoryLoad);
        xmlItem.SetAttribute("memoryLoad",  buf);

        StorageCapacity2Str(memory.ullTotalPhys, buf);
        xmlItem.SetAttribute("totalPhys",   buf);

        StorageCapacity2Str(memory.ullAvailPhys, buf);
        xmlItem.SetAttribute("availPhys",   buf);

        StorageCapacity2Str(memory.ullTotalVirtual, buf);
        xmlItem.SetAttribute("totalVirtual",   buf);

        StorageCapacity2Str(memory.ullAvailVirtual, buf);
        xmlItem.SetAttribute("availVirtual",   buf);

        TiXmlElement subXmlItem("item");
        for (int i=0; i<memory.validMemoryNum; i++)
        {
            Win32PhysicalMemory &phyMemory = memory.physicalMemory[i];

            subXmlItem.SetAttribute("capacity", phyMemory.Capacity);
            subXmlItem.SetAttribute("Manufacturer", phyMemory.Manufacturer);
            subXmlItem.SetAttribute("Caption", phyMemory.Caption);
            subXmlItem.SetAttribute("DeviceLocator", phyMemory.DeviceLocator);
            xmlItem.InsertEndChild(subXmlItem);
        }

        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertDisplayCards(TiXmlElement &elmParent, DisplayInfo *pdi)
{
    // 显卡
    TiXmlElement xmlDivName = TiXmlElement("display_card");
    TiXmlElement xmlItem("item");

    if (pdi)
    {
        DisplayInfo &di = *pdi;

        xmlItem.SetAttribute("驱动提供商",  di.brand);
        char buf[64];
        StorageCapacity2Str(di.captacity, buf);
        xmlItem.SetAttribute("显存大小",    buf);
        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertSoundCards(TiXmlElement &elmParent, AudioInfo *pai)
{
    //声卡
    TiXmlElement xmlDivName = TiXmlElement("sound_card");
    TiXmlElement xmlItem("item");

    if (pai)
    {
        AudioInfo &ai = *pai;

        xmlItem.SetAttribute("驱动提供商",  ai.brand);
        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertEthernetAdapters(TiXmlElement &elmParent, NetworkCardInfo* pEthernetAdapter, int ethnetNum)
{
    //网卡
    TiXmlElement xmlDivName = TiXmlElement("network_card");
    TiXmlElement xmlItem("item");

    for (int i = 0; i < ethnetNum; i++)
    {
        NetworkCardInfo &netcard = pEthernetAdapter[i];

        xmlItem.SetAttribute("驱动提供商",  netcard.brand);
        xmlItem.SetAttribute("描述",        netcard.softSetting);
        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertSecurityOptions(TiXmlElement &elmParent, char *pName, SecurityOptions *pSecurityOpt, int optNum)
{
    //安全选项
    TiXmlElement xmlDivName = TiXmlElement(pName);
    TiXmlElement xmlItem("item");

    for (int i = 0; i < optNum; i++)
    {
        SecurityOptions &securityOpt = pSecurityOpt[i];

        xmlItem.SetAttribute("名称",        securityOpt.szName);
        xmlItem.SetAttribute("安全设置",    securityOpt.szValue);
        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}
VOID InsertRegistrySetsOptions(TiXmlElement &elmParent, SecurityOptions *pSecurityOpt, int optNum)
{
    //注册表设置
    InsertSecurityOptions(elmParent, "registry_set", pSecurityOpt, optNum);
}
VOID InsertEventlogsOptions(TiXmlElement &elmParent, SecurityOptions *pSecurityOpt, int optNum)
{
    //eventlog
    InsertSecurityOptions(elmParent, "eventlog", pSecurityOpt, optNum);
}

VOID InsertUsers(TiXmlElement &elmParent, USER_INFO_2 *pUserInfo, int userNum)
{
    //账户信息
    TiXmlElement xmlDivName = TiXmlElement("users");
    TiXmlElement xmlItem("item");

    int  userNameLen = 0;
    CHAR strUserName[MAX_PATH];
    CHAR strDisabled[100];
    CHAR PasswordChangeable[100];
    CHAR PasswordExpires[100];
    CHAR PasswordRequired[100];
    CHAR Lockout[100];
    CHAR strHideUser[50];

    for (int i=0; i<userNum; i++)
    {
        USER_INFO_2 &userInfo = pUserInfo[i];

        memset(strUserName, 0, sizeof(strUserName));
        memset(strDisabled, 0, sizeof(strDisabled));
        memset(PasswordChangeable, 0, sizeof(PasswordChangeable));
        memset(PasswordExpires, 0, sizeof(PasswordExpires));
        memset(PasswordRequired, 0, sizeof(PasswordRequired));
        memset(Lockout, 0, sizeof(Lockout));
        widechar_to_multibyte(userInfo.usri2_name, wcslen(userInfo.usri2_name), strUserName, sizeof(strUserName));

        if (userInfo.usri2_flags&UF_ACCOUNTDISABLE)
        {
            strcpy(strDisabled, "账户已禁用");
        }
        else
        {
            strcpy(strDisabled, "账户已启用");
        }

        if (userInfo.usri2_flags&UF_PASSWD_CANT_CHANGE)
            strcpy(PasswordChangeable, "用户不能更改密码");
        else
            strcpy(PasswordChangeable, "用户能更改密码");

        if (userInfo.usri2_flags&UF_DONT_EXPIRE_PASSWD)
            strcpy(PasswordExpires, "密码永不过期");
        else
            strcpy(PasswordExpires, "密码不为永不过期");

        strcpy(PasswordRequired, "用户下次登录时不须更改密码");

        if (userInfo.usri2_flags&UF_LOCKOUT)
            strcpy(Lockout, "账户已锁定");
        else
            strcpy(Lockout, "账户未锁定");

        userNameLen = strlen(strUserName);
        if ((userNameLen > 0) && (strUserName[userNameLen-1] == '$'))
        {
            strcpy(strHideUser, "隐藏用户");
        }
        else
        {
            strcpy(strHideUser, "非隐藏用户");
        }

        xmlItem.SetAttribute("用户名",          strUserName);
        xmlItem.SetAttribute("是否禁用",        strDisabled);
        xmlItem.SetAttribute("是否能更改密码",  PasswordChangeable);
        xmlItem.SetAttribute("是否期限",        PasswordExpires);
        xmlItem.SetAttribute("是否锁定",        Lockout);
        xmlItem.SetAttribute("下次登录是是否需要更改密码",  PasswordRequired);
        xmlItem.SetAttribute("是否隐藏用户",    strHideUser);
        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertShares(TiXmlElement &elmParent, SHARE_INFO_502 *pShareInfo, int shareNum)
{
    //共享
    TiXmlElement xmlDivName = TiXmlElement("share");
    TiXmlElement xmlItem("item");

    CHAR strPathName[MAX_PATH] = {0};
    CHAR strShareName[MAX_PATH] = {0};
    CHAR strShareType[MAX_PATH] = {0};

    for (int i=0; i<shareNum; i++)
    {
        SHARE_INFO_502 &shareInfo = pShareInfo[i];

        memset(strShareName, 0, sizeof(strShareName));
        memset(strPathName, 0, sizeof(strPathName));
        memset(strShareType, 0, sizeof(strShareType));

        widechar_to_multibyte(shareInfo.shi502_netname, wcslen(shareInfo.shi502_netname), strShareName, sizeof(strShareName));
        widechar_to_multibyte(shareInfo.shi502_path, wcslen(shareInfo.shi502_path), strPathName, sizeof(strPathName));
        widechar_to_multibyte(shareInfo.shi502_remark, wcslen(shareInfo.shi502_remark), strShareType, sizeof(strShareType));

        xmlItem.SetAttribute("共享名",      strShareName);
        xmlItem.SetAttribute("共享路径",    strPathName);
        xmlItem.SetAttribute("描述",        strShareType);
        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertActivePorts(TiXmlElement &elmParent, PortInfo *pPortInfo)
{
    //端口
    TiXmlElement xmlDivName = TiXmlElement("active_port");
    TiXmlElement xmlItem("item");

    while (NULL != pPortInfo)
    {
        PortInfo &port = *pPortInfo;
        pPortInfo = pPortInfo->pNext;

        xmlItem.SetAttribute("名称",    port.name);
        xmlItem.SetAttribute("本地IP",  port.localAddr);
        xmlItem.SetAttribute("本地端口",port.localPort);
        xmlItem.SetAttribute("远程IP",  port.mstcAddr);
        xmlItem.SetAttribute("远程端口",port.mstscPort);
        xmlItem.SetAttribute("状态",    port.state);
        xmlItem.SetAttribute("PID",     port.pId);
        xmlItem.SetAttribute("路径",    port.path);
        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertAntivirus(TiXmlElement &elmParent, AntivirusSoft *pAntiVirusSoft, int antivirusNum)
{
    // 杀毒软件
    TiXmlElement xmlDivName = TiXmlElement("antivirus");
    TiXmlElement xmlItem("item");

    for (int i=0; i<antivirusNum; i++)
    {
        AntivirusSoft &antivirus = pAntiVirusSoft[i];

        // 只显示已安装的杀毒软件
        if (0 == antivirus.szVersion[0])
            continue;

        xmlItem.SetAttribute("名称",            antivirus.szDisplayName);
        xmlItem.SetAttribute("版本",            antivirus.szVersion);
        xmlItem.SetAttribute("运行状态",        antivirus.szRunStatus);
        xmlItem.SetAttribute("病毒库版本时间",  antivirus.szUpdateTime);
        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertRuns(TiXmlElement &elmParent, RunItems *pRunItems)
{
    // 开机启动项
    TiXmlElement xmlDivName = TiXmlElement("run_on_start");
    TiXmlElement xmlItem("item");

    while(NULL != pRunItems)
    {
        RunItems &run = *pRunItems;
        pRunItems = pRunItems->pNext;

        xmlItem.SetAttribute("名称",    run.name);
        xmlItem.SetAttribute("启动方式",run.szRunType);
        xmlItem.SetAttribute("命令行",  run.path);
        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertPatchsInstalled(TiXmlElement &elmParent, SystemDefectInfo *pSystemDefInstall)
{
    // 已安装的补丁
    TiXmlElement xmlDivName = TiXmlElement("install_patch");
    TiXmlElement xmlItem("item");

    while (NULL != pSystemDefInstall)
    {
        SystemDefectInfo &patch = *pSystemDefInstall;
        pSystemDefInstall = pSystemDefInstall->pNext;

        xmlItem.SetAttribute("补丁号",  patch.defectNum);
        xmlItem.SetAttribute("补丁描述",patch.defectName);
        xmlItem.SetAttribute("安装时间",patch.defectDate);
        xmlItem.SetAttribute("发布时间",patch.strPubdate);
        xmlItem.SetAttribute("严重等级",patch.patchLevel);
        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertCheckResult(TiXmlElement &elmParent, char *pName, DtckResults* pDtckResults)
{
    TiXmlElement xmlDivName = TiXmlElement(pName);
    TiXmlElement xmlItem("item");

    while(pDtckResults)
    {
        DtckResult &dtResult = pDtckResults->result;
        pDtckResults = pDtckResults->pNext;

        xmlItem.SetAttribute("名称",        dtResult.strCkPoint);
        xmlItem.SetAttribute("安全设置",    dtResult.strResult);
        xmlDivName.InsertEndChild(xmlItem);
    }

    elmParent.InsertEndChild(xmlDivName);
}

VOID InsertPasswordPolicies(TiXmlElement &elmParent, DtckResults* pDtckResults)
{
    InsertCheckResult(elmParent, "password_policy", pDtckResults);
}

VOID InsertAuditPolicies(TiXmlElement &elmParent, DtckResults* pDtckResults)
{
    InsertCheckResult(elmParent, "audit_policy", pDtckResults);
}

VOID InsertAccLockPolicys(TiXmlElement &elmParent, DtckResults* pDtckResults)
{
    InsertCheckResult(elmParent, "acclock_policy", pDtckResults);
}

VOID InsertUserRightAssignment(TiXmlElement &elmParent, DtckResults* pDtckResults)
{
    InsertCheckResult(elmParent, "userright_assignment", pDtckResults);
}

VOID InsertSecurityOption(TiXmlElement &elmParent, DtckResults* pDtckResults)
{
    InsertCheckResult(elmParent, "security_option", pDtckResults);
}

VOID InsertAutoAdminLogin(TiXmlElement &elmParent, DtckResults* pDtckResults)
{
    InsertCheckResult(elmParent, "auto_login", pDtckResults);
}

VOID InsertDriverAutoOperation(TiXmlElement &elmParent, DtckResults* pDtckResults)
{
    InsertCheckResult(elmParent, "driver_auto_open", pDtckResults);
}

VOID InsertMakeDumpFile(TiXmlElement &elmParent, DtckResults* pDtckResults)
{
    InsertCheckResult(elmParent, "make_dump_file", pDtckResults);
}

VOID InsertNetConnects(TiXmlElement &elmParent, DtckResults* pDtckResults)
{
    InsertCheckResult(elmParent, "net_connect", pDtckResults);
}
VOID InsertGroupPolicys(TiXmlElement &elmParent, DtckResults* pDtckResults)
{
    InsertCheckResult(elmParent, "group_policy", pDtckResults);
}

VOID InsertAllItems(TiXmlElement &elmParent)
{
    //获取主机所有检查项   （重复）
//    InsertStandardItems(elmParent, CheckResultResouce::pDtckResults);

    qInstallMessageHandler(outputMessage);
    // USB
    InsertUSBItems(elmParent, CheckResultResouce::pUsbHistory);
    InsertDeepUSBItems(elmParent);
#ifdef DEBUGLOG
    qDebug()<<"usb";
#endif

    // 浏览器
    InsertBrowserItems(elmParent, CheckResultResouce::pIeHistory, CheckResultResouce::pFirefoxHistory, CheckResultResouce::pChromeHistory);
    InsertDeepBrowserItems(elmParent);
#ifdef DEBUGLOG
    qDebug()<<"browser";
#endif

    // 系统信息
    BiosInfo* pBiosInfo = CheckResultResouce::pBiosInfo;
    char* pBiosParamValue = "未知";
    if (pBiosInfo)
        pBiosParamValue = pBiosInfo->parameterValue;
    InsertSystemOs(elmParent, CheckResultResouce::pOsVersion, CheckResultResouce::osInstallTime,
        CheckResultResouce::computerName, CheckResultResouce::pBootTime, pBiosParamValue);
#ifdef DEBUGLOG
    qDebug()<<"sys";
#endif

    // 软件信息
    InsertSoftwares(elmParent, CheckResultResouce::pSoft, CheckResultResouce::softNum);
#ifdef DEBUGLOG
    qDebug()<<"soft";
#endif

    // 进程信息
    InsertProcess(elmParent, CheckResultResouce::pProcess, CheckResultResouce::processNum);
#ifdef DEBUGLOG
    qDebug()<<"process";
#endif

    // 服务信息
    InsertServices(elmParent, CheckResultResouce::pServiceStatus, CheckResultResouce::servicesNum);
#ifdef DEBUGLOG
    qDebug()<<"service";
#endif

    // 服务信息
    InsertSnmp(elmParent, CheckResultResouce::pSnmpService);
#ifdef DEBUGLOG
    qDebug()<<"snmp";
#endif

    // 硬件信息
    // 分区
    InsertDiskPartitions(elmParent, CheckResultResouce::pLogicDrives, CheckResultResouce::logicDrivesNum);
#ifdef DEBUGLOG
    qDebug()<<"diskpar";
#endif

    // 磁盘权限
    InsertDiskRights(elmParent, CheckResultResouce::pDrivesRights, CheckResultResouce::drivesRightsNum);
#ifdef DEBUGLOG
    qDebug()<<"diskright";
#endif

    // system权限
    InsertSystemRights(elmParent, CheckResultResouce::pSystemRights, CheckResultResouce::systemRightsNum);
#ifdef DEBUGLOG
    qDebug()<<"sysright";
#endif

    // CPU
    InsertCPUs(elmParent, CheckResultResouce::pCpuInfo);
#ifdef DEBUGLOG
    qDebug()<<"cpu";
#endif

    // 硬盘
    InsertHardDisks(elmParent, CheckResultResouce::pHardDisk, CheckResultResouce::diskNum);
#ifdef DEBUGLOG
    qDebug()<<"hard";
#endif

    // 主板
    InsertBoard(elmParent, CheckResultResouce::pBoardInfo);
#ifdef DEBUGLOG
    qDebug()<<"board";
#endif

    // 内存
    InsertMemorys(elmParent, CheckResultResouce::pMemory);
#ifdef DEBUGLOG
    qDebug()<<"memory";
#endif

    // 显卡
    InsertDisplayCards(elmParent, CheckResultResouce::pDisplayCard);
#ifdef DEBUGLOG
    qDebug()<<"display";
#endif

    // 声卡
    InsertSoundCards(elmParent, CheckResultResouce::pAudio);
#ifdef DEBUGLOG
    qDebug()<<"sound";
#endif

    // 网卡信息
    InsertEthernetAdapters(elmParent, CheckResultResouce::pNetwork, CheckResultResouce::netcardNum);
#ifdef DEBUGLOG
    qDebug()<<"ada";
#endif


    // 安全选项
    InsertSecurityOptions(elmParent, "security_opt", CheckResultResouce::pSecurityOpt, CheckResultResouce::secOptionsNum);
#ifdef DEBUGLOG
    qDebug()<<"sec";
#endif
    // 注册表设置
    InsertRegistrySetsOptions(elmParent, CheckResultResouce::pRegistrySets, CheckResultResouce::regOptionsNum);
#ifdef DEBUGLOG
    qDebug()<<"set";
#endif
    // windows日志
    InsertEventlogsOptions(elmParent, CheckResultResouce::pEventlogs, CheckResultResouce::eventlogNum);
#ifdef DEBUGLOG
    qDebug()<<"logs";
#endif

    // 账户信息
    InsertUsers(elmParent, CheckResultResouce::pUserInfo, CheckResultResouce::usersNum);
#ifdef DEBUGLOG
    qDebug()<<"users";
#endif

    // 共享目录
    InsertShares(elmParent, CheckResultResouce::pShareInfo, CheckResultResouce::shareNum);
#ifdef DEBUGLOG
    qDebug()<<"share";
#endif

    // 端口信息
    InsertActivePorts(elmParent, CheckResultResouce::pPortInfo);
#ifdef DEBUGLOG
    qDebug()<<"port";
#endif

    // 杀毒
    InsertAntivirus(elmParent, CheckResultResouce::pAntivirusSoft, CheckResultResouce::antivirusSoftNum);
#ifdef DEBUGLOG
    qDebug()<<"anti";
#endif

    // 启动项
    InsertRuns(elmParent, CheckResultResouce::pRunItems);
#ifdef DEBUGLOG
    qDebug()<<"runs";
#endif

    // 已安装的补丁
    InsertPatchsInstalled(elmParent, CheckResultResouce::pSystemDefectInfo);
#ifdef DEBUGLOG
    qDebug()<<"pachs";
#endif

//    // 密码策略
//    InsertPasswordPolicies(elmParent, CheckResultResouce::pDtPwdPolicy);

//    // 审核策略
//    InsertAuditPolicies(elmParent, CheckResultResouce::pDtAuditPolicy);

//    // 访问控制策略
//    InsertAccLockPolicys(elmParent, CheckResultResouce::pDtAccLockPolicy);

    // 用户权限分配
    InsertUserRightAssignment(elmParent, CheckResultResouce::pDtUserRightAssignment);
#ifdef DEBUGLOG
    qDebug()<<"assi";
#endif

    // 自动登录
    InsertAutoAdminLogin(elmParent, CheckResultResouce::pDtAutoAdminLogin);
#ifdef DEBUGLOG
    qDebug()<<"adminlo";
#endif

    // 驱动器自动运行
    InsertDriverAutoOperation(elmParent, CheckResultResouce::pDtDriverAutoOperation);
#ifdef DEBUGLOG
    qDebug()<<"auto";
#endif

    // dump文件
    InsertMakeDumpFile(elmParent, CheckResultResouce::pDtMakeDumpFile);
#ifdef DEBUGLOG
    qDebug()<<"dump";
#endif

    // 网络连接
    InsertNetConnects(elmParent, CheckResultResouce::pDtNetConnect);
#ifdef DEBUGLOG
    qDebug()<<"net";
#endif

    //  敏感词
    InsertSensItems(elmParent);
#ifdef DEBUGLOG
    qDebug()<<"sens";
#endif

//    // 组策略
//    InsertGroupPolicys(elmParent, CheckResultResouce::pDtGroupPolicy);
}


void    InsertHostInfo(TiXmlElement *pElmParent)
{
    // <host_info>
    //     <hostname>MY-PC</hostname>
    //     <os>Windows 7 Ultimate</os>
    //     <os_version> 6.1 (7601) Service Pack 1</os_version>
    //     <uptime>0天08小时51分36秒</uptime>
    //     <cpu>GenuineIntel Intel(R) Core(TM) i5-2400 CPU @ 3.10GHz 3101</cpu>
    //     <bios>BIOS Date: 02/15/11 09:36:59 Ver: 04.06.04</bios>
    //     <baseboard>
    //     <item SerialNumber="..CN7360413I00T6." Product="0Y2MRG" Manufacturer="Dell Inc."/>
    //     </baseboard>
    //     <display_adapter>AMD Radeon HD 6450 显存容量：1073741824B</display_adapter>
    //     <memory_list>
    //     <item Manufacturer="Physical Memory" Capacity="2147483648"/>
    //     <item Manufacturer="Physical Memory" Capacity="2147483648"/>
    //     </memory_list>
    //     <hard_disk_list>
    //     <item size="500105249280" model="WDC WD5000AAKX-753CA0 ATA Device"/>
    //     </hard_disk_list>
    //     ……
    // </host_info>

    char szBuf[256];
    int i;
    TiXmlElement xmlHostInfo( "host_info" );

    // <hostname>MY-PC</hostname>
    TiXmlElement xmlCheckPointName( "hostname" );
    xmlCheckPointName.InsertEndChild(TiXmlText(CheckResultResouce::computerName));
    xmlHostInfo.InsertEndChild(xmlCheckPointName );

    // <os>Windows 7 Ultimate</os>
    xmlCheckPointName = TiXmlElement( "os" );
    if (CheckResultResouce::pOsVersion)
        sprintf(szBuf, "%s", CheckResultResouce::pOsVersion->systemName);
    else
        strcpy(szBuf, "未知");

    xmlCheckPointName.InsertEndChild(TiXmlText(szBuf));
    xmlHostInfo.InsertEndChild( xmlCheckPointName );

    // <os_version> 6.1 (7601) Service Pack 1</os_version>
    xmlCheckPointName = TiXmlElement( "os_version" );
    OsVersionInfo *pOsVersion = CheckResultResouce::pOsVersion;
    if (pOsVersion)
        sprintf(szBuf, "%s.%s (%s) %s", pOsVersion->majorVersion, pOsVersion->MinorVersion, pOsVersion->buildNumber, pOsVersion->CSDVersion);
    else
        strcpy(szBuf, "未知");

    xmlCheckPointName.InsertEndChild(TiXmlText(szBuf));
    xmlHostInfo.InsertEndChild(xmlCheckPointName );

    // <uptime>0天08小时51分36秒</uptime>
    xmlCheckPointName = TiXmlElement( "uptime" );
    xmlCheckPointName.InsertEndChild( TiXmlText(CheckResultResouce::pBootTime));
    xmlHostInfo.InsertEndChild( xmlCheckPointName );

    // <cpu>GenuineIntel Intel(R) Core(TM) i5-2400 CPU @ 3.10GHz 3101</cpu>
    xmlCheckPointName = TiXmlElement( "cpu" );

    CpuInfo *pCpuinfo = CheckResultResouce::pCpuInfo;
    if (pCpuinfo)
    {
        sprintf(szBuf, "序列号：%s, 型号: %s, 主频: %s, CPU数：%d, 核数: %d",
            pCpuinfo->factoryNumber, pCpuinfo->model, pCpuinfo->parameterValue, pCpuinfo->dwNumberOfCpu, pCpuinfo->dwNumberOfProcessors);
    }
    else
        strcpy(szBuf, "未知");
    xmlCheckPointName.InsertEndChild( TiXmlText(szBuf));
    xmlHostInfo.InsertEndChild( xmlCheckPointName );

    //     <bios>BIOS Date: 02/15/11 09:36:59 Ver: 04.06.04</bios>
    xmlCheckPointName = TiXmlElement("bios");
    BiosInfo *pBiosInfo = CheckResultResouce::pBiosInfo;
    if (pBiosInfo)
        sprintf(szBuf, "%s", pBiosInfo->parameterValue);
    else
        strcpy(szBuf, "未知");
    xmlCheckPointName.InsertEndChild(TiXmlText(szBuf));
    xmlHostInfo.InsertEndChild(xmlCheckPointName);

    //     <baseboard>
    //         <item SerialNumber="..CN7360413I00T6." Product="0Y2MRG" Manufacturer="Dell Inc."/>
    //     </baseboard>
    xmlCheckPointName = TiXmlElement("baseboard");
    MainBoardInfo *pmbi = CheckResultResouce::pBoardInfo;
    TiXmlElement xmlCheckItem("item");
    if (pmbi)
    {
        xmlCheckItem.SetAttribute("Manufacturer", pmbi->brand);
        xmlCheckItem.SetAttribute("SerialNumber", pmbi->factoryNumber);
        xmlCheckItem.SetAttribute("Product", pmbi->model);
    }
    else
    {
        xmlCheckItem.SetAttribute("Manufacturer", "未知");
        xmlCheckItem.SetAttribute("SerialNumber", "未知");
        xmlCheckItem.SetAttribute("Product", "未知");
    }
    xmlCheckPointName.InsertEndChild(xmlCheckItem);
    xmlHostInfo.InsertEndChild(xmlCheckPointName);

    //     <display_adapter>AMD Radeon HD 6450 显存容量：1073741824B</display_adapter>
    xmlCheckPointName = TiXmlElement("display_adapter");
    DisplayInfo *pDisplayCd = CheckResultResouce::pDisplayCard;
    if (pDisplayCd)
    {
        char buf[64];
        StorageCapacity2Str(pDisplayCd->captacity, buf);
        sprintf(szBuf, "%s 容量：%s", pDisplayCd->brand, buf);
    }
    else
        strcpy(szBuf, "未知");
    xmlCheckPointName.InsertEndChild(TiXmlText(szBuf));
    xmlHostInfo.InsertEndChild(xmlCheckPointName);
    //     <memory_list>
    //     <item Manufacturer="Physical Memory" Capacity="2147483648"/>
    //     <item Manufacturer="Physical Memory" Capacity="2147483648"/>
    //     </memory_list>
    xmlCheckPointName = TiXmlElement("memory_list");
    MemoryInfo *pMemory = CheckResultResouce::pMemory;
    if (pMemory)
    {
        MemoryInfo &memory = *pMemory;
        xmlCheckItem = TiXmlElement("item");

        if (memory.validMemoryNum > 0)
        {
            xmlCheckItem.SetAttribute("Manufacturer", memory.physicalMemory[0].Manufacturer);
        }
        xmlCheckItem.SetAttribute("Capacity", memory.ullTotalPhys);
        xmlCheckPointName.InsertEndChild(xmlCheckItem);
    }
    xmlHostInfo.InsertEndChild(xmlCheckPointName);
    //     <hard_disk_list>
    //     <item size="500105249280" model="WDC WD5000AAKX-753CA0 ATA Device"/>
    //     </hard_disk_list>
    xmlCheckPointName = TiXmlElement("hard_disk_list");
    HardDiskInfo* pHardDisk = CheckResultResouce::pHardDisk;
    for (int i = 0; i < CheckResultResouce::diskNum; i++)
    {
        xmlCheckItem = TiXmlElement("item");
        xmlCheckItem.SetAttribute("size", pHardDisk[i].size);
        xmlCheckItem.SetAttribute("model", pHardDisk[i].model);
        xmlCheckPointName.InsertEndChild(xmlCheckItem);
    }
    xmlHostInfo.InsertEndChild(xmlCheckPointName);

    // share
    TiXmlElement    xmlShareList("share_list");

    SHARE_INFO_502 *pSharInfo;
    CHAR strPathName[MAX_PATH]  = {0};
    CHAR strShareName[MAX_PATH] = {0};
    CHAR strShareType[MAX_PATH] = {0};

    for (int i=0; i<CheckResultResouce::shareNum; i++)
    {
        pSharInfo = &CheckResultResouce::pShareInfo[i];

        memset(strShareName, 0, sizeof(strShareName));
        memset(strPathName,  0, sizeof(strPathName));
        memset(strShareType, 0, sizeof(strShareType));

        widechar_to_multibyte(pSharInfo->shi502_netname, wcslen(pSharInfo->shi502_netname), strShareName, sizeof(strShareName));
        widechar_to_multibyte(pSharInfo->shi502_path, wcslen(pSharInfo->shi502_path), strPathName, sizeof(strPathName));
        widechar_to_multibyte(pSharInfo->shi502_remark, wcslen(pSharInfo->shi502_remark), strShareType, sizeof(strShareType));
        //sprintf_s(item.strResult, "共享文件名：%s 路径:%s", strShareName, strPathName);
        TiXmlElement xmlShareItem("item");
        xmlShareItem.SetAttribute("type", strShareType);
        xmlShareItem.SetAttribute("name", strShareName);
        xmlShareItem.SetAttribute("path", strPathName);
        xmlShareList.InsertEndChild(xmlShareItem);
    }

    xmlHostInfo.InsertEndChild(xmlShareList);

    TiXmlElement xmlUserList("user_list");
    USER_INFO_2 *pUserInfo;
    CHAR strUserName[MAX_PATH];
    CHAR strDisabled[10];

    for (int i=0; i<CheckResultResouce::usersNum; i++)
    {
        pUserInfo = &CheckResultResouce::pUserInfo[i];

        memset(strUserName, 0, sizeof(strUserName));
        memset(strDisabled, 0, sizeof(strDisabled));
        //WideCharToMultiByte(CP_ACP, 0, pUserInfo->usri1_name, wcslen(pUserInfo->usri1_name), strUserName, MAX_PATH, NULL, FALSE);
        widechar_to_multibyte(pUserInfo->usri2_name, wcslen(pUserInfo->usri2_name), strUserName, sizeof(strUserName));

        if (pUserInfo->usri2_flags&UF_ACCOUNTDISABLE)
        {
            strcpy(strDisabled, "false");
        }
        else
        {
            strcpy(strDisabled, "true");
        }

        TiXmlElement xmlUserItem("item");
        xmlUserItem.SetAttribute("Caption", strUserName);
        xmlUserItem.SetAttribute("Disabled", strDisabled);

        if (pUserInfo->usri2_flags&UF_PASSWD_CANT_CHANGE)
            strcpy(strDisabled, "false");
        else
            strcpy(strDisabled, "true");
        xmlUserItem.SetAttribute("PasswordChangeable", strDisabled);

        if (pUserInfo->usri2_flags&UF_DONT_EXPIRE_PASSWD)
            strcpy(strDisabled, "false");
        else
            strcpy(strDisabled, "true");
        xmlUserItem.SetAttribute("PasswordExpires", strDisabled);

        // 			if (pUserInfo->usri2_flags&UF_DONT_EXPIRE_PASSWD)
        // 				strcpy(strDisabled, "false");
        // 			else
        // 				strcpy(strDisabled, "true");
        strcpy(strDisabled, "false");
        xmlUserItem.SetAttribute("PasswordRequired", strDisabled);

        if (pUserInfo->usri2_flags&UF_LOCKOUT)
            strcpy(strDisabled, "true");
        else
            strcpy(strDisabled, "false");
        xmlUserItem.SetAttribute("Lockout", strDisabled);

        xmlUserList.InsertEndChild(xmlUserItem);
    }
    xmlHostInfo.InsertEndChild(xmlUserList);
    //
    TiXmlElement xmlPatchList("patch_list");
    SystemDefectInfo *pSystemDefInstall = CheckResultResouce::pSystemDefectInfo;
    while (NULL != pSystemDefInstall)
    {
        TiXmlElement xmlPatchItem("item");
        xmlPatchItem.SetAttribute("Description", pSystemDefInstall->defectName);
        xmlPatchItem.SetAttribute("HotFixID", pSystemDefInstall->defectNum);
        xmlPatchItem.SetAttribute("InstalledOn", pSystemDefInstall->defectDate);
        xmlPatchItem.SetAttribute("Pubdate", pSystemDefInstall->strPubdate);
        xmlPatchItem.SetAttribute("SeverityLevel", GetPatchLevel(pSystemDefInstall->patchLevel));
        xmlPatchList.InsertEndChild(xmlPatchItem);
        pSystemDefInstall = pSystemDefInstall->pNext;
    }
    xmlHostInfo.InsertEndChild(xmlPatchList);

    //软件
    TiXmlElement xmlSoftList("software_list");

    SoftwareInfo *pSoftware = CheckResultResouce::pSoft;
    for (i = 0; i < CheckResultResouce::softNum; i++)
    {
        if ( (0 == pSoftware[i].m_displayname[0])
            && (0 == pSoftware[i].m_displayversion[0]) )
            continue;
        TiXmlElement xmlItem("item");
        xmlItem.SetAttribute("Caption",     pSoftware[i].m_displayname);
        //xmlItem.SetAttribute("Type",        pSoftware[i].szSoftType);
        xmlItem.SetAttribute("Version",     pSoftware[i].m_displayversion);
        xmlItem.SetAttribute("InstallDate", pSoftware[i].m_displaytime);
        xmlItem.SetAttribute("PackageCache",pSoftware[i].szInstallLocation);
        //xmlItem.SetAttribute("Vendor", "");
        xmlSoftList.InsertEndChild(xmlItem);
    }
    xmlHostInfo.InsertEndChild(xmlSoftList);

    // 进程
    TiXmlElement xmlProcessList("process_list");
    ProcessInfo* pProcess = CheckResultResouce::pProcess;
    for(i = 0; i < CheckResultResouce::processNum; i++)
    {
        TiXmlElement xmlItem("item");
        xmlItem.SetAttribute("Caption", pProcess[i].proName);
        xmlItem.SetAttribute("Processed", pProcess[i].processid);
        xmlItem.SetAttribute("Path", pProcess[i].path);
        xmlProcessList.InsertEndChild(xmlItem);
    }
    xmlHostInfo.InsertEndChild(xmlProcessList);

    //CHardware chd;
    // Ethernet Adapter
    NetworkCardInfo* pEthernetAdapter = CheckResultResouce::pNetwork;
    TiXmlElement xmlAdapterList("network_adapter_list");
    for (int i = 0; i < CheckResultResouce::netcardNum; i++)
    {
        TiXmlElement xmlNetItem("item");
        xmlNetItem.SetAttribute("Caption", pEthernetAdapter[i].brand);
        xmlNetItem.SetAttribute("MACAddress", pEthernetAdapter[i].MACAddress);
        xmlNetItem.SetAttribute("IPAddress", pEthernetAdapter[i].IPAddress);
        xmlNetItem.SetAttribute("IPSubnet", pEthernetAdapter[i].IPMask);
        xmlNetItem.SetAttribute("DefaultIPGateway", pEthernetAdapter[i].Gateway);
        xmlNetItem.SetAttribute("DNSServerSearchOrder", CheckResultResouce::szDns);
        xmlNetItem.SetAttribute("NetConnectionID", pEthernetAdapter[i].brand);
        xmlAdapterList.InsertEndChild(xmlNetItem);
    }
    xmlHostInfo.InsertEndChild(xmlAdapterList);

    TiXmlElement xmlPortList("active_port_list");
    PortInfo *pPortInfo = CheckResultResouce::pPortInfo;
    while (NULL != pPortInfo)
    {
        TiXmlElement xmlPortItem("item");
        xmlPortItem.SetAttribute("protocol",    pPortInfo->name);
        xmlPortItem.SetAttribute("Localaddr",   pPortInfo->localAddr);
        xmlPortItem.SetAttribute("Localport",   pPortInfo->localPort );
        xmlPortItem.SetAttribute("Remoteaddr",  pPortInfo->mstcAddr);
        xmlPortItem.SetAttribute("Remoteport",  pPortInfo->mstscPort);
        xmlPortItem.SetAttribute("State",       pPortInfo->state);
        xmlPortItem.SetAttribute("Processeid",  pPortInfo->pId);
        xmlPortItem.SetAttribute("Path",        pPortInfo->path);
        xmlPortList.InsertEndChild(xmlPortItem);
        pPortInfo = pPortInfo->pNext;
    }
    xmlHostInfo.InsertEndChild(xmlPortList);

    //杀毒软件
    TiXmlElement xmlAntivirusList("Antivirusproduct");
    AntivirusSoft   *pAntiVirusSoft = CheckResultResouce::pAntivirusSoft;
    for (int i=0; i<CheckResultResouce::antivirusSoftNum; i++)
    {
        // 只显示已安装的杀毒软件
        if (0 == pAntiVirusSoft[i].szVersion[0])
            continue;

        TiXmlElement xmlAntivirusItem("item");
        xmlAntivirusItem.SetAttribute("Caption", pAntiVirusSoft[i].szDisplayName);
        xmlAntivirusItem.SetAttribute("Version", pAntiVirusSoft[i].szVersion);
        xmlAntivirusItem.SetAttribute("RunStatus", pAntiVirusSoft[i].szRunStatus);
        xmlAntivirusItem.SetAttribute("VirusUpDate", pAntiVirusSoft[i].szUpdateTime);
        xmlAntivirusList.InsertEndChild(xmlAntivirusItem);
    }
    xmlHostInfo.InsertEndChild(xmlAntivirusList);

    pElmParent->InsertEndChild( xmlHostInfo );
}

BOOL    InsertLevelResult(TiXmlElement *pElmItems, CHECK_RESULT_GUID *pCheckResultGuid, int iGuidNum)
{
    BOOL    bValid;                 // 是否有效
    INT32	nResult;			    // 判定值- 0-无效 1-符合、2-不符合、4-部分符合8-人工判断
    CHECK_POINT_GUID    tCheckGuid; // 唯一标识符
    char	strComment[512];	    // 参考的标准建议
    CHAR    szGUID[][16] = { "GUID1", "GUID2", "GUID3", "GUID4" };
    int     iGuidSize = sizeof(szGUID)/sizeof(szGUID[0]);
    int     iIndex;

    if (iGuidNum > iGuidSize)
        iGuidNum = iGuidSize;

    //     <GUID1>
    //         <Valid>0</Valid>        // 1有效，0无效
    //         <Result>1</Result>      // 判定值- 0-无效 1-符合、2-不符合、4-部分符合8-人工判断
    //         <GUID>abcd-efgh-ijkl-nopq<GUID>
    //         <Reference>参考意见</Reference>
    //     </GUID1>

    char szBuf[32];
    for (iIndex=0; iIndex<iGuidNum; iIndex++)
    {
        TiXmlElement xmlElmChild( szGUID[iIndex] );
        TiXmlElement xmlElmChildSub("Valid");
        itoa(pCheckResultGuid[iIndex].bValid, szBuf, 10);
        TiXmlText xmlText( szBuf );
        xmlElmChildSub.InsertEndChild( xmlText );
        xmlElmChild.InsertEndChild( xmlElmChildSub );

        xmlElmChildSub    = TiXmlElement("Result");
        itoa(pCheckResultGuid[iIndex].nResult, szBuf, 10);
        xmlText = TiXmlText( szBuf );
        xmlElmChildSub.InsertEndChild( xmlText );
        xmlElmChild.InsertEndChild( xmlElmChildSub );

        xmlElmChildSub    = TiXmlElement("GUID");
        xmlText = TiXmlText( pCheckResultGuid[iIndex].tCheckGuid.szGuid );
        xmlElmChildSub.InsertEndChild( xmlText );
        xmlElmChild.InsertEndChild( xmlElmChildSub );

        xmlElmChildSub    = TiXmlElement("Reference");
        xmlText = TiXmlText( pCheckResultGuid[iIndex].strComment );
        xmlElmChildSub.InsertEndChild( xmlText );
        xmlElmChild.InsertEndChild( xmlElmChildSub );

        pElmItems->InsertEndChild(xmlElmChild);
    }

    return TRUE;
}

void    InsertItemsContentNull(TiXmlElement* pElmParent)
{
    TiXmlElement xmlElmItems( "item" );

    TiXmlElement xmlElmChild( "policy" );
    TiXmlText xmlText( "" );
    xmlElmChild.InsertEndChild( xmlText );
    xmlElmItems.InsertEndChild(xmlElmChild);

    xmlElmChild = TiXmlElement( "option" );
    xmlText = TiXmlText( "" );
    xmlElmChild.InsertEndChild( xmlText );
    xmlElmItems.InsertEndChild(xmlElmChild);

    xmlElmChild = TiXmlElement( "policy_number" );
    xmlText = TiXmlText( "" );
    xmlElmChild.InsertEndChild( xmlText );
    xmlElmItems.InsertEndChild(xmlElmChild);

    xmlElmChild = TiXmlElement( "option_number" );
    xmlText = TiXmlText( "" );
    xmlElmChild.InsertEndChild(xmlText );
    xmlElmItems.InsertEndChild(xmlElmChild);

    xmlElmChild = TiXmlElement( "comment" );
    xmlText = TiXmlText( "" );
    xmlElmChild.InsertEndChild(xmlText );
    xmlElmItems.InsertEndChild(xmlElmChild);

    pElmParent->InsertEndChild(xmlElmItems);
}

void    InsertItemsContent(TiXmlElement* pElmParent, DtckResult &dtResult, char *contentStr)
{
    TiXmlElement xmlElmItems( "item" );

    TiXmlElement xmlElmChild( "policy" );
    TiXmlText xmlText( contentStr );
    xmlElmChild.InsertEndChild( xmlText );
    xmlElmItems.InsertEndChild(xmlElmChild);

    xmlElmChild = TiXmlElement( "option" );
    xmlText = TiXmlText( dtResult.option );
    xmlElmChild.InsertEndChild( xmlText );
    xmlElmItems.InsertEndChild(xmlElmChild);

    xmlElmChild = TiXmlElement( "result" );
    xmlText = TiXmlText( dtResult.strResult );
    xmlElmChild.InsertEndChild( xmlText );
    xmlElmItems.InsertEndChild(xmlElmChild);

    xmlElmChild = TiXmlElement( "policy_number" );
    xmlText = TiXmlText( dtResult.policy_number );
    xmlElmChild.InsertEndChild( xmlText );
    xmlElmItems.InsertEndChild(xmlElmChild);

    xmlElmChild = TiXmlElement( "option_number" );
    xmlText = TiXmlText( dtResult.option_number );
    xmlElmChild.InsertEndChild(xmlText );
    xmlElmItems.InsertEndChild(xmlElmChild);

    xmlElmChild = TiXmlElement( "comment" );
    xmlText = TiXmlText( dtResult.strComment );
    xmlElmChild.InsertEndChild(xmlText );
    xmlElmItems.InsertEndChild(xmlElmChild);

    pElmParent->InsertEndChild(xmlElmItems);

}


void InsertAntivirus(TiXmlElement* pElmParent)
{
    TiXmlElement xmlAntiList("anti_virus_install");

    TiXmlElement xmlAntiItem("item");
    TiXmlElement xmlAntiItemSub("policy");
    TiXmlText xmlText("anti_virus_install");
    xmlAntiItemSub.InsertEndChild(xmlText);
    xmlAntiItem.InsertEndChild(xmlAntiItemSub);

    xmlAntiItemSub = TiXmlElement("option");
    if (CheckResultResouce::antivirusSoftNum > 0)
    {
        xmlText =TiXmlText( "已安装" );

    }
    else
    {
        xmlText =TiXmlText( "未安装" );
    }
    xmlAntiItemSub.InsertEndChild(xmlText);
    xmlAntiItem.InsertEndChild(xmlAntiItemSub);

    xmlAntiItemSub = TiXmlElement("result");
    if (CheckResultResouce::antivirusSoftNum > 0)
    {
        xmlText =TiXmlText( "已安装" );

    }
    else
    {
        xmlText =TiXmlText( "未安装" );
    }
    xmlAntiItemSub.InsertEndChild(xmlText);
    xmlAntiItem.InsertEndChild(xmlAntiItemSub);

    xmlAntiItemSub = TiXmlElement("policy_number");
    xmlText =TiXmlText("无数据");
    xmlAntiItemSub.InsertEndChild(xmlText);
    xmlAntiItem.InsertEndChild(xmlAntiItemSub);

    xmlAntiItemSub = TiXmlElement("option_number");
    xmlText =TiXmlText("无数据");
    xmlAntiItemSub.InsertEndChild(xmlText);
    xmlAntiItem.InsertEndChild(xmlAntiItemSub);

    xmlAntiItemSub = TiXmlElement("comment");
    xmlText =TiXmlText("安装");
    xmlAntiItemSub.InsertEndChild(xmlText);
    xmlAntiItem.InsertEndChild(xmlAntiItemSub);

    xmlAntiList.InsertEndChild(xmlAntiItem);
    pElmParent->InsertEndChild(xmlAntiList);
}

void    InsertItemsContents(TiXmlElement& elmParent, DtckResults* pResult)
{
    if(ifPolicyXml)
    {
        while(pResult)
        {
            DtckResult &dtResult = pResult->result;
            pResult = pResult->pNext;
            InsertItemsContent(&elmParent, dtResult, dtResult.strCkPoint);
        }
    }
    else
    {
        InsertItemsContentNull(&elmParent);
    }
}

void    InsertServiceItemsContents(TiXmlElement& elmParent, DtckResults* pResult)
{
    char szBegin[]  = "是否禁用";
    char szEnd[]    = "服务";
    char *pszBegin;
    char *pszEnd;
    char szService[128];
    char szTmpService[128];
    char *pBlackSpace;

    while(pResult)
    {
        DtckResult &dtResult = pResult->result;
        pResult = pResult->pNext;

        // Remote Registry
        // Messenger
        // Clipbook
        // Alerter
        if ((pszBegin = strstr(dtResult.strCkPoint, szBegin))
            && (pszEnd = strstr(pszBegin, szEnd)))
        {
            pszBegin += strlen(szBegin);
            strncpy(szService, pszBegin, pszEnd-pszBegin);
            szService[pszEnd-pszBegin] = 0;
            do
            {
                pBlackSpace = strchr(szService, 0x20);
                if (pBlackSpace)
                {
                    int copyLen = pBlackSpace-szService;
                    strncpy(szTmpService, szService, copyLen);
                    strcpy(szTmpService+copyLen, szService+copyLen+1);
                }
                else
                    strcpy(szTmpService, szService);
            } while (pBlackSpace);

            TiXmlElement xmlElmSub( szTmpService );

            InsertItemsContent(&xmlElmSub, dtResult, szService);

            elmParent.InsertEndChild(xmlElmSub);
        }
    }
}

void    InsertItemsType(TiXmlElement* pElmParent, ECheckControlPoint eCheckPoint)
{
    TiXmlElement xmlElm("");

    switch(eCheckPoint)
    {
    case E_TP_WINDOWS_ACCOUNTPOLICY:     // 账户策略
        {
            //     <account_policy>
            //       <password_policy>
            //         <item>
            //         <policy>密码最短使用期限(天)</policy>
            //         <option>0</option>
            //         <policy_number>无数据</policy_number>
            //         <option_number>无数据</option_number>
            //         </item>
            //       </password_policy>
            //       <acc_lock_policy>
            //         <item>
            //         <policy>锁定阈值</policy>
            //         <option>0</option>
            //         <policy_number>001003002101102101</policy_number>
            //         <option_number>001003002101102101a000</option_number>
            //         </item>
            //     </acc_lock_policy>
            xmlElm = TiXmlElement( "account_policy" );
            TiXmlElement xmlElmSub( "password_policy" );
            TiXmlElement xmlElmSub2( "acc_lock_policy" );

            if(ifPolicyXml)
            {
                InsertItemsContents(xmlElmSub, CheckResultResouce::pDtPwdPolicy);
                InsertItemsContents(xmlElmSub2, CheckResultResouce::pDtAccLockPolicy);
                xmlElm.InsertEndChild( xmlElmSub );
                xmlElm.InsertEndChild( xmlElmSub2 );
            }


            break;
        }
    case E_TP_WINDOWS_LOCALPOLICY:       // 本地策略
        {
            //         <local_policy>
            //           </audit_policy>
            //           </user_right_assignment>
            //           </security_option>
            //         </local_policy>
            xmlElm = TiXmlElement( "local_policy" );
            TiXmlElement xmlElmSub( "audit_policy" );
            //TiXmlElement xmlElmSub2( "user_right_assignment" );
            //TiXmlElement xmlElmSub3( "security_option" );

            if(ifPolicyXml)
            {
                InsertItemsContents(xmlElmSub, CheckResultResouce::pDtAuditPolicy);
                //InsertItemsContents(xmlElmSub2, CheckResultResouce::pDtUserRightAssignment);
                //InsertItemsContents(xmlElmSub3, CheckResultResouce::pDtSecurityOption);

                xmlElm.InsertEndChild( xmlElmSub );
                //xmlElm.InsertEndChild( xmlElmSub2 );
                //xmlElm.InsertEndChild( xmlElmSub3 );
            }

            break;
        }
    case E_TP_WINDOWS_INFORMATIONPOLICY: // 信息策略
        {
            //         <operation_protect>
            //           </operation_protect_result>
            //         </operation_protect>
            xmlElm = TiXmlElement( "operation_protect" );
            TiXmlElement xmlElmSub( "close_sharedisk" );
            TiXmlElement xmlElmSub2( "auto_admin_logon" );
            TiXmlElement xmlElmSub3( "driver_auto_operation" );
            TiXmlElement xmlElmSub4( "make_dumpfile" );

            if(ifPolicyXml)
            {
                InsertAntivirus(&xmlElm);
                InsertItemsContents(xmlElmSub, CheckResultResouce::pDtCloseSharDisk);
                InsertItemsContents(xmlElmSub2, CheckResultResouce::pDtAutoAdminLogin);
                InsertItemsContents(xmlElmSub3, CheckResultResouce::pDtDriverAutoOperation);
                InsertItemsContents(xmlElmSub4, CheckResultResouce::pDtMakeDumpFile);

                xmlElm.InsertEndChild( xmlElmSub );
                xmlElm.InsertEndChild( xmlElmSub2 );
                xmlElm.InsertEndChild( xmlElmSub3 );
                xmlElm.InsertEndChild( xmlElmSub4 );
            }



            break;
        }
    case E_TP_WINDOWS_SERVICE:           // 服务策略
        {
            //         <service>
            //           </service_result>
            //         </service>
//            xmlElm = TiXmlElement( "service" );
//            InsertServiceItemsContents(xmlElm, CheckResultResouce::pDtService);

            break;
        }
    case E_TP_WINDOWS_GROUPPOLICY:       // 组策略
        {
            //             <group_policy>
            //                 </group_policy_result>
            //             </group_policy>
            xmlElm = TiXmlElement( "group_policy" );
            TiXmlElement xmlElmSub( "group_policy_result" );

            if(ifPolicyXml)
            {
                InsertItemsContents(xmlElmSub, CheckResultResouce::pDtNetConnect);
                InsertItemsContents(xmlElmSub, CheckResultResouce::pDtGroupPolicy);
                xmlElm.InsertEndChild(xmlElmSub);
            }

            break;
        }
    default:
        {
            break;
        }
    }

    // 把整个子节点插入到父节点中
    pElmParent->InsertEndChild( xmlElm );
}

void    InsertItems(TiXmlElement* pElmParent)
{
    InsertItemsType(pElmParent, E_TP_WINDOWS_ACCOUNTPOLICY);
    InsertItemsType(pElmParent, E_TP_WINDOWS_LOCALPOLICY);
    InsertItemsType(pElmParent, E_TP_WINDOWS_INFORMATIONPOLICY);
//    InsertItemsType(pElmParent, E_TP_WINDOWS_SERVICE);
    InsertItemsType(pElmParent, E_TP_WINDOWS_GROUPPOLICY);
}
