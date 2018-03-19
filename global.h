#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QDebug>
#include <QStringList>
#include <QWidget>
#include <windows.h>
#include <QTimer>
#include <vector>
#include <QMutex>
#include <QPoint>
#include "testdirscan.h"
#include "mainwindow.h"
#include "WriteHtmlDll.h"
//#include <string>
//#include "renderthread.h"

using namespace  std;

//#define DEBUGLOG 3

typedef struct _MSG_TRANS_FILE_INFO_T
{
    INT32		nID;
    INT32		nSubID;
    DWORD		dwFileSize;
    char	strUpFile[256]; 	//指定的需要上传的文件名(absolute path)
}MsgTransFile;

//服务端下发的终端磁盘文件目录检查命令
//临时定义,后续扩展- 关键词的长度是不确定的,后续考虑字符指针方式
typedef struct DB_TASK_SCANDISK_T
{
    int			nID;			//在返回的时候携带
    int			nSubID;
    char		strDir[280];	//如果为空,则为全盘扫描;否则指定目录扫描
    char		strKeys[1024];	//以; 号区分的关键词列表
}DbTaskScanDisk;

typedef struct _TASK_INFO_T
{
    DbTaskScanDisk *pTransF;
    int nKind;
    int taskState;    //任务状态
}TaskInfo;

typedef struct SENS_RES
{
    QString filePath;
    QString keyWord;
}SensRes;

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);  //写log

int WriteHtmlFileTest(HtmlInfo &htmlInfo, HtmlWriteInfo *pHtmlWrite, vector<HtmlColumnInfo> &colInfo);

int my_strcpy_s(char *_DEST, size_t _SIZE, const char *_SRC);
int my_strcat_s(char *_DEST, size_t _SIZE, const char *_SRC);
int my_memcpy_s(void *Dst, int nDstSize, const void *Src, int nCpyLen);

extern QPoint gp;

extern int isChecked;
extern QString scanProject;
extern int num;
extern HWND hwnd;

extern QStringList keyWordList;    //敏感词扫描项
extern QList<SensRes> sensResList;    //敏感词结果
//usb深度检查
extern QStringList usbResList;
//上网记录深度检查
extern QStringList internetResList;
//文件操作
extern QStringList wjczResList;

//是否隐藏界面
extern bool ifHide;

//深度检查进度
extern __int64 gTotalSize;
extern __int64 gCurrSize;

extern bool ifUsbFinish;
extern bool ifIntFinish;
extern bool wjczFinish;

//连接相关
extern int failCode;
extern int isConnected;     //连接服务器 0：成功 1：失败

//extern MsgTransFile *pTaskFile;
extern QTimer *task_timer;    //捕获任务
extern vector<TaskInfo> fileVector;

extern int id;
extern int ifDeep;    //是否有深度检查任务
extern int ifSens;    //是否有敏感任务
extern DWORD hostId;

extern bool ifFromServer;    //是否是服务端下发的任务

extern TestDirScan g_tTestDirScan;
extern bool haveSensTask;    //服务端下发的任务是否包含敏感词
extern bool ifDeepFinish;    //服务端下发的深度检查任务是否结束
extern bool ifSensFinish;    //服务端下发的敏感词检查任务是否结束

extern bool ifHgFinish;    //服务端下发的合规等任务是否结束

extern bool ifSensTask;       //客户端是否启动敏感词检查

extern bool ifPolicyXml;      //xml文件是否写入策略信息


//extern bool readLoginInfo();    //从注册表中读取登录信息

#endif // GLOBAL_H
