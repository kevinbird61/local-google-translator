#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include "translator.h"
#include "configbox.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sendUrl(QString url);

public slots:
    void trans2Cht(bool flags); // translate left side to chinese
    void trans2Eng(bool flags); // translate left side to english
    void getTrans(QNetworkReply *reply);
    void showConfigbox(); // show the configBox
    // menu bar
    void showAbout();
    // config
    void matcher(int flags);
    void changeUrl(QString newUrl);

private:
    Ui::MainWindow *ui;
    configBox *config_window;
    translator *translator_man;
};

#endif // MAINWINDOW_H
