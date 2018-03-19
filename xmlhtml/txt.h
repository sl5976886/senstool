#ifndef __TXT_H__
#define __TXT_H__

#include <Windows.h>

enum u78 {utf8NoBOM=0, ascii7bits=1, ascii8bits=2};
typedef unsigned short utf16; // 16 bits
typedef unsigned char utf8; // 8 bits
typedef unsigned char ubyte;

enum UniMode {uni8Bit=0, uniUTF8=1, uni16BE=2, uni16LE=3, uniUTF8_NoBOM=4, uni7Bit=5, uni16BE_NoBOM=6, uni16LE_NoBOM=7, uniEnd};

/*
【函数功能】转换编码格式为多字节编码
【函数输入】encode:待转换buf的编码格式，参见UniMode
            pSrcBuf:待转换的buf
            iSrcLen:待转换的buf字节长度
            pDstBuf:接收转换的buf
            iDstLen:接收转的的buf长度
【函数输出】无            
【函数返回】转换的字节长度
【修改记录】
20130507 xiaowj UTF16编码格式解析修改

 */
UniMode determineEncoding(utf8 *pucBuf, DWORD dwBufLen);

/*
【函数功能】判断所给内容的编码类型
【函数输入】pucBuf:待检测编码格式的指针
			dwBufLen:待检测内容的字节长度
【函数输出】无            
【函数返回】编码类型，参见UniMode定义，成功，返回文本长度；失败，返回错误代码

 */
int convert_to_multibyte(UniMode encode, const char *pSrcBuf, int iSrcLen, char *pDstBuf, int iDstLen);

/*
【函数功能】转换UTF16编码格式为多字节编码
【函数输入】WCHAR *wpWideCharBuf:待转换的buf
            UINT32 uiWideCharNum:待转换的buf字符个数
            UINT32 uiMultiByteLen:接收转换buf长度
【函数输出】
            CHAR *szMultiByteBuf:接收转换的buf，
【函数返回】成功返回转换的字符个数，返回-1表示参数无效，返回-2表示目的Buf空间不够，返回-3表示转换失败
【修改记录】
20150702 xiaowj 新增
 */
INT32 widechar_to_multibyte(WCHAR *wpWideCharBuf, UINT32 uiWideCharNum, char *szMultiByteBuf, UINT32 uiMultiByteLen);

/*
【函数功能】转换UTF16编码格式为多字节编码
【函数输入】WCHAR *wpWideCharBuf:待转换的buf
            UINT32 uiWideCharNum:待转换的buf字符个数
【函数输出】
            CHAR **pszMultiByteBuf:接收转换的buf，
            UINT32 uiMultiByteLen:接收转的的buf长度
【函数返回】成功返回转换的字符个数，返回-1表示参数无效，返回-2表示目的Buf空间不够，返回-3表示转换失败
【修改记录】
20150702 xiaowj 新增
 */
INT32 widechar_to_multibyte(WCHAR *wpWideCharBuf, UINT32 uiWideCharNum, char **pszMultiByteBuf, UINT32 &uiMultiByteLen);

#endif
