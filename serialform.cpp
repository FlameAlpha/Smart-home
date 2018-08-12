#include "serialform.h"
#include "ui_serialform.h"
#include <QDebug>
#include "database.h"

#define SERIALTEST

SerialForm::SerialForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialForm)
{
    m_fd=openSerialPort();
    if(m_fd<0)
    {
        QMessageBox::warning(this,tr("Error"),tr("Fail to open serial port!"));
        return ;
    }
    m_notifier=new QSocketNotifier(m_fd,QSocketNotifier::Read,this);

    QObject::connect(m_notifier,SIGNAL(activated(int)),this,SLOT(remoteDataIncoming_clicked()));

    ui->setupUi(this);
}

SerialForm::~SerialForm()
{
    if(m_notifier)
    {
        delete m_notifier;
        m_notifier=0;
    }
    if(m_fd>=0)
    {
        ::close(m_fd);
        m_fd=-1;
    }
    delete ui;
}

void SerialForm::show_this_window()
{
    this->move(0,0);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->show();
    emit close_other_windows();
}

void SerialForm::close_this_window()
{
    this->close();
}

void SerialForm::on_SendButton_clicked()
{
    static int number=0;
    if(number<1){
    QString declare="this is PortHelper,which is made by Flame.Thanke you!";
    ::write(m_fd,declare.toLatin1(),declare.length());
    number++;
    }

    QString string=ui->SendWindow->toPlainText();
    if(string.isEmpty())
    {
        return;
    }
    ::write(m_fd,string.toLatin1(),string.length());
    ui->SendWindow->setText("");
}

int SerialForm::openSerialPort()
{
    int fd=-1;
    const char *devName="/dev/ttySAC2";
    fd=::open(devName,O_RDWR|O_NONBLOCK);
    if(fd<0){
        return -1;
    }
    termios serialAttr;
    memset(&serialAttr,0,sizeof serialAttr);
    serialAttr.c_cflag=B115200|HUPCL|CS8|CREAD|CLOCAL;
    serialAttr.c_cc[VMIN]=1;
    if(tcsetattr(fd,TCSANOW,&serialAttr)!=0){
        return -1;
    }
    return fd;
}

void SerialForm::remoteDataIncoming_clicked()
{
    char c;
    static QString ch;
    bool success=read(m_fd,&c,1);
    static QString temp,hum;
    if(!success){
        qDebug()<<"Error"<<endl;
        return;
    }
    else{
    if((c>='0')&&(c<='9'))  ch.append(c);
    if(c=='#')
    {/*
    qDebug()<<"Success"<<endl;
    ui->DisplayWindow->insertPlainText(ch);
    ui->DisplayWindow->insertPlainText(QString("\n"));

    int number=ch.toInt();
    ch.clear();

    emit data_change(number);
    qDebug()<<number;
    int ID_num=number/10000;
    bool Status=number%10000/1000;
    int Properties=number%1000;
    DataBase database;
    database.UpdateByID(ID_num,Status,Properties);*/
    if(ch.length()==7){ qDebug()<<"Wifi Data Success"; emit data_change(ch);}
    else qDebug()<<"Wifi Data Error";
    ch.clear();
    }
    if(c=='T'){
       temp=ch.mid(0,4);
       ch.clear();
    //emit data_change_Temp_Hum(temp,hum);
    }
    if(c=='H'){
        hum=ch.mid(0,4);
        ch.clear();
        emit data_change_Temp_Hum(temp,hum);
    }
    }
}

void SerialForm::on_CloseButton_clicked()
{
    this->close();
}

void SerialForm::sendstring_clicked(QString serial_senddata_str)
{
    ::write(m_fd,serial_senddata_str.append("#").toLatin1(),serial_senddata_str.append("#").length());
}

QString SerialForm::getstring_clicked()
{
    char c[8];
    if(read(m_fd,c,sizeof c)){
        qDebug()<<"Success"<<endl;
        qDebug()<<c;
    }
    QString serial_getdata_str=QString(QLatin1String(c));
    return serial_getdata_str;
}
