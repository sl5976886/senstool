#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QObject>
#include <QThread>
#include <string>
#include <vector>
#include <QTimer>

using namespace std;

extern bool isDirExist(QString fullPath);
extern bool Write2Xml(char *szXml);

enum NET_MSG_TYPE_E
{
    NET_MSG_UNKNOWN = 0,
    NET_MSG_AUTH_REQ	 ,		//1客户端认证请求
    NET_MSG_AUTH_RSP	 ,		//2认证响应
    NET_MSG_TRANS_FILE	 ,		//3传输文件
//	NET_MSG_KEY_POLICY	 ,		//4关键词策略表
    NET_MSG_WARN_LEVEL 	 ,		//4告警等级策略表
    NET_MSG_KEY3_POLICY	 ,		//5关键词策略表
    NET_MSG_EXT_POLICY	 ,		//6后缀名搜索策略表
    //系统控制命令
    NET_MSG_USB_INSERT	 ,		//07USB插入记录
    NET_MSG_USB_REMOVE	 ,		//08USB拔出记录
    NET_MSG_USB_ENABLE	 ,		//09允许USB
    NET_MSG_USB_DISABLE	 ,		//10禁止USB
    NET_MSG_USB_READONLY ,		//11只读USB
    NET_MSG_NET_ENABLE	 ,		//12允许网络访问
    NET_MSG_NET_SVRONLY	 ,		//13只允许网络连接服务器
    NET_MSG_NET_DISABLE	 ,		//14禁止网络
    NET_MSG_BLOCK_ALL	 ,		//15禁止终端的所有操作(键盘和鼠标)
    NET_MSG_UNBLOCK_ALL	 ,		//16恢复终端的所有操作(键盘和鼠标)
    NET_MSG_SNAP_SCRN	 ,		//17上传截屏

    NET_MSG_HEART_REQ	 ,		//18心跳请求
    NET_MSG_HEART_RSP	 ,		//19心跳响应
    NET_MSG_NTP_REQ	 	 ,		//20网络时间请求
    NET_MSG_NTP_RSP	 	 ,		//21网络时间响应
    NET_MSG_CTRLSTATE_REQ,		//22获取终端控制状态请求
    NET_MSG_CTRLSTATE_RSP,		//23获取终端控制状态响应
    NET_MSG_SOFT_CLIVER	 ,		//24客户端软件版本
    NET_MSG_SRCH_EXTSET	 ,		//25设置搜索后缀名
    NET_MSG_SRCH_EXTGET	 ,		//26请求获取搜索后缀名
    NET_MSG_SRCH_EXTRPT	 ,		//27报告当前搜索后缀名
    NET_MSG_UP_LOGCUR	 ,		//28上传当前日志
    NET_MSG_UP_LOGDAY	 ,		//29上传指定天的日志
    NET_MSG_UP_LOGALL	 ,		//30上传所有日志
    NET_MSG_UP_LOG_EXT	 ,		//31上传指定要求的日志
    NET_MSG_UP_PROCESS	 ,		//32上传进程列表
    NET_MSG_UP_SERVICES	 ,		//33上传服务列表
    NET_MSG_UP_SOFTWARE	 ,		//34上传本地安装软件列表
    NET_MSG_UP_URLHIS	 ,		//35上传网页访问历史
    NET_MSG_UP_SCRNCUR	 ,		//36上传当前截屏
    NET_MSG_UP_SCRNMEM	 ,		//37上传内存最近的截屏
    NET_MSG_UP_DIR		 ,		//38上传指定文件夹
    NET_MSG_UP_FILE		 ,		//39上传指定文件
    NET_MSG_TFILE_CHUNK	 ,		//40指定文件的一部分
    NET_MSG_TFILE_EOF	 ,		//41指定文件的一部分
    NET_MSG_ALARM_EVENT	 ,		//42上报告警事件
    NET_MSG_ALARM_LIST	 ,		//43上报告警事件
    NET_MSG_TFILE_CMD	 ,		//44文件传输相关的控制命令
    NET_MSG_TFILE_CK_END ,		//45文件传输的最后一个数据块
    NET_MSG_TFILE_ACK	 ,		//46文件传输命令的确认,会携带原因值
    NET_MSG_ALARM_NET	 ,		//47上报网络告警事件
    NET_MSG_ALARM_REG	 ,		//48上报注册表修改告警事件
    NET_MSG_ALARM_FILECHG,		//49上报文件修改告警事件
    NET_MSG_DISK_CHECK	 ,		//50专项检查
    NET_MSG_REG_MON_PLY	 ,		//51下发注册表监控键值列表
    NET_MSG_FILE_MON_PLY ,		//52下发文件监测列表 --- 由于文件监测列表会很长,故以END表示结束
    NET_MSG_FILE_MON_END ,		//53
    NET_MSG_USR_SET_PWD  ,		//54用户发起设置密码请求
    NET_MSG_USR_GET_SYSINFO,	//55获得所有终端信息
    NET_MSG_DISK_DIR_SCAN,		//56用户终端磁盘/目录关键词扫描
    NET_MSG_LOGINOUT     ,		//57用户终端登陆退出,用于上层记录
    NET_MSG_CTRL_STAS_REQ,		//58下发终端控制状态请求
    NET_MSG_CTRL_STAS_RSP,		//59终端控制状态响应
    NET_MSG_TFILE_CHKEOF ,		//60指定文件最后一部分
    NET_MSG_VERSION_FILES,		//61版本号和文件数目
    NET_MSG_SEND_FILE	 ,		//62发送文件
    NET_MSG_TASK_OVER	 ,		//63所有通信完成,断开连接
    NET_MSG_ERR_NTFY	 ,		//64对端发送的错误通知
    NET_MSG_SGL_NOTICE	 ,		//65单点的消息通知
    NET_MSG_BROADCAST	 ,		//66广播消息
    NET_MSG_FORCEUPDATE  ,		//67强制客户端升级
    NET_MSG_CUST_CMD     ,		//68发送自定义命令
    NET_MSG_SVR_IP_PORT  ,		//69服务器变更IP地址和端口号- 控制服务器和自动更新服务器
    NET_MSG_CFG_POLICY = 91,	//91 全局策略配置(keyword filetypes usb net ctrl flag)

    NET_MSG_CUST_CMDREQ = 98 ,	//98终端自定义命令请求
    NET_MSG_CUST_CMDRSP = 99  ,	//99自定义命令响应
    NET_MSG_ACK = 100	 ,		//100上报告警事件
    NET_MSG_TYPE_ERR
};

enum TASK_STATE
{
    TASK_WAIT = 0,
    TASK_RUN,
    TASK_SENDFILE,
    TASK_FINISH
};


class RenderThread : public QThread
{
    Q_OBJECT
public:
    explicit RenderThread(QObject *parent = 0);
    ~RenderThread();
    void test();
    void stop();
//    static int CallBackFunc(void *pPara, void *pReserved);
protected:
    void run();
    volatile bool stopped;
signals:
    void refresh();
private slots:
//    void report_slot();
};

#endif // RENDERTHREAD_H
