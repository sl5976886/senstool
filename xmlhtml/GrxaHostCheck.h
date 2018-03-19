#ifndef GRXA_HOST_CHECK_H
#define GRXA_HOST_CHECK_H

#include <windows.h>
#include "CheckCommon.h"

#ifdef GRXAHOSTCHECK_EXPORTS
#define GRXAHOSTCHECK_API __declspec(dllexport)
#else
#define GRXAHOSTCHECK_API __declspec(dllimport)
#endif

#define ARGCALLORDER
typedef VOID (*pfCheckCallBack)(char*pMsg, int iPercent);

#ifdef __cplusplus
extern "C" {
#endif

GRXAHOSTCHECK_API   VOID    SetCheckCallBackFun(pfCheckCallBack pfCallback);
GRXAHOSTCHECK_API   BOOL    ARGCALLORDER  HostCheckInit(char *pInitFile);
GRXAHOSTCHECK_API   BOOL    ARGCALLORDER  HostCheckUnInit();

// 设置消息回调函数
GRXAHOSTCHECK_API   BOOL    ARGCALLORDER  CheckResultCallBackProc(char* pMsg, int iPercent);
// 计算机名
GRXAHOSTCHECK_API   char*   ARGCALLORDER  GetNameOfComputer();
// 获取USB历史信息
// 成功返回USB使用历史记录，失败返回NULL
GRXAHOSTCHECK_API   USBHISTORY*     ARGCALLORDER  GetUsbUseHistory();
GRXAHOSTCHECK_API   VOID            ARGCALLORDER  ReleaseUsbUseHistory();
// IE历史记录
GRXAHOSTCHECK_API   IeVisitHistory* ARGCALLORDER  GetIeAccessHistory();
GRXAHOSTCHECK_API   void            ARGCALLORDER  ReleaseIeAccessHistory();
// 火狐浏览器历史记录
GRXAHOSTCHECK_API   FireFoxHistory* ARGCALLORDER  GetFirefoxHistory();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseFireFoxHistory();
// 谷歌浏览器历史记录
GRXAHOSTCHECK_API   ChromeHistory*  ARGCALLORDER  GetChromeHistory();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseChromeHistory();
// 获取系统补丁
GRXAHOSTCHECK_API   SystemDefectInfo*     ARGCALLORDER    GetHotfixesInfoWUAInstall();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseHotfixesInfoWUA();
// 启动项
GRXAHOSTCHECK_API   RunItems* ARGCALLORDER    GetRunItemsInfo();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseRunItemsInfo();
// 密码策略
GRXAHOSTCHECK_API   CBuffer*    ARGCALLORDER  GetSecurityPolicy();
// 组策略
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetGroupPolicyResult(gropu_policy::DbGroupPolicy **ppGroupPolicy);
// 权利指派，以下两个函数弃用
//GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetUserRightsAssignments(user_rights_assignment_t **ppUserRrightsAssignments);
//GRXAHOSTCHECK_API   VOID    ARGCALLORDER  ReleaseRightsAssignments();
// 策略和权利指派，以下三个函数执行前需要先调用InitPolicy，执行结束后需要调用UnInitPolicy
GRXAHOSTCHECK_API   BOOL    ARGCALLORDER  InitPolicy();
GRXAHOSTCHECK_API   BOOL    ARGCALLORDER  UnInitPolicy();
GRXAHOSTCHECK_API   BOOL    ARGCALLORDER  GetAuditPolicy(AuditPolicy **ppAuditPolicy, int &auditNum);
GRXAHOSTCHECK_API   BOOL    ARGCALLORDER  GetSystemAccessPolicy(SystemAccess **ppSystemAccess, int &systemNum);
GRXAHOSTCHECK_API   BOOL    ARGCALLORDER  GetUserRightsAssignment(user_rights_assignment_t **pUserRights, int &userRtNum);
// 账户信息
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetNetUsers(USER_INFO_2** ppUserInfo);
GRXAHOSTCHECK_API   VOID    ARGCALLORDER  ReleaseNetUsers();
// 共享
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetNetshare(SHARE_INFO_502 **ppShareInfo);
GRXAHOSTCHECK_API   VOID    ARGCALLORDER  ReleaseNetshare();
// 服务
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetServices(SERVICE_STATUS_INFO1 **ppServiceStatus);
GRXAHOSTCHECK_API   VOID    ARGCALLORDER  ReleaseServices();
// snmp
GRXAHOSTCHECK_API   SNMPService*    ARGCALLORDER  GetSnmpInfo();
GRXAHOSTCHECK_API   VOID    ARGCALLORDER  ReleaseSnmpInfo();
// 软件
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetSoftWareInfo(SoftwareInfo **ppSoft);
// 进程
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetProcessInfo(ProcessInfo **ppProcess);
// 杀毒软件，获取杀毒软件信息需要先获取安装软件和进程
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetViruslibraryUupdateTime(SoftwareInfo *pSoft, int iSoftSize, ProcessInfo *pProcess, int iProcessSize, AntivirusSoft **ppAntivirusSoft);
//GRXAHOSTCHECK_API   AntivirusProduct*   ARGCALLORDER  GetVirusLibraryInfo();
GRXAHOSTCHECK_API   VOID    ARGCALLORDER  ReleaseVirusLibraryInfo();
// 开机时间
GRXAHOSTCHECK_API   char*   ARGCALLORDER  GetSysBootTime();
// BIOS
GRXAHOSTCHECK_API   BiosInfo*   ARGCALLORDER  GetBiosInfo();
// 分区
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetLogicalDrivesInfo(LogicalDrivesInfo **ppLogDrives);
// 磁盘访问权限
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetDrivesAccountRights(DrivesAccountRights **ppDrivesRights);
GRXAHOSTCHECK_API   void    ARGCALLORDER  ReleaseDrivesAccountRights();
// 系统访问权限
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetSystemAccountRights(DrivesAccountRights **ppDrivesRights);
GRXAHOSTCHECK_API   void    ARGCALLORDER  ReleaseSystemAccountRights();
// CPU
GRXAHOSTCHECK_API   CpuInfo*    ARGCALLORDER  GetCPUInfo();
// 硬盘
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetHardDiskInfo(HardDiskInfo **ppHardDisk);
// 显卡
GRXAHOSTCHECK_API   DisplayInfo*    ARGCALLORDER  GetDisplayInfo();
// 主板
GRXAHOSTCHECK_API   MainBoardInfo*  ARGCALLORDER  GetBoardInfo();
// 内存
GRXAHOSTCHECK_API   MemoryInfo*     ARGCALLORDER  GetMemoryInfo();
// 声卡
GRXAHOSTCHECK_API   AudioInfo*  ARGCALLORDER  GetAudioInfo();
// 网卡
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetNetworkCardInfo(NetworkCardInfo **ppNetwork);
// DNS
GRXAHOSTCHECK_API   int     ARGCALLORDER  GetDNSInfo(char *szDns, int lenOfDns);
// 安全选项
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetSecurityOptionsValue(SecurityOptions **ppSOI);
// 注册表设置
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetRegistrySetsOptionsValue(SecurityOptions **ppRegistrySets);
// windows事件
GRXAHOSTCHECK_API   DWORD   ARGCALLORDER  GetEventlogsOptionsValue(SecurityOptions **ppEventlogs);

// 端口
GRXAHOSTCHECK_API   PortInfo* ARGCALLORDER    GetPort();
GRXAHOSTCHECK_API   void    ARGCALLORDER  ReleasePortInfo();


// 等保检查项项
GRXAHOSTCHECK_API   DtckResults*    ARGCALLORDER  GetDtckResults();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseDtckResults();
// 从检查结果中剥离出来的细项
GRXAHOSTCHECK_API   DtckResults*    ARGCALLORDER  GetDtckResultsPwdPolicy();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseDtckResultsPwdPolicy();
GRXAHOSTCHECK_API   DtckResults*    ARGCALLORDER  GetDtckResultsAccLockPolicy();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseDtckResultsAccLockPolicy();

GRXAHOSTCHECK_API   DtckResults*    ARGCALLORDER  GetDtckResultsAuditPolicy();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseDtckResultsAuditPolicy();
GRXAHOSTCHECK_API   DtckResults*    ARGCALLORDER  GetDtckResultsUserRightAssignment();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseDtckResultsUserRightAssignment();
GRXAHOSTCHECK_API   DtckResults*    ARGCALLORDER  GetDtckResultsSecurityOption();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseDtckResultsSecurityOption();

GRXAHOSTCHECK_API   DtckResults*    ARGCALLORDER  GetDtckResultsCloseSharDisk();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseDtckResultsCloseSharDisk();
GRXAHOSTCHECK_API   DtckResults*    ARGCALLORDER  GetDtckResultsAutoAdminLogin();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseDtckResultsAutoAdminLogin();
GRXAHOSTCHECK_API   DtckResults*    ARGCALLORDER  GetDtckResultsDriverAutoOperation();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseDtckResultsDriverAutoOperation();
GRXAHOSTCHECK_API   DtckResults*    ARGCALLORDER  GetDtckResultsMakeDumpFile();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseDtckResultsMakeDumpFile();

GRXAHOSTCHECK_API   DtckResults*    ARGCALLORDER  GetDtckResultsService();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseDtckResultsService();
GRXAHOSTCHECK_API   DtckResults*    ARGCALLORDER  GetDtckResultsNetConnect();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseDtckResultsNetConnect();
GRXAHOSTCHECK_API   DtckResults*    ARGCALLORDER  GetDtckResultsGroupPolicy();
GRXAHOSTCHECK_API   void ARGCALLORDER ReleaseDtckResultsGroupPolicy();


// 获取组策略
// 成功返回TRUE，失败返回FALSE
GRXAHOSTCHECK_API   BOOL    ARGCALLORDER  GetSecEditItemResult2(AuditPolicy **ppAuditPolicy, int &auditNum, SystemAccess **ppSystemAccess, int &systemNum,
                                                  user_rights_assignment_t **ppUserRightsAssignment, int &userRightNum);
// 获取OS系统信息
// 失败返回NULL，成功返回操作系统指针
GRXAHOSTCHECK_API   OsVersionInfo*  ARGCALLORDER  GetOsVersionInfo();
// 系统安装时间，返回秒数
GRXAHOSTCHECK_API   time_t  ARGCALLORDER  GetOsTimeInfo();

GRXAHOSTCHECK_API   char*   ARGCALLORDER  GetPatchLevel(int iLevel);



#ifdef __cplusplus
}
#endif

#endif  // GRXA_HOST_CHECK_H
