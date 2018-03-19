#ifndef CHECK_COMMON_H
#define CHECK_COMMON_H

#include <windows.h>
#include <LMaccess.h>
#include <LMShare.h>
#include <WinSvc.h>



#define MAX_FUNC_ITEM_NUM   1000
//==================================================================================

typedef enum _CHECK_LEVEL
{
    CHECK_LEVEL_BEGIN=1,
    CHECK_LEVEL_1   = CHECK_LEVEL_BEGIN,
    CHECK_LEVEL_2   = 2,
    CHECK_LEVEL_3   = 4,
    CHECK_LEVEL_4   = 8,
    CHECK_LEVEL_END=CHECK_LEVEL_4,
    CHECK_LEVEL_UNKNOWN = 16,
}CHECK_LEVEL, *LPCHECK_LEVEL;


#define CHECK_LEVEL_12          (CHECK_LEVEL_1 | CHECK_LEVEL_2)
#define CHECK_LEVEL_23          (CHECK_LEVEL_2 | CHECK_LEVEL_3)
#define CHECK_LEVEL_34          (CHECK_LEVEL_3 | CHECK_LEVEL_4)
#define CHECK_LEVEL_234         (CHECK_LEVEL_2 | CHECK_LEVEL_3 | CHECK_LEVEL_4)
#define CHECK_LEVEL_1234        (CHECK_LEVEL_1 | CHECK_LEVEL_2 | CHECK_LEVEL_3 | CHECK_LEVEL_4)
//工具软件模块定义 - 全局统一定义不得自行修改
typedef enum DT_MODULE_E
{
    DTMDL_ZDAQ_WIN = 1	,		//WINDOWS 终端安全
    DTMDL_ZDAQ_LINUX	,		//LINUX 终端安全
    DTMDL_KLPJ			,		//口令破解
    DTMDL_PZFX			,		//配置分析
    DTMDL_EYDM			,		//恶意代码
    DTMDL_RDSM			,		//弱点扫描
    DTMDL_LDLY			,		//漏洞利用

}DtModuleE;

typedef enum    E_TOOL_TYPE
{
    E_TP_WINDOWS,   //"windows主机配置检查工具"
    E_TP_LINUX,     // "linux主机配置检查工具"
    E_TP_VIRUS,     // "病毒检查工具"
    E_TP_TROJAN,    // "木马检查工具"
    E_TP_NETEQU,    // "网络设备配置检查工具"
    E_TP_WEBSHELL,  // "网站恶意代码检查工具"
    E_TP_RESERVE,   // "保留，以便后续扩充使用"
    E_TP_SAFEEQU,   // "安全设备配置检查工具"
    E_TP_WEAKPWD,   // "弱口令检查工具"
    E_TP_SQLINJECT, // "SQL注入验证检查工具"
    E_TP_SYSSCAN,   // "系统漏洞扫描工具"
    E_TP_WEBSCAN,   // "网站安全检查工具"
    E_TP_DBSCAN,   // "数据库安全检查工具"
}EToolType;

typedef enum    E_CHECK_CONTROL_POINT
{
    E_TP_WINDOWS_CONTROL_POINT_BEGIN = 100,
    E_TP_WINDOWS_ACCOUNTPOLICY = E_TP_WINDOWS_CONTROL_POINT_BEGIN,    // 账户策略
    E_TP_WINDOWS_LOCALPOLICY,           // 本地策略
    E_TP_WINDOWS_INFORMATIONPOLICY,     // 信息策略
    E_TP_WINDOWS_SERVICE,               // 服务策略
    E_TP_WINDOWS_GROUPPOLICY,           // 组策略，网络连接，等保标准中把网络连接被归到组策略中去了
    //E_TP_WINDOWS_NET_CONNECT,           // 网络连接，等保标准中把网络连接被归到组策略中去了

}ECheckControlPoint;

typedef struct E_CHECK_CONTROL_POINT_INFO
{
    ECheckControlPoint    tCheckItemType;
    CHAR                  szItemDescribe[300];
}ECheckControlPointInfo, *LPECheckControlPointInfo;

typedef enum    E_CHECK_CONTROL_POINT_ITEM
{
    E_TP_WINDOWS_CONTROL_POINT_ITEM_BEGIN = 100,
    E_TP_WINDOWS_ACCOUNTPOLICY_ITEM = E_TP_WINDOWS_CONTROL_POINT_ITEM_BEGIN,                    // 账户策略未知
    E_TP_WINDOWS_ACCOUNTPOLICY_PWDPOLICY,               // 密码策略
    E_TP_WINDOWS_ACCOUNTPOLICY_ACCLOCKPOLICY,           // 访问锁定策略

    E_TP_WINDOWS_LOCALPOLICY_ITEM,                      // 本地策略未知
    E_TP_WINDOWS_LOCALPOLICY_AUDITPOLICY,               // 审核策略
    E_TP_WINDOWS_LOCALPOLICY_USERRIGHTASSIGNMENT,       // 用户权限指派
    E_TP_WINDOWS_LOCALPOLICY_SECURITYOPTION,            // 安全选项

    E_TP_WINDOWS_INFORMATIONPOLICY_ITEM,                // 信息策略未知
    E_TP_WINDOWS_INFORMATIONPOLICY_CLOSESHAREDISK,      // 关闭默认共享
    E_TP_WINDOWS_INFORMATIONPOLICY_AUTOADMINLOGIN,      // 管理员自动登陆
    E_TP_WINDOWS_INFORMATIONPOLICY_DRIVERAUTOOPERATION, // 驱动自动运行
    E_TP_WINDOWS_INFORMATIONPOLICY_MAKEDUMPFILE,        // 生成dump文件
    E_TP_WINDOWS_INFORMATIONPOLICY_ANTIVIRUSINSTALL,    // 反病毒软件安装

    E_TP_WINDOWS_SERVICE_ITEM,      // 服务策略项
    //     E_TP_WINDOWS_SERVICE_REMOTEREGISTRY,    // Remote Registry
    //     E_TP_WINDOWS_SERVICE_MESSAGER,          // Messenger
    //     E_TP_WINDOWS_SERVICE_CLIPBOOK,          // Clipbook
    //     E_TP_WINDOWS_SERVICE_ALERTER,           // Alerter

    E_TP_WINDOWS_GROUPPOLICY_ITEM,          // 组策略项
    E_TP_WINDOWS_GROUPPOLICY_NET_CONNECT,   // 网络连接项
    //E_TP_WINDOWS_NET_CONNECT_ITEM,  // 网络连接项

}ECheckControlPointItem;

typedef struct E_CHECK_CONTROL_POINT_ITEM_INFO
{
    ECheckControlPointItem  tCheckItemType;
    CHAR                    szItemDescribe[300];
}ECheckControlPointItemInfo, *LPECheckControlPointItemInfo;

// 主机检查类别
typedef enum _HOST_SECURITY_CHECK_TYPE
{
    // 主机
    HOST_SECURITY_BEGIN,
    HOST_IDCHECK = HOST_SECURITY_BEGIN, // 身份鉴别
    HOST_ACL,                           // 访问控制
    HOST_SAFEAUDIT,                     // 安全审计
    HOST_INTRUSIONPREVENTION,           // 入侵防范
    HOST_MALWARE,                       // 恶意代码防范
    HOST_RESOURCE,                      // 资源控制
    HOST_SECURITY_END   = HOST_RESOURCE,


    // 网络设备
    NET_SECURITY_BEGIN,
    NET_STRUCTURESAFETY = NET_SECURITY_BEGIN,   // 结构安全
    NET_ACL,                    // 访问控制
    NET_SAFEAUDIT,              // 安全审计
    NET_COMPLETEBOUNDARY,       // 边界完整性检查
    NET_INTRUSIONPREVENTION,    // 入侵防范
    NET_MALICIOUSCODE,          // 恶意代码防范
    NET_PROTECTION,             // 网络设备防护
    NET_SECURITY_END,

    // 未知
    HOST_UNKNOWN_TYPE,          // 未知的类型

}HOST_SECURITY_CHECK_TYPE, *LPHOST_SECURITY_CHECK_TYPE;

