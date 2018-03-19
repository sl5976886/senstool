#-------------------------------------------------
#
# Project created by QtCreator 2017-12-11T15:15:01
#
#-------------------------------------------------

QT   += core gui xml designer

include(./singleapplication/singleapplication.pri)
DEFINES += QAPPLICATION_CLASS=QApplication UMBCS

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sensTool
TEMPLATE += app lib

LIBS += -LC:/Users/liusuzhe/Desktop/config -lGrxaHostCheck
LIBS += -LC:/Users/liusuzhe/Desktop/config -lcheckhistory
LIBS += -LC:/Users/liusuzhe/Desktop/config -lCrossClient
LIBS += -LC:/Users/liusuzhe/Desktop/config -lMsWSock
LIBS += -LC:/Users/liusuzhe/Desktop/config -lShLwApi
LIBS += -LC:/Users/liusuzhe/Desktop/config -lWS2_32
LIBS += -LC:/Users/liusuzhe/Desktop/config -lTXlib

LIBS += -LC:/Users/liusuzhe/Desktop/config -lWriteHtmlDll


SOURCES += main.cpp\
        mainwindow.cpp \
    ringsmapprogressbar.cpp \
    titlebar.cpp \
    xmlresolution.cpp \
    include/htmllog/xmlccBuilder.cpp \
    include/htmllog/xmlccDevParser.cpp \
    include/htmllog/xmlccDomGrabber.cpp \
    include/htmllog/xmlccDomParser.cpp \
    include/htmllog/xmlccDomTokenizer.cpp \
    include/htmllog/xmlccDomViewer.cpp \
    include/htmllog/xmlccDomWriter.cpp \
    include/htmllog/xmlccErrError.cpp \
    include/htmllog/xmlccErrException.cpp \
    include/htmllog/xmlccErrFailure.cpp \
    include/htmllog/xmlccObjAttribute.cpp \
    include/htmllog/xmlccObjCData.cpp \
    include/htmllog/xmlccObjComment.cpp \
    include/htmllog/xmlccObjDoctype.cpp \
    include/htmllog/xmlccObject.cpp \
    include/htmllog/xmlccObjElement.cpp \
    include/htmllog/xmlccObjHeader.cpp \
    include/htmllog/xmlccObjRoot.cpp \
    include/htmllog/xmlccObjValue.cpp \
    include/htmllog/xmlccSaxParser.cpp \
    include/htmllog/xmlccSaxParserHandler.cpp \
    include/htmllog/xmlccSaxParserHandlerExample.cpp \
    include/htmllog/xmlccSysListTest.cpp \
    include/htmllog/xmlccSysString.cpp \
    include/htmllog/xmlccSysStringTool.cpp \
    include/tinyxml/tinystr.cpp \
    include/tinyxml/tinyxml.cpp \
    include/tinyxml/tinyxmlerror.cpp \
    include/tinyxml/tinyxmlparser.cpp \
    ringsmapprogressbarplugin.cpp \
    SecString.cpp \
    xmlhtml/CheckResultResouce.cpp \
    xmlhtml/result2html.cpp \
    xmlhtml/result2xml.cpp \
    xmlhtml/txt.cpp \
    global.cpp \
    renderthread.cpp \
    MQ.cpp \
    testdirscan.cpp \
    anaxmlfile.cpp \
    waitdialog.cpp

HEADERS  += mainwindow.h \
    ringsmapprogressbar.h \
    titlebar.h \
    xmlresolution.h \
    include/htmllog/xmlcc.h \
    include/htmllog/xmlccBuilder.h \
    include/htmllog/xmlccDevParser.h \
    include/htmllog/xmlccDomGrabber.h \
    include/htmllog/xmlccDomParser.h \
    include/htmllog/xmlccDomTokenizer.h \
    include/htmllog/xmlccDomViewer.h \
    include/htmllog/xmlccDomWriter.h \
    include/htmllog/xmlccErrError.h \
    include/htmllog/xmlccErrException.h \
    include/htmllog/xmlccErrFailure.h \
    include/htmllog/xmlccInclDefs.h \
    include/htmllog/xmlccObjAttribute.h \
    include/htmllog/xmlccObjCData.h \
    include/htmllog/xmlccObjComment.h \
    include/htmllog/xmlccObjDoctype.h \
    include/htmllog/xmlccObject.h \
    include/htmllog/xmlccObjElement.h \
    include/htmllog/xmlccObjHeader.h \
    include/htmllog/xmlccObjRoot.h \
    include/htmllog/xmlccObjValue.h \
    include/htmllog/xmlccSaxParser.h \
    include/htmllog/xmlccSaxParserHandler.h \
    include/htmllog/xmlccSaxParserHandlerExample.h \
    include/htmllog/xmlccSysList.h \
    include/htmllog/xmlccSysString.h \
    include/htmllog/xmlccSysStringTool.h \
    include/htmllog/xmlccTypes.h \
    include/tinyxml/tinystr.h \
    include/tinyxml/tinyxml.h \
    ringsmapprogressbarplugin.h \
    SecString.h \
    xmlhtml/CheckResultResouce.h \
    xmlhtml/GrxaHostCheck.h \
    xmlhtml/result2html.h \
    xmlhtml/result2xml.h \
    xmlhtml/txt.h \
    xmlhtml/CheckCommon.h \
    global.h \
    renderthread.h \
    xmlhtml/Resource.h \
    checkhistory.h \
    clientmodule.h \
    webaxwidget.h \
    MQ.h \
    TXConstant.h \
    TXlib.h \
    testdirscan.h \
    anaxmlfile.h \
    NetUtlity.h \
    WriteHtmlDll.h \
    include/htmllog/HtmlLog.h \
    waitdialog.h

FORMS    += mainwindow.ui \
    waitdialog.ui

RESOURCES += \
    qss.qrc \
    button.qrc \
    customprogressbar.qrc

RC_FILE = myico.rc

