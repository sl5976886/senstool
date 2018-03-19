#include "txt.h"


u78 utf8_7bits_8bits(utf8 *pucBuf, DWORD dwBufLen);

// Returned value :
// 0 : utf8
// 1 : 7bits
// 2 : 8bits
u78 utf8_7bits_8bits(utf8 *pucBuf, DWORD dwBufLen)
{
    int rv = 1;
    int ASCII7only = 1;
    utf8 *sx	= (utf8 *)pucBuf;
    utf8 *endx	= sx + dwBufLen;

    while (sx<endx)
    {
        if (!*sx)
        {											// For detection, we'll say that NUL means not UTF8
            ASCII7only = 0;
            rv = 0;
            break;
        }
        else if (*sx < 0x80)
        {			// 0nnnnnnn If the byte's first hex code begins with 0-7, it is an ASCII character.
            sx++;
        }
        else if (*sx < (0x80 + 0x40))
        {											  // 10nnnnnn 8 through B cannot be first hex codes
            ASCII7only=0;
            rv=0;
            break;
        }
        else if (*sx < (0x80 + 0x40 + 0x20))
        {					  // 110xxxvv 10nnnnnn  If it begins with C or D, it is an 11 bit character
            ASCII7only=0;
            if (sx>=endx-1)
                break;
            if (!(*sx & 0x1F) || (sx[1]&(0x80+0x40)) != 0x80) {
                rv=0; break;
            }
            sx+=2;
        }
        else if (*sx < (0x80 + 0x40 + 0x20 + 0x10))
        {								// 1110qqqq 10xxxxvv 10nnnnnn If it begins with E, it is 16 bit
            ASCII7only=0;
            if (sx>=endx-2)
                break;
            if (!(*sx & 0xF) || (sx[1]&(0x80+0x40)) != 0x80 || (sx[2]&(0x80+0x40)) != 0x80) {
                rv=0; break;
            }
            sx+=3;
        }
        else
        {													  // more than 16 bits are not allowed here
            ASCII7only=0;
            rv=0;
            break;
        }
    }
    if (ASCII7only)
        return ascii7bits;
    if (rv)
        return utf8NoBOM;
    return ascii8bits;
}


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
int convert_to_multibyte(UniMode encode, const char *pSrcBuf, int iSrcLen, char *pDstBuf, int iDstLen)
{
    int ret = 0;
    int i;
    int j;
    unsigned char tmpChar;
    unsigned char *pTmpBuf;
    unsigned char ucUtf82Utf16Buf[1024+3] = "";

    if (NULL == pSrcBuf || iSrcLen <= 0 || NULL == pDstBuf || iDstLen < iSrcLen)
        return 0;
    switch(encode)
    {
    case uni7Bit:
    case uni8Bit:
        {
            ret = iSrcLen;
            memcpy(pDstBuf, pSrcBuf, iSrcLen);
            break;
        }
    case uniUTF8:   // utf8带标识头
        {
            // 去除带标识头
            pSrcBuf += 3;
            iSrcLen -=3;
        }
    case uniUTF8_NoBOM: // utf8不带带标识头
        {
            pTmpBuf = (unsigned char*)pSrcBuf;
            j = 0;
            i = 0;
            // 转成utf16小字节序
            while (i < iSrcLen)
            {
                if (pTmpBuf[i] < 0x80)
                {
                    ucUtf82Utf16Buf[j++] = pTmpBuf[i];
                    ucUtf82Utf16Buf[j++] = 0;
                    i++;
                }
                else if (pTmpBuf[i] < (0x80 + 0x40))
                {
                    break;
                }
                else if (pTmpBuf[i] < (0x80 + 0x40 + 0x20))
                {
                    if (i+1 < iSrcLen)
                    {
                        ucUtf82Utf16Buf[j++] = ((pTmpBuf[i]&0x3)<<6) | (pTmpBuf[i+1] &0x3F);
                        ucUtf82Utf16Buf[j++] = (pTmpBuf[i]>>2)&0x7;
                    }
                    i += 2;
                }
                else if (pTmpBuf[i] < (0x80 + 0x40 + 0x20 + 0x10))
                {
                    if (i+2 < iSrcLen)
                    {
                        ucUtf82Utf16Buf[j++] = ((pTmpBuf[i+1]&0x3)<<6) | (pTmpBuf[i+2]&0x3F);
                        ucUtf82Utf16Buf[j++] = ((pTmpBuf[i]&0xF)<<4) | ((pTmpBuf[i+1]>>2)&0xF);
                    }
                    i += 3;
                }
                else
                {
                    break;
                }

                // 每次转换不超过1024字节
                if (j >= 1024 )
                {
                    ret += WideCharToMultiByte( CP_ACP, 0, (wchar_t *)ucUtf82Utf16Buf, j>>1, pDstBuf+ret, iDstLen-ret, NULL, NULL );
                    j = 0;
                }
            }

            // 转换最后剩余的字符
            if (j > 0)
            {
                ret += WideCharToMultiByte( CP_ACP, 0, (wchar_t *)ucUtf82Utf16Buf, j>>1, pDstBuf+ret, iDstLen-ret, NULL, NULL );
            }

            break;
        }
    case uni16BE:
        {
            pTmpBuf = (unsigned char*)pSrcBuf;
            iSrcLen &= 0xFFFFFFFE;
            // 转成小字节序
            for (i=0; i<iSrcLen; i+=2)
            {
                tmpChar = pTmpBuf[i];
                pTmpBuf[i] = pTmpBuf[i+1];
                pTmpBuf[i+1] = tmpChar;
            }
        }
    case uni16LE:
        {
            // 转成多字节
            ret = WideCharToMultiByte( CP_ACP, 0, (wchar_t *)(pSrcBuf+2), (iSrcLen-2)>>1, pDstBuf, iDstLen, NULL, NULL );
            break;
        }
    case uni16BE_NoBOM:
        {
            pTmpBuf = (unsigned char*)pSrcBuf;
            iSrcLen &= 0xFFFFFFFE;
            // 转成小字节序
            for (i=0; i<iSrcLen; i+=2)
            {
                tmpChar = pTmpBuf[i];
                pTmpBuf[i] = pTmpBuf[i+1];
                pTmpBuf[i+1] = tmpChar;
            }
        }
    case uni16LE_NoBOM:
        {
            // 转成多字节
            ret = WideCharToMultiByte( CP_ACP, 0, (wchar_t *)(pSrcBuf), iSrcLen>>1, pDstBuf, iDstLen, NULL, NULL );
            break;
        }
    case uniEnd:
    default:
        {
            break;
        }
    }

    return ret;
}


