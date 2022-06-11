#ifndef USER_H
#define USER_H

#include <QMainWindow>
#include "specifications.h"
#include "sql.h"
#include "mainwindow.h"
#include <QButtonGroup>

namespace Ui { class user; }

class userWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit userWindow(QWidget *parent = 0);
    ~userWindow();

        void closeEvent(QCloseEvent *event);

private slots:
    void on_spec_Btn_clicked(Goods *good);
    void pushcart(Goods *good, int i);

private:
    void fixedOptions(specifications *s, int y, int h);
    void init();
    Ui::user *ui;
    MainWindow *ptr = NULL;
    QButtonGroup *bgCup;
    QButtonGroup *bgTem;
    QButtonGroup *bgSweet;
    QButtonGroup *bgAddi;
    int index = 0;
    void checkout();

};

#endif // USER_H
