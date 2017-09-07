#include "bookmarkbox.h"
#include "ui_bookmarkbox.h"

bookmarkbox::bookmarkbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bookmarkbox)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":icon"));
    this->setWindowTitle("書籤(bookmark)");
    // connect
    QObject::connect(ui->sourceBtn,SIGNAL(clicked(bool)),this,SLOT(selectSourceFile()));
    QObject::connect(ui->saveBtn,SIGNAL(clicked(bool)),this,SLOT(saveBookmark()));
    QObject::connect(ui->addfromhisBtn,SIGNAL(clicked(bool)),this,SLOT(loadFromhis()));
    QObject::connect(ui->chooseBtn,SIGNAL(clicked(bool)),this,SLOT(popBookmark()));
    // Initialize with empty view
    model = new QStringListModel(this);
    QStringList list;
    updateView(list);
}

bookmarkbox::~bookmarkbox()
{
    delete ui;
}

void bookmarkbox::updateView(QStringList bmklist)
{
    model->setStringList(bmklist);
    ui->bookmarkView->setModel(model);
}

void bookmarkbox::refresh()
{
    // refresh
    ui->bookmarkView->setModel(model);
}

void bookmarkbox::selectSourceFile()
{
    // using ".bmk" as save file format
    QString selectedFile = QFileDialog::getOpenFileName(this,tr("選擇載入的書籤檔(Select bookmark file)"),QDir::currentPath(),tr("*.bmk"));
    // Get this file
    ui->sourcePath->setText(selectedFile);
    // Load file & parse to get all bookmark
    QFile file(selectedFile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray result;
    while(!file.atEnd()){
        result += file.readLine();
    }
    // Then fill the bookmarkview & update current model
    QStringList bookmarktag = QString(result).split('\n');
    updateView(bookmarktag);
}

void bookmarkbox::saveBookmark()
{
    // display message
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("儲存書籤(Save bookmark)!"),
                           tr("書籤將儲存於執行檔相同的位置\n"
                              "並且命名為 bookmark.bmk\n"
                              "是否儲存?"),
                           QMessageBox::Yes | QMessageBox::No);
    // get reply
    if(reply == QMessageBox::Yes){
        // save
        QFile savebmk("bookmark.bmk");
        if (!savebmk.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        // write
        QTextStream out(&savebmk);
        out.setCodec("UTF-8"); // encode as utf8
        QStringList curBmk = model->stringList();
        foreach (const QString &str, curBmk) {
            out << str << "\n";
        }
    }
    else{
        // ignore
    }
}

void bookmarkbox::popBookmark()
{
    emit chooseFromBmk(ui->bookmarkView->selectionModel()->selectedIndexes().first().data(Qt::DisplayRole).toString());
    this->hide();
}

void bookmarkbox::saveFromhis(QString query)
{
    // store into temp buffer
    buffer << query;
}

void bookmarkbox::loadFromhis()
{
    // QStringList bmklist = model->stringList();
    // bmklist = bmklist + buffer;
    updateView(model->stringList()+buffer);
}
