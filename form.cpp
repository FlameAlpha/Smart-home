#include "form.h"
#include "serialform.h"
#include "ui_form.h"
#include <QDebug>
#include "database.h"

#define SERIALTEST

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
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

Form::~Form()
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

void Form::show_this_window()
{
    this->move(0,0);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->show();
    emit close_other_windows();
}

void Form::close_this_window()
{
    this->close();
}

void Form::on_SendButton_clicked()
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

int Form::openSerialPort()
{
    int fd=-1;
    const char *devName="/dev/ttySAC1";
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
void Form::remoteDataIncoming_clicked()
{
    char c;
    static QString ch;
    static bool count_true=false;
    bool success=read(m_fd,&c,1);
    if(!success){
        qDebug()<<"Error"<<endl;
        return;
    }
    else{
    //if((c>='0')&&(c<='9'))  ch.append(c);
    if(c==0xFE) count_true=true;
    if(count_true){
    ch.append(c);
    if(c==0xFF)
    {
    qDebug()<<"STM32 Data Success"<<endl;
    ch=ch.mid(6,7);
    qDebug()<<ch<<endl;
    SerialForm serialform;
    serialform.sendstring_clicked(ch);

    int number=ch.toInt();
    int ID_num=number/10000;
    bool Status=number%10000/1000;
    int Properties=number%1000;
    DataBase database;
    database.UpdateByID(ID_num,Status,Properties);
    emit data_change(number);
    emit data_change_ST(ch);
    count_true=false;
    ch.clear();
    }
   }
  }
}

void Form::on_CloseButton_clicked()
{
    this->close();
}

void Form::sendstring_clicked(QString serial_senddata_str)
{
    QString Send_data_temp; //FE 08 90 91 0F 0E 30 30 30 30 30 30 30 30 35 FF
    char xieyibaotou[]={0xFE,0x0C,0x90,0x91,0xF7,0x0E};
    char xieyibaowei=0xFF;
    Send_data_temp=QString(xieyibaotou).append(serial_senddata_str).append('#').append(QString(xieyibaowei));
    ::write(m_fd,Send_data_temp.toLatin1(),Send_data_temp.length());
    //::write(m_fd,serial_senddata_str.append("#").toLatin1(),serial_senddata_str.append("#").length());
}

QString Form::getstring_clicked()
{
    char c[8];
    if(read(m_fd,c,sizeof c)){
        qDebug()<<"Success"<<endl;
        qDebug()<<c;
    }
    QString serial_getdata_str=QString(QLatin1String(c));
    return serial_getdata_str;
}
