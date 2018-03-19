// HtmlLog.cpp : 定义 DLL 应用程序的导出函数。
//

//#include "../GrxaHostCheck/stdafx.h"
#include <time.h>
#include "result2html.h"
#include <vector>
#include "SecString.h"
#include "txt.h"
#include "global.h"
#include "WriteHtmlDll.h"
//#include "checkresultfromserver.h"
#include <stdio.h>
#include <string>
#include <QDebug>


using namespace std;

static vector<HtmlColumnInfo> gs_tableRowInfo;


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
        sprintf(szBuf, "%lluM", storageCapacity);
    }
}

VOID HtmlStandardItems(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults)
{
    //获取主机所有检查项
    int iColIndex = 0;
    //htmlCol.tableIndex = 0;
    char numStr[32] = "";

    while (NULL != pDtckResults)
    {
        DtckResult &result = pDtckResults->result;
        pDtckResults = pDtckResults->pNext;

        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, result.strCkPoint);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, result.strResult);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, result.strComment);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlUsbDeep(HtmlColumnInfo &htmlCol,int &iNums)
{
    int iColIndex = 0;
    QStringList mList;
    QString strModel,strTime,strId,strBz;
    QString mRes;

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
            htmlCol.colIndex = iColIndex++;

            sprintf(htmlCol.column, "%d", iColIndex);
            gs_tableRowInfo.push_back(htmlCol);

            strcpy(htmlCol.column,c_model);
            gs_tableRowInfo.push_back(htmlCol);

            strcpy(htmlCol.column,c_time);
            gs_tableRowInfo.push_back(htmlCol);

            strcpy(htmlCol.column,c_id);
            gs_tableRowInfo.push_back(htmlCol);

            strcpy(htmlCol.column,c_bz);
            gs_tableRowInfo.push_back(htmlCol);

            mList.clear();
        }
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlBrowserDeep(HtmlColumnInfo &htmlCol,int &iNums)
{
    int iColIndex = 0;
    QString mRes;
    QStringList mList;
    QString strModel,strTime,strId,strBz;
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

            htmlCol.colIndex = iColIndex++;

            sprintf(htmlCol.column, "%d", iColIndex);
            gs_tableRowInfo.push_back(htmlCol);

            strcpy(htmlCol.column,c_model);
            gs_tableRowInfo.push_back(htmlCol);

            strcpy(htmlCol.column,c_time);
            gs_tableRowInfo.push_back(htmlCol);

            strcpy(htmlCol.column,c_id);
            gs_tableRowInfo.push_back(htmlCol);

            strcpy(htmlCol.column,c_bz);
            gs_tableRowInfo.push_back(htmlCol);

            mList.clear();
        }
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlUSBItems(HtmlColumnInfo &htmlCol, int &iNums, USBHISTORY* pUsbHis)
{
    //USB
    int  iColIndex = 0;
    //htmlCol.tableIndex = 1;

    while (NULL != pUsbHis)
    {
        htmlCol.colIndex = iColIndex++;
        sprintf(htmlCol.column, "%d", iColIndex);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pUsbHis->caDeviceDesc);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pUsbHis->caService);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pUsbHis->caCreateTime);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pUsbHis->caUpdateTime);
        gs_tableRowInfo.push_back(htmlCol);

        pUsbHis = pUsbHis->pNext;
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlKeyWord(HtmlColumnInfo &htmlCol,int &iNums)
{
    SensRes mRes;
    QList<SensRes>::iterator it;
    int  iColIndex = 0;
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

        htmlCol.colIndex = iColIndex++;
        sprintf(htmlCol.column, "%d", iColIndex);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column,c_path);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column,c_key);
        gs_tableRowInfo.push_back(htmlCol);

        count++;
        if(count>=500)
        {
            break;
        }
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlBrowserItems(HtmlColumnInfo &htmlCol, int &iNums, IeVisitHistory *pHistoryIE, FireFoxHistory *pFirefoxHis, ChromeHistory *pChromeHis)
{
    //浏览记录
    //htmlCol.tableIndex = 2;
    int iColIndex = 0;
    char buffer[1024];
    int j ;
    int  iColumnLen = sizeof(htmlCol.column);
    HtmlColumnInfo BrowserName;
    BrowserName.tableIndex = htmlCol.tableIndex;
    strcpy(BrowserName.column, "Internet Explorer");

    while(NULL != pHistoryIE)
    {
        htmlCol.colIndex = iColIndex;
        sprintf(htmlCol.column, "%d", iColIndex+1);
        gs_tableRowInfo.push_back(htmlCol);

        BrowserName.colIndex = iColIndex;
        gs_tableRowInfo.push_back(BrowserName);

        //char *pErrUrl =  "javascript:void(function(){document.open();document.write(\"<!DOCTYPE html><html xmlns='http://www.w3.org/1999/xhtml' class='view' ><head><style type='text/css'>.view{padding:0;word-wrap:break-word;cursor:text;height:90%;}body{margin:8px;font-family:sans-serif;font-size:16px;}p{margin:5px 0;}</style><link rel='stylesheet' type='text/css' href='/wenda/js/ueditor/themes/iframe.css'/></head><body class='view' ></body><script type='text/javascript' defer='defer' id='_initialScript'>setTimeout(function(){editor =";
        char *pIeUrl = pHistoryIE->IeUrl;

        //memset(buffer,0, sizeof(buffer));
        if (!strncmp(pIeUrl, "javascript", 10))
        {
            j = 0;
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
        sec_strcpy(htmlCol.column, iColumnLen, pIeUrl);
        gs_tableRowInfo.push_back(htmlCol);

        sec_strcpy(htmlCol.column, iColumnLen, pHistoryIE->IeTitle);
        gs_tableRowInfo.push_back(htmlCol);

        sec_strcpy(htmlCol.column, iColumnLen, pHistoryIE->visitTime);
        gs_tableRowInfo.push_back(htmlCol);

        pHistoryIE = pHistoryIE->pNext;
        iColIndex++;
    }

    strcpy(BrowserName.column, "Mozilla Firefox");
    while (NULL != pFirefoxHis)
    {
        htmlCol.colIndex = iColIndex;
        sprintf(htmlCol.column, "%d", iColIndex+1);
        gs_tableRowInfo.push_back(htmlCol);

        BrowserName.colIndex = iColIndex;
        gs_tableRowInfo.push_back(BrowserName);

        sec_strcpy(htmlCol.column, iColumnLen, pFirefoxHis->fireFoxUrl);
        gs_tableRowInfo.push_back(htmlCol);

        sec_strcpy(htmlCol.column, iColumnLen, pFirefoxHis->fireFoxTitle);
        gs_tableRowInfo.push_back(htmlCol);

        sec_strcpy(htmlCol.column, iColumnLen, pFirefoxHis->fireFoxVisitTime);
        gs_tableRowInfo.push_back(htmlCol);

        pFirefoxHis = pFirefoxHis->pNext;
        iColIndex++;
    }

    strcpy(BrowserName.column, "Google Chrome");
    while (NULL != pChromeHis)
    {
        htmlCol.colIndex = iColIndex;
        sprintf(htmlCol.column, "%d", iColIndex+1);
        gs_tableRowInfo.push_back(htmlCol);

        BrowserName.colIndex = iColIndex;
        gs_tableRowInfo.push_back(BrowserName);

        sec_strcpy(htmlCol.column, iColumnLen, pChromeHis->chromeUrl);
        gs_tableRowInfo.push_back(htmlCol);

        sec_strcpy(htmlCol.column, iColumnLen, pChromeHis->chromeTitle);
        gs_tableRowInfo.push_back(htmlCol);

        sec_strcpy(htmlCol.column, iColumnLen, pChromeHis->chromeVisitTime);
        gs_tableRowInfo.push_back(htmlCol);

        pChromeHis = pChromeHis->pNext;
        iColIndex++;
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlSystemOs(HtmlColumnInfo &htmlCol, int &iNums, OsVersionInfo *pOsVersion, time_t osInstallTime, char *hostName, char *bootTime, char *biosParameterValue)
{
    int iColIndex = 0;
    int  iColumnLen = sizeof(htmlCol.column);
    //htmlCol.tableIndex = 3;

    OsVersionInfo os;
    if (NULL == pOsVersion)
    {
        ZeroMemory(&os, sizeof(os));
    }

    OsVersionInfo *pTmpOs = pOsVersion;
    if (NULL == pTmpOs)
        pTmpOs = &os;

    htmlCol.colIndex = iColIndex++;
    sprintf(htmlCol.column, "%d", iColIndex);
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, "系统名称");
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, pTmpOs->systemName);
    gs_tableRowInfo.push_back(htmlCol);

    htmlCol.colIndex = iColIndex++;
    sprintf(htmlCol.column, "%d", iColIndex);
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, "版本号");
    gs_tableRowInfo.push_back(htmlCol);
    sprintf(htmlCol.column, "%s.%s.%s", pTmpOs->majorVersion, pTmpOs->MinorVersion, pTmpOs->buildNumber);
    gs_tableRowInfo.push_back(htmlCol);

    htmlCol.colIndex = iColIndex++;
    sprintf(htmlCol.column, "%d", iColIndex);
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, "系统安装时间");
    gs_tableRowInfo.push_back(htmlCol);
    tm *pt = localtime(&osInstallTime);
    if (pt)
    {
        //tm结构体存储的是从1900年开始的时间，月份为0-11
        sprintf(htmlCol.column, "%d/%d/%d %d:%d:%d", pt->tm_year+1900, pt->tm_mon+1, pt->tm_mday, pt->tm_hour, pt->tm_min, pt->tm_sec);
    }
    else
        strcpy(htmlCol.column, "未知");
    gs_tableRowInfo.push_back(htmlCol);

    htmlCol.colIndex = iColIndex++;
    sprintf(htmlCol.column, "%d", iColIndex);
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, "系统路径");
    gs_tableRowInfo.push_back(htmlCol);
    char *pSystemRoot = getenv("systemroot");
    if (pSystemRoot)
        strcpy(htmlCol.column, pSystemRoot);
    else
        strcpy(htmlCol.column, "未知");
    gs_tableRowInfo.push_back(htmlCol);

    htmlCol.colIndex = iColIndex++;
    sprintf(htmlCol.column, "%d", iColIndex);
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, "计算机名称");
    gs_tableRowInfo.push_back(htmlCol);
    if (hostName)
        strcpy(htmlCol.column, hostName);
    else
        strcpy(htmlCol.column, "未知");
    gs_tableRowInfo.push_back(htmlCol);

    htmlCol.colIndex = iColIndex++;
    sprintf(htmlCol.column, "%d", iColIndex);
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, "开机时间");
    gs_tableRowInfo.push_back(htmlCol);
    if(bootTime)
        strcpy(htmlCol.column, bootTime);
    else
        strcpy(htmlCol.column, "未知");
    gs_tableRowInfo.push_back(htmlCol);

    htmlCol.colIndex = iColIndex++;
    sprintf(htmlCol.column, "%d", iColIndex);
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, "BIOS");
    gs_tableRowInfo.push_back(htmlCol);
    if(biosParameterValue)
        strcpy(htmlCol.column, biosParameterValue);
    else
        strcpy(htmlCol.column, "未知");
    gs_tableRowInfo.push_back(htmlCol);

    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlSoftwares(HtmlColumnInfo &htmlCol, int &iNums, SoftwareInfo *pSoftware, int softNum)
{
    //软件
    int  iColIndex = 0;
    char numStr[32] = "";
    int i;
    for (i = 0; i < softNum; i++)
    {
        if ( (0 == pSoftware[i].m_displayname[0])
            && (0 == pSoftware[i].m_displayversion[0]) )
            continue;

        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pSoftware[i].m_displayname);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pSoftware[i].szSoftType);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pSoftware[i].m_displayversion);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pSoftware[i].m_displaytime);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pSoftware[i].szInstallLocation);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlProcess(HtmlColumnInfo &htmlCol, int &iNums, ProcessInfo* pProcess, int processNum)
{
    int  iColIndex = 0;
    char numStr[32] = "";
    int i;
    for(i = 0; i < processNum; i++)
    {
        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pProcess[i].proName);
        gs_tableRowInfo.push_back(htmlCol);

        sprintf(htmlCol.column, "%lu", pProcess[i].processid);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pProcess[i].path);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlSnmp(HtmlColumnInfo &htmlCol, int &iNums, SNMPService *pSnmp)
{
    int  iColIndex = 0;
    char numStr[32] = "";

    if (pSnmp)
    {
        RegistryValueInfo *pRV = pSnmp->pRegistrValues;
        while (pRV)
        {
            htmlCol.colIndex = iColIndex++;
            numStr[0] = 0;
            itoa(iColIndex, numStr , 10);
            strcpy(htmlCol.column, numStr);
            gs_tableRowInfo.push_back(htmlCol);

            strcpy(htmlCol.column, pRV->communities);
            gs_tableRowInfo.push_back(htmlCol);

            pRV = pRV->pNext;
        }
    }

    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlServices(HtmlColumnInfo &htmlCol, int &iNums, SERVICE_STATUS_INFO1 *pServiceStatus, int serviceNum)
{
    int  iColIndex = 0;
    char numStr[32] = "";
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


    for (int i=0; i<serviceNum; i++)
    {
        ENUM_SERVICE_STATUS_PROCESSA& serviceStatusInfo  = pServiceStatus[i].serviceStatusInfo;

        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

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

        strcpy(htmlCol.column, serviceStatusInfo.lpDisplayName);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, serviceStatusInfo.lpServiceName);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, szServiceStatus[serviceStatusInfo.ServiceStatusProcess.dwCurrentState]);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, szServiceStartType[dwStartType]);
        gs_tableRowInfo.push_back(htmlCol);

        if (bFind)
        {
            strcpy(htmlCol.column, svRiskLevel[j].szRiskLevel);
            gs_tableRowInfo.push_back(htmlCol);
        }
        else
        {
            strcpy(htmlCol.column, "一般风险");
            gs_tableRowInfo.push_back(htmlCol);
        }

        strcpy(htmlCol.column, lpBinaryPathName);
        gs_tableRowInfo.push_back(htmlCol);
    }

    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlDiskPartitions(HtmlColumnInfo &htmlCol, int &iNums, LogicalDrivesInfo* pLogicDrives, int drivesNum)
{
    //分区
    int  iColIndex = 0;
    char numStr[32] = "";
    int i;
    for (i = 0; i < drivesNum; i++)
    {
        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pLogicDrives[i].name);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlRights(HtmlColumnInfo &htmlCol, int &iNums, DrivesAccountRights *pRights, int rightsNum)
{
    //磁盘权限
    int  iColIndex = 0;
    char numStr[32] = "";
    int i;
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

    for (i = 0; i < rightsNum; i++)
    {
        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pDrivesRights[i].strDriveName);
        gs_tableRowInfo.push_back(htmlCol);

        htmlCol.column[0] = 0;
        AccountRights *pAccountRt = pDrivesRights[i].pAccountRt;
        while(pAccountRt && (pAccountRt->valid))
        {
            sprintf(htmlCol.column+strlen(htmlCol.column), "account=%s:\n", pAccountRt->strAccount);
            for (int i = 0; i < 32; i++)
            {
                int nTmpRight = pAccountRt->arrRights[i];
                if (nTmpRight != 0)
                {
                    sprintf(htmlCol.column+strlen(htmlCol.column), "%s:%s;\n", filedesc[i].c_str(), rights[nTmpRight-1].c_str());
                }
            }
            sprintf(htmlCol.column+strlen(htmlCol.column), "|||\n");

            pAccountRt = pAccountRt->pNext;
        }

        strcpy(htmlCol.column, htmlCol.column);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlDiskRights(HtmlColumnInfo &htmlCol, int &iNums, DrivesAccountRights *pRights, int rightsNum)
{
    //iNums = CSysInfo::m_siDrivesRightNum;
    HtmlRights(htmlCol, iNums, pRights, rightsNum);
}

VOID HtmlSystemRights(HtmlColumnInfo &htmlCol, int &iNums, DrivesAccountRights *pRights, int rightsNum)
{
    //iNums = sizeof(CSysInfo::m_sSystemRights)/sizeof(CSysInfo::m_sSystemRights[0]);
    HtmlRights(htmlCol, iNums, pRights, rightsNum);
}

VOID HtmlCPUs(HtmlColumnInfo &htmlCol, int &iNums, CpuInfo *pCpuinfo)
{
    //cpu
    int  iColIndex = 0;
    char numStr[32] = "";
    //int i;

    if (pCpuinfo)
    {
        CpuInfo &cpuinfo = *pCpuinfo;

        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, cpuinfo.brand);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, cpuinfo.factoryNumber);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, cpuinfo.model);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, cpuinfo.parameterValue);
        gs_tableRowInfo.push_back(htmlCol);

        sprintf(htmlCol.column, "%lu", cpuinfo.dwNumberOfCpu);
        gs_tableRowInfo.push_back(htmlCol);

        sprintf(htmlCol.column, "%lu", cpuinfo.dwNumberOfProcessors);
        gs_tableRowInfo.push_back(htmlCol);

    }

    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlHardDisks(HtmlColumnInfo &htmlCol, int &iNums, HardDiskInfo* pHardDisk, int diskNum)
{
    //硬盘
    int  iColIndex = 0;
    char numStr[32] = "";
    int i;
    for (i = 0; i < diskNum; i++)
    {
        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pHardDisk[i].brand);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pHardDisk[i].factoryNumber);
        gs_tableRowInfo.push_back(htmlCol);

        char buf[64];
        StorageCapacity2Str(pHardDisk[i].captacity, buf);
        strcpy(htmlCol.column, buf);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pHardDisk[i].model);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlBoard(HtmlColumnInfo &htmlCol, int &iNums, MainBoardInfo *pBoardInfo)
{
    //主板
    int  iColIndex = 0;
    char numStr[32] = "";

    if (pBoardInfo)
    {
        MainBoardInfo &boardInfo = *pBoardInfo;

        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, boardInfo.brand);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, boardInfo.factoryNumber);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, boardInfo.model);
        gs_tableRowInfo.push_back(htmlCol);
    }

    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlMemorys(HtmlColumnInfo &htmlCol, int &iNums, MemoryInfo* pMemory)
{
    //内存信息
    int  iColIndex = 0;
    char numStr[32] = "";
    int i;

    if (pMemory)
    {
        MemoryInfo &memory = *pMemory;

        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        sprintf(htmlCol.column, "%u%%", memory.dwMemoryLoad);
        gs_tableRowInfo.push_back(htmlCol);

        char buf[64];
        StorageCapacity2Str(memory.ullTotalPhys, buf);
        strcpy(htmlCol.column, buf);
        gs_tableRowInfo.push_back(htmlCol);

        StorageCapacity2Str(memory.ullAvailPhys, buf);
        strcpy(htmlCol.column, buf);
        gs_tableRowInfo.push_back(htmlCol);

        StorageCapacity2Str(memory.ullTotalVirtual, buf);
        strcpy(htmlCol.column, buf);
        gs_tableRowInfo.push_back(htmlCol);

        StorageCapacity2Str(memory.ullAvailVirtual, buf);
        strcpy(htmlCol.column, buf);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlMemorys2(HtmlColumnInfo &htmlCol, int &iNums, MemoryInfo* pMemory)
{
    //内存信息
    int  iColIndex = 0;
    char numStr[32] = "";
    int i;

    if (pMemory)
    {
        MemoryInfo &memory = *pMemory;

        for (int i=0; i<memory.validMemoryNum; i++)
        {
            htmlCol.colIndex = iColIndex++;

            numStr[0] = 0;
            itoa(iColIndex, numStr , 10);
            strcpy(htmlCol.column, numStr);
            gs_tableRowInfo.push_back(htmlCol);

            Win32PhysicalMemory &phyMemory = memory.physicalMemory[i];

            strcpy(htmlCol.column, phyMemory.Capacity);
            gs_tableRowInfo.push_back(htmlCol);

            strcpy(htmlCol.column, phyMemory.Manufacturer);
            gs_tableRowInfo.push_back(htmlCol);

            strcpy(htmlCol.column, phyMemory.Caption);
            gs_tableRowInfo.push_back(htmlCol);

            strcpy(htmlCol.column, phyMemory.DeviceLocator);
            gs_tableRowInfo.push_back(htmlCol);
        }
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlDisplayCards(HtmlColumnInfo &htmlCol, int &iNums, DisplayInfo *pdi)
{
    // 显卡
    int  iColIndex = 0;
    char numStr[32] = "";

    if (pdi)
    {
        DisplayInfo &di = *pdi;
        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, di.brand);
        gs_tableRowInfo.push_back(htmlCol);

        char buf[64];
        StorageCapacity2Str(di.captacity, buf);
        strcpy(htmlCol.column, buf);
        gs_tableRowInfo.push_back(htmlCol);
    }

    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlSoundCards(HtmlColumnInfo &htmlCol, int &iNums, AudioInfo *pai)
{
    //声卡
    int  iColIndex = 0;
    char numStr[32] = "";

    if (pai)
    {
        AudioInfo &ai = *pai;
        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, ai.brand);
        gs_tableRowInfo.push_back(htmlCol);
    }

    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlEthernetAdapters(HtmlColumnInfo &htmlCol, int &iNums, NetworkCardInfo* pEthernetAdapter, int ethnetNum)
{
    //网卡
    int  iColIndex = 0;
    char numStr[32] = "";
    int i;
    for (i = 0; i < ethnetNum; i++)
    {
        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pEthernetAdapter[i].brand);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pEthernetAdapter[i].softSetting);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlSecurityOptions(HtmlColumnInfo &htmlCol, int &iNums, SecurityOptions *pSecurityOpt, int optNum)
{
    //安全选项
    int  iColIndex = 0;
    char numStr[32] = "";
    //int i;
    for (int i = 0; i < optNum; i++)
    {
        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pSecurityOpt[i].szName);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pSecurityOpt[i].szValue);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}
VOID HtmlRegistrySetsOptions(HtmlColumnInfo &htmlCol, int &iNums, SecurityOptions *pSecurityOpt, int optNum)
{
    //注册表设置
    HtmlSecurityOptions(htmlCol, iNums, pSecurityOpt, optNum);
}
VOID HtmlEventlogsOptions(HtmlColumnInfo &htmlCol, int &iNums, SecurityOptions *pSecurityOpt, int optNum)
{
    //eventlog
    HtmlSecurityOptions(htmlCol, iNums, pSecurityOpt, optNum);
}

VOID HtmlUsers(HtmlColumnInfo &htmlCol, int &iNums, USER_INFO_2 *pUserInfo, int userNum)
{
    //账户信息
    int  iColIndex = 0;
    char numStr[32] = "";
    //int i;
    //DWORD dwRet = 0;
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

        //sprintf(htmlCol.column, "%s, %s, %s, %s，%s", strDisabled,PasswordChangeable, PasswordExpires,Lockout, PasswordRequired);
        userNameLen = strlen(strUserName);
        if ((userNameLen > 0) && (strUserName[userNameLen-1] == '$'))
        {
            //strcat(htmlCol.column, ", 隐藏用户");
            strcpy(strHideUser, "隐藏用户");
        }
        else
        {
            //strcat(htmlCol.column, ", 非隐藏用户");
            strcpy(strHideUser, "非隐藏用户");
        }
        //gs_tableRowInfo.push_back(htmlCol);

        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, strUserName);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, strDisabled);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, PasswordChangeable);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, PasswordExpires);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, Lockout);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, PasswordRequired);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, strHideUser);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlShares(HtmlColumnInfo &htmlCol, int &iNums, SHARE_INFO_502 *pShareInfo, int shareNum)
{
    //共享
    int  iColIndex = 0;
    char numStr[32] = "";
    //int i;
    //SHARE_INFO_502 *pSharInfo;

    CHAR strPathName[MAX_PATH] = {0};
    CHAR strShareName[MAX_PATH] = {0};
    CHAR strShareType[MAX_PATH] = {0};
    //BOOL    bExistDefaultShare = FALSE;

    for (int i=0; i<shareNum; i++)
    {
        SHARE_INFO_502 &shareInfo = pShareInfo[i];

        memset(strShareName, 0, sizeof(strShareName));
        memset(strPathName, 0, sizeof(strPathName));
        memset(strShareType, 0, sizeof(strShareType));

        widechar_to_multibyte(shareInfo.shi502_netname, wcslen(shareInfo.shi502_netname), strShareName, sizeof(strShareName));
        widechar_to_multibyte(shareInfo.shi502_path, wcslen(shareInfo.shi502_path), strPathName, sizeof(strPathName));
        widechar_to_multibyte(shareInfo.shi502_remark, wcslen(shareInfo.shi502_remark), strShareType, sizeof(strShareType));
        //sprintf_s(item.strResult, "共享文件名：%s 路径:%s", strShareName, strPathName);

        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, strShareName);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, strPathName);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, strShareType);
        gs_tableRowInfo.push_back(htmlCol);
    }

    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlActivePorts(HtmlColumnInfo &htmlCol, int &iNums, PortInfo *pPortInfo)
{
    //端口
    int  iColIndex = 0;
    char numStr[32] = "";
    //int i;
    while (NULL != pPortInfo)
    {
        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pPortInfo->name);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pPortInfo->localAddr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pPortInfo->localPort);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pPortInfo->mstcAddr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pPortInfo->mstscPort);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pPortInfo->state);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pPortInfo->pId);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pPortInfo->path);
        gs_tableRowInfo.push_back(htmlCol);

        pPortInfo = pPortInfo->pNext;
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlAntivirus(HtmlColumnInfo &htmlCol, int &iNums, AntivirusSoft *pAntiVirusSoft, int antivirusNum)
{
    // 杀毒软件
    int  iColIndex = 0;
    char numStr[32] = "";
    //int i;
    for (int i=0; i<antivirusNum; i++)
    {
        // 只显示已安装的杀毒软件
        if (0 == pAntiVirusSoft[i].szVersion[0])
            continue;

        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pAntiVirusSoft[i].szDisplayName);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pAntiVirusSoft[i].szVersion);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pAntiVirusSoft[i].szRunStatus);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pAntiVirusSoft[i].szUpdateTime);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlAntivirusPro(HtmlColumnInfo &htmlCol, int &iNums, AntivirusProduct *pAntivirusPro)
{
    // 杀毒软件2
    int  iColIndex = 0;
    char numStr[32] = "";
    int i;
    AntivirusProduct *pTmpVirusPro;

    while (pAntivirusPro)
    {
        pTmpVirusPro = pAntivirusPro;
        pAntivirusPro = pAntivirusPro->pNext;

        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pTmpVirusPro->antivirusName);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pTmpVirusPro->antivirusState);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pTmpVirusPro->antivirusVersion);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlRuns(HtmlColumnInfo &htmlCol, int &iNums, RunItems *pRunItems)
{
    // 开机启动项
    int  iColIndex = 0;
    char numStr[32] = "";
    while(NULL != pRunItems)
    {
        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pRunItems->name);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pRunItems->szRunType);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pRunItems->path);
        gs_tableRowInfo.push_back(htmlCol);

        pRunItems = pRunItems->pNext;
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlPatchsInstalled(HtmlColumnInfo &htmlCol, int &iNums, SystemDefectInfo *pSystemDefInstall)
{
    // 已安装的补丁
    int  iColIndex = 0;
    char numStr[32] = "";
    while (NULL != pSystemDefInstall)
    {
        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pSystemDefInstall->defectNum);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pSystemDefInstall->defectName);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pSystemDefInstall->defectDate);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, pSystemDefInstall->strPubdate);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, GetPatchLevel(pSystemDefInstall->patchLevel));
        gs_tableRowInfo.push_back(htmlCol);

        pSystemDefInstall = pSystemDefInstall->pNext;
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlCheckResult(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults)
{
    int  iColIndex = 0;
    char numStr[32] = "";

    while(pDtckResults)
    {
        DtckResult &dtResult = pDtckResults->result;
        pDtckResults = pDtckResults->pNext;

        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, dtResult.strCkPoint);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, dtResult.strResult);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlPasswordPolicies(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults)
{
    HtmlCheckResult(htmlCol, iNums, pDtckResults);
}

