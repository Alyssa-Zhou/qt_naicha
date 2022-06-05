#include "manager.h"
#include "ui_manager.h"
#include <qsqltablemodel.h>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QTextEdit>

manager::manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::manager)
{

    ui->setupUi(this);

    this->ptr=(MainWindow*)parentWidget();
    this->ptr->sql.selectGoods("",NULL,0,100);

    this->InitComboBox();

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

manager::~manager()
{
    delete ui;
}
//搜索商品
void manager::on_btn_search_clicked()
{
    //search in database
    QString curRow=ui->cb_selectRow->currentText();//
    QString relationship=ui->cb_selectRel->currentText();
    QString key=ui->keyWord->text();
    //组成sql语句查找
    qDebug()<<"search:"<<curRow<<relationship<<key;

    //！！查询结果有点问题
    if(curRow=="商品名称") ptr->sql.selectGoods(key,NULL,0,1000);
    if(curRow=="商品编号ID") ptr->sql.selectGoods("",key.toInt(),0,1000);
    if(curRow=="商品价格"){
        if(relationship=="等于") ptr->sql.selectGoods("",NULL,key.toInt(),key.toInt());
        if(relationship=="小于") ptr->sql.selectGoods("",NULL,0,key.toInt());
        if(relationship=="大于") ptr->sql.selectGoods("",NULL,key.toInt(),10000);
    }
    if(curRow=="") ptr->sql.selectGoods("",NULL,0,10000);

    ui->tableView->setModel(ptr->sql.model);
}

//初始化下拉选择框
void manager::InitComboBox(){
    ui->cb_selectRow->addItem("商品名称");
    ui->cb_selectRow->addItem("商品编号ID");
    ui->cb_selectRow->addItem("商品价格");

    ui->cb_selectRel->addItem("等于");
    ui->cb_selectRel->addItem("小于");
    ui->cb_selectRel->addItem("大于");
}

void manager::on_btn_fresh_clicked()
{
    ptr->sql.selectUser("");
}

//增加商品
void manager::on_btn_add_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("上架奶茶："));
    // Value1
    QString value1 = QString("名称: ");
    QLineEdit *input1 = new QLineEdit(&dialog);
    form.addRow(value1, input1);
    // Value2
    QString value2 = QString("ID: ");
    QLineEdit *input2 = new QLineEdit(&dialog);
    form.addRow(value2, input2);

    QString value3 = QString("价格: ");
    QLineEdit *input3 = new QLineEdit(&dialog);
    form.addRow(value3, input3);

    QString value4 = QString("描述: ");
    QTextEdit *input4 = new QTextEdit(&dialog);
    form.addRow(value4, input4);

    QString value5 = QString("图片：");
    QLineEdit *input5 = new QLineEdit(&dialog);
    form.addRow(value5, input5);

    // Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Process when OK button is clicked
    if (dialog.exec() == QDialog::Accepted) {
        Goods g1(input1->text(),input2->text().toInt(),input3->text().toInt(),input4->toPlainText(),input5->text());
        ptr->sql.addGoods(&g1);
        ptr->sql.selectGoods("",NULL,0,10000);
        ui->tableView->setModel(ptr->sql.model);
        qDebug()<<"新增商品:"<<input1->text()<<input2->text()<<input3->text()<<input4->toPlainText()<<input5->text();
    }

}
//删除商品
void manager::on_btn_delete_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("请输入想要删除的商品ID："));
    // Value1
    QString value1 = QString("商品ID: ");
    QLineEdit *input1 = new QLineEdit(&dialog);
    form.addRow(value1, input1);

    // Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted){
        qDebug()<<"删除商品:"<<input1->text();
        ptr->sql.deleteGoods(input1->text().toInt());
        ptr->sql.selectGoods("",NULL,0,10000);
        ui->tableView->setModel(ptr->sql.model);
    }
}
//修改【未完成】
void manager::on_tableView_doubleClicked(const QModelIndex &index)
{
    //QString val = ptr->sql.model->data(index).toString();

//    qDebug()<<"新增商品:"<<index<<index.row()<<ptr->sql.model->data(index).toString();

}

void manager::on_tableView_entered(const QModelIndex &index)
{
    QString val = ptr->sql.model->data(index).toString();
    qDebug()<<"新增商品:"<<val;
}

//搜索订单
void manager::on_bt_search2_clicked()
{
    //search in database
    QString maxDate=ui->maxDate->text();//
    QString minDate=ui->minDate->text();
    QString key=ui->keyWord2->text();
    //组成sql语句查找
    qDebug()<<"search:"<<maxDate<<minDate<<key;

    //！！查询结果有点问题
    ptr->sql.selectOrder(minDate,maxDate,key);
    ui->tableView_2->setModel(ptr->sql.model2);
}
//新增订单
void manager::on_btn_add2_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("添加订单："));
    // Value1
    QString value1 = QString("ID: ");
    QLineEdit *input1 = new QLineEdit(&dialog);
    form.addRow(value1, input1);
    // Value2
    QString value2 = QString("用户名: ");
    QLineEdit *input2 = new QLineEdit(&dialog);
    form.addRow(value2, input2);

    QString value3 = QString("日期: ");
    QLineEdit *input3 = new QLineEdit(&dialog);
    form.addRow(value3, input3);

    QString value4 = QString("时间: ");
    QLineEdit *input4 = new QLineEdit(&dialog);
    form.addRow(value4, input4);

    QString value5 = QString("商品ID：");
    QLineEdit *input5 = new QLineEdit(&dialog);
    form.addRow(value5, input5);

    QString value6 = QString("杯型：");
    QLineEdit *input6 = new QLineEdit(&dialog);
    form.addRow(value6, input6);

    QString value7 = QString("温度：");
    QLineEdit *input7 = new QLineEdit(&dialog);
    form.addRow(value7, input7);

    QString value8 = QString("甜度：");
    QLineEdit *input8 = new QLineEdit(&dialog);
    form.addRow(value8, input8);

    QString value9 = QString("备注：");
    QLineEdit *input9 = new QLineEdit(&dialog);
    form.addRow(value9, input9);

    QString value10 = QString("状态：");
    QLineEdit *input10 = new QLineEdit(&dialog);
    form.addRow(value10, input10);
    // Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Process when OK button is clicked
    if (dialog.exec() == QDialog::Accepted) {
        Order o1(input1->text().toInt(),input2->text(),input3->text(),input4->text(),input5->text().toInt()
                 ,input6->text(),input7->text(),input8->text(),input9->text(),input10->text());
        ptr->sql.addOrder(&o1);
        ptr->sql.selectOrder("","","");
        ui->tableView_2->setModel(ptr->sql.model2);
    }
}
//删除订单
void manager::on_btn_selete2_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("请输入想要删除的订单ID："));
    // Value1
    QString value1 = QString("订单ID: ");
    QLineEdit *input1 = new QLineEdit(&dialog);
    form.addRow(value1, input1);

    // Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted){
        qDebug()<<"删除订单:"<<input1->text();
        ptr->sql.deleteOrder(input1->text().toInt());
        ptr->sql.selectOrder("","","");
        ui->tableView_2->setModel(ptr->sql.model2);
    }
}
//搜索用户
void manager::on_bt_search2_2_clicked()
{

}


//新增用户
void manager::on_btn_add2_2_clicked()
{

}

//删除用户
void manager::on_btn_selete2_2_clicked()
{

}
