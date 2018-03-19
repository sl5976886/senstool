//#include "stdafx.h"
#include "CheckResultResouce.h"


// 组策略
AuditPolicy      *CheckResultResouce::pAuditPolicy   = NULL;
int              CheckResultResouce::auditNum        = 0;
SystemAccess     *CheckResultResouce::pSystemAccess  = NULL;
int              CheckResultResouce::systemNum       = 0;

// 系统版本信息
OsVersionInfo    *CheckResultResouce::pOsVersion     = NULL;
// DNS
char            CheckResultResouce::szDns[512] = "";

// USB使用记录
USBHISTORY       *CheckResultResouce::pUsbHistory    = NULL;

// 浏览器历史记录
IeVisitHistory   *CheckResultResouce::pIeHistory       = NULL;
FireFoxHistory   *CheckResultResouce::pFirefoxHistory  = NULL;
ChromeHistory    *CheckResultResouce::pChromeHistory    = NULL;

// 系统补丁
SystemDefectInfo *CheckResultResouce::pSystemDefectInfo  = NULL;

// 启动项
RunItems         *CheckResultResouce::pRunItems  = NULL;

// 密码策略及账号锁定
CBuffer          *CheckResultResouce::pPolicyBuf = NULL;

// 组策略
gropu_policy::DbGroupPolicy  *CheckResultResouce::pGroupPolicy   = NULL;
int                        CheckResultResouce::groupPolicyNum  = 0;

// 用户权利指派
user_rights_assignment_t *CheckResultResouce::pUserRightsAssignments = NULL;
int                      CheckResultResouce::userRightsNum           = 0;

// 账户信息
USER_INFO_2              *CheckResultResouce::pUserInfo  = NULL;
int                    CheckResultResouce::usersNum    = 0;

// 共享
SHARE_INFO_502           *CheckResultResouce::pShareInfo = NULL;
int                    CheckResultResouce::shareNum    = 0;

// 服务
SERVICE_STATUS_INFO1     *CheckResultResouce::pServiceStatus = NULL;
int                    CheckResultResouce::servicesNum     = 0;

// snmp
SNMPService             *CheckResultResouce::pSnmpService   = NULL;

// 系统安装时间
time_t                   CheckResultResouce::osInstallTime  = 0;
//主机名
char                     *CheckResultResouce::computerName   = NULL;

// 软件
SoftwareInfo             *CheckResultResouce::pSoft  = NULL;
int                    CheckResultResouce::softNum = 0;

//进程
ProcessInfo              *CheckResultResouce::pProcess   = NULL;
int                    CheckResultResouce::processNum  = 0;

// 杀毒软件
AntivirusSoft            *CheckResultResouce::pAntivirusSoft     = NULL;
int                     CheckResultResouce::antivirusSoftNum    = 0;
AntivirusProduct        *CheckResultResouce::pAntivirusPro      = NULL;

//开机时间
char                     *CheckResultResouce::pBootTime  = NULL;

// BIOS
BiosInfo                 *CheckResultResouce::pBiosInfo  = NULL;

//分区
LogicalDrivesInfo        *CheckResultResouce::pLogicDrives  = NULL;
int                    CheckResultResouce::logicDrivesNum = 0;

// 磁盘权限
DrivesAccountRights      *CheckResultResouce::pDrivesRights  = NULL;
int                    CheckResultResouce::drivesRightsNum = 0;

// 系统文件权限
DrivesAccountRights      *CheckResultResouce::pSystemRights  = NULL;
int                    CheckResultResouce::systemRightsNum = 0;

//CPU
CpuInfo                  *CheckResultResouce::pCpuInfo   = NULL;

//硬盘
HardDiskInfo             *CheckResultResouce::pHardDisk  = NULL;
int                    CheckResultResouce::diskNum     = 0;

//主板
MainBoardInfo            *CheckResultResouce::pBoardInfo = NULL;

//显卡
DisplayInfo              *CheckResultResouce::pDisplayCard   = NULL;

//内存信息
MemoryInfo               *CheckResultResouce::pMemory    = NULL;

//声卡
AudioInfo                *CheckResultResouce::pAudio = NULL;

//网卡
NetworkCardInfo          *CheckResultResouce::pNetwork   = NULL;
int                    CheckResultResouce::netcardNum  = 0;

//安全选项
SecurityOptions          *CheckResultResouce::pSecurityOpt   = NULL;
int                    CheckResultResouce::secOptionsNum   = 0;
// 注册表设置
SecurityOptions          *CheckResultResouce::pRegistrySets  = NULL;
int                    CheckResultResouce::regOptionsNum   = 0;
// eventlog
SecurityOptions          *CheckResultResouce::pEventlogs     = NULL;
int                    CheckResultResouce::eventlogNum     = 0;

//端口
PortInfo                 *CheckResultResouce::pPortInfo  = NULL;

// 等保检查项
DtckResults              *CheckResultResouce::pDtckResults          = NULL;
// 从检查结果中分离出来的小项
DtckResults              *CheckResultResouce::pDtPwdPolicy          = NULL;
DtckResults              *CheckResultResouce::pDtAccLockPolicy      = NULL;

DtckResults              *CheckResultResouce::pDtAuditPolicy        = NULL;
DtckResults              *CheckResultResouce::pDtUserRightAssignment= NULL;
DtckResults              *CheckResultResouce::pDtSecurityOption     = NULL;

DtckResults              *CheckResultResouce::pDtCloseSharDisk      = NULL;
DtckResults              *CheckResultResouce::pDtAutoAdminLogin     = NULL;
DtckResults              *CheckResultResouce::pDtDriverAutoOperation= NULL;
DtckResults              *CheckResultResouce::pDtMakeDumpFile       = NULL;

DtckResults              *CheckResultResouce::pDtService            = NULL;
DtckResults              *CheckResultResouce::pDtNetConnect         = NULL;
DtckResults              *CheckResultResouce::pDtGroupPolicy        = NULL;
