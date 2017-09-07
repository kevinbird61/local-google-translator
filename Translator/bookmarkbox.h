#ifndef BOOKMARKBOX_H
#define BOOKMARKBOX_H

#include <QStringListModel>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>
#include <QDebug>

namespace Ui {
class bookmarkbox;
}

class bookmarkbox : public QWidget
{
    Q_OBJECT

public:
    explicit bookmarkbox(QWidget *parent = 0);
    ~bookmarkbox();
    void updateView(QStringList bmklist);
    void refresh();

signals:
    void chooseFromBmk(QString query); // choose from bookmark signal

public slots:
    void selectSourceFile();
    void saveBookmark();
    void popBookmark(); // choose from bookmark btn
    void saveFromhis(QString query); // save in current model as history
    void loadFromhis(); // append the buffer to current bookmark


private:
    Ui::bookmarkbox *ui;
    QStringListModel *model;
    QStringList buffer; // buffer from history addbookmark
};

#endif // BOOKMARKBOX_H
