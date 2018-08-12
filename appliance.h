#ifndef APPLIANCE_H
#define APPLIANCE_H

#include <QWidget>
#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>


namespace Ui {
class Appliance;
}

class Appliance : public QWidget
{
    Q_OBJECT

public:
    explicit Appliance(QWidget *parent = 0);
    ~Appliance();
signals:
    void open_userlock();
    void close_other_windows();
public slots:
    void ReadFile_clicked();
    void close_this_window();
private slots:
    void on_closeButton_clicked();

private:
    Ui::Appliance *ui;
};

#endif // APPLIANCE_H
