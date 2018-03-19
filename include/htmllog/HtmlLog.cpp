// HtmlLog.cpp : 定义 DLL 应用程序的导出函数。
//

#include <windows.h>
#include <tchar.h>
#include "HtmlLog.h"

#include "SecString.h"
#include "global.h"
#include <QDebug>
#include <QFile>

#ifndef __cplusplus
#error compiler is not a C++ one; use a C++ compiler for XMLCC:: ~8>
#endif

#ifdef _WIN32
#pragma warning(disable:4127)
#endif

#ifdef _WIN32
#ifdef _DEBUG // find memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // _DEBUG
#endif // _WIN32

#include "xmlcc.h"
//#include "include/atlstr.h"
//#include <iterator>
#include <fstream>

// #ifdef _DEBUG
//  #pragma comment(lib, "XMLCC_D.lib")
// #else
//  #pragma comment(lib, "XMLCC_R.lib")
// #endif

int index;

void WriteTdRow(XMLCC::Builder builder, XMLCC::Object *tr, int i, int m, vector<HtmlColumnInfo>& colInfo)
{
    if (index<colInfo.size())
    {
        while (index<colInfo.size() && colInfo[index].tableIndex == i && colInfo[index].colIndex == m)
        {
            XMLCC::Object *td1 = builder.create(XMLCC::Types::Element, "td", colInfo[index].column);
            builder.create(td1, XMLCC::Types::Attribute, "class", "linefeed");
            tr->addObject(td1);
            if ((index<colInfo.size()-1) && (colInfo[index].tableIndex != colInfo[index+1].tableIndex))
            {
                ++index;
                break;
            }
            ++index;
        }
    }
    return;
}
static string styleStr = "";

