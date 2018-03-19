#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "titlebar.h"
#include "xmlresolution.h"
#include "global.h"
#include "xmlhtml/txt.h"
#include "xmlhtml/CheckResultResouce.h"
#include "clientmodule.h"
#include "xmlhtml/result2xml.h"
#include "renderthread.h"
#include "xmlhtml/Resource.h"
#include "xmlhtml/GrxaHostCheck.h"
#include "xmlhtml/result2html.h"
#include "testdirscan.h"
#include "anaxmlfile.h"
#include "checkhistory.h"
#include <QFile>
#include <QLabel>
#include <QMessageBox>
#include <QSettings>
#include <QPalette>
#include <QVBoxLayout>
#include <QDebug>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QLibrary>
#include <QDesktopServices>
#include <QUrl>
#include <Tlhelp32.h>
#include <stdlib.h>
#include <stdio.h>
#include <QProcess>
#include <QProgressDialog>

//标题栏的长度
int pos_min_x = 0;
int pos_max_x = 800 - 50;  //为最小化和关闭按钮留空间
int pos_min_y = 0;
int pos_max_y = 30;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    if(!paraseCmd())
//    {
//        qApp->quit();
//    }
    ui->setupUi(this);

    //initStyle();
    // 初始化标题栏;
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉窗口标题栏
//    Qt::WindowFlags flags = windowFlags();
//    flags |= Qt::WindowStaysOnTopHint;
//    this->setWindowFlags(flags);
    this->setWindowTitle(QString("终端安全工具"));
    this->setFixedSize(this->width(),this->height());
    initTitleBar();
//    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);

    initMainLabel();

    qInstallMessageHandler(outputMessage);

    //gTaskVector = new vector<MsgTransFile>();

    hwnd=(HWND)this->winId();

    gp = this->pos();

//    wdlg = new waitDialog(this);

    mIndex=0;
    mIndex_2=2;
    mIndex_3=4;
    mIndex_4=6;
    mIndex_5=8;
    hjIndex_1=0;
    hjIndex_2=2;
    hjIndex_3=3;
    hjIndex_4=4;
    hjIndex_5=5;
    reportIndex=5;
    mainIndex=0;
    clIndex=4;

    m_persent=0;
    m_persent_2=0;
    m_persent_3=0;

    isRun=0;
    isSysRun=0;
    isClRun=0;
    isMainRun=0;

    flag=0;

    ui->ringsBar->setVisible(false);

    pix = QPixmap(":/button/alert1.png");

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateProgressbar()));
    buding_timer = new QTimer(this);
    connect(buding_timer,SIGNAL(timeout()),this,SLOT(updateBudingProgress()));
    henji_timer = new QTimer(this);
    connect(henji_timer,SIGNAL(timeout()),this,SLOT(updateHenjiProgress()));

    dengbao_timer = new QTimer(this);
    connect(dengbao_timer,SIGNAL(timeout()),this,SLOT(dengbao_task_finish()));

    sens_tiemr = new QTimer(this);
    connect(sens_tiemr,SIGNAL(timeout()),this,SLOT(sens_timer_slot()));

    ifUsbDeepCheck = false;
    ifIntDeepCheck = false;
    ifWjczDeepCheck = false;

    render = new RenderThread(this);

//    buttonStyle = QString("QPushButton{border:none;background-color:#696969;color:#DCDCDC;"
//                          "border-radius:0px;}"
//                          "QPushButton:hover{border:none;background-color:#383838;color:#DCDCDC;"
//                          "border-radius:0px;}"
//                          "QPushButton:pressed{border:none;background-color:#383838;color:#DCDCDC;"
//                          "border-radius:0px;}");
//    buttonStyle_2 = QString("QPushButton{border:none;background-color:#383838;color:#DCDCDC;"
//                            "border-radius:0px;}"
//                            "QPushButton:hover{border:none;background-color:#383838;color:#DCDCDC;"
//                            "border-radius:0px;}"
//                            "QPushButton:pressed{border:none;background-color:#383838;color:#DCDCDC;"
//                            "border-radius:0px;}");
    buttonStyle = QString("QPushButton{border:none;background-color:#BFD4E8;color:black;"
                          "border-radius:0px;}"
                          "QPushButton:hover{border:none;background-color:white;color:black;"
                          "border-radius:0px;}"
                          "QPushButton:pressed{border:none;background-color:white;color:black;"
                          "border-radius:0px;}");
    buttonStyle_2 = QString("QPushButton{border:none;background-color:white;color:black;"
                            "border-radius:0px;}"
                            "QPushButton:hover{border:none;background-color:white;color:black;"
                            "border-radius:0px;}"
                            "QPushButton:pressed{border:none;background-color:white;color:black;"
                            "border-radius:0px;}");
//    style_2 = QString("QPushButton{background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #5B5F5F,stop:0.5 #0C2436,stop:1.0 #27405A);"
//                              "border-style:outset;border-width:1px;border-radius:5px;border-color: #11223F;padding: 1px;font: 16pt 微软雅黑;}"
//                              "QPushButton:hover{background:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #758385, stop: 0.5 #122C39,stop: 1.0 #0E7788);"
//                              "border-color:#11505C;font: 16pt 微软雅黑;}"
//                              "QPushButton:pressed{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #969B9C, stop: 0.5 #16354B,stop: 1.0 #244F76);"
//                              "border-color: #11505C;font: 16pt 微软雅黑;}");
//    buttonStyle_3 = QString("QPushButton{border:none;color:#DCDCDC;padding:5px;min-height:15px;font: 12pt 微软雅黑;"
//                                           "border-radius:5px;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);}"
//                                           "QPushButton:hover{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #646464,stop:1 #525252);}"
//                                           "QPushButton:pressed{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);}");


    buttonStyle_3 = QString("QPushButton{border:none;color:black;padding:5px;min-height:15px;font: 12pt 微软雅黑;"
                                           "border-radius:10px;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #FAFAF9,stop:1 #F1F1F1);}"
                                           "QPushButton:hover{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #F1F1F1,stop:1 #DCDCDC);}"
                                           "QPushButton:pressed{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #F1F1F1,stop:1 #DCDCDC);}");

    buttonStyle_4 = QString("QPushButton{border:none;color:white;padding:5px;min-height:15px;font: 12pt 微软雅黑;"
                                           "border-radius:5px;background-color:rgb(24,158,252);}"
                                           "QPushButton:hover{background-color:rgb(30,198,255);}"
                                           "QPushButton:pressed{background-color:rgb(30,198,255);}");

    toolButtonStyle = QString("QToolButton{border:none;background-color:#BADBFC;color:#000000;border-radius:7px;}"
                              "QToolButton:hover{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #F9FCFF,stop:1 #C0DEFC);}"
                              "QToolButton:pressed{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #F9FCFF,stop:1 #C0DEFC);}"
                              "QToolButton:checked{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #F9FCFF,stop:1 #C0DEFC);}");

    textEditStyle = QString("QLineEdit{border:1px solid #242424;border-radius:3px;padding:2px;"
                            "color:black;background-color:white;selection-background-color:#484848;selection-color:#DCDCDC;}");
    buttonInit();

    ui->wjmlLineEdit->setFocusPolicy(Qt::NoFocus);

    ui->sysStackedWidget->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(0);
    ui->henjiWidget->setCurrentIndex(0);

//    initSysTrayIcon();

    ui->budingTableWidget->setVisible(false);
    ui->chengxuTableWidget->setVisible(false);
    ui->scrollArea->setVisible(false);
    ui->gongxiangTableWidget->setVisible(false);
    ui->peizhiTableWidget->setVisible(false);


    jxwjTableShow();
    ui->dengbaoTableWidget->setVisible(false);

    ui->jxwjButton->setVisible(false);
    ui->wjnrDeepCheckButton->setVisible(false);

    ui->deepTaskStopButton->setVisible(false);

    ifUpdate();

    //初始化连接服务器
    failCode = 0;
    NtCrsInit((void*)this, TestClientChngCb,NetClientMsgCb);
    //登录
    qDebug()<<"try login";
    login();

    //心跳定时器
    heart_timer = new QTimer(this);
    connect(heart_timer,SIGNAL(timeout()),this,SLOT(heart_state_slot()));
//    reLogin_timer = new QTimer(this);
//    connect(reLogin_timer,SIGNAL(timeout()),this,SLOT(relogin_slot()));

    failTime = 0;
    heart_timer->start(2*60*1000);

    stop_timer = new QTimer(this);
    connect(stop_timer,SIGNAL(timeout()),this,SLOT(stop_task_slot()));

    connect(task_timer,SIGNAL(timeout()),this,SLOT(task_start_slot()));
    task_timer->start(30000);

    statusInit();

    HWND m_hWnd;
    m_hWnd = (HWND)this->winId();
    g_tTestDirScan.CreateShareMemInfo(m_hWnd);

    connect(this,SIGNAL(sensTaskStart()),this,SLOT(sensTaskSlot()));

    sensResNotShow();

    QString strPath = qApp->applicationDirPath();
    strPath +="\\update\\Update.exe";
    bool ok = QProcess::startDetached(strPath,QStringList());
    if (!ok)
    {
        qDebug()<<"init update process error!";
    }

    ui->pushButton->setVisible(false);
}

//函数功能：判断进程是否存在，如果存在则返回进程id，否则返回0
//参数 name: 进程名
DWORD GetProcessidFromName(LPCSTR name)
{
    PROCESSENTRY32 pe;
    DWORD id=0;
    HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    pe.dwSize=sizeof(PROCESSENTRY32);
    if(!Process32First(hSnapshot,&pe))
        return 0;
    while(1)
    {
        pe.dwSize=sizeof(PROCESSENTRY32);
        if(Process32Next(hSnapshot,&pe)==FALSE)
            break;
        char output[64];
        sprintf(output, "%ws", pe.szExeFile );
        if(strcmp(output,name)==0)
        {
            id=pe.th32ProcessID;
            break;
        }
    }
    CloseHandle(hSnapshot);
    return id;
}


//注意：目前是强制退出，将来要改成发送退出信号让tests程序主动退出
void exitTests()
{
    PROCESSENTRY32 pe;
    DWORD processId = GetProcessidFromName("TestS.exe");
    if (processId)
    {
        HANDLE process = ::OpenProcess(PROCESS_TERMINATE,FALSE,processId);
        if(process)
        {
            ::TerminateProcess(process,0);
        }
    }
}

MainWindow::~MainWindow()
{
    qDebug()<<"mainwindows delete";
    keyWordList.clear();
    usbResList.clear();
    internetResList.clear();
    wjczResList.clear();
    sensResList.clear();
    if(isChecked==0)
    {
        CheckStop();
    }
    render->stop();
    render->wait();
    if(heart_timer->isActive())
    {
        heart_timer->stop();
    }
    if(task_timer->isActive())
    {
        task_timer->stop();
    }
    if(!fileVector.empty())
    {
        fileVector.clear();
    }

    NtCrsUninit();      //与服务器断开连接
    exitTests();
    delete ui;
}

void MainWindow::sensResNotShow()
{
    ui->label_148->setVisible(false);
    ui->resLabel_19->setVisible(false);
    ui->label_57->setVisible(false);
    ui->resLabel_8->setVisible(false);
    ui->result_button_8->setVisible(false);
}

bool QWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);
    MSG* msg = reinterpret_cast<MSG*>(message);
    if(msg->message==WM_RECEIVE)
    {
        WPARAM wParam = msg->wParam;
        LPARAM lParam = msg->lParam;
        g_tTestDirScan.OnRecvFromTxLib(wParam,lParam);
        return false;
    }
    return false;
}

//bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
//{
//    MSG *param = static_cast<MSG *>(message);

//    switch (param->message)
//    {
//    case WM_RECEIVE:
//    {
//        WPARAM wParam = param->wParam;
//        LPARAM lParam = param->lParam;
//        g_tTestDirScan.OnRecvFromTxLib(wParam,lParam);
//        return true;
//    }
//    }
//    return QWidget::nativeEvent(eventType, message, result);
//}

void MainWindow::sensTaskSlot()
{
    if(ifDeepFinish==true&&ifSensFinish==true&&ifHgFinish==true)
    {
        //生成报告
        ifSens = 0;
        ifSensFinish = false;
        haveSensTask = false;
        QString localPath = qApp->applicationDirPath();
        localPath += "\\sssens\\senscan.xml";
        AnaXmlFile::anaXml(localPath);
        ifSensFinish = false;
        QString localPath_2 = qApp->applicationDirPath();
        localPath_2 += "/report";
        isDirExist(localPath_2);
        if(!ifFromServer)
        {
            localPath_2 += QString("/myxml.xml");
        }
        else
        {
            localPath_2 += QString("/myxmlfromserver.xml");
        }

        QByteArray ba_2 = localPath_2.toLatin1();
        char *c_str_2 = ba_2.data();
        Write2Xml(c_str_2);

        QString localPath_3 = qApp->applicationDirPath();
        localPath_3 += "/report";
        if(!ifFromServer)
        {
            localPath_3 += "/myhtml.html";
        }
        else
        {
            localPath_3 += "/myhtmlfromserver.html";
        }
//        QByteArray ba_3 = localPath_3.toLatin1();
//        char *c_str_3 = ba_3.data();
//        WriteHtml(c_str_3);

        qDebug()<<"sensTaskSlot id:"<<id;
        NtCrsSntdFele(c_str_2,id);
        ifFromServer = false;
        isChecked = 1;
    }
    else
    {
        if(!sens_tiemr->isActive())
        {
            sens_tiemr->start(10000);
        }
    }
}

void MainWindow::sens_timer_slot()
{
    if(ifDeepFinish==true&&ifSensFinish==true&&ifHgFinish==true)
    {
        //生成报告
        QString localPath = qApp->applicationDirPath();
        localPath += "\\sssens\\senscan.xml";
        AnaXmlFile::anaXml(localPath);
        ifSensFinish = false;
        QString localPath_2 = qApp->applicationDirPath();
        localPath_2 += "/report";
        isDirExist(localPath_2);
        if(!ifFromServer)
        {
            localPath_2 += QString("/myxml.xml");
        }
        else
        {
            localPath_2 += QString("/myxmlfromserver.xml");
        }
        QByteArray ba_2 = localPath_2.toLatin1();
        char *c_str_2 = ba_2.data();
        Write2Xml(c_str_2);

//        QString localPath_3 = qApp->applicationDirPath();
//        localPath_3 += "/report";
//        if(!ifFromServer)
//        {
//            localPath_3 += "/myhtml.html";
//        }
//        else
//        {
//            localPath_3 += "/myhtmlfromserver.html";
//        }
//        QByteArray ba_3 = localPath_3.toLatin1();
//        char *c_str_3 = ba_3.data();
//        WriteHtml(c_str_3);
        qDebug()<<"sens_timer_slot id:"<<id;
        NtCrsSntdFele(c_str_2,id);
        haveSensTask=false;
        ifSens = 0;
        isChecked = 1;
        ifFromServer = false;
        if(sens_tiemr->isActive())
        {
            sens_tiemr->stop();
        }
    }
    else
    {
        return;
    }
}

void GetExePath(char* process)
{
    GetModuleFileNameA(NULL,process,MAX_PATH);

    for(int i=(int)_tcslen(process);i>0;i--)
    {
        if( process[i] =='\\')
        {
            process[i+1]='\0';
            break;
        }
    }
}

