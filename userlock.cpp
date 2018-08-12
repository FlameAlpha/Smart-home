#include "userlock.h"
#include "ui_userlock.h"

#include <QProcess>
#include <QDebug>
#define PIN_Lock_number "123456"

UserLock::UserLock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserLock)
{
    ui->setupUi(this);
    time.start(1000);
    PIN_txt=QString("");
    //ui->PIN->setStyleSheet("color:red;");
    ui->Warning->setStyleSheet("color:red;");
    //qDebug()<<"lock init"<<endl;
    QObject::connect(&time,SIGNAL(timeout()),this,SLOT(time_display_clicked()));
    //qDebug()<<"timer start"<<endl;
    QObject::connect(ui->PIN,SIGNAL(returnPressed()),this,SLOT(PIN_txt_clicked()));
}

UserLock::~UserLock()
{
    delete ui;
}

void UserLock::on_OkButton_clicked()
{
    if(PIN_txt==QString(PIN_Lock_number))
       {
        ui->PIN->setText("");
        ui->Warning->setText("");
        emit open_system();
    }
    else
    {
        ui->Warning->setText("Error !");
    }
    ui->PIN->setText("");
    PIN_txt.clear();
}

void UserLock::PIN_txt_clicked()
{
    if(PIN_txt==QString(PIN_Lock_number))
       {
        ui->PIN->setText("");
        ui->Warning->setText("");
        emit open_system();
    }
    else
    {
        ui->Warning->setText("Error !");
    }
}

void UserLock::time_display_clicked()
{
    datetime=QDateTime::currentDateTime();
    QString displaytime=datetime.toString("yyyy-M-dd hh:mm:ss");
    ui->TimeDisplay->setText(displaytime);
}

void UserLock::displaylock_clicked()
{
    this->QWidget::move(0,0);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->show();
}

void UserLock::on_PowerButton_clicked()
{
    this->close();
   // QProcess::execute("shutdown");
}

void UserLock::close_this_window()
{
    this->close();
}

void UserLock::on_Push_0_clicked()
{
    if(PIN_txt.length()<6) {
        PIN_txt.append("0");
        ui->PIN->setText(PIN_txt);
    }
}

void UserLock::on_Push_1_clicked()
{
    if(PIN_txt.length()<6) {
        PIN_txt.append("1");
        ui->PIN->setText(PIN_txt);
    }
}

void UserLock::on_Push_2_clicked()
{
    if(PIN_txt.length()<6) {
        PIN_txt.append("2");
        ui->PIN->setText(PIN_txt);
    }
}

void UserLock::on_Push_3_clicked()
{
    if(PIN_txt.length()<6) {
        PIN_txt.append("3");
        ui->PIN->setText(PIN_txt);
    }
}

void UserLock::on_Push_4_clicked()
{
    if(PIN_txt.length()<6) {
        PIN_txt.append("4");
        ui->PIN->setText(PIN_txt);
    }
}

void UserLock::on_Push_5_clicked()
{
    if(PIN_txt.length()<6) {
        PIN_txt.append("5");
        ui->PIN->setText(PIN_txt);
    }
}

void UserLock::on_Push_6_clicked()
{
    if(PIN_txt.length()<6) {
        PIN_txt.append("6");
        ui->PIN->setText(PIN_txt);
    }
}

void UserLock::on_Push_8_clicked()
{
    if(PIN_txt.length()<6) {
        PIN_txt.append("8");
        ui->PIN->setText(PIN_txt);
    }
}

void UserLock::on_Push_7_clicked()
{
    if(PIN_txt.length()<6) {
        PIN_txt.append("7");
        ui->PIN->setText(PIN_txt);
    }
}

void UserLock::on_Push_9_clicked()
{
    if(PIN_txt.length()<6) {
        PIN_txt.append("9");
        ui->PIN->setText(PIN_txt);
    }
}
