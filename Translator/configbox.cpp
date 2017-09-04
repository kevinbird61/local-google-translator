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
    // connect ui element
    connect(ui->readmeBtn,SIGNAL(clicked(bool)),this,SLOT(showReadme()));
    connect(ui->setupBtn,SIGNAL(clicked(bool)),this,SLOT(runSetup()));
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

void configBox::showReadme()
{
    // display the functionality of automatically run
    QMessageBox::information(this, tr("Run up localhost server"),
                           tr("Prerequisites(先備條件):\n"
                              " - Node.js (v8.1.2)\n"),
                           QMessageBox::Ok | QMessageBox::Cancel,
                             QMessageBox::Ok);
}

void configBox::runSetup()
{
    // display the functionality of automatically run
    QMessageBox::information(this, tr("How to do?"),
                           tr("Step 1: \n"
                              " - go to Translator Server directory.\n"
                              "Step 2: \n"
                              " - open an terminal(bash/linux , powershell(or cmd.exe)/windows).\n"
                              " - wait until seeing 'Server is running on xxxx ... ',"
                              "   then you can modify url to localhost:3000(default) !"
                              ),
                           QMessageBox::Ok | QMessageBox::Cancel,
                             QMessageBox::Ok);
    // TODO: using QProcess to setup translate server
}
