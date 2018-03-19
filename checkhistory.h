#ifndef CHECKHISTORY_H
#define CHECKHISTORY_H

//#ifndef DWORD
//#define DWORD unsigned int
//#endif

//#ifndef BOOL
//#define BOOL int
//#endif

//#ifndef PVOID
//#define PVOID void*
//#endif

//#ifndef WCHAR
//#define WCHAR wchar_t
//#endif
//

#define MAX_CHECK_NUM	9

//检查项类型。
enum _QCHECK_TYPE
{
    QCHECK_INFRO=0,			//"红外设备"
    QCHECK_BLUETOOTH,		//"蓝牙设备"
    QCHECK_WIRELESS_NIC,	//"无线网卡设备"
    QCHECK_PATCH,			//"未安装补丁"
    QCHECK_FILE_OPEND,		//"打开的文档"
    QCHECK_USB,				//"USB设备"
    QCHECK_INTERNET,		//"上网记录"
    QCHECK_FILEHEADER_SEARCH,	//文件头
    QCHECK_KEYWORD_SEARCH,	//"特殊字符查询"。仅深度搜索有效。
};

//深度检查参数
typedef struct _CHECK_PARAM
{
    int					type;
    vector<wstring>*	pVectorResult;	//查询结果
    vector<wstring>*	pVectorParam;	//输入参数
    PVOID				reserve1;		//暂时不用，将来扩展保留。
    PVOID				reserve2;		//暂时不用，将来扩展保留。
}CHECK_PARAM,*PCHECK_PARAM;

//字符串类型。文字搜索用。URL转义暂时没有做？
enum _CHAR_TYPE
{
    CHAR_ANSI=0,
    CHAR_UNICODE,
    CHAR_UNICODE_BIGENDIAN,//大边
    CHAR_UTF8,
};

#define KEYWORD_MAX_SIZE		32		//搜索字符最大长度。

//普通返回格式，就一个值。
#define RESULT_FORMAT_NORMAL				"%s"

//最近打开的文件格式 "检查模式|时间|文件名|备注"
#define RESULT_FORMAT_RECENTOPEN			"%s|%s|%s|%s"

//USB格式 "检查模式|时间|ID|备注"
#define RESULT_FORMAT_USB					"%s|%s|%s|%s"

//违规外联格式，可能有的项为空 "工具类型|时间|URL|title"
#define RESULT_FORMAT_INTERNET				"%s|%s|%s|%s"

//关键字搜索结果返回格式 "磁盘序号（0~25或者'A'~'Z'）|偏移量高~偏移量第|字符串类型|字符串"
#define RESULT_FORMAT_KEYWORD_SECTOR		"%d|%08X~%08X|%d|%s"

//文件头 "index_highOffset~lowOffset_highSize~lowSize.extent"
#define RESULT_FORMAT_HEADER_SEARCH			"%d_%08X~%08X_%08X~%08X.%s"

//关键字搜索结果返回格式 "文件名|偏移量高~偏移量第|字符串类型|字符串"
#define RESULT_FORMAT_KEYWORD_FILE			"%s|%08X~%08X|%d|%s"


//文件搜索参数。
typedef struct _FILESEARCH_PARAM_PUBLIC
{
    BOOL bSubDir;					//是否包含子文件。
    BOOL bContinue;					//是否继续上一次位置查找。
    PVOID CallBackFileSearchOver;
    PVOID CallBackSetDataW;

    vector<wstring>* pVectorResult;	//查询结果
    vector<wstring>* pVecPath;		//搜索路径。如果不特别指定，则搜索整个本地硬盘。
    vector<wstring>* pVecExt;		//文件扩展名。如果不特别指定，则是txt,html,xml等。
    vector<wstring>* pVecKeyword;	//特征字符。
    PVOID CallBackShowProgressFile;
}FILESEARCH_PARAM_PUBLIC,*PFILESEARCH_PARAM_PUBLIC;

//文件头后缀名。深度搜索返回的文件类型。
#define EXT_bmp			 "bmp"
#define EXT_89A_gif		 "89A_gif"
#define EXT_87A_gif		 "87A_gif"
#define EXT_fe_jpg		 "fe_jpg"
#define EXT_e0_jpg		 "e0_jpg"
#define EXT_i_tif		 "i_tif"
#define EXT_m_tif		 "m_tif"
#define EXT_4g_tif		 "4g_tif"
#define EXT_png			 "png"
#define EXT_office2003	 "office2003"
#define EXT_pdf			 "pdf"
#define EXT_lnk			 "lnk"
#define EXT_reg			 "reg"
#define EXT_rtf			 "rtf"
#define EXT_a_xml		 "a_xml"
#define EXT_u_xml		 "u_xml"
#define EXT_old_doc		 "old_doc"
#define EXT_6_0_doc		 "6_0_doc"
#define EXT_dos_6_0_doc	 "dos_6_0_doc"
#define EXT_avi			 "avi"
#define EXT_mpg			 "mpg"
#define EXT_mov			 "mov"
#define EXT_mp4			 "mp4"
#define EXT_rar			 "rar"
#define EXT_gz			 "gz"
#define EXT_tar			 "tar"
#define EXT_zip			 "zip"