BOOL IsAdmin()
{
    static BOOL bAdmin=-1;
    if(bAdmin==-1)
    {
        char DevName[] = "\\\\.\\C:";

        char szPath[MAX_PATH]={0};
        GetExePath(szPath);


        DevName[4] = szPath[0];

        HANDLE h = CreateFileA(
            DevName,
            GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        if (h==INVALID_HANDLE_VALUE)
        {
            bAdmin=FALSE;
        }
        else
        {
            bAdmin=TRUE;
            CloseHandle(h);
        }
    }
    return bAdmin;
}


// bRet - 0:连接成功 1:关闭套接字
// dwErr - 失败原因值
void __stdcall MainWindow::TestClientChngCb(const int &bRet, const void *pApp, const int &dwErr)
{
    Q_UNUSED(pApp);
    isConnected = bRet;
    if (isConnected==1) //CLOSE SOCKET
    {
        failCode = dwErr;
        qWarning()<<"tcp connect failed:"<<dwErr;
    }
    else if(isConnected==0)
    {
        qDebug()<<"tcp connect,wait login";
    }
    else if(isConnected==NET_MSG_CFG_POLICY)  // connect success
    {
        qDebug()<<"login success";
    }
}

//接收指令的回调函数
int __stdcall MainWindow::NetClientMsgCb(const WORD &wMsg, const int &nMsgContent,void *content,void *reserved)
{
    qDebug()<<"____________________NetClientMsgCb__________________________";
    int taskCode = (int)wMsg;
    Q_UNUSED(nMsgContent);
    Q_UNUSED(reserved);
    if(content)
    {
        DbTaskScanDisk *pTaskFile = new  DbTaskScanDisk;
        memcpy(pTaskFile,content,sizeof(DbTaskScanDisk));
//                = (DbTaskScanDisk*)content;
        qDebug()<<"code:"<<taskCode<<" id:"<<pTaskFile->nID<<" subId:"<<pTaskFile->nSubID<<" char:"<<pTaskFile->strKeys<<" task:"<<pTaskFile->strDir;
        TaskInfo mTask;
        mTask.pTransF = pTaskFile;
        mTask.nKind = taskCode;
        fileVector.push_back(mTask);

//        TaskInfo mTask1 = fileVector[0];

//        char *mKey = new char[1024];
//        my_strcpy_s(mKey,1024,mTask1.pTransF->strKeys);
//        QString strKey = QString::fromLocal8Bit(mKey);
//        qDebug()<<"mKey"<<mKey<<"strKey"<<strKey;

        if(pTaskFile)
        {
            pTaskFile = NULL;
        }
    }
    return 0;
}

void MainWindow::task_start_slot()
{
    if(!fileVector.empty())
    {
        if(isChecked==0||m_persent!=0||m_persent_2!=0||m_persent_3!=0)     //有任务正在运行
        {
            qDebug()<<"task is running";
            return;
        }
        else
        {
            TaskInfo mTask;
            mTask = fileVector[0];
//            id = mTask.pTransF->nID;

            char *pTask = new char[280];
            my_strcpy_s(pTask,280,mTask.pTransF->strDir);
            if(pTask!=NULL)
            {
                QString strCmd = QString::fromLocal8Bit(pTask);
                QStringList cmdList = strCmd.split(",");
                if(!cmdList.isEmpty())
                {
                    if(cmdList.contains(QString("mgxx")))
                    {
                        QString strKey = QString::fromLocal8Bit(mTask.pTransF->strKeys);
//                        qDebug()<<"id is:"<<mTask.pTransF->nID;
                        QString strPath = QString("");
                        keyWordList.append(strKey);
                        keyWordList.append(strPath);
                        emit sensTaskStart();
                    }
                }
            }
            num = 100;
            render->test();
        }
    }
}

void MainWindow::relogin_slot()
{
    login();
}

// 过滤掉虚拟网卡
int FilterNetCards(NetworkCardInfo *pCards, int cardNum, NetworkCardInfo *pSortCards, int sortCardNum)
{
//    NetworkCardInfo cards2[4];
    int idx=0;
    int i=0;
    for(i=0; i<cardNum; i++)
    {
        NetworkCardInfo &netCard = pCards[i];
        if (0 == strnicmp(netCard.brand, "VMware", strlen("VMware")))
            continue;

        if (idx >= sortCardNum)
            break;

        NetworkCardInfo &sordCard = pSortCards[idx++];
        sordCard = netCard;
    }

    NetworkCardInfo tmpCard;
    for (i=0; i<idx; i++)
    {
        for (int j=i+1; j<idx; j++)
        {
            if (strcmp(pSortCards[i].MACAddress, pSortCards[j].MACAddress) > 0)
            {
                tmpCard = pSortCards[i];
                pSortCards[i] = pSortCards[j];
                pSortCards[j] = tmpCard;
            }
        }
    }
    return idx;
}

DWORD ReadRegDWORD(HKEY hRootKey, LPCSTR strCurrentPath, LPCSTR strKey, DWORD &dwValue)
{
    HKEY hKey;
    DWORD dwSize = sizeof(dwValue);
    DWORD dwType = REG_DWORD;
    if (::RegOpenKeyExA(hRootKey, strCurrentPath, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
    {
        return GetLastError();
    }
    if (::RegQueryValueExA(hKey, strKey, NULL, &dwType, (LPBYTE)&dwValue, &dwSize)
        != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        return GetLastError();
    }
    RegCloseKey(hKey);
    return 0;
}

DWORD ReadRegSZ(HKEY hRootKey, LPCSTR strCurrentPath, LPCSTR strKey, char *regValue, const DWORD & dwLen)
{
    HKEY hKey;
    DWORD dwSize = dwLen;
    DWORD dwType = REG_SZ;
    if (::RegOpenKeyExA(hRootKey, strCurrentPath, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        return GetLastError();
    }
    if (::RegQueryValueExA(hKey, strKey, NULL, &dwType, (LPBYTE)regValue, &dwSize)
        != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        return GetLastError();
    }
    RegCloseKey(hKey);
    return 0;
}

typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);

bool ifWin64()
{
    OSVERSIONINFOEX osvi;
    SYSTEM_INFO si;
    PGNSI pGNSI;
    ZeroMemory(&si, sizeof(SYSTEM_INFO));
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    GetVersionEx((OSVERSIONINFO*)&osvi);
    pGNSI = (PGNSI) GetProcAddress(
                GetModuleHandle(TEXT("kernel32.dll")),
                "GetNativeSystemInfo");
    if(NULL != pGNSI)
    {
        pGNSI(&si);
    }
    else
    {
        GetSystemInfo(&si);
    }

    if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
    {
        return true;
    }

    else if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL )
    {
        return false;
    }
    return false;
}

unsigned char a2x(const char c)
{
    switch(c) {
    case '0'...'9':
        return (unsigned char)atoi(&c);
    case 'a'...'f':
        return 0xa + (c-'a');
    case 'A'...'F':
        return 0xa + (c-'A');
    default:
        goto error;
    }
error:
    exit(0);
}

BOOL WriteRegDWORD(HKEY hRootKey, LPCSTR strCurrentPath, LPCSTR strKey, DWORD regValue)
{
    HKEY hKey;
    if (::RegOpenKeyExA(hRootKey, strCurrentPath, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS)
    {
        return FALSE;
    }
    if (::RegSetValueExA(hKey, strKey, 0, REG_DWORD, (LPBYTE)&regValue, sizeof(regValue))
        != ERROR_SUCCESS)
    {
        return FALSE;
    }
    ::RegCloseKey(hKey);
    return TRUE;
}

const unsigned int key = 1234567890;
enum ENCRYPTIONTYPE{ENCRYPTION_ENCRYPT, ENCRYPTION_DECRYPT};
#define ROTL32(x,y) ((x<<y)|(x>>(32-y)))
#define ROTR32(x,y) ((x>>y)|(x<<(32-y)))
#define ROTL24(x,y) ((x<<y)|(x>>(24-y)))
#define ROTR24(x,y) ((x>>y)|(x<<(24-y)))
#define ROTL16(x,y) ((x<<y)|(x>>(16-y)))
#define ROTR16(x,y) ((x>>y)|(x<<(16-y)))
#define ROTL8(x,y) ((x<<y)|(x>>(8-y)))
#define ROTR8(x,y) ((x>>y)|(x<<(8-y)))

bool XOR32(char * filename, unsigned int key, int encode)
{
    srand(key);
    FILE * in, * out;
    char tempfilename[MAX_PATH] = {0};
    sprintf(tempfilename,"%s%s",filename,".temp");
    if ((in = fopen(filename, "rb")) == NULL)
    {
        return false;
    }
    else
    {
        if ((out = fopen(tempfilename, "wb")) == NULL)
        {
            return false;
        }
        else
        {
            unsigned int block;
            int a, b, c, d, magnitude, polarity;
            if (encode)
            {
                while((a = fgetc(in)) != EOF && (b = fgetc(in)) != EOF && (c = fgetc(in)) != EOF && (d = fgetc(in)) != EOF)
                {
                    polarity = rand()%2;
                    magnitude = rand()%32;
                    block = ((d<<24) | (c<<16) |(b<<8) | a);
                    block ^= ((rand()%256<<24) | (rand()%256<<16) | (rand()%256<<8) | rand()%256);
                    if (polarity) block = ROTL32(block,magnitude);
                    else block = ROTR32(block,magnitude);
                    putc(block,out);
                    putc(block=block>>8,out);
                    putc(block=block>>8,out);
                    putc(block=block>>8,out);
                }
                if (a != EOF && b != EOF && c != EOF && d == EOF)
                {
                    polarity = rand()%2;
                    magnitude = rand()%24;
                    block = ((c<<16) |(b<<8) | a);
                    block ^= ((rand()%256<<16) | (rand()%256<<8) | rand()%256);
                    if (polarity) block = ROTL24(block,magnitude);
                    else block = ROTR24(block,magnitude);
                    putc(block,out);
                    putc(block=block>>8,out);
                    putc(block=block>>8,out);
                }
                else if (a != EOF && b != EOF && c == EOF)
                {
                    polarity = rand()%2;
                    magnitude = rand()%16;
                    block = ((b<<8) | a);
                    block ^= ((rand()%256<<8) | rand()%256);
                    if (polarity) block = ROTL16(block,magnitude);
                    else block = ROTR16(block,magnitude);
                    putc(block,out);
                    putc(block=block>>8,out);
                }
                else if (a != EOF && b == EOF)
                {
                    polarity = rand()%2;
                    magnitude = rand()%8;
                    block = (a);
                    block ^= (rand()%256);
                    if (polarity) block = ROTL8(block,magnitude);
                    else block = ROTR8(block,magnitude);
                    putc(block,out);
                }
            }
            else
            {
                while((a = fgetc(in)) != EOF && (b = fgetc(in)) != EOF && (c = fgetc(in)) != EOF && (d = fgetc(in)) != EOF)
                {
                    polarity = rand()%2;
                    magnitude = rand()%32;
                    block = ((d<<24) | (c<<16) |(b<<8) | a);
                    if (polarity) block = ROTR32(block,magnitude);
                    else block = ROTL32(block,magnitude);
                    block ^= ((rand()%256<<24) | (rand()%256<<16) | (rand()%256<<8) | rand()%256);
                    putc(block,out);
                    putc(block=block>>8,out);
                    putc(block=block>>8,out);
                    putc(block=block>>8,out);
                }
                if (a != EOF && b != EOF && c != EOF && d == EOF)
                {
                    polarity = rand()%2;
                    magnitude = rand()%24;
                    block = ((c<<16) |(b<<8) | a);
                    if (polarity) block = ROTR24(block,magnitude);
                    else block = ROTL24(block,magnitude);
                    block ^= ((rand()%256<<16) | (rand()%256<<8) | rand()%256);
                    putc(block,out);
                    putc(block=block>>8,out);
                    putc(block=block>>8,out);
                }
                else if (a != EOF && b != EOF && c == EOF)
                {
                    polarity = rand()%2;
                    magnitude = rand()%16;
                    block = ((b<<8) | a);
                    if (polarity) block = ROTR16(block,magnitude);
                    else block = ROTL16(block,magnitude);
                    block ^= ((rand()%256<<8) | rand()%256);
                    putc(block,out);
                    putc(block=block>>8,out);
                }
                else if (a != EOF && b == EOF)
                {
                    polarity = rand()%2;
                    magnitude = rand()%8;
                    block = (a);
                    if (polarity) block = ROTR8(block,magnitude);
                    else block = ROTL8(block,magnitude);
                    block ^= (rand()%256);
                    putc(block,out);
                }
            }
            fclose(in);
            fclose(out);
            remove(filename);
            rename(tempfilename,filename);
        }
    }
    return true;

}

BOOL GRXAWritePrivateProfileString(char* lpAppName,char* lpKeyName,char* lpString,char* lpFileName)
{
    BOOL bRet = TRUE;
    HANDLE m_hFile;
    bool bCreate = false;

    if (INVALID_FILE_ATTRIBUTES == GetFileAttributesA(lpFileName))
    {
        // 文件不存在
        m_hFile = CreateFileA(lpFileName, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (INVALID_HANDLE_VALUE != m_hFile)
        {
            CloseHandle(m_hFile);
            WritePrivateProfileStringA(lpAppName, lpKeyName, "", lpFileName);
            XOR32(lpFileName, key, ENCRYPTION_ENCRYPT);
        }
        bCreate = true;
    }

    if (bCreate)
    {
        if(XOR32(lpFileName, key, ENCRYPTION_DECRYPT))
        {
            bRet = WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
            if ((bRet)&&(XOR32(lpFileName, key, ENCRYPTION_ENCRYPT)))
            {
                bRet = TRUE;
            }
        }
        else
        {
            bRet = FALSE;
        }

    }
    else
    {
        if(XOR32(lpFileName, key, ENCRYPTION_DECRYPT))
        {
            bRet = WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
            XOR32(lpFileName, key, ENCRYPTION_ENCRYPT);
        }
        else
        {
            bRet = FALSE;
        }
    }
    return bRet;
}

void MainWindow::ifUpdate()
{
    QString localPath = qApp->applicationDirPath();
    localPath += "\\SensDef.ini";
    QFileInfo fi(localPath);
    if(!fi.isFile())
    {
        QByteArray ba = localPath.toLatin1();
        char *c_strPath = ba.data();
        char *mAppName = "setting";
        char *mKeyName = "version";
        char *strString = "256";
        GRXAWritePrivateProfileString(mAppName,mKeyName,strString,c_strPath);
    }
    return;
}


void MainWindow::login()
{
    NetLoginInfo tNLI;
    memset(&tNLI,0,sizeof(tNLI));

    char m_strSvrIp[32] ={ 0 };
    DWORD m_Port = 0;
    int err1,err2;
    if(ifWin64())
    {
        err1=ReadRegSZ(HKEY_LOCAL_MACHINE,"SOFTWARE\\Wow6432Node\\phenix\\pclient\\SafeCheck","ServerIP",m_strSvrIp,sizeof(m_strSvrIp));
//        ReadRegDWORD(HKEY_LOCAL_MACHINE,"SOFTWARE\\Wow6432Node\\phenix\\pclient\\SafeCheck","PORT",m_Port);
        err2=ReadRegDWORD(HKEY_LOCAL_MACHINE,"SOFTWARE\\Wow6432Node\\phenix\\pclient\\SafeCheck","HostID",hostId);
    }
    else
    {
        err1=ReadRegSZ(HKEY_LOCAL_MACHINE,"SOFTWARE\\phenix\\pclient\\SafeCheck","ServerIP",m_strSvrIp,sizeof(m_strSvrIp));
//        ReadRegDWORD(HKEY_LOCAL_MACHINE,"SOFTWARE\\phenix\\pclient\\SafeCheck","PORT",m_Port);
        err2=ReadRegDWORD(HKEY_LOCAL_MACHINE,"SOFTWARE\\phenix\\pclient\\SafeCheck","HostID",hostId);
    }
    if(err1!=0||err2!=0)
    {
        qWarning()<<"read reg error! errcode1:"<<err1<<"errcode2"<<err2;
    }

//    tNLI.iPort = 51234;         //对外环境
//    tNLI.iPort = 1234;
    QString localPath = qApp->applicationDirPath();
    localPath+="\\config.ini";
    QSettings settings(localPath,QSettings::IniFormat);
    settings.setIniCodec("utf-8");
    QString strPort = settings.value("server/port").toString();
    m_Port = strPort.toLong();
    tNLI.iPort = m_Port;
    my_strcpy_s(tNLI.szServerIP,20,m_strSvrIp);
    qDebug()<<"server ip:"<<m_strSvrIp<<"port"<<m_Port;
    char strHostId[32] = { 0 };
    itoa(hostId,strHostId,10);
//    strcpy(tNLI.szServerIP, "218.2.97.66");     //对外环境
//    strcpy(tNLI.szServerIP, "172.16.39.93");     //测试环境

    NetMsgAuthEx2 tAuthEx;
    memset(&tAuthEx, 0, sizeof(tAuthEx));
    memcpy(&tAuthEx, &tNLI.tAuth, sizeof(NetMsgAuth));

    //硬盘信息
    CheckResultResouce::diskNum = 0;
    CheckResultResouce::pHardDisk = NULL;
    CheckResultResouce::diskNum = GetHardDiskInfo(&CheckResultResouce::pHardDisk);
//    my_strcpy_s(tAuthEx.strPid,32,CheckResultResouce::pHardDisk->factoryNumber);
    my_strcpy_s(tAuthEx.strPid,32,strHostId);
    my_strcpy_s(tAuthEx.strHost,sizeof(tAuthEx.strHost),CheckResultResouce::pHardDisk->factoryNumber);
    qDebug()<<"pid is: "<<tAuthEx.strPid;
    //网卡信息
    CheckResultResouce::netcardNum = 0;
    CheckResultResouce::pNetwork = NULL;
    CheckResultResouce::netcardNum = GetNetworkCardInfo(&CheckResultResouce::pNetwork);
    NetworkCardInfo *pNetCard = new NetworkCardInfo[4];
    int num = FilterNetCards(CheckResultResouce::pNetwork,CheckResultResouce::netcardNum,pNetCard,4);
    if(num>4)
    {
        num=4;
    }
    int ipNum = 0;
    for(int i=0;i<num;i++)
    {
        char *mIp = pNetCard[i].IPAddress;
        DWORD dwIp = inet_addr(mIp);
        if(dwIp==0)
        {
            num=num-1;
            continue;
        }
        char *mMac = pNetCard[i].MACAddress;
        for(int j = 0; j < 6; j++)
        {
            tAuthEx.baMacAddr[j+6*ipNum] = (a2x(mMac[j*3]) << 4) + a2x(mMac[j*3 + 1]);
        }
        tAuthEx.dwIpAddr[ipNum] = dwIp;
        ipNum++;
    }
    if(pNetCard)
    {
        delete []pNetCard;
        pNetCard=NULL;
    }
//    strcpy(tAuthEx.strPid, "11-0c-29-05-7e-3f");
    memcpy(tAuthEx.baFlag, "GRXA", GR_AUTH_FLAG_N);
    tAuthEx.bExVer = 3; //2:测试版本 3:

//    my_strcpy_s(tAuthEx.strHost, "test1");
//    tAuthEx.dwIpAddr[0] = 0x12341221;//, &(pCurrAddresses->FirstUnicastAddress->Address.lpSockaddr->sa_data[2]), 4) ;

    NtCrsLgon(2, tNLI, tAuthEx);
}

void MainWindow::heart_state_slot()
{  
    QString strVersion ;
    if(isConnected!=NET_MSG_CFG_POLICY)  //连接失败
    {
//        if(!reLogin_timer->isActive())
//        {
//            reLogin_timer->start(60*1000);
//        }
        strVersion = QString("未连接服务器");
        qDebug()<<"try login";
        login();    //重连
    }
    else
    {
        NtCrsSndCmnd(NET_MSG_HEART_REQ, 0, 0, NULL);
//        if(reLogin_timer->isActive())
//        {
//            reLogin_timer->stop();
//        }
        strVersion = QString("已连接服务器");
    }
    verLabel->setText(strVersion);
}

void MainWindow::initMainLabel()
{
    QString time,hegui,wailian,mingan,all;
    QString localPath = qApp->applicationDirPath();
    localPath+="\\config.ini";
    QSettings settings(localPath,QSettings::IniFormat);
    settings.setIniCodec("utf-8");
    time = settings.value("result/time").toString();
    hegui = settings.value("result/hegui").toString();
    wailian = settings.value("result/wailian").toString();
    mingan = settings.value("result/usb").toString();
    all = settings.value("result/all").toString();
    if(time.isEmpty())
    {
        QString str_1 = QString("进行电脑体检，守护电脑安全");
        ui->mainLabel_1->setText(str_1);
        ui->mainLabel_2->setText(" ");
        ui->mainLabel_3->setText(" ");
    }
    else
    {
        QString str_1 = QString("上次体检已完成，检查出%1个问题项").arg(all);
        ui->mainLabel_1->setText(str_1);
        QString str_2 = QString("合规检查:%1  违规外联:%2  移动介质使用:%3").arg(hegui).arg(wailian).arg(mingan);
        ui->mainLabel_2->setText(str_2);
        QString str_3 = QString("上次体检时间:%1").arg(time);
        ui->mainLabel_3->setText(str_3);
    }

}

void MainWindow::initTitleBar()
{
    int width = this->width();//获取界面的宽度
    QToolButton *minButton = new QToolButton(this);   //最小按钮
    QToolButton *closeButton = new QToolButton(this);  //关闭按钮
    QLabel *titleLabel = new QLabel(this);   //标题
    QLabel *iconLabel = new QLabel(this);  //图标
    connect(minButton, SIGNAL(clicked()), this, SLOT(on_actionMinimize_triggered()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(on_actionClose_triggered()));

    //获取最小化、关闭按钮图标
    QPixmap minPix  = QPixmap(":/button/subtract.png");
    QPixmap closePix = QPixmap(":/button/close.png");
    QPixmap iconPix = QPixmap(":/button/shield.png");

    //设置最小化、关闭按钮图标
    minButton->setIcon(minPix);
    closeButton->setIcon(closePix);

    //设置最小化、关闭按钮在界面的位置
    minButton->setGeometry(width-50,0,25,25);
    closeButton->setGeometry(width-25,0,25,25);
    titleLabel->setGeometry(width-850,0,100,30);
    iconLabel->setGeometry(width-875,5,20,20);

    //设置鼠标移至按钮上的提示信息
    minButton->setToolTip(QString("最小化"));
    closeButton->setToolTip(QString("关闭"));
    titleLabel->setText(QString("终端安全工具"));
    iconLabel->setScaledContents(true);
    iconLabel->setPixmap(iconPix);


    //设置最小化、关闭等按钮的样式
    QString m_style = QString("QToolButton{border:none;background-color:#BADBFC;border-radius:0px;}"
                              "QToolButton:hover{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #F9FCFF,stop:1 #C0DEFC);}"
                              "QToolButton:pressed{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #F9FCFF,stop:1 #C0DEFC);}");
    minButton->setStyleSheet(m_style);
    closeButton->setStyleSheet(m_style);
    titleLabel->setStyleSheet(QString("background-color:transparent;font:10pt 微软雅黑"));
}


//自己实现的窗口拖动操作
void MainWindow::mousePressEvent(QMouseEvent *event)
{
        //当鼠标单击窗体准备拖动时，初始化鼠标在窗体中的相对位置
        mousePosition = event->pos();
        //只对标题栏范围内的鼠标事件进行处理
        if (mousePosition.x()<=pos_min_x)
            return;
        if ( mousePosition.x()>=pos_max_x)
            return;
        if (mousePosition.y()<=pos_min_y )
            return;
        if (mousePosition.y()>=pos_max_y)
            return;
        isMousePressed = true;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ( isMousePressed==true )
    {
        QPoint movePot = event->globalPos() - mousePosition;
        //move是移动的位置是相对于全局而言(即屏幕)
        move(movePot);
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    isMousePressed=false;
}

void MainWindow::on_actionMinimize_triggered()
{
    if( windowState() != Qt::WindowMinimized ){
        setWindowState( Qt::WindowMinimized );
    }

}
void MainWindow::on_actionClose_triggered()
{
    //系统自定义的窗口关闭函数
    close();
}

void MainWindow::hide_slot()
{
    tray->hide();
}

void MainWindow::initSysTrayIcon()
{
    tray=new QSystemTrayIcon(this);//初始化托盘对象tray
    tray->setIcon(QIcon(QPixmap(":/button/shield.png")));//设定托盘图标，引号内是自定义的png图片路径
    tray->setToolTip(QString("终端安全工具"));
    tray->show();//让托盘图标显示在系统托盘上
    QObject::connect(tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(TrayIconAction(QSystemTrayIcon::ActivationReason)));//连接信号与槽，实现单击图标恢复窗口的功能，槽是自定义的槽

   //***初始化托盘菜单及功能***
    menu=new QMenu(this);//初始化菜单
    reset=new QAction(this);//初始化恢复窗口
    reset->setText(QString("显示窗口"));
    QObject::connect(reset,SIGNAL(triggered()),this,SLOT(showNormal()));//菜单中的显示窗口，单击连接显示窗口

    quit=new QAction(this);//初始化退出程序
    quit->setText(QString("退出程序"));
    QObject::connect(quit,SIGNAL(triggered()),qApp,SLOT(quit()));//菜单中的退出程序，单击连接退出</span>
    //qApp，是Qt自带的demo中的知识点，查了一下文档，qApp是Qt中所有app的指针，关闭它就可以关闭当前的程序</span>
   //之所以不用this，close()，是由于软件要求关闭改为最小化到托盘，所以close()的功能已经不再是关闭窗口的功能，所以要另寻方法

    hide=new QAction(this);
    hide->setText(QString("隐藏程序"));
    QObject::connect(hide,SIGNAL(triggered()),this,SLOT(hide_slot()));
    //***将定义好的菜单加入托盘的菜单模块中***
    tray->setContextMenu(menu);
    menu->addAction(reset);
    menu->addAction(hide);
    menu->addAction(quit);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QWidget::hide();//隐藏窗口
    event->ignore();//忽略关闭事件
}

//最小化隐藏程序
//void MainWindow::changeEvent(QEvent *e)
//{
//    if((e->type()==QEvent::WindowStateChange)&&this->isMinimized())
//    {
//        QWidget::hide();
//    }
//}

//***托盘图标槽***
void MainWindow::TrayIconAction(QSystemTrayIcon::ActivationReason reason)
//参数是Qt的保留字，表示对托盘图标的操作，该槽函数功能只实现了单击功能，可以实现其他功能比如双击、中击，具体可查文档或者Qt自带demo(关键字tray)
{
    if (reason==QSystemTrayIcon::Trigger)
        this->showNormal();//如果对图标进行单击，则显示正常大小的窗口
}

void MainWindow::initStyle()
{
    QFile file(":/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void MainWindow::buttonInit()
{
    ui->mainToolButton->setStyleSheet(toolButtonStyle);
    ui->mainToolButton->setChecked(true);
    ui->sysToolButton->setStyleSheet(toolButtonStyle);
    ui->docuToolButton->setStyleSheet(toolButtonStyle);
    ui->ployToolButton->setStyleSheet(toolButtonStyle);
    ui->funcToolButton->setStyleSheet(toolButtonStyle);

    ui->scanButton->setStyleSheet(buttonStyle_3);
    ui->updateReportButton->setStyleSheet(buttonStyle_3);

    ui->homeBackButton->setStyleSheet(buttonStyle_3);

    ui->sysButton_1->setStyleSheet(buttonStyle_2);
    ui->sysButton_2->setStyleSheet(buttonStyle);
    ui->sysButton_3->setStyleSheet(buttonStyle);
    ui->sysButton_4->setStyleSheet(buttonStyle);
    ui->sysButton_5->setStyleSheet(buttonStyle);

    ui->budingButton->setStyleSheet(buttonStyle_3);
    ui->baojingButton->setStyleSheet(buttonStyle_3);
    ui->yingjianButton->setStyleSheet(buttonStyle_3);
    ui->muluButton->setStyleSheet(buttonStyle_3);
    ui->peizhiButton->setStyleSheet(buttonStyle_3);

    ui->budingBackButton->setStyleSheet(buttonStyle_3);
    ui->budingCheckButton->setStyleSheet(buttonStyle_3);
    ui->baojingBackButton->setStyleSheet(buttonStyle_3);
    ui->baojingCheckButton->setStyleSheet(buttonStyle_3);
    ui->yingjianBackButton->setStyleSheet(buttonStyle_3);
    ui->yingjianCheckButton->setStyleSheet(buttonStyle_3);
    ui->muluBackButton->setStyleSheet(buttonStyle_3);
    ui->muluCheckButton->setStyleSheet(buttonStyle_3);
    ui->peizhiBackButton->setStyleSheet(buttonStyle_3);
    ui->peizhiCheckButton->setStyleSheet(buttonStyle_3);

    ui->budingCheckButton->setVisible(false);
    ui->baojingCheckButton->setVisible(false);
    ui->yingjianCheckButton->setVisible(false);
    ui->muluCheckButton->setVisible(false);
    ui->peizhiCheckButton->setVisible(false);

    ui->wailianButton->setStyleSheet(buttonStyle_2);
    ui->wjczButton->setStyleSheet(buttonStyle);
    ui->wjnrButton->setStyleSheet(buttonStyle);
    ui->ydjzButton->setStyleSheet(buttonStyle);
    ui->jxwjButton->setStyleSheet(buttonStyle);

    ui->wlDeepCheckButton->setStyleSheet(buttonStyle_3);
    ui->wlMildCheckButton->setStyleSheet(buttonStyle_3);
    ui->wjczMildCheckButton_2->setStyleSheet(buttonStyle_3);
    ui->wjczDeepCheckButton_2->setStyleSheet(buttonStyle_3);
    ui->wjnrDeepCheckButton->setStyleSheet(buttonStyle_3);
    ui->wjnrMildCheckButton->setStyleSheet(buttonStyle_3);
    ui->ydjzDeepCheckButton->setStyleSheet(buttonStyle_3);
    ui->ydjzMildCheckButton->setStyleSheet(buttonStyle_3);
    ui->jxwjCheckButton->setStyleSheet(buttonStyle_3);
    ui->hjBackButton->setStyleSheet(buttonStyle_3);

    ui->wjnrLineEdit->setStyleSheet(textEditStyle);

    ui->clshButton->setStyleSheet(buttonStyle_3);
    ui->clshBackButton->setStyleSheet(buttonStyle_4);

    ui->htmlButton->setStyleSheet(buttonStyle_3);

    ui->htmlBackButton->setStyleSheet(buttonStyle_3);

    QString mStyle = QString("QPushButton{border:none;color:black;padding:5px;min-height:15px;font: 8pt 微软雅黑;"
                                           "border-radius:10px;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #FAFAF9,stop:1 #F1F1F1);}"
                                           "QPushButton:hover{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #F1F1F1,stop:1 #DCDCDC);}"
                                           "QPushButton:pressed{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #F1F1F1,stop:1 #DCDCDC);}");

    ui->outHtmlButton->setStyleSheet(mStyle);

    ui->wailianBackButton->setStyleSheet(buttonStyle_3);
    ui->wjczBackButton->setStyleSheet(buttonStyle_3);
    ui->wjnrBackButton->setStyleSheet(buttonStyle_3);
    ui->ydjzBackButton->setStyleSheet(buttonStyle_3);
    ui->jxwjBackButton->setStyleSheet(buttonStyle_3);

    ui->chooseDirButton->setStyleSheet(buttonStyle_3);
    ui->deepTaskStopButton->setStyleSheet(buttonStyle_3);

    ui->budingButton_2->setStyleSheet(buttonStyle_3);
    ui->yingjianButton_2->setStyleSheet(buttonStyle_3);
    ui->muluButton_2->setStyleSheet(buttonStyle_3);
    ui->wailianButton_2->setStyleSheet(buttonStyle_3);
    ui->ydjzButton_2->setStyleSheet(buttonStyle_3);
    ui->ydjzButton_3->setStyleSheet(buttonStyle_3);
}

bool MainWindow::ifTaskRun()
{
    if(isChecked!=1||isMainRun!=0||isSysRun!=0||isClRun!=0)
    {
        return true;
    }
    return false;
}

void MainWindow::statusInit()
{
    ui->statusBar->setSizeGripEnabled(false);
    ui->statusBar->setStyleSheet("QStatusBar::item{border: 0px;}"
                                 "QStatusBar{background-color:rgb(55,80,102);}");

    QString localVersion;
    QString localPath = qApp->applicationDirPath();
    localPath+="\\config.ini";
    QSettings settings(localPath,QSettings::IniFormat);
    localVersion = settings.value("version/LocalVersion").toString();

    stateLabel = new QLabel(QString("当前版本:%1").arg(localVersion),this);
    stateLabel->setAlignment(Qt::AlignTop);
    stateLabel->setStyleSheet("QLabel{background-color:rgb(55,80,102);color:white;}");
    stateLabel->setMinimumSize(stateLabel->sizeHint());
    ui->statusBar->addWidget(stateLabel);

    QString strVersion ;
    if(isConnected==NET_MSG_CFG_POLICY)
    {
        strVersion = QString("已连接服务器");
    }
    else
    {
        strVersion = QString("未连接服务器");
    }

    verLabel = new QLabel(strVersion,this);
    verLabel->setAlignment(Qt::AlignTop);
    verLabel->setMinimumSize(verLabel->sizeHint());
    verLabel->setStyleSheet("QLabel{background-color:rgb(55,80,102);color:white;}");
    ui->statusBar->addPermanentWidget(verLabel);
    QLabel *noneLabel = new QLabel(" ",this);
    noneLabel->setStyleSheet("QLabel{background-color:rgb(55,80,102);color:white;}");
    ui->statusBar->addPermanentWidget(noneLabel);
}

void MainWindow::updateProgressbar()
{
    if(num!=99)
    {
        m_timer->stop();
        return;
    }
    if(m_persent < 85){
        m_persent += 1;
        ui->mainLabel_1->setText(scanProject);
    }
    else if(m_persent>=85&&m_persent<99)
    {
        m_persent += 1;
        ui->mainLabel_1->setText(QString("正在生成报告"));
    }
    if(isChecked==1&&m_persent==99)
    {
        m_persent = 100;
//        isChecked = 0;
        ui->mainLabel_1->setText(QString("体检已完成"));
    }
    ui->ringsBar->setPersent(m_persent);
    if(m_persent==100)
    {
        isMainRun=0;
        ui->scanButton->setEnabled(true);
        m_timer->stop();
        m_persent = 0;
        resultShow();
        ui->stackedWidget->setCurrentIndex(6);
        mainIndex=6;
    }
}

void MainWindow::updateBudingProgress()
{
    ui->budingRings->setPersent(0);
    if(m_persent_2<99)
    {
        m_persent_2+=1;
    }
    if(isChecked==1&&m_persent_2==99)
    {
        m_persent_2=100;
//        isChecked=0;
    }
    if(mKind==0)
    {
        ui->budingRings->setPersent(m_persent_2);
    }
    else if(mKind==1)
    {
        ui->baojingRings->setPersent(m_persent_2);
    }
    else if(mKind==2)
    {
        ui->yingjianRings->setPersent(m_persent_2);
    }
    else if(mKind==3)
    {
        ui->muluRings->setPersent(m_persent_2);
    }
    else if(mKind==4)
    {
        ui->peizhiRings->setPersent(m_persent_2);
    }
    if(m_persent_2>=99&&isChecked==1)    //注意：将来需要改成100！！！
    {
        buding_timer->stop();
        isSysRun=0;
        m_persent_2 = 0;
        if(mKind==0)     //系统补丁扫描
        {
            ui->budingRings->setPersent(100);
            ui->budingBackButton->setEnabled(true);
            ui->sysLabel_1->setText("    扫描已完成");
            budingTableShow();
        }
        else if(mKind==1)   //已安装程序
        {
            ui->baojingRings->setPersent(100);
            ui->baojingBackButton->setEnabled(true);
            ui->sysLabel_2->setText("    扫描已完成");
            chengxuTableShow();
        }
        else if(mKind==2)   //硬件信息
        {
            ui->yingjianRings->setPersent(100);
            ui->yingjianBackButton->setEnabled(true);
            ui->sysLabel_3->setText("    扫描已完成");
            yingjianTableShow();
        }
        else if(mKind==3)    //共享目录
        {
            ui->muluRings->setPersent(100);
            ui->muluBackButton->setEnabled(true);
            ui->sysLabel_4->setText("    扫描已完成");
            gongxiangTableShow();
        }
        else if(mKind==4)    //系统配置
        {
            ui->peizhiRings->setPersent(100);
            ui->peizhiBackButton->setEnabled(true);
            ui->sysLabel_5->setText("    扫描已完成");
            peizhiTableShow();
        }
    }
}

void MainWindow::on_mainToolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(mainIndex);
    ui->mainToolButton->setChecked(true);
    ui->sysToolButton->setChecked(false);
    ui->docuToolButton->setChecked(false);
    ui->ployToolButton->setChecked(false);
    ui->funcToolButton->setChecked(false);
}

void MainWindow::on_sysToolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->mainToolButton->setChecked(false);
    ui->sysToolButton->setChecked(true);
    ui->docuToolButton->setChecked(false);
    ui->ployToolButton->setChecked(false);
    ui->funcToolButton->setChecked(false);
}

void MainWindow::on_docuToolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->mainToolButton->setChecked(false);
    ui->sysToolButton->setChecked(false);
    ui->docuToolButton->setChecked(true);
    ui->ployToolButton->setChecked(false);
    ui->funcToolButton->setChecked(false);
}


void MainWindow::on_ployToolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(clIndex);
    ui->mainToolButton->setChecked(false);
    ui->sysToolButton->setChecked(false);
    ui->docuToolButton->setChecked(false);
    ui->ployToolButton->setChecked(true);
    ui->funcToolButton->setChecked(false);
}

void MainWindow::on_funcToolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(reportIndex);
    ui->mainToolButton->setChecked(false);
    ui->sysToolButton->setChecked(false);
    ui->docuToolButton->setChecked(false);
    ui->ployToolButton->setChecked(false);
    ui->funcToolButton->setChecked(true);
}

void MainWindow::on_scanButton_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
#endif
    if(ifTaskRun())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("已有扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else
    {
        ui->scanButton->setEnabled(false);
        ui->imageLabel->setVisible(false);
        ui->ringsBar->setVisible(true);
        m_persent = 0;
        isMainRun=1;
        m_timer->start(50);
        num = 99;
        //connect(render,SIGNAL(refresh()),this,SLOT(updateProgressbar()));
        render->test();
    }
}

void MainWindow::on_sysButton_1_clicked()
{
    ui->sysStackedWidget->setCurrentIndex(mIndex);
    ui->sysButton_1->setStyleSheet(buttonStyle_2);
    ui->sysButton_2->setStyleSheet(buttonStyle);
    ui->sysButton_3->setStyleSheet(buttonStyle);
    ui->sysButton_4->setStyleSheet(buttonStyle);
    ui->sysButton_5->setStyleSheet(buttonStyle);
}

void MainWindow::on_sysButton_2_clicked()
{
    ui->sysStackedWidget->setCurrentIndex(mIndex_2);
    ui->sysButton_1->setStyleSheet(buttonStyle);
    ui->sysButton_2->setStyleSheet(buttonStyle_2);
    ui->sysButton_3->setStyleSheet(buttonStyle);
    ui->sysButton_4->setStyleSheet(buttonStyle);
    ui->sysButton_5->setStyleSheet(buttonStyle);
}

void MainWindow::on_sysButton_3_clicked()
{
    ui->sysStackedWidget->setCurrentIndex(mIndex_3);
    ui->sysButton_1->setStyleSheet(buttonStyle);
    ui->sysButton_2->setStyleSheet(buttonStyle);
    ui->sysButton_3->setStyleSheet(buttonStyle_2);
    ui->sysButton_4->setStyleSheet(buttonStyle);
    ui->sysButton_5->setStyleSheet(buttonStyle);
}

void MainWindow::on_sysButton_4_clicked()
{
    ui->sysStackedWidget->setCurrentIndex(mIndex_4);
    ui->sysButton_1->setStyleSheet(buttonStyle);
    ui->sysButton_2->setStyleSheet(buttonStyle);
    ui->sysButton_3->setStyleSheet(buttonStyle);
    ui->sysButton_4->setStyleSheet(buttonStyle_2);
    ui->sysButton_5->setStyleSheet(buttonStyle);
}

void MainWindow::on_sysButton_5_clicked()
{
    ui->sysStackedWidget->setCurrentIndex(mIndex_5);
    ui->sysButton_1->setStyleSheet(buttonStyle);
    ui->sysButton_2->setStyleSheet(buttonStyle);
    ui->sysButton_3->setStyleSheet(buttonStyle);
    ui->sysButton_4->setStyleSheet(buttonStyle);
    ui->sysButton_5->setStyleSheet(buttonStyle_2);
}

QString getTaskName(int kind)
{
    QString strKind;
    if(kind==1)
    {
        strKind=QString("正在进行系统补丁扫描");
    }
    else if(kind==2)
    {
        strKind=QString("正在检查已安装程序");
    }
    else if(kind==3)
    {
        strKind=QString("正在检查系统硬件信息");
    }
    else if(kind==4)
    {
        strKind=QString("正在检查共享目录");
    }
    else if(kind==5)
    {
        strKind=QString("正在检查系统配置");
    }
    return strKind;
}


void MainWindow::on_budingButton_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
#endif
    if(isSysRun!=0)
    {
        QString strTitle = QString("提示");
        QString strMsg = getTaskName(isSysRun);
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else if(ifTaskRun())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("已有扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else
    {
        num=0;
        isSysRun=1;
        ui->budingRings->setPersent(0);
        ui->sysStackedWidget->setCurrentIndex(1);
        m_persent_2 = 0;
        mIndex=1;
        mKind=0;
        ui->budingBackButton->setEnabled(false);
//        isChecked=0;
        ui->budingRings->setVisible(true);
        ui->budingTableWidget->setVisible(false);
        //connect(render,SIGNAL(refresh()),this,SLOT(updateBudingProgress()));
        render->test();
        buding_timer->start(100);
    }
}

void MainWindow::on_budingBackButton_clicked()
{
    isSysRun=0;
    ui->sysStackedWidget->setCurrentIndex(0);
    mIndex=0;
}

void MainWindow::on_budingCheckButton_clicked()
{
    ui->sysStackedWidget->setCurrentIndex(1);
    mIndex=1;
}

void MainWindow::on_baojingButton_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
#endif
    if(isSysRun!=0)
    {
        QString strTitle = QString("提示");
        QString strMsg = getTaskName(isSysRun);
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else if(ifTaskRun())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("已有扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else
    {
        isSysRun=2;
        ui->budingRings->setPersent(0);
        ui->sysStackedWidget->setCurrentIndex(3);
        m_persent_2 = 0;
        buding_timer->start(15);
        mKind=1;
        mIndex_2=3;
        ui->baojingBackButton->setEnabled(false);
        ui->baojingRings->setVisible(true);
        ui->chengxuTableWidget->setVisible(false);

        num=1;
//        connect(render,SIGNAL(refresh()),this,SLOT(updateBudingProgress()));
        render->test();
    }
}

void MainWindow::on_baojingCheckButton_clicked()
{
    ui->sysStackedWidget->setCurrentIndex(3);
    mIndex_2=3;
}

void MainWindow::on_baojingBackButton_clicked()
{
    isSysRun=0;
    ui->sysStackedWidget->setCurrentIndex(2);
    mIndex_2=2;
}

void MainWindow::on_yingjianButton_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
#endif
    if(isSysRun!=0)
    {
        QString strTitle = QString("提示");
        QString strMsg = getTaskName(isSysRun);
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else if(ifTaskRun())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("已有扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else
    {
        isSysRun=3;
        ui->budingRings->setPersent(0);
        ui->sysStackedWidget->setCurrentIndex(5);
        m_persent_2 = 0;
        buding_timer->start(15);
        mKind=2;
        mIndex_3=5;
        ui->yingjianBackButton->setEnabled(false);
        ui->yingjianRings->setVisible(true);
        ui->scrollArea->setVisible(false);

        num=2;
//        connect(render,SIGNAL(refresh()),this,SLOT(updateBudingProgress()));
        render->test();
    }
}

void MainWindow::on_yingjianCheckButton_clicked()
{
    ui->sysStackedWidget->setCurrentIndex(5);
    mIndex_3=5;
}

void MainWindow::on_yingjianBackButton_clicked()
{
    isSysRun=0;
    ui->sysStackedWidget->setCurrentIndex(4);
    mIndex_3=4;
}

bool MainWindow::ifCennected()
{
    if(isConnected!=NET_MSG_CFG_POLICY)  //连接失败
    {
        verLabel->setText(QString("未连接服务器"));
        QString strTitle = QString("提示");
        QString strMsg = QString("未连接服务器");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return false;
    }
    else
    {
        verLabel->setText(QString("已连接服务器"));
        return true;
    }
}

void MainWindow::on_muluButton_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
#endif
    if(isSysRun!=0)
    {
        QString strTitle = QString("提示");
        QString strMsg = getTaskName(isSysRun);
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else if(ifTaskRun())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("已有扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else
    {
        isSysRun=4;
        ui->budingRings->setPersent(0);
        ui->sysStackedWidget->setCurrentIndex(7);
        m_persent_2 = 0;
        buding_timer->start(15);
        mKind=3;
        mIndex_4=7;
        ui->muluBackButton->setEnabled(false);
        ui->muluRings->setVisible(true);
        ui->gongxiangTableWidget->setVisible(false);

        num=3;
//        connect(render,SIGNAL(refresh()),this,SLOT(updateBudingProgress()));
        render->test();
    }
}

void MainWindow::on_muluCheckButton_clicked()
{
    ui->sysStackedWidget->setCurrentIndex(7);
    mIndex_4=7;
}

void MainWindow::on_muluBackButton_clicked()
{
    isSysRun=0;
    ui->sysStackedWidget->setCurrentIndex(6);
    mIndex_4=6;
}

void MainWindow::on_peizhiButton_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
#endif
    if(isSysRun!=0)
    {
        QString strTitle = QString("提示");
        QString strMsg = getTaskName(isSysRun);
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else if(ifTaskRun())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("已有扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else
    {
        isSysRun=5;
        ui->budingRings->setPersent(0);
        ui->sysStackedWidget->setCurrentIndex(9);
        m_persent_2 = 0;
        buding_timer->start(15);
        mKind=4;
        mIndex_5=9;
        ui->peizhiBackButton->setEnabled(false);
        ui->peizhiTableWidget->setVisible(false);
        ui->peizhiRings->setVisible(true);

        num=4;
//        connect(render,SIGNAL(refresh()),this,SLOT(updateBudingProgress()));
        render->test();
    }
}

void MainWindow::on_peizhiCheckButton_clicked()
{
    ui->sysStackedWidget->setCurrentIndex(9);
    mIndex_5=9;
}

void MainWindow::on_peizhiBackButton_clicked()
{
    isSysRun=0;
    ui->sysStackedWidget->setCurrentIndex(8);
    mIndex_5=8;
}

//痕迹扫描相关

void MainWindow::on_wailianButton_clicked()
{
    ui->henjiWidget->setCurrentIndex(hjIndex_1);
    ui->wailianButton->setStyleSheet(buttonStyle_2);
    ui->wjczButton->setStyleSheet(buttonStyle);
    ui->wjnrButton->setStyleSheet(buttonStyle);
    ui->ydjzButton->setStyleSheet(buttonStyle);
    ui->jxwjButton->setStyleSheet(buttonStyle);
}

void MainWindow::on_wjczButton_clicked()
{
    ui->henjiWidget->setCurrentIndex(hjIndex_2);
    ui->wailianButton->setStyleSheet(buttonStyle);
    ui->wjczButton->setStyleSheet(buttonStyle_2);
    ui->wjnrButton->setStyleSheet(buttonStyle);
    ui->ydjzButton->setStyleSheet(buttonStyle);
    ui->jxwjButton->setStyleSheet(buttonStyle);
}

void MainWindow::on_wjnrButton_clicked()
{
    ui->henjiWidget->setCurrentIndex(hjIndex_3);
    ui->wailianButton->setStyleSheet(buttonStyle);
    ui->wjczButton->setStyleSheet(buttonStyle);
    ui->wjnrButton->setStyleSheet(buttonStyle_2);
    ui->ydjzButton->setStyleSheet(buttonStyle);
    ui->jxwjButton->setStyleSheet(buttonStyle);
}

void MainWindow::on_ydjzButton_clicked()
{
    ui->henjiWidget->setCurrentIndex(hjIndex_4);
    ui->wailianButton->setStyleSheet(buttonStyle);
    ui->wjczButton->setStyleSheet(buttonStyle);
    ui->wjnrButton->setStyleSheet(buttonStyle);
    ui->ydjzButton->setStyleSheet(buttonStyle_2);
    ui->jxwjButton->setStyleSheet(buttonStyle);
}

void MainWindow::on_jxwjButton_clicked()
{
    ui->henjiWidget->setCurrentIndex(hjIndex_5);
    ui->wailianButton->setStyleSheet(buttonStyle);
    ui->wjczButton->setStyleSheet(buttonStyle);
    ui->wjnrButton->setStyleSheet(buttonStyle);
    ui->ydjzButton->setStyleSheet(buttonStyle);
    ui->jxwjButton->setStyleSheet(buttonStyle_2);
}

void MainWindow::updateHenjiProgress()
{

    if(ifUsbDeepCheck||ifIntDeepCheck||ifWjczDeepCheck)
    {
        if(m_persent_3<99&&gTotalSize>0)
        {
            m_persent_3 = (int)(((double)gCurrSize/gTotalSize)*100);
        }
        else if(m_persent_3<99&&gTotalSize==0)
        {
            m_persent_3=0;
        }
    }
    else
    {
        if(m_persent_3 < 99){
            m_persent_3 += 1;
        }
    }

    ui->henjiRings->setPersent(m_persent_3);
    if(ifUsbFinish)   //usb深度检查是否结束
    {
        m_persent_3 = 0;
        ifUsbFinish = false;
        ifUsbDeepCheck = false;
        ui->henjiRings->setPersent(100);
        ui->hjBackButton->setEnabled(true);
        ui->deepTaskStopButton->setEnabled(true);
        ui->deepTaskStopButton->setVisible(false);
        if(henji_timer->isActive())
        {
            henji_timer->stop();
        }
        gCurrSize = 0;
        gTotalSize = 0;

        isRun=0;
        hjIndex_4=9;
        ui->wailianButton->setStyleSheet(buttonStyle);
        ui->wjczButton->setStyleSheet(buttonStyle);
        ui->wjnrButton->setStyleSheet(buttonStyle);
        ui->ydjzButton->setStyleSheet(buttonStyle_2);
        ui->jxwjButton->setStyleSheet(buttonStyle);
        ui->henjiWidget->setCurrentIndex(9);
        ydjzDeepTableShow();
    }
    else if(ifIntFinish)      //违规外联深度检查
    {
        m_persent_3 = 0;
        ifIntFinish = false;
        ifIntDeepCheck = false;
        ui->henjiRings->setPersent(100);
        ui->hjBackButton->setEnabled(true);
        ui->deepTaskStopButton->setEnabled(true);
        ui->deepTaskStopButton->setVisible(false);
        if(henji_timer->isActive())
        {
            henji_timer->stop();
        }
        gCurrSize = 0;
        gTotalSize = 0;
        ui->wailianButton->setStyleSheet(buttonStyle_2);
        ui->wjczButton->setStyleSheet(buttonStyle);
        ui->wjnrButton->setStyleSheet(buttonStyle);
        ui->ydjzButton->setStyleSheet(buttonStyle);
        ui->jxwjButton->setStyleSheet(buttonStyle);

        ui->henjiWidget->setCurrentIndex(6);
        wailianDeepTableShow();
        isRun=0;
        hjIndex_1=6;

    }
    else if(wjczFinish)
    {
        wjczFinish = false;
        ifWjczDeepCheck = false;
        m_persent_3 = 0;
        ui->henjiRings->setPersent(100);
        ui->hjBackButton->setEnabled(true);
        ui->deepTaskStopButton->setEnabled(true);
        ui->deepTaskStopButton->setVisible(false);
        if(henji_timer->isActive())
        {
            henji_timer->stop();
        }
        gCurrSize = 0;
        gTotalSize = 0;

        ui->wailianButton->setStyleSheet(buttonStyle);
        ui->wjczButton->setStyleSheet(buttonStyle_2);
        ui->wjnrButton->setStyleSheet(buttonStyle);
        ui->ydjzButton->setStyleSheet(buttonStyle);
        ui->jxwjButton->setStyleSheet(buttonStyle);
        ui->henjiWidget->setCurrentIndex(7);
        wjczTableShow();
        isRun=0;
        hjIndex_2=7;
    }
    else if(m_persent_3==99&&isChecked==1)  //注意：将来需要改成100
    {
        m_persent_3 = 0;
        ui->henjiRings->setPersent(100);
        ui->hjBackButton->setEnabled(true);
        if(henji_timer->isActive())
        {
            henji_timer->stop();
        }
        if(isRun==1)     //违规外联
        {
            ui->henjiWidget->setCurrentIndex(6);
            ui->wailianButton->setStyleSheet(buttonStyle_2);
            ui->wjczButton->setStyleSheet(buttonStyle);
            ui->wjnrButton->setStyleSheet(buttonStyle);
            ui->ydjzButton->setStyleSheet(buttonStyle);
            ui->jxwjButton->setStyleSheet(buttonStyle);
            wailianTableShow();
            isRun=0;
            hjIndex_1=6;
        }
        else if(isRun==2)    //文件操作轻度检查
        {
            ui->wailianButton->setStyleSheet(buttonStyle);
            ui->wjczButton->setStyleSheet(buttonStyle_2);
            ui->wjnrButton->setStyleSheet(buttonStyle);
            ui->ydjzButton->setStyleSheet(buttonStyle);
            ui->jxwjButton->setStyleSheet(buttonStyle);
            ui->henjiWidget->setCurrentIndex(7);
            wjczTableShow();
            isRun=0;
            hjIndex_2=7;
        }
        else if(isRun==3)    //文件内容
        {
            ui->wailianButton->setStyleSheet(buttonStyle);
            ui->wjczButton->setStyleSheet(buttonStyle);
            ui->wjnrButton->setStyleSheet(buttonStyle_2);
            ui->ydjzButton->setStyleSheet(buttonStyle);
            ui->jxwjButton->setStyleSheet(buttonStyle);
            ui->henjiWidget->setCurrentIndex(8);
            isRun=0;
            hjIndex_3=8;
            wjnrTableShow();
        }
        else if(isRun==4)     //移动介质
        {
            isRun=0;
            hjIndex_4=9;
            ui->wailianButton->setStyleSheet(buttonStyle);
            ui->wjczButton->setStyleSheet(buttonStyle);
            ui->wjnrButton->setStyleSheet(buttonStyle);
            ui->ydjzButton->setStyleSheet(buttonStyle_2);
            ui->jxwjButton->setStyleSheet(buttonStyle);
            ui->henjiWidget->setCurrentIndex(9);
            ydjzTableShow();
        }
        else if(isRun==5)
        {
            isRun=0;
            hjIndex_5=10;
            ui->henjiWidget->setCurrentIndex(10);
        }
        else
        {
            isRun = 0;
        }
    }
}

QString taskKind(int kind)
{
    QString strKind;
    if(kind==1)
    {
        strKind = QString("正在进行违规外联检查");
    }
    else if(kind==2)
    {
        strKind = QString("正在进行文件操作痕迹检查");
    }
    else if(kind==3)
    {
        strKind = QString("正在进行文件内容检查");
    }
    else if(kind==4)
    {
        strKind = QString("正在进行移动介质使用检查");
    }
    else if(kind==5)
    {
        strKind = QString("正在进行镜像文件检查");
    }
    return strKind;
}

void MainWindow::on_wlMildCheckButton_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
#endif
    if(isRun!=0)
    {
        QString strTitle = QString("提示");
        QString strMsg = taskKind(isRun);
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else if(ifTaskRun())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("已有扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else
    {
        isRun=1;
        ui->henjiRings->setPersent(0);
        ui->henjiWidget->setCurrentIndex(1);
        hjIndex_1=1;
        m_persent_3=0;
        hjKind=0;
        ui->hjBackButton->setEnabled(false);

        num = 5;
//        connect(render,SIGNAL(refresh()),this,SLOT(updateHenjiProgress()));
        render->test();
        henji_timer->start(50);
    }
}

void MainWindow::on_wlDeepCheckButton_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
#endif
    if(!IsAdmin())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("深度扫描任务需要管理员权限");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    QString strTitle = QString("警告");
    QString strMsg = QString("深度检查花费时间较长，确定继续吗？");
    QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, strMsg, QMessageBox::Ok|QMessageBox::No,this);
    if(NULL!=WrrMsg->button(QMessageBox::Ok))
    {
        WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
    }
    if(NULL!=WrrMsg->button(QMessageBox::No))
    {
        WrrMsg->button(QMessageBox::No)->setText(QString("取消"));
    }
    int ok = WrrMsg->exec();
    if(ok == QMessageBox::No)
    {
        return;
    }
    else
    {
        if(isRun!=0)
        {
            QString strTitle = QString("提示");
            QString strMsg = taskKind(isRun);
            QString showMsg = "<font color='black'>"+strMsg+"</font>";
            QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
            WrrMsg->setIconPixmap(pix);
            if(NULL!=WrrMsg->button(QMessageBox::Ok))
            {
                WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
            }
            WrrMsg->exec();
            return;
        }
        else if(ifTaskRun())
        {
            QString strTitle = QString("提示");
            QString strMsg = QString("已有扫描任务正在运行");
            QString showMsg = "<font color='black'>"+strMsg+"</font>";
            QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
            WrrMsg->setIconPixmap(pix);
            if(NULL!=WrrMsg->button(QMessageBox::Ok))
            {
                WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
            }
            WrrMsg->exec();
            return;
        }
        else
        {
            isRun=1;
            ui->henjiWidget->setCurrentIndex(1);
            hjIndex_1=1;
            m_persent_3=0;
            hjKind=0;
            ui->hjBackButton->setEnabled(false);
            ui->deepTaskStopButton->setVisible(true);

            ifIntDeepCheck = true;
            num = 13;
            render->test();
            henji_timer->start(15);
        }
    }
}

void MainWindow::on_hjBackButton_clicked()
{
    if(hjKind==0)
    {
        ui->henjiWidget->setCurrentIndex(0);
        hjIndex_1=0;
    }
    else if(hjKind==1)
    {
        ui->henjiWidget->setCurrentIndex(2);
        hjIndex_2=2;
    }
    else if(hjKind==2)
    {
        ui->henjiWidget->setCurrentIndex(3);
        hjIndex_3=3;
    }
    else if(hjKind==3)
    {
        ui->henjiWidget->setCurrentIndex(4);
        hjIndex_4=4;
    }
    else if(hjKind==4)
    {
        ui->henjiWidget->setCurrentIndex(5);
        hjIndex_5=5;
    }
}


void MainWindow::on_wjczMildCheckButton_2_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
#endif
    if(isRun!=0)
    {
        QString strTitle = QString("提示");
        QString strMsg = taskKind(isRun);
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else if(ifTaskRun())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("已有扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else
    {
        isRun=2;
        ui->henjiRings->setPersent(0);
        m_persent_3=0;
        ui->henjiWidget->setCurrentIndex(1);
        hjIndex_2=1;      
        hjKind=1;
        ui->hjBackButton->setEnabled(false);

        num = 14;
//        connect(render,SIGNAL(refresh()),this,SLOT(updateBudingProgress()));
        render->test();
        henji_timer->start(50);
    }
}

void MainWindow::on_wjczDeepCheckButton_2_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
#endif
    if(!IsAdmin())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("深度扫描任务需要管理员权限");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    QString strTitle = QString("警告");
    QString strMsg = QString("深度检查花费时间较长，确定继续吗？");
    QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, strMsg, QMessageBox::Ok|QMessageBox::No,this);
    if(NULL!=WrrMsg->button(QMessageBox::Ok))
    {
        WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
    }
    if(NULL!=WrrMsg->button(QMessageBox::No))
    {
        WrrMsg->button(QMessageBox::No)->setText(QString("取消"));
    }
    int ok = WrrMsg->exec();
    if(ok == QMessageBox::No)
    {
        return;
    }
    else
    {
        if(isRun!=0)
        {
            QString strTitle = QString("提示");
            QString strMsg = taskKind(isRun);
            QString showMsg = "<font color='black'>"+strMsg+"</font>";
            QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
            WrrMsg->setIconPixmap(pix);
            if(NULL!=WrrMsg->button(QMessageBox::Ok))
            {
                WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
            }
            WrrMsg->exec();
            return;
        }
        else if(ifTaskRun())
        {
            QString strTitle = QString("提示");
            QString strMsg = QString("已有扫描任务正在运行");
            QString showMsg = "<font color='black'>"+strMsg+"</font>";
            QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
            WrrMsg->setIconPixmap(pix);
            if(NULL!=WrrMsg->button(QMessageBox::Ok))
            {
                WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
            }
            WrrMsg->exec();
            return;
        }
        else
        {
            isRun=2;
            ui->henjiRings->setPersent(0);
            ui->henjiWidget->setCurrentIndex(1);
            hjIndex_2=1;
            m_persent_3=0;
            hjKind=1;
            ui->hjBackButton->setEnabled(false);
            ui->deepTaskStopButton->setVisible(true);
            ifWjczDeepCheck = true;
            num = 15;
            render->test();

            henji_timer->start(100);
        }
    }
}

void MainWindow::on_wjnrMildCheckButton_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
#endif
    QString strKeyword = ui->wjnrLineEdit->text();
    if(isRun!=0)
    {
        QString strTitle = QString("提示");
        QString strMsg = taskKind(isRun);
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else if(ifTaskRun())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("已有扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else
    {
        QString strTitle = QString("警告");
        QString strMsg = QString("文件内容检查花费时间较长，确定继续吗？");
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, strMsg, QMessageBox::Ok|QMessageBox::No,this);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        if(NULL!=WrrMsg->button(QMessageBox::No))
        {
            WrrMsg->button(QMessageBox::No)->setText(QString("取消"));
        }
        int ok = WrrMsg->exec();
        if(ok == QMessageBox::No)
        {
            return;
        }

        QString strPath = ui->wjmlLineEdit->text();
        keyWordList.clear();
        keyWordList.append(strKeyword);
        keyWordList.append(strPath);

        isRun=3;
        m_persent_3=0;
        ui->henjiRings->setPersent(0);
        ui->henjiWidget->setCurrentIndex(1);
        hjIndex_3=1;            
        hjKind=2;
        ui->hjBackButton->setEnabled(false);

        num = 11;
//        connect(render,SIGNAL(refresh()),this,SLOT(updateBudingProgress()));
        render->test();
        henji_timer->start(1000);
        ifSensTask = true;
    }
}

void MainWindow::on_wjnrDeepCheckButton_clicked()
{
    if(isRun!=0)
    {
        QString strTitle = QString("提示");
        QString strMsg = taskKind(isRun);
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else if(ifTaskRun())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("已有扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else
    {
        isRun=3;
        ui->henjiRings->setPersent(0);
        ui->henjiWidget->setCurrentIndex(1);
        hjIndex_3=1;
        m_persent_3=0;
        henji_timer->start(100);
        hjKind=2;
        ui->hjBackButton->setEnabled(false);
    }
}

void MainWindow::on_ydjzMildCheckButton_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
#endif
    if(isRun!=0)
    {
        QString strTitle = QString("提示");
        QString strMsg = taskKind(isRun);
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else if(ifTaskRun())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("已有扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else
    {
        isRun=4;
        ui->henjiRings->setPersent(0);
        ui->henjiWidget->setCurrentIndex(1);
        hjIndex_4=1;
        m_persent_3=0;
        hjKind=3;
        ui->hjBackButton->setEnabled(false);

        num = 6;
//        connect(render,SIGNAL(refresh()),this,SLOT(updateHenjiProgress()));
        render->test();
        henji_timer->start(15);
    }
}

void MainWindow::on_ydjzDeepCheckButton_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
    if(!IsAdmin())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("深度扫描任务需要管理员权限");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
#endif
    QString strTitle = QString("警告");
    QString strMsg = QString("深度检查花费时间较长，确定继续吗？");
    QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, strMsg, QMessageBox::Ok|QMessageBox::No,this);
    if(NULL!=WrrMsg->button(QMessageBox::Ok))
    {
        WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
    }
    if(NULL!=WrrMsg->button(QMessageBox::No))
    {
        WrrMsg->button(QMessageBox::No)->setText(QString("取消"));
    }
    int ok = WrrMsg->exec();
    if(ok == QMessageBox::No)
    {
        return;
    }
    else
    {
        if(isRun!=0)
        {
            QString strTitle = QString("提示");
            QString strMsg = taskKind(isRun);
            QString showMsg = "<font color='black'>"+strMsg+"</font>";
            QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
            WrrMsg->setIconPixmap(pix);
            if(NULL!=WrrMsg->button(QMessageBox::Ok))
            {
                WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
            }
            WrrMsg->exec();
            return;
        }
        else if(ifTaskRun())
        {
            QString strTitle = QString("提示");
            QString strMsg = QString("已有扫描任务正在运行");
            QString showMsg = "<font color='black'>"+strMsg+"</font>";
            QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
            WrrMsg->setIconPixmap(pix);
            if(NULL!=WrrMsg->button(QMessageBox::Ok))
            {
                WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
            }
            WrrMsg->exec();
            return;
        }
        else
        {
            isRun=4;
            ui->henjiRings->setPersent(0);
            ui->henjiWidget->setCurrentIndex(1);
            hjIndex_4=1;
            m_persent_3=0;

            hjKind=3;
            ui->hjBackButton->setEnabled(false);
            ui->deepTaskStopButton->setVisible(true);

            ifUsbDeepCheck = true;
            num = 12;
//            connect(render,SIGNAL(refresh()),this,SLOT(updateHenjiProgress()));
            render->test();

            henji_timer->start(100);
        }
    }
}

void MainWindow::on_jxwjCheckButton_clicked()
{
    if(isRun!=0)
    {
        QString strTitle = QString("提示");
        QString strMsg = taskKind(isRun);
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else if(ifTaskRun())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("已有扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else
    {
        isRun=5;
        ui->henjiRings->setPersent(0);
        ui->henjiWidget->setCurrentIndex(1);
        hjIndex_5=1;
        m_persent_3=0;
        henji_timer->start(15);
        hjKind=4;
        ui->hjBackButton->setEnabled(false);
    }
}

void MainWindow::on_clshButton_clicked()
{
#ifdef FORTEST
    if(!ifCennected())
    {
        return;
    }
#endif
    if(ifTaskRun())
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("已有扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    else
    {
        isClRun=1;
        clIndex=3;
        ui->dengbaoLabel->setText("正在审核...");
        ui->stackedWidget->setCurrentIndex(3);
        QByteArray loadByte("");
        loadMovie = new QMovie(":/button/load2.gif",loadByte,this);
        ui->loadLabel->setMovie(loadMovie);
        loadMovie->start();

        num = 21;
//        connect(render,SIGNAL(refresh()),this,SLOT(dengbao_task_finish()));
        render->test();
        dengbao_timer->start(20);
        ui->clshBackButton->setEnabled(false);
    }
}

void MainWindow::on_clshBackButton_clicked()
{
    clIndex=4;
    ui->stackedWidget->setCurrentIndex(4);
    ui->dengbaoTableWidget->setVisible(false);
}

void MainWindow::on_homeBackButton_clicked()
{
    QString localVersion;
    QString localPath = qApp->applicationDirPath();
    localPath+="\\config.ini";
    QSettings settings(localPath,QSettings::IniFormat);
    localVersion = settings.value("version/LocalVersion").toString();

    QString strVer = QString("当前版本:%1").arg(localVersion);
    QString curMsg = ui->statusBar->currentMessage();
    if(curMsg==QString("完成"))
    {
        QLabel *stateLabel = new QLabel(QString("当前版本:%1").arg(localVersion),this);
        stateLabel->setAlignment(Qt::AlignTop);
        stateLabel->setStyleSheet("QLabel{background-color:rgb(55,80,102);color:white;}");
        stateLabel->setMinimumSize(stateLabel->sizeHint());
        ui->statusBar->addWidget(stateLabel);
    }
    else
    {
        stateLabel->setText(strVer);
    }
    initMainLabel();
    mainIndex = 0;
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_htmlButton_clicked()
{
//    initAxWidget();
    if(isMainRun!=0)
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }

    num = 888;
    render->test();

    reportIndex=7;
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_htmlBackButton_clicked()
{
    QString localVersion;
    QString localPath = qApp->applicationDirPath();
    localPath+="\\config.ini";
    QSettings settings(localPath,QSettings::IniFormat);
    localVersion = settings.value("version/LocalVersion").toString();

    QString strVer = QString("当前版本:%1").arg(localVersion);
    QString curMsg = ui->statusBar->currentMessage();
    if(curMsg==QString("完成"))
    {
        QLabel *stateLabel = new QLabel(QString("当前版本:%1").arg(localVersion),this);
        stateLabel->setAlignment(Qt::AlignTop);
        stateLabel->setStyleSheet("QLabel{background-color:rgb(55,80,102);color:white;}");
        stateLabel->setMinimumSize(stateLabel->sizeHint());
        ui->statusBar->addWidget(stateLabel);
    }
    else
    {
        stateLabel->setText(strVer);
    }
    reportIndex=5;
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::sltMessageReceived(quint32 mUnum,QByteArray msg)
{
    qDebug()<<"receive message";
    Q_UNUSED(mUnum);
    Q_UNUSED(msg);
    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::WindowStaysOnTopHint;
    this->setWindowFlags(flags);
    show();
    flags &= ~Qt::WindowStaysOnTopHint;
    this->setWindowFlags(flags);
    showNormal();
}

void MainWindow::budingTableShow()
{
    ui->budingTableWidget->setVisible(true);
    ui->budingRings->setVisible(false);
    ui->budingTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置表头
    ui->budingTableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->budingTableWidget->verticalHeader()->setVisible(false);
    ui->budingTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);"
                                                             "}");
    ui->budingTableWidget->setColumnWidth(0,127);
    ui->budingTableWidget->setColumnWidth(1,221);
    ui->budingTableWidget->setColumnWidth(2,127);
    ui->budingTableWidget->setColumnWidth(3,127);
    ui->budingTableWidget->setColumnWidth(4,127);

    ui->budingTableWidget->setRowCount(0);

    QString strNum,StrName,strDate,StrPub,strLevel;
    int row = 0;
    while (NULL != CheckResultResouce::pSystemDefectInfo)
    {
        strNum = QString::fromLocal8Bit(CheckResultResouce::pSystemDefectInfo->defectNum);
        StrName = QString::fromLocal8Bit(CheckResultResouce::pSystemDefectInfo->defectName);
        strDate = QString::fromLocal8Bit(CheckResultResouce::pSystemDefectInfo->defectDate);
        StrPub = QString::fromLocal8Bit(CheckResultResouce::pSystemDefectInfo->strPubdate);
        strLevel = QString::number(CheckResultResouce::pSystemDefectInfo->patchLevel, 10);
        QTableWidgetItem *item_1 = new QTableWidgetItem(strNum);
        QTableWidgetItem *item_2 = new QTableWidgetItem(StrName);
        QTableWidgetItem *item_3 = new QTableWidgetItem(strDate);
        QTableWidgetItem *item_4 = new QTableWidgetItem(StrPub);
        QTableWidgetItem *item_5 = new QTableWidgetItem(strLevel);
        ui->budingTableWidget->insertRow(row);
        ui->budingTableWidget->setItem(row,0,item_1);
        ui->budingTableWidget->setItem(row,1,item_2);
        ui->budingTableWidget->setItem(row,2,item_3);
        ui->budingTableWidget->setItem(row,3,item_4);
        ui->budingTableWidget->setItem(row,4,item_5);
        row++;
        CheckResultResouce::pSystemDefectInfo = CheckResultResouce::pSystemDefectInfo->pNext;
    }
}

void MainWindow::budingResShow()
{
    if((int)CheckResultResouce::softNum==0)
    {
        return;
    }
    ui->chengxuTableWidget_2->horizontalHeader()->setSectionsClickable(false);
    ui->chengxuTableWidget_2->verticalHeader()->setVisible(false);
    ui->chengxuTableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");
    ui->chengxuTableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->chengxuTableWidget_2->setColumnWidth(0,266);
    ui->chengxuTableWidget_2->setColumnWidth(1,116);
    ui->chengxuTableWidget_2->setColumnWidth(2,116);
    ui->chengxuTableWidget_2->setColumnWidth(3,166);
    ui->chengxuTableWidget_2->setColumnWidth(4,366);

    ui->chengxuTableWidget_2->setRowCount(0);

    QString strName,strType,strVersion,strTime,strLocation;
    for (int i = 0; i < (int)CheckResultResouce::softNum; i++)
    {
        if ( (0 == CheckResultResouce::pSoft[i].m_displayname[0])
            && (0 == CheckResultResouce::pSoft[i].m_displayversion[0]) )
            continue;

        strName = QString::fromLocal8Bit(CheckResultResouce::pSoft[i].m_displayname);
        strType = QString::fromLocal8Bit(CheckResultResouce::pSoft[i].szSoftType);
        strVersion = QString::fromLocal8Bit(CheckResultResouce::pSoft[i].m_displayversion);
        strTime = QString::fromLocal8Bit(CheckResultResouce::pSoft[i].m_displaytime);
        strLocation = QString::fromLocal8Bit(CheckResultResouce::pSoft[i].szInstallLocation);

        QTableWidgetItem *item_1 = new QTableWidgetItem(strName);
        QTableWidgetItem *item_2 = new QTableWidgetItem(strType);
        QTableWidgetItem *item_3 = new QTableWidgetItem(strVersion);
        QTableWidgetItem *item_4 = new QTableWidgetItem(strTime);
        QTableWidgetItem *item_5 = new QTableWidgetItem(strLocation);

        ui->chengxuTableWidget_2->insertRow(i);
        ui->chengxuTableWidget_2->setItem(i,0,item_1);
        ui->chengxuTableWidget_2->setItem(i,1,item_2);
        ui->chengxuTableWidget_2->setItem(i,2,item_3);
        ui->chengxuTableWidget_2->setItem(i,3,item_4);
        ui->chengxuTableWidget_2->setItem(i,4,item_5);
    }
}

void MainWindow::chengxuTableShow()
{
    ui->chengxuTableWidget->setVisible(true);
    ui->baojingRings->setVisible(false);
    ui->chengxuTableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->chengxuTableWidget->verticalHeader()->setVisible(false);
    ui->chengxuTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");
    ui->chengxuTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->chengxuTableWidget->setColumnWidth(0,266);
    ui->chengxuTableWidget->setColumnWidth(1,116);
    ui->chengxuTableWidget->setColumnWidth(2,116);
    ui->chengxuTableWidget->setColumnWidth(3,166);
    ui->chengxuTableWidget->setColumnWidth(4,366);

    ui->chengxuTableWidget->setRowCount(0);

    QString strName,strType,strVersion,strTime,strLocation;
    for (int i = 0; i < (int)CheckResultResouce::softNum; i++)
    {
        if ( (0 == CheckResultResouce::pSoft[i].m_displayname[0])
            && (0 == CheckResultResouce::pSoft[i].m_displayversion[0]) )
            continue;

        strName = QString::fromLocal8Bit(CheckResultResouce::pSoft[i].m_displayname);
        strType = QString::fromLocal8Bit(CheckResultResouce::pSoft[i].szSoftType);
        strVersion = QString::fromLocal8Bit(CheckResultResouce::pSoft[i].m_displayversion);
        strTime = QString::fromLocal8Bit(CheckResultResouce::pSoft[i].m_displaytime);
        strLocation = QString::fromLocal8Bit(CheckResultResouce::pSoft[i].szInstallLocation);

        QTableWidgetItem *item_1 = new QTableWidgetItem(strName);
        QTableWidgetItem *item_2 = new QTableWidgetItem(strType);
        QTableWidgetItem *item_3 = new QTableWidgetItem(strVersion);
        QTableWidgetItem *item_4 = new QTableWidgetItem(strTime);
        QTableWidgetItem *item_5 = new QTableWidgetItem(strLocation);

        ui->chengxuTableWidget->insertRow(i);
        ui->chengxuTableWidget->setItem(i,0,item_1);
        ui->chengxuTableWidget->setItem(i,1,item_2);
        ui->chengxuTableWidget->setItem(i,2,item_3);
        ui->chengxuTableWidget->setItem(i,3,item_4);
        ui->chengxuTableWidget->setItem(i,4,item_5);
    }
}
void StorageCapacity2StrL(DWORDLONG storageCapacity, char szBuf[64])
{
    if (storageCapacity > 1024*1024*1024)
    {
        sprintf(szBuf, "%.2llfG", storageCapacity*1.0/(1024*1024*1024));
    }
    else if (storageCapacity > 1024*1024)
    {
        sprintf(szBuf, "%.2llfM", storageCapacity*1.0/(1024*1024));
    }
    else if (storageCapacity > 1024)
    {
        sprintf(szBuf, "%.2llfK", storageCapacity*1.0/(1024));
    }
    else
    {
        sprintf(szBuf, "%uM", storageCapacity);
    }
}

void MainWindow::yingjianTableShow()
{
    ui->yingjianRings->setVisible(false);
    ui->scrollArea->setVisible(true);

    ui->yingjianTableWidget_1->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_1->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_1->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_2->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_2->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_3->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_3->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_3->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_4->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_4->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_4->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_5->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_5->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_5->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_6->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_6->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_6->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_7->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_7->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_7->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->yingjianTableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->yingjianTableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->yingjianTableWidget_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->yingjianTableWidget_5->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->yingjianTableWidget_6->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->yingjianTableWidget_7->setEditTriggers(QAbstractItemView::NoEditTriggers);


    ui->yingjianTableWidget_1->setColumnWidth(0,130);
    ui->yingjianTableWidget_1->setColumnWidth(1,130);
    ui->yingjianTableWidget_1->setColumnWidth(2,300);
    ui->yingjianTableWidget_1->setColumnWidth(3,300);
    ui->yingjianTableWidget_1->setColumnWidth(4,59);
    ui->yingjianTableWidget_1->setColumnWidth(5,59);

    ui->yingjianTableWidget_2->setColumnWidth(0,280);
    ui->yingjianTableWidget_2->setColumnWidth(1,199);
    ui->yingjianTableWidget_2->setColumnWidth(2,199);
    ui->yingjianTableWidget_2->setColumnWidth(3,300);

    ui->yingjianTableWidget_3->setColumnWidth(0,326);
    ui->yingjianTableWidget_3->setColumnWidth(1,326);
    ui->yingjianTableWidget_3->setColumnWidth(2,326);

    ui->yingjianTableWidget_4->setColumnWidth(0,246);
    ui->yingjianTableWidget_4->setColumnWidth(1,244);
    ui->yingjianTableWidget_4->setColumnWidth(2,244);
    ui->yingjianTableWidget_4->setColumnWidth(3,244);

    ui->yingjianTableWidget_5->setColumnWidth(0,489);
    ui->yingjianTableWidget_5->setColumnWidth(1,489);

    ui->yingjianTableWidget_6->setColumnWidth(0,978);

    ui->yingjianTableWidget_7->setColumnWidth(0,389);
    ui->yingjianTableWidget_7->setColumnWidth(1,589);

    ui->yingjianTableWidget_1->setRowCount(0);
    ui->yingjianTableWidget_2->setRowCount(0);
    ui->yingjianTableWidget_3->setRowCount(0);
    ui->yingjianTableWidget_4->setRowCount(0);
    ui->yingjianTableWidget_5->setRowCount(0);
    ui->yingjianTableWidget_6->setRowCount(0);
    ui->yingjianTableWidget_7->setRowCount(0);

    QString cpuBrand,cpuNum,cpuModel,cpuValue,cpuDwnum,cpuPro;
    if(CheckResultResouce::pCpuInfo)
    {
        cpuBrand = QString::fromLocal8Bit(CheckResultResouce::pCpuInfo->brand);
        cpuNum = QString::fromLocal8Bit(CheckResultResouce::pCpuInfo->factoryNumber);
        cpuModel = QString::fromLocal8Bit(CheckResultResouce::pCpuInfo->model);
        cpuValue = QString::fromLocal8Bit(CheckResultResouce::pCpuInfo->parameterValue);
        cpuDwnum = QString::number(CheckResultResouce::pCpuInfo->dwNumberOfCpu,10);
        cpuPro = QString::number(CheckResultResouce::pCpuInfo->dwNumberOfProcessors,10);

        QTableWidgetItem *item_1_1 = new QTableWidgetItem(cpuBrand);
        QTableWidgetItem *item_1_2 = new QTableWidgetItem(cpuNum);
        QTableWidgetItem *item_1_3 = new QTableWidgetItem(cpuModel);
        QTableWidgetItem *item_1_4 = new QTableWidgetItem(cpuValue);
        QTableWidgetItem *item_1_5 = new QTableWidgetItem(cpuDwnum);
        QTableWidgetItem *item_1_6 = new QTableWidgetItem(cpuPro);
        ui->yingjianTableWidget_1->insertRow(0);
        ui->yingjianTableWidget_1->setItem(0,0,item_1_1);
        ui->yingjianTableWidget_1->setItem(0,1,item_1_2);
        ui->yingjianTableWidget_1->setItem(0,2,item_1_3);
        ui->yingjianTableWidget_1->setItem(0,3,item_1_4);
        ui->yingjianTableWidget_1->setItem(0,4,item_1_5);
        ui->yingjianTableWidget_1->setItem(0,5,item_1_6);
    }

    QString diskBrand,diskNum,diskValue,diskModel;
    for (int i = 0; i < (int)CheckResultResouce::diskNum; i++)
    {
        diskBrand = QString::fromLocal8Bit(CheckResultResouce::pHardDisk[i].brand);
        diskNum = QString::fromLocal8Bit(CheckResultResouce::pHardDisk[i].factoryNumber);
        char buf[64];
        StorageCapacity2StrL(CheckResultResouce::pHardDisk[i].captacity, buf);
        diskValue = QString::fromLocal8Bit(buf);
        diskModel = QString::fromLocal8Bit(CheckResultResouce::pHardDisk[i].model);

        QTableWidgetItem *item_2_1 = new QTableWidgetItem(diskBrand);
        QTableWidgetItem *item_2_2 = new QTableWidgetItem(diskNum);
        QTableWidgetItem *item_2_3 = new QTableWidgetItem(diskValue);
        QTableWidgetItem *item_2_4 = new QTableWidgetItem(diskModel);

        ui->yingjianTableWidget_2->insertRow(i);
        ui->yingjianTableWidget_2->setItem(i,0,item_2_1);
        ui->yingjianTableWidget_2->setItem(i,1,item_2_2);
        ui->yingjianTableWidget_2->setItem(i,2,item_2_3);
        ui->yingjianTableWidget_2->setItem(i,3,item_2_4);
    }

    //主板
    QString boardBrand,boardNum,boardModel;
    if (CheckResultResouce::pBoardInfo)
    {
        boardBrand = QString::fromLocal8Bit(CheckResultResouce::pBoardInfo->brand);
        boardNum = QString::fromLocal8Bit(CheckResultResouce::pBoardInfo->factoryNumber);
        boardModel = QString::fromLocal8Bit(CheckResultResouce::pBoardInfo->model);

        QTableWidgetItem *item_3_1 = new QTableWidgetItem(boardBrand);
        QTableWidgetItem *item_3_2 = new QTableWidgetItem(boardNum);
        QTableWidgetItem *item_3_3 = new QTableWidgetItem(boardModel);

        ui->yingjianTableWidget_3->insertRow(0);
        ui->yingjianTableWidget_3->setItem(0,0,item_3_1);
        ui->yingjianTableWidget_3->setItem(0,1,item_3_2);
        ui->yingjianTableWidget_3->setItem(0,2,item_3_3);
    }
    //显卡
    QString disBrand,disParameter;
    if (CheckResultResouce::pDisplayCard)
    {
        disBrand = QString::fromLocal8Bit(CheckResultResouce::pDisplayCard->brand);
        char buf[64];
        StorageCapacity2StrL(CheckResultResouce::pDisplayCard->captacity, buf);
        disParameter = QString::fromLocal8Bit(buf);

        QTableWidgetItem *item_5_1 = new QTableWidgetItem(disBrand);
        QTableWidgetItem *item_5_2 = new QTableWidgetItem(disParameter);

        ui->yingjianTableWidget_5->insertRow(0);
        ui->yingjianTableWidget_5->setItem(0,0,item_5_1);
        ui->yingjianTableWidget_5->setItem(0,1,item_5_2);
    }

    //内存
    QString str1,str2,str3,str4;
    if (CheckResultResouce::pMemory)
    {
        MemoryInfo &memory = *CheckResultResouce::pMemory;

        char buf[64];

        StorageCapacity2StrL(memory.ullTotalPhys, buf);
        str1 = QString::fromLocal8Bit(buf);

        StorageCapacity2StrL(memory.ullAvailPhys, buf);
        str2 = QString::fromLocal8Bit(buf);

        StorageCapacity2StrL(memory.ullTotalVirtual, buf);
        str3 = QString::fromLocal8Bit(buf);

        StorageCapacity2StrL(memory.ullAvailVirtual, buf);
        str4 = QString::fromLocal8Bit(buf);

        QTableWidgetItem *item_4_1 = new QTableWidgetItem(str1);
        QTableWidgetItem *item_4_2 = new QTableWidgetItem(str2);
        QTableWidgetItem *item_4_3 = new QTableWidgetItem(str3);
        QTableWidgetItem *item_4_4 = new QTableWidgetItem(str4);

        ui->yingjianTableWidget_4->insertRow(0);
        ui->yingjianTableWidget_4->setItem(0,0,item_4_1);
        ui->yingjianTableWidget_4->setItem(0,1,item_4_2);
        ui->yingjianTableWidget_4->setItem(0,2,item_4_3);
        ui->yingjianTableWidget_4->setItem(0,3,item_4_4);
    }

    //声卡
    QString audioBrand;
    if (CheckResultResouce::pAudio)
    {
        audioBrand = QString::fromLocal8Bit(CheckResultResouce::pAudio->brand);

        QTableWidgetItem *item_6_1 = new QTableWidgetItem(audioBrand);

        ui->yingjianTableWidget_6->insertRow(0);
        ui->yingjianTableWidget_6->setItem(0,0,item_6_1);
    }

    //网卡
    QString netBrand,netSoft;
    for (int k = 0; k < (int)CheckResultResouce::netcardNum; k++)
    {
        netBrand = QString::fromLocal8Bit(CheckResultResouce::pNetwork[k].brand);
        netSoft = QString::fromLocal8Bit(CheckResultResouce::pNetwork[k].softSetting);

        QTableWidgetItem *item_7_1 = new QTableWidgetItem(netBrand);
        QTableWidgetItem *item_7_2 = new QTableWidgetItem(netSoft);

        ui->yingjianTableWidget_7->insertRow(k);
        ui->yingjianTableWidget_7->setItem(k,0,item_7_1);
        ui->yingjianTableWidget_7->setItem(k,1,item_7_2);
    }
}

void MainWindow::yingjianResShow()
{
    if(CheckResultResouce::pCpuInfo==NULL||(int)CheckResultResouce::diskNum==0)
    {
        return;
    }
    ui->scrollArea_2->setVisible(true);

    ui->yingjianTableWidget_8->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_8->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_8->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_9->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_9->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_9->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_10->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_10->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_10->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_11->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_11->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_11->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_12->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_12->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_12->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_13->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_13->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_13->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_14->horizontalHeader()->setSectionsClickable(false);
    ui->yingjianTableWidget_14->verticalHeader()->setVisible(false);
    ui->yingjianTableWidget_14->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");

    ui->yingjianTableWidget_8->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->yingjianTableWidget_9->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->yingjianTableWidget_10->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->yingjianTableWidget_11->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->yingjianTableWidget_12->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->yingjianTableWidget_13->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->yingjianTableWidget_14->setEditTriggers(QAbstractItemView::NoEditTriggers);


    ui->yingjianTableWidget_8->setColumnWidth(0,130);
    ui->yingjianTableWidget_8->setColumnWidth(1,130);
    ui->yingjianTableWidget_8->setColumnWidth(2,300);
    ui->yingjianTableWidget_8->setColumnWidth(3,300);
    ui->yingjianTableWidget_8->setColumnWidth(4,59);
    ui->yingjianTableWidget_8->setColumnWidth(5,59);

    ui->yingjianTableWidget_9->setColumnWidth(0,280);
    ui->yingjianTableWidget_9->setColumnWidth(1,199);
    ui->yingjianTableWidget_9->setColumnWidth(2,199);
    ui->yingjianTableWidget_9->setColumnWidth(3,300);

    ui->yingjianTableWidget_10->setColumnWidth(0,326);
    ui->yingjianTableWidget_10->setColumnWidth(1,326);
    ui->yingjianTableWidget_10->setColumnWidth(2,326);

    ui->yingjianTableWidget_11->setColumnWidth(0,246);
    ui->yingjianTableWidget_11->setColumnWidth(1,244);
    ui->yingjianTableWidget_11->setColumnWidth(2,244);
    ui->yingjianTableWidget_11->setColumnWidth(3,244);

    ui->yingjianTableWidget_12->setColumnWidth(0,489);
    ui->yingjianTableWidget_12->setColumnWidth(1,489);

    ui->yingjianTableWidget_13->setColumnWidth(0,978);

    ui->yingjianTableWidget_14->setColumnWidth(0,385);
    ui->yingjianTableWidget_14->setColumnWidth(1,585);

    ui->yingjianTableWidget_8->setRowCount(0);
    ui->yingjianTableWidget_9->setRowCount(0);
    ui->yingjianTableWidget_10->setRowCount(0);
    ui->yingjianTableWidget_11->setRowCount(0);
    ui->yingjianTableWidget_12->setRowCount(0);
    ui->yingjianTableWidget_13->setRowCount(0);
    ui->yingjianTableWidget_14->setRowCount(0);

    QString cpuBrand,cpuNum,cpuModel,cpuValue,cpuDwnum,cpuPro;
    if(CheckResultResouce::pCpuInfo)
    {
        cpuBrand = QString::fromLocal8Bit(CheckResultResouce::pCpuInfo->brand);
        cpuNum = QString::fromLocal8Bit(CheckResultResouce::pCpuInfo->factoryNumber);
        cpuModel = QString::fromLocal8Bit(CheckResultResouce::pCpuInfo->model);
        cpuValue = QString::fromLocal8Bit(CheckResultResouce::pCpuInfo->parameterValue);
        cpuDwnum = QString::number(CheckResultResouce::pCpuInfo->dwNumberOfCpu,10);
        cpuPro = QString::number(CheckResultResouce::pCpuInfo->dwNumberOfProcessors,10);

        QTableWidgetItem *item_1_1 = new QTableWidgetItem(cpuBrand);
        QTableWidgetItem *item_1_2 = new QTableWidgetItem(cpuNum);
        QTableWidgetItem *item_1_3 = new QTableWidgetItem(cpuModel);
        QTableWidgetItem *item_1_4 = new QTableWidgetItem(cpuValue);
        QTableWidgetItem *item_1_5 = new QTableWidgetItem(cpuDwnum);
        QTableWidgetItem *item_1_6 = new QTableWidgetItem(cpuPro);
        ui->yingjianTableWidget_8->insertRow(0);
        ui->yingjianTableWidget_8->setItem(0,0,item_1_1);
        ui->yingjianTableWidget_8->setItem(0,1,item_1_2);
        ui->yingjianTableWidget_8->setItem(0,2,item_1_3);
        ui->yingjianTableWidget_8->setItem(0,3,item_1_4);
        ui->yingjianTableWidget_8->setItem(0,4,item_1_5);
        ui->yingjianTableWidget_8->setItem(0,5,item_1_6);
    }

    QString diskBrand,diskNum,diskValue,diskModel;
    for (int i = 0; i < (int)CheckResultResouce::diskNum; i++)
    {
        diskBrand = QString::fromLocal8Bit(CheckResultResouce::pHardDisk[i].brand);
        diskNum = QString::fromLocal8Bit(CheckResultResouce::pHardDisk[i].factoryNumber);
        char buf[64];
        StorageCapacity2StrL(CheckResultResouce::pHardDisk[i].captacity, buf);
        diskValue = QString::fromLocal8Bit(buf);
        diskModel = QString::fromLocal8Bit(CheckResultResouce::pHardDisk[i].model);
        diskModel = QString::fromLocal8Bit(CheckResultResouce::pHardDisk[i].model);

        QTableWidgetItem *item_2_1 = new QTableWidgetItem(diskBrand);
        QTableWidgetItem *item_2_2 = new QTableWidgetItem(diskNum);
        QTableWidgetItem *item_2_3 = new QTableWidgetItem(diskValue);
        QTableWidgetItem *item_2_4 = new QTableWidgetItem(diskModel);

        ui->yingjianTableWidget_9->insertRow(i);
        ui->yingjianTableWidget_9->setItem(i,0,item_2_1);
        ui->yingjianTableWidget_9->setItem(i,1,item_2_2);
        ui->yingjianTableWidget_9->setItem(i,2,item_2_3);
        ui->yingjianTableWidget_9->setItem(i,3,item_2_4);
    }

    //主板
    QString boardBrand,boardNum,boardModel;
    if (CheckResultResouce::pBoardInfo)
    {
        boardBrand = QString::fromLocal8Bit(CheckResultResouce::pBoardInfo->brand);
        boardNum = QString::fromLocal8Bit(CheckResultResouce::pBoardInfo->factoryNumber);
        boardModel = QString::fromLocal8Bit(CheckResultResouce::pBoardInfo->model);

        QTableWidgetItem *item_3_1 = new QTableWidgetItem(boardBrand);
        QTableWidgetItem *item_3_2 = new QTableWidgetItem(boardNum);
        QTableWidgetItem *item_3_3 = new QTableWidgetItem(boardModel);

        ui->yingjianTableWidget_10->insertRow(0);
        ui->yingjianTableWidget_10->setItem(0,0,item_3_1);
        ui->yingjianTableWidget_10->setItem(0,1,item_3_2);
        ui->yingjianTableWidget_10->setItem(0,2,item_3_3);
    }
    //显卡
    QString disBrand,disParameter;
    if (CheckResultResouce::pDisplayCard)
    {
        disBrand = QString::fromLocal8Bit(CheckResultResouce::pDisplayCard->brand);
        char buf[64];
        StorageCapacity2StrL(CheckResultResouce::pDisplayCard->captacity, buf);
        disParameter = QString::fromLocal8Bit(buf);

        QTableWidgetItem *item_5_1 = new QTableWidgetItem(disBrand);
        QTableWidgetItem *item_5_2 = new QTableWidgetItem(disParameter);

        ui->yingjianTableWidget_12->insertRow(0);
        ui->yingjianTableWidget_12->setItem(0,0,item_5_1);
        ui->yingjianTableWidget_12->setItem(0,1,item_5_2);
    }

    //内存
    QString str1,str2,str3,str4;
    if (CheckResultResouce::pMemory)
    {
        MemoryInfo &memory = *CheckResultResouce::pMemory;

        char buf[64];

        StorageCapacity2StrL(memory.ullTotalPhys, buf);    //物理内存
        str1 = QString::fromLocal8Bit(buf);

        StorageCapacity2StrL(memory.ullAvailPhys, buf);    //可用物理内存
        str2 = QString::fromLocal8Bit(buf);

        StorageCapacity2StrL(memory.ullTotalVirtual, buf);   //虚拟内存
        str3 = QString::fromLocal8Bit(buf);

        StorageCapacity2StrL(memory.ullAvailVirtual, buf);    //可用虚拟内存
        str4 = QString::fromLocal8Bit(buf);

        QTableWidgetItem *item_4_1 = new QTableWidgetItem(str1);
        QTableWidgetItem *item_4_2 = new QTableWidgetItem(str2);
        QTableWidgetItem *item_4_3 = new QTableWidgetItem(str3);
        QTableWidgetItem *item_4_4 = new QTableWidgetItem(str4);

        ui->yingjianTableWidget_11->insertRow(0);
        ui->yingjianTableWidget_11->setItem(0,0,item_4_1);
        ui->yingjianTableWidget_11->setItem(0,1,item_4_2);
        ui->yingjianTableWidget_11->setItem(0,2,item_4_3);
        ui->yingjianTableWidget_11->setItem(0,3,item_4_4);
    }

    //声卡
    QString audioBrand;
    if (CheckResultResouce::pAudio)
    {
        audioBrand = QString::fromLocal8Bit(CheckResultResouce::pAudio->brand);

        QTableWidgetItem *item_6_1 = new QTableWidgetItem(audioBrand);

        ui->yingjianTableWidget_13->insertRow(0);
        ui->yingjianTableWidget_13->setItem(0,0,item_6_1);
    }

    //网卡
    QString netBrand,netSoft;
    for (int k = 0; k < (int)CheckResultResouce::netcardNum; k++)
    {
        netBrand = QString::fromLocal8Bit(CheckResultResouce::pNetwork[k].brand);
        netSoft = QString::fromLocal8Bit(CheckResultResouce::pNetwork[k].softSetting);

        QTableWidgetItem *item_7_1 = new QTableWidgetItem(netBrand);
        QTableWidgetItem *item_7_2 = new QTableWidgetItem(netSoft);

        ui->yingjianTableWidget_14->insertRow(k);
        ui->yingjianTableWidget_14->setItem(k,0,item_7_1);
        ui->yingjianTableWidget_14->setItem(k,1,item_7_2);
    }
}

void MainWindow::gongxiangTableShow()
{
    ui->gongxiangTableWidget->setVisible(true);
    ui->muluRings->setVisible(false);

    ui->gongxiangTableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->gongxiangTableWidget->verticalHeader()->setVisible(false);
    ui->gongxiangTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");
    ui->gongxiangTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->gongxiangTableWidget->setColumnWidth(0,169);
    ui->gongxiangTableWidget->setColumnWidth(1,230);
    ui->gongxiangTableWidget->setColumnWidth(2,330);

    ui->gongxiangTableWidget->setRowCount(0);

    CHAR strPathName[MAX_PATH] = {0};
    CHAR strShareName[MAX_PATH] = {0};
    CHAR strShareType[MAX_PATH] = {0};

    QString sharePath,shareName,shareType;
    for (int i=0; i<(int)CheckResultResouce::shareNum; i++)
    {
        memset(strShareName, 0, sizeof(strShareName));
        memset(strPathName, 0, sizeof(strPathName));
        memset(strShareType, 0, sizeof(strShareType));

        UINT32 len = (UINT32)wcslen(CheckResultResouce::pShareInfo[i].shi502_netname);
        widechar_to_multibyte(CheckResultResouce::pShareInfo[i].shi502_netname,len, strShareName, sizeof(strShareName));
        widechar_to_multibyte(CheckResultResouce::pShareInfo[i].shi502_path, wcslen(CheckResultResouce::pShareInfo[i].shi502_path), strPathName, sizeof(strPathName));
        widechar_to_multibyte(CheckResultResouce::pShareInfo[i].shi502_remark, wcslen(CheckResultResouce::pShareInfo[i].shi502_remark), strShareType, sizeof(strShareType));

        sharePath = QString::fromLocal8Bit(strPathName);
        shareName = QString::fromLocal8Bit(strShareName);
        shareType = QString::fromLocal8Bit(strShareType);

        QTableWidgetItem *item_1 = new QTableWidgetItem(shareName);
        QTableWidgetItem *item_2 = new QTableWidgetItem(sharePath);
        QTableWidgetItem *item_3 = new QTableWidgetItem(shareType);

        ui->gongxiangTableWidget->insertRow(i);

        ui->gongxiangTableWidget->setItem(i,0,item_1);
        ui->gongxiangTableWidget->setItem(i,1,item_2);
        ui->gongxiangTableWidget->setItem(i,2,item_3);
    }
}

void MainWindow::gongxiangResShow()
{
    if((int)CheckResultResouce::shareNum==0)
    {
        return;
    }
    ui->gongxiangTableWidget_2->horizontalHeader()->setSectionsClickable(false);
    ui->gongxiangTableWidget_2->verticalHeader()->setVisible(false);
    ui->gongxiangTableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");
    ui->gongxiangTableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->gongxiangTableWidget_2->setColumnWidth(0,224);
    ui->gongxiangTableWidget_2->setColumnWidth(1,275);
    ui->gongxiangTableWidget_2->setColumnWidth(2,380);

    ui->gongxiangTableWidget_2->setRowCount(0);

    CHAR strPathName[MAX_PATH] = {0};
    CHAR strShareName[MAX_PATH] = {0};
    CHAR strShareType[MAX_PATH] = {0};

    QString sharePath,shareName,shareType;
    for (int i=0; i<(int)CheckResultResouce::shareNum; i++)
    {
        memset(strShareName, 0, sizeof(strShareName));
        memset(strPathName, 0, sizeof(strPathName));
        memset(strShareType, 0, sizeof(strShareType));

        UINT32 len = (UINT32)wcslen(CheckResultResouce::pShareInfo[i].shi502_netname);
        widechar_to_multibyte(CheckResultResouce::pShareInfo[i].shi502_netname,len, strShareName, sizeof(strShareName));
        widechar_to_multibyte(CheckResultResouce::pShareInfo[i].shi502_path, wcslen(CheckResultResouce::pShareInfo[i].shi502_path), strPathName, sizeof(strPathName));
        widechar_to_multibyte(CheckResultResouce::pShareInfo[i].shi502_remark, wcslen(CheckResultResouce::pShareInfo[i].shi502_remark), strShareType, sizeof(strShareType));

        sharePath = QString::fromLocal8Bit(strPathName);
        shareName = QString::fromLocal8Bit(strShareName);
        shareType = QString::fromLocal8Bit(strShareType);

        QTableWidgetItem *item_1 = new QTableWidgetItem(shareName);
        QTableWidgetItem *item_2 = new QTableWidgetItem(sharePath);
        QTableWidgetItem *item_3 = new QTableWidgetItem(shareType);

        ui->gongxiangTableWidget_2->insertRow(i);

        ui->gongxiangTableWidget_2->setItem(i,0,item_1);
        ui->gongxiangTableWidget_2->setItem(i,1,item_2);
        ui->gongxiangTableWidget_2->setItem(i,2,item_3);
    }
}

void MainWindow::peizhiTableShow()
{
    ui->peizhiRings->setVisible(false);
    ui->peizhiTableWidget->setVisible(true);

    ui->peizhiTableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->peizhiTableWidget->verticalHeader()->setVisible(false);
    ui->peizhiTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");
    ui->peizhiTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->peizhiTableWidget->setColumnWidth(0,390);
    ui->peizhiTableWidget->setColumnWidth(1,339);

    ui->peizhiTableWidget->setRowCount(0);

    QString optionName,optionValue;
    for (int i = 0; i < (int)CheckResultResouce::secOptionsNum; i++)
    {
        optionName = QString::fromLocal8Bit(CheckResultResouce::pSecurityOpt[i].szName);
        optionValue = QString::fromLocal8Bit(CheckResultResouce::pSecurityOpt[i].szValue);

        QTableWidgetItem *item_1 = new QTableWidgetItem(optionName);
        QTableWidgetItem *item_2 = new QTableWidgetItem(optionValue);

        ui->peizhiTableWidget->insertRow(i);

        ui->peizhiTableWidget->setItem(i,0,item_1);
        ui->peizhiTableWidget->setItem(i,1,item_2);
    }
}

void MainWindow::wailianTableShow()
{
    ui->wailianTableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->wailianTableWidget->verticalHeader()->setVisible(false);
    ui->wailianTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");
    ui->wailianTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->wailianTableWidget->setColumnWidth(0,149);
    ui->wailianTableWidget->setColumnWidth(1,280);
    ui->wailianTableWidget->setColumnWidth(2,150);
    ui->wailianTableWidget->setColumnWidth(3,125);

    connect(ui->wailianTableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),
            ui->wailianTableWidget,SLOT(resizeRowsToContents()));

    ui->wailianTableWidget->setRowCount(0);

    char buffer[1024];
    int j ;
    int row = 0;
    QString hisUrl,hisTitle,hisTime;

    while (NULL != CheckResultResouce::pFirefoxHistory)
    {
        hisUrl = QString::fromLocal8Bit(CheckResultResouce::pFirefoxHistory->fireFoxUrl);
        hisTitle = QString::fromLocal8Bit(CheckResultResouce::pFirefoxHistory->fireFoxTitle);
        hisTime = QString::fromLocal8Bit(CheckResultResouce::pFirefoxHistory->fireFoxVisitTime);

        QTableWidgetItem *item_5 = new QTableWidgetItem("Mozilla Firefox");
        QTableWidgetItem *item_6 = new QTableWidgetItem(hisUrl);
        QTableWidgetItem *item_7 = new QTableWidgetItem(hisTitle);
        QTableWidgetItem *item_8 = new QTableWidgetItem(hisTime);

        ui->wailianTableWidget->insertRow(row);

        ui->wailianTableWidget->setItem(row,0,item_5);
        ui->wailianTableWidget->setItem(row,1,item_6);
        ui->wailianTableWidget->setItem(row,2,item_7);
        ui->wailianTableWidget->setItem(row,3,item_8);

        CheckResultResouce::pFirefoxHistory = CheckResultResouce::pFirefoxHistory->pNext;
        row++;

//        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

        if(row>100)
        {
            return;
        }
    }

    while (NULL != CheckResultResouce::pChromeHistory)
    {
        hisUrl = QString::fromLocal8Bit(CheckResultResouce::pChromeHistory->chromeUrl);
        hisTitle = QString::fromLocal8Bit(CheckResultResouce::pChromeHistory->chromeTitle);
        hisTime = QString::fromLocal8Bit(CheckResultResouce::pChromeHistory->chromeVisitTime);

        QTableWidgetItem *item_9 = new QTableWidgetItem("Google Chrome");
        QTableWidgetItem *item_10 = new QTableWidgetItem(hisUrl);
        QTableWidgetItem *item_11 = new QTableWidgetItem(hisTitle);
        QTableWidgetItem *item_12 = new QTableWidgetItem(hisTime);

        ui->wailianTableWidget->insertRow(row);

        ui->wailianTableWidget->setItem(row,0,item_9);
        ui->wailianTableWidget->setItem(row,1,item_10);
        ui->wailianTableWidget->setItem(row,2,item_11);
        ui->wailianTableWidget->setItem(row,3,item_12);

        CheckResultResouce::pChromeHistory = CheckResultResouce::pChromeHistory->pNext;
        row++;
//        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        if(row>100)
        {
            return;
        }
    }

    while(NULL != CheckResultResouce::pIeHistory)
    {
        char *pIeUrl = CheckResultResouce::pIeHistory->IeUrl;

        //memset(buffer,0, sizeof(buffer));
        if (!strncmp(pIeUrl, "javascript", 10))
        {
            j = 0;
            int iUrlLen = strlen(pIeUrl);
            for (int i = 0; i < iUrlLen; i++)
            {
                if ((j+3)> 1023)
                    break;

                if (pIeUrl[i] == '<')
                {
                    strncpy(buffer+j, "&lt", 3);
                    j = j+3;
                }
                else if (pIeUrl[i] == '>')
                {
                    strncpy(buffer+j, "&gt", 3);
                    j = j+3;
                }
                else
                {
                    buffer[j] = pIeUrl[i];
                    j++;
                }
            }
            buffer[j] = 0;
            pIeUrl = buffer;
        }

        hisUrl = QString::fromLocal8Bit(pIeUrl);
        hisTitle = QString::fromLocal8Bit(CheckResultResouce::pIeHistory->IeTitle);
        hisTime = QString::fromLocal8Bit(CheckResultResouce::pIeHistory->visitTime);

        ui->wailianTableWidget->insertRow(row);

        QTableWidgetItem *item_1 = new QTableWidgetItem("Internet Explorer");
        QTableWidgetItem *item_2 = new QTableWidgetItem(hisUrl);
        QTableWidgetItem *item_3 = new QTableWidgetItem(hisTitle);
        QTableWidgetItem *item_4 = new QTableWidgetItem(hisTime);

        ui->wailianTableWidget->setItem(row,0,item_1);
        ui->wailianTableWidget->setItem(row,1,item_2);
        ui->wailianTableWidget->setItem(row,2,item_3);
        ui->wailianTableWidget->setItem(row,3,item_4);

        CheckResultResouce::pIeHistory = CheckResultResouce::pIeHistory->pNext;
        row++;
//        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        if(row>100)
        {
            return;
        }
    }
}

void MainWindow::wailianResShow()
{
    if(NULL==CheckResultResouce::pIeHistory&&CheckResultResouce::pFirefoxHistory==NULL&&CheckResultResouce::pChromeHistory==NULL)
    {
        return;
    }
    ui->wailianTableWidget_2->horizontalHeader()->setSectionsClickable(false);
    ui->wailianTableWidget_2->verticalHeader()->setVisible(false);
    ui->wailianTableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");
    ui->wailianTableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->wailianTableWidget_2->setColumnWidth(0,181);
    ui->wailianTableWidget_2->setColumnWidth(1,315);
    ui->wailianTableWidget_2->setColumnWidth(2,182);
    ui->wailianTableWidget_2->setColumnWidth(3,182);

    connect(ui->wailianTableWidget_2,SIGNAL(itemChanged(QTableWidgetItem*)),
            ui->wailianTableWidget_2,SLOT(resizeRowsToContents()));

    ui->wailianTableWidget_2->setRowCount(0);

    char buffer[1024];
    int j ;
    int row = 0;
    QString hisUrl,hisTitle,hisTime;
    while(NULL != CheckResultResouce::pIeHistory)
    {
        char *pIeUrl = CheckResultResouce::pIeHistory->IeUrl;

        //memset(buffer,0, sizeof(buffer));
        if (!strncmp(pIeUrl, "javascript", 10))
        {
            j = 0;
            int iUrlLen = strlen(pIeUrl);
            for (int i = 0; i < iUrlLen; i++)
            {
                if ((j+3)> 1023)
                    break;

                if (pIeUrl[i] == '<')
                {
                    strncpy(buffer+j, "&lt", 3);
                    j = j+3;
                }
                else if (pIeUrl[i] == '>')
                {
                    strncpy(buffer+j, "&gt", 3);
                    j = j+3;
                }
                else
                {
                    buffer[j] = pIeUrl[i];
                    j++;
                }
            }
            buffer[j] = 0;
            pIeUrl = buffer;
        }

        hisUrl = QString::fromLocal8Bit(pIeUrl);
        hisTitle = QString::fromLocal8Bit(CheckResultResouce::pIeHistory->IeTitle);
        hisTime = QString::fromLocal8Bit(CheckResultResouce::pIeHistory->visitTime);

        ui->wailianTableWidget_2->insertRow(row);

        QTableWidgetItem *item_1 = new QTableWidgetItem("Internet Explorer");
        QTableWidgetItem *item_2 = new QTableWidgetItem(hisUrl);
        QTableWidgetItem *item_3 = new QTableWidgetItem(hisTitle);
        QTableWidgetItem *item_4 = new QTableWidgetItem(hisTime);

        ui->wailianTableWidget_2->setItem(row,0,item_1);
        ui->wailianTableWidget_2->setItem(row,1,item_2);
        ui->wailianTableWidget_2->setItem(row,2,item_3);
        ui->wailianTableWidget_2->setItem(row,3,item_4);

        CheckResultResouce::pIeHistory = CheckResultResouce::pIeHistory->pNext;
        row++;
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }

    while (NULL != CheckResultResouce::pFirefoxHistory)
    {
        hisUrl = QString::fromLocal8Bit(CheckResultResouce::pFirefoxHistory->fireFoxUrl);
        hisTitle = QString::fromLocal8Bit(CheckResultResouce::pFirefoxHistory->fireFoxTitle);
        hisTime = QString::fromLocal8Bit(CheckResultResouce::pFirefoxHistory->fireFoxVisitTime);

        QTableWidgetItem *item_5 = new QTableWidgetItem("Mozilla Firefox");
        QTableWidgetItem *item_6 = new QTableWidgetItem(hisUrl);
        QTableWidgetItem *item_7 = new QTableWidgetItem(hisTitle);
        QTableWidgetItem *item_8 = new QTableWidgetItem(hisTime);

        ui->wailianTableWidget_2->insertRow(row);

        ui->wailianTableWidget_2->setItem(row,0,item_5);
        ui->wailianTableWidget_2->setItem(row,1,item_6);
        ui->wailianTableWidget_2->setItem(row,2,item_7);
        ui->wailianTableWidget_2->setItem(row,3,item_8);

        CheckResultResouce::pFirefoxHistory = CheckResultResouce::pFirefoxHistory->pNext;
        row++;
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }

    while (NULL != CheckResultResouce::pChromeHistory)
    {
        hisUrl = QString::fromLocal8Bit(CheckResultResouce::pChromeHistory->chromeUrl);
        hisTitle = QString::fromLocal8Bit(CheckResultResouce::pChromeHistory->chromeTitle);
        hisTime = QString::fromLocal8Bit(CheckResultResouce::pChromeHistory->chromeVisitTime);

        QTableWidgetItem *item_9 = new QTableWidgetItem("Google Chrome");
        QTableWidgetItem *item_10 = new QTableWidgetItem(hisUrl);
        QTableWidgetItem *item_11 = new QTableWidgetItem(hisTitle);
        QTableWidgetItem *item_12 = new QTableWidgetItem(hisTime);

        ui->wailianTableWidget_2->insertRow(row);

        ui->wailianTableWidget_2->setItem(row,0,item_9);
        ui->wailianTableWidget_2->setItem(row,1,item_10);
        ui->wailianTableWidget_2->setItem(row,2,item_11);
        ui->wailianTableWidget_2->setItem(row,3,item_12);

        CheckResultResouce::pChromeHistory = CheckResultResouce::pChromeHistory->pNext;
        row++;
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    return;
}

void MainWindow::on_wailianBackButton_clicked()
{
    ui->henjiWidget->setCurrentIndex(0);
    hjIndex_1=0;
}

void MainWindow::wjczTableShow()
{
    ui->wjczTableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->wjczTableWidget->verticalHeader()->setVisible(false);
    ui->wjczTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");
    ui->wjczTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->wjczTableWidget->setColumnWidth(0,120);
    ui->wjczTableWidget->setColumnWidth(1,170);
    ui->wjczTableWidget->setColumnWidth(2,270);
    ui->wjczTableWidget->setColumnWidth(3,169);

    ui->wjczTableWidget->setRowCount(0);

    //检查模式|时间|文件名|备注
    QString mRes;
    QStringList mList;
    QString strModel,strTime,strId,strBz;
    for(int i=0;i<wjczResList.count();i++)
    {
        ui->wjczTableWidget->insertRow(i);
        mRes = wjczResList[i];
        mList = mRes.split("|");
        int len = mList.count();
        if(len<4)
        {
            qWarning()<<"usb result fault!";
        }
        else
        {
            strModel = mList[0];
            strTime = mList[1];
            strId = mList[2];
            strBz = mList[3];
            QTableWidgetItem *item_1 = new QTableWidgetItem(strModel);
            QTableWidgetItem *item_2 = new QTableWidgetItem(strTime);
            QTableWidgetItem *item_3 = new QTableWidgetItem(strId);
            QTableWidgetItem *item_4 = new QTableWidgetItem(strBz);

            ui->wjczTableWidget->setItem(i,0,item_1);
            ui->wjczTableWidget->setItem(i,1,item_2);
            ui->wjczTableWidget->setItem(i,2,item_3);
            ui->wjczTableWidget->setItem(i,3,item_4);
            mList.clear();
        }
    }
}

void MainWindow::on_wjczBackButton_clicked()
{
    ui->henjiWidget->setCurrentIndex(2);
    hjIndex_2=2;
}

void MainWindow::wjnrTableShow()
{
    ui->wjnrTableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->wjnrTableWidget->verticalHeader()->setVisible(false);
    ui->wjnrTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                           "{background-color:rgb(215,215,215);}");
    ui->wjnrTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->wjnrTableWidget->setColumnWidth(0,119);
    ui->wjnrTableWidget->setColumnWidth(1,320);
    ui->wjnrTableWidget->setColumnWidth(2,290);

    ui->wjnrTableWidget->setRowCount(0);
    QList<SensRes>::iterator it;
    SensRes mRes;
    int row = 0;
    for(it = sensResList.begin();it!=sensResList.end();it++)
    {
        ui->wjnrTableWidget->insertRow(row);
        mRes = *it;
        QString strPath = mRes.filePath;
        QString strKey = mRes.keyWord;
        QString strIndex = QString::number(row+1,10);
        QTableWidgetItem *item1 = new QTableWidgetItem(strPath);
        QTableWidgetItem *item2 = new QTableWidgetItem(strKey);
        QTableWidgetItem *item3 = new QTableWidgetItem(strIndex);
        ui->wjnrTableWidget->setItem(row,0,item3);
        ui->wjnrTableWidget->setItem(row,1,item1);
        ui->wjnrTableWidget->setItem(row,2,item2);
        row++;
        if(row>=500)   //超过500个就不展示了
        {
            break;
        }
    }
}


void MainWindow::on_wjnrBackButton_clicked()
{
    ui->henjiWidget->setCurrentIndex(3);
    hjIndex_3=3;
}

void MainWindow::ydjzTableShow()
{
    ui->ydjzTableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->ydjzTableWidget->verticalHeader()->setVisible(false);
    ui->ydjzTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                           "{background-color:rgb(215,215,215);}");
    ui->ydjzTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->ydjzTableWidget->setColumnWidth(0,257);
    ui->ydjzTableWidget->setColumnWidth(1,208);
    ui->ydjzTableWidget->setColumnWidth(2,132);
    ui->ydjzTableWidget->setColumnWidth(3,132);

    ui->ydjzTableWidget->setRowCount(0);

    QString usbDesc,usbService,usbCreateTime,usbUpdateTime;
    int row=0;
    while (NULL != CheckResultResouce::pUsbHistory)
    {
        usbDesc = QString::fromLocal8Bit(CheckResultResouce::pUsbHistory->caDeviceDesc);
        usbService = QString::fromLocal8Bit(CheckResultResouce::pUsbHistory->caService);
        usbCreateTime = QString::fromLocal8Bit(CheckResultResouce::pUsbHistory->caCreateTime);
        usbUpdateTime = QString::fromLocal8Bit(CheckResultResouce::pUsbHistory->caUpdateTime);

        QTableWidgetItem *item_1 = new QTableWidgetItem(usbDesc);
        QTableWidgetItem *item_2 = new QTableWidgetItem(usbService);
        QTableWidgetItem *item_3 = new QTableWidgetItem(usbCreateTime);
        QTableWidgetItem *item_4 = new QTableWidgetItem(usbUpdateTime);

        ui->ydjzTableWidget->insertRow(row);

        ui->ydjzTableWidget->setItem(row,0,item_1);
        ui->ydjzTableWidget->setItem(row,1,item_2);
        ui->ydjzTableWidget->setItem(row,2,item_3);
        ui->ydjzTableWidget->setItem(row,3,item_4);

        CheckResultResouce::pUsbHistory = CheckResultResouce::pUsbHistory->pNext;
        row++;
    }
}

void MainWindow::ydjzResShow()
{
    if(NULL == CheckResultResouce::pUsbHistory)
    {
        return;
    }
    ui->ydjzTableWidget_2->horizontalHeader()->setSectionsClickable(false);
    ui->ydjzTableWidget_2->verticalHeader()->setVisible(false);
    ui->ydjzTableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                           "{background-color:rgb(215,215,215);}");
    ui->ydjzTableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->ydjzTableWidget_2->setColumnWidth(0,275);
    ui->ydjzTableWidget_2->setColumnWidth(1,244);
    ui->ydjzTableWidget_2->setColumnWidth(2,170);
    ui->ydjzTableWidget_2->setColumnWidth(3,170);

    ui->ydjzTableWidget_2->setRowCount(0);

    QString usbDesc,usbService,usbCreateTime,usbUpdateTime;
    int row=0;
    while (NULL != CheckResultResouce::pUsbHistory)
    {
        usbDesc = QString::fromLocal8Bit(CheckResultResouce::pUsbHistory->caDeviceDesc);
        usbService = QString::fromLocal8Bit(CheckResultResouce::pUsbHistory->caService);
        usbCreateTime = QString::fromLocal8Bit(CheckResultResouce::pUsbHistory->caCreateTime);
        usbUpdateTime = QString::fromLocal8Bit(CheckResultResouce::pUsbHistory->caUpdateTime);

        QTableWidgetItem *item_1 = new QTableWidgetItem(usbDesc);
        QTableWidgetItem *item_2 = new QTableWidgetItem(usbService);
        QTableWidgetItem *item_3 = new QTableWidgetItem(usbCreateTime);
        QTableWidgetItem *item_4 = new QTableWidgetItem(usbUpdateTime);

        ui->ydjzTableWidget_2->insertRow(row);

        ui->ydjzTableWidget_2->setItem(row,0,item_1);
        ui->ydjzTableWidget_2->setItem(row,1,item_2);
        ui->ydjzTableWidget_2->setItem(row,2,item_3);
        ui->ydjzTableWidget_2->setItem(row,3,item_4);

        CheckResultResouce::pUsbHistory = CheckResultResouce::pUsbHistory->pNext;
        row++;
    }
}

void MainWindow::ydjzDeepTableShow()
{
    ui->ydjzTableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->ydjzTableWidget->verticalHeader()->setVisible(false);
    ui->ydjzTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                           "{background-color:rgb(215,215,215);}");
    ui->ydjzTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->ydjzTableWidget->setColumnWidth(0,143);
    ui->ydjzTableWidget->setColumnWidth(1,130);
    ui->ydjzTableWidget->setColumnWidth(2,300);
    ui->ydjzTableWidget->setColumnWidth(3,125);

    ui->ydjzTableWidget->setRowCount(0);

    //检查模式|时间|ID|备注
    QTableWidgetItem *columnHeaderItem0 = ui->ydjzTableWidget->horizontalHeaderItem(0);
    columnHeaderItem0->setText(QString("检查模式"));

    QTableWidgetItem *columnHeaderItem1 = ui->ydjzTableWidget->horizontalHeaderItem(1);
    columnHeaderItem1->setText(QString("时间"));

    QTableWidgetItem *columnHeaderItem2 = ui->ydjzTableWidget->horizontalHeaderItem(2);
    columnHeaderItem2->setText(QString("ID"));

    QTableWidgetItem *columnHeaderItem3 = ui->ydjzTableWidget->horizontalHeaderItem(3);
    columnHeaderItem3->setText(QString("备注"));

    QString mRes;
    QStringList mList;
    QString strModel,strTime,strId,strBz;
    int count=0;
    for(int i=0;i<usbResList.count();i++)
    {
        ui->ydjzTableWidget->insertRow(i);
        mRes = usbResList[i];
        mList = mRes.split("|");
        int len = mList.count();
        if(len<4)
        {
            qWarning()<<"usb result fault!";
        }
        else
        {
            strModel = mList[0];
            strTime = mList[1];
            strId = mList[2];
            strBz = mList[3];
            QTableWidgetItem *item_1 = new QTableWidgetItem(strModel);
            QTableWidgetItem *item_2 = new QTableWidgetItem(strTime);
            QTableWidgetItem *item_3 = new QTableWidgetItem(strId);
            QTableWidgetItem *item_4 = new QTableWidgetItem(strBz);

            ui->ydjzTableWidget->setItem(i,0,item_1);
            ui->ydjzTableWidget->setItem(i,1,item_2);
            ui->ydjzTableWidget->setItem(i,2,item_3);
            ui->ydjzTableWidget->setItem(i,3,item_4);
            mList.clear();
            count++;
            if(count>=100)
            {
                break;
            }
        }
    }
}

void MainWindow::wailianDeepTableShow()
{
    ui->wailianTableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->wailianTableWidget->verticalHeader()->setVisible(false);
    ui->wailianTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                             "{background-color:rgb(215,215,215);}");
    ui->wailianTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->wailianTableWidget->setColumnWidth(0,149);
    ui->wailianTableWidget->setColumnWidth(1,280);
    ui->wailianTableWidget->setColumnWidth(2,150);
    ui->wailianTableWidget->setColumnWidth(3,125);

    connect(ui->wailianTableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),
            ui->wailianTableWidget,SLOT(resizeRowsToContents()));

    ui->wailianTableWidget->setRowCount(0);

    //工具类型|时间|URL|title
    QString mRes;
    QStringList mList;
    QString strModel,strTime,strId,strBz;
    int count = 0;
    for(int i=0;i<internetResList.count();i++)
    {
        ui->wailianTableWidget->insertRow(i);
        mRes = internetResList[i];
        mList = mRes.split("|");
        int len = mList.count();
        if(len<4)
        {
            qWarning()<<"usb result fault!";
        }
        else
        {
            strModel = mList[0];
            strTime = mList[1];
            strId = mList[2];
            strBz = mList[3];
            QTableWidgetItem *item_1 = new QTableWidgetItem(strModel);
            QTableWidgetItem *item_2 = new QTableWidgetItem(strId);
            QTableWidgetItem *item_3 = new QTableWidgetItem(strBz);
            QTableWidgetItem *item_4 = new QTableWidgetItem(strTime);

            ui->wailianTableWidget->setItem(i,0,item_1);
            ui->wailianTableWidget->setItem(i,1,item_2);
            ui->wailianTableWidget->setItem(i,2,item_3);
            ui->wailianTableWidget->setItem(i,3,item_4);
            mList.clear();
            count++;
            if(count>=100)
            {
                break;
            }
        }
    }
}

void MainWindow::on_ydjzBackButton_clicked()
{
    ui->henjiWidget->setCurrentIndex(4);
    hjIndex_4=4;
}

void MainWindow::jxwjTableShow()
{
    ui->jxwjTableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->jxwjTableWidget->verticalHeader()->setVisible(false);
    ui->jxwjTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                           "{background-color:rgb(215,215,215);}");
    ui->jxwjTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->jxwjTableWidget->setColumnWidth(0,182);
    ui->jxwjTableWidget->setColumnWidth(1,182);
    ui->jxwjTableWidget->setColumnWidth(2,182);
    ui->jxwjTableWidget->setColumnWidth(3,183);
}

void MainWindow::on_jxwjBackButton_clicked()
{
    ui->henjiWidget->setCurrentIndex(5);
    hjIndex_5=5;
}

void MainWindow::dengbao_task_finish()
{
    if(flag<100)
    {
        flag+=1;
    }
    if(flag==100)
    {
        loadMovie->stop();
        dengbao_timer->stop();
        flag=0;
        isClRun=0;
        ui->dengbaoLabel->setText(QString("审核完成"));
        dengbaoTableShow();
        ui->clshBackButton->setEnabled(true);
    }
}

void MainWindow::dengbaoTableShow()
{
    ui->dengbaoTableWidget->setVisible(true);
    ui->dengbaoTableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->dengbaoTableWidget->verticalHeader()->setVisible(false);
    ui->dengbaoTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                           "{background-color:rgb(215,215,215);}");
    ui->dengbaoTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->dengbaoTableWidget->setColumnWidth(0,300);
    ui->dengbaoTableWidget->setColumnWidth(1,275);
    ui->dengbaoTableWidget->setColumnWidth(2,279);

    ui->dengbaoTableWidget->setRowCount(0);

    int row=0;
    QString dengbCkpoint,dengbResult,dengbComment;
    while (NULL != CheckResultResouce::pDtckResults)
    {
        dengbCkpoint = QString::fromLocal8Bit(CheckResultResouce::pDtckResults->result.strCkPoint);
        dengbResult = QString::fromLocal8Bit(CheckResultResouce::pDtckResults->result.strResult);
        dengbComment = QString::fromLocal8Bit(CheckResultResouce::pDtckResults->result.strComment);

        ui->dengbaoTableWidget->insertRow(row);

        QTableWidgetItem *item_1 = new QTableWidgetItem(dengbCkpoint);
        QTableWidgetItem *item_2 = new QTableWidgetItem(dengbResult);
        QTableWidgetItem *item_3 = new QTableWidgetItem(dengbComment);

        ui->dengbaoTableWidget->setItem(row,0,item_1);
        ui->dengbaoTableWidget->setItem(row,1,item_2);
        ui->dengbaoTableWidget->setItem(row,2,item_3);

        CheckResultResouce::pDtckResults = CheckResultResouce::pDtckResults->pNext;
        row++;
    }
}


void MainWindow::on_chooseDirButton_clicked()
{
    QString filePath = QFileDialog::getExistingDirectory(this,QString::fromLocal8Bit("选择目录"),QDir::currentPath(),
                                                     QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(filePath.isEmpty())
    {
        //QMessageBox::information(this,QString::fromLocal8Bit("出错"),QString::fromLocal8Bit("请选择文件"));
        return;
    }
    else
    {
        ui->wjmlLineEdit->setText(filePath);
    }
}

void MainWindow::stop_task_slot()
{
    if(ifUsbFinish)   //usb深度检查是否结束
    {
        ifUsbFinish = false;
        ifUsbDeepCheck = false;
        ui->hjBackButton->setEnabled(true);
        ui->deepTaskStopButton->setEnabled(true);
        ui->henjiRings->setPersent(0);
        if(stop_timer->isActive())
        {
            stop_timer->stop();
        }
        gCurrSize = 0;
        gTotalSize = 0;

        isRun=0;
        hjIndex_4=9;
        ui->henjiWidget->setCurrentIndex(9);
        ydjzDeepTableShow();
    }
    else if(ifIntFinish)      //违规外联深度检查
    {
        ifIntFinish = false;
        ifIntDeepCheck = false;
        ui->hjBackButton->setEnabled(true);
        ui->deepTaskStopButton->setEnabled(true);
        ui->henjiRings->setPersent(0);
        if(stop_timer->isActive())
        {
            stop_timer->stop();
        }
        gCurrSize = 0;
        gTotalSize = 0;

        ui->henjiWidget->setCurrentIndex(6);
        wailianDeepTableShow();
        isRun=0;
        hjIndex_1=6;
    }
    else if(wjczFinish)
    {
        wjczFinish = false;
        ifWjczDeepCheck = false;
        ui->hjBackButton->setEnabled(true);
        ui->deepTaskStopButton->setEnabled(true);
        ui->henjiRings->setPersent(0);
        if(stop_timer->isActive())
        {
            stop_timer->stop();
        }
        gCurrSize = 0;
        gTotalSize = 0;

        ui->henjiWidget->setCurrentIndex(7);
        wjczTableShow();
        isRun=0;
        hjIndex_2=7;
    }
}


void MainWindow::on_deepTaskStopButton_clicked()
{
    ui->deepTaskStopButton->setEnabled(false);
    if(ifSensTask)
    {
        ifSensTask = false;
    }
    else
    {
        num = 77;
        //connect(render,SIGNAL(refresh()),this,SLOT(stop_task_slot()));
        //connect(stop_timer,SIGNAL(timeout()),this,SLOT(stop_task_slot()));
        render->test();
    }
}



void MainWindow::on_updateReportButton_clicked()
{
    if(isMainRun!=0)
    {
        QString strTitle = QString("提示");
        QString strMsg = QString("扫描任务正在运行");
        QString showMsg = "<font color='black'>"+strMsg+"</font>";
        QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
        WrrMsg->setIconPixmap(pix);
        if(NULL!=WrrMsg->button(QMessageBox::Ok))
        {
            WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
        }
        WrrMsg->exec();
        return;
    }
    static int s_nFileId = 100;

    QString localPath_2 = qApp->applicationDirPath();
    localPath_2+="/report/myxml.xml";
    QByteArray ba_2 = localPath_2.toLocal8Bit();
    char *c_str_2 = ba_2.data();
    NtCrsSntdFele(c_str_2, s_nFileId);

//    QString localPath = qApp->applicationDirPath();
//    localPath+="/report/myxml.xml";
//    QByteArray ba = localPath.toLocal8Bit();
//    char *c_str = ba.data();
//    NtCrsSntdFele(c_str, s_nFileId++);

    QString serverState = verLabel->text();
    QString strTitle;
    QString strMsg;
    if(serverState=="已连接服务器")
    {
        strTitle = QString("成功");
        strMsg = QString("上传报告成功");
    }
    else
    {
        strTitle = QString("失败");
        strMsg = QString("未连接服务器");
    }
    QString showMsg = "<font color='black'>"+strMsg+"</font>";
    QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
    WrrMsg->setIconPixmap(pix);
    if(NULL!=WrrMsg->button(QMessageBox::Ok))
    {
        WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
    }
    WrrMsg->exec();
}

void MainWindow::resultShow()
{
    QString strRes;
    strRes = QString("正常");
    ui->resLabel_1->setText(strRes);
    ui->resLabel_25->setText(strRes);
//    ui->result_button_1->setVisible(false);
    strRes = QString("本机一共安装了%1个程序").arg(CheckResultResouce::softNum);
    if(CheckResultResouce::softNum==0)
    {
        ui->result_button_2->setVisible(false);
    }
    ui->resLabel_2->setText(strRes);
    ui->resLabel_27->setText(strRes);
    strRes = QString("正常");
    ui->resLabel_3->setText(strRes);
    ui->resLabel_20->setText(strRes);
    strRes = QString("本机有%1个共享目录").arg(CheckResultResouce::shareNum);
    if(CheckResultResouce::shareNum==0)
    {
        ui->result_button_4->setVisible(false);
    }
    ui->resLabel_4->setText(strRes);
    ui->resLabel_26->setText(strRes);
    strRes = QString("正常");
    ui->resLabel_5->setText(strRes);
    ui->resLabel_24->setText(strRes);
    ui->result_button_5->setVisible(false);

    if(CheckResultResouce::pIeHistory!=NULL||CheckResultResouce::pFirefoxHistory!=NULL||CheckResultResouce::pChromeHistory!=NULL)
    {
        strRes = QString("存在");
    }
    else
    {
        strRes = QString("不存在");
        ui->result_button_6->setVisible(false);
    }
    ui->resLabel_6->setText(strRes);
    ui->resLabel_23->setText(strRes);

    if(CheckResultResouce::pUsbHistory!=NULL)
    {
        strRes = QString("存在");
    }
    else
    {
        strRes = QString("不存在");
        ui->result_button_9->setVisible(false);
    }
    ui->resLabel_9->setText(strRes);
    ui->resLabel_22->setText(strRes);

    int num=0;
    ui->dengbaoTableWidget_2->horizontalHeader()->setSectionsClickable(false);
    ui->dengbaoTableWidget_2->verticalHeader()->setVisible(false);
    ui->dengbaoTableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                                           "{background-color:rgb(215,215,215);}");
    ui->dengbaoTableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->dengbaoTableWidget_2->setColumnWidth(0,300);
    ui->dengbaoTableWidget_2->setColumnWidth(1,275);
    ui->dengbaoTableWidget_2->setColumnWidth(2,279);

    ui->dengbaoTableWidget_2->setRowCount(0);

    int row=0;
    QString dengbCkpoint,dengbResult,dengbComment;
    while (NULL != CheckResultResouce::pDtckResults)
    {
        dengbCkpoint = QString::fromLocal8Bit(CheckResultResouce::pDtckResults->result.strCkPoint);
        dengbResult = QString::fromLocal8Bit(CheckResultResouce::pDtckResults->result.strResult);
        dengbComment = QString::fromLocal8Bit(CheckResultResouce::pDtckResults->result.strComment);

        ui->dengbaoTableWidget_2->insertRow(row);

        QTableWidgetItem *item_1 = new QTableWidgetItem(dengbCkpoint);
        QTableWidgetItem *item_2 = new QTableWidgetItem(dengbResult);
        QTableWidgetItem *item_3 = new QTableWidgetItem(dengbComment);

        ui->dengbaoTableWidget_2->setItem(row,0,item_1);
        ui->dengbaoTableWidget_2->setItem(row,1,item_2);
        ui->dengbaoTableWidget_2->setItem(row,2,item_3);

        int code = CheckResultResouce::pDtckResults->result.nResult;
        if(code==2)
        {
            num++;
        }
        CheckResultResouce::pDtckResults = CheckResultResouce::pDtckResults->pNext;
        row++;
    }
    if(num==0)
    {
        strRes = QString("合规");
        ui->result_button_10->setVisible(false);
    }
    else
    {
        strRes = QString("检查出%1个不合规项").arg(num);
    }
    ui->resLabel_10->setText(strRes);
    ui->resLabel_21->setText(strRes);

    QString buttonStyle = QString("QPushButton{border-style:solid;border-width:1px;color:#9ab1c1;font: 12px 宋体;"
                                  "border-radius:5px;background-color:white;border-color:#9ab1c1;}"
                                  "QPushButton:hover{background-color:#9ab1c1;color:white;}"
                                  "QpushButton:pressed{background-color:#9ab1c1;color:white;}");
//    ui->result_button_1->setStyleSheet(buttonStyle);
    ui->result_button_2->setStyleSheet(buttonStyle);
    ui->result_button_3->setStyleSheet(buttonStyle);
    ui->result_button_4->setStyleSheet(buttonStyle);
    ui->result_button_5->setStyleSheet(buttonStyle);
    ui->result_button_6->setStyleSheet(buttonStyle);
    ui->result_button_8->setStyleSheet(buttonStyle);
    ui->result_button_9->setStyleSheet(buttonStyle);
    ui->result_button_10->setStyleSheet(buttonStyle);
}

void MainWindow::on_pushButton_clicked()
{
    login();
}

void MainWindow::on_budingButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    mainIndex=6;
}


void MainWindow::on_result_button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    mainIndex=8;
    budingResShow();
}

