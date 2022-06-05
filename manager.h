#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include "mainwindow.h"
#include "sql.h"

namespace Ui {
class manager;
}

class manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit manager(QWidget *parent = 0);
    ~manager();

private slots:
    void on_btn_search_clicked();
    void InitComboBox();

    void on_btn_fresh_clicked();

    void on_btn_add_clicked();

    void on_btn_delete_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableView_entered(const QModelIndex &index);

    void on_bt_search2_clicked();

    void on_btn_add2_clicked();

    void on_bt_search2_2_clicked();

    void on_btn_selete2_clicked();

    void on_btn_add2_2_clicked();

    void on_btn_selete2_2_clicked();

private:
    Ui::manager *ui;
    MainWindow *ptr = NULL;
};

#endif // MANAGER_H
