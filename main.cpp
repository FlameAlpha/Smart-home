#include "main.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //DataResetAlone();
    DataDefaultAlone();
    AllWindows allwindows;
    allwindows.userlock.move(0,0);
    allwindows.userlock.setWindowFlags(Qt::FramelessWindowHint);
    allwindows.userlock.show();
    return a.exec();
}

void AllWindows::Task_number_change(QString data)
{
    int x=0;
    bool test=false;
    int Data_temp=0;
    int y=0;
    timer.blockSignals(false);
    Data_temp=data.mid(0,7).toInt()/10000;
    for(x=0;x<Task_num;x++) if(ChangeData_ID[x]==Data_temp){ test=true; y=x; break;}
    if(test) ChangeData[y]=data;
    else{
    ChangeData_ID[Task_num]=Data_temp;
    ChangeState[Task_num]=true;
    ChangeData[Task_num]=data;
    Task_num++;
    }
    qDebug()<<"Task Number:"<<Task_num<<"Data Change"<<endl;
}

bool AllWindows::Datachange_task()
{
    int n; int m=0;
    for(n=Task_num;n>0;n--)
    {
        if(ChangeState[n-1]) form.sendstring_clicked(ChangeData[n-1]);
        else m++;
    }
    if(m==Task_num) { Task_num=0; timer.blockSignals(true); qDebug()<<"Task Over"<<endl; return true;}
    return false;
}

void AllWindows::Data_FromST(QString data_ST)
{
    int x;
    for(x=0;x<Task_num;x++) if(ChangeData[x]==data_ST){ ChangeState[x]=false; return;}
}
