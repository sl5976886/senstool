// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 HTMLLOG_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// HTMLLOG_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
// #ifdef HTMLLOG_EXPORTS
// #define HTMLLOG_API __declspec(dllexport)
// #else
// #define HTMLLOG_API __declspec(dllimport)
// #endif

#ifndef _HTML_LOG__
#define _HTML_LOG__

//#include "xmlcc.h"
#include <vector>
using namespace std;

#define		COLLENGTH		4096
#define		COLNUM			10

#define     HTML_LEFT_ITEM_LEN  128
#define     MAX_COLUMN_NUM      10

typedef struct _HTML_COLUMN_ITEM
{
    int  iColumnLen;
    const char *pColumnName;
}HtmlColumnItem;

typedef struct  _HTML_WRITE_INFO
{
    const char *pHtmlLeftStr;
    int  iTotalNum;
    //int  iTableIndex;
    int  iColumnNum;
    HtmlColumnItem  htmlColumn[MAX_COLUMN_NUM];
}HtmlWriteInfo;


//右边部分表格列名，列宽
typedef struct _HTMLTABLEINFO{
    int  tableIndex;
    char colName[COLLENGTH];
    int  colLength;
}HtmlTableInfo, _PHTMLTABLEINFO;

typedef struct _HTMLLEFTINFO{
    char htmlLeftStr[COLLENGTH];
    int num;
}HtmlLeftInfo;

typedef struct _HTMLINFO{
    char htmlFilePath[COLLENGTH]; //html保存路径
    char htmlTitle[COLLENGTH];//html文件标题
    int htmlLeftNum;   //html左半部分总共条数
}HtmlInfo, _PHTMLINFO;

typedef struct _HTMLCOLUMNINFO{
    int  tableIndex;
    int  colIndex;
    char column[COLLENGTH];
}HtmlColumnInfo;

//成功返回0，失败返回错误码
//int WriteHtmlFile(HtmlInfo &htmlInfo, HtmlLeftInfo *htmlLeftInfo, HtmlTableInfo *htmlTableInfo, vector<HtmlColumnInfo> &colInfo);
//int WriteHtmlFile(HtmlInfo &htmlInfo, HtmlWriteInfo *pHtmlWrite, vector<HtmlColumnInfo> &colInfo);
//extern HtmlTableInfo htmlTableInfo[];


#endif  // _HTML_LOG__
