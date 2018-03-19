#ifndef _NET_NET_UTLITY_H__
#define _NET_NET_UTLITY_H__

#ifdef GA_STATIC_RELEASE
#define GR_UTLITY_API
#else
#ifdef GR_UTILITY_EXPORTS
#define GR_UTLITY_API __declspec(dllexport)
#else
#define GR_UTLITY_API __declspec(dllimport)
#endif
#endif


//#include "NetDef.h"
#include <time.h>

#define NET_MSGTYPE_LEN		2
#define NET_CTNT_LEN		2
#define NET_TIME_LEN		4
#define GR_DB_WARN_LEVEL	3		//数据库设定的告警等级数目- 编解码相关不能随意改动

#ifdef CBUILDER_VER_6
#define __time32_t 	time_t
#define _time32  	time
/*
   time_t timer;
   struct tm *tblock;
   // gets time of day
   timer = time(NULL);
   // converts date/time to a structure
   tblock = localtime(&timer);
   printf("Local time is: %s", asctime(tblock));
*/

#endif

// USB控制状态
enum CLIENT_USB_STATUS
{
    CLIENT_USB_INVALID	= 0x0,	//USB 驱动无法打开(未安装)
    CLIENT_USB_ENABLE	= 0x1,	//USB使能状态
    CLIENT_USB_DISABLE	= 0x2,	//
    CLIENT_USB_READONLY = 0x4,
    CLIENT_USB_IOERR	= 0x8	//最近一次命令执行失败
};

// 网络控制状态
enum CLIENT_NET_STATUS
{
    CLIENT_NET_INVALID	= 0x0,	//NET 驱动无法打开(未安装)
    CLIENT_NET_ENABLE 	= 0x1,	//NET驱动未启用过滤但正常运行
    CLIENT_NET_DISABLE  = 0x2,	//禁止所有网络
    CLIENT_NET_SVRONLY  = 0x4,
    CLIENT_NET_IOERR	= 0x8	//最近一次命令执行失败
};

// 锁屏状态
enum CLIENT_BLOCK_STATUS
{
    CLIENT_BLOCK_NOCMD	= 0x0,
    CLIENT_UNBLOCK_ALL	= 0x1,
    CLIENT_BLOCK_ALL	= 0x2,
    CLIENT_BLOCK_ERR	= 0x8	//最近一次命令执行失败
};

// 文件传输状态只列一个状态，其他状态直接引用NET_MSG_TYPE_E
enum CLIENT_TRANS_STATUS
{
    CLIENT_TRANS_NONE = 0x00
};

enum NET_MSG_TYPE_E
{
    NET_MSG_UNKNOWN = 0,
    NET_MSG_AUTH_REQ	 ,		//1客户端认证请求
    NET_MSG_AUTH_RSP	 ,		//2认证响应
    NET_MSG_TRANS_FILE	 ,		//3传输文件
//	NET_MSG_KEY_POLICY	 ,		//4关键词策略表
    NET_MSG_WARN_LEVEL 	 ,		//4告警等级策略表
    NET_MSG_KEY3_POLICY	 ,		//5关键词策略表
    NET_MSG_EXT_POLICY	 ,		//6后缀名搜索策略表
    //系统控制命令
    NET_MSG_USB_INSERT	 ,		//07USB插入记录
    NET_MSG_USB_REMOVE	 ,		//08USB拔出记录
    NET_MSG_USB_ENABLE	 ,		//09允许USB
    NET_MSG_USB_DISABLE	 ,		//10禁止USB
    NET_MSG_USB_READONLY ,		//11只读USB
    NET_MSG_NET_ENABLE	 ,		//12允许网络访问
    NET_MSG_NET_SVRONLY	 ,		//13只允许网络连接服务器
    NET_MSG_NET_DISABLE	 ,		//14禁止网络
    NET_MSG_BLOCK_ALL	 ,		//15禁止终端的所有操作(键盘和鼠标)
    NET_MSG_UNBLOCK_ALL	 ,		//16恢复终端的所有操作(键盘和鼠标)
    NET_MSG_SNAP_SCRN	 ,		//17上传截屏

