#ifndef _RESULT_2_HTML__
#define _RESULT_2_HTML__

#include "GrxaHostCheck.h"
#include "CheckResultResouce.h"
//#include "include/htmllog/HtmlLog.h"
#include "WriteHtmlDll.h"

BOOL WriteHtml(char szHtmlFile[512]);

VOID HtmlStandardItems(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults);

VOID HtmlUSBItems(HtmlColumnInfo &htmlCol, int &iNums, USBHISTORY* pUsbHis);
VOID HtmlBrowserItems(HtmlColumnInfo &htmlCol, int &iNums, IeVisitHistory *pHistoryIE, FireFoxHistory *pFirefoxHis, ChromeHistory *pChromeHis);
VOID HtmlSystemOs(HtmlColumnInfo &htmlCol, int &iNums, OsVersionInfo *pOsVersion, time_t osInstallTime, char *hostName, char *bootTime, char *biosParameterValue);
VOID HtmlSoftwares(HtmlColumnInfo &htmlCol, int &iNums, SoftwareInfo *pSoftware, int softNum);
VOID HtmlProcess(HtmlColumnInfo &htmlCol, int &iNums, ProcessInfo* pProcess, int processNum);
VOID HtmlServices(HtmlColumnInfo &htmlCol, int &iNums, SERVICE_STATUS_INFO1 *pServiceStatus, int serviceNum);
VOID HtmlSnmp(HtmlColumnInfo &htmlCol, int &iNums, SNMPService *pSnmp);
VOID HtmlDiskPartitions(HtmlColumnInfo &htmlCol, int &iNums, LogicalDrivesInfo* pLogicDrives, int drivesNum);
VOID HtmlRights(HtmlColumnInfo &htmlCol, int &iNums, DrivesAccountRights *pRights, int rightsNum);
VOID HtmlDiskRights(HtmlColumnInfo &htmlCol, int &iNums, DrivesAccountRights *pRights, int rightsNum);
VOID HtmlSystemRights(HtmlColumnInfo &htmlCol, int &iNums, DrivesAccountRights *pRights, int rightsNum);
VOID HtmlCPUs(HtmlColumnInfo &htmlCol, int &iNums, CpuInfo *pCpuinfo);
VOID HtmlHardDisks(HtmlColumnInfo &htmlCol, int &iNums, HardDiskInfo* pHardDisk, int diskNum);
VOID HtmlBoard(HtmlColumnInfo &htmlCol, int &iNums, MainBoardInfo *pBoardInfo);
VOID HtmlMemorys(HtmlColumnInfo &htmlCol, int &iNums, MemoryInfo* pMemory);
VOID HtmlMemorys2(HtmlColumnInfo &htmlCol, int &iNums, MemoryInfo* pMemory);
VOID HtmlDisplayCards(HtmlColumnInfo &htmlCol, int &iNums, DisplayInfo *pdi);
VOID HtmlSoundCards(HtmlColumnInfo &htmlCol, int &iNums, AudioInfo *pai);
VOID HtmlEthernetAdapters(HtmlColumnInfo &htmlCol, int &iNums, NetworkCardInfo* pEthernetAdapter, int ethnetNum);
VOID HtmlSecurityOptions(HtmlColumnInfo &htmlCol, int &iNums, SecurityOptions *pSecurityOpt, int optNum);
VOID HtmlRegistrySetsOptions(HtmlColumnInfo &htmlCol, int &iNums, SecurityOptions *pSecurityOpt, int optNum);
VOID HtmlEventlogsOptions(HtmlColumnInfo &htmlCol, int &iNums, SecurityOptions *pSecurityOpt, int optNum);
VOID HtmlUsers(HtmlColumnInfo &htmlCol, int &iNums, USER_INFO_2 *pUserInfo, int userNum);
VOID HtmlShares(HtmlColumnInfo &htmlCol, int &iNums, SHARE_INFO_502 *pShareInfo, int shareNum);
VOID HtmlActivePorts(HtmlColumnInfo &htmlCol, int &iNums, PortInfo *pPortInfo);
VOID HtmlAntivirus(HtmlColumnInfo &htmlCol, int &iNums, AntivirusSoft *pAntiVirusSoft, int antivirusNum);
VOID HtmlAntivirusPro(HtmlColumnInfo &htmlCol, int &iNums, AntivirusProduct *pAntivirusPro);
VOID HtmlRuns(HtmlColumnInfo &htmlCol, int &iNums, RunItems *pRunItems);
VOID HtmlPatchsInstalled(HtmlColumnInfo &htmlCol, int &iNums, SystemDefectInfo *pSystemDefInstall);

VOID HtmlCheckResult(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults);
VOID HtmlPasswordPolicies(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults);
VOID HtmlAuditPolicies(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults);
VOID HtmlAccLockPolicys(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults);
VOID HtmlUserRightAssignment(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults);
VOID HtmlUserRightAssignment(HtmlColumnInfo &htmlCol, int &iNums, user_rights_assignment_t *pUserRightsAssignments, int userRightsNum);
VOID HtmlSecurityOption(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults);
VOID HtmlAutoAdminLogin(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults);
VOID HtmlDriverAutoOperation(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults);
VOID HtmlMakeDumpFile(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults);
VOID HtmlNetConnects(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults);
VOID HtmlGroupPolicys(HtmlColumnInfo &htmlCol, int &iNums, DtckResults* pDtckResults);

VOID HtmlUsbDeep(HtmlColumnInfo &htmlCol,int &iNums);
VOID HtmlBrowserDeep(HtmlColumnInfo &htmlCol,int &iNums);
VOID HtmlKeyWord(HtmlColumnInfo &htmlCol,int &iNums);

#endif  // _RESULT_2_HTML__
