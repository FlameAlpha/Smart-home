#include "appdatashow.h"
#include "ui_appdatashow.h"
#include "database.h"
#include "serialform.h"

AppDataShow::AppDataShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppDataShow)
{
    this->move(0,0);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QObject::connect(&timer,SIGNAL(timeout()),this,SLOT(UpdateByTime_clicked()));
    timer.start(1000);
    timer.blockSignals(true);
    ui->setupUi(this);
}

AppDataShow::~AppDataShow()
{
    delete ui;
}

void AppDataShow::ShowThisWindows(QString data)
{
    this->AppDataShowWindows(data);
    this->show();
    timer.blockSignals(false);
}

void AppDataShow::AppDataShowWindows(QString string)
{
    ui->TypeLabel->setText(string);
    ui->StatusDial->blockSignals(true);
    ui->NumberSelect->blockSignals(true);
    ui->PropertiesBox->blockSignals(true);
    ui->NumberSelect->clear();
    DataBase database;
    Appliance appliance (database.GetDataByAppType(string));
    int count;
    for(count=0;count<appliance.number;count++){
        ui->NumberSelect->addItem(QString::number(count));
    }
    ui->IDLabel->setText(QString::number(appliance.ID[0]));
    ui->StatusLabel->setText(QString::number(appliance.status[0]));
    ui->PropertiesBox->setValue(appliance.properties[0]);
    ui->StatusDial->blockSignals(false);
    ui->NumberSelect->blockSignals(false);
    ui->PropertiesBox->blockSignals(false);
}

void AppDataShow::on_StatusDial_valueChanged(int value)
{
    DataBase database;
    Appliance appliance(database.GetDataByID(ui->IDLabel->text().toInt()));
    //ui->PropertiesBox->blockSignals(true);
    //ui->StatusDial->blockSignals(true);
    //SerialForm serialform;
    QString IDStr=QString("%1").arg(appliance.ID[0],3,10,QLatin1Char('0'));
    QString ValueStr=QString("%1").arg(value,3,10,QLatin1Char('0'));
    QString str=IDStr.append(QString("1")).append(ValueStr);
    //serialform.sendstring_clicked(str);
    qDebug()<<"AppDataShow : "<<str<<endl;
    //ui->PropertiesBox->blockSignals(false);
    //ui->StatusDial->blockSignals(false);
    emit data_change_Str(str);
}

void AppDataShow::on_ONButton_clicked()
{
    DataBase database;
    Appliance appliance(database.GetDataByID(ui->IDLabel->text().toInt()));
    if(appliance.status[0])return;
    else {
        //SerialForm serialform;
        QString IDStr=QString("%1").arg(appliance.ID[0],3,10,QLatin1Char('0'));
        QString str=IDStr.append(QString("1000"));
        //serialform.sendstring_clicked(str);
        qDebug()<<"AppDataShow : "<<str<<endl;
        emit data_change_Str(str);
    }
}

void AppDataShow::on_OFFButton_clicked()
{
    DataBase database;
    Appliance appliance(database.GetDataByID(ui->IDLabel->text().toInt()));
    if(!appliance.status[0])return;
    else {
        //SerialForm serialform;
        QString IDStr=QString("%1").arg(appliance.ID[0],3,10,QLatin1Char('0'));
        QString str=IDStr.append(QString("0000"));
        //serialform.sendstring_clicked(str);
        qDebug()<<"AppDataShow : "<<str<<endl;
        emit data_change_Str(str);
    }
}

void AppDataShow::DataChange_clicked(int data)
{
    int ID_num=data/10000;
    ui->PropertiesBox->blockSignals(true);
    //ui->StatusDial->blockSignals(true);
    if(ui->IDLabel->text().toInt()==ID_num)
    {
        ui->PropertiesBox->setValue(data%1000);
        ui->StatusLabel->setText(QString::number(data%10000/1000));
    }
    else return;
    ui->PropertiesBox->blockSignals(false);
    //ui->StatusDial->blockSignals(false);
}

void AppDataShow::on_NumberSelect_currentIndexChanged(int index)
{
    DataBase database;
    Appliance appliance(database.GetDataByAppType(ui->TypeLabel->text()));
    int number=index;
    ui->PropertiesBox->blockSignals(true);
    ui->StatusDial->blockSignals(true);
    ui->IDLabel->setText(QString::number(appliance.ID[number]));
    ui->StatusLabel->setText(QString::number(appliance.status[number]));
    ui->PropertiesBox->setValue(appliance.properties[number]);
    ui->PropertiesBox->blockSignals(false);
    ui->StatusDial->blockSignals(false);
}

void AppDataShow::UpdateByTime_clicked()
{
    DataBase database;
    ui->PropertiesBox->blockSignals(true);
    ui->StatusDial->blockSignals(true);
    Appliance appliance (database.GetDataByID(ui->IDLabel->text().toInt()));
    ui->StatusLabel->setText(QString::number(appliance.status[0]));
    ui->PropertiesBox->setValue(appliance.properties[0]);
    ui->StatusDial->setValue(appliance.properties[0]);
    ui->StatusDial->blockSignals(false);
    ui->PropertiesBox->blockSignals(false);
}

void AppDataShow::on_CloseButton_clicked()
{
    this->close();
    timer.blockSignals(true);
}
