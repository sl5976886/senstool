#include <windows.h>
#include "MQ.h"
#include <stdio.h>
#include <tchar.h>
#include "TXConstant.h"


CMQ::CMQ()
{
    m_hFileMap=NULL;
    m_hMutex = INVALID_HANDLE_VALUE;
    m_head = NULL;
}

CMQ::~CMQ()
{
    Close();
}

DWORD CMQ::Open(LPCSTR pName, DWORD size)
{
    char temp[MAX_PATH];
    DWORD mapRet, dwRet=0;

    Close();
    //_sntprintf_s(temp, MAX_PATH, _TRUNCATE, "ShareMem_%s", pName);
    snprintf(temp, MAX_PATH, "ShareMem_%s", pName); // 内存共享文件名称
    m_hFileMap = CreateFileMappingA((HANDLE)0XFFFFFFFF, NULL, PAGE_READWRITE, 0, size, temp);// 针对不同的应用建立内存共享文件，大小根据事先的定义
    mapRet = GetLastError();
    if(m_hFileMap == NULL)
    {
        perror("CreateFileMapping");
        dwRet = mapRet;
        goto EXIT;
    }

    m_head = (struct _MQHEAD *)MapViewOfFile(m_hFileMap, FILE_MAP_READ|FILE_MAP_WRITE, 0, 0, size);// 提交文件数据，m_head指向该地址？
    // 并且将m_head放在共享文件的头部来描述这个共享文件。
    if(m_head == NULL)
    {
        perror("MapViewOfFile");
        dwRet = GetLastError();
        goto EXIT;
    }

//    _sntprintf_s(temp, MAX_PATH, _TRUNCATE, "WMutex_%s", pName);
    snprintf(temp, MAX_PATH,"WMutex_%s", pName);//创建针对该共享文件的互斥锁
    m_hMutex = CreateMutexA(NULL, FALSE, temp);
    if(m_hMutex == NULL)
    {
        perror("CreateMutex");
        dwRet = GetLastError();
        goto EXIT;
    }
    if(mapRet != ERROR_ALREADY_EXISTS)
    {
        //临时处理
        //try
        {
            WaitForSingleObject(m_hMutex,INFINITE);
            m_head->m_pid = 0;
            m_head->m_hWnd = NULL;
            m_head->m_len = size - sizeof(struct _MQHEAD);//实际长度就是共享区长度减m_head长度
            m_head->m_h = m_head->m_t = m_head->m_num = 0;//相对位置全部为0
        }
        //finally
        {
            ReleaseMutex(m_hMutex);
        }
    }
EXIT:
    if(dwRet)
        Close();
    if (mapRet == ERROR_ALREADY_EXISTS)
    {
        return ERROR_ALREADY_EXISTS;
    }
    return dwRet;
}

void CMQ::Close()
{
    if(m_head)
    {
        UnmapViewOfFile((LPCVOID)m_head);
        m_head = NULL;
    }
    if(m_hMutex)
    {
        CloseHandle(m_hMutex);
        m_hMutex = INVALID_HANDLE_VALUE;
    }
    if(m_hFileMap)
    {
        CloseHandle(m_hFileMap);
        m_hFileMap = NULL;
    }
}

DWORD CMQ::GetFreeLen()//写之前调用，用于判断当前所有剩余空间是否可以存储当前数据
{
    DWORD len=0;//共享文件剩余空间
    if(m_head != NULL)
    {
        if(m_head->m_h>m_head->m_t)
            len = m_head->m_h-m_head->m_t;
        else
            len = m_head->m_len-m_head->m_t+m_head->m_h;
    }
    return len-1;
}

void CMQ::Read(char *pc, USHORT len,int flag)
{//从共享文件内读信息
    int one,two;
    char *pBuf = (char *)(m_head + 1);

    if(m_head->m_len - GetFreeLen() < len)
    {
        fprintf(stderr,"MQRead ERROR total=%d,freelen=%d,readlen=%d\n",
            m_head->m_len,GetFreeLen(),len);
        len = (USHORT)(m_head->m_len - GetFreeLen() -1);
        SetLastError(ERROR_INTERNAL_MQBUF);
    }
    pBuf += m_head->m_h;
    if(m_head->m_t > m_head->m_h)
        one = m_head->m_t - m_head->m_h;
    else
        one = m_head->m_len - m_head->m_h;
    if(one>=len)
    {
        one = len;
        two = 0;
        m_head->m_h += len;
    }
    else
    {
        two = len - one;
        m_head->m_h = two;
    }

    if(one>0)
        CopyMemory(pc,pBuf,one);
    if(two>0)
    {
        pBuf = (char *)(m_head + 1);
        CopyMemory(pc+one,pBuf,two);
    }
}

void CMQ::Write(const char *pc, USHORT len)
{
    int one,two;
    char *pBuf = (char *)(m_head + 1);//开始指针在m_head后开始

    pBuf += m_head->m_t;//当前位置移到最后一个存储的数据的位置后
    one = m_head->m_len - m_head->m_t;//剩余空间长度
    if(one>len)//如果剩余空间能够存储当前需要存入的数据
    {
        one = len;
        two = 0;
        m_head->m_t += len;
    }
    else //如果不能，
    {
        two = len - one;//表示数据要回头
        m_head->m_t = two;//回头的位置
    }

    if(one>0)
        CopyMemory(pBuf,pc,one);
    if(two>0)
    {
        pBuf = (char *)(m_head + 1);
        CopyMemory(pBuf,pc+one,two);
    }
}

void CMQ::SetWnd(HWND hWnd)
{
    if(m_head)
        m_head->m_hWnd = hWnd;
    else
        SetLastError(ERROR_NO_INIT);
}

void CMQ::SetPID(DWORD pid)
{
    if(m_head)
        m_head->m_pid = pid;
    else
        SetLastError(ERROR_NO_INIT);
}

DWORD CMQ::GetPID()
{
    if(m_head)
        return m_head->m_pid;
    else
        SetLastError(ERROR_NO_INIT);
    return 0;
}

HWND CMQ::GetWnd()
{
    if(m_head)
        return m_head->m_hWnd;
    else
        SetLastError(ERROR_NO_INIT);
    return 0;
}

bool CMQ::IsActive()
{
    if(m_head != NULL && m_head->m_pid != 0 && GetProcessVersion(m_head->m_pid)!=0)
        return true;
    else
        return false;
}

void CMQ::SetEmpty()
{
    m_head->m_num = m_head->m_h = m_head->m_t = 0;
}