    NET_MSG_HEART_REQ	 ,		//18心跳请求
    NET_MSG_HEART_RSP	 ,		//19心跳响应
    NET_MSG_NTP_REQ	 	 ,		//20网络时间请求
    NET_MSG_NTP_RSP	 	 ,		//21网络时间响应
    NET_MSG_CTRLSTATE_REQ,		//22获取终端控制状态请求
    NET_MSG_CTRLSTATE_RSP,		//23获取终端控制状态响应
    NET_MSG_SOFT_CLIVER	 ,		//24客户端软件版本
    NET_MSG_SRCH_EXTSET	 ,		//25设置搜索后缀名
    NET_MSG_SRCH_EXTGET	 ,		//26请求获取搜索后缀名
    NET_MSG_SRCH_EXTRPT	 ,		//27报告当前搜索后缀名
    NET_MSG_UP_LOGCUR	 ,		//28上传当前日志
    NET_MSG_UP_LOGDAY	 ,		//29上传指定天的日志
    NET_MSG_UP_LOGALL	 ,		//30上传所有日志
    NET_MSG_UP_LOG_EXT	 ,		//31上传指定要求的日志
    NET_MSG_UP_PROCESS	 ,		//32上传进程列表
    NET_MSG_UP_SERVICES	 ,		//33上传服务列表
    NET_MSG_UP_SOFTWARE	 ,		//34上传本地安装软件列表
    NET_MSG_UP_URLHIS	 ,		//35上传网页访问历史
    NET_MSG_UP_SCRNCUR	 ,		//36上传当前截屏
    NET_MSG_UP_SCRNMEM	 ,		//37上传内存最近的截屏
    NET_MSG_UP_DIR		 ,		//38上传指定文件夹
    NET_MSG_UP_FILE		 ,		//39上传指定文件
    NET_MSG_TFILE_CHUNK	 ,		//40指定文件的一部分
    NET_MSG_TFILE_EOF	 ,		//41指定文件的一部分
    NET_MSG_ALARM_EVENT	 ,		//42上报告警事件
    NET_MSG_ALARM_LIST	 ,		//43上报告警事件
    NET_MSG_TFILE_CMD	 ,		//44文件传输相关的控制命令
    NET_MSG_TFILE_CK_END ,		//45文件传输的最后一个数据块
    NET_MSG_TFILE_ACK	 ,		//46文件传输命令的确认,会携带原因值
    NET_MSG_ALARM_NET	 ,		//47上报网络告警事件
    NET_MSG_ALARM_REG	 ,		//48上报注册表修改告警事件
    NET_MSG_ALARM_FILECHG,		//49上报文件修改告警事件
    NET_MSG_DISK_CHECK	 ,		//50专项检查
    NET_MSG_REG_MON_PLY	 ,		//51下发注册表监控键值列表
    NET_MSG_FILE_MON_PLY ,		//52下发文件监测列表 --- 由于文件监测列表会很长,故以END表示结束
    NET_MSG_FILE_MON_END ,		//53
    NET_MSG_USR_SET_PWD  ,		//54用户发起设置密码请求
    NET_MSG_USR_GET_SYSINFO,	//55获得所有终端信息
    NET_MSG_DISK_DIR_SCAN,		//56用户终端磁盘/目录关键词扫描
    NET_MSG_LOGINOUT     ,		//57用户终端登陆退出,用于上层记录
    NET_MSG_CTRL_STAS_REQ,		//58下发终端控制状态请求
    NET_MSG_CTRL_STAS_RSP,		//59终端控制状态响应
    NET_MSG_TFILE_CHKEOF ,		//60指定文件最后一部分
    NET_MSG_VERSION_FILES,		//61版本号和文件数目
    NET_MSG_SEND_FILE	 ,		//62发送文件
    NET_MSG_TASK_OVER	 ,		//63所有通信完成,断开连接
    NET_MSG_ERR_NTFY	 ,		//64对端发送的错误通知
    NET_MSG_SGL_NOTICE	 ,		//65单点的消息通知
    NET_MSG_BROADCAST	 ,		//66广播消息
    NET_MSG_FORCEUPDATE  ,		//67强制客户端升级
    NET_MSG_CUST_CMD     ,		//68发送自定义命令
    NET_MSG_SVR_IP_PORT  ,		//69服务器变更IP地址和端口号- 控制服务器和自动更新服务器
    NET_MSG_CFG_POLICY = 91,	//91 全局策略配置(keyword filetypes usb net ctrl flag)