// 主机检查子类别
typedef enum _HOST_SECURITY_CHECK_SUB_TYPE
{
    // 主机安全
    // 身份鉴别
    HOST_IDCHECK_COMBINATION,       // 应采用两种或两种以上组合的鉴别技术对管理用户进行身份鉴别；
    HOST_IDCHECK_USER,              // 操作系统和数据库系统管理用户身份标识应具有不易被冒用的特点，口令应有复杂度要求并定期更换。
    HOST_IDCHECK_CANT_FORGE,        // 身份鉴别信息至少有一种是不可伪造的。

    // 访问控制
    HOST_ACL_DEFAULTUSER,           // 应严格限制默认账户的访问权限，重命名系统默认账户，修改这些账户的默认口令；

    // 安全审计
    HOST_SAFEAUDIT_AUDIT,           // 应对重要用户行为、系统资源的异常使用和重要系统命令的使用等系统内重要的安全相关事件进行审计，并能够根据记录数据进行分析，并生成审计报表；
    HOST_SAFEAUDIT_LOGPROTECT,      // 应对审计记录进行保护，避免受到未预期的删除、修改或覆盖等。
    HOST_SAFEAUDIT_FORTIANALYZER,   // 应能够根据信息系统的统一安全策略，实现集中审计。

    // 入侵防范
    HOST_INTRUSIONPREVENTION_DEAL,  // 应能够检测到对重要服务器进行入侵的行为，并在发生严重入侵事件时提供报警。

    // 恶意代码防范
    HOST_MALWARE_INSTALL,           // 应安装防恶意代码软件，并及时更新防恶意代码软件版本和恶意代码库；

    // 资源控制
    HOST_RESOURCE_MONITOR,          // 应对主要服务器进行监视，包括监视服务器的CPU、硬盘、内存、网络等资源的使用情况。


    // 网络安全
    // 结构安全
    NET_STRUCTURESAFETY_VLAN,       // 应绘制与当前运行情况相符的网络拓扑结构图，并根据各网段重要性划分不同的子网或网段；
    NET_STRUCTURESAFETY_QUARANTINE, // 且重要网段与其他网段之间应采取可靠的技术隔离手段。

    // 访问控制
    NET_ACL_ENABLE,                 // 应在网络边界部署访问控制设备，启用访问控制功能，且访问控制功能应根据会话状态信息为数据流提供明确的允许/拒绝访问的能力，控制粒度应为端口级；
    NET_ACL_ARP,                    // 重要网段应采取技术手段防止地址欺骗。
    NET_ACL_DIAL,                   // 应不开放远程拨号访问功能。

    // 安全审计
    NET_SAFEAUDIT_LOGPROTECT,       // 应对审计记录进行保护，避免受到未预期的删除、修改或覆盖等。
    NET_SAFEAUDIT_STATUS,           // 应对网络系统中的网络设备运行状况、网络流量、用户行为等进行日志记录，并能够根据记录数据进行分析，并生成审计报表；
    NET_SAFEAUDIT_LIMITMEMORY,      // 应定义审计跟踪极限的阈值，当存储空间接近极限时，能采取必要的措施，当存储空间被耗尽时，终止可审计事件的发生；应实现集中审计，时钟保持与时钟服务器同步。

    // 边界完整性检查
    NET_COMPLETEBOUNDARY_NETACCESS, // 应能够对非授权设备私自联到内部网络和内部网络用户私自联到外部网络的行为进行检查，准确定出位置，并对其进行有效阻断。

    // 入侵防范
    NET_INTRUSIONPREVENTION_ATTACK, // 应在网络边界处监视以下攻击行为：端口扫描、强力攻击、木马后门攻击、拒绝服务攻击、缓冲区溢出攻击、IP碎片攻击和网络蠕虫攻击等，并在检测到攻击时，应针对严重入侵事件进行报警。

    // 恶意代码防范
    NET_MALICIOUSCODE_KILL,         // 应在网络边界处对恶意代码进行检测和清除。

    // 网络设备防护
    NET_PROTECTION_IDAUDIT,         // 应对登录网络设备的用户进行身份鉴别，且对同一用户应选择两种或两种以上组合的鉴别技术来进行身份鉴别，身份鉴别信息应具有不易被冒用的特点，口令应有复杂度要求并定期更换；
    NET_PROTECTION_CIPHERTEXT,      // 当对网络设备进行远程管理时，应采取必要措施防止鉴别信息在网络传输过程中被窃听。
    NET_PROTECTION_IDFORGE,         // 网络设备用户的身份鉴别信息至少应有一种是不可伪造的；

    HOST_UNKNOWN_SUBCHECK,          // 未知的检查点

}HOST_SECURITY_CHECK_SUB_TYPE, *LPHOST_SECURITY_CHECK_SUB_TYPE;

// 网络设备检查类别
typedef enum _NETWORK_EQUIPMENT_CHECK_TYPE
{
    NETWORK_EQUIPMENT_STRUCTURE_SAFETY  = 1,        // 结构安全
    NETWORK_EQUIPMENT_ACCESS_CONTROL,               // 访问控制
    NETWORK_EQUIPMENT_SECURITY_AUDIT,               // 安全审计
    NETWORK_EQUIPMENT_COMPLETE_BOUNDARY,            // 边界完整性
    NETWORK_EQUIPMENT_INTRUSION_PREVENTION,         // 入侵防范
    NETWORK_EQUIPMENT_MALICIOUS_CODE_RESISTANCE,    // 恶意代码防范
    NETWORK_EQUIPMENT_PROTECTION,                   // 网络设备防护

}NETWORK_EQUIPMENT_CHECK_TYPE, *LPNETWORK_EQUIPMENT_CHECK_TYPE;

