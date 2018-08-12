#include "flameweibo.h"
#include "ui_flameweibo.h"

FlameWeibo::FlameWeibo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlameWeibo)
{
    //QObject::connect(ui->BackButton,SIGNAL(clicked()),ui->webView,SLOT(back()));
    ui->setupUi(this);
}

FlameWeibo::~FlameWeibo()
{
    delete ui;
}

void FlameWeibo::on_GoButton_clicked()
{
    ui->webView->load(QUrl(QString(ui->address->text().toLocal8Bit())));
    //ui->webView->setPage(QWebPage::setPreferredContentsSize(QSize(480,272)));
    QWebSettings *setting=ui->webView->settings();
    QWebSettings::globalSettings();
    setting->setAttribute(QWebSettings::PluginsEnabled,true);
    setting->setAttribute(QWebSettings::JavaEnabled,true);
    setting->setAttribute(QWebSettings::JavascriptEnabled,true);
    setting->setAttribute(QWebSettings::JavascriptCanOpenWindows,true);
    setting->setAttribute(QWebSettings::JavascriptCanAccessClipboard,true);
    setting->setAttribute(QWebSettings::DeveloperExtrasEnabled,true);
    setting->setAttribute(QWebSettings::SpatialNavigationEnabled,true);
    setting->setAttribute(QWebSettings::LinksIncludedInFocusChain,true);
    setting->setAttribute(QWebSettings::AcceleratedCompositingEnabled,true);
    setting->setAttribute(QWebSettings::AutoLoadImages,true);
    //delete [] setting;
}

void FlameWeibo::on_CloseButton_clicked()
{
    this->close();
}

void FlameWeibo::on_BackButton_clicked()
{
    ui->webView->back();
}
