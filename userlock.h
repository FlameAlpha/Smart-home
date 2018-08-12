#ifndef USERLOCK_H
#define USERLOCK_H

#include <QWidget>
#include <QDateTime>
#include <QTimer>

namespace Ui {
class UserLock;
}

class UserLock : public QWidget
{
    Q_OBJECT

public:
    explicit UserLock(QWidget *parent = 0);
    ~UserLock();
    Ui::UserLock *ui;
    QDateTime datetime;
    QTimer time;
    QString PIN_txt;
signals:
    void open_system();
public slots:
    void displaylock_clicked();
    void close_this_window();
    void on_OkButton_clicked();
    void PIN_txt_clicked();
    void time_display_clicked();
    void on_PowerButton_clicked();
private slots:
    void on_Push_0_clicked();
    void on_Push_1_clicked();
    void on_Push_2_clicked();
    void on_Push_3_clicked();
    void on_Push_4_clicked();
    void on_Push_5_clicked();
    void on_Push_6_clicked();
    void on_Push_8_clicked();
    void on_Push_7_clicked();
    void on_Push_9_clicked();
};



#endif // USERLOCK_H
