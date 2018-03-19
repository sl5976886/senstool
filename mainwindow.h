#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QTimer>
#include <QMovie>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QPixmap>
#include <QLabel>
#include <windows.h>
#include "renderthread.h"
#include "waitdialog.h"


#define FORTEST 1     //是否依据服务器连接控制功能
//#define DEBUGTEST 2      //敏感词检查是否是测试目录
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSystemTrayIcon *tray;//托盘图标
    QMenu *menu;//托盘菜单
    QAction *reset;//菜单实现功能：恢复窗口
    QAction *quit;//菜单实现功能：退出程序
    QAction *hide;  //隐藏托盘

    RenderThread *render;

    void login();    //登录服务器

    static void __stdcall TestClientChngCb(const int &bRet, const void *pApp, const int &dwErr);
    static int __stdcall NetClientMsgCb(const WORD &wMsg, const int &nMsgContent,void *content,void *reserved);

//    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

//    QTimer *reLogin_timer;   //重新连接的定时器

    waitDialog *wdlg;

//    bool paraseCmd();

    //vector *gTaskVector;
protected:
    void closeEvent(QCloseEvent *event);//由于要关闭窗口变为隐藏至托盘图标，所以要重写close事件
//    void changeEvent(QEvent *e);

    //改写QWidget的函数，自己重新实现拖动操作
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent(QMouseEvent * event);

    void initTitleBar();

    bool ifCennected();

signals:
    void showJm();
    void sensTaskStart();

private slots:
    void sensTaskSlot();

    void sltMessageReceived(quint32 mUnum,QByteArray msg);
    void on_actionMinimize_triggered();     //最小化窗口
    void on_actionClose_triggered();        //关闭窗口


    void on_mainToolButton_clicked();

    void on_sysToolButton_clicked();

    void on_docuToolButton_clicked();

    void on_ployToolButton_clicked();

    void on_funcToolButton_clicked();

    void updateProgressbar();

    void updateBudingProgress();

    void on_scanButton_clicked();

    void on_sysButton_1_clicked();

    void on_sysButton_2_clicked();

    void on_sysButton_3_clicked();

    void on_sysButton_4_clicked();

    void on_sysButton_5_clicked();

    void on_budingButton_clicked();

    void on_budingBackButton_clicked();

    void on_budingCheckButton_clicked();

    void on_baojingButton_clicked();

    void on_baojingCheckButton_clicked();

    void on_baojingBackButton_clicked();

    void on_yingjianButton_clicked();

    void on_yingjianCheckButton_clicked();

    void on_yingjianBackButton_clicked();

    void on_muluButton_clicked();

    void on_muluCheckButton_clicked();

    void on_muluBackButton_clicked();

    void on_peizhiButton_clicked();

    void on_peizhiCheckButton_clicked();

    void on_peizhiBackButton_clicked();

    void on_wailianButton_clicked();

    void on_wjczButton_clicked();

    void on_wjnrButton_clicked();

    void on_ydjzButton_clicked();

    void on_jxwjButton_clicked();

    void on_wlMildCheckButton_clicked();

    void updateHenjiProgress();

    void on_wlDeepCheckButton_clicked();

    void on_hjBackButton_clicked();

    void on_wjczMildCheckButton_2_clicked();

    void on_wjczDeepCheckButton_2_clicked();

    void on_wjnrMildCheckButton_clicked();

    void on_wjnrDeepCheckButton_clicked();

    void on_ydjzMildCheckButton_clicked();

    void on_ydjzDeepCheckButton_clicked();

    void on_jxwjCheckButton_clicked();

    void on_clshButton_clicked();

    void on_clshBackButton_clicked();

    void TrayIconAction(QSystemTrayIcon::ActivationReason reason);//对托盘图标操作的槽：本代码实现单击图标恢复窗口功能

    void on_homeBackButton_clicked();

    void on_htmlButton_clicked();

    void on_htmlBackButton_clicked();

    void hide_slot();

    void on_wailianBackButton_clicked();

    void on_wjczBackButton_clicked();

    void on_wjnrBackButton_clicked();

    void on_ydjzBackButton_clicked();

    void on_jxwjBackButton_clicked();

    void dengbao_task_finish();

    void on_chooseDirButton_clicked();

    void heart_state_slot();

    void relogin_slot();

    void on_deepTaskStopButton_clicked();

    void stop_task_slot();

    void on_updateReportButton_clicked();

//    void if_show_slot();

    void task_start_slot();
    void on_pushButton_clicked();

    void on_budingButton_2_clicked();

    void on_result_button_2_clicked();

    void on_result_button_3_clicked();

    void on_result_button_4_clicked();

    void on_yingjianButton_2_clicked();

    void on_muluButton_2_clicked();

    void on_result_button_6_clicked();

    void on_wailianButton_2_clicked();

    void on_result_button_9_clicked();

    void on_ydjzButton_2_clicked();

    void on_ydjzButton_3_clicked();

    void on_result_button_10_clicked();

    void sens_timer_slot();

    void on_outHtmlButton_clicked();

private:
    Ui::MainWindow *ui;

    QLabel *verLabel;     //状态栏label
    QLabel *stateLabel;
    //自己重新实现拖动操作
    QPoint mousePosition;
    bool isMousePressed;

    void initStyle();
    void buttonInit();
    void statusInit();

//    QTimer *show_timer;
    QTimer *m_timer;
    QTimer *buding_timer;
    QTimer *henji_timer;
    QTimer *dengbao_timer;
    QTimer *stop_timer;    //停止任务的定时器

    QTimer *sens_tiemr;

    QTimer *heart_timer;    //发送心跳的定时器
    int failTime;        //心跳失败次数


    int m_persent;
    int m_persent_2;
    int m_persent_3;
    int mIndex,mIndex_2,mIndex_3,mIndex_4,mIndex_5;
    int hjIndex_1,hjIndex_2,hjIndex_3,hjIndex_4,hjIndex_5;
    int mKind;
    int hjKind;
    int flag;
    int reportIndex;
    int mainIndex;
    int clIndex;

    bool ifTaskRun();   //是否有任务正在运行
    int isMainRun;   //是否有检查任务
    int isRun;    //是否有痕迹检查任务正在运行 0:没有  非0:有
    int isSysRun;  //是否有系统任务正在运行 0:没有 非0:有
    int isClRun;   //是否有策略审核任务正在运行 0:没有  1:有

    bool ifUsbDeepCheck;
    bool ifIntDeepCheck;
    bool ifWjczDeepCheck;

    QString buttonStyle;
    QString buttonStyle_2;
    QString style_2;
    QString buttonStyle_3;
    QString textEditStyle;
    QString buttonStyle_4;
    QString toolButtonStyle;


    QPixmap pix;

    QMovie *loadMovie;

    void initSysTrayIcon();    //初始化系统托盘
    void initMainLabel();

    void budingTableShow();
    void budingResShow();
    void chengxuTableShow();
    void yingjianTableShow();
    void yingjianResShow();
    void gongxiangTableShow();
    void gongxiangResShow();
    void peizhiTableShow();

    void wailianTableShow();
    void wailianResShow();
    void wailianDeepTableShow();   //外联深度检查
    void wjczTableShow();
    void wjnrTableShow();
    void ydjzTableShow();
    void ydjzResShow();
    void ydjzDeepTableShow();    //usb深度检查
    void jxwjTableShow();

    void dengbaoTableShow();

    void resultShow();

    void sensResNotShow();

    void ifUpdate();
};

#endif // MAINWINDOW_H
