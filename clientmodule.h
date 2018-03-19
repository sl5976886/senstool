#ifndef CLIENT_MODULE_H__
#define CLIENT_MODULE_H__

#ifdef CROSSCLIENT_EXPORTS
#define GR_CROSSNET_API __declspec(dllexport)
#else
#define GR_CROSSNET_API __declspec(dllimport)
#endif

//#include "NetUtlity.h"

//为了避免过多包含，把相关定义从头文件中摘出
#define NET_MAX_USER_PID		32		//终端物理标识最大字符串长度
#define NET_MAX_USER_NAME		16		//user name最大字符串长度
#define		GR_AUTH_MAXIP_N	4		//登录认证的时候携带的最大IP地址数目
#define		GR_AUTH_FLAG_N	4		//GRXA

typedef struct NET_MSG_AUTH_T
{
//	BYTE	bPidLen;
//	BYTE	bNameLen;
//	BYTE	bPwdLen;
//	BYTE	bReserved;	// 4 bytes align boudary
    char	strPid[NET_MAX_USER_PID];
    char	strName[NET_MAX_USER_NAME];	//目前保存工号
    char	strPwd[NET_MAX_USER_NAME];
    WORD	wVersion;
    BYTE	bPidType;
}NetMsgAuth;
typedef struct NET_LOGIN_INFO
{
    NetMsgAuth	tAuth;				// 登录信息
    char		szServerIP[20];		// 服务器IP地址
    int			iPort;				// 服务器端口号
}NetLoginInfo, *PNETLOGININFO;
typedef struct NET_MSG_AUTH_EX_2_T
{
    char	strPid[NET_MAX_USER_PID];	//目前保存硬盘序列号或者GUID
    char	strName[NET_MAX_USER_NAME];	//目前保存工号
    char	strPwd[NET_MAX_USER_NAME];
    WORD	wVersion;
    BYTE	bPidType;
    BYTE	bExVer;							//后续子域的版本
    BYTE	baFlag[GR_AUTH_FLAG_N];		//消息包的标识,防止恶意攻击
    BYTE	baAddrType[GR_AUTH_MAXIP_N];	//IPV4 地址类型-
    DWORD32	dwIpAddr[GR_AUTH_MAXIP_N];		//最多携带4个IPV4的地址
    BYTE	baMacAddr[GR_AUTH_MAXIP_N*6];	//4*6=24 -> 4个IP地址对应的MAC地址
    char	strHost[256];					//主机名-gethostname
}NetMsgAuthEx2;

//为了避免防火墙和杀毒软件根据导出函数名告警,导出名非规则
//底层状态变化告知
// bRet - 0:连接成功 1:关闭套接字
// dwErr - 失败原因值
typedef void __stdcall NetClientChngCb(const int &bRet, const VOID *pApp, const int &dwErr);

//nMsgContent 仅包括消息长度和内容,不含消息类型长度
typedef int __stdcall NetClientMsgCb(const WORD &wMsg, const int &nMsgContent,void *content,void *reserved);
extern "C"
{
GR_CROSSNET_API int NtCrsInit(void * pAppData, NetClientChngCb *fn, NetClientMsgCb *f2);
GR_CROSSNET_API int NtCrsUninit();
GR_CROSSNET_API int NtCrsLgon(const BYTE &bType, NetLoginInfo &tNLI, NetMsgAuthEx2 &tAuthEx);
GR_CROSSNET_API DWORD NtCrsSndCmnd(const int &nMsgType, const int &nID,  const int &nSubID, const char *pPara);
//下面这个函数仅仅用于测试, nTid 是服务端命令相关的, 如果测试最好自增长
GR_CROSSNET_API DWORD NtCrsSntdFele(const char *strFile, const int &nTID);
}

#endif

