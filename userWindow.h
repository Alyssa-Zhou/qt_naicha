#ifndef USER_H
#define USER_H

#include <QMainWindow>
#include "specifications.h"
#include "sql.h"
#include "mainwindow.h"

namespace Ui { class user; }

class userWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit userWindow(QWidget *parent = 0);
    ~userWindow();

        void closeEvent(QCloseEvent *event);

private slots:
    void on_spec_Btn_clicked(Goods *good);

private:
    void fixedOptions(specifications *s, int y, int h);
    void init();
    Ui::user *ui;
    MainWindow *ptr = NULL;

};

#endif // USER_H
