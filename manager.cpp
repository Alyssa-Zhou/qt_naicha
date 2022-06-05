#include "manager.h"
#include "ui_manager.h"

manager::manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::manager)
{
    ui->setupUi(this);
}

manager::~manager()
{
    delete ui;
}

void manager::on_btn_search_clicked()
{
    //search in database
    QString curRow=ui->cb_selectRow->currentText();//
    QString relationship=ui->cb_selectRel->currentText();
    QString key=ui->keyWord->text();
    //组成sql语句查找


}