typedef enum _HOST_CHECK_ITEM_TYPE
{
    // 主机安全
    // 身份鉴别
    // 应采用两种或两种以上组合的鉴别技术对管理用户进行身份鉴别；
    HOST_IDCHECK_IDCHECK_COMBINATION,       // 操作系统和数据库系统管理用户采取两种或两种以上组合鉴别技术（证书、用户名/口令、动态令牌和生物特性等均可作为一种鉴别技术，两种鉴别技术需作为前后两道认证机制，而不是通过用户名/口令或证书均可完成认证）。
    // 操作系统和数据库系统管理用户身份标识应具有不易被冒用的特点，口令应有复杂度要求并定期更换。
    HOST_IDCHECK_USER_PWD_COMPLEXITY,       // 操作系统的密码复杂度是否符合要求？
    HOST_IDCHECK_USER_PWD_MIN_LEN,          // 操作系统的密码长度最小值是否符合要求？
    HOST_IDCHECK_USER_PWD_AGEING_TIME,      // 操作系统的密码使用期限是否符合要求？
    HOST_IDCHECK_USER_PWD_OLD_NOT_USE,      // 操作系统的旧密码不被连续重新使用是否符合要求？
    HOST_IDCHECK_USER_LOGIN_FAIL_NUM,       // 操作系统的帐户被锁定的登录尝试失败的次数是否符合要求？
    HOST_IDCHECK_USER_LOGIN_FAIL_LOCK_TIME, // 操作系统的锁定帐户在自动解锁之前保持锁定的时间是否符合要求？
    HOST_IDCHECK_USER_RESTE_LOCK_COUNTER,   // 操作系统的复位账户锁定计数器的安全设置是否符合要求？
    HOST_IDCHECK_USER_ACCOUNT_SAME_UID,     // 是否无相同UID账户？
    HOST_IDCHECK_USER_ACCOUNT_WITHOUT_PWD,  // 是否无空密码账户？
    HOST_IDCHECK_USER_SYS_ACCOUNT_ENABLE_PWD_COMPLEXITY,    // 系统账户是否启用密码复杂性要求？
    HOST_IDCHECK_USER_SYS_ACCOUNT_PWD_MIN_LEN,      // 系统账户密码长度最小值是否符合要求？
    HOST_IDCHECK_USER_SYS_ACCOUNT_PWD_AGEING_TIME,  // 系统账户密码有效期是否符合要求？
    HOST_IDCHECK_USER_LOGIN_FAIL_DEAL,              // 登录失败处理功能是否符合要求？
    HOST_IDCHECK_USER_ACCOUNT_WITHOUT_WEAK_PWD,     // 是否无弱口令账户？
    HOST_IDCHECK_USER_WITHOUT_DEFAULT_USER,         // 是否禁止所有操作系统随带的缺省账号？
    HOST_IDCHECK_USER_WEAK_PWD_SMB,         // 是否不存在SMB协议弱口令？
    HOST_IDCHECK_USER_WEAK_PWD_MSSQL,       // 是否不存在MSSQL协议弱口令？
    HOST_IDCHECK_USER_WEAK_PWD_FTP,         // 是否不存在FTP协议弱口令？
    HOST_IDCHECK_USER_WEAK_PWD_MYSQL,       // 是否不存在MYSQL协议弱口令？
    HOST_IDCHECK_USER_WEAK_PWD_ORACLE,      // 是否不存在ORAClE协议弱口令？
    HOST_IDCHECK_USER_WEAK_PWD_RDP,         // 是否不存在RDP协议弱口令？
    HOST_IDCHECK_USER_WEAK_PWD_POP3,        // 是否不存在POP3协议弱口令？
    HOST_IDCHECK_USER_WEAK_PWD_SSH,         // 是否不存在SSH协议弱口令？
    HOST_IDCHECK_USER_DB_PWD_MIN_LEN,       // 数据库账户密码长度最小值是否符合要求？
    HOST_IDCHECK_USER_DB_PWD_AGEING_TIME,   // 数据库账户密码有效期是否符合要求？
    HOST_IDCHECK_USER_DB_LOGIN_FAIL_DEAL,   // 数据库登录失败处理功能是否符合要求？
    HOST_IDCHECK_USER_DB_WITHOUT_DEFAULT_USER,  // 是否禁止数据库随带的缺省账号？
    // 身份鉴别信息至少有一种是不可伪造的。
    HOST_IDCHECK_IDCHECK_CANT_FORGE,        // 鉴别技术中至少采用一种生物特征鉴别技术.

    // 访问控制
    // 应严格限制默认账户的访问权限，重命名系统默认账户，修改这些账户的默认口令；
    HOST_ACL_DEFAULTUSER_DB_DEFAULT_DISABLE,        // 数据库已禁用或删除默认的用户名和口令。
    HOST_ACL_DEFAULTUSER_SHUTDOWN_WITHOUT_LOGIN,    // 是否禁止系统在未登录的情况下关闭？
    HOST_ACL_DEFAULTUSER_RENAME_ADMIN,              // 是否重命名管理员帐户？
    HOST_ACL_DEFAULTUSER_LOGIN_WITH_THREE_KEY,      // 是否禁用无须按Ctrl+Alt+Del才能登录？
    HOST_ACL_DEFAULTUSER_ADMIN_AUTO_LOGIN,          // 是否禁用自动管理员登陆？
    HOST_ACL_DEFAULTUSER_SAM_ENUM_ANONYMITY,        // 是否启用不允许 SAM 帐户的匿名枚举功能？
    HOST_ACL_DEFAULTUSER_SAM_SHARE_ENUM_ANONYMITY,  // 是否启用不允许 SAM 帐户和共享的匿名枚举？
    HOST_ACL_DEFAULTUSER_EVERYONE_FOR_ANONYMITY,    // 是否禁用将Everyone 权限应用于匿名用户？
    HOST_ACL_DEFAULTUSER_SAVE_PWD_FOR_NET_ID,       // 是否启用不允许存储网络身份验证的密码和凭据？
    HOST_ACL_DEFAULTUSER_SAVE_HASH_FOR_CHANGE_PWD,  // 是否启用更改密码时不存储 LAN 管理器哈希值功能？
    HOST_ACL_DEFAULTUSER_NULL_PWD_LOGIN_CONSOLE,    // 是否启用使用空密码的本地帐户只允许进行控制台登录功能？
    HOST_ACL_DEFAULTUSER_DRIVES_AUTO_RUN,           // 是否禁用全部驱动器自动运行？
    HOST_ACL_DEFAULTUSER_ALLOW_AUTO_LOGIN,          // 是否禁用恢复控制台中的允许自动管理登陆的功能？
    HOST_ACL_DEFAULTUSER_FLOPPY_COPY,               // 是否允许软盘复制并访问所有驱动器和所有文件夹？
    HOST_ACL_DEFAULTUSER_DISABLE_SMB_WITHOUT_ENCRYPT,   // 是否禁用发送未加密的密码以连接到第三方 SMB 服务器的功能？
    HOST_ACL_DEFAULTUSER_UMASK_WITH_022,                // 系统当前的umask文件权限限制措施是否为022？
    HOST_ACL_DEFAULTUSER_DISABLE_SUDO,                  // 是否启用sudo命令？
    HOST_ACL_DEFAULTUSER_DIR_WITH_777_CONTAIN_ENV_VAR,  // 环境变量下权限为777的目录是否符合要求？
    HOST_ACL_DEFAULTUSER_FILE_WITH_777_CONTAIN_ENV_VAR, // 环境变量下权限为777的文件是否符合要求？
    HOST_ACL_DEFAULTUSER_ACL_KEY_FILE,          // 是否严格限制关键文件权限？
    HOST_ACL_DEFAULTUSER_ACL_KEY_FILE_OWNER,    // 是否严格限制关键文件的属主？
    HOST_ACL_DEFAULTUSER_DISABLE_REMOTE_ROOT,   // 是否禁止root账户远程登陆？
    HOST_ACL_DEFAULTUSER_IMPORT_RESOURCE,       // 重要信息资源设置有敏感标记。
    HOST_ACL_DEFAULTUSER_DISABLE_GUEST,         // 是否禁用来宾GUEST帐户状态？
    HOST_ACL_DEFAULTUSER_DB_ACL_ADMIN,          // 数据库的管理员权限是否严格限制？
    HOST_ACL_DEFAULTUSER_DB_MODIFY_DEFAULT_PWD,     // 数据库的默认口令是否修改？
    HOST_ACL_DEFAULTUSER_DB_RENAME_DEFAULT_USER,    // 数据库的默认帐户限是否重命名，或禁用？
    HOST_ACL_DEFAULTUSER_DB_REMOTE_CONNECT_ENCRYPT, // 数据库远程访问是否采用加密方式？

    // 安全审计
    // 应对重要用户行为、系统资源的异常使用和重要系统命令的使用等系统内重要的安全相关事件进行审计，并能够根据记录数据进行分析，并生成审计报表；
    HOST_SAFEAUDIT_AUDIT_LOGIN_EVENT,           // 操作系统的审核登录事件安全设置是否符合要求？
    HOST_SAFEAUDIT_AUDIT_OBJ_ACCESS,            // 操作系统的审核对象访问安全设置是否符合要求？
    HOST_SAFEAUDIT_AUDIT_PROCESS_TRACKING,      // 操作系统的审核过程跟踪安全设置是否符合要求？
    HOST_SAFEAUDIT_AUDIT_DIR_SERVICE_ACCESS,    // 操作系统的审核目录服务访问安全设置是否符合要求？
    HOST_SAFEAUDIT_AUDIT_PRIVILEGE_USAGE,       // 操作系统的审核特权使用安全设置是否符合要求？
    HOST_SAFEAUDIT_AUDIT_SYS_EVENT,             // 操作系统的审核系统事件安全设置是否符合要求？
    HOST_SAFEAUDIT_AUDIT_ACCOUNT_LOGIN_EVENT,   // 操作系统的审核账户登录事件安全设置是否符合要求？
    HOST_SAFEAUDIT_AUDIT_ACCOUNT_MANAGE,        // 操作系统的审核账户管理安全设置是否符合要求？
    HOST_SAFEAUDIT_AUDIT_CHANGE_POLICIES,       // 操作系统的审核策略更改安全设置是否符合要求？
    HOST_SAFEAUDIT_AUDIT_SYS_LOG_AND_SAFE,      // 是否开启系统日志和系统安全审计功能？
    HOST_SAFEAUDIT_AUDIT_MANAGE_PRIVILEGE_SAFE, // 是否开启对管理、特权和安全等行为进行审计？
    HOST_SAFEAUDIT_AUDIT_SYS_LOG,               // 系统已开启系统日志审计功能；
    HOST_SAFEAUDIT_AUDIT_LOG_REPORT,            // 通过日志管理工具对系统日志进行统计分析并生成报表。
    HOST_SAFEAUDIT_AUDIT_DBLOG_SAFE,            // 是否开启数据库日志和安全审计功能？
    // 应对审计记录进行保护，避免受到未预期的删除、修改或覆盖等。
    HOST_SAFEAUDIT_LOGPROTECT_LOG_PRIVILEGE,    // 系统日志文件权限设置符合安全要求；
    HOST_SAFEAUDIT_LOGPROTECT_SAVE_AUDIT_RESULT,    // 已对审计记录进行备份保存；
    HOST_SAFEAUDIT_LOGPROTECT_LOG_CANT_DEL,         // 不为用户提供日志单条删除功能。
    // 应能够根据信息系统的统一安全策略，实现集中审计。
    HOST_SAFEAUDIT_FORTIANALYZER_AUDIT,       // 根据信息系统的统一安全策略，实现集中审计。

    // 入侵防范
    // 应能够检测到对重要服务器进行入侵的行为，并在发生严重入侵事件时提供报警。
    HOST_INTRUSIONPREVENTION_CHECK_AND_ALARM,       // 已部署有可检测到对重要服务器有入侵行为的设备；
    HOST_INTRUSIONPREVENTION_ALARM_WAY,             // 入侵报警方式包括邮件、短信或声音等；
    HOST_INTRUSIONPREVENTION_ALARM_SET,             // 入侵防范产品中报警的目标手机和邮件地址设置正确
    // 用户权限指派
    //     HOST_INTRUSIONPREVENTION_BACK_FILE,             // 操作系统中备份文件和目录的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_CREATE_SAFE_AUDIT,     // 操作系统中生成安全审核的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_CREATE_TOKEN,          // 操作系统中创建令牌对象的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_CREATE_PAGE,           // 操作系统中创建页面文件的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_CREATE_SHARE_FOREVER,  // 操作系统中创建永久共享对象的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_SHUTDOWN_FROM_REMOTE,  // 操作系统中从远程系统强制关机的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_DEBUG_PROGRAM,         // 操作系统中调试程序的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_ADJUST_PROCESS_MEM_ALLOCATION, // 操作系统中调整进程的内存配额的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_CHANGE_SYS_TIME, // 操作系统中更改系统时间的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_DISABLE_SYS_PRIVILEGE_ASSIGN,  // 操作系统中关闭系统的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_MANAGE_AUDIT_AND_LOG,      // 操作系统中管理审核和安全日志的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_RESTORE_FILE_AND_DIR,      // 操作系统中还原文件和目录的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_GET_FILE_OWNERSHIP,        // 操作系统中取得文件或其他对象的所有权的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_OPERATING_MODE,            // 操作系统中以操作系统方式操作的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_ADD_WORKSTATION_IN_DOMAIN, // 操作系统中域中添加工作站的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_TRUST_PC,                  // 操作系统中允许计算机和用户帐户被信任以便于委任的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_INCREASE_SCHEDULING_PRIORITY,  // 操作系统中增加进度优先级的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_PERFORM_VOLUME_MAINTAIN,   // 操作系统中执行卷维护任务的权利指派是否符合要求？
    //     HOST_INTRUSIONPREVENTION_LOAD_AND_UNLOAD_DRIVERS,   // 操作系统中加载和卸载设备驱动程序的权利指派是否符合要求？
    HOST_INTRUSIONPREVENTION_USER_DISTRIBUTION_OF_POWER_BEGIN,      // 用户权限分配开始
    HOST_INTRUSIONPREVENTION_BACK_FILE=HOST_INTRUSIONPREVENTION_USER_DISTRIBUTION_OF_POWER_BEGIN,   //备份文件和目录
    HOST_INTRUSIONPREVENTION_CREATE_SYSLINK,                        //创建符号链接
    HOST_INTRUSIONPREVENTION_CREATE_GLOBE_OBJECT,                   //创建全局对象
    HOST_INTRUSIONPREVENTION_CREATE_TOKEN,                          //创建一个令牌对象
    HOST_INTRUSIONPREVENTION_CREATE_PAGE,                           //创建一个页面文件
    HOST_INTRUSIONPREVENTION_CREATE_SHARE_FOREVER,                  //创建永久共享对象
    HOST_INTRUSIONPREVENTION_REMOVE_PC_FROM_DOCKING_STATION,        //从扩展坞上取下计算机
    HOST_INTRUSIONPREVENTION_ACCESS_PC_FROM_NET,                    //从网络访问此计算机
    HOST_INTRUSIONPREVENTION_SHUTDOWN_FROM_REMOTE,                  //从远程系统强制关机
    HOST_INTRUSIONPREVENTION_CHANGE_TIMEZONE,                       //更改时区
    HOST_INTRUSIONPREVENTION_CHANGE_SYS_TIME,                       //更改系统时间
    HOST_INTRUSIONPREVENTION_SHUTDOWN_PC,                           //关闭系统
    HOST_INTRUSIONPREVENTION_MANAGE_AUDIT_AND_LOG,                  //管理审核和安全日志
    HOST_INTRUSIONPREVENTION_RESTORE_FILE_AND_DIR,                  //还原文件和目录
    HOST_INTRUSIONPREVENTION_LOAD_AND_UNLOAD_DRIVERS,               //加载和卸载设备驱动程序
    HOST_INTRUSIONPREVENTION_ADD_WORKSTATION_IN_DOMAIN,             //将工作站添加到域
    HOST_INTRUSIONPREVENTION_REFUSE_LOCAL_LOGON,                    //拒绝本地登录
    HOST_INTRUSIONPREVENTION_REFUSE_ACCESS_PC_FROM_NET,             //拒绝从网络访问这台计算机
    HOST_INTRUSIONPREVENTION_REFUSE_ACCESS_PC_FROM_REMOTE,          //拒绝通过远程桌面服务登录
    HOST_INTRUSIONPREVENTION_REFUSE_SERVICE_LOG,                    //拒绝以服务身份登录
    HOST_INTRUSIONPREVENTION_REFUSE_LOGIN_AS_A_BATCH_JOB,           //拒绝作为批处理作业登录
    HOST_INTRUSIONPREVENTION_CONFIG_FILE_IN_A_SINGLE_PROCESS,       //配置文件单一进程
    HOST_INTRUSIONPREVENTION_CONFIG_FILE_SYSTEM_PERFORMANCE,        //配置文件系统性能
    HOST_INTRUSIONPREVENTION_GET_FILE_OWNERSHIP,                    //取得文件或其他对象的所有权
    HOST_INTRUSIONPREVENTION_BYPASS_TRAVERSE_CHECKING,              //绕过遍历检查
    HOST_INTRUSIONPREVENTION_SIMULATE_CLIENT_AFTER_AUTHENTICATION,  //身份验证后模拟客户端
    HOST_INTRUSIONPREVENTION_CREATE_SAFE_AUDIT,                     //生成安全审核
    HOST_INTRUSIONPREVENTION_LOCKING_MEMORY_PAGES,                  //锁定内存页
    HOST_INTRUSIONPREVENTION_INCREASE_SCHEDULING_PRIORITY,          //提高计划优先级
    HOST_INTRUSIONPREVENTION_REPLACING_A_TOKEN_PROCESS_LEVEL,       //替换一个进程级令牌
    HOST_INTRUSIONPREVENTION_DEBUG_PROGRAM,                         //调试程序
    HOST_INTRUSIONPREVENTION_SYNCHRONOUS_DATA_DIRECTORY_SERVICE,    //同步目录服务数据
    HOST_INTRUSIONPREVENTION_ADJUST_PROCESS_MEM_ALLOCATION,         //为进程调整内存配额
    HOST_INTRUSIONPREVENTION_TRUST_PC,                              //信任计算机和用户帐户可以执行委派
    HOST_INTRUSIONPREVENTION_MODIFY_FIRMWARE_ENVIRONMENT_VALUE,     //修改固件环境值
    HOST_INTRUSIONPREVENTION_MODIFY_AN_OBJECT_TAG,                  //修改一个对象标签
    HOST_INTRUSIONPREVENTION_OPERATING_MODE,                        //以操作系统方式执行
    HOST_INTRUSIONPREVENTION_ALLOW_LOG_ON_LOCALLY,                  //允许本地登录
    HOST_INTRUSIONPREVENTION_ALLOW_LOGIN_VIA_REMOTE_DESKTOP_SERVICE,//允许通过远程桌面服务登录
    HOST_INTRUSIONPREVENTION_INCREASE_THE_PROCESS_WORKING_SET,      //增加进程工作集
    HOST_INTRUSIONPREVENTION_PERFORM_VOLUME_MAINTAIN,               //执行卷维护任务
    HOST_INTRUSIONPREVENTION_LOG_ON_AS_A_SERVICE,                   //作为服务登录
    HOST_INTRUSIONPREVENTION_AS_A_BATCH_JOB_TO_LOG_IN,              //作为批处理作业登录
    HOST_INTRUSIONPREVENTION_AS_TRUSTED_CALLER_ACCESS_CREDENTIAL_MANAGER,   //作为受信任的呼叫方访问凭据管理器
    HOST_INTRUSIONPREVENTION_USER_DISTRIBUTION_OF_POWER_END=HOST_INTRUSIONPREVENTION_AS_TRUSTED_CALLER_ACCESS_CREDENTIAL_MANAGER,      // 用户权限分配结束

    HOST_INTRUSIONPREVENTION_DISPLAY_LAST_LOGIN_NAME,   // 是否不显示上一次登陆的用户名？
    HOST_INTRUSIONPREVENTION_CLEAR_VIRTUAL_MEMORY_AT_SHUTDOWN,  // 是否启用关机时清除虚拟内存页面文件？
    HOST_INTRUSIONPREVENTION_CLOSE_DEFAULT_SHARE_DISKS, // 是否关闭默认共享盘？
    HOST_INTRUSIONPREVENTION_DISABLE_CREATE_DUMP,       // 是否禁止产生dump文件？
    HOST_INTRUSIONPREVENTION_DISABLE_REMOTE_REGISTRY,   // 是否禁用Remote Registry服务？
    HOST_INTRUSIONPREVENTION_DISABLE_MESSENGER,         // 是否禁用Messenger服务？
    HOST_INTRUSIONPREVENTION_DISABLE_CLIPBOOK,          // 是否禁用Clipbook服务？
    HOST_INTRUSIONPREVENTION_DISABLE_ALERTER,           // 是否禁用Alerter服务？
    HOST_INTRUSIONPREVENTION_DISABLE_TALK,              // 是否禁用talk服务？
    HOST_INTRUSIONPREVENTION_DISABLE_NTALK,             // 是否禁用ntalk服务？
    HOST_INTRUSIONPREVENTION_DISABLE_POP2,              // 是否禁用pop-2服务？
    HOST_INTRUSIONPREVENTION_DISABLE_SENDMAIN,          // 是否禁用sendmail服务？
    HOST_INTRUSIONPREVENTION_DISABLE_TASKSCHEDULER,     // 是否禁用Task Scheduler服务？
    HOST_INTRUSIONPREVENTION_DISABLE_PRINTSPOOLER,      // 是否禁用Print Spooler服务？
    HOST_INTRUSIONPREVENTION_DISABLE_TERMINALSERVICES,  // 是否禁用Terminal Services服务？
    HOST_INTRUSIONPREVENTION_DISABLE_TLNTSVR,           // 是否禁用Telnet服务？
    HOST_INTRUSIONPREVENTION_DISABLE_IISADMIN,          // 是否禁用IIS Admin Service服务？
    HOST_INTRUSIONPREVENTION_DISABLE_W3SVC,             // 是否禁用World Wide Web Publishing Service服务？
    HOST_INTRUSIONPREVENTION_DB_ATTACK_WITH_SQL_INJECTION,  // 是否能检测用户对数据库进行的SQL注入和缓冲区溢出攻击？

    // 恶意代码防范
    // 应安装防恶意代码软件，并及时更新防恶意代码软件版本和恶意代码库；
    HOST_MALWARE_INSTALL_PROTECT_PROGRAM_IN_WIN,            // Windows操作系统已安装恶意代码防范产品；
    HOST_MALWARE_INSTALL_PROTECT_PROGRAM_IN_LINUX,          // Linux或AIX操作系统已安装恶意代码防范产品；
    HOST_MALWARE_INSTALL_PROTECT_PROGRAM_UPDATE_VIR_LIB,    // 恶意代码防范产品的病毒库已及时更新。
    HOST_MALWARE_INSTALL_PROTECT_PROGRAM_VIR_DIFF,          // 主机恶意代码防范产品和网络恶意代码防范产品的恶意代码库名称和版本各不相同。
    HOST_MALWARE_INSTALL_PROTECT_PROGRAM_NO_VIR,            // 主机是否用病毒检查工具进行检查，且不存在病毒？
    HOST_MALWARE_INSTALL_PROTECT_PROGRAM_NO_TROJAN,         // 主机是否用木马检查工具进行检查，且不存在木马？

    // 资源控制
    // 应对主要服务器进行监视，包括监视服务器的CPU、硬盘、内存、网络等资源的使用情况。
    HOST_RESOURCE_MONITOR_SERVER_RESOURCE_USAGE,                // 已采取措施对操作系统的资源消耗（如CPU、内存、网络带宽资源）和其他信息进行实时监控和预警。
    HOST_RESOURCE_MONITOR_SERVER_IDLE_TIMEOUT,                  // 是否启用登录时间过期后断开与客户端的连接？
    HOST_RESOURCE_MONITOR_SERVER_CONFIG_TCPIP_DISABLE,          // 是否禁用TCP/IP高级配置服务？
    HOST_RESOURCE_MONITOR_SERVER_USER_REMOTE_CONNECT_DISABLE,   // 是否禁用更改所有用户远程访问连接的属性？
    HOST_RESOURCE_MONITOR_SERVER_LAN_CONNECT_DISABLE,           // 是否禁用LAN连接的能力？
    HOST_RESOURCE_MONITOR_SERVER_TIMEOUT_LOCK,                  // 是否启用登陆超时锁定？
    HOST_RESOURCE_MONITOR_SERVER_LOG_ACCESS_PRIVILEGE,          // 日志访问权限是否符合要求？


    // 网络安全
    // 结构安全
    // 应绘制与当前运行情况相符的网络拓扑结构图，并根据各网段重要性划分不同的子网或网段；
    NET_STRUCTURESAFETY_VLAN_TOPOLOGY,          // 有能反映系统当前状况的网络整体拓扑图；
    NET_STRUCTURESAFETY_VLAN_SUBNET,            // 是否根据各网段重要性划分不同的子网或网段。
    // 且重要网段与其他网段之间应采取可靠的技术隔离手段。
    NET_STRUCTURESAFETY_QUARANTINE_TECHNOLOGY,  // 重要网段与其他网段之间有技术隔离措施。

    // 访问控制
    // 应在网络边界部署访问控制设备，启用访问控制功能，且访问控制功能应根据会话状态信息为数据流提供明确的允许/拒绝访问的能力，控制粒度应为端口级；
    NET_ACL_ENABLE_BOUNDARY_PROTECTION,         // 网络边界有防火墙、网闸等安全设备对系统的边界进行防护，并启动访问控制功能；
    NET_ACL_ENABLE_QUARANTINE,                  // 核心区域边界采用访问控制措施与其他区域进行有效隔离；
    NET_ACL_ENABLE_GRANULAR_CTL,                // 访问控制粒度控制到端口级，且配置默认拒绝策略。
    // 重要网段应采取技术手段防止地址欺骗。
    NET_ACL_ARP_CHEAT,                          // 采取地址绑定（如IP/MAC、端口）等手段防止重要网段的地址欺骗。
    // 应不开放远程拨号访问功能。
    NET_ACL_DIAL_DISABLE,                       // 已关闭远程拨号访问功能；

    // 安全审计
    // 应对审计记录进行保护，避免受到未预期的删除、修改或覆盖等。
    NET_SAFEAUDIT_LOGPROTECT_LOGINFO,           // 设备可以对审计记录进行备份保存，日志信息循环覆盖；
    NET_SAFEAUDIT_LOGPROTECT_BUFSIZE,           // 设备能合理配置日志缓冲区大小；
    NET_SAFEAUDIT_LOGPROTECT_LOGSERVER,         // 已部署设备日志集中管理系统（如Syslog服务器）。
    // 应对网络系统中的网络设备运行状况、网络流量、用户行为等进行日志记录，并能够根据记录数据进行分析，并生成审计报表；
    NET_SAFEAUDIT_STATUS_AUDITLOG,              // 设备有审计记录
    NET_SAFEAUDIT_STATUS_RUNNING,               // 能对设备运行状况、网络流量、用户行为进行审计；
    NET_SAFEAUDIT_STATUS_AUDITREPORT,           // 设备运维过程中能生成审计报表。
    NET_SAFEAUDIT_STATUS_ENABLE_LOGSERVER,      // 路由器、核心交换机是否开启日志服务？
    NET_SAFEAUDIT_STATUS_ENABLE_TIMESTAMP,      // 路由器、核心交换机是否开启日志时间戳服务？
    NET_SAFEAUDIT_STATUS_ENABLE_LOG,            // 防火墙是否开启日志审计？
    NET_SAFEAUDIT_STATUS_RECORD_LOGIN_USER,     // 防火墙日志是否对用户登录使用的帐号进行记录？
    NET_SAFEAUDIT_STATUS_RECORD_LOGIN_RESULT,   // 防火墙日志是否记录用户登录是否成功？
    NET_SAFEAUDIT_STATUS_RECORD_LOGIN_TIME,     // 防火墙日志是否对用户登录时间进行记录？
    NET_SAFEAUDIT_STATUS_RECORD_LOGIN_IP,       // 远程登录时，防火墙日志是否对用户登录的IP地址进行记录？
    NET_SAFEAUDIT_STATUS_RECORD_MODIFY_PWD,     // 防火墙日志是否记录口令修改的操作？
    NET_SAFEAUDIT_STATUS_RECORD_RW_CONFIG,      // 防火墙日志是否记录读取和修改设备配置的操作？
    NET_SAFEAUDIT_STATUS_ENABLE_NAT,            // 防火墙是否开启记录NAT日志，记录转换前后IP地址的对应关系？
    NET_SAFEAUDIT_STATUS_ENABLE_VPN,            // 防火墙是否开启记录VPN日志，记录VPN访问登陆、退出等信息？
    NET_SAFEAUDIT_STATUS_ENABLE_FLUX,           // 防火墙是否配置记录流量日志，记录通过防火墙的网络连接的信息？
    NET_SAFEAUDIT_STATUS_ENABLE_FIREWALL_RULE,  // 是否配置防火墙规则，记录防火墙拒绝和丢弃报文的日志？
    NET_SAFEAUDIT_STATUS_LOG_ALARM_THRSHOLD,    // 防火墙是否配置日志容量告警阈值，在日志数达到一定的日志容量时产生告警？
    NET_SAFEAUDIT_STATUS_RECORD_ROOT_OPERATE,   // 防火墙是否配置记录管理员操作日志，如管理员登录，修改管理员组操作，帐号解锁等信息？
    NET_SAFEAUDIT_STATUS_LOG_SEND,              // 是否配置防火墙，将相关的操作日志送往操作日志审计系统或者其他相关的安全管控系统？
    NET_SAFEAUDIT_STATUS_FIREWALLALARM_SYS_ERROR,   // 是否配置防火墙告警功能，报告对防火墙本身的攻击或者防火墙的系统内部错误？
    NET_SAFEAUDIT_STATUS_FIREWALLALARM_TCP_ATTACK,  // 是否配置防火墙告警功能，报告网络流量中对TCP/IP协议网络层异常报文攻击的相关告警？
    NET_SAFEAUDIT_STATUS_FIREWALLALARM_DOS,         // 防火墙是否配置对DOS和DDOS攻击告警？
    NET_SAFEAUDIT_STATUS_FIREWALLALARM_HOST_SCAN,   // 防火墙是否配置扫描攻击检测功能，对网络和主机扫描探测行为告警？
    // 应定义审计跟踪极限的阈值，当存储空间接近极限时，能采取必要的措施，当存储空间被耗尽时，终止可审计事件的发生；应实现集中审计，时钟保持与时钟服务器同步。
    NET_SAFEAUDIT_LIMITMEMORY_AUDIT_THRESHOLD,      // 审计设置是否定义了审计极限的阈值，当存储空间被耗尽时，是否能够采取必要的保护措施，例如报警并导出、丢弃未记录的审计信息、暂停审计或覆盖以前的审计记录等。
    NET_SAFEAUDIT_LIMITMEMORY_CLOCK_SYN,            // 检查边界和主要网络设备时钟是否与时钟服务器同步？

    // 边界完整性检查
    // 应能够对非授权设备私自联到内部网络和内部网络用户私自联到外部网络的行为进行检查，准确定出位置，并对其进行有效阻断。
    NET_COMPLETEBOUNDARY_NETACCESS_CHECK_INTERNET,  // 具有安全措施能检查、定位、报警并阻断内部用户私自通过无线网卡或其他网口等连接外网；
    NET_COMPLETEBOUNDARY_NETACCESS_DISABLE_PORT,    // 采用终端端口禁用的方法防止用户私自外联；
    NET_COMPLETEBOUNDARY_NETACCESS_SOFTWARE_CONTROL,// 采用终端管理软件实现私自外联管理；
    NET_COMPLETEBOUNDARY_NETACCESS_FIREWALL_CONTENT_FILITER,    // 防火墙是否配置关键字内容过滤功能，在HTTP，SMTP，POP3等应用协议流量过滤包含有设定的关键字的报文？
    NET_COMPLETEBOUNDARY_NETACCESS_FIREWALL_VIRUS_DEFENSE,      // 防火墙是否配置病毒防护选项，对蠕虫等病毒传播时的攻击流量进行过滤？
    NET_COMPLETEBOUNDARY_NETACCESS_FIREWALL_LAST_ACL,           // 防火墙在配置访问规则列表时，最后一条是否是拒绝一切流量？
    NET_COMPLETEBOUNDARY_NETACCESS_ACL_LIMIT_RANGE,             // 在配置访问规则时，源地址，目的地址，服务或端口的范围是否以实际访问需求为前提，尽可能的缩小范围？
    NET_COMPLETEBOUNDARY_NETACCESS_NAT_SWITCH_HIDE_INTRANET,    // 配置NAT地址转换，防火墙是否对互联网隐藏内网主机的实际地址？
    NET_COMPLETEBOUNDARY_NETACCESS_MAC_BIND,                    // 对于防火墙各逻辑接口，是否配置开启防源地址欺骗功能（例如，MAC地址绑定）？
    NET_COMPLETEBOUNDARY_NETACCESS_ENABLE_ACL,                  // 是否启用访问控制列表？
    NET_COMPLETEBOUNDARY_NETACCESS_ENABLE_8021X,                // 是否开启802.1x全局控制功能？
    NET_COMPLETEBOUNDARY_NETACCESS_ENABLE_DEFAULT_ROUTE,        // 是否开启默认路由？
    NET_COMPLETEBOUNDARY_NETACCESS_ENABLE_SYS_NOTE,             // 是否开启系统启动注释？

    // 入侵防范
    // 应在网络边界处监视以下攻击行为：端口扫描、强力攻击、木马后门攻击、拒绝服务攻击、缓冲区溢出攻击、IP碎片攻击和网络蠕虫攻击等，并在检测到攻击时，应针对严重入侵事件进行报警。
    NET_INTRUSIONPREVENTION_ATTACK_IDS_DEPLOY,          // 已部署入侵检测类安全产品（IDS）；
    NET_INTRUSIONPREVENTION_ATTACK_IDS_UPDATE,          // 入侵检测类安全产品（IDS）的特征库已及时更新升级；
    NET_INTRUSIONPREVENTION_ATTACK_ALARM_CONFIG,        // 报警方式包括邮件、短信或声音且报警的目的邮箱或手机设置正确。
    NET_INTRUSIONPREVENTION_ATTACK_DISABLE_HTTP,        // 是否关闭HTTP服务？
    NET_INTRUSIONPREVENTION_ATTACK_DISABLE_TCPSMALL,    // 是否关闭tcp-small服务？
    NET_INTRUSIONPREVENTION_ATTACK_DISABLE_UDPSMALL,    // 是否关闭udp-small服务？
    NET_INTRUSIONPREVENTION_ATTACK_DISABLE_FINGER,      // 是否关闭Finger服务？
    NET_INTRUSIONPREVENTION_ATTACK_DISABLE_BOOTS,       // 是否关闭Boots服务？
    NET_INTRUSIONPREVENTION_ATTACK_DISABLE_PROXY_ARP,   // 是否关闭代理ARP服务？
    NET_INTRUSIONPREVENTION_ATTACK_DISABLE_GARP,        // 是否关闭无故ARP服务？
    NET_INTRUSIONPREVENTION_ATTACK_DISABLE_DNS,         // 是否关闭DNS查询服务？
    NET_INTRUSIONPREVENTION_ATTACK_DISABLE_PING,        // 对于外网口地址，防火墙是否关闭对ping包的回应？
    NET_INTRUSIONPREVENTION_ATTACK_FIREWALL_VER,        // 查看防火墙的版本号和升级时间。
    NET_INTRUSIONPREVENTION_ATTACK_SNMP_GTE_3,          // 是否使用SNMP V3以上的版本对防火墙做远程管理？
    NET_INTRUSIONPREVENTION_ATTACK_LIMIT_MANAGE_PC,     // 是否对防火墙的管理地址做源地址限制（例如，使用防火墙自身的限定功能，或在防火墙管理口的接入设备上设置ACL）？

    // 恶意代码防范
    // 应在网络边界处对恶意代码进行检测和清除。
    NET_MALICIOUSCODE_KILL_DEPLOY_UTM,          // 在边界部署有网络防恶意代码产品（网络防毒墙、UTM的病毒检测模块等）；
    NET_MALICIOUSCODE_KILL_VIRUS_LATEST_LIB,    // 网络防恶意代码产品的病毒库已及时更新升级（至少每周升级一次）。

    // 网络设备防护
    // 应对登录网络设备的用户进行身份鉴别，且对同一用户应选择两种或两种以上组合的鉴别技术来进行身份鉴别，身份鉴别信息应具有不易被冒用的特点，口令应有复杂度要求并定期更换；
    NET_PROTECTION_IDAUDIT_COMBINATION_IDENTIFY,        // 核心交换机、路由器和重要防火墙等网络设备采取两种或两种以上组合鉴别技术（证书、用户名/口令、动态令牌和生物特性等均可作为一种鉴别技术，两种鉴别技术需作为前后两道认证机制，而不是通过用户名/口令或证书均可完成认证）；
    NET_PROTECTION_IDAUDIT_SECURITY_POLICY,             // 设备有限制口令最小长度、复杂度和更新时间等安全策略
    NET_PROTECTION_IDAUDIT_PWD_STORE_ENCRYPTE,          // 设备的口令列表采用加密保存的方式。
    NET_PROTECTION_IDAUDIT_ENABLE_PWD_ENCRYPTE,         // 路由器、核心交换机是否开启密码加密服务？
    NET_PROTECTION_IDAUDIT_ENABLE_TACACS,               // 是否开启TACACS服务器？
    NET_PROTECTION_IDAUDIT_ENABLE_RADIUS,               // 是否开启Radius服务器？
    NET_PROTECTION_IDAUDIT_ENABLE_LOGIN_PWD,            // 是否启用登陆密码？
    NET_PROTECTION_IDAUDIT_ENABLE_SSH_LOGIN,            // 是否启用SSH登陆？
    NET_PROTECTION_IDAUDIT_DISABLE_PAD,                 // 是否关闭PAD（Packet assembler/Disassembly）设置？
    NET_PROTECTION_IDAUDIT_ENABLE_PRIVILEGE_PWD,        // 是否开启特权密码？
    NET_PROTECTION_IDAUDIT_ENABLE_AAA,                  // 是否启用AAA认证？
    NET_PROTECTION_IDAUDIT_USER_NO_NEED,                // 是否没有test等与工作无关的账户？
    NET_PROTECTION_IDAUDIT_FIREWALL_PWD_LEN,            // 防火墙口令的密码长度是否符合要求？
    NET_PROTECTION_IDAUDIT_FIREWALL_PWD_AGEING_TIME,    // 防火墙的口令生存期是否符合要求？
    NET_PROTECTION_IDAUDIT_FIREWALL_LOGIN_FAIL_NUM,     // 防火墙口令的被锁定的登录失败的次数是否符合要求？
    NET_PROTECTION_IDAUDIT_USE_VLAN,                    // 是否启用VLAN管理域（VTP域）？
    // 当对网络设备进行远程管理时，应采取必要措施防止鉴别信息在网络传输过程中被窃听。
    NET_PROTECTION_CIPHERTEXT_USE_HTTPS_SSH_SUPERVISORY_UNIT,   // 设备管理时采用SSH或HTTPS等加密协议。
    NET_PROTECTION_CIPHERTEXT_USE_SSH_MAINTAIN,                 // 是否采用SSH等加密协议对防火墙进行远程维护？
    NET_PROTECTION_CIPHERTEXT_FIREWALL_IDLE_TIMEOUT,            // 防火墙账户的超时锁定是否符合要求？
    NET_PROTECTION_CIPHERTEXT_FIREWALL_ENABLE_CONSOLE_PWD,      // 防火墙的consol口密码保护功能是否启用？
    // 网络设备用户的身份鉴别信息至少应有一种是不可伪造的；
    NET_PROTECTION_IDFORGE_BIOLOGICAL_FEATURE_USE_BIONT_IDENTIFY,   //鉴别技术中至少采用一种生物特征鉴别技术。

    HOST_UNKNOWN_SUBCHECK_ITEM,                                 // 未知的检查项

}HOST_CHECK_ITEM_TYPE, *LPHOST_CHECK_ITEM_TYPE;

