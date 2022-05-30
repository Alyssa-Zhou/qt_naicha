#include "user.h"
#include "ui_user.h"
#include "qsteeing.h"

user::user(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);

    ui->tabWidget->tabBar()->setStyle(new QSteeing);
}

user::~user()
{
    delete ui;
}
