//#include "checkresultfromserver.h"

// 组策略
AuditPolicy      *CheckResultResouceFromServer::pAuditPolicy   = NULL;
int              CheckResultResouceFromServer::auditNum        = 0;
SystemAccess     *CheckResultResouceFromServer::pSystemAccess  = NULL;
int              CheckResultResouceFromServer::systemNum       = 0;

// 系统版本信息
OsVersionInfo    *CheckResultResouceFromServer::pOsVersion     = NULL;
// DNS
char            CheckResultResouceFromServer::szDns[512] = "";

// USB使用记录
USBHISTORY       *CheckResultResouceFromServer::pUsbHistory    = NULL;

// 浏览器历史记录
IeVisitHistory   *CheckResultResouceFromServer::pIeHistory       = NULL;
FireFoxHistory   *CheckResultResouceFromServer::pFirefoxHistory  = NULL;
ChromeHistory    *CheckResultResouceFromServer::pChromeHistory    = NULL;

// 系统补丁
SystemDefectInfo *CheckResultResouceFromServer::pSystemDefectInfo  = NULL;

// 启动项
RunItems         *CheckResultResouceFromServer::pRunItems  = NULL;

// 密码策略及账号锁定
CBuffer          *CheckResultResouceFromServer::pPolicyBuf = NULL;

// 组策略
gropu_policy::DbGroupPolicy  *CheckResultResouceFromServer::pGroupPolicy   = NULL;
int                        CheckResultResouceFromServer::groupPolicyNum  = 0;

// 用户权利指派
user_rights_assignment_t *CheckResultResouceFromServer::pUserRightsAssignments = NULL;
int                      CheckResultResouceFromServer::userRightsNum           = 0;

// 账户信息
USER_INFO_2              *CheckResultResouceFromServer::pUserInfo  = NULL;
int                    CheckResultResouceFromServer::usersNum    = 0;

// 共享
SHARE_INFO_502           *CheckResultResouceFromServer::pShareInfo = NULL;
int                    CheckResultResouceFromServer::shareNum    = 0;

// 服务
SERVICE_STATUS_INFO1     *CheckResultResouceFromServer::pServiceStatus = NULL;
int                    CheckResultResouceFromServer::servicesNum     = 0;

// snmp
SNMPService             *CheckResultResouceFromServer::pSnmpService   = NULL;

// 系统安装时间
time_t                   CheckResultResouceFromServer::osInstallTime  = 0;
//主机名
char                     *CheckResultResouceFromServer::computerName   = NULL;

// 软件
SoftwareInfo             *CheckResultResouceFromServer::pSoft  = NULL;
int                    CheckResultResouceFromServer::softNum = 0;

//进程
ProcessInfo              *CheckResultResouceFromServer::pProcess   = NULL;
int                    CheckResultResouceFromServer::processNum  = 0;

// 杀毒软件
AntivirusSoft            *CheckResultResouceFromServer::pAntivirusSoft     = NULL;
int                     CheckResultResouceFromServer::antivirusSoftNum    = 0;
AntivirusProduct        *CheckResultResouceFromServer::pAntivirusPro      = NULL;

//开机时间
char                     *CheckResultResouceFromServer::pBootTime  = NULL;

// BIOS
BiosInfo                 *CheckResultResouceFromServer::pBiosInfo  = NULL;

//分区
LogicalDrivesInfo        *CheckResultResouceFromServer::pLogicDrives  = NULL;
int                    CheckResultResouceFromServer::logicDrivesNum = 0;

// 磁盘权限
DrivesAccountRights      *CheckResultResouceFromServer::pDrivesRights  = NULL;
int                    CheckResultResouceFromServer::drivesRightsNum = 0;

// 系统文件权限
DrivesAccountRights      *CheckResultResouceFromServer::pSystemRights  = NULL;
int                    CheckResultResouceFromServer::systemRightsNum = 0;

//CPU
CpuInfo                  *CheckResultResouceFromServer::pCpuInfo   = NULL;

//硬盘
HardDiskInfo             *CheckResultResouceFromServer::pHardDisk  = NULL;
int                    CheckResultResouceFromServer::diskNum     = 0;

//主板
MainBoardInfo            *CheckResultResouceFromServer::pBoardInfo = NULL;

//显卡
DisplayInfo              *CheckResultResouceFromServer::pDisplayCard   = NULL;

//内存信息
MemoryInfo               *CheckResultResouceFromServer::pMemory    = NULL;

//声卡
AudioInfo                *CheckResultResouceFromServer::pAudio = NULL;

//网卡
NetworkCardInfo          *CheckResultResouceFromServer::pNetwork   = NULL;
int                    CheckResultResouceFromServer::netcardNum  = 0;

//安全选项
SecurityOptions          *CheckResultResouceFromServer::pSecurityOpt   = NULL;
int                    CheckResultResouceFromServer::secOptionsNum   = 0;
// 注册表设置
SecurityOptions          *CheckResultResouceFromServer::pRegistrySets  = NULL;
int                    CheckResultResouceFromServer::regOptionsNum   = 0;
// eventlog
SecurityOptions          *CheckResultResouceFromServer::pEventlogs     = NULL;
int                    CheckResultResouceFromServer::eventlogNum     = 0;

//端口
PortInfo                 *CheckResultResouceFromServer::pPortInfo  = NULL;

// 等保检查项
DtckResults              *CheckResultResouceFromServer::pDtckResults          = NULL;
// 从检查结果中分离出来的小项
DtckResults              *CheckResultResouceFromServer::pDtPwdPolicy          = NULL;
DtckResults              *CheckResultResouceFromServer::pDtAccLockPolicy      = NULL;

DtckResults              *CheckResultResouceFromServer::pDtAuditPolicy        = NULL;
DtckResults              *CheckResultResouceFromServer::pDtUserRightAssignment= NULL;
DtckResults              *CheckResultResouceFromServer::pDtSecurityOption     = NULL;

DtckResults              *CheckResultResouceFromServer::pDtCloseSharDisk      = NULL;
DtckResults              *CheckResultResouceFromServer::pDtAutoAdminLogin     = NULL;
DtckResults              *CheckResultResouceFromServer::pDtDriverAutoOperation= NULL;
DtckResults              *CheckResultResouceFromServer::pDtMakeDumpFile       = NULL;

DtckResults              *CheckResultResouceFromServer::pDtService            = NULL;
DtckResults              *CheckResultResouceFromServer::pDtNetConnect         = NULL;
DtckResults              *CheckResultResouceFromServer::pDtGroupPolicy        = NULL;