typedef union _CHECK_ITEM_TYPE
{
    DtModuleE                       tCheckModule;
    HOST_SECURITY_CHECK_TYPE        tCheckHostSub;
    NETWORK_EQUIPMENT_CHECK_TYPE    tCheckNetSub;
    HOST_CHECK_ITEM_TYPE            tCheckHostItem;
}CHECK_ITEM_TYPE, *LPCHECK_ITEM_TYPE;

typedef struct _DJJC_CHECK_SUB_ITEM_INFO
{
    // CHECK_ITEM_TYPE      tCheckItemType;
    // DWORD   tCheckItemType;
    HOST_SECURITY_CHECK_TYPE    tCheckItemType;
    CHAR                        szItemDescribe[300];
}DJJC_CHECK_SUB_ITEM_INFO, *LPDJJC_CHECK_SUB_ITEM_INFO ;

typedef struct _DJJC_CHECK_SUB_ITEM_KIND_INFO
{
    HOST_SECURITY_CHECK_SUB_TYPE    tCheckItemType;
    CHAR                            szItemDescribe[300];
}DJJC_CHECK_SUB_ITEM_KIND_INFO, *LPDJJC_CHECK_SUB_ITEM_KIND_INFO ;

typedef struct _DJJC_CHECK_ITEM_INFO
{
    // CHECK_ITEM_TYPE      tCheckItemType;
    // DWORD   tCheckItemType;
    // HOST_SECURITY_CHECK_TYPE    tCheckItemType;
    HOST_CHECK_ITEM_TYPE        tCheckItemType;
    CHAR                        szItemDescribe[300];
}DJJC_CHECK_ITEM_INFO, *LPDJJC_CHECK_ITEM_INFO ;


