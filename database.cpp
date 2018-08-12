#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"

int ID;
int AppCount=0;
QString VERSION_STR="1.0.0";


//appliance string
QString LIGHT_STR="Light";
QString FAN_STR="Fan";

//appliance enable
bool LIGHT_ENABLE=false;
bool FAN_ENABLE=false;

DataBase::DataBase()
{
/*
    QSqlDatabase bd;
    if(QSqlDatabase::contains("qt_sql_default_connection")) bd=QSqlDatabase::database("qt_sql_default_connection");
    else bd=QSqlDatabase::addDatabase("QSQLITE");
     //set SQL file name
    bd.setDatabaseName("/usr/local/bin/AppDataSQL.db");
    bd.open();

    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery("SELECT * FROM appliance WHERE appliance_type='Light'");
    int count=model->rowCount();
    //int *id, int num, bool *sta, QString ver, QString *bra, int *pro
    allappliance.light=new Light(new int[count],0,new bool[count],VERSION_STR,new QString[count],new int[count]);
    qDebug()<<"Light count:"<<count;

    model->setQuery("SELECT * FROM appliance WHERE appliance_type='Fan'");
    count=model->rowCount();
    allappliance.fan=new Fan(new int[count],0,new bool[count],VERSION_STR,new QString[count],new int[count]);
    qDebug()<<"Fan count:"<<count;

    bd.close();*/
}

void DataBase::DataReset()
{
    QFile::remove("/usr/local/bin/AppDataSQL.db");
    QFile::remove("/usr/local/bin/AppCountSQL.db");
    qDebug()<<"Start";

    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");

     //set SQL file name
    db.setDatabaseName("/usr/local/bin/AppDataSQL.db");

    if(db.open()) qDebug()<<"open right reset one";
    else  qDebug()<<"open error reset one";

    QSqlQuery query;
    bool success=query.exec("CREATE TABLE appliance("
                            "id INT PRIMARY KEY,"
                            "appliance_type VARCHAR,"
                            "brand VARCHAR,"
                            "version VARCHAR,"
                            "number INT,"
                            "status BOOL,"
                            "properties INT)");

    if(success) qDebug()<<"creat right";
    else qDebug()<<"creat error";

    query.prepare("INSERT INTO appliance (id, appliance_type, brand, version, number, status, properties) "
                      "VALUES (:id, :appliance_type, :brand, :version, :number, :status, :properties)");

    query.bindValue(":id",0);
    query.bindValue(":appliance_type","Light");
    query.bindValue(":brand","Brand0");
    query.bindValue(":version","VERSION_STR");
    query.bindValue(":number",0);
    query.bindValue(":status",false);
    query.bindValue(":properties",0);
    query.exec();

     query.exec("INSERT INTO appliance VALUES(1,'Fan','Brand0','1.0.0',0,0,0)");
     //query.exec("INSERT INTO appliance VALUES(2,'Light','Brand0','1.0.0',0,0,0)");
     //query.exec("INSERT INTO appliance VALUES(3,'Fan','Brand0','1.0.0',0,0,0)");

    query.exec("SELECT * FROM appliance ORDER BY id DESC");
    query.first();
    do
    {
        qDebug()<<"ID:"<<query.value(0).toInt();
        qDebug()<<"appliance_type:"<<query.value(1).toString();
        qDebug()<<"brand:"<<query.value(2).toString();
        qDebug()<<"version"<<query.value(3).toString();
        qDebug()<<"number"<<query.value(4).toInt();
        qDebug()<<"status:"<<query.value(5).toBool();
        qDebug()<<"properties"<<query.value(6).toInt();
    }
     while(query.next());
    db.close();

    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");

     //set SQL file name
    db.setDatabaseName("/usr/local/bin/AppCountSQL.db");

    if(db.open()) qDebug()<<"open right reset two";
    else  qDebug()<<"open error reset two";
        QSqlQuery query0;
    success=query0.exec("CREATE TABLE appliancecount("
                            "id INT PRIMARY KEY,"
                            "appliance_type VARCHAR)");

    if(success) qDebug()<<"creat right";
    query0.prepare("INSERT INTO appliancecount (id, appliance_type) "
                      "VALUES (:id, :appliance_type)");

    query0.bindValue(":id",0);
    query0.bindValue(":appliance_type","Light");

    query0.exec();

    query0.exec("INSERT INTO appliancecount VALUES(1,'Fan')");

    query0.exec("SELECT * FROM appliancecount ORDER BY id DESC");

    query0.first();
    do
    {
        qDebug()<<"ID:"<<query0.value(0).toInt();
        qDebug()<<"appliance_type:"<<query0.value(1).toString();
    }
    while(query0.next());

    db.close();
}