    NET_MSG_CUST_CMDREQ = 98 ,	//98终端自定义命令请求
    NET_MSG_CUST_CMDRSP = 99  ,	//99自定义命令响应
    NET_MSG_ACK = 100	 ,		//100上报告警事件
    NET_MSG_TYPE_ERR
};

// 命令操作状态，其他命令执行在秒级，不记入状态
enum CLIENT_OPT_STATUS
{
    CLIENT_OPT_NONE = 0x00,
    CLIENT_OPT_DISK_CHECK = NET_MSG_DISK_CHECK, // 专项检查
    CLIENT_OPT_GET_SYSINFO = NET_MSG_USR_GET_SYSINFO, // 获得系统信息
    CLIENT_OPT_DISK_DIR_SCAN = NET_MSG_DISK_DIR_SCAN // 用户终端磁盘/目录关键词扫描
};

enum DRIVER_STATUS
{
    DRIVER_NOT_EXITED = 0, DRIVER_INITIALIZED, DRIVER_STARTED, DRIVER_LOADED, DRIVER_REMOVED
};
typedef struct NET_MSG_DECODE_T
{
    WORD	wMsgType;
    int		(*decode)(char *pData, int &nLen, void *pPara);
}NetMsgDecode;
//NetMsgHandler
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
#define		GR_AUTH_MAXIP_N	4		//登录认证的时候携带的最大IP地址数目
#define		GR_AUTH_FLAG_N	4		//GRXA
typedef struct NET_MSG_AUTH_EX_T
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
}NetMsgAuthEx;
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
typedef struct NET_MSG_USR_SET_PWD_T
{
    INT32	nSeq;							//终端发送的消息序号,用于确认定位
    char	strOldPwd[NET_MAX_USER_NAME];	//携带的老密码
    char	strNewPwd[NET_MAX_USER_NAME];	//携带的需要修改的密码
}NetMsgSetPwd;

typedef struct NET_MSG_USB_ACT_T
{
    time_t tmEvent;					//信息获取时间
    char szFSName[64];				//文件系统名称
    char szVolume[64];				//卷标
    char szFriendName[MAX_PATH];	//设备友好名
    char cDrive;					//==0表示不存在 >0表示存在 'A'
    BYTE nType;						//磁盘类型，0-硬盘/1-U盘
    BYTE nActInsert;				//0 拔出 1插入
}MsgUsbAct;

#define NET_IP_LEN				20
typedef struct NET_LOGIN_INFO
{
    NetMsgAuth	tAuth;				// 登录信息
    char		szServerIP[20];		// 服务器IP地址
    int			iPort;				// 服务器端口号
}NetLoginInfo, *PNETLOGININFO;

typedef struct NET_SVRADDR_INFO_T
{
    DWORD32		dwSvrIp;			//控制服务器地址- 目前只支持IPV4
    DWORD32		dwUpdtIp;			//自动更新服务器地址
    WORD		wSvrPort;
    WORD		wUpdtPort;
}NetSvrAddrInfo;

#define WARN_KEY_LEVEL_1		1	//红色告警
#define WARN_KEY_LEVEL_2		1	//黄色告警
#define WARN_KEY_LEVEL_3		1	//橙色告警