// 这是导出函数的一个示例。
int WriteHtmlFile(HtmlInfo &htmlInfo, HtmlLeftInfo *htmlLeftInfo, HtmlTableInfo *htmlTableInfo, vector<HtmlColumnInfo> &colInfo)
{
    //CString styleStr = "";
    styleStr = "";
    styleStr = "\r\n@CHARSET \"GB2312\";";
    styleStr = styleStr + "\r\nbody, div, ul, ol, li, dl, dt, dd, h1, h2, h3, h4, h5, h6, pre, form, blockquote { margin: 0; padding: 0; }";
    styleStr = styleStr + "\r\nhtml, body { min-width: 800px; }";
    styleStr = styleStr + "\r\nbody { font: normal normal 14px/1.5 Tahoma, Verdana, \"BitStream vera Sans\", Arial, Helvetica, \"Hiragino Sans GB\", \"Microsoft Yahei\", sans-serif; color: #333; }";
    styleStr = styleStr + "\r\nbody.one-column { background-color: #FFF; }";
    styleStr = styleStr + "\r\nbody.two-column { background-color: #EEE; }";
    styleStr = styleStr + "\r\ntable {width: 100%;font-size: 14px; line-height: 1.5;table-layout: fixed;border-collapse: collapse; border: 1px solid transparent; border-color: #FFF transparent transparent #FFF;background-color: #FFF;}";
    styleStr = styleStr + "\r\ntable th, table td { text-align: left; vertical-align: top; padding: 5px 8px; border: 1px solid #E8E8E8; }";
    styleStr = styleStr + "\r\ntable thead th { background-color: #CCC; border-bottom: 1px solid #A6A6A6 !important; border-width: 0 0 1px; vertical-align: middle; }";
    styleStr = styleStr + "\r\nfieldset { background-color: #F3F3F3; padding: 10px; margin: 15px 0; border: 1px solid #A6A6A6; border-radius: 5px; }";
    styleStr = styleStr + "\r\n.linefeed { word-wrap: break-word; word-wrap: normal\\0; word-break: break-all; white-space: normal; }";
    styleStr = styleStr + "\r\nh2.title { border-bottom: 1px dashed #CCC; font-size: 18px; padding: 0 5px 5px; margin: 20px 0 15px; }";
    styleStr = styleStr + "\r\n.two-column .risk, .two-column .info { padding: 0; margin-bottom: 80px; }";
    styleStr = styleStr + "\r\n.table-wrapper { border: 1px solid #A6A6A6; box-sizing: border-box; margin-bottom: 15px; }";
    styleStr = styleStr + "\r\n.table-row-even td { background-color: #F5F5F5 !important; }";
    styleStr = styleStr + "\r\n#sidebar {width: 200px;position: fixed; top: 0; bottom: 0; left: 0;overflow-x: hidden; overflow-y: auto;background-color: #F9F9F9;border-right: 1px solid #CCC;box-shadow: 0 0 20px #CCC;font-size: 12px;padding: 15px 0 30px 30px;}";
    styleStr = styleStr + "\r\n#sidebar ul { list-style: none outside none; margin-top: 5px; }";
    styleStr = styleStr + "\r\n#sidebar b { font-size: 13px; text-decoration: underline; margin-top: 15px; display: inline-block; }";
    styleStr = styleStr + "\r\n#sidebar a:link, #sidebar a:visited { text-decoration: none; color: #333; outline: none; }";
    styleStr = styleStr + "\r\n#sidebar a:hover { color: #888; text-decoration: underline; }";
    styleStr = styleStr + "\r\n#content { margin: 40px 100px 50px 265px; }";
    styleStr = styleStr + "\r\n.one-column .site { border: 1px solid #A6A6A6; background-color: #F5F5F5; padding: 20px; margin: 20px; }";
    styleStr = styleStr + "\r\n.one-column .site h1 { font-size: 30px; margin-bottom: 10px; }";
    styleStr = styleStr + "\r\n.one-column .site-summary th, .site-summary td { vertical-align: middle; }";
    styleStr = styleStr + "\r\n.one-column .site-summary tbody th { background-color: #E8E8E8; text-align: right; }";
    styleStr = styleStr + "\r\n.risk { padding: 20px; margin-bottom: 10px; }";
    styleStr = styleStr + "\r\n.risk-summary { border: 1px solid #A6A6A6; padding: 10px; background-color: #F5F5F5; margin-bottom: 15px; }";
    styleStr = styleStr + "\r\n.risk-summary dt, .risk-summary dd { padding: 8px; border: 1px dotted #CCC; }";
    styleStr = styleStr + "\r\n.risk-summary dt { float: left; width: 100px; text-align: right; padding-right: 15px; border-width: 0 0 1px 0; }";
    styleStr = styleStr + "\r\n.risk-summary dd { overflow: hidden; padding-left: 15px; border-width: 0 0 1px 1px; }";
    styleStr = styleStr + "\r\n.risk-summary dt.last { border-width: 0; }";
    styleStr = styleStr + "\r\n.risk-summary dd.last { border-width: 0 0 0 1px; }";
    styleStr = styleStr + "\r\n.db .risk-list tbody th, .summary table.info-list tbody th { background-color: #F5F5F5; text-align: right; }";


    try{

        XMLCC::OBJ::Root *root = 0;
        XMLCC::Builder builder;
        root = builder.createRoot(htmlInfo.htmlFilePath);
        root->setString(htmlInfo.htmlFilePath);

    //html
    root->addObject(builder.createDoctype());
    XMLCC::Object *html = builder.create(XMLCC::Types::Element, "html");
    root->addObject(html);

    //head
    XMLCC::Object *head = builder.create(XMLCC::Types::Element, "head");
    html->addObject(head);

    //meta
    XMLCC::Object *meta = builder.create(XMLCC::Types::Element, "META");
    builder.create( meta, XMLCC::Types::Attribute, "http-equiv", "Content-Type" );
    builder.create( meta, XMLCC::Types::Attribute, "content", "text/html; charset=GB2312" );
    head->addObject(meta);

    //title
    XMLCC::Object *title = builder.create(XMLCC::Types::Element, "title", htmlInfo.htmlTitle);
    head->addObject(title);

    //style
    XMLCC::Object *style = builder.create(XMLCC::Types::Element, "style", (XMLCC::String)styleStr);
    builder.create(style, XMLCC::Types::Attribute, "type", "text/css");
    head->addObject(style);

    //body
    XMLCC::Object *body = builder.create(XMLCC::Types::Element, "body");
    builder.create(body, XMLCC::Types::Attribute, "class", "two-column web");
    html->addObject(body);

    //div id = "sidebar"
    XMLCC::Object *div1 = builder.create(XMLCC::Types::Element, "div");
    builder.create(div1, XMLCC::Types::Attribute, "id", "sidebar");
    body->addObject(div1);

    //div class = "catelog"
    XMLCC::Object *div2 = builder.create(XMLCC::Types::Element, "div");
    builder.create(div2, XMLCC::Types::Attribute, "class", "catalog");
    div1->addObject(div2);

    //b
    XMLCC::Object *b = builder.create(XMLCC::Types::Element, "b", "扫描结果");
    div2->addObject(b);

    //ul
    XMLCC::Object *ul = builder.create(XMLCC::Types::Element, "ul");
    div2->addObject(ul);

    //li
    char liNumStr[100] = {0};
    char liStr[100] = {0};
    for (int i = 0; i < htmlInfo.htmlLeftNum; i++)
    {
        XMLCC::Object *li = builder.create(XMLCC::Types::Element, "li", "- ");
        XMLCC::Object *a = builder.create(XMLCC::Types::Element, "a", htmlLeftInfo[i].htmlLeftStr);
        char herfStr[100] = {0};
        sec_strcpy(herfStr, 100, "#RiskType_");
        char numStr[10] = {0};
        itoa(i+1, numStr, 10);
        sec_strcat(herfStr, 100, numStr);
        builder.create(a, XMLCC::Types::Attribute, "href", herfStr);
        li->addObject(a);


        sec_strcpy(liStr, 100, " (");
        itoa(htmlLeftInfo[i].num, liNumStr, 10);
        sec_strcat(liStr, 100, liNumStr);
        sec_strcat(liStr, 100, ")");
        builder.create(li, XMLCC::Types::Value, liStr);
        div2->addObject(li);
    }

    //div3 id = "content"
    XMLCC::Object *div3 = builder.create(XMLCC::Types::Element, "div");
    builder.create(div3, XMLCC::Types::Attribute, "id", "content");
    body->addObject(div3);

    //右边部分
    int tableIndex = 0;
    int tableIndex1 = 0;
    XMLCC::Object *div4=NULL;
    XMLCC::Object *h2 = NULL;
    XMLCC::Object *div5 = NULL;
    XMLCC::Object *table = NULL;
    XMLCC::Object *colgroup = NULL;
    XMLCC::Object *thead = NULL;
    XMLCC::Object *tr = NULL;
    XMLCC::Object *tbody = NULL;
    char idStr[100] = {0};
    char colWidth[1024] = {0};
    for (int i = 0; i < htmlInfo.htmlLeftNum; i++)
    {
        //div class="risk" id="RiskType_1"
        div4 = builder.create(XMLCC::Types::Element, "div");
        sec_strcpy(idStr, 100, "RiskType_");
        char numStr[10] = {0};
        itoa(i+1, numStr, 10);
        sec_strcat(idStr, 100, numStr);
        builder.create(div4, XMLCC::Types::Attribute, "class", "risk");
        builder.create(div4, XMLCC::Types::Attribute, "id", idStr);
        div3->addObject(div4);

        h2 = builder.create(XMLCC::Types::Element, "h2", htmlLeftInfo[i].htmlLeftStr);
        builder.create(h2, XMLCC::Types::Attribute, "class", "risk-title title");
        div4->addObject(h2);

        //div class="table-wrapper"
        div5 = builder.create(XMLCC::Types::Element, "div");
        builder.create(div5, XMLCC::Types::Attribute, "class", "table-wrapper");
        div4->addObject(div5);

        //table
        table = builder.create(XMLCC::Types::Element, "table");
        builder.create(table, XMLCC::Types::Attribute, "class", "risk-list");
        div5->addObject(table);

        //colgroup
        colgroup = builder.create(XMLCC::Types::Element, "colgroup");
        table->addObject(colgroup);

        XMLCC::Object *col = NULL;

        while (htmlTableInfo[tableIndex].colName[0])
        {
            col = builder.create(XMLCC::Types::Element, "col");
            sprintf(colWidth,"width: %d%%;", htmlTableInfo[tableIndex].colLength);
            builder.create(col, XMLCC::Types::Attribute, "style", colWidth);
            colgroup->addObject(col);
            tableIndex++;
        }
        tableIndex++;

        //thead
        thead = builder.create(XMLCC::Types::Element, "thead");
        table->addObject(thead);

        //tr
        tr = builder.create(XMLCC::Types::Element, "tr");
        thead->addObject(tr);
        //th
        XMLCC::Object *th = NULL;
        while (htmlTableInfo[tableIndex1].colName[0])
        {
            th = builder.create(XMLCC::Types::Element, "th", htmlTableInfo[tableIndex1].colName);
            tr->addObject(th);
            tableIndex1++;
        }
        tableIndex1++;

        //tbody
        tbody = builder.create(XMLCC::Types::Element, "tbody");
        table->addObject(tbody);


        for (int m = 0; m < htmlLeftInfo[i].num; m++)
        {
            XMLCC::Object *trRow = builder.create(XMLCC::Types::Element, "tr");
            if (m%2 == 0)
            {
                builder.create(trRow, XMLCC::Types::Attribute, "class", "table-row-odd");
            }
            else
            {
                builder.create(trRow, XMLCC::Types::Attribute, "class", "table-row-even");
            }
            tbody->addObject(trRow);

            WriteTdRow(builder, trRow, i, m, colInfo);
        }
    }

    std::fstream file;

    std::string strFileName = root->getFileName( );
    char* charFileName = (char*)(strFileName.c_str( ));

    file.open( charFileName, std::ios::out );

    if(file.fail())
    {
        index = 0;
        return GetLastError();
    }

     file << root << std::endl << std::flush;

    file.close( );
//	std::cout<<std::endl<<std::endl<<std::flush;
    delete root;

     } catch( XMLCC::ERR::Exception e ) { // own exception class

    //	 std::cout << e;
    } catch( std::exception e ) { // standard exception class
     // std::cout << "std::exception caught:" << std::endl << std::flush;
      e.what( );
     } catch( ... ) { // any other exception thrown
        // std::cout << "Strange exception caught:" << std::endl << std::flush;
         XMLCC::ERR::Exception e;
         e.nuke( ); // nuke screen
  } // try
    index = 0;
    return 0;
}

