#ifndef FLAMEWEIBO_H
#define FLAMEWEIBO_H

#include <QWidget>
#include <QUrl>
#include <QWebSettings>
#include <QWebFrame>

namespace Ui {
class FlameWeibo;
}

class FlameWeibo : public QWidget
{
    Q_OBJECT

public:
    explicit FlameWeibo(QWidget *parent = 0);
    ~FlameWeibo();

private slots:
    void on_GoButton_clicked();

    void on_CloseButton_clicked();

    void on_BackButton_clicked();

private:
    Ui::FlameWeibo *ui;
};

#endif // FLAMEWEIBO_H