//关键词告警策略
//typedef struct _MSG_KEYWORD_POLICY_T
//{
//	int		nID;				//数据库标识
//	int		nLevel;				//告警等级
//	int		nVer;				//版本
//	int		nType;				//告警模板类型
//	char	strKeys[128];		//关键词列表 ; 区分
//}MsgKeyPolicy;
//后缀名策略
//typedef struct _MSG_EXTNAME_POLICY_T
//{
//	int		nID;				//数据库标识
//	int		nVer;				//版本
//	int		nType;				//告警模板类型
//	char	strName[128];		//extension names列表 ; 区分
//}MsgExtPolicy;

//File Transfer
typedef struct _MSG_SEND_FILE_INFO_T
{
    INT32	nID;				//本端的序号
    INT32	nPeerTid;			//对端的传输文件序号-如果有的话
    DWORD32	dwFileSize;
    char	strUpFile[256]; 	//指定的发送的文件名(绝对或者相对路径)
}MsgSendFile;
typedef struct _MSG_TRANS_FILE_INFO_T
{
    INT32		nID;
    INT32		nSubID;
    DWORD32		dwFileSize;
    char	strUpFile[256]; 	//指定的需要上传的文件名(absolute path)
}MsgTransFile;
typedef struct _MSG_TRANS_COMMAND_T
{
    int		nID;
    int		nSubID;
    WORD	wType;	//file transferring control command
}MsgTransCmd;
typedef struct _MSG_TRANS_FILE_CHUNK_T
{
    INT32		nID;
    INT32		nSubID;
    DWORD32		nSeq;
    DWORD32		nFilePos;
    DWORD32		nFileLen;
    char	strContent[NET_MAX_PERDATA_N];
}MsgFileChunk;
typedef struct _MSG_SET_USR_PWD_T
{
    char	strOldPwd[NET_MAX_USER_NAME];
    char	strNewPwd[NET_MAX_USER_NAME];
}MsgSetUsrPwd;
typedef enum _ERR_IND_E
{
    ErrIndNetSend = 1,
    ErrIndNetRecv	,
    ErrDiskCheck	,
}MsgErrIndE;
typedef struct _MSG_NET_ERR_NTFY_T
{
    INT32	nID;				//消息序号
    DWORD32 dwTid;				//文件传输过程中的对应ID
//	WORD	wOprType;			//错误类别
//	WORD	wLastErr;			//GetLastError() etc
    DWORD32 dwErr;				//error code - 高16位为错误类型,低16位错误码GetLastError()得到
    char	strMsg[250];		//error messge
}MsgErrNtfy;
typedef struct _MSG_ACK_T
{
    INT32		nPeerID;			//数据库中的指令ID
    INT32		nSubID;
    INT32		nMsgSeq;
    INT32		nStatus;			//执行的结果
    WORD		wMsgType;			//对应的发送的命令、控制消息
}MsgAck;

//==================================================
// DB 相关的数据结构
//==================================================

//终端控制状态
typedef struct _DB_CTRL_STATUS_T
{
    INT32		nID;
    INT32		nSubID;
    WORD		wRegDrvVer;		//驱动保护程序版本
    WORD		wUsbDrvVer;		//USB控制驱动版本
    WORD		wNetDrvVer;		//网络驱动版本
    WORD		wOtherVer;		//保留驱动版本-字节对齐
    DWORD32		dwNetIpAddr;	//网络驱动服务端地址

    BYTE		bRcntUsbCmd;	//最近下发的USB控制命令
    BYTE		bUsbState;		//USB驱动运行状态
    BYTE		bRcntNetCmd;	//最近下发的NET控制命令
    BYTE		bNetState;		//网络驱动运行状态
    BYTE		bRcntBlckCmd;	//最近下发的BLOCK控制命令
    BYTE		bBlockState;	//终端锁屏状态
    BYTE		bTranSend;		//终端文件传输send状态
    BYTE		bTranRecv;		//终端文件传输recv状态

    BYTE		bCkState;		//磁盘检查任务,终端信息检查任务运行状态
    BYTE		bReserved[3];	//保留字段 - 4bytes align
}DbCtrlStatus;