VOID HtmlAuditPolicies(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults)
{
    HtmlCheckResult(htmlCol, iNums, pDtckResults);
}

VOID HtmlAccLockPolicys(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults)
{
    HtmlCheckResult(htmlCol, iNums, pDtckResults);
}

VOID HtmlUserRightAssignment(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults)
{
    HtmlCheckResult(htmlCol, iNums, pDtckResults);
}

VOID HtmlUserRightAssignment(HtmlColumnInfo &htmlCol, int &iNums, user_rights_assignment_t *pUserRightsAssignments, int userRightsNum)
{
    int  iColIndex = 0;
    char numStr[32] = "";

    for (int i=0; i<userRightsNum; i++)
    {
        user_rights_assignment_t &userRightsAssignments = pUserRightsAssignments[i];

        htmlCol.colIndex = iColIndex++;
        numStr[0] = 0;
        itoa(iColIndex, numStr , 10);
        strcpy(htmlCol.column, numStr);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, userRightsAssignments.policy);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, userRightsAssignments.userright);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, userRightsAssignments.option);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, userRightsAssignments.transResult);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, userRightsAssignments.policy_number);
        gs_tableRowInfo.push_back(htmlCol);

        strcpy(htmlCol.column, userRightsAssignments.option_number);
        gs_tableRowInfo.push_back(htmlCol);
    }
    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlSecurityOption(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults)
{
    HtmlCheckResult(htmlCol, iNums, pDtckResults);
}