//标准结构定义
typedef struct DT_STANDARD_IDX_T
{
    INT32	nIdx;				//自1开始的序号
    INT32	nLevel;				//对应的检查等级 （1-2级 2-3级 4-4级 0x0f-所有等级
    INT32	nModule;			//对应的安全类别-用于快速匹配用, 暂未用
    INT32	nType;				//类型，用户后续的扩充分类, 暂未用
    char	strStdCode[16];		//对应的标准号	"7.1.3.1-a)"
    char	strDesc[256];		//对应的标准描述
    char	strReserved[128];	//备注
}DtStandardIdx;

typedef union _RESOURCE_CHECK_TYPE
{
    NETWORK_EQUIPMENT_CHECK_TYPE    netCheckType;
    HOST_SECURITY_CHECK_TYPE        hostCheckType;
    UINT32   ui32Other;
}RESOURCE_CHECK_TYPE, *LPRESOURCE_CHECK_TYPE;

typedef struct  _CHECK_POINT_GUID
{
    char    szGuid[64]; // 等级检查项标识符
}CHECK_POINT_GUID, *LPCHECK_POINT_GUID;

typedef struct _DJJC_CHECK_RESOURCE_INFO
{
    DtModuleE               eCheckModule;
    // RESOURCE_CHECK_TYPE     tResourceCheckType;
    // DWORD                   tResourceCheckType;
    HOST_SECURITY_CHECK_TYPE        tResourceCheckType;
    HOST_SECURITY_CHECK_SUB_TYPE    tResourceCheckSubType;
    HOST_CHECK_ITEM_TYPE    tCheckItemType;
    DWORD                   dwCheckLevel;
    CHECK_POINT_GUID        tCheckGuid[4];
}DJJC_CHECK_RESOURCE_INFO, *LPDJJC_CHECK_RESOURCE_INFO;

