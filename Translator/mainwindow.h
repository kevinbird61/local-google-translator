#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include "translator.h"
#include "configbox.h"
#include "historybox.h"
#include "bookmarkbox.h"

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
    void sendWord2His(QString source); // record history

public slots:
    void translate(); // translate anything, which depend on ui->LanguageCombobox
    void getTrans(QNetworkReply *reply);
    // menu bar
    void showAbout();
    void showConfigbox(); // show the configBox
    void showHistory(); // show history
    void showBookmark(); // show bookmark
    // config
    void matcher(int flags);
    void changeUrl(QString newUrl);
    // history
    void fillQuery(QString query); // fill the query field

private:
    Ui::MainWindow *ui;
    configBox *config_window;
    translator *translator_man;
    historybox *hisbox;
    bookmarkbox *bmbox;
};

#endif // MAINWINDOW_H
