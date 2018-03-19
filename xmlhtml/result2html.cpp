// HtmlLog.cpp : ���� DLL Ӧ�ó���ĵ���������
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
    //��ȡ�������м����
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
            //��������|ʱ��|URL|title
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
    //�����¼
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
    strcpy(htmlCol.column, "ϵͳ����");
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, pTmpOs->systemName);
    gs_tableRowInfo.push_back(htmlCol);

    htmlCol.colIndex = iColIndex++;
    sprintf(htmlCol.column, "%d", iColIndex);
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, "�汾��");
    gs_tableRowInfo.push_back(htmlCol);
    sprintf(htmlCol.column, "%s.%s.%s", pTmpOs->majorVersion, pTmpOs->MinorVersion, pTmpOs->buildNumber);
    gs_tableRowInfo.push_back(htmlCol);

    htmlCol.colIndex = iColIndex++;
    sprintf(htmlCol.column, "%d", iColIndex);
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, "ϵͳ��װʱ��");
    gs_tableRowInfo.push_back(htmlCol);
    tm *pt = localtime(&osInstallTime);
    if (pt)
    {
        //tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬�·�Ϊ0-11
        sprintf(htmlCol.column, "%d/%d/%d %d:%d:%d", pt->tm_year+1900, pt->tm_mon+1, pt->tm_mday, pt->tm_hour, pt->tm_min, pt->tm_sec);
    }
    else
        strcpy(htmlCol.column, "δ֪");
    gs_tableRowInfo.push_back(htmlCol);

    htmlCol.colIndex = iColIndex++;
    sprintf(htmlCol.column, "%d", iColIndex);
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, "ϵͳ·��");
    gs_tableRowInfo.push_back(htmlCol);
    char *pSystemRoot = getenv("systemroot");
    if (pSystemRoot)
        strcpy(htmlCol.column, pSystemRoot);
    else
        strcpy(htmlCol.column, "δ֪");
    gs_tableRowInfo.push_back(htmlCol);

    htmlCol.colIndex = iColIndex++;
    sprintf(htmlCol.column, "%d", iColIndex);
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, "���������");
    gs_tableRowInfo.push_back(htmlCol);
    if (hostName)
        strcpy(htmlCol.column, hostName);
    else
        strcpy(htmlCol.column, "δ֪");
    gs_tableRowInfo.push_back(htmlCol);

    htmlCol.colIndex = iColIndex++;
    sprintf(htmlCol.column, "%d", iColIndex);
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, "����ʱ��");
    gs_tableRowInfo.push_back(htmlCol);
    if(bootTime)
        strcpy(htmlCol.column, bootTime);
    else
        strcpy(htmlCol.column, "δ֪");
    gs_tableRowInfo.push_back(htmlCol);

    htmlCol.colIndex = iColIndex++;
    sprintf(htmlCol.column, "%d", iColIndex);
    gs_tableRowInfo.push_back(htmlCol);
    strcpy(htmlCol.column, "BIOS");
    gs_tableRowInfo.push_back(htmlCol);
    if(biosParameterValue)
        strcpy(htmlCol.column, biosParameterValue);
    else
        strcpy(htmlCol.column, "δ֪");
    gs_tableRowInfo.push_back(htmlCol);

    iNums = iColIndex;
    htmlCol.tableIndex++;
}

