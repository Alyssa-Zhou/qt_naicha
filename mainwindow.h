#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QMessageBox>
#include <QDialog>
#include "sql.h"

namespace Ui { class MainWindow; }

// TODO: 新增注册用户界面，输入名称，密码，手机号，创建UserInfo对象并使用Sql::updateUser，如果用户已存在则报错

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Sql sql;                    // 数据库
    UserInfo usr;


private slots:
    void on_logging_Btn_clicked();
    void on_reg_Btn_clicked();
    void on_exit_Btn_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