void DataBase::DataDefault()
{
    //int count;
    //int count_temp;
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("/usr/local/bin/AppCountSQL.db");
    if(db.open()) qDebug()<<"open right";

    QSqlQuery query;

    query.exec("SELECT * FROM appliancecount ORDER BY id DESC");

    QString string_temp;
    query.first();
    do
    {
        string_temp=query.value(1).toString();
        if(LIGHT_STR==string_temp)  {LIGHT_ENABLE=true; }
        if(FAN_STR==string_temp)    {FAN_ENABLE=true; }
        qDebug()<<"*";
        AppCount++;
    }
    while(query.next());

    qDebug()<<"AppCount:"<<AppCount;
    qDebug()<<"LIGHT_ENABLE"<<LIGHT_ENABLE;
    qDebug()<<"FAN_ENABLE"<<FAN_ENABLE;

    db.close();

    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");
     //set SQL file name
    db.setDatabaseName("/usr/local/bin/AppDataSQL.db");
    db.open();

    //order sql
    query.exec("SELECT * FROM appliance ORDER BY id DESC");

    //get ID number
    query.first();
    ID=query.value(0).toInt();
    qDebug()<<"ID:"<<ID;
    db.close();
}

void DataBase::DataInsect(QString appliance_type,QString brand)
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");

     //set SQL file name
    db.setDatabaseName("/usr/local/bin/AppDataSQL.db");

    if(db.open()) qDebug()<<"open right insect one";
    else  qDebug()<<"open error insect one";

    QSqlQuery query;

    query.prepare("INSERT INTO appliance (id, appliance_type, brand, version, number, status, properties) "
                      "VALUES (:id, :appliance_type, :brand, :version, :number, :status, :properties)");

    query.bindValue(":id",++ID);
    query.bindValue(":appliance_type",appliance_type);
    query.bindValue(":brand",brand);
    query.bindValue(":version",VERSION_STR);
    query.bindValue(":number",0);
    query.bindValue(":status",false);
    query.bindValue(":properties",0);
    if(query.exec()) qDebug()<<"Insect allright";

    QString str=QString("SELECT * FROM appliance WHERE id =").append(QString::number(ID));
    query.exec(str);

    query.next();
    {
        qDebug()<<"ID:"<<query.value(0).toInt();
        qDebug()<<"appliance_type:"<<query.value(1).toString();
        qDebug()<<"brand:"<<query.value(2).toString();
        qDebug()<<"version"<<query.value(3).toString();
        qDebug()<<"number"<<query.value(4).toInt();
        qDebug()<<"status:"<<query.value(5).toBool();
        qDebug()<<"properties"<<query.value(6).toInt();
    }

    db.close();

    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");

     //set SQL file name
    db.setDatabaseName("/usr/local/bin/AppCountSQL.db");

    if(db.open()) qDebug()<<"open right insect two";
    else  qDebug()<<"open error insect two";

    QSqlQuery query_count;

    QString str0=QString("SELECT * FROM appliancecount");
    query_count.exec(str0);

    while(query_count.next())
    {
        if(query_count.value(1).toString()==appliance_type){
            db.close();
            return;
        }

    }

    {
      str0=QString("SELECT * FROM appliancecount");
      QSqlQueryModel model;
      model.setQuery(str0);
      int ID_temp=model.rowCount();

      query_count.prepare("INSERT INTO appliancecount (id, appliance_type) "
                        "VALUES (:id, :appliance_type)");

      query_count.bindValue(":id",ID_temp);
      query_count.bindValue(":appliance_type",appliance_type);

      query_count.exec();
      qDebug()<<"add app";
    }

    db.close();
}
void DataBase::AllDataDisplay()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");

     //set SQL file name
    db.setDatabaseName("/usr/local/bin/AppDataSQL.db");

    if(db.open()) qDebug()<<"open right alldisplay";
    else  qDebug()<<"open error reset alldisplay";

    QSqlQuery query;

    query.exec("SELECT * FROM appliance ORDER BY id DESC");
    query.first();
    do
    {
        qDebug()<<"ID:"<<query.value(0).toInt();
        qDebug()<<"appliance_type:"<<query.value(1).toString();
        qDebug()<<"brand:"<<query.value(2).toString();
        qDebug()<<"version"<<query.value(3).toString();
        qDebug()<<"number"<<query.value(4).toInt();
        qDebug()<<"status:"<<query.value(5).toBool();
        qDebug()<<"properties"<<query.value(6).toInt();
    }
    while(query.next());
    db.close();

    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");

     //set SQL file name
    db.setDatabaseName("/usr/local/bin/AppCountSQL.db");

    if(db.open()) qDebug()<<"open right reset two";
    else  qDebug()<<"open error reset two";

    QSqlQuery query0;

    query0.exec("SELECT * FROM appliancecount ORDER BY id DESC");

    query0.first();
    do
    {
        qDebug()<<"ID:"<<query0.value(0).toInt();
        qDebug()<<"appliance_type:"<<query0.value(1).toString();
    }
    while(query0.next());

    db.close();
}

