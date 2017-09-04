#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Setting font
    QFontDatabase::addApplicationFont(":notosans");
    qApp->setFont(QFont("notosans",14,QFont::Normal,false));
    // Mainwindow
    MainWindow w;
    w.setWindowIcon(QIcon(":icon"));
    // Make window on the top
    Qt::WindowFlags flags = w.windowFlags();
    w.setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    w.show();
    return a.exec();
}
