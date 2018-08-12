#ifndef SERIALFORM_H
#define SERIALFORM_H

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
class SerialForm;
}

class SerialForm : public QWidget
{
    Q_OBJECT

public:
    explicit SerialForm(QWidget *parent = 0);
    ~SerialForm();
    int openSerialPort();
public slots:
    void show_this_window();
    void close_this_window();
signals:
    void close_other_windows();
    void data_change(QString data);
    void data_change_Temp_Hum(QString Temp,QString Hum);
public slots:
    void on_SendButton_clicked();
    void remoteDataIncoming_clicked();
    void on_CloseButton_clicked();
    void sendstring_clicked(QString serial_senddata_str);
    QString getstring_clicked();
public:
    Ui::SerialForm *ui;
    int m_fd;
    QSocketNotifier *m_notifier;
};

#endif // SERIALFORM_H
