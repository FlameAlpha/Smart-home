#include "database.h"
#include "smarthome.h"
#include "ui_smarthome.h"
#include "sys/reboot.h"
#include "appdatashow.h"
#include <QProcess>
#include "about.h"

SmartHome::SmartHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmartHome)
{
    time.start(1000);
    QObject::connect(&time,SIGNAL(timeout()),this,SLOT(time_display_clicked()));
  /*
   *
   *ui->TVButton->setVisible(false);
    ui->WHButton->setVisible(false);
    ui->FridgeButton->setVisible(false);
    ui->MotorButton->setVisible(false);
    ui->SerialButton->setVisible(false);
*/
    ui->setupUi(this);
}

SmartHome::~SmartHome()
{
    delete ui;
}

void SmartHome::OpenSystemClicked()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->QWidget::move(0,0);
    this->show();
    emit close_other_windows();
}

void SmartHome::time_display_clicked()
{
    datetime=QDateTime::currentDateTime();
    QString displaytime=datetime.toString("yyyy-M-dd hh:mm:ss");
    ui->TimeDisplay->setText(displaytime);
}


void SmartHome::on_AboutButton_clicked()
{
    About *about=new About;
    about->move(0,0);
    about->setWindowFlags(Qt::FramelessWindowHint);
    about->show();
    about->setAttribute(Qt::WA_DeleteOnClose);
}

void SmartHome::on_LockButton_clicked()
{
    this->close();
}

void SmartHome::close_this_window()
{
    this->close();
}

void SmartHome::on_LightButton_clicked()
{
    emit open_appdisplay(QString("Light"));
}

void SmartHome::on_SerialButton_clicked()
{
    emit open_serialtest_window();
}

void SmartHome::on_FanButton_clicked()
{
    emit open_appdisplay(QString("Fan"));
}

void SmartHome::temp_hum_data_deal(QString Temp,QString Hum){
    ui->temp_display->setText(Temp);
    ui->hum_display->setText(Hum);
}
