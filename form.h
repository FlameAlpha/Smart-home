#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QSocketNotifier>
#include <QMessageBox>
#include <QString>
#include <QLatin1String>

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <errno.h>
#include <string.h>
#include <termio.h>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    int openSerialPort();
public slots:
    void show_this_window();
    void close_this_window();
signals:
    void close_other_windows();
    void data_change(int data);
    void data_change_ST(QString data_s);
public slots:
    void on_SendButton_clicked();
    void remoteDataIncoming_clicked();
    void on_CloseButton_clicked();
    void sendstring_clicked(QString serial_senddata_str);
    QString getstring_clicked();
public:
    Ui::Form *ui;
    int m_fd;
    QSocketNotifier *m_notifier;
};

#endif // FORM_H
