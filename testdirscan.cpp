#include "testdirscan.h"
#include "global.h"
#include "mainwindow.h"
#include "anaxmlfile.h"

TestDirScan::TestDirScan()
{
    m_hShareMem = NULL;
    m_pShareInfo = NULL;
    m_hMain = NULL;
}

TestDirScan::~TestDirScan()
{

}

int TestDirScan::CreateShareMemInfo(const HWND &h)
{
    // 存入本窗口句柄
    // 获得本程序的绝对路径
    int ret = -1;

    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    // 去掉可执行程序名本身
    // 去掉包含可执行程序的目录
    char *p = NULL;
    for (int i = 0; i < 2; i++)
    {
        p = strrchr(path, '\\');
        if (p != NULL)
        {
            *p = 0;
        }
    }

    m_hMain = h;

    // 创建共享内存，用于进程间通信
    // 主控为GreeClient，其他应用程序如果需要和GreeClient通信，需要向GreeClient注册
    DWORD dwLen;
    dwLen = sizeof(MainAppInfo);
    m_hShareMem = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, dwLen, "GreeGuardShareInfo");

    if (INVALID_HANDLE_VALUE != m_hShareMem)
    {
        m_pShareInfo  = (PMAINAPPINFO)MapViewOfFile(m_hShareMem, FILE_MAP_READ|FILE_MAP_WRITE, 0, 0, 0);
        if (NULL != m_pShareInfo)
        {
            m_pShareInfo->m_hWnd = m_hMain;//this->GetSafeHwnd();
            my_strcpy_s(m_pShareInfo->m_szInstallPath, MAX_PATH, path);
            ret = 0;
        }
    }

    return ret;
}

/*************************************************************************
函 数 名：DeleteShareMemInfo
功    能：删除共享内存空间
参    数：
返 回 值：
备    注：
更改描述：
*************************************************************************/
void TestDirScan::DeleteShareMemInfo()
{
    if(m_pShareInfo)
    {
        UnmapViewOfFile((LPCVOID)m_pShareInfo);
    }

    if(m_hShareMem)
    {
        CloseHandle(m_hShareMem);
    }
}

/*************************************************************************
函 数 名：DestroyMQ
功    能：删除内存中为各自进程开辟的消息存储空间
参    数：
返 回 值：
备    注：
更改描述：
*************************************************************************/
void TestDirScan::DestroyMQ()
{
    CMQ *pmq;
    MQMap_Iterator pMap;
    while (m_sndMap.size() > 0)
    {
        pMap = m_sndMap.begin();
        pmq = (*pMap).second;
        m_sndMap.erase(pMap);
        delete pmq;
    }

    while (m_rcvMap.size() > 0)
    {
        pMap = m_rcvMap.begin();
        pmq = (*pMap).second;
        m_rcvMap.erase(pMap);
        delete pmq;
    }
}

DWORD TestDirScan::GramDispatch(USHORT appID, DWORD len)
{
    // 由本地应用程序收到需要分发的报文
    char buffer[0xffff];
    USHORT rLen;
    DWORD dwret = 1;
    CMQ *psnd = NULL;

    // 是给其他应用程序的报文
    MQMap_Iterator pMap;
    pMap = m_sndMap.find(appID);
    if (pMap != m_sndMap.end())
    {
        psnd = (*pMap).second;
        if((psnd != NULL) && (psnd->MsgNum()))
        {
            // 读取报文
            psnd->Lock();
            psnd->Read((char *)&rLen, sizeof(rLen), 0);
            psnd->Read(buffer, rLen, 0);
            psnd->MsgNum()--;
            psnd->Unlock();

            TxHead txhead;
            memset(&txhead, 0 , sizeof(TxHead));
            my_memcpy_s(&txhead, sizeof(TxHead), buffer, sizeof(TxHead));

            if (APP_GREEGUARD == txhead.m_uDstApp)
            {
                switch(txhead.m_uMsgType)
                {
                case MS_APP_GREEGUARD_DISK_SCANED:
                    {
                        DbTaskScanDisk	dsd;
                        memset(&dsd, 0, sizeof(DbTaskScanDisk));
                        memcpy(&dsd, buffer + sizeof(TxHead), sizeof(DbTaskScanDisk));
                        if(ifFromServer)
                        {
                            ifSensFinish = true;
                        }
                        else
                        {
                            //解析文件
                            isChecked = 1;
                            QString localPath = qApp->applicationDirPath();
                            localPath += "\\sssens\\senscan.xml";
                            AnaXmlFile::anaXml(localPath);
                        }
                    }
                    break;
                case MS_APP_GREEGUARD_CLOSE://主程序退出消息
                    {
                        qApp->exit(0);
                    }
                    break;
                default:
                    break;
                }
            }
            else
            {
                // 发送报文
                dwret = PushDataToApp(txhead.m_uDstApp, buffer, rLen, false);
            }
        }
    }
    return dwret;
}

