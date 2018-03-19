#ifndef TESTDIRSCAN_H
#define TESTDIRSCAN_H

#include "TXConstant.h"
#include "TXlib.h"
#include "MQ.h"
#include <map>
#include <windows.h>
#include <tchar.h>
#include <QDebug>

using namespace std;

class TestDirScan
{
public:
    TestDirScan();
    ~TestDirScan();

    typedef map<USHORT, CMQ*> MQMap;
    typedef map<USHORT, CMQ*>::iterator MQMap_Iterator;
    // 共享内存句柄
    HANDLE				m_hShareMem;
    PMAINAPPINFO		m_pShareInfo;
    /*针对所有程序的收发共享缓存管理*/
    MQMap m_sndMap; 			// 所有应用的发送区
    MQMap m_rcvMap; 			// 所有应用的接收区

    HWND m_hMain;

/*************************************************************************
函 数 名：CreateShareMemInfo
功    能：创建共享内存空间
参    数：
返 回 值：
0成功
-1失败
备    注：

用于其他在GreeClient主程序注册的进程读取主程序（GreeClient）的窗口句柄和安装路径，
方便向其发送数据。

更改描述：
*************************************************************************/
    int CreateShareMemInfo(const HWND &h);


/*************************************************************************
函 数 名：DeleteShareMemInfo
功    能：删除共享内存空间
参    数：
返 回 值：
备    注：
更改描述：
*************************************************************************/
    void DeleteShareMemInfo();

/*************************************************************************
函 数 名：DestroyMQ
功    能：删除内存中为各自进程开辟的消息存储空间
参    数：
返 回 值：
备    注：
更改描述：
*************************************************************************/
    void DestroyMQ();

    DWORD GramDispatch(USHORT appID, DWORD len);

    LRESULT OnRecvFromTxLib(WPARAM wParam, LPARAM lParam);

    DWORD CreateAppBuf(USHORT AppID);

    DWORD DeleteAppBuf(USHORT AppID);

    DWORD PushDataToApp(USHORT appID, char* pBuf, USHORT uLen, bool bFlag);
};

#endif
