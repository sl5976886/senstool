#ifndef SEC_STRING_H
#define SEC_STRING_H

#if defined(__cplusplus)||defined(c_plusplus)

#endif // _cplusplus

#if defined(__cplusplus)||defined(c_plusplus) //跨平台定义方法
extern "C"{
#endif  // defined(__cplusplus)||defined(c_plusplus)

int sec_strcpy(char *strDst, unsigned int uiDstSize, const char *strSrc);
int sec_strcat(char *strDst, unsigned int uiDstSize, const char *strSrc);

#if defined(__cplusplus)||defined(c_plusplus) //跨平台定义方法
}
#endif  // defined(__cplusplus)||defined(c_plusplus)

#endif  // SEC_STRING_H
