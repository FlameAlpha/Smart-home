#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QTextCodec>
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QString>

extern int ID;
extern int AppCount;
extern QString VERSION_STR;
extern void DataResetAlone();
extern void DataDefaultAlone();
class Appliance
{
public :
    int *ID;
    int number;
    bool *status;
    QString version;
    QString *brand;
    int *properties;
    Appliance(int *id, int num, bool *sta, QString ver, QString *bra, int *pro):ID(id),number(num),status(sta),version(ver),brand(bra),properties(pro){}
};
class Light:public Appliance
{
public :
    Light(int *id, int num, bool *sta, QString ver, QString *bra, int *pro):Appliance(id,num,sta,ver,bra,pro){}
};
class Fan:public Appliance
{
public:
    Fan(int *id, int num, bool *sta, QString ver, QString *bra, int *pro):Appliance(id,num,sta,ver,bra,pro){}
};
class AllAppliance
{
public:
    Light *light;
    Fan *fan;
};

class DataBase
{
public:
    DataBase();
    void DataReset();
    void DataDefault();
    void DataInsect(QString appliance_type,QString brand);
    void AllDataDisplay();
    void DeleteByID(int ID_temp);
    void UpdateByID(int ID_temp,bool status_temp,int properties_temp);
    Appliance GetDataByID(int ID_temp);
    Appliance GetDataByAppType(QString appliance_type);
    //AllAppliance allappliance;
};

#endif // DATABASE_H
