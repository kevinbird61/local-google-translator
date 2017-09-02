#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    translator_man = new translator();
    // set connect
    QObject::connect(translator_man,SIGNAL(getTrans(QNetworkReply*)),this,SLOT(getTrans(QNetworkReply*)));
    QObject::connect(ui->ChtBtn,SIGNAL(clicked(bool)),this,SLOT(trans2Cht(bool)));
    QObject::connect(ui->EngBtn,SIGNAL(clicked(bool)),this,SLOT(trans2Eng(bool)));
    QObject::connect(ui->menuBtn_about,SIGNAL(triggered(bool)),this,SLOT(showAbout(bool)));
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
    ui->statusBar->showMessage("success");
}

void MainWindow::showAbout(bool flags)
{
    QMessageBox::information(this, tr("關於我(About me)"),
                           tr("Kevin Cyu, kevinbird61@gmail.com\n"
                              "© 2017 Copyright by Kevin CYU"),
                           QMessageBox::Ok | QMessageBox::Cancel,
                           QMessageBox::Ok);
}