VOID HtmlSoftwares(HtmlColumnInfo &htmlCol, int &iNums, SoftwareInfo *pSoftware, int softNum)
{
    //���
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
        "δ֪",       //"UNKNOWN",
        "ֹͣ",       //"STOPPED", // 1
        "����",       //"START_PENDING", // 2
        "ֹͣ",       //"STOP_PENDING", // 3
        "����",      //"RUNNING", // 4
        "��ͣ",       //"CONTINUE_PENDING", // 5
        "��ͣ",       //"PAUSE_PENDING", // 6
        "��ͣ",       //"PAUSED" // 7
    };

    CHAR *szServiceStartType[] = {
        "�Զ�",   //"BOOT_START", // 0
        "�Զ�",   //"SYSTEM_START", // 1
        "�Զ�",   //"AUTO_START", // 2
        "�ֶ�",   //"DEMAND_START", // 3
        "����",   //"DISABLED", // 4
        "δ֪",   //"UNKNOWN",  // 5
    };

    struct ServiceRiskLevel
    {
        char szServiceName[64];
        char szRiskLevel[16];
    };
    ServiceRiskLevel    svRiskLevel[] =
    {
        { "Clipbook",           "�߷���" },
        { "talk",               "�߷���" },
        { "ntalk",              "�߷���" },
        { "pop-2",              "�߷���" },
        { "sendmail",           "�߷���" },
        { "TaskScheduler",      "�߷���" },
        { "PrintSpooler",       "�߷���" },
        { "TermService",        "�߷���" },
        { "RemoteRegistry",     "�߷���" },
        { "TlntSvr",            "�߷���" },
        { "EventSystem",        "�߷���" },
        { "WerSvc",             "�߷���" },
        { "ERSvc",              "�߷���" },
        { "ClipSrv",            "�߷���" },
        { "Alerter",            "�߷���" },
        { "Messenger",          "�߷���" },
        { "IISADMIN",           "���ڷ���" },
        { "W3SVC",              "���ڷ���" },
        { "Schedule",           "�ͷ���" },
        { "Spooler",            "���ڷ���" },
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
            strcpy(htmlCol.column, "һ�����");
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
    //����
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
    //����Ȩ��
    int  iColIndex = 0;
    char numStr[32] = "";
    int i;
    DrivesAccountRights* pDrivesRights = pRights;

    //����ACCESS_MASK�и���λ����ĺ�����ο�MSDN
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
        "�г��ļ���/��ȡ����", "�����ļ�/д������", "�����ļ���/��������", "��ȡ��չ����",

        "д����չ����", "�����ļ���/ִ���ļ�", "ɾ�����ļ��м��ļ�", "��ȡ����",

        "д������", " ", " ", " ",

        " ", " ", " ", " ",

        "ɾ�� ", "��ȡȨ��", "д����DACL", "д�������ߵ�Ȩ��",

        "ͬ������ ", " ", " "," ",

        "����ϵͳ��ȫ", "����������", " "," ",

        "��ȫ����", "ִ��", "д��","��ȡ"
    };

    string rights[] = {"����", "�ܾ�"};

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
    //Ӳ��
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
    //����
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
    //�ڴ���Ϣ
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
    //�ڴ���Ϣ
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
    // �Կ�
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
    //����
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
    //����
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
    //��ȫѡ��
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
    //ע�������
    HtmlSecurityOptions(htmlCol, iNums, pSecurityOpt, optNum);
}
VOID HtmlEventlogsOptions(HtmlColumnInfo &htmlCol, int &iNums, SecurityOptions *pSecurityOpt, int optNum)
{
    //eventlog
    HtmlSecurityOptions(htmlCol, iNums, pSecurityOpt, optNum);
}

