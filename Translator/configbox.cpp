#include "configbox.h"
#include "ui_configbox.h"

configBox::configBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::configBox)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":icon"));;
    this->setWindowTitle("Edit Connection");
    // connect to target
    connect(ui->updateBtn,SIGNAL(clicked(bool)),this,SLOT(updateUrl()));
    // emit fetching signal to client to get current url
    emit fetchClient(0);
}

configBox::~configBox()
{
    delete ui;
}

void configBox::updateUrl()
{
    emit updateClient(ui->update_field->toPlainText()); // emit to client to update
    // and then update! close
    this->close();
}

void configBox::fillCurrent(QString url)
{
    ui->change_field->setText(url);
}