typedef struct _CHECK_RESULT_GUID
{
    BOOL    bValid;                 // 是否有效
    INT32	nResult;			    // 判定值- 0-无效 1-符合、2-不符合、4-部分符合8-人工判断
    CHECK_POINT_GUID    tCheckGuid; // 唯一标识符
    char	strComment[512];	    // 参考的标准建议
}CHECK_RESULT_GUID, *LPCHECK_RESULT_GUID;

enum    E_CHECK_RESULT
{
    //判定值- 0-无效 1-符合、2-不符合、4-部分符合8-人工判断
    E_CHECK_RESULT_INVALID          = 0,    // 无效
    E_CHECK_RESULT_CONFORMITY       = 1,    // 符合
    E_CHECK_RESULT_NON_CONFORMITY   = 2,    // 不符合
    E_CHECK_RESULT_PARTIAL_MATCH    = 4,    // 部分符合
    E_CHECK_RESULT_MANUAL_JUDGMENT  = 8,    // 自行判断
};

//统一的检查结果定义
typedef struct DTCK_RESULT_T
{
    INT32	nResult;			//判定值- 0-无效 1-符合、2-不符合、4-部分符合8-人工判断
    INT32	nStdIdx;			//对应的标准号整数索引
    INT32	nModule;			//所属的模块-用于分类显示
    INT32	nRiskLvl;			//风险级别或者重要性程度
    void *	pExtension;			//扩展指针,留待后用,防止成员扩充修改结构
    char	strStdCode[16];		//对应的标准号
    char	strCkPoint[128];	//本检查点的描述
    char	strResult[128];		//检查结果描述
    char	strZhengai[128];	//整改建议-如果有的话,没有的话直接参考标准建议
    char	strComment[512];	//参考的标准建议
    char	strBeizhu[128];		//备注

    // 以下用于二级标准
    INT32	nResult2;			//判定值- 0-无效 1-符合、2-不符合、4-部分符合8-人工判断
    char	strComment2[512];	//参考的标准建议
    HOST_CHECK_ITEM_TYPE    tCheckItemType;
    CHECK_RESULT_GUID   tCheckResultGuid[4];

    ECheckControlPoint      eCheckPoint;
    ECheckControlPointItem  eCheckPointItem;

    HOST_SECURITY_CHECK_TYPE        tResourceCheckType;     // 仅在tCheckItemType为HOST_UNKNOWN_SUBCHECK_ITEM时有效
    HOST_SECURITY_CHECK_SUB_TYPE    tResourceCheckSubType;  // 仅在tCheckItemType为HOST_UNKNOWN_SUBCHECK_ITEM时有效

    char    option[1024];
    char    policy_number[32];
    char    option_number[32];
}DtckResult;

typedef struct DTCK_RESULTS_T
{
    DtckResult      result;
    DTCK_RESULTS_T* pNext;
    DTCK_RESULTS_T()
    {
        ZeroMemory(&result, sizeof(result));
        pNext = NULL;
    }
}DtckResults;

//以下为服务端任务的存储结构

typedef struct DTCK_RESULTSSERVER_T
{
    DtckResults      result;
    DTCK_RESULTSSERVER_T* pNext;
    DTCK_RESULTSSERVER_T()
    {
        ZeroMemory(&result, sizeof(result));
        pNext = NULL;
    }
}DtckResultsServer;

enum E_AUDIT_POLICY
{
    AUDIT_POLICY_NOAUDIT,
    AUDIT_POLICY_SUCCESSED,
    AUDIT_POLICY_FAILED,
    AUDIT_POLICY_ALL,
    AUDIT_POLICY_NUM,
};