void MainWindow::on_result_button_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    mainIndex=9;
    yingjianResShow();
}

void MainWindow::on_result_button_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
    mainIndex=10;
    gongxiangResShow();
}

void MainWindow::on_yingjianButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    mainIndex=6;
}

void MainWindow::on_muluButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    mainIndex=6;
}

void MainWindow::on_result_button_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
    mainIndex=11;
    wailianResShow();
}

void MainWindow::on_wailianButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    mainIndex=6;
}

void MainWindow::on_result_button_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
    mainIndex=12;
    ydjzResShow();
}

void MainWindow::on_ydjzButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    mainIndex=6;
}

void MainWindow::on_ydjzButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    mainIndex=6;
}

void MainWindow::on_result_button_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(13);
    mainIndex=13;
}

//拷贝文件：
bool copyFileToPath(QString sourceDir ,QString toDir)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile  = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        createfile->remove(toDir);
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

void MainWindow::on_outHtmlButton_clicked()
{
    QString saveFileName = QFileDialog::getSaveFileName(this,QString("导出xml报告"),
                                                        QDir::currentPath(),"(*.xml);;(*.html)");
    if(saveFileName.isEmpty())
    {
        return;
    }
    else if(saveFileName.endsWith(".xml"))
    {
        QString localPath_2 = qApp->applicationDirPath();
        localPath_2 += "/report";
        isDirExist(localPath_2);
        localPath_2 += QString("/myxml.xml");
        bool ok = copyFileToPath(localPath_2,saveFileName);
        if(ok)
        {
            QString strTitle = QString("成功");
            QString strMsg = QString("已导出xml报告");
            QString showMsg = "<font color='black'>"+strMsg+"</font>";
            QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
            WrrMsg->setIconPixmap(pix);
            if(NULL!=WrrMsg->button(QMessageBox::Ok))
            {
                WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
            }
            WrrMsg->exec();
            return;
        }
        else
        {
            QString strTitle = QString("失败");
            QString strMsg = QString("请检查报告文件是否存在");
            QString showMsg = "<font color='black'>"+strMsg+"</font>";
            QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
            WrrMsg->setIconPixmap(pix);
            if(NULL!=WrrMsg->button(QMessageBox::Ok))
            {
                WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
            }
            WrrMsg->exec();
            return;
        }
    }
    else if(saveFileName.endsWith(".html"))
    {
        QString localPath_2 = qApp->applicationDirPath();
        localPath_2 += "/report";
        isDirExist(localPath_2);
        localPath_2 += QString("/myhtml.html");
        bool ok = copyFileToPath(localPath_2,saveFileName);
        if(ok)
        {
            QString strTitle = QString("成功");
            QString strMsg = QString("已导出html报告");
            QString showMsg = "<font color='black'>"+strMsg+"</font>";
            QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
            WrrMsg->setIconPixmap(pix);
            if(NULL!=WrrMsg->button(QMessageBox::Ok))
            {
                WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
            }
            WrrMsg->exec();
            return;
        }
        else
        {
            QString strTitle = QString("失败");
            QString strMsg = QString("请检查报告文件是否存在");
            QString showMsg = "<font color='black'>"+strMsg+"</font>";
            QMessageBox *WrrMsg = new QMessageBox(QMessageBox::NoIcon, strTitle, showMsg, QMessageBox::Ok, this);
            WrrMsg->setIconPixmap(pix);
            if(NULL!=WrrMsg->button(QMessageBox::Ok))
            {
                WrrMsg->button(QMessageBox::Ok)->setText(QString("确定"));
            }
            WrrMsg->exec();
            return;
        }
    }
}
