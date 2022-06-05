#include "mainwindow.h"
#include "manager.h"
#include "userWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->password_lineEdit->setEchoMode(QLineEdit::Password);    // 密码方式显示文本
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_logging_Btn_clicked(){
    //合法性检测
    if((ui->name_lineEdit->text() == "") || (ui->password_lineEdit->text() == "")){
        QMessageBox::information(this, tr("警告"), tr("输入不能为空！"), QMessageBox::Ok);
        return;
    }

    //用户名密码匹配
    QString name= ui->name_lineEdit->text();
    QString password=ui->password_lineEdit->text();

    //管理者界面
    if(name == "admin" && password == "admin"){
        this->hide();
        manager *m = new manager(this);
        m->show();
        return;
    }

    // 登陆
    this->sql.query = new QSqlQuery;
    QString str = QString("select * from UserTbl where name = '%1' and Upassword = '%2'").arg(name, password);
    this->sql.query->exec(str);
    if(!this->sql.query->first()){
        QMessageBox::information(this, tr("错误"), tr("登陆失败！"), QMessageBox::Ok);
        return;
    }

    this->usr.name = name;
    this->usr.password = password;
    this->usr.phone = this->sql.query->value(2).toString();

    //用户界面
    this->hide();
    userWindow *u =new userWindow(this);
    u->show();
}

void MainWindow::on_exit_Btn_clicked(){
    this->close();
}
