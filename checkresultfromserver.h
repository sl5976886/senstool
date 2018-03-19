#pragma once

#include "xmlhtml/GrxaHostCheck.h"

class CheckResultResouceFromServer
{
public:
    // 组策略
    static AuditPolicy      *pAuditPolicy;
    static int              auditNum;
    static SystemAccess     *pSystemAccess;
    static int              systemNum;

    // 系统版本信息
    static OsVersionInfo    *pOsVersion;
    // DNS
    static char             szDns[512];

    // USB使用记录
    static USBHISTORY       *pUsbHistory;

    // 浏览器历史记录
    static IeVisitHistory *pIeHistory;
    static FireFoxHistory *pFirefoxHistory;
    static ChromeHistory *pChromeHistory;

    // 系统补丁
    static SystemDefectInfo *pSystemDefectInfo;

    // 启动项
    static RunItems *pRunItems;

    // 密码策略及账号锁定
    static CBuffer *pPolicyBuf;

    // 组策略
    static gropu_policy::DbGroupPolicy *pGroupPolicy;
    static int groupPolicyNum;

    // 用户权利指派
    static user_rights_assignment_t *pUserRightsAssignments;
    static int userRightsNum;

    // 账户信息
    static USER_INFO_2 *pUserInfo;
    static int usersNum;

    // 共享
    static SHARE_INFO_502 *pShareInfo;
    static int shareNum;

    // 服务
    static SERVICE_STATUS_INFO1 *pServiceStatus;
    static int servicesNum;

    // snmp
    static SNMPService *pSnmpService;

    // 系统安装时间
    static time_t osInstallTime;
    //主机名
    static char* computerName;

    // 软件
    static SoftwareInfo *pSoft;
    static int softNum;

    //进程
    static ProcessInfo* pProcess;
    static int processNum;

    // 杀毒软件
    static AntivirusSoft *pAntivirusSoft;
    static int antivirusSoftNum;
    static AntivirusProduct *pAntivirusPro;

    //开机时间
    static char* pBootTime;

    // BIOS
    static BiosInfo* pBiosInfo;

    //分区
    static LogicalDrivesInfo *pLogicDrives;
    static int logicDrivesNum;

    // 磁盘权限
    static DrivesAccountRights *pDrivesRights;
    static int drivesRightsNum;

    // 系统文件权限
    static DrivesAccountRights *pSystemRights;
    static int systemRightsNum;

    //CPU
    static CpuInfo* pCpuInfo;

    //硬盘
    static HardDiskInfo* pHardDisk;
    static int diskNum;

    //主板
    static MainBoardInfo* pBoardInfo;

    //显卡
    static DisplayInfo* pDisplayCard;

    //内存信息
    static MemoryInfo *pMemory;

    //声卡
    static AudioInfo* pAudio;

    //网卡
    static NetworkCardInfo *pNetwork;
    static int netcardNum;

    //安全选项
    static SecurityOptions *pSecurityOpt;
    static int secOptionsNum;
    // 注册表设置
    static SecurityOptions *pRegistrySets;
    static int regOptionsNum;
    // eventlog
    static SecurityOptions *pEventlogs;
    static int eventlogNum;

    //端口
    static PortInfo* pPortInfo;

    // 等保检查项
    static DtckResults* pDtckResults;

    // 从检查结果中分离出来的小项
    static  DtckResults* pDtPwdPolicy;
    static  DtckResults* pDtAccLockPolicy;

    static  DtckResults* pDtAuditPolicy;
    static  DtckResults* pDtUserRightAssignment;
    static  DtckResults* pDtSecurityOption;

    static  DtckResults* pDtCloseSharDisk;
    static  DtckResults* pDtAutoAdminLogin;
    static  DtckResults* pDtDriverAutoOperation;
    static  DtckResults* pDtMakeDumpFile;

    static  DtckResults* pDtService;
    static  DtckResults* pDtNetConnect;
    static  DtckResults* pDtGroupPolicy;
};