// 一个通用的与告警等级相关的字符串结构
// DB -> T_RegistrySettings
typedef struct _DB_WARN_LEVEL_STR_T
{
//	WORD			wOffset1;		//告警级别1偏移量固定为0, 无须变量标识
//	WORD			wOffset2;		//告警级别2 在strMonitor 中的偏移
//	WORD			wOffset3;		//告警级别3 在strMonitor 中的偏移
    WORD			wMsg;
    WORD			wMsgLen;		//为了节约重新编码申请内存,与Encode 对应-整个结构体实际占用的内存
    WORD			waOffset[GR_DB_WARN_LEVEL-1];	//0->level2 | 1->level3
    WORD			wLen;			//现在改变为整个结构体实际申请的内存 //strMonitor 的长度
    char 			strMonitor[0];
}DbWarnLvStr;
typedef union _DB_WARN_LVL_STR_U
{
    DbWarnLvStr		tLvl;
    BYTE*			baStr;
}DbWarnLvlU;

//对应于DB- T_KeyWordsSet T_FileType
//#define		DB_MAX_KEYWORDBUF_LEN	256
typedef struct DB_KEY_WORD_T
{
    INT32 	nIndex;			//对应于数据库中的ID
    BYTE	bLevel;			//对应于等级0-1-2; 如果是文档类型则对应classification 1-file 2-network
    BYTE	bGlobal;		//对应于数据库中的 isNoGlobal -  0(disable)  1(enable)
    //BYTE	bType;
    //BYTE	bReserved;
    //int nLevel;
    //DWORD dwTime
    char strKey[COMM_SRCH_KEY_LEN];
}DbKeyWord;

// DB -> T_WarnLevel
//关键词告警策略
typedef struct _DB_WARN_LEVEL_POLICY_T
{
    BYTE		bLevel;				//告警等级 0-1-2
    BYTE		bNetCtrl;			// if disable network 0-false 1-true
    BYTE		bUsbCtrl;			// if disable usb 0-false 1-true
    BYTE		bAlarm;				// if send the alarm message to server
    BYTE		bShowWarn;			// field informationRemind -> if show warning message
    BYTE		bLogKept;			// field logKept
    BYTE		baReserved[6];
}DbWarnLevel;

// DB -> T_Strategy
typedef struct _DB_CFG_POLICY_T
{
    INT32			nDbId;
    INT32			nVersion;
    DWORD32			dwTime;
//	DbKeywordPlcy	tKeyPlcy[3];
    DbWarnLevel		tWarnLvl[GR_DB_WARN_LEVEL];		//告警等级策略
    DbWarnLvStr		*tKeysPlcy;						//关键词列表
    char			strFileTypes[256];	//文件后缀列表,以; 区分
}DbCfgPlcy;

// DB -> T_Area
typedef struct _DB_TBL_AREA_T
{
    WORD			nDbId;				//仅仅局限于65535个单位
    WORD			nFID;
    BYTE			bGrade;
    BYTE			bType;
    char			strFDNCode[32];	//文件后缀列表,以; 区分
}DbTblArea;

//////////////////////////////////////////////////
// 定义指令结构
enum DB_TASK_STATUS_E
{
    EDB_TASK_INIT 		= 0,
    EDB_TASK_SEND 		= 2,
    EDB_TASK_SND_ERR 	= 3,
    EDB_TASK_OVER 		= 4,
    EDB_TASK_NO_RSP 	= 5,
    EDB_TASK_CLI_ERR 	= 6,	//目前客户端异常就认为命令无法执行,后续增加详细的子类型
    EDB_TASK_SVR_ERR 	= 7,	//服务端异常,后续增加详细的子类型
    EDB_TASK_RESND_ERR	= 8,	//服务端重发一定数量后仍然无响应
};

#define		DB_TASK_ID_MASK			0x1fffffff