LRESULT TestDirScan::OnRecvFromTxLib(WPARAM wParam, LPARAM lParam)
{
    USHORT AppID = wParam;
    int len = lParam;
//    qDebug()<<"receive message";
    if(len < MSG_BASE)
    {// 传输报文,文件
        return GramDispatch((USHORT)AppID, len);
    }
    else
    {
        if(len == MSG_CREATEBUF)		// 应用软件启动
        {
            return CreateAppBuf((USHORT)AppID);
        }
        else
        {
            if(len == MSG_DELETEBUF)		// 应用程序退出
            {
                return DeleteAppBuf((USHORT)AppID);
            }
        }
    }

    return 0;
}

DWORD TestDirScan::CreateAppBuf(USHORT AppID)
{
    DWORD len = MAX_BUF;
    DWORD ret = 0;
    char temp[MAX_PATH];
    CMQ *pmq;

    MQMap_Iterator pMap;
    pMap = m_sndMap.find(AppID);
    if(pMap == m_sndMap.end())
    {
        sprintf(temp, "GreeGuard%dSND", AppID);
        pmq = new CMQ;
        if(pmq)
        {
            ret = pmq->Open(temp ,len);
            if((ret == 0) || (ret == ERROR_ALREADY_EXISTS))
            {
                pmq->SetPID(GetCurrentProcessId());
                pmq->SetWnd(m_hMain);//m_hWnd);

                m_sndMap.insert(std::pair<USHORT, CMQ*>(AppID, pmq));
            }
            else
            {
                pmq->Close();
                delete pmq;
            }
        }
        else
            ret = GetLastError();
    }

    pMap = m_rcvMap.find(AppID);
    if(ret == 0 && (pMap == m_rcvMap.end()))
    {
        sprintf(temp, "GreeGuard%dREV",AppID);
        pmq = new CMQ;
        if(pmq)
        {
            ret = pmq->Open(temp, len);
            if((ret==0) || (ret == ERROR_ALREADY_EXISTS))
            {
                m_rcvMap.insert(std::pair<USHORT, CMQ*>(AppID, pmq));
            }
            else
            {
                pmq->Close();
                delete pmq;
            }
        }
        else
            ret = GetLastError();
    }

    if (ret == ERROR_ALREADY_EXISTS)
    {
        ret = 0;
    }
    return ret;
}

DWORD TestDirScan::DeleteAppBuf(USHORT AppID)
{
    CMQ *pmq;
    string str;
    MQMap_Iterator pMap;
    pMap = m_sndMap.find(AppID);
    if (pMap != m_sndMap.end())
    {
        pmq = (*pMap).second;
        pmq->Close();
        delete pmq;
        m_sndMap.erase(AppID);
    }

    pMap = m_rcvMap.find(AppID);
    if(pMap != m_rcvMap.end())
    {
        pmq = (*pMap).second;
        pmq->Close();
        delete pmq;
        m_rcvMap.erase(AppID);
    }

    return 0;
}


DWORD TestDirScan::PushDataToApp(USHORT appID, char* pBuf, USHORT uLen, bool bFlag)
{

    DWORD dwRet = 1;
    MQMap_Iterator pMap;
    CMQ *prcv = NULL;

    pMap = m_rcvMap.find(APP_SEARCHDISK);
    if (pMap != m_rcvMap.end())
    {
        prcv = (*pMap).second;
        prcv->Lock();
        prcv->Write((char*)&uLen, sizeof(USHORT));
        prcv->Write(pBuf, uLen);
        prcv->MsgNum()++;
        prcv->Unlock();
        HWND hTmp = NULL;
        hTmp = prcv->GetWnd();
        if (hTmp != NULL)
        {
            ::PostMessage(prcv->GetWnd(), WM_RECEIVE, 0, 0);
        }
        dwRet = 0;
    }
    else
    {
        if (bFlag)
        {
            CreateAppBuf(appID);
            pMap = m_rcvMap.find(appID);
            if (pMap != m_rcvMap.end())
            {
                prcv = (*pMap).second;
                prcv->Lock();
                prcv->Write((char*)&uLen, sizeof(USHORT));
                prcv->Write(pBuf, uLen);
                prcv->MsgNum()++;
                prcv->Unlock();
                dwRet = 0;
            }
        }
    }

    return dwRet;
}