VOID HtmlUsers(HtmlColumnInfo &htmlCol, int &iNums, USER_INFO_2 *pUserInfo, int userNum)
{
    //�˻���Ϣ
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
            strcpy(strDisabled, "�˻��ѽ���");
        }
        else
        {
            strcpy(strDisabled, "�˻�������");
        }

        if (userInfo.usri2_flags&UF_PASSWD_CANT_CHANGE)
            strcpy(PasswordChangeable, "�û����ܸ�������");
        else
            strcpy(PasswordChangeable, "�û��ܸ�������");

        if (userInfo.usri2_flags&UF_DONT_EXPIRE_PASSWD)
            strcpy(PasswordExpires, "������������");
        else
            strcpy(PasswordExpires, "���벻Ϊ��������");

        strcpy(PasswordRequired, "�û��´ε�¼ʱ�����������");

        if (userInfo.usri2_flags&UF_LOCKOUT)
            strcpy(Lockout, "�˻�������");
        else
            strcpy(Lockout, "�˻�δ����");

        //sprintf(htmlCol.column, "%s, %s, %s, %s��%s", strDisabled,PasswordChangeable, PasswordExpires,Lockout, PasswordRequired);
        userNameLen = strlen(strUserName);
        if ((userNameLen > 0) && (strUserName[userNameLen-1] == '$'))
        {
            //strcat(htmlCol.column, ", �����û�");
            strcpy(strHideUser, "�����û�");
        }
        else
        {
            //strcat(htmlCol.column, ", �������û�");
            strcpy(strHideUser, "�������û�");
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
    //����
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
        //sprintf_s(item.strResult, "�����ļ�����%s ·��:%s", strShareName, strPathName);

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
    //�˿�
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
    // ɱ�����
    int  iColIndex = 0;
    char numStr[32] = "";
    //int i;
    for (int i=0; i<antivirusNum; i++)
    {
        // ֻ��ʾ�Ѱ�װ��ɱ�����
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
    // ɱ�����2
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
    // ����������
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
    // �Ѱ�װ�Ĳ���
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

    //��ȡ�������м����

    HtmlStandardItems(htmlCol, iStandardItems, CheckResultResouce::pDtckResults);

    // USB

    HtmlUSBItems(htmlCol, iUsbItems, CheckResultResouce::pUsbHistory);
    //usb deep
    HtmlUsbDeep(htmlCol,usbDeepItems);

    // �����
    HtmlBrowserItems(htmlCol, iBrowserItems, CheckResultResouce::pIeHistory, CheckResultResouce::pFirefoxHistory, CheckResultResouce::pChromeHistory);

    //deep browser
    HtmlBrowserDeep(htmlCol,browserDeep);

    // ϵͳ��Ϣ

    BiosInfo* pBiosInfo = CheckResultResouce::pBiosInfo;
    char* pBiosParamValue = NULL;
    if (pBiosInfo)
        pBiosParamValue = pBiosInfo->parameterValue;
    HtmlSystemOs(htmlCol, iSystemOs, CheckResultResouce::pOsVersion, CheckResultResouce::osInstallTime,
                CheckResultResouce::computerName, CheckResultResouce::pBootTime, pBiosParamValue);

    // �����Ϣ

    HtmlSoftwares(htmlCol, iSoftwares, CheckResultResouce::pSoft, CheckResultResouce::softNum);

    // ������Ϣ

    HtmlProcess(htmlCol, iProcess, CheckResultResouce::pProcess, CheckResultResouce::processNum);

    // ������Ϣ

    HtmlServices(htmlCol, iServices, CheckResultResouce::pServiceStatus, CheckResultResouce::servicesNum);

    // snmp

    HtmlSnmp(htmlCol, iSnmps, CheckResultResouce::pSnmpService);

    // Ӳ����Ϣ
    // ����

    HtmlDiskPartitions(htmlCol, iDiskPartitions, CheckResultResouce::pLogicDrives, CheckResultResouce::logicDrivesNum);

    // ����Ȩ��

    HtmlDiskRights(htmlCol, iDiskRights, CheckResultResouce::pDrivesRights, CheckResultResouce::drivesRightsNum);

    // systemȨ��

    HtmlSystemRights(htmlCol, iSystemRights, CheckResultResouce::pSystemRights, CheckResultResouce::systemRightsNum);

    // CPU

    HtmlCPUs(htmlCol, iCpus, CheckResultResouce::pCpuInfo);

    // Ӳ��

    HtmlHardDisks(htmlCol, iHardDisks, CheckResultResouce::pHardDisk, CheckResultResouce::diskNum);

    // ����

    HtmlBoard(htmlCol, iBoard, CheckResultResouce::pBoardInfo);

    // �ڴ�

    HtmlMemorys(htmlCol, iMemorys, CheckResultResouce::pMemory);

    HtmlMemorys2(htmlCol, iMemorys2, CheckResultResouce::pMemory);

    // �Կ�

    HtmlDisplayCards(htmlCol, iDisplayCards, CheckResultResouce::pDisplayCard);

    // ����

    HtmlSoundCards(htmlCol, iSoundCards, CheckResultResouce::pAudio);

    // ������Ϣ

    HtmlEthernetAdapters(htmlCol, iEthernetAdapters, CheckResultResouce::pNetwork, CheckResultResouce::netcardNum);

    // ��ȫѡ��

    HtmlSecurityOptions(htmlCol, iSecurityOptions, CheckResultResouce::pSecurityOpt, CheckResultResouce::secOptionsNum);
    // ע�������

    HtmlRegistrySetsOptions(htmlCol, iRegistrySets, CheckResultResouce::pRegistrySets, CheckResultResouce::regOptionsNum);
    // windows��־

    HtmlEventlogsOptions(htmlCol, iEventlogs, CheckResultResouce::pEventlogs, CheckResultResouce::eventlogNum);

    // �˻���Ϣ

    HtmlUsers(htmlCol, iUsers, CheckResultResouce::pUserInfo, CheckResultResouce::usersNum);

    // ����Ŀ¼

    HtmlShares(htmlCol, iShares, CheckResultResouce::pShareInfo, CheckResultResouce::shareNum);

    // �˿���Ϣ

    HtmlActivePorts(htmlCol, iActivePorts, CheckResultResouce::pPortInfo);

    // ɱ��

    HtmlAntivirus(htmlCol, iAntivirus, CheckResultResouce::pAntivirusSoft, CheckResultResouce::antivirusSoftNum);

    // ɱ��2

    HtmlAntivirusPro(htmlCol, iAntivirusPro, CheckResultResouce::pAntivirusPro);

    // ������

    HtmlRuns(htmlCol, iRuns, CheckResultResouce::pRunItems);

    // �Ѱ�װ�Ĳ���

    HtmlPatchsInstalled(htmlCol, iPatchsInstalled, CheckResultResouce::pSystemDefectInfo);

    // �������

    HtmlPasswordPolicies(htmlCol, iPasswordPolicies, CheckResultResouce::pDtPwdPolicy);

    // ��˲���

    HtmlAuditPolicies(htmlCol, iAuditPolicies, CheckResultResouce::pDtAuditPolicy);

    // ���ʿ��Ʋ���

    HtmlAccLockPolicys(htmlCol, iAccLockPolicys, CheckResultResouce::pDtAccLockPolicy);

    // �û�Ȩ�޷���

    //HtmlUserRightAssignment(htmlCol, iUserRightAssignment, CheckResultResouce::pDtUserRightAssignment);
    HtmlUserRightAssignment(htmlCol, iUserRightAssignment, CheckResultResouce::pUserRightsAssignments, CheckResultResouce::userRightsNum);

    // �Զ���¼

    HtmlAutoAdminLogin(htmlCol, iAutoAdminLogin, CheckResultResouce::pDtAutoAdminLogin);

    // �������Զ�����

    HtmlDriverAutoOperation(htmlCol, iDriverAutoOperation, CheckResultResouce::pDtDriverAutoOperation);

    // dump�ļ�

    HtmlMakeDumpFile(htmlCol, iMakeDumpFile, CheckResultResouce::pDtMakeDumpFile);

    // ��������
    HtmlNetConnects(htmlCol, iNetConnects, CheckResultResouce::pDtNetConnect);

    // �����
    HtmlGroupPolicys(htmlCol, iGroupPolicys, CheckResultResouce::pDtGroupPolicy);

    //keyword
    int iKeyWord;
    HtmlKeyWord(htmlCol,iKeyWord);

    HtmlInfo html;
    //sec_strcpy(html.htmlFilePath, 1024, pszFileName);
    sec_strcpy(html.htmlTitle, 1024, "�ն˰�ȫ���");

    HtmlWriteInfo   htmlWrite[]   =
    {
        {"�����ն˰�ȫ���",   iStandardItems,      4,  {{10, "���"}, {30, "�����"}, {30, "���������"}, {30, "�ο���׼"}} },
        {"USBʹ�ü�¼",        iUsbItems,           5,  {{10, "���"}, {30, "����"}, {20, "�豸����"}, {20, "����ʱ��"}, {20, "�޸�ʱ��"}} },
        {"USBʹ�ü�¼��ȼ��", usbDeepItems,      5,    {{10,"���"},{30,"���ģʽ"},{20,"ʱ��"},{20,"ID"},{20,"��ע"}}   },
        {"�������ʷ��¼",     iBrowserItems,       5,  {{10, "���"}, {15, "���������"}, {30, "URL"}, {30, "����"}, {15, "����ʱ��"}} },
        {"�������¼��ȼ��",  browserDeep,         5,  {{10,"���"},{15,"���������"},{15,"ʱ��"},{30,"URL"},{30,"����"}}   },
        {"����ϵͳ",           iSystemOs,           3,  {{10, "���"}, {30, "����"}, {60, "����"}} },
        {"�Ѱ�װ����",         iSoftwares,          6,  {{10, "���"}, {20, "����"}, {10, "����"}, {10, "�汾"}, {20, "��װʱ��"}, {30, "��װĿ¼"}} },
        {"����",               iProcess,            4,  {{10, "���"}, {20, "����"}, {20, "PID"}, {50, "·��"}} },
        {"������Ϣ",           iServices,           7,  {{10, "���"}, {20, "����"}, {15, "������"}, {10, "״̬"}, {10, "��������"}, {10, "���յȼ�"}, {35, "·��"}} },
        {"SNMP",               iSnmps,              2,  {{10, "���"}, {90, "community"}} },
        {"���̷���",           iDiskPartitions,     2,  {{10, "���"}, {90, "�̷�"}} },
        {"���̷���Ȩ��",       iDiskRights,         3,  {{10, "���"}, {30,  "�̷�"}, {60, "Ȩ��"}} },
        {"ϵͳ����Ȩ��",       iSystemRights,       3,  {{10, "���"}, {30, "·��"}, {60, "Ȩ��"}} },
        {"CPU",                iCpus,               7,  {{10, "���"}, {15, "����"}, {15, "���к�"}, {20, "�ͺ�"}, {20, "��Ƶ"}, {10, "CPU��"}, {10, "����"}} },
        {"Ӳ��",               iHardDisks,          5,  {{10, "���"}, {20, "����"}, {20, "���к�"}, {20, "��С"}, {30, "�ͺ�"}} },
        {"����",               iBoard,              4,  {{10, "���"}, {30, "����"}, {20, "���к�"}, {40, "�ͺ�"}} }, 
        {"�ڴ�",               iMemorys,            6,  {{10, "���"}, {15, "�ڴ�ʹ����"}, {15, "�����ڴ�"}, {20, "���������ڴ�"}, {20, "�������ڴ�"}, {20, "���������ڴ�"}} },
        {"�ڴ�2",              iMemorys2,           5,  {{10, "���"}, {15, "����"}, {15, "������"}, {20, "Caption"}, {20, "DeviceLocator"}} },
        {"�Կ�",               iDisplayCards,       3,  {{10, "���"}, {30, "�����ṩ��"}, {60, "�Դ��С"}} },
        {"����",               iSoundCards,         2,  {{10, "���"}, {90, "�����ṩ��"}} },
        {"����",               iEthernetAdapters,   3,  {{10, "���"}, {30, "�����ṩ��"}, {60, "����"}} },
        {"��ȫѡ��",           iSecurityOptions,    3,  {{10, "���"}, {60, "����"}, {30, "��ȫ����"}} },
        {"ע�������",         iRegistrySets,       3,  {{10, "���"}, {60, "����"}, {30, "����"}} },
        {"windows��־",        iEventlogs,          3,  {{10, "���"}, {60, "����"}, {30, "��־��С(�ֽ���)"}} },
        {"�û�",               iUsers,              8,  {{10, "���"}, {15, "�û���"}, {15, "�˻��ѽ���"}, {15, "�û����ܸ�������"}, {15, "������������"}, {10, "�˻�������"}, {10, "�û��´ε�½ʱ���������"}, {10, "�˻�����"}} },
        {"����Ŀ¼",           iShares,             4,  {{10, "���"}, {20, "������"}, {30, "����·��"}, {40, "����"}} },
        {"��˿�",           iActivePorts,        9,  {{10, "���"}, {10, "����"}, {10, "����IP"}, {10, "���ض˿�"}, {10, "Զ��IP"}, {10, "Զ�̶˿�"}, {10, "״̬"}, {10, "PID"}, {20, "·��"}} },
        {"ɱ�����",           iAntivirus,          5,  {{10, "���"}, {30, "����"}, {20, "�汾"}, {20, "����״̬"}, {20, "������汾ʱ��"}} }, 
        {"ɱ�����2",          iAntivirusPro,       4,  {{10, "���"}, {30, "����"}, {30, "����״̬"}, {30, "�汾"}} }, 
        {"������",             iRuns,               4,  {{10, "���"}, {30, "����"}, {20, "������ʽ"}, {40, "������"}} },
        {"�Ѱ�װ�Ĳ���",       iPatchsInstalled,    6,  {{10, "���"}, {15, "������"}, {40, "��������"}, {15, "��װʱ��"}, {15, "����ʱ��"}, {15, "���صȼ�"}} },
        {"�������",           iPasswordPolicies,   3,  {{10, "���"}, {40, "����"}, {50, "��ȫ����"}} },
        {"��˲���",           iAuditPolicies,      3,  {{10, "���"}, {40, "����"}, {50, "��ȫ����"}} },
        {"���ʿ��Ʋ���",       iAccLockPolicys,     3,  {{10, "���"}, {40, "����"}, {50, "��ȫ����"}} },
        //{"�û�Ȩ�޷���",       iUserRightAssignment,3,  {{10, "���"}, {40, "����"}, {50, "��ȫ����"}} },
        {"�û�Ȩ�޷���",       iUserRightAssignment,7,  {{10, "���"}, {15, "����"}, {15, "Ӣ����"}, {20, "���"}, {20, "ת������"}, {10, "������"}, {10, "���Խ��"}} },
        //{"��ȫѡ��",           iSecurityOption,     3,  {{10, "���"}, {40, "����"}, {50, "��ȫ����"}} },
        {"�Զ���½",           iAutoAdminLogin,     3,  {{10, "���"}, {40, "����"}, {50, "�����"}} },
        {"�������Զ�����",     iDriverAutoOperation,3,  {{10, "���"}, {40, "����"}, {50, "״̬"}} },
        {"dump�ļ�",           iMakeDumpFile,       3,  {{10, "���"}, {40, "����"}, {50, "�����"}} },
        {"��������",           iNetConnects,        3,  {{10, "���"}, {40, "����"}, {50, "״̬"}} },
        {"�����",             iGroupPolicys,       3,  {{10, "���"}, {40, "����"}, {50, "״̬"}} },
        {"���д�",            iKeyWord,         3,   {{10,"���"}, {50,"·��"},{40,"�ؼ���"}} },
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
        sprintf(szMsg, "�����ļ�%sʧ�ܣ���ȷ��·���Ƿ���ȷ���Ŀ¼�д����ļ���Ȩ��", szHtmlFile);
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

    //TraceLevelLog(TRACE_LOG_LEVEL_INFO, "���������Ϊhtml��%s", szHtmlFile);
    return TRUE;
}
