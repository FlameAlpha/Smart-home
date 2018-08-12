#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>

namespace Ui {
class About;
}

class About : public QWidget
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();
public slots:
    void Display_AboutWidget_clicked();
    void close_this_window();
private slots:
    void on_pushButton_clicked();

    void on_ResetButton_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