int WriteHtmlFile(HtmlInfo &htmlInfo, HtmlWriteInfo *pHtmlWrite, vector<HtmlColumnInfo> &colInfo)
{
    //CString styleStr = "";
    styleStr = "";
    styleStr = "\r\n@CHARSET \"GB2312\";";
    styleStr = styleStr + "\r\nbody, div, ul, ol, li, dl, dt, dd, h1, h2, h3, h4, h5, h6, pre, form, blockquote { margin: 0; padding: 0; }";
    styleStr = styleStr + "\r\nhtml, body { min-width: 800px; }";
    styleStr = styleStr + "\r\nbody { font: normal normal 14px/1.5 Tahoma, Verdana, \"BitStream vera Sans\", Arial, Helvetica, \"Hiragino Sans GB\", \"Microsoft Yahei\", sans-serif; color: #333; }";
    styleStr = styleStr + "\r\nbody.one-column { background-color: #FFF; }";
    styleStr = styleStr + "\r\nbody.two-column { background-color: #EEE; }";
    styleStr = styleStr + "\r\ntable {width: 100%;font-size: 14px; line-height: 1.5;table-layout: fixed;border-collapse: collapse; border: 1px solid transparent; border-color: #FFF transparent transparent #FFF;background-color: #FFF;}";
    styleStr = styleStr + "\r\ntable th, table td { text-align: left; vertical-align: top; padding: 5px 8px; border: 1px solid #E8E8E8; }";
    styleStr = styleStr + "\r\ntable thead th { background-color: #CCC; border-bottom: 1px solid #A6A6A6 !important; border-width: 0 0 1px; vertical-align: middle; }";
    styleStr = styleStr + "\r\nfieldset { background-color: #F3F3F3; padding: 10px; margin: 15px 0; border: 1px solid #A6A6A6; border-radius: 5px; }";
    styleStr = styleStr + "\r\n.linefeed { word-wrap: break-word; word-wrap: normal\\0; word-break: break-all; white-space: normal; }";
    styleStr = styleStr + "\r\nh2.title { border-bottom: 1px dashed #CCC; font-size: 18px; padding: 0 5px 5px; margin: 20px 0 15px; }";
    styleStr = styleStr + "\r\n.two-column .risk, .two-column .info { padding: 0; margin-bottom: 80px; }";
    styleStr = styleStr + "\r\n.table-wrapper { border: 1px solid #A6A6A6; box-sizing: border-box; margin-bottom: 15px; }";
    styleStr = styleStr + "\r\n.table-row-even td { background-color: #F5F5F5 !important; }";
    styleStr = styleStr + "\r\n#sidebar {width: 200px;position: fixed; top: 0; bottom: 0; left: 0;overflow-x: hidden; overflow-y: auto;background-color: #F9F9F9;border-right: 1px solid #CCC;box-shadow: 0 0 20px #CCC;font-size: 12px;padding: 15px 0 30px 30px;}";
    styleStr = styleStr + "\r\n#sidebar ul { list-style: none outside none; margin-top: 5px; }";
    styleStr = styleStr + "\r\n#sidebar b { font-size: 13px; text-decoration: underline; margin-top: 15px; display: inline-block; }";
    styleStr = styleStr + "\r\n#sidebar a:link, #sidebar a:visited { text-decoration: none; color: #333; outline: none; }";
    styleStr = styleStr + "\r\n#sidebar a:hover { color: #888; text-decoration: underline; }";
    styleStr = styleStr + "\r\n#content { margin: 40px 100px 50px 265px; }";
    styleStr = styleStr + "\r\n.one-column .site { border: 1px solid #A6A6A6; background-color: #F5F5F5; padding: 20px; margin: 20px; }";
    styleStr = styleStr + "\r\n.one-column .site h1 { font-size: 30px; margin-bottom: 10px; }";
    styleStr = styleStr + "\r\n.one-column .site-summary th, .site-summary td { vertical-align: middle; }";
    styleStr = styleStr + "\r\n.one-column .site-summary tbody th { background-color: #E8E8E8; text-align: right; }";
    styleStr = styleStr + "\r\n.risk { padding: 20px; margin-bottom: 10px; }";
    styleStr = styleStr + "\r\n.risk-summary { border: 1px solid #A6A6A6; padding: 10px; background-color: #F5F5F5; margin-bottom: 15px; }";
    styleStr = styleStr + "\r\n.risk-summary dt, .risk-summary dd { padding: 8px; border: 1px dotted #CCC; }";
    styleStr = styleStr + "\r\n.risk-summary dt { float: left; width: 100px; text-align: right; padding-right: 15px; border-width: 0 0 1px 0; }";
    styleStr = styleStr + "\r\n.risk-summary dd { overflow: hidden; padding-left: 15px; border-width: 0 0 1px 1px; }";
    styleStr = styleStr + "\r\n.risk-summary dt.last { border-width: 0; }";
    styleStr = styleStr + "\r\n.risk-summary dd.last { border-width: 0 0 0 1px; }";
    styleStr = styleStr + "\r\n.db .risk-list tbody th, .summary table.info-list tbody th { background-color: #F5F5F5; text-align: right; }";


    try{
        if(!strcmp(htmlInfo.htmlFilePath, ""))
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：html路径为空！");
            qWarning()<<"HtmlLog err：html path is null";
            return -1;
        }

        XMLCC::OBJ::Root *root = 0;
        XMLCC::Builder builder;
        root = builder.createRoot(htmlInfo.htmlFilePath);
        if(root == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：root为空！");
            qWarning()<<"HtmlLog err：html root is null";
            return -2;
        }
        root->setString(htmlInfo.htmlFilePath);

        //html
        root->addObject(builder.createDoctype());
        XMLCC::Object *html = builder.create(XMLCC::Types::Element, "html");
        if(html == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：html项添加错误！");
            qWarning()<<"HtmlLog err：html add error";
            return -3;
        }
        root->addObject(html);

        //head
        XMLCC::Object *head = builder.create(XMLCC::Types::Element, "head");
        if(head == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：head项添加错误！");
            qWarning()<<"HtmlLog err：head add error";
            return -4;
        }
        html->addObject(head);

        //meta
        XMLCC::Object *meta = builder.create(XMLCC::Types::Element, "META");
        if(meta == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：META项添加错误！");
            qWarning()<<"HtmlLog err：META add error";
            return -5;
        }
        builder.create( meta, XMLCC::Types::Attribute, "http-equiv", "Content-Type" );
        builder.create( meta, XMLCC::Types::Attribute, "content", "text/html; charset=GB2312" );
        head->addObject(meta);

        //title
        XMLCC::Object *title = builder.create(XMLCC::Types::Element, "title", htmlInfo.htmlTitle);
        if(title == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：title项添加错误！");
            qWarning()<<"HtmlLog err：title add error";
            return -6;
        }
        head->addObject(title);

        //style
        XMLCC::Object *style = builder.create(XMLCC::Types::Element, "style", (XMLCC::String)styleStr);
        if(style == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：style项添加错误！");
            qWarning()<<"HtmlLog err：style add error";
            return -7;
        }
        builder.create(style, XMLCC::Types::Attribute, "type", "text/css");
        head->addObject(style);

        //body
        XMLCC::Object *body = builder.create(XMLCC::Types::Element, "body");
        if (body == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：body项添加错误！");
            qWarning()<<"HtmlLog err：body add error";
            return -8;
        }
        builder.create(body, XMLCC::Types::Attribute, "class", "two-column web");
        html->addObject(body);

        //div id = "sidebar"
        XMLCC::Object *div1 = builder.create(XMLCC::Types::Element, "div");
        if (div1 == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：div1项添加错误！");
            qWarning()<<"HtmlLog err：div1 add error";
            return -9;
        }
        builder.create(div1, XMLCC::Types::Attribute, "id", "sidebar");
        body->addObject(div1);

        //div class = "catelog"
        XMLCC::Object *div2 = builder.create(XMLCC::Types::Element, "div");
        if (div2 == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：div2项添加错误！");
            qWarning()<<"HtmlLog err：div2 add error";
            return -10;
        }
        builder.create(div2, XMLCC::Types::Attribute, "class", "catalog");
        div1->addObject(div2);

        //b
        XMLCC::Object *b = builder.create(XMLCC::Types::Element, "b", "扫描结果");
        if (b == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：b项添加错误！");
            qWarning()<<"HtmlLog err：b add error";
            return -11;
        }
        div2->addObject(b);

        //ul
        XMLCC::Object *ul = builder.create(XMLCC::Types::Element, "ul");
        if (ul == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：ul项添加错误！");
            qWarning()<<"HtmlLog err：ul add error";
            return -12;
        }
        div2->addObject(ul);

        //li
        char liNumStr[100] = {0};
        char liStr[100] = {0};

        int idex=0;
        int i=0;
        HtmlWriteInfo   *pCurHtmlWrite = pHtmlWrite;
        while ((NULL != pCurHtmlWrite) && (NULL != pCurHtmlWrite->pHtmlLeftStr))
        {
            XMLCC::Object *li = builder.create(XMLCC::Types::Element, "li", "- ");
            XMLCC::Object *a = builder.create(XMLCC::Types::Element, "a", pCurHtmlWrite->pHtmlLeftStr);
            char herfStr[100] = {0};
            sec_strcpy(herfStr, 100, "#RiskType_");
            char numStr[10] = {0};
            itoa(++idex, numStr, 10);
            sec_strcat(herfStr, 100, numStr);
            builder.create(a, XMLCC::Types::Attribute, "href", herfStr);
            li->addObject(a);

            sec_strcpy(liStr, 100, " (");
            itoa(pCurHtmlWrite->iTotalNum, liNumStr, 10);
            sec_strcat(liStr, 100, liNumStr);
            sec_strcat(liStr, 100, ")");
            builder.create(li, XMLCC::Types::Value, liStr);
            div2->addObject(li);

            pCurHtmlWrite++;
        }

        XMLCC::Object *div3 = builder.create(XMLCC::Types::Element, "div");
        if (div3 == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：div3项添加错误！");
            return -13;
        }
        builder.create(div3, XMLCC::Types::Attribute, "id", "content");
        body->addObject(div3);

        //右边部分
        int tableIndex = 0;
        int tableIndex1 = 0;
        XMLCC::Object *div4=NULL;
        XMLCC::Object *h2 = NULL;
        XMLCC::Object *div5 = NULL;
        XMLCC::Object *table = NULL;
        XMLCC::Object *colgroup = NULL;
        XMLCC::Object *thead = NULL;
        XMLCC::Object *tr = NULL;
        XMLCC::Object *tbody = NULL;
        char idStr[100] = {0};
        char colWidth[1024] = {0};

        pCurHtmlWrite = pHtmlWrite;
        while ((NULL != pCurHtmlWrite) && (NULL != pCurHtmlWrite->pHtmlLeftStr))
        {
            //div class="risk" id="RiskType_1"
            div4 = builder.create(XMLCC::Types::Element, "div");
            sec_strcpy(idStr, 100, "RiskType_");
            char numStr[10] = {0};
            itoa(i+1, numStr, 10);
            sec_strcat(idStr, 100, numStr);
            builder.create(div4, XMLCC::Types::Attribute, "class", "risk");
            builder.create(div4, XMLCC::Types::Attribute, "id", idStr);
            div3->addObject(div4);

            h2 = builder.create(XMLCC::Types::Element, "h2", pCurHtmlWrite->pHtmlLeftStr);
            builder.create(h2, XMLCC::Types::Attribute, "class", "risk-title title");
            div4->addObject(h2);

            //div class="table-wrapper"
            div5 = builder.create(XMLCC::Types::Element, "div");
            builder.create(div5, XMLCC::Types::Attribute, "class", "table-wrapper");
            div4->addObject(div5);

            //table
            table = builder.create(XMLCC::Types::Element, "table");
            builder.create(table, XMLCC::Types::Attribute, "class", "risk-list");
            div5->addObject(table);

            //colgroup
            colgroup = builder.create(XMLCC::Types::Element, "colgroup");
            table->addObject(colgroup);

            XMLCC::Object *col = NULL;

            for (idex=0; idex<pCurHtmlWrite->iColumnNum; idex++)
            {
                col = builder.create(XMLCC::Types::Element, "col");
                sprintf(colWidth, "width: %dpx;", pCurHtmlWrite->htmlColumn[idex].iColumnLen);
                builder.create(col, XMLCC::Types::Attribute, "style", colWidth);
                colgroup->addObject(col);
                tableIndex++;
            }
            tableIndex++;
            //             while (htmlTableInfo[tableIndex].colName[0])
            //             {
            //                 col = builder.create(XMLCC::Types::Element, "col");
            //                 sprintf_s(colWidth, 1024, "width: %dpx;", htmlTableInfo[tableIndex].colLength);
            //                 builder.create(col, XMLCC::Types::Attribute, "style", colWidth);
            //                 colgroup->addObject(col);
            //                 tableIndex++;
            //             }
            //             tableIndex++;

            //thead
            thead = builder.create(XMLCC::Types::Element, "thead");
            table->addObject(thead);

            //tr
            tr = builder.create(XMLCC::Types::Element, "tr");
            thead->addObject(tr);
            //th
            XMLCC::Object *th = NULL;
            for (idex=0; idex<pCurHtmlWrite->iColumnNum; idex++)
            {
                th = builder.create(XMLCC::Types::Element, "th", pCurHtmlWrite->htmlColumn[idex].pColumnName);
                tr->addObject(th);
                tableIndex1++;
            }
            tableIndex1++;
            //             while (htmlTableInfo[tableIndex1].colName[0])
            //             {
            //                 th = builder.create(XMLCC::Types::Element, "th", htmlTableInfo[tableIndex1].colName);
            //                 tr->addObject(th);
            //                 tableIndex1++;
            //             }
            //             tableIndex1++;

            //tbody
            tbody = builder.create(XMLCC::Types::Element, "tbody");
            table->addObject(tbody);


            //for (int m = 0; m < htmlLeftInfo[i].num; m++)
            for (int m = 0; m < pCurHtmlWrite->iTotalNum; m++)
            {
                XMLCC::Object *trRow = builder.create(XMLCC::Types::Element, "tr");
                if (m%2 == 0)
                {
                    builder.create(trRow, XMLCC::Types::Attribute, "class", "table-row-odd");
                }
                else
                {
                    builder.create(trRow, XMLCC::Types::Attribute, "class", "table-row-even");
                }
                tbody->addObject(trRow);

                WriteTdRow(builder, trRow, i, m, colInfo);
            }

            i++;
            pCurHtmlWrite++;
        }

        qDebug()<<"pCurHtmlWrite_2 is done";

        std::string strFileName = root->getFileName( );
        char* charFileName = (char*)(strFileName.c_str( ));

//        QFile fileOut(charFileName);

//        if( ! fileOut.open( QIODevice::WriteOnly ))
//        {

//        }

//        QTextStream tsOut( &fileOut);

//        int noOfObjects = root->getNoOfObjects( );

//        for( int o = 0; o < noOfObjects; o++ ) {

//          XMLCC::Object* sonObj = root->getObject( o );
//          sonObj->setIndent( root );
//          tsOut<<sonObj;
//        }


        fstream file;
        locale loc = locale::global(locale(""));
        file.open( charFileName, std::ios::out );
        //int aa = GetLastError();
        locale::global(loc);
        if(file.fail())
        {
            index = 0;
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：file.fail()%d", aa);
            qWarning()<<"html flie failed";
            return -14;
        }

        file << root << std::endl << std::flush;
        file.close( );
        delete root;

    } catch( XMLCC::ERR::Exception e ) { // own exception class

        qWarning()<<"XMLCC err";
        //	 std::cout << e;
    } catch( std::exception e ) { // standard exception class
        // std::cout << "std::exception caught:" << std::endl << std::flush;
        e.what( );
        qWarning()<<"std::exception caught:";
    } catch( ... ) { // any other exception thrown
        // std::cout << "Strange exception caught:" << std::endl << std::flush;
        XMLCC::ERR::Exception e;
        e.nuke( ); // nuke screen
        qWarning()<<"Strange exception caught:";
    } // try
    index = 0;
    // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog:WriteHtmlFile成功！");
    return 0;
}