/*
【函数功能】判断所给内容的编码类型
【函数输入】pucBuf:待检测编码格式的指针
            dwBufLen:待检测内容的字节长度
【函数输出】无
【函数返回】编码类型，参见UniMode定义，成功，返回文本长度；失败，返回错误代码

 */
UniMode determineEncoding(utf8 *pucBuf, DWORD dwBufLen)
{
    UniMode    eEncoding = uni8Bit;

    utf8 k_Boms[uniEnd][3] = {
        {0x00, 0x00, 0x00},  // Unknown
        {0xEF, 0xBB, 0xBF},  // UTF8
        {0xFE, 0xFF, 0x00},  // Big endian
        {0xFF, 0xFE, 0x00},  // Little endian
    };

    // detect UTF-16 big-endian with BOM
    if (dwBufLen > 1 && pucBuf[0] == k_Boms[uni16BE][0] && pucBuf[1] == k_Boms[uni16BE][1])
    {
        eEncoding = uni16BE;
    }
    // detect UTF-16 little-endian with BOM
    else if (dwBufLen > 1 && pucBuf[0] == k_Boms[uni16LE][0] && pucBuf[1] == k_Boms[uni16LE][1])
    {
        eEncoding = uni16LE;
    }
    // detect UTF-8 with BOM
    else if (dwBufLen > 2 && pucBuf[0] == k_Boms[uniUTF8][0] &&
        pucBuf[1] == k_Boms[uniUTF8][1] && pucBuf[2] == k_Boms[uniUTF8][2])
    {
        eEncoding = uniUTF8;
    }
    // try to detect UTF-16 little-endian without BOM
    /*else if (m_nLen > 1 && m_pBuf[0] != NULL && m_pBuf[1] == NULL && IsTextUnicode(m_pBuf, m_nLen, NULL))
    {
        eEncoding = uni16LE_NoBOM;
    }
     UTF-16 big-endian without BOM detection is taken away scince this detection is very week
    // try to detect UTF-16 big-endian without BOM
    else if (m_nLen > 1 && m_pBuf[0] == NULL && m_pBuf[1] != NULL)
    {
        eEncoding = uni16BE_NoBOM;
    }
    */
    else
    {
        u78 detectedEncoding = utf8_7bits_8bits(pucBuf, dwBufLen);
        if (detectedEncoding == utf8NoBOM)
        {
            eEncoding = uniUTF8_NoBOM;
        }
        else if (detectedEncoding == ascii7bits)
            eEncoding = uni7Bit;
        else //(detectedEncoding == ascii8bits)
        {
            eEncoding = uni8Bit;
            // 8bit继续判断是utf16或GB2312
            utf8 *sx	= (utf8 *)pucBuf;
            utf8 *endx	= sx + dwBufLen;
            DWORD dwPos = 0;
            while (sx < endx)
            {
                dwPos = sx - pucBuf;
                // 判断 0x00是在奇数位置还是偶数位置，若0x00在奇数位置且前面一字节是 <0x80，则是小字节序，
                // 若0x00在偶数位置且后一字节 <0x80，则是大字节序
                if (0x00 == *sx)
                {
                    if ( 1 == (dwPos & 1))
                    {
                        if (( 0 < dwPos ) &&(0x80 > *(sx-1)))
                        {
                            eEncoding = uni16LE_NoBOM;
                            break;
                        }
                    }
                    else
                    {
                        if ( 0x80 > *(sx+1))
                        {
                            eEncoding = uni16BE_NoBOM;
                            break;
                        }
                    }
                }
                sx++;
            }
        }
    }

    return eEncoding;
}

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
INT32 widechar_to_multibyte(WCHAR *wpWideCharBuf, UINT32 uiWideCharNum, char *szMultiByteBuf, UINT32 uiMultiByteLen)
{
    if ((NULL == wpWideCharBuf) || (0 == uiWideCharNum) || (NULL == szMultiByteBuf) || (0 == uiMultiByteLen))
        return -1;

    int iTextLen = WideCharToMultiByte( CP_ACP, 0, wpWideCharBuf, uiWideCharNum, NULL, 0, NULL, NULL ) + 1;
    if (iTextLen >= uiMultiByteLen)
        return -2;

    int iRet = WideCharToMultiByte( CP_ACP, 0, wpWideCharBuf, uiWideCharNum, szMultiByteBuf, iTextLen, NULL, NULL );
    if (0 == iRet)
        return -3;

    szMultiByteBuf[iRet] = 0;

    return iRet;
}

