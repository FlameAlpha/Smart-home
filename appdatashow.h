#ifndef APPDATASHOW_H
#define APPDATASHOW_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class AppDataShow;
}

class AppDataShow : public QWidget
{
    Q_OBJECT

public:
    explicit AppDataShow(QWidget *parent = 0);
    ~AppDataShow();
    void AppDataShowWindows(QString string);
private slots:

    void on_StatusDial_valueChanged(int value);

    void on_ONButton_clicked();

    void on_OFFButton_clicked();

    void DataChange_clicked(int data);

    void ShowThisWindows(QString data);

    void on_NumberSelect_currentIndexChanged(int index);

    void UpdateByTime_clicked();

    void on_CloseButton_clicked();

private:
    Ui::AppDataShow *ui;
    QTimer timer;

signals:

    void data_change_Str(QString data);
};

#endif // APPDATASHOW_H
