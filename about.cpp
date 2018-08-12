#include "about.h"
#include "ui_about.h"
#include "database.h"
#include "flameweibo.h"

#include <QUrl>
#include <QWebView>
#include <QtWebKit>

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}

void About::Display_AboutWidget_clicked()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->QWidget::move(0,0);
    this->show();
}

void About::on_pushButton_clicked()
{
    this->close();
}

void About::close_this_window()
{
    this->close();
}

void About::on_ResetButton_clicked()
{
    DataResetAlone();
}

void About::on_commandLinkButton_clicked()
{
    FlameWeibo *weibo=new FlameWeibo;
    weibo->setWindowFlags(Qt::FramelessWindowHint);
    weibo->setAttribute(Qt::WA_DeleteOnClose);
    weibo->show();
}