/*
#define CALLMODE __stdcall
*/
#define CALLMODE __cdecl

typedef void (CALLMODE* SHOWPROGRESS)(int index,__int64 totalSize,__int64 currentSize);
typedef void (CALLMODE* SHOWPROGRESS_FILE)(char* szFileName,__int64 totalSize,__int64 currentSize);

typedef void (CALLMODE* SETDATA)(vector<wstring>*,const WCHAR*);//不能在DLL赋值，需要回调（在主程序中赋值，否则，析构函数中释放会有问题）。
typedef void (CALLMODE* CHECKOVER)(int size,PCHECK_PARAM pCheckParam);//size 检查项目数,pCheckParam 检查项目存放结果数组
typedef void (CALLMODE* FILESEARCHOVER)(PFILESEARCH_PARAM_PUBLIC);

extern "C"
{
void CALLMODE CheckOneW(int size,PCHECK_PARAM pCheckParam,SETDATA CallBackSetDataW);
BOOL CALLMODE IsDoing();
//
//	深度搜索。
//	bContinue 是否从上一次的位置继续
//	CallBackCheckOver 检查结束回调处理。
//
void CALLMODE CheckOneWDeep(int CallBackSize,
                            PCHECK_PARAM pCheckParam,
                            CHECKOVER CallBackCheckOver,
                            SETDATA CallBackSetDataW,
                            SHOWPROGRESS CallBackShowProgress,
                            BOOL bContinue=TRUE);

//	终止查询。
void CALLMODE CheckStop();
void CALLMODE SearchFileW(PFILESEARCH_PARAM_PUBLIC pOut);

//
//从扇区中提取文件。如果文件很大，可以调用CheckStop终止。
//
BOOL CALLMODE FileExtract(	IN const int	index,			//磁盘序号
                            IN __int64		size,			//恢复大小
                            IN const char*	szFile,			//提取文件的文件名。
                            IN __int64		diskOffset		//扇区偏移量
                            );
//e.g. 从文件头搜索结果，提取参数并恢复文件。
/*
    #define MAX_RESTORE_SIZE	(10*1024*1024)	//10M

    DWORD highOffset=0;
    DWORD lowOffset=0;
    DWORD highSize=0;
    DWORD lowSize=0;
    char sz[MAX_PATH]={0};
    int index=0;
    sscanf(resultOffset[i].c_str(),RESULT_FORMAT_HEADER_SEARCH,&index,&highOffset,&lowOffset,&highSize,&lowSize,sz);
    LARGE_INTEGER liSize;
    liSize.LowPart=lowSize;
    liSize.HighPart=highSize;
    LARGE_INTEGER liOffset;
    liOffset.LowPart=lowOffset;
    liOffset.HighPart=highOffset;

    __int64 size=liSize.QuadPart;
    __int64 diskOffset=liOffset.QuadPart;

    if(size<=0||size>MAX_RESTORE_SIZE)//如果没有大小，指定缺省值
    {
        size=MAX_RESTORE_SIZE;//
    }
    FileExtract(index,size,szFile,diskOffset);
*/

//文件填零复位。如果文件很大，可以调用CheckStop终止。
BOOL CALLMODE FileReset(IN const char* szFile);
}

//深度--上网类型
#define STR_DEEP_UNV					"DB_DEEP_unv"
#define STR_DEEP_FIREFOX				"DB_DEEP_Firefox"
#define STR_DEEP_SOGOU					"DB_DEEP_Sogou"
#define STR_DEEP_IE_INDEX				"IE_INDEX_DEEP"
#define STR_DEEP_IE_TYPED				"IE_TYPED_DEEP"

//普通--上网类型
#define STR_IE_TYPED					"IE_TYPED"
#define STR_FIREFOX						"Firefox"
#define STR_CHROME						"Chrome"

#define STR_360							"360Browser"
#define STR_QQ							"QQBrowser"
#define STR_UC							"UCBrowser"
#define STR_SOGOU						"SogouExplorer"
#define STR_BAIDU						"BaiduBrowser"
#define STR_MAXTHON						"Maxthon"
#define STR_2345						"2345Explorer"

//
#define STR_RECENTOPEN_REGENUM_DEEP		"RECENTOPEN_REGENUM_DEEP"
#define STR_RECENTOPEN_REGENUM			"RECENTOPEN_REGENUM"

#endif