// DB -> T_TaskList
typedef struct DB_TASK_LIST_T
{
    INT32			nItemState;	//当前项的状态
    INT32			nID;		//DB中的序列号	- 1~29个比特是真正的序号,30~31为不同命令的区分,32bit空
    INT32			nPID;		//Device ID
    INT32			nSubAlarm;	//Alarm 子表 的序列号
    INT32			nType;		//命令类型
    INT32			nTableType;	//命令来源 : 0-传统T_TaskList  1-T_NetTaskList 2-T_CheckVice
    INT32			nStatus;	//命令执行状态
    DWORD32			nErrCode;	//异常原因值- Generally from GetLastError
    INT32			nSndNum;	//指令重发次数- 重发指令可能需要挂接到另外的队列
    INT32			nSsnID;		//当前指令对应的执行命令的会话ID -> Session ID
    __time32_t	dwRcvTime;	//接收指令的时间
    __time32_t	dwSndTime;	//指令下发的时间，用于资源回收和超时重发
    __time32_t	dwCmpTime;	//指令完成时间
    __time32_t  dwRcntTime; //该指令的最近活跃时间
    char		strFile[256];	//上传文件名
    char		strExtPara[256];	//扩展参数- 可能是额外申请的内存指针,需要释放
}DbTaskList;

//服务端下发的终端磁盘文件目录检查命令
//临时定义,后续扩展- 关键词的长度是不确定的,后续考虑字符指针方式
typedef struct DB_TASK_SCANDISK_T
{
    int			nID;			//在返回的时候携带
    int			nSubID;
    char		strDir[280];	//如果为空,则为全盘扫描;否则指定目录扫描
    char		strKeys[1024];	//以; 号区分的关键词列表
}DbTaskScanDisk;

// 定义指令结构结束
//////////////////////////////////////////////////


//extern GR_UTLITY_API
//{
//extern GR_UTLITY_API MsgKeyPolicy	g_tKeyPolicy[];	//对应三个等级的关键词策略 0-level1 1-level2 2-level3
//extern GR_UTLITY_API MsgExtPolicy	g_tExtPolicy;

extern GR_UTLITY_API DbCfgPlcy	g_tDbCfgPlcy;

