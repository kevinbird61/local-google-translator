#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":icon"));
    // Make window on the top
    Qt::WindowFlags flags = w.windowFlags();
    w.setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    w.show();
    return a.exec();
}
