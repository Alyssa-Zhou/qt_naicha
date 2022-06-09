#ifndef ENROLL_H
#define ENROLL_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class enroll;
}

class enroll : public QDialog
{
    Q_OBJECT

public:
    explicit enroll(QWidget *parent = 0);
    ~enroll();

private slots:
    void on_ok_Btn_clicked();

private:
    Ui::enroll *ui;
    MainWindow *ptr = NULL;
};

#endif // ENROLL_H
