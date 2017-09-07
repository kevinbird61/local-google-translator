#include "historybox.h"
#include "ui_historybox.h"

historybox::historybox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::historybox)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":icon"));
    this->setWindowTitle("歷史紀錄(history record)");
    // connect
    QObject::connect(ui->addbmBtn,SIGNAL(clicked(bool)),this,SLOT(addbookMark()));
    QObject::connect(ui->helpBtn,SIGNAL(clicked(bool)),this,SLOT(showHow2do()));
    QObject::connect(ui->chooseBtn,SIGNAL(clicked(bool)),this,SLOT(choose()));
    // Initialize with empty view
    model = new QStringListModel(this);
    QStringList list;
    updateView(list);
}

historybox::~historybox()
{
    delete ui;
}

void historybox::updateView(QStringList newlist)
{
    model->setStringList(newlist);
    ui->hisView->setModel(model);
}

void historybox::addbookMark()
{
    /* QMessageBox::information(this, tr("尚未支援!"),
                           tr("敬請期待書籤功能!\n"),
                           QMessageBox::Ok | QMessageBox::Cancel,
                             QMessageBox::Ok);*/
    emit choosefromHis(ui->hisView->selectionModel()->selectedIndexes().first().data(Qt::DisplayRole).toString());
}

void historybox::showHow2do()
{
    QMessageBox::information(this, tr("操作說明(Helping Guide)"),
                           tr("首先在欄位中點選你要的項目\n"
                              "再來點選\"加入書籤\"即可完成加入!"),
                           QMessageBox::Ok | QMessageBox::Cancel,
                             QMessageBox::Ok);
}

void historybox::choose()
{
    // choose the word
    emit choosefromHis(ui->hisView->selectionModel()->selectedIndexes().first().data(Qt::DisplayRole).toString());
    // hide this widget
    this->hide();
}

void historybox::addHistoryItem(QString query)
{
    // Update stringlist
    QStringList curlist = model->stringList();
    curlist << query;
    updateView(curlist);
}
