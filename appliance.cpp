#include "appliance.h"
#include "ui_appliance.h"
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>

Appliance::Appliance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Appliance)
{
    ui->setupUi(this);
}

Appliance::~Appliance()
{
    delete ui;
}

void Appliance::ReadFile_clicked()
{

       QString filename="/usr/local/bin/data";
       QFile file;
       file.setFileName(filename);
       file.open(QIODevice::ReadOnly);
       QTextStream in(&file);
       QString string=in.readAll();
       ui->TextBrowser->setText(string);
       file.close();

       char *data;
       QByteArray ba=string.toLatin1();
       data=ba.data();

       this->setWindowFlags(Qt::FramelessWindowHint);
       this->QWidget::move(0,0);
       this->show();
       emit close_other_windows();
}

void Appliance::on_closeButton_clicked()
{
    emit open_userlock();
}

void Appliance::close_this_window()
{
    this->close();
}
