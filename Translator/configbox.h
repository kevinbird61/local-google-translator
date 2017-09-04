#ifndef CONFIGBOX_H
#define CONFIGBOX_H

#include <QWidget>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>

namespace Ui {
class configBox;
}

class configBox : public QWidget
{
    Q_OBJECT

public:
    explicit configBox(QWidget *parent = 0);
    ~configBox();

signals:
    void updateClient(QString url);
    void fetchClient(int flags);

public slots:
    // manual
    void updateUrl(); // match updateBtn signal
    void fillCurrent(QString url); // fetch current using url, and fill it
    // auto
    void showReadme(); // dispaly readme
    void runSetup(); // display command of running up server

private:
    Ui::configBox *ui;
    QProcess *process;
};

#endif // CONFIGBOX_H