extern GR_UTLITY_API int NetDecodeAuth(char *pBuf, const int &nLen, NetMsgAuth *pPara);
extern GR_UTLITY_API int NetEncodeAuth(char *pBuf, const int &nLen, NetMsgAuth *pPara);
extern GR_UTLITY_API int NetDecodeAuthEx(char *pBuf, const int &nLen, NetMsgAuthEx *pPara);
extern GR_UTLITY_API int NetEncodeAuthEx(char *pBuf, const int &nLen, NetMsgAuthEx *pPara);
extern GR_UTLITY_API int NetDecodeAuthEx2(char *pBuf, const int &nLen, NetMsgAuthEx2 *pPara);
extern GR_UTLITY_API int NetEncodeAuthEx2(char *pBuf, const int &nLen, NetMsgAuthEx2 *pPara);
extern GR_UTLITY_API int NetEncodePacket(const int &nMsgType, char *pBuf, const int &nLen, void *pPara);
extern GR_UTLITY_API int NetDecodePacket(char *pBuf, const int &nLen, WORD &wMsg, void *pPara);
extern GR_UTLITY_API int NetDecodeWarnLvl3Policy(char *pBuf, const int &nLen, DbWarnLevel *pPara);
extern GR_UTLITY_API int NetEncodeWarnLvl3Policy(char *pBuf, const int &nLen, DbWarnLevel *pPara);
extern GR_UTLITY_API int NetDecode3KeyPolicy(char *pBuf, const int &nLen, DbWarnLvStr *pPara);
extern GR_UTLITY_API int NetEncode3KeyPolicy(char *pBuf, const int &nLen, DbWarnLvStr *pPara);
extern GR_UTLITY_API int NetEncodeExtPolicy(char *pBuf, const int &nLen, char *pPara);
extern GR_UTLITY_API int NetDecodeExtPolicy(char *pBuf, const int &nLen, char *pPara);
extern GR_UTLITY_API int NetEncodeCfgPlcy(char *pBuf, const int &nLen, DbCfgPlcy *pPara);
extern GR_UTLITY_API int NetDecodeCfgPlcy(char *pBuf, const int &nLen, DbCfgPlcy *pPara);
extern GR_UTLITY_API int NetEncodeUsbLog(char *pBuf, const int &nLen, DbUsbLog *pPara);
extern GR_UTLITY_API int NetDecodeUsbLog(char *pBuf, const int &nLen, DbUsbLog *pPara);
extern GR_UTLITY_API int NetEncodeAlarmEvent(char *pBuf, const int &nLen, DbAlarmEvent *pPara);
extern GR_UTLITY_API int NetDecodeAlarmEvent(char *pBuf, const int &nLen, DbAlarmEvent *pPara);
extern GR_UTLITY_API int NetEncodeAlarmList(char *pBuf, const int &nLen, FmSrchRpt *pPara);
extern GR_UTLITY_API int NetDecodeAlarmList(char *pBuf, const int &nLen, FmSrchRpt *pPara);
extern GR_UTLITY_API int NetEncodeNetAlarm(char *pBuf, const int &nLen, NetmSrchRpt *pPara);
extern GR_UTLITY_API int NetDecodeNetAlarm(char *pBuf, const int &nLen, NetmSrchRpt *pPara);
extern GR_UTLITY_API int NetEncodeRegAlarm(char *pBuf, const int &nLen, RegMonRpt *pPara, const int &nItemN);
extern GR_UTLITY_API int NetDecodeRegAlarm(char *pBuf, const int &nLen, RegMonRpt *pPara);
extern GR_UTLITY_API int NetEncodeFlchgAlarm(char *pBuf, const int &nLen, FileMonSys *pPara);
extern GR_UTLITY_API int NetDecodeFlchgAlarm(char *pBuf, const int &nLen, FileMonSys *pPara);
extern GR_UTLITY_API int NetEncodeFRegPolicy(char *pBuf, const int &nLen, DbWarnLvStr *pPara);
extern GR_UTLITY_API int NetDecodeFRegPolicy(char *pBuf, const int &nLen, DbWarnLvStr *pPara);
extern GR_UTLITY_API int NetEncodeTransFile(char *pBuf, const int &nLen, MsgTransFile *pPara);
extern GR_UTLITY_API int NetDecodeTransFile(char *pBuf, const int &nLen, MsgTransFile *pPara);
extern GR_UTLITY_API int NetEncodeSendFile(char *pBuf, const int &nLen, MsgSendFile *pPara);
extern GR_UTLITY_API int NetDecodeSendFile(char *pBuf, const int &nLen, MsgSendFile *pPara);
extern GR_UTLITY_API int NetEncodeCustMsg(char *pBuf, const DWORD32 &nLen, const WORD &wMsg,
        const char *pCustMsg, const DWORD32 & dwCustLen );
