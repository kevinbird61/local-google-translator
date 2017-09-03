#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    config_window = new configBox(parent);
    config_window->hide();
    translator_man = new translator();
    // set connect with translator
    QObject::connect(translator_man,SIGNAL(getTrans(QNetworkReply*)),this,SLOT(getTrans(QNetworkReply*)));
    // set connect with itself
    QObject::connect(ui->ChtBtn,SIGNAL(clicked(bool)),this,SLOT(trans2Cht(bool)));
    QObject::connect(ui->EngBtn,SIGNAL(clicked(bool)),this,SLOT(trans2Eng(bool)));
    QObject::connect(ui->aboutBtn,SIGNAL(clicked(bool)),this,SLOT(showAbout()));
    // set connect with config box
    QObject::connect(ui->editconnBtn,SIGNAL(clicked(bool)),this,SLOT(showConfigbox()));
    QObject::connect(config_window,SIGNAL(fetchClient(int)),this,SLOT(matcher(int)));
    QObject::connect(this,SIGNAL(sendUrl(QString)),config_window,SLOT(fillCurrent(QString)));
    QObject::connect(config_window,SIGNAL(updateClient(QString)),this,SLOT(changeUrl(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::trans2Cht(bool flags)
{
    translator_man->makeTrans(QString("zh-TW"),QString(ui->TransEdit->toPlainText()));
}

void MainWindow::trans2Eng(bool flags)
{
    translator_man->makeTrans(QString("en"),QString(ui->TransEdit->toPlainText()));
}

void MainWindow::getTrans(QNetworkReply *reply)
{
    ui->TransResult->setText(reply->readAll());
    if(ui->TransResult->toPlainText() == QString("error")){
        ui->statusBar->showMessage("error, please check out your url.");
    }
    else{
        ui->statusBar->showMessage("success");
    }
}

void MainWindow::showConfigbox()
{
    // pull this window to highest
    Qt::WindowFlags flags = config_window->windowFlags();
    config_window->setWindowFlags( flags | Qt::WindowStaysOnTopHint);
    config_window->show();
    // emit first
    emit sendUrl(translator_man->getServerUrl());
}

void MainWindow::showAbout()
{
    QMessageBox::information(this, tr("關於我(About me)"),
                           tr("Kevin Cyu, kevinbird61@gmail.com\n"
                              "© 2017 Copyright by Kevin CYU"),
                           QMessageBox::Ok | QMessageBox::Cancel,
                             QMessageBox::Ok);
}

void MainWindow::matcher(int flags)
{
    if(flags == 0){
        // fetch client signal
        qDebug() << "matcher";
        emit sendUrl(translator_man->getServerUrl());
    }
}

void MainWindow::changeUrl(QString newUrl)
{
    qDebug() << "Get new url:" << newUrl;
    translator_man->setServerUrl(newUrl);
}
