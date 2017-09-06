#ifndef HISTORYBOX_H
#define HISTORYBOX_H

#include <QStringListModel>
#include <QMessageBox>
#include <QWidget>
#include <QDebug>

namespace Ui {
class historybox;
}

class historybox : public QWidget
{
    Q_OBJECT

public:
    explicit historybox(QWidget *parent = 0);
    ~historybox();
    void updateView(QStringList newlist);

signals:
    void send2bookMark(); // bookmark btn (real signal)
    void choosefromHis(QString hisquery);

public slots:
    void addbookMark(); // bookmark btn (display message)
    void showHow2do(); // help btn
    void choose(); // choose btn
    /* receive from mainwindow */
    void addHistoryItem(QString query);

private:
    Ui::historybox *ui;
    QStringListModel *model;
};

#endif // HISTORYBOX_H
