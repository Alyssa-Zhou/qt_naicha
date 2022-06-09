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

    void closeEvent(QCloseEvent *event);

private slots:
    // 搜索商品
    void on_btn_searchG_clicked();
    // 初始化下拉选项框
    void InitComboBox();
    // 增加商品
    void on_btn_addG_clicked();
    // 删除商品
    void on_btn_deleteG_clicked();
    // 双击表格
    //void on_tableView_doubleClicked(const QModelIndex &index);
    // 搜索订单
    void on_btn_searchO_clicked();
    // 增加订单
    void on_btn_addO_clicked();
    // 搜索用户
    void on_btn_searchU_clicked();
    // 删除订单
    void on_btn_deleteO_clicked();
    // 选择商品图片
    QString on_selectPicture_clicked();


private:
    Ui::manager *ui;
    MainWindow *ptr = NULL;
};

#endif // MANAGER_H