/*
【函数功能】转换UTF16编码格式为多字节编码
【函数输入】WCHAR *wpWideCharBuf:待转换的buf
            UINT32 uiWideCharNum:待转换的buf字符个数
【函数输出】
            CHAR **pszMultiByteBuf:接收转换的buf，
            UINT32 uiMultiByteLen:接收转的的buf长度
【函数返回】成功返回转换的字符个数，返回-1表示参数无效，返回-2表示目的Buf申请空间失败，返回-3表示转换失败
【修改记录】
20150702 xiaowj 新增
 */
INT32 widechar_to_multibyte(WCHAR *wpWideCharBuf, UINT32 uiWideCharNum, char **pszMultiByteBuf, UINT32 &uiMultiByteLen)
{
    if ((NULL == wpWideCharBuf) || (0 == uiWideCharNum))
        return -1;

    int iTextLen = WideCharToMultiByte( CP_ACP, 0, wpWideCharBuf, uiWideCharNum, NULL, 0, NULL, NULL ) + 1;

    *pszMultiByteBuf = (char *)malloc(iTextLen);
    if (NULL == pszMultiByteBuf)
        return -2;

    int iRet = WideCharToMultiByte( CP_ACP, 0, wpWideCharBuf, uiWideCharNum, *pszMultiByteBuf, iTextLen, NULL, NULL );
    if (0 == iRet)
        return -3;

    (*pszMultiByteBuf)[iRet] = 0;

    return iRet;
}

