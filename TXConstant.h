#ifndef _INC_CONSTANT
#define _INC_CONSTANT


// 自定义错误代码
#define ERROR_USER_BASE			0XE0000000				// 自定义错误代码的初始值
#define ERROR_NO_INIT			(ERROR_USER_BASE+1)		// 没有初始化
#define ERROR_INTERNAL_MQBUF	(ERROR_USER_BASE+2)		// 消息缓冲队列内部错误
#define ERROR_NO_START_APPID	(ERROR_USER_BASE+3)		// 目的应用实体没有启动
#define ERROR_NO_FIND_APPID		(ERROR_USER_BASE+4)		// 没有找到该实体标识
#define ERROR_BUF_TOO_LONG		(ERROR_USER_BASE+5)		// 发送过长的缓冲区数据
#define ERROR_FILE_TOO_LONG		(ERROR_USER_BASE+6)		// 发送过长的文件信息
#define ERROR_APP_EXIT			(ERROR_USER_BASE+7)		// 目的应用实体已退出
#define ERROR_WRONG_PARA		(ERROR_USER_BASE+8)		// 错误的参数


// 应用程序标识号（进程间收发数据时，以此为作为应用程序的唯一标识）
#define APP_GREEGUARD		1		// 主程序
#define APP_UNINSTALL       2       //卸载程序
#define APP_SEARCHDISK		11		// 根据命令进行磁盘扫描应用程序sd.exe
#define APP_UPDATE_EXIT		21		//自动升级客户端程序发送退出程序命令

// 应用程序消息类型细分
//////////////////////////////////////////////////////////////////////////
// APP_GREEGUARD（1 - 10）
//////////////////////////////////////////////////////////////////////////
#define MS_APP_GREEGUARD_DISK_SCANED	1		// 磁盘指定目录扫描完毕
#define MS_APP_GREEGUARD_CLOSE          2       //关闭GuardClient主程序

//////////////////////////////////////////////////////////////////////////
// APP_SEARCHDISK（11 - 20）
//////////////////////////////////////////////////////////////////////////
#define MS_SEARCHDISK_BEGIN				11		// 开始扫描


#endif