void DataBase::DeleteByID(int ID_temp)
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");

     //set SQL file name
    db.setDatabaseName("/usr/local/bin/AppDataSQL.db");

    if(db.open()) qDebug()<<"open right delete one";
    else  qDebug()<<"open error delete one";

    QSqlQuery query;
    QString str=QString("DELETE FROM appliance WHERE id =").append(QString::number(ID_temp));
    query.prepare(str);
    if(!query.exec()) qDebug()<<"delete error";

}

void DataBase::UpdateByID(int ID_temp,bool status_temp,int properties_temp)
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");

     //set SQL file name
    db.setDatabaseName("/usr/local/bin/AppDataSQL.db");

    if(db.open()) qDebug()<<"open right Update one";
    else  qDebug()<<"open error Update one";

    QSqlQuery query;
    query.prepare(QString("UPDATE appliance SET status=?, properties=? WHERE id=").append(QString::number(ID_temp)));
    query.bindValue(0,status_temp);
    query.bindValue(1,properties_temp);
    query.exec();

    db.close();
}
Appliance DataBase::GetDataByID(int ID_temp)
{
     QSqlDatabase db;
     if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
     else db=QSqlDatabase::addDatabase("QSQLITE");

      //set SQL file name
     db.setDatabaseName("/usr/local/bin/AppDataSQL.db");

     if(db.open()) qDebug()<<"open right GetDataByAppType";
     else  qDebug()<<"open error reset GetDataByAppType";

     QSqlQuery query;
     QString str=QString("SELECT * FROM appliance WHERE id = ").append(QString::number(ID_temp));
     query.exec(str);

     QSqlQueryModel model;
     model.setQuery(str);
     int count=model.rowCount();

     Appliance appliance(new int[count],0,new bool[count],VERSION_STR,new QString[count],new int[count]);

     query.next();
     int count_temp=0;

     //int *id, int num, bool *sta, QString ver, QString *bra, int *pro
     appliance.version=query.value(3).toString();
     appliance.number=query.value(4).toInt();


         appliance.ID[count_temp] = query.value(0).toInt();
         appliance.brand[count_temp] = query.value(2).toString();
         appliance.status[count_temp] = query.value(5).toBool();
         appliance.properties[count_temp] = query.value(6).toInt();
         count_temp++;


     db.close();
     return appliance;
}
Appliance DataBase::GetDataByAppType(QString appliance_type)
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");

     //set SQL file name
    db.setDatabaseName("/usr/local/bin/AppDataSQL.db");

    if(db.open()) qDebug()<<"open right GetDataByAppType";
    else  qDebug()<<"open error reset GetDataByAppType";

    QSqlQuery query;
    QString str=QString("SELECT * FROM appliance WHERE appliance_type = '").append(appliance_type).append(QString("'"));
    query.exec(str);

    QSqlQueryModel model;
    model.setQuery(str);
    int count=model.rowCount();

    Appliance appliance(new int[count],0,new bool[count],VERSION_STR,new QString[count],new int[count]);

    query.next();
    int count_temp=0;

    //int *id, int num, bool *sta, QString ver, QString *bra, int *pro
    appliance.version=query.value(3).toString();


    do
    {
        appliance.ID[count_temp] = query.value(0).toInt();
        appliance.brand[count_temp] = query.value(2).toString();
        appliance.status[count_temp] = query.value(5).toBool();
        appliance.properties[count_temp] = query.value(6).toInt();
        count_temp++;
    }
    while(query.next());

    appliance.number=count_temp;

    db.close();
    return appliance;
}
void DataResetAlone()
{
    QFile::remove("/usr/local/bin/AppDataSQL.db");
    QFile::remove("/usr/local/bin/AppCountSQL.db");
    qDebug()<<"Start";

    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");

     //set SQL file name
    db.setDatabaseName("/usr/local/bin/AppDataSQL.db");

    if(db.open()) qDebug()<<"open right reset one";
    else  qDebug()<<"open error reset one";

    QSqlQuery query;
    bool success=query.exec("CREATE TABLE appliance("
                            "id INT PRIMARY KEY,"
                            "appliance_type VARCHAR,"
                            "brand VARCHAR,"
                            "version VARCHAR,"
                            "number INT,"
                            "status BOOL,"
                            "properties INT)");

    if(success) qDebug()<<"creat right";
    else qDebug()<<"creat error";

    query.prepare("INSERT INTO appliance (id, appliance_type, brand, version, number, status, properties) "
                      "VALUES (:id, :appliance_type, :brand, :version, :number, :status, :properties)");

    query.bindValue(":id",0);
    query.bindValue(":appliance_type","Light");
    query.bindValue(":brand","Brand0");
    query.bindValue(":version","VERSION_STR");
    query.bindValue(":number",0);
    query.bindValue(":status",true);
    query.bindValue(":properties",10);
    query.exec();

     query.exec("INSERT INTO appliance VALUES(1,'Fan','Brand0','1.0.0',0,0,0)");
     query.exec("INSERT INTO appliance VALUES(4,'Fan','Brand0','1.0.0',0,0,0)");
     query.exec("INSERT INTO appliance VALUES(2,'Light','Brand0','1.0.0',0,1,50)");
     query.exec("INSERT INTO appliance VALUES(3,'Light','Brand0','1.0.0',0,1,100)");

    query.exec("SELECT * FROM appliance ORDER BY id DESC");
    query.first();
    do
    {
        qDebug()<<"ID:"<<query.value(0).toInt();
        qDebug()<<"appliance_type:"<<query.value(1).toString();
        qDebug()<<"brand:"<<query.value(2).toString();
        qDebug()<<"version"<<query.value(3).toString();
        qDebug()<<"number"<<query.value(4).toInt();
        qDebug()<<"status:"<<query.value(5).toBool();
        qDebug()<<"properties"<<query.value(6).toInt();
    }
     while(query.next());
    db.close();

    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");

     //set SQL file name
    db.setDatabaseName("/usr/local/bin/AppCountSQL.db");

    if(db.open()) qDebug()<<"open right reset two";
    else  qDebug()<<"open error reset two";
    QSqlQuery query0;
    success=query0.exec("CREATE TABLE appliancecount("
                            "id INT PRIMARY KEY,"
                            "appliance_type VARCHAR)");

    if(success) qDebug()<<"creat right";
    query0.prepare("INSERT INTO appliancecount (id, appliance_type) "
                      "VALUES (:id, :appliance_type)");

    query0.bindValue(":id",0);
    query0.bindValue(":appliance_type","Light");

    query0.exec();

    query0.exec("INSERT INTO appliancecount VALUES(1,'Fan')");

    query0.exec("SELECT * FROM appliancecount ORDER BY id DESC");

    query0.first();
    do
    {
        qDebug()<<"ID:"<<query0.value(0).toInt();
        qDebug()<<"appliance_type:"<<query0.value(1).toString();
    }
    while(query0.next());

    db.close();
}