// [Event Audit]
// AuditSystemEvents = 3
// AuditLogonEvents = 2
// AuditObjectAccess = 1
// AuditPrivilegeUse = 1
// AuditPolicyChange = 0
// AuditAccountManage = 3
// AuditProcessTracking = 2
// AuditDSAccess = 0
// AuditAccountLogon = 0
typedef struct T_AuditPolicy
{
    char szEngName[32];
    //char szName[32];
    HOST_CHECK_ITEM_TYPE    eCkItemType;
    E_AUDIT_POLICY  eAuditPolicy;
    char *pszResult;
    char szItemDes[32];
}AuditPolicy;

typedef struct T_SystemAccess
{
    char szEngName[32];
    union
    {
        int iValue;
        char szValue[128];
    }unValue;
}SystemAccess;

#define OSVERSION_LENGTH  1024
#define USERNAME_LENGTH   100
#define USERGROUP_LENGTH  100
typedef struct _OSVERSIONINFO{
    char systemName[OSVERSION_LENGTH];  //系统名称
    char buildNumber[OSVERSION_LENGTH];  //系统构建号
    char majorVersion[OSVERSION_LENGTH]; //系统主版本号
    char MinorVersion[OSVERSION_LENGTH]; //系统次版本号
    char PlatformId[OSVERSION_LENGTH];   //系统支持平台
    char CSDVersion[OSVERSION_LENGTH]; //系统支持平台
}OsVersionInfo, *MPOSVERSIONINFO;


#define MAX_KEY_LENGTH      255
#define MAX_VALUE_LENGTH    16383 //16,383 characters for a name (260 ANSI)
typedef struct  T_USBHISTORY
{
    CHAR    caSerialNumber[64];     // USB\VID_XXXX&PID_YYYY\XXXYYYZZZ
    CHAR    caUsbPath[MAX_KEY_LENGTH+1];         // USB\VID_XXXX&PID_YYYY\XXXYYYZZZ
    DWORD   dwCapabilities;         //
    CHAR    caClass[32];            // 类型 USB|WPD|HIDClass
    CHAR    caClassGUID[64];        // 对应HKLM\System\CurrentControlSet\Control\Class\{36fc9e60-c465-11cf-8056-444553540000}
    CHAR    caCompatibleIDs[128];   //
    DWORD   dwConfigFlags;          //
    CHAR    caContainerID[64];      // {c4c2c7f6-6558-59d9-8e6d-6e3501f2a94e}，若Service为USBSTOR，则对应USBSTOR中的ContainerID
    CHAR    caDeviceDesc[64];       // USB 大容量存储设备|USB 输入设备SAMSUNG_Android
    CHAR    caDriver[64];           // 对应HKLM\System\CurrentControlSet\Control\Class\{36fc9e60-c465-11cf-8056-444553540000}\0019
    CHAR    caHardwareID[64];       //
    CHAR    caLocationInformation[64];  //
    CHAR    caMfg[64];              // 兼容USB存储设备|标准系统设备|标准USB主控制器
    CHAR    caService[16];          // USBSTOR|HidUsb|usbccgp|WUDFRd|VBoxUSB
    CHAR    caCreateTime[32];       // 首次使用时间
    CHAR    caUpdateTime[32];       // 最近使用时间
    T_USBHISTORY    *pNext;

    T_USBHISTORY()
    {
        ZeroMemory(caSerialNumber, sizeof(T_USBHISTORY));
    }
}USBHISTORY, *PUSBHISTORY;


#define		LENGTH		1024
typedef struct IEVISITHISTORY{
    CHAR IeTitle[LENGTH];
    CHAR IeUrl[LENGTH];
    CHAR visitTime[LENGTH];
    IEVISITHISTORY   *pNext;
    IEVISITHISTORY()
    {
        ZeroMemory(IeTitle, sizeof(IEVISITHISTORY));
    }
}IeVisitHistory, *PIEVISITHISTORY;

typedef struct FIREFOXHISTORY{
    char fireFoxTitle[LENGTH];
    char fireFoxUrl[LENGTH];
    char fireFoxVisitTime[LENGTH];
    FIREFOXHISTORY *pNext;
    FIREFOXHISTORY()
    {
        ZeroMemory(fireFoxTitle, sizeof(FIREFOXHISTORY));
    }
}FireFoxHistory, *PFIREFOXHISTORY;

typedef struct CHROMEHISTORY{
    char chromeTitle[LENGTH];
    char chromeUrl[LENGTH];
    char chromeVisitTime[LENGTH];
    CHROMEHISTORY *pNext;
    CHROMEHISTORY()
    {
        ZeroMemory(chromeTitle, sizeof(CHROMEHISTORY));
    }
}ChromeHistory, *PCHROMEHISTORY;

typedef struct SYSTEMDEFECTINFO{
    char defectName[LENGTH];
    char defectNum[LENGTH];
    char defectDate[LENGTH];
    char strPubdate[64];
    int  patchLevel;
    SYSTEMDEFECTINFO *pNext;
    SYSTEMDEFECTINFO()
    {
        ZeroMemory(defectName, sizeof(SYSTEMDEFECTINFO));
    }
}SystemDefectInfo, *PSYSTEMDEFECTINFO;

typedef struct RUNITEMS{
    char name[LENGTH];
    char path[LENGTH];
    char szRunType[16];
    RUNITEMS *pNext;
    RUNITEMS()
    {
        ZeroMemory(&name, sizeof(RUNITEMS));
        strcpy(szRunType, "注册表");
    }
}RunItems, *PRUNITEMS;

struct CBuffer
{
    DWORD   dwBuflen;
    DWORD   dwBufSize;
    char    *pBuf;

    CBuffer()
    {
        dwBufSize   = 0x10000+2; // 注册表二进制最大值为0x10000
        dwBuflen    = dwBufSize;
        pBuf = new char[dwBuflen];
    }

    ~CBuffer()
    {
        dwBuflen    = 0;
        dwBufSize   = 0;

        if (NULL != pBuf)
        {
            delete[] pBuf;
        }
    }
};


namespace   gropu_policy
{
    typedef struct T_DB_GROUP_POLICY_KEY
    {
        DWORD dwType;               // Key的类型
        char  szKeyName[128];       // 键名
        char  szKeyValue[256];      // 键值
        //DWORD dwKeyValueLen;        // 键值长度
        //char  szKeyEnableValue[256];// 启用的值
        char  szKeyRealValue[256];  // 键的实际值
    }DbGroupPolicyKey;

    typedef struct T_DB_GROUP_POLICY_KEYS
    {
        int iEnableNum;
        int iDisableNum;
        DbGroupPolicyKey    gpEnableKey[4];
        DbGroupPolicyKey    pgDisableKey[4];
    }DbGroupPolicyKeys;

    typedef struct T_DB_GROUP_POLICY
    {
        char szPolicyName[256];     //
        char szKeyPath[256];        // Key的路径
        DWORD dwResult;             // 0是未配置，1是启用，2是禁用
        DbGroupPolicyKeys   gpKeys;
    }DbGroupPolicy;
}

typedef struct  user_rights_assignment_tag{
    char userright[LENGTH];     // 英文名
    char policy[LENGTH];        // 中文策略名
    char option[LENGTH];        // 结果
    char policy_number[LENGTH]; // ID
    char option_number[LENGTH]; // 检查结果
    char transResult[LENGTH];   // 转换后的结果
}user_rights_assignment_t;

typedef struct  T_USER_INFO
{
    LPUSER_INFO_2 pUserInfo;
    DWORD dwNum;
}USER_INFO, *PUSER_INFO;

typedef struct  T_SHARE_INFO
{
    PSHARE_INFO_502 pShareInfo;
    DWORD dwNum;
}SHARE_INFO, *PSHARE_INFO;

#define SERVICE_STATT_TYPE_NUM            5
typedef struct  T_SERVICES_STATUS_INFO1
{
    ENUM_SERVICE_STATUS_PROCESSA serviceStatusInfo;
    QUERY_SERVICE_CONFIGA       serviceConfig;
}SERVICE_STATUS_INFO1, *LPSERVICE_STATUS_INFO1;
typedef struct  T_SERVICES_STATUS_INFO
{
    LPENUM_SERVICE_STATUS_PROCESSA pServiceStatusInfo;
    LPDWORD pdwConfig;
    DWORD dwNum;
}SERVICE_STATUS_INFO, *LPSERVICE_STATUS_INFO;

typedef struct _SOFTWAREINFO{
    char m_displayname[LENGTH]; //软件名称
    char m_displayversion[LENGTH];//软件版本
    char m_uninstall[LENGTH];//软件卸载
    char m_displaytime[LENGTH];//软件安装时间	
    char szInstallLocation[LENGTH];   // 安装路径
    DWORD m_displaynamelen;
    DWORD m_displayversionlen;
    DWORD m_uninstalllen;
    DWORD m_displaytimelen;
    DWORD m_iInstallLocationlen;
    int   iSoftType;        // 软件类型
    char  szSoftType[32];   // 软件类型描述

    _SOFTWAREINFO()
    {
        ZeroMemory(m_displayname, sizeof(_SOFTWAREINFO));
        iSoftType = 26;
        strcpy(szSoftType, "其他");
    }
}SoftwareInfo, *PSOFTWAREINFO;

typedef struct _PROCESSINFO{
    DWORD processid;//进程ID
    char proName[LENGTH];//进程名称
    char path[MAX_PATH];//进程路径
}ProcessInfo, *PPROCESSINFO;

// 反病毒软件
enum    eVirusType
{
    VIRUS_TYPE_BEGIN,                   //
    VIRUS_TYPE_RAV,                     // 瑞星杀毒
    VIRUS_TYPE_RFW,                     // 瑞星防火墙
    VIRUS_TYPE_KINGSOFT_ANTIVIRUS,      // 金山杀毒
    VIRUS_TYPE_KINGSOFT_ENTERPRISE,     // 金山企业版
    VIRUS_TYPE_360_ANTIVIRUS,           // 360杀毒
    VIRUS_TYPE_BAIDU,                   // 百度杀毒
    VIRUS_TYPE_JIANGMIN,                // 江民
    VIRUS_TYPE_ZHXXWFBD,                // 江民的另一个版本，综合信息网防病毒
    VIRUS_TYPE_JIANGMIN_NET,            // 江民网络版
    VIRUS_TYPE_KASPERSKY,               // 卡巴斯基
    VIRUS_TYPE_KASPERSKY_ENTERPRISE,    // 卡巴斯基企业版
    VIRUS_TYPE_MCAFEE,                  // Mcafee迈克菲
    VIRUS_TYPE_AVIRA,                   // 小红伞
    VIRUS_TYPE_AVIRA_ENTERPRISE,        // 小红伞企业版
    VIRUS_TYPE_END,                     //
    VIRUS_TYPE_UNKNOWN,                 // 未知类型
};

