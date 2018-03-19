#ifndef __TXT_H__
#define __TXT_H__

#include <Windows.h>

enum u78 {utf8NoBOM=0, ascii7bits=1, ascii8bits=2};
typedef unsigned short utf16; // 16 bits
typedef unsigned char utf8; // 8 bits
typedef unsigned char ubyte;

enum UniMode {uni8Bit=0, uniUTF8=1, uni16BE=2, uni16LE=3, uniUTF8_NoBOM=4, uni7Bit=5, uni16BE_NoBOM=6, uni16LE_NoBOM=7, uniEnd};

/*
���������ܡ�ת�������ʽΪ���ֽڱ���
���������롿encode:��ת��buf�ı����ʽ���μ�UniMode
            pSrcBuf:��ת����buf
            iSrcLen:��ת����buf�ֽڳ���
            pDstBuf:����ת����buf
            iDstLen:����ת�ĵ�buf����
�������������            
���������ء�ת�����ֽڳ���
���޸ļ�¼��
20130507 xiaowj UTF16�����ʽ�����޸�

 */
UniMode determineEncoding(utf8 *pucBuf, DWORD dwBufLen);

/*
���������ܡ��ж��������ݵı�������
���������롿pucBuf:���������ʽ��ָ��
			dwBufLen:��������ݵ��ֽڳ���
�������������            
���������ء��������ͣ��μ�UniMode���壬�ɹ��������ı����ȣ�ʧ�ܣ����ش������

 */
int convert_to_multibyte(UniMode encode, const char *pSrcBuf, int iSrcLen, char *pDstBuf, int iDstLen);

/*
���������ܡ�ת��UTF16�����ʽΪ���ֽڱ���
���������롿WCHAR *wpWideCharBuf:��ת����buf
            UINT32 uiWideCharNum:��ת����buf�ַ�����
            UINT32 uiMultiByteLen:����ת��buf����
�����������
            CHAR *szMultiByteBuf:����ת����buf��
���������ء��ɹ�����ת�����ַ�����������-1��ʾ������Ч������-2��ʾĿ��Buf�ռ䲻��������-3��ʾת��ʧ��
���޸ļ�¼��
20150702 xiaowj ����
 */
INT32 widechar_to_multibyte(WCHAR *wpWideCharBuf, UINT32 uiWideCharNum, char *szMultiByteBuf, UINT32 uiMultiByteLen);

/*
���������ܡ�ת��UTF16�����ʽΪ���ֽڱ���
���������롿WCHAR *wpWideCharBuf:��ת����buf
            UINT32 uiWideCharNum:��ת����buf�ַ�����
�����������
            CHAR **pszMultiByteBuf:����ת����buf��
            UINT32 uiMultiByteLen:����ת�ĵ�buf����
���������ء��ɹ�����ת�����ַ�����������-1��ʾ������Ч������-2��ʾĿ��Buf�ռ䲻��������-3��ʾת��ʧ��
���޸ļ�¼��
20150702 xiaowj ����
 */
INT32 widechar_to_multibyte(WCHAR *wpWideCharBuf, UINT32 uiWideCharNum, char **pszMultiByteBuf, UINT32 &uiMultiByteLen);

#endif
