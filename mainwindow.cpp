#include "mainwindow.h"
#include "manager.h"
#include "user.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //密码方式显示文本
    ui->password_lineEdit->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_logging_Btn_clicked()
{
    //合法性检测
    if((ui->name_lineEdit->text()=="")||(ui->password_lineEdit->text()==""))
    {
        QMessageBox::information(this,tr("警告"),tr("输入不能为空！"),QMessageBox::Ok);
        return;
    }

    //用户名密码匹配
    QString name= ui->name_lineEdit->text();
    QString passward=ui->password_lineEdit->text();

    //管理者界面
    if(name=="admin"&&passward=="admin")
    {
        this->hide();
        manager *m=new manager(this);
        m->show();
        return;
    }
    //用户界面
    else if(name=="123"&&passward=="123")
    {
        this->hide();
        user *u=new user(this);
        u->show();
        return;
    }
}

void MainWindow::on_exit_Btn_clicked()
{
    this->close();
}