void DataDefaultAlone()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("/usr/local/bin/AppCountSQL.db");
    if(db.open()) qDebug()<<"open right";

    QSqlQuery query;

    query.exec("SELECT * FROM appliancecount ORDER BY id DESC");

    QString string_temp;
    query.first();
    do
    {
        string_temp=query.value(1).toString();
        if(LIGHT_STR==string_temp)  {LIGHT_ENABLE=true; }
        if(FAN_STR==string_temp)    {FAN_ENABLE=true; }
        qDebug()<<"*";
        AppCount++;
    }
    while(query.next());

    qDebug()<<"AppCount:"<<AppCount;
    qDebug()<<"LIGHT_ENABLE"<<LIGHT_ENABLE;
    qDebug()<<"FAN_ENABLE"<<FAN_ENABLE;

    db.close();

    if(QSqlDatabase::contains("qt_sql_default_connection")) db=QSqlDatabase::database("qt_sql_default_connection");
    else db=QSqlDatabase::addDatabase("QSQLITE");
     //set SQL file name
    db.setDatabaseName("/usr/local/bin/AppDataSQL.db");
    db.open();

    //get ID number

    QSqlQueryModel model;
    model.setQuery("SELECT * FROM appliance");
    ID=model.rowCount();
    qDebug()<<"ID:"<<--ID;
    db.close();
}
#endif
