#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    config_window = new configBox(parent);
    config_window->hide();
    hisbox = new historybox(parent);
    hisbox->hide();
    bmbox = new bookmarkbox(parent);
    bmbox->hide();
    translator_man = new translator();
    // Setting supported language. Format: ( "Display Name", "Attribute" )
    ui->LangCombobox->addItem("English",QVariant("en"));
    ui->LangCombobox->addItem("Français",QVariant("fr"));
    ui->LangCombobox->addItem("Deutsch",QVariant("de"));
    ui->LangCombobox->addItem("Español",QVariant("es"));
    ui->LangCombobox->addItem("日本語",QVariant("ja"));
    ui->LangCombobox->addItem("简体中文",QVariant("zh-CN"));
    ui->LangCombobox->addItem("繁體中文",QVariant("zh-TW"));

    // set connect with translator
    QObject::connect(translator_man,SIGNAL(getTrans(QNetworkReply*)),this,SLOT(getTrans(QNetworkReply*)));
    // set connect with itself
    QObject::connect(ui->aboutBtn,SIGNAL(clicked(bool)),this,SLOT(showAbout()));
    QObject::connect(ui->TransBtn,SIGNAL(clicked(bool)),this,SLOT(translate()));
    // set connect with config box
    QObject::connect(ui->editconnBtn,SIGNAL(clicked(bool)),this,SLOT(showConfigbox()));
    QObject::connect(config_window,SIGNAL(fetchClient(int)),this,SLOT(matcher(int)));
    QObject::connect(this,SIGNAL(sendUrl(QString)),config_window,SLOT(fillCurrent(QString)));
    QObject::connect(config_window,SIGNAL(updateClient(QString)),this,SLOT(changeUrl(QString)));
    // set connect with history box
    QObject::connect(ui->historyBtn,SIGNAL(clicked(bool)),this,SLOT(showHistory()));
    QObject::connect(this,SIGNAL(sendWord2His(QString)),hisbox,SLOT(addHistoryItem(QString)));
    QObject::connect(hisbox,SIGNAL(choosefromHis(QString)),this,SLOT(fillQuery(QString)));
    // set connect with bookmark box
    QObject::connect(ui->bookmarkBtn,SIGNAL(clicked(bool)),this,SLOT(showBookmark()));
    QObject::connect(bmbox,SIGNAL(chooseFromBmk(QString)),this,SLOT(fillQuery(QString)));
    // connection between different component
    QObject::connect(hisbox,SIGNAL(choosefromHis(QString)),bmbox,SLOT(saveFromhis(QString)));;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::translate()
{
    // qDebug() << ui->LangCombobox->currentData(Qt::DisplayRole).toString(); // get name of it
    qDebug() << ui->LangCombobox->currentData().toString(); // get attribute of it
    // And then using translator man
    translator_man->makeTrans(ui->LangCombobox->currentData().toString(),QString(ui->TransEdit->toPlainText()));
    // And then add to history
    emit sendWord2His(QString(ui->TransEdit->toPlainText()));
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

void MainWindow::showHistory()
{
    Qt::WindowFlags flags = hisbox->windowFlags();
    hisbox->setWindowFlags( flags | Qt::WindowStaysOnTopHint);
    hisbox->show();
}

void MainWindow::showBookmark()
{
    Qt::WindowFlags flags = bmbox->windowFlags();
    bmbox->setWindowFlags( flags | Qt::WindowStaysOnTopHint);
    bmbox->refresh(); // refresh with its model
    bmbox->show();
}

void MainWindow::showAbout()
{
    QMessageBox::information(this, tr("關於我(About me)"),
                           tr("Kevin Cyu, kevinbird61@gmail.com\n"
                              "© 2017 Copyright by Kevin Cyu"),
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

void MainWindow::fillQuery(QString query)
{
    ui->TransEdit->setText(query);
}
