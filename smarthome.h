#ifndef SMARTHOME_H
#define SMARTHOME_H

#include <QWidget>
#include <QDateTime>
#include <QTimer>


namespace Ui {
class SmartHome;
}


class SmartHome :public QWidget
{
    Q_OBJECT

public :
    explicit SmartHome(QWidget *parent = 0);
    ~SmartHome();
    Ui::SmartHome *ui;
    QDateTime datetime;
    QTimer time;
signals:
    void open_aboutwidget();
    void open_displaylightdata();
    void close_other_windows();
    void open_serialtest_window();
    void open_appdisplay(QString data);
public slots:
    void OpenSystemClicked();
    void time_display_clicked();
    void close_this_window();
public slots:
    void on_AboutButton_clicked();
    void on_LockButton_clicked();
    void temp_hum_data_deal(QString Temp,QString Hum);
private slots:
    void on_LightButton_clicked();
    void on_SerialButton_clicked();
    void on_FanButton_clicked();
};

#endif // SMARTHOME_H
