#ifndef MAIN_H
#define MAIN_H
#include <QApplication>
#include <QWidget>

#include "smarthome.h"
#include "userlock.h"
#include "serialform.h"
#include "database.h"
#include "appdatashow.h"
#include "form.h"

class AllWindows:public QWidget
{
    Q_OBJECT
public:
    UserLock userlock;
    SmartHome smarthome;
    SerialForm serialform;
    AppDataShow appdatashow;
    Form form;
    QTimer timer;
    bool ChangeState[100];
    QString ChangeData[100];
    int ChangeData_ID[100];
    int Task_num;
    AllWindows(QWidget *parent = 0):QWidget(parent)
    {
        Task_num=0;
        timer.start(1000);
        timer.blockSignals(true);
        QObject::connect(&userlock,SIGNAL(open_system()),&smarthome,SLOT(OpenSystemClicked()));
        QObject::connect(&smarthome,SIGNAL(open_serialtest_window()),&serialform,SLOT(show_this_window()));
        QObject::connect(&smarthome,SIGNAL(open_appdisplay(QString)),&appdatashow,SLOT(ShowThisWindows(QString)));
        QObject::connect(&form,SIGNAL(data_change(int)),&appdatashow,SLOT(DataChange_clicked(int)));
        QObject::connect(&form,SIGNAL(data_change_ST(QString)),this,SLOT(Data_FromST(QString)));
        QObject::connect(&appdatashow,SIGNAL(data_change_Str(QString)),this,SLOT(Task_number_change(QString)));
        QObject::connect(&serialform,SIGNAL(data_change(QString)),this,SLOT(Task_number_change(QString)));
        QObject::connect(&timer,SIGNAL(timeout()),this,SLOT(Datachange_task()));
        QObject::connect(&serialform,SIGNAL(data_change_Temp_Hum(QString,QString)),&smarthome,SLOT(temp_hum_data_deal(QString,QString)));
    }
    ~AllWindows()
    {

    }

public slots:
    bool Datachange_task();
    void Task_number_change(QString data);
    void Data_FromST(QString data_ST);
};

extern AllWindows allwindows;

#endif // MAIN_H
