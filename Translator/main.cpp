#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QSysInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Setting font
    qDebug() << QSysInfo::productType();
    if(QSysInfo::productType() == "windows"){
        QFontDatabase::addApplicationFont(":notosans");
    }
    else{
        QFontDatabase::addApplicationFont("font/setofont.ttf");
    }
    qApp->setFont(QFont("cyu",14,QFont::Normal,false));
    // Mainwindow
    MainWindow w;
    w.setWindowIcon(QIcon(":icon"));
    // Make window on the top
    Qt::WindowFlags flags = w.windowFlags();
    w.setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    w.show();
    return a.exec();
}
