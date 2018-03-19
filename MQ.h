#ifndef MQ_H
#define MQ_H
#include <windows.h>

#define MAX_BUF					0x10000			// 传输缓冲区大小(统一为64K)

#define MSG_BASE		0X10000					// 传输报文
#define MSG_CREATEBUF	0X10001					// 创建应用实体的缓冲区
#define MSG_DELETEBUF	0X10002					// 删除应用实体的缓冲区

class CMQ//针对每个应用建立内存共享文件
{
public:
    void SetEmpty();
    bool IsActive();
    DWORD GetPID();
    void SetPID(DWORD pid);
    HWND GetWnd();
    void SetWnd(HWND hWnd);
    void Close();
    DWORD Open(LPCSTR pName,DWORD size);
    DWORD GetFreeLen();
    CMQ();
    virtual ~CMQ();
    void Lock(){WaitForSingleObject(m_hMutex,INFINITE);}
    void Unlock(){ReleaseMutex(m_hMutex);}
    int &MsgNum(){return m_head->m_num;}
    void Write(const char *pc,USHORT len);
    void Read(char *pc,USHORT len,int flag);
private:
    struct _MQHEAD//采用了循环队列写的方式
    {
        DWORD m_pid;					// 进程标识
        HWND  m_hWnd;					// 接收消息的窗口句柄
        int m_num;						// 存放消息的个数
        int m_len;						// 存放消息缓冲区的长度
        int m_h,m_t;					// 消息队列的头尾下标,相等为空
        // 从头部读,从尾部写
    };
    HANDLE m_hFileMap;
    struct _MQHEAD * m_head;			// 共享内存的虚拟地址指针
    HANDLE m_hMutex;					// 互斥锁
};

#endif