extern GR_UTLITY_API int NetDecodeCustMsg(char *pBuf, const int &nLen, void *pPara, const DWORD32 &dwLen);
extern GR_UTLITY_API int NetEncodeCommand(char *pBuf, const int &nLen, const WORD &wMsg, const DWORD32 &dwMID, const int & wAttach );
extern GR_UTLITY_API int NetEncodeFileChunk(char *pBuf, const int &nLen, MsgFileChunk *pPara);
extern GR_UTLITY_API int NetDecodeFileChunk(char *pBuf, const int &nLen, MsgFileChunk *pPara);
extern GR_UTLITY_API int NetEncodeSnapScrn(char *pBuf, const int &nLen, MsgTransFile *pPara);
extern GR_UTLITY_API int NetDecodeSnapScrn(char *pBuf, const int &nLen, MsgTransFile *pPara);
extern GR_UTLITY_API int NetEncodeSetUsrPwd(char *pBuf, const int &nLen, MsgSetUsrPwd *pPara);
extern GR_UTLITY_API int NetDecodeSetUsrPwd(char *pBuf, const int &nLen, MsgSetUsrPwd *pPara);
extern GR_UTLITY_API int NetEncodeDskSc(char *pBuf, const int &nLen, DbTaskScanDisk *pPara);
extern GR_UTLITY_API int NetDecodeDskSc(char *pBuf, const int &nLen, DbTaskScanDisk *pPara);
extern GR_UTLITY_API int NetEncryptData(char *pBuf, const int &nLen, char *pOut);
extern GR_UTLITY_API int NetDecryptData(char *pBuf, const int &nLen, char *pOut);
extern GR_UTLITY_API int NetEncodeErrNtfy(char *pBuf, const int &nLen, MsgErrNtfy *pPara);
extern GR_UTLITY_API int NetDecodeErrNtfy(char *pBuf, const int &nLen, MsgErrNtfy *pPara);
extern GR_UTLITY_API int NetEncodeAck(char *pBuf, const int &nLen, MsgAck *pPara);
extern GR_UTLITY_API int NetDecodeAck(char *pBuf, const int &nLen, MsgAck *pPara);
extern GR_UTLITY_API int UtlAllocMem(DbWarnLvStr **ptr,  WORD wAllocLen);
extern GR_UTLITY_API void UtlFreeMem(DbWarnLvStr *ptr);
//};

#ifdef CBUILDER_VER_6
//extern int strcpy_s(char * _Dst, const UINT & _SizeInBytes, const char * _Src);
extern GR_UTLITY_API int __cdecl strcpy_s(char *_DEST, size_t _SIZE, const char *_SRC);
extern GR_UTLITY_API int __cdecl strcat_s(char *_DEST, size_t _SIZE, const char *_SRC);
extern GR_UTLITY_API int memcpy_s(char *Dst, int nDstSize, const char *Src, int nCpyLen);
#endif
extern GR_UTLITY_API int memcpy_ex_s(char *Dst, const DWORD &nDstSize, const char *Src, const DWORD &nCpyLen);
/*
#ifndef CBUILDER_VER_6
extern int CBWriteLogin(int nPid, int nWid, char *strPid, char *strName, const int &nType, const int &nRet);
extern int CBWriteUsbLog(int &nPid, DbUsbLog &tUlog);
extern int CBWriteAlarmEvent(int &nPid, DbAlarmEvent &tAlarm);
extern int CBWriteAlarmList(const INT32 &nPid, const INT32 &nWid, const INT32 &nAid, FmSrchRpt &tAlarm);
extern int CBWriteNetAlarmList(const INT32 &nPid, const INT32 &nWid, const INT32 &nAid, NetmSrchRpt &tAlarm);
extern int CBWriteRegAlarm(const INT32 &nPid, const INT32 &nWid, const INT32 &nAid, RegMonRpt &tAlarm);
extern int CBWriteFlchgAlarm(const INT32 &nPid, const INT32 &nWid, const INT32 &nAid, FileMonSys &tAlarm);
extern int CBWriteCmdAck(const int &nID, const char *pPara);
extern int CBUpdateUsrPwd(const int &id, const char *strNewPwd);
#else
#define CBWriteLogin( nPid,  nWid, strPid, strName, nType, nRet)
#define  CBWriteUsbLog(a, b)
#define  CBWriteAlarmEvent(nPid, tAlarm)
#define  CBWriteAlarmList(nPid, nWid, nAid, tAlarm)
#define  CBWriteNetAlarmList(nPid, nWid, nAid, tAlarm)
#define  CBWriteRegAlarm(nPid, nWid, nAid, tAlarm)
#define  CBWriteFlchgAlarm(nPid, nWid, nAid, tAlarm)
#define  CBWriteCmdAck(nid,pPara)
#define  CBUpdateUsrPwd(nid,pPara)
#endif
*/
#endif