typedef struct  AntivirusSoft
{
    eVirusType  eVt;                // 病毒类型
    char   szDisplayName[128];      // 软件名(对应卸载中的DisplayName)
    char   szExeAlias[512];         // 查找的软件名列表别名，以|分割，比如  金山毒霸|新毒霸|毒霸|金山企业版
    char   szExeName[64];           // exe名称
    char   szConfigPath[128];       // 相对于exe的路径
    char   szAppName[128];          // 配置文件
    char   szKeyName[128];          // 配置文件
    BOOL   bString;                 // TRUE是string；FALSE是整形
    char   szRunStatus[16];         // 运行状态
    char   szUpdateTime[64];        // 病毒库更新时间
    char   szVersion[64];           // 软件版本
    char   szUninstallString[512];  // exe全路径

    //     AntivirusSoft()
    //     {
    //         eVt = VIRUS_TYPE_UNKNOWN;
    //         szDisplayName[0]     = 0;
    //         szExeName[0]         = 0;
    //         szConfigPath[0]      = 0;
    //         szAppName[0]         = 0;
    //         szKeyName[0]         = 0;
    //         bString              = TRUE;
    //         szRunStatus[0]       = 0;
    //         szUpdateTime[0]      = 0;
    //         szVersion[0]         = 0;
    //         szUninstallString[0] = 0;
    //     }
}AntivirusSoft;
// 反病毒软件
typedef struct ANTIVIRUSPRODUCT{
    char antivirusName[LENGTH];
    char antivirusState[LENGTH];
    char antivirusVersion[LENGTH];
    ANTIVIRUSPRODUCT *pNext;
    ANTIVIRUSPRODUCT()
    {
        ZeroMemory(antivirusName, sizeof(ANTIVIRUSPRODUCT));
    }
}AntivirusProduct, *PANTIVIRUSPRODUCT;

typedef struct _BIOSINFO{
    char name[LENGTH];//名称
    char parameterValue[LENGTH];
    char brand[LENGTH];//主板品牌
    char factoryNumber[LENGTH];//出厂编号
    char model[LENGTH];//型号
    char time[LENGTH];
    char softSetting[LENGTH];
}BiosInfo;

typedef struct _LOGICALDRIVESINFO{
    char name[LENGTH];
    char DriverBuffer[LENGTH];
    //char parameterValue[LENGTH];
    char brand[LENGTH];//品牌
    char factoryNumber[LENGTH];//出厂编号
    char model[LENGTH];//型号
    char time[LENGTH];
    char softSetting[LENGTH];

    char size[LENGTH];
    char description[LENGTH];
    UINT64 captacity;
}LogicalDrivesInfo,*PLOGICALDRIVESINFO;

typedef struct  _ACCOUNTRIGHTS
{
    char strAccount[1024];
    int  arrRights[32];
    bool valid;
    _ACCOUNTRIGHTS *pNext;
    _ACCOUNTRIGHTS()
    {
        ZeroMemory(strAccount, sizeof(_ACCOUNTRIGHTS));
    }
}AccountRights, *PACCOUNTRIGHTS;

typedef struct _DEIVESACCOUNTRIGHTS
{
    char strDriveName[LENGTH];
    AccountRights *pAccountRt;
}DrivesAccountRights, *PDEIVESACCOUNTRIGHTS;

typedef struct _CPUINFO{
    char name[LENGTH];//名称
    char parameterValue[LENGTH];
    char brand[LENGTH];//主板品牌
    char factoryNumber[LENGTH];//出厂编号
    char model[LENGTH];//型号
    char time[LENGTH];
    char softSetting[LENGTH];
    DWORD   dwNumberOfProcessors;   // 核数
    DWORD   dwNumberOfCpu;          // CPU数
}CpuInfo, _PCPUINFO;

#define HARDDISK_LENGTH     1024
typedef struct _HARDDISKINFO{
    char name[LENGTH];//名称
    //char parameterValue[LENGTH];
    char brand[LENGTH];//主板品牌
    char factoryNumber[LENGTH];//出厂编号  序列号
    char model[LENGTH];//型号
    char time[LENGTH];
    char softSetting[LENGTH];

    char size[HARDDISK_LENGTH];
    UINT64 captacity;

}HardDiskInfo, _PHARDDISKINFO;

typedef struct _DISPLAYINFO{
    char name[LENGTH];//名称
    //char parameterValue[LENGTH];
    char brand[LENGTH];//主板品牌
    char factoryNumber[LENGTH];//出厂编号
    char model[LENGTH];//型号
    char time[LENGTH];
    char softSetting[LENGTH];
    UINT64 captacity;
}DisplayInfo, _PDISPLAYINFO;

typedef struct _MAINBOARDINFO{
    char name[LENGTH];//主板名称
    char brand[LENGTH];//主板品牌
    char factoryNumber[LENGTH];//出厂编号
    char model[LENGTH];//型号
    char parameterValue[LENGTH];
    char time[LENGTH];
    char softSetting[LENGTH];
}MainBoardInfo, _PMAINBOARDINFO;

typedef struct tagWin32PhysicalMemory
{
    //Data type: string
    char Manufacturer[LENGTH];  // 制造商

    //Data type: string
    //Physically-labeled bank where the memory is located. This property is inherited from CIM_PhysicalMemory.
    //Examples: "Bank 0", "Bank A"
    char BankLabel[LENGTH];

    //Data type: uint64, string， 调试发现是string
    //Total capacity of the physical memory—in bytes. This property is inherited from CIM_PhysicalMemory.
    //For more information about using uint64 values in scripts, see Scripting in WMI.
    char Capacity[LENGTH];

    //Data type: string
    //Short description of the object—a one-line string. This property is inherited from CIM_ManagedSystemElement.
    char Caption[LENGTH];

    //Data type: string
    //Qualifiers: Key, MaxLen(256)
    //Name of the first concrete class that appears in the inheritance chain used in the creation of an instance. When used with the other key properties of the class, the property allows all instances of this class and its subclasses to be identified uniquely. This property is inherited from CIM_PhysicalElement.
    char CreationClassName[LENGTH];

    //Data type: uint16
    //Data width of the physical memory—in bits. A data width of 0 (zero) and a total width of 8 (eight) indicates that the memory is used solely to provide error correction bits. This property is inherited from CIM_PhysicalMemory.
    UINT16 DataWidth;

    //Data type: string
    //Description of an object. This property is inherited from CIM_ManagedSystemElement.
    char Description[LENGTH];

    //Data type: string
    //Label of the socket or circuit board that holds the memory.
    //Example: "SIMM 3"
    char DeviceLocator[LENGTH];

    //Data type: uint16
    //Implementation form factor for the chip. This property is inherited from CIM_Chip.
    UINT16 FormFactor;
}Win32PhysicalMemory;

typedef struct _MEMORYINFO{
    DWORD dwMemoryLoad;
    DWORDLONG ullTotalPhys;
    DWORDLONG ullAvailPhys;
    DWORDLONG ullTotalPageFile;
    DWORDLONG ullAvailPageFile;
    DWORDLONG ullTotalVirtual;
    DWORDLONG ullAvailVirtual;
    DWORDLONG ullAvailExtendedVirtual;

    Win32PhysicalMemory physicalMemory[10];
    DWORD   validMemoryNum;

}MemoryInfo, _PMEMORYINFO;

typedef struct _AUDIOINFO{
    char name[LENGTH];//名称
    char parameterValue[LENGTH];
    char brand[LENGTH];//主板品牌
    char factoryNumber[LENGTH];//出厂编号
    char model[LENGTH];//型号
    char time[LENGTH];
    char softSetting[LENGTH];
}AudioInfo, _PAUDIOINFO;

typedef struct _NETWORKCARDINFO{
    char name[LENGTH];
    char brand[LENGTH];//主板品牌
    char factoryNumber[LENGTH];//出厂编号
    char model[LENGTH];//型号
    char parameterValue[LENGTH];
    char time[LENGTH];
    char softSetting[LENGTH];
    char MACAddress[LENGTH];         //mac地址
    char IPAddress[LENGTH];               //IP地址
    char IPMask[LENGTH];                  //IP掩码
    char Gateway[LENGTH];                 //网关
}NetworkCardInfo, *PNETWORKCARDINFO;

#define SECURITYOPTIONSLENGTH    1024
#define SECURITYOPTIONSNUM       94
#define REGISTRYSETTINGNUM       3
#define EVENTLOGNUM              3
struct SecurityOptions{
    int iType;
    char szName[SECURITYOPTIONSLENGTH];

    int iValue;
    char szValue[SECURITYOPTIONSLENGTH];

    SecurityOptions()
    {
        iType = -1;
        szName[0] = 0;
        iValue = 0;
        strcpy(szValue, "没有定义");
    }
};

typedef struct _PORTINFO
{
    char name[100];
    char localPort[100];
    char mstscPort[100];
    char state[20];
    char pId[20];
    char localAddr[100];
    char mstcAddr[100];
    char path[MAX_PATH];
    _PORTINFO *pNext;
    _PORTINFO()
    {
        ZeroMemory(name, sizeof(_PORTINFO));
    }
}PortInfo, *PPORTINFO;

typedef struct SYSTEMINFO{
    DWORD infoTypeD;
    char infoType[LENGTH];
    char infoName[LENGTH];
    char infoDes[LENGTH];
    char infoPath[LENGTH];
    SYSTEMINFO *pNext;
    SYSTEMINFO()
    {
        ZeroMemory(&infoTypeD, sizeof(SYSTEMINFO));
    }
}SystemInfoDec, *PSYSTEMINFODEC;

typedef struct tagRegistryValueInfo
{
    char    communities[256];
    DWORD   valueType;
    tagRegistryValueInfo *pNext;

    tagRegistryValueInfo()
    {
        communities[0] = 0;
        valueType = -1;
        pNext = NULL;
    }
}RegistryValueInfo;

typedef struct tagSNMPService
{
    BOOL  isValid;
    RegistryValueInfo *pRegistrValues;
    tagSNMPService()
    {
        isValid = FALSE;
        pRegistrValues = NULL;
    }
}SNMPService;

#endif  // CHECK_COMMON_H
