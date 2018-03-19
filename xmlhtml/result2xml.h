// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DJJC_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// DJJC_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#pragma once

#include "include/tinyxml/tinyxml.h"
#include "GrxaHostCheck.h"
#include "global.h"


/******************************************************************************
Parameters
    iToolNum [in]
        The tool number, between 0 and 12. 
        0 is windows host.
        1 is linux host
        ……
    lists [in]
        The vector is used to save the content which is reads from the xml file.
    pToolName [in]
        The name is written into the xml file, which is from '1' to '7'.
    *pResult [out]
        Write result to the pResult buf.
    len [out]
        the length of *pResult buf.

Return Value
    If the operation completes successfully, the return value is 0.
    If the function fails, the return value is nonzero.

Remarks
    This function is used to write the vector into a memory.

******************************************************************************/
int    WriteDjjcResult2Memory(int iToolNum, char **pResult, int &len);

/******************************************************************************
Parameters
    *pResult [in|out]
        Delete the buf of pResult.

Return Value
    none.

Remarks
    This function is used to free the buf, whitch is malloc from WriteDjjcResult2Memory.

******************************************************************************/
void   FreeMemoryBuf(char **pResult);


BOOL InsertHead(TiXmlElement &elmParent, int iToolNum);
VOID InsertAllItems(TiXmlElement &elmParent);

VOID InsertStandardItems(TiXmlElement &xmlElements, DtckResults* pDtckResults);
VOID InsertUSBItems(TiXmlElement &xmlElements, USBHISTORY* pUsbHis);
VOID InsertBrowserItems(TiXmlElement &xmlElements, IeVisitHistory *pHistoryIE, FireFoxHistory *pFirefoxHis, ChromeHistory *pChromeHis);
VOID InsertSystemOs(TiXmlElement &xmlElements, OsVersionInfo *pOsVersion, time_t osInstallTime, char *pHostName, char *pBootTime, char *pBiosParameterValue);
VOID InsertSoftwares(TiXmlElement &xmlElements, SoftwareInfo *pSoftware, int softNum);
VOID InsertProcess(TiXmlElement &xmlElements, ProcessInfo* pProcess, int processNum);
VOID InsertServices(TiXmlElement &xmlElements, SERVICE_STATUS_INFO1 *pServiceStatus, int serviceNum);
VOID InsertSnmp(TiXmlElement &xmlElements, SNMPService *pSnmpService);
VOID InsertDiskPartitions(TiXmlElement &elmParent, LogicalDrivesInfo* pLogicDrives, int drivesNum);
VOID InsertRights(TiXmlElement &elmParent, char *pName, DrivesAccountRights *pRights, int rightsNum);
VOID InsertDiskRights(TiXmlElement &elmParent, DrivesAccountRights *pRights, int rightsNum);
VOID InsertSystemRights(TiXmlElement &elmParent, DrivesAccountRights *pRights, int rightsNum);
VOID InsertCPUs(TiXmlElement &elmParent, CpuInfo *pCpuinfo);
VOID InsertHardDisks(TiXmlElement &elmParent, HardDiskInfo* pHardDisk, int diskNum);
VOID InsertBoard(TiXmlElement &elmParent, MainBoardInfo *pBoardInfo);
VOID InsertMemorys(TiXmlElement &elmParent, MemoryInfo* pMemory);
VOID InsertDisplayCards(TiXmlElement &elmParent, DisplayInfo *pdi);
VOID InsertSoundCards(TiXmlElement &elmParent, AudioInfo *pai);
VOID InsertEthernetAdapters(TiXmlElement &elmParent, NetworkCardInfo* pEthernetAdapter, int ethnetNum);
VOID InsertSecurityOptions(TiXmlElement &elmParent, char *pName, SecurityOptions *pSecurityOpt, int optNum);
VOID InsertRegistrySetsOptions(TiXmlElement &elmParent, SecurityOptions *pSecurityOpt, int optNum);
VOID InsertEventlogsOptions(TiXmlElement &elmParent, SecurityOptions *pSecurityOpt, int optNum);
VOID InsertUsers(TiXmlElement &elmParent, USER_INFO_2 *pUserInfo, int userNum);
VOID InsertShares(TiXmlElement &elmParent, SHARE_INFO_502 *pShareInfo, int shareNum);
VOID InsertActivePorts(TiXmlElement &elmParent, PortInfo *pPortInfo);
VOID InsertAntivirus(TiXmlElement &elmParent, AntivirusSoft *pAntiVirusSoft, int antivirusNum);
VOID InsertRuns(TiXmlElement &elmParent, RunItems *pRunItems);
VOID InsertPatchsInstalled(TiXmlElement &elmParent, SystemDefectInfo *pSystemDefInstall);
VOID InsertCheckResult(TiXmlElement &elmParent, char *pName, DtckResults* pDtckResults);
VOID InsertPasswordPolicies(TiXmlElement &elmParent, DtckResults* pDtckResults);
VOID InsertAuditPolicies(TiXmlElement &elmParent, DtckResults* pDtckResults);
VOID InsertAccLockPolicys(TiXmlElement &elmParent, DtckResults* pDtckResults);
VOID InsertUserRightAssignment(TiXmlElement &elmParent, DtckResults* pDtckResults);
VOID InsertSecurityOption(TiXmlElement &elmParent, DtckResults* pDtckResults);
VOID InsertAutoAdminLogin(TiXmlElement &elmParent, DtckResults* pDtckResults);
VOID InsertDriverAutoOperation(TiXmlElement &elmParent, DtckResults* pDtckResults);
VOID InsertMakeDumpFile(TiXmlElement &elmParent, DtckResults* pDtckResults);
VOID InsertNetConnects(TiXmlElement &elmParent, DtckResults* pDtckResults);
VOID InsertGroupPolicys(TiXmlElement &elmParent, DtckResults* pDtckResults);

VOID InsertDeepUSBItems(TiXmlElement &elmParent);
VOID InsertDeepBrowserItems(TiXmlElement &elmParent);

VOID InsertSensItems(TiXmlElement &elmParent);