VOID HtmlAutoAdminLogin(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults)
{
    HtmlCheckResult(htmlCol, iNums, pDtckResults);
}

VOID HtmlDriverAutoOperation(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults)
{
    HtmlCheckResult(htmlCol, iNums, pDtckResults);
}

VOID HtmlMakeDumpFile(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults)
{
    HtmlCheckResult(htmlCol, iNums, pDtckResults);
}

VOID HtmlNetConnects(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults)
{
    HtmlCheckResult(htmlCol, iNums, pDtckResults);
}
VOID HtmlGroupPolicys(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults)
{
    HtmlCheckResult(htmlCol, iNums, pDtckResults);
}

// VOID HtmlMixs(HtmlColumnInfo &htmlCol, int &iNums)
// {
//     int  iColIndex = 0;
//     char numStr[32] = "";
//
//     SystemInfoDec *pSysInfo = CSysInfo::m_spSystemInfo;
//     while (pSysInfo)
//     {
//         htmlCol.colIndex = iColIndex++;
//         numStr[0] = 0;
//         itoa(iColIndex, numStr , 10);
//         strcpy(htmlCol.column, numStr);
//         gs_tableRowInfo.push_back(htmlCol);
//
//         itoa(pSysInfo->infoTypeD, numStr, 10);
//         strcpy(htmlCol.column, numStr);
//         gs_tableRowInfo.push_back(htmlCol);
//
//         strcpy(htmlCol.column, pSysInfo->infoDes);
//         gs_tableRowInfo.push_back(htmlCol);
//
//         strcpy(htmlCol.column, pSysInfo->infoName);
//         gs_tableRowInfo.push_back(htmlCol);
//
//         strcpy(htmlCol.column, pSysInfo->infoPath);
//         gs_tableRowInfo.push_back(htmlCol);
//
//         strcpy(htmlCol.column, pSysInfo->infoType);
//         gs_tableRowInfo.push_back(htmlCol);
//
//         pSysInfo = pSysInfo->pNext;
//     }
//
//     SystemDefectInfo *pSystemDefInstall = CSysInfo::m_spSystemPatchInstall; //g_pSystemPatchInstall;//hostSec.GetHotfixesInfoWUA();
//     while (NULL != pSystemDefInstall)
//     {
//         htmlCol.colIndex = iColIndex++;
//         numStr[0] = 0;
//         itoa(iColIndex, numStr , 10);
//         strcpy(htmlCol.column, numStr);
//         gs_tableRowInfo.push_back(htmlCol);
//
//         strcpy(htmlCol.column, pSystemDefInstall->defectNum);
//         gs_tableRowInfo.push_back(htmlCol);
//
//         strcpy(htmlCol.column, pSystemDefInstall->defectName);
//         gs_tableRowInfo.push_back(htmlCol);
//
//         strcpy(htmlCol.column, pSystemDefInstall->defectDate);
//         gs_tableRowInfo.push_back(htmlCol);
//
//         strcpy(htmlCol.column, pSystemDefInstall->strPubdate);
//         gs_tableRowInfo.push_back(htmlCol);
//
//         strcpy(htmlCol.column, CSysInfo::GetPatchLevel(pSystemDefInstall->patchLevel));
//         gs_tableRowInfo.push_back(htmlCol);
//
//         pSystemDefInstall = pSystemDefInstall->pNext;
//     }
//     iNums = iColIndex;
//     htmlCol.tableIndex++;
// }
//static string styleStr = "";

