#include "global.h"
#include "include/htmllog/xmlcc.h"
#include "SecString.h"
#include <QMutex>
#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <windows.h>
#ifdef _WIN32
#ifdef _DEBUG // find memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // _DEBUG
#endif // _WIN32
#include <iterator>

bool ifHide = false;

int isChecked = 1;

QString scanProject = QString("");

QPoint gp;

int num = 0;

HWND hwnd;

QStringList keyWordList;

QStringList usbResList;
QStringList internetResList;
QStringList wjczResList;

QList<SensRes> sensResList;

__int64 gTotalSize = 0;
__int64 gCurrSize = 0;

bool ifUsbFinish = false;
bool ifIntFinish = false;
bool wjczFinish = false;

int failCode = 0;
int isConnected = 0;

int ifDeep = 0;
int ifSens = 0;
int id = 0;
DWORD hostId = 0;

bool ifFromServer = false;

bool haveSensTask = false;
bool ifDeepFinish = true;
bool ifSensFinish = false;
bool ifSensTask = false;

bool ifHgFinish =true;

bool ifPolicyXml = false;


//MsgTransFile *pTaskFile = NULL;

QTimer *task_timer = new QTimer();

vector<TaskInfo> fileVector;

TestDirScan g_tTestDirScan;

void checkFile()
{
    QString localPath = qApp->applicationDirPath();
    localPath+="\\log.txt";
    QFile logFile(localPath);
    if (logFile.size() > 1024*5000)
    {
          logFile.flush();
          logFile.close();

          QString localPath_1 = qApp->applicationDirPath();
          QString newLogPath = localPath_1+"\\pLog.txt";
          QFile pLogFile(newLogPath);
          if(pLogFile.exists())
          {
              QFile::remove(newLogPath);         //只保留一个之前的日志文件
          }
          QFile::copy(localPath, newLogPath); // Bug: 按理说 rename 会更合适，但是 rename 时最后一个文件总是显示不出来，需要 killall Finder 后才出现
          QFile::remove(localPath); // 删除重新创建，改变创建时间
      }
}

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    checkFile();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
    default:
        text = QString("Debug:");
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

    QString localPath = qApp->applicationDirPath();
    localPath+="\\log.txt";
    QFile file(localPath);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}


int my_strcpy_s(char *_DEST, size_t _SIZE, const char *_SRC)
{
    if (_DEST == NULL || _SRC == NULL || _SIZE == 0)
        return -1;
    char *p;
    size_t available;

    /* validation section */
    //_VALIDATE_STRING(_DEST, _SIZE);
    //_VALIDATE_POINTER_RESET_STRING(_SRC, _DEST, _SIZE);

    p = _DEST;
    available = _SIZE;
    while ((*p++ = *_SRC++) != 0 && --available > 0)
    {
    }

    if (available == 0)
    {
        //_RESET_STRING(_DEST, _SIZE);
        //_RETURN_BUFFER_TOO_SMALL(_DEST, _SIZE);
        _DEST[_SIZE-1] = 0;
        return 2;
    }
    //_FILL_STRING(_DEST, _SIZE, _SIZE - available + 1);
    //_RETURN_NO_ERROR;
    return 0;
}
int my_strcat_s(char *_DEST, size_t _SIZE, const char *_SRC)
{
    if (_DEST == NULL || _SRC == NULL || _SIZE == 0)
        return -1;
    char *p;
    size_t available;

    /* validation section */
    //_VALIDATE_STRING(_DEST, _SIZE);
    //_VALIDATE_POINTER_RESET_STRING(_SRC, _DEST, _SIZE);

    p = _DEST;
    available = _SIZE;
    while (available > 0 && *p != 0)
    {
        p++;
        available--;
    }

    if (available == 0)
    {
        //_RESET_STRING(_DEST, _SIZE);
        //_RETURN_DEST_NOT_NULL_TERMINATED(_DEST, _SIZE);
        return 1;
    }

    while ((*p++ = *_SRC++) != 0 && --available > 0)
    {
    }

    if (available == 0)
    {
        //_RESET_STRING(_DEST, _SIZE);
        //_RETURN_BUFFER_TOO_SMALL(_DEST, _SIZE);
        _DEST[_SIZE-1] = 0;
        return 2;
    }
    //_FILL_STRING(_DEST, _SIZE, _SIZE - available + 1);
    //_RETURN_NO_ERROR;
    return 0;
}


