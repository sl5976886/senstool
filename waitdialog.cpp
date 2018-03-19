#include "waitdialog.h"
#include "ui_waitdialog.h"
#include "global.h"
#include <QMovie>
#include <QDesktopWidget>

waitDialog::waitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waitDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//无边框
    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明
//    this->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存

    //屏幕居中显示
//    int frmX = width();
//    int frmY = height();
//    QDesktopWidget w;
//    int deskWidth = w.width();
//    int deskHeight = w.height();

//    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
//    move(movePoint);
    this->setGeometry(gp.x()+340,gp.y()+150,200,200);
    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::WindowStaysOnTopHint;
    this->setWindowFlags(flags);
    //加载gif图片
    QMovie *movie = new QMovie(":/button/wait.gif");
    ui->label->setMovie(movie);
    movie->start();
}

waitDialog::~waitDialog()
{
    delete ui;
}