BOOL WriteHtml(char szHtmlFile[512])
{
    qInstallMessageHandler(outputMessage);
    HtmlColumnInfo htmlCol;
    //ZeroMemory(&htmlCol, sizeof(HtmlColumnInfo));
    htmlCol.tableIndex = 0;
    int iStandardItems;
    int iUsbItems;
    int usbDeepItems;
    int iBrowserItems;
    int browserDeep;
    int iSystemOs;
    int iSoftwares;
    int iProcess;
    int iServices = 0;
    int iSnmps;
    int iDiskPartitions;
    int iDiskRights;
    int iSystemRights;
    int iCpus;
    int iHardDisks;
    int iBoard;
    int iMemorys;
    int iMemorys2;
    int iDisplayCards;
    int iSoundCards;
    int iEthernetAdapters;
    int iSecurityOptions;
    int iRegistrySets;
    int iEventlogs;
    int iUsers;
    int iShares;
    int iActivePorts;
    int iAntivirus;
    int iAntivirusPro;
    int iRuns;
    int iPatchsInstalled;
    int iPasswordPolicies;
    int iAuditPolicies;
    int iAccLockPolicys;
    int iUserRightAssignment;
    int iAutoAdminLogin;
    int iDriverAutoOperation;
    int iMakeDumpFile;
    int iNetConnects;
    int iGroupPolicys;

    //获取主机所有检查项

    HtmlStandardItems(htmlCol, iStandardItems, CheckResultResouce::pDtckResults);

    // USB

    HtmlUSBItems(htmlCol, iUsbItems, CheckResultResouce::pUsbHistory);
    //usb deep
    HtmlUsbDeep(htmlCol,usbDeepItems);

    // 浏览器
    HtmlBrowserItems(htmlCol, iBrowserItems, CheckResultResouce::pIeHistory, CheckResultResouce::pFirefoxHistory, CheckResultResouce::pChromeHistory);

    //deep browser
    HtmlBrowserDeep(htmlCol,browserDeep);

    // 系统信息

    BiosInfo* pBiosInfo = CheckResultResouce::pBiosInfo;
    char* pBiosParamValue = NULL;
    if (pBiosInfo)
        pBiosParamValue = pBiosInfo->parameterValue;
    HtmlSystemOs(htmlCol, iSystemOs, CheckResultResouce::pOsVersion, CheckResultResouce::osInstallTime,
                CheckResultResouce::computerName, CheckResultResouce::pBootTime, pBiosParamValue);

    // 软件信息

    HtmlSoftwares(htmlCol, iSoftwares, CheckResultResouce::pSoft, CheckResultResouce::softNum);

    // 进程信息

    HtmlProcess(htmlCol, iProcess, CheckResultResouce::pProcess, CheckResultResouce::processNum);

    // 服务信息

    HtmlServices(htmlCol, iServices, CheckResultResouce::pServiceStatus, CheckResultResouce::servicesNum);

    // snmp

    HtmlSnmp(htmlCol, iSnmps, CheckResultResouce::pSnmpService);

    // 硬件信息
    // 分区

    HtmlDiskPartitions(htmlCol, iDiskPartitions, CheckResultResouce::pLogicDrives, CheckResultResouce::logicDrivesNum);

    // 磁盘权限

    HtmlDiskRights(htmlCol, iDiskRights, CheckResultResouce::pDrivesRights, CheckResultResouce::drivesRightsNum);

    // system权限

    HtmlSystemRights(htmlCol, iSystemRights, CheckResultResouce::pSystemRights, CheckResultResouce::systemRightsNum);

    // CPU

    HtmlCPUs(htmlCol, iCpus, CheckResultResouce::pCpuInfo);

    // 硬盘

    HtmlHardDisks(htmlCol, iHardDisks, CheckResultResouce::pHardDisk, CheckResultResouce::diskNum);

    // 主板

    HtmlBoard(htmlCol, iBoard, CheckResultResouce::pBoardInfo);

    // 内存

    HtmlMemorys(htmlCol, iMemorys, CheckResultResouce::pMemory);

    HtmlMemorys2(htmlCol, iMemorys2, CheckResultResouce::pMemory);

    // 显卡

    HtmlDisplayCards(htmlCol, iDisplayCards, CheckResultResouce::pDisplayCard);

    // 声卡

    HtmlSoundCards(htmlCol, iSoundCards, CheckResultResouce::pAudio);

    // 网卡信息

    HtmlEthernetAdapters(htmlCol, iEthernetAdapters, CheckResultResouce::pNetwork, CheckResultResouce::netcardNum);

    // 安全选项

    HtmlSecurityOptions(htmlCol, iSecurityOptions, CheckResultResouce::pSecurityOpt, CheckResultResouce::secOptionsNum);
    // 注册表设置

    HtmlRegistrySetsOptions(htmlCol, iRegistrySets, CheckResultResouce::pRegistrySets, CheckResultResouce::regOptionsNum);
    // windows日志

    HtmlEventlogsOptions(htmlCol, iEventlogs, CheckResultResouce::pEventlogs, CheckResultResouce::eventlogNum);

    // 账户信息

    HtmlUsers(htmlCol, iUsers, CheckResultResouce::pUserInfo, CheckResultResouce::usersNum);

    // 共享目录

    HtmlShares(htmlCol, iShares, CheckResultResouce::pShareInfo, CheckResultResouce::shareNum);

    // 端口信息

    HtmlActivePorts(htmlCol, iActivePorts, CheckResultResouce::pPortInfo);

    // 杀毒

    HtmlAntivirus(htmlCol, iAntivirus, CheckResultResouce::pAntivirusSoft, CheckResultResouce::antivirusSoftNum);

    // 杀毒2

    HtmlAntivirusPro(htmlCol, iAntivirusPro, CheckResultResouce::pAntivirusPro);

    // 启动项

    HtmlRuns(htmlCol, iRuns, CheckResultResouce::pRunItems);

    // 已安装的补丁

    HtmlPatchsInstalled(htmlCol, iPatchsInstalled, CheckResultResouce::pSystemDefectInfo);

    // 密码策略

    HtmlPasswordPolicies(htmlCol, iPasswordPolicies, CheckResultResouce::pDtPwdPolicy);

    // 审核策略

    HtmlAuditPolicies(htmlCol, iAuditPolicies, CheckResultResouce::pDtAuditPolicy);

    // 访问控制策略

    HtmlAccLockPolicys(htmlCol, iAccLockPolicys, CheckResultResouce::pDtAccLockPolicy);

    // 用户权限分配

    //HtmlUserRightAssignment(htmlCol, iUserRightAssignment, CheckResultResouce::pDtUserRightAssignment);
    HtmlUserRightAssignment(htmlCol, iUserRightAssignment, CheckResultResouce::pUserRightsAssignments, CheckResultResouce::userRightsNum);

    // 自动登录

    HtmlAutoAdminLogin(htmlCol, iAutoAdminLogin, CheckResultResouce::pDtAutoAdminLogin);

    // 驱动器自动运行

    HtmlDriverAutoOperation(htmlCol, iDriverAutoOperation, CheckResultResouce::pDtDriverAutoOperation);

    // dump文件

    HtmlMakeDumpFile(htmlCol, iMakeDumpFile, CheckResultResouce::pDtMakeDumpFile);

    // 网络连接
    HtmlNetConnects(htmlCol, iNetConnects, CheckResultResouce::pDtNetConnect);

    // 组策略
    HtmlGroupPolicys(htmlCol, iGroupPolicys, CheckResultResouce::pDtGroupPolicy);

    //keyword
    int iKeyWord;
    HtmlKeyWord(htmlCol,iKeyWord);

    HtmlInfo html;
    //sec_strcpy(html.htmlFilePath, 1024, pszFileName);
    sec_strcpy(html.htmlTitle, 1024, "终端安全检查");

    HtmlWriteInfo   htmlWrite[]   =
    {
        {"主机终端安全检查",   iStandardItems,      4,  {{10, "序号"}, {30, "检查项"}, {30, "检查结果描述"}, {30, "参考标准"}} },
        {"USB使用记录",        iUsbItems,           5,  {{10, "序号"}, {30, "描述"}, {20, "设备类型"}, {20, "创建时间"}, {20, "修改时间"}} },
        {"USB使用记录深度检查", usbDeepItems,      5,    {{10,"序号"},{30,"检查模式"},{20,"时间"},{20,"ID"},{20,"备注"}}   },
        {"浏览器历史记录",     iBrowserItems,       5,  {{10, "序号"}, {15, "浏览器类型"}, {30, "URL"}, {30, "标题"}, {15, "访问时间"}} },
        {"浏览器记录深度检查",  browserDeep,         5,  {{10,"序号"},{15,"浏览器类型"},{15,"时间"},{30,"URL"},{30,"标题"}}   },
        {"操作系统",           iSystemOs,           3,  {{10, "序号"}, {30, "名称"}, {60, "描述"}} },
        {"已安装程序",         iSoftwares,          6,  {{10, "序号"}, {20, "名称"}, {10, "类型"}, {10, "版本"}, {20, "安装时间"}, {30, "安装目录"}} },
        {"进程",               iProcess,            4,  {{10, "序号"}, {20, "名称"}, {20, "PID"}, {50, "路径"}} },
        {"服务信息",           iServices,           7,  {{10, "序号"}, {20, "名称"}, {15, "服务名"}, {10, "状态"}, {10, "启动类型"}, {10, "风险等级"}, {35, "路径"}} },
        {"SNMP",               iSnmps,              2,  {{10, "序号"}, {90, "community"}} },
        {"磁盘分区",           iDiskPartitions,     2,  {{10, "序号"}, {90, "盘符"}} },
        {"磁盘访问权限",       iDiskRights,         3,  {{10, "序号"}, {30,  "盘符"}, {60, "权限"}} },
        {"系统访问权限",       iSystemRights,       3,  {{10, "序号"}, {30, "路径"}, {60, "权限"}} },
        {"CPU",                iCpus,               7,  {{10, "序号"}, {15, "描述"}, {15, "序列号"}, {20, "型号"}, {20, "主频"}, {10, "CPU数"}, {10, "核数"}} },
        {"硬盘",               iHardDisks,          5,  {{10, "序号"}, {20, "描述"}, {20, "序列号"}, {20, "大小"}, {30, "型号"}} },
        {"主板",               iBoard,              4,  {{10, "序号"}, {30, "描述"}, {20, "序列号"}, {40, "型号"}} }, 
        {"内存",               iMemorys,            6,  {{10, "序号"}, {15, "内存使用率"}, {15, "物理内存"}, {20, "可用物理内存"}, {20, "总虚拟内存"}, {20, "可用虚拟内存"}} },
        {"内存2",              iMemorys2,           5,  {{10, "序号"}, {15, "容量"}, {15, "制造商"}, {20, "Caption"}, {20, "DeviceLocator"}} },
        {"显卡",               iDisplayCards,       3,  {{10, "序号"}, {30, "驱动提供商"}, {60, "显存大小"}} },
        {"声卡",               iSoundCards,         2,  {{10, "序号"}, {90, "驱动提供商"}} },
        {"网卡",               iEthernetAdapters,   3,  {{10, "序号"}, {30, "驱动提供商"}, {60, "描述"}} },
        {"安全选项",           iSecurityOptions,    3,  {{10, "序号"}, {60, "名称"}, {30, "安全设置"}} },
        {"注册表设置",         iRegistrySets,       3,  {{10, "序号"}, {60, "名称"}, {30, "设置"}} },
        {"windows日志",        iEventlogs,          3,  {{10, "序号"}, {60, "名称"}, {30, "日志大小(字节数)"}} },
        {"用户",               iUsers,              8,  {{10, "序号"}, {15, "用户名"}, {15, "账户已禁用"}, {15, "用户不能更改密码"}, {15, "密码永不过期"}, {10, "账户已锁定"}, {10, "用户下次登陆时需更改密码"}, {10, "账户类型"}} },
        {"共享目录",           iShares,             4,  {{10, "序号"}, {20, "共享名"}, {30, "共享路径"}, {40, "描述"}} },
        {"活动端口",           iActivePorts,        9,  {{10, "序号"}, {10, "名称"}, {10, "本地IP"}, {10, "本地端口"}, {10, "远程IP"}, {10, "远程端口"}, {10, "状态"}, {10, "PID"}, {20, "路径"}} },
        {"杀毒软件",           iAntivirus,          5,  {{10, "序号"}, {30, "名称"}, {20, "版本"}, {20, "运行状态"}, {20, "病毒库版本时间"}} }, 
        {"杀毒软件2",          iAntivirusPro,       4,  {{10, "序号"}, {30, "名称"}, {30, "运行状态"}, {30, "版本"}} }, 
        {"启动项",             iRuns,               4,  {{10, "序号"}, {30, "名称"}, {20, "启动方式"}, {40, "命令行"}} },
        {"已安装的补丁",       iPatchsInstalled,    6,  {{10, "序号"}, {15, "补丁号"}, {40, "补丁描述"}, {15, "安装时间"}, {15, "发布时间"}, {15, "严重等级"}} },
        {"密码策略",           iPasswordPolicies,   3,  {{10, "序号"}, {40, "名称"}, {50, "安全设置"}} },
        {"审核策略",           iAuditPolicies,      3,  {{10, "序号"}, {40, "名称"}, {50, "安全设置"}} },
        {"访问控制策略",       iAccLockPolicys,     3,  {{10, "序号"}, {40, "名称"}, {50, "安全设置"}} },
        //{"用户权限分配",       iUserRightAssignment,3,  {{10, "序号"}, {40, "名称"}, {50, "安全设置"}} },
        {"用户权限分配",       iUserRightAssignment,7,  {{10, "序号"}, {15, "名称"}, {15, "英文名"}, {20, "结果"}, {20, "转换后结果"}, {10, "策略名"}, {10, "策略结果"}} },
        //{"安全选项",           iSecurityOption,     3,  {{10, "序号"}, {40, "名称"}, {50, "安全设置"}} },
        {"自动登陆",           iAutoAdminLogin,     3,  {{10, "序号"}, {40, "名称"}, {50, "检查结果"}} },
        {"驱动器自动运行",     iDriverAutoOperation,3,  {{10, "序号"}, {40, "名称"}, {50, "状态"}} },
        {"dump文件",           iMakeDumpFile,       3,  {{10, "序号"}, {40, "名称"}, {50, "检查结果"}} },
        {"网络连接",           iNetConnects,        3,  {{10, "序号"}, {40, "名称"}, {50, "状态"}} },
        {"组策略",             iGroupPolicys,       3,  {{10, "序号"}, {40, "名称"}, {50, "状态"}} },
        {"敏感词",            iKeyWord,         3,   {{10,"序号"}, {50,"路径"},{40,"关键词"}} },
        {NULL,                 0,                   0,  {{0, NULL}} },
    };

    int iRt;

    sec_strcpy(html.htmlFilePath, sizeof(html.htmlFilePath), szHtmlFile);

//    int index = 0;
//    string styleStr = "";
    int size = gs_tableRowInfo.size();
    HtmlColumnInfo *pColimnInfo = new HtmlColumnInfo[size];

    for (int i=0;i<size;i++)
    {
        memcpy(pColimnInfo+i,&gs_tableRowInfo[i],sizeof(HtmlColumnInfo));
    }

    iRt = WriteHtmlFile(html,htmlWrite,pColimnInfo,size);
//    iRt = WriteHtmlFileTest(html, htmlWrite, gs_tableRowInfo);
    if (iRt)
    {
        char szMsg[512];
        sprintf(szMsg, "保存文件%s失败，请确认路径是否正确或该目录有创建文件的权限", szHtmlFile);
        //TraceLevelLog(TRACE_LOG_LEVEL_WARN, szMsg);
        //MessageBox(NULL, szMsg, "", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    if(pColimnInfo)
    {
        delete []pColimnInfo;
        pColimnInfo = NULL;
    }

    if (!gs_tableRowInfo.empty())
    {
        std::vector<HtmlColumnInfo> tmp;
        gs_tableRowInfo.swap(tmp);
    }

    //TraceLevelLog(TRACE_LOG_LEVEL_INFO, "检查结果保存为html，%s", szHtmlFile);
    return TRUE;
}
