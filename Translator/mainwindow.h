#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "translator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void trans2Cht(bool flags); // translate left side to chinese
    void trans2Eng(bool flags); // translate left side to english
    void getTrans(QNetworkReply *reply);
    // menu bar
    void showAbout(bool flags);

private:
    Ui::MainWindow *ui;
    translator *translator_man;
};

#endif // MAINWINDOW_H
