// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 TXLIB_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// TXLIB_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifndef TXLIB_H
#define TXLIB_H
#include <windows.h>

#ifdef GA_STATIC_RELEASE
#define TXLIB_API
#else
#ifdef TXLIB_EXPORTS
#define TXLIB_API __declspec(dllexport)
#else
#define TXLIB_API __declspec(dllimport)
#endif
#endif

#define WM_RECEIVE		WM_APP + 101		// 该消息通知应用软件有报文到达
#define WM_APPCLOSE		WM_APP + 102		// 主程序（GreeGuard）通知应用程序关闭消息

typedef struct _MainAppInfo
{
    HWND	m_hWnd;					// 信息传输的窗口句柄
    char	m_szInstallPath[MAX_PATH];// 指控软件系统安装路径
}MainAppInfo, *PMAINAPPINFO;

typedef struct _TxHead
{
    USHORT m_uDstApp;		//	报文的目的APP
    USHORT m_uMsgType;		//	报文的类型
    USHORT m_uMsgLen;		//	报文的长度
}TxHead, *PTXHEAD;
// 连接通信库
TXLIB_API DWORD TXlib_Init(USHORT uAppID, HWND hWnd);
// 通知通信库释放资源，应用程序也可以选择不释放，如果不释放那么共享内存中的数据将保留
TXLIB_API void TXlib_Uninit();
// 发送数据
TXLIB_API DWORD TXlib_SD(USHORT uDesAppID, USHORT uMsg, char* pMsg, USHORT uMsgLength);
// 接收数据
TXLIB_API DWORD	TXlib_RD(USHORT &uMsg, char *pMsg, USHORT uMsgBufLen, USHORT &uMsgRetLen);
// 运行应用程序
TXLIB_API DWORD TXlib_RunAPP(USHORT uAppID, LPCTSTR pParam);
// 获得错误代码
TXLIB_API LPCTSTR TXlib_GetErrorString(DWORD dwErr);
// 获得软件安装路径
TXLIB_API LPCTSTR	TXlib_GetInstallPath();


#endif
