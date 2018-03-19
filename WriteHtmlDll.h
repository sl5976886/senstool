#ifndef _WRITEHTMLDLL_H
#define _WRITEHTMLDLL_H

#define		COLLENGTH		4096
#define		COLNUM			10

#define     HTML_LEFT_ITEM_LEN  128
#define     MAX_COLUMN_NUM      10

typedef struct _HTML_COLUMN_ITEM
{
    int  iColumnLen;
    char *pColumnName;
}HtmlColumnItem;

typedef struct  _HTML_WRITE_INFO
{
    char *pHtmlLeftStr;
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


extern "C" __declspec(dllimport) int WriteHtmlFile(HtmlInfo &htmlInfo, HtmlWriteInfo *pHtmlWrite, HtmlColumnInfo *colInfo,int size);
#endif
