#include "enroll.h"
#include "ui_enroll.h"
#include "sql.h"
#include <QMessageBox>
#include <QDebug>

enroll::enroll(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::enroll)
{
    ui->setupUi(this);

    ui->LE_password->setEchoMode(QLineEdit::Password);    // 密码方式显示文本
    ui->LE_ensure->setEchoMode(QLineEdit::Password);    // 密码方式显示文本

    this->ptr=(MainWindow*)parentWidget();
}

enroll::~enroll()
{
    delete ui;
}

void enroll::on_ok_Btn_clicked()
{
    QString name = ui->LE_name->text();
    QString password = ui->LE_password->text();
    QString ensure = ui->LE_ensure->text();
    QString phone = ui->LE_phone->text();

    if(name == ""){
        QMessageBox::information(this, tr("警告"), tr("请输入用户名！"), QMessageBox::Ok);
        return;
    }
    else if(password == ""){
        QMessageBox::information(this, tr("警告"), tr("请输入密码！"), QMessageBox::Ok);
        return;
    }
    else if(ensure == ""){
        QMessageBox::information(this, tr("警告"), tr("请输入确认密码！"), QMessageBox::Ok);
        return;
    }
    else if(phone == ""){
        QMessageBox::information(this, tr("警告"), tr("请输入手机号！"), QMessageBox::Ok);
        return;
    }

    if(ptr->sql.findUser(name)){
        QMessageBox::information(this, tr("警告"), tr("用户名已存在，请重新输入！"), QMessageBox::Ok);
        ui->LE_name->setText("");
        return;
    }

    if(password != ensure){
        QMessageBox::information(this, tr("警告"), tr("密码不一致，请重新输入！"), QMessageBox::Ok);
        ui->LE_password->setText("");
        ui->LE_ensure->setText("");
        return;
    }

    UserInfo usr(name, password, phone);
    ptr->sql.addUser(&usr);

    QMessageBox::information(this, tr("提示"), tr("恭喜您，注册成功！"), QMessageBox::Ok);

    this->close();
}
