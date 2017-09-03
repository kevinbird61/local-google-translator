#ifndef CONFIGBOX_H
#define CONFIGBOX_H

#include <QWidget>

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
    void updateUrl(); // match updateBtn signal
    void fillCurrent(QString url); // fetch current using url, and fill it

private:
    Ui::configBox *ui;
};

#endif // CONFIGBOX_H
