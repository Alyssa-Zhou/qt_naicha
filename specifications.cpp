#include "specifications.h"
#include "ui_specifications.h"
#include <QLabel>

specifications::specifications(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::specifications)
{
    ui->setupUi(this);
}

specifications::~specifications()
{
    delete ui;
}