int my_memcpy_s(void *Dst, int nDstSize, const void *Src, int nCpyLen)
{
    if (nCpyLen >= nDstSize)
        memcpy(Dst, Src, nDstSize);
    else
        memcpy(Dst, Src, nCpyLen);
    return 0;
}

int index = 0;

void WriteTdRow(XMLCC::Builder builder, XMLCC::Object *tr, int i, int m, vector<HtmlColumnInfo>& colInfo)
{
    qInstallMessageHandler(outputMessage);
    if (index<colInfo.size())
    {
        while (index<colInfo.size() && colInfo[index].tableIndex == i && colInfo[index].colIndex == m)
        {
//            qDebug()<<"tableIndex:"<<colInfo[index].tableIndex<<"colIndex"<<colInfo[index].colIndex;
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

int WriteHtmlFileTest(HtmlInfo &htmlInfo, HtmlWriteInfo *pHtmlWrite, vector<HtmlColumnInfo> &colInfo)
{
    //CString styleStr = "";
    string styleStr = "";
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
            return -1;
        }

        XMLCC::OBJ::Root *root = 0;
        XMLCC::Builder builder;
        root = builder.createRoot(htmlInfo.htmlFilePath);
        if(root == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：root为空！");
            return -2;
        }
        root->setString(htmlInfo.htmlFilePath);

        //html
        root->addObject(builder.createDoctype());
        XMLCC::Object *html = builder.create(XMLCC::Types::Element, "html");
        if(html == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：html项添加错误！");
            return -3;
        }
        root->addObject(html);

        //head
        XMLCC::Object *head = builder.create(XMLCC::Types::Element, "head");
        if(head == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：head项添加错误！");
            return -4;
        }
        html->addObject(head);

        //meta
        XMLCC::Object *meta = builder.create(XMLCC::Types::Element, "META");
        if(meta == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：META项添加错误！");
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
            return -6;
        }
        head->addObject(title);

        //style
        XMLCC::Object *style = builder.create(XMLCC::Types::Element, "style", (XMLCC::String)styleStr);
        if(style == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：style项添加错误！");
            return -7;
        }
        builder.create(style, XMLCC::Types::Attribute, "type", "text/css");
        head->addObject(style);

        //body
        XMLCC::Object *body = builder.create(XMLCC::Types::Element, "body");
        if (body == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：body项添加错误！");
            return -8;
        }
        builder.create(body, XMLCC::Types::Attribute, "class", "two-column web");
        html->addObject(body);

        //div id = "sidebar"
        XMLCC::Object *div1 = builder.create(XMLCC::Types::Element, "div");
        if (div1 == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：div1项添加错误！");
            return -9;
        }
        builder.create(div1, XMLCC::Types::Attribute, "id", "sidebar");
        body->addObject(div1);

        //div class = "catelog"
        XMLCC::Object *div2 = builder.create(XMLCC::Types::Element, "div");
        if (div2 == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：div2项添加错误！");
            return -10;
        }
        builder.create(div2, XMLCC::Types::Attribute, "class", "catalog");
        div1->addObject(div2);

        //b
        XMLCC::Object *b = builder.create(XMLCC::Types::Element, "b", "扫描结果");
        if (b == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：b项添加错误！");
            return -11;
        }
        div2->addObject(b);

        //ul
        XMLCC::Object *ul = builder.create(XMLCC::Types::Element, "ul");
        if (ul == NULL)
        {
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：ul项添加错误！");
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

        std::fstream file;

        std::string strFileName = root->getFileName( );
        char* charFileName = (char*)(strFileName.c_str( ));
        locale loc = locale::global(locale(""));
        file.open( charFileName, std::ios::out );
        int aa = GetLastError();
        locale::global(loc);
        if(file.fail())
        {
            index = 0;
            // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog错误：file.fail()%d", aa);
            return -14;
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
    // CLogger::Instance()->LogWrite(LOG_MODULE_HTML, LOG_TYPE_DEBUG, LOG_LEVEL_INFO, "HtmlLog:WriteHtmlFile成功！");
    return 0;
}


