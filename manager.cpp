#include "manager.h"
#include "ui_manager.h"
#include <qsqltablemodel.h>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QTextEdit>
#include <QFileDialog>

manager::manager(QWidget* parent) : QMainWindow(parent), ui(new Ui::manager) {
    ui->setupUi(this);
    this->ptr = (MainWindow*)parentWidget();
    this->ptr->sql.selectGoods("", (int)NULL, 0, 100);
    this->InitComboBox();

    //表格列宽自适应
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

manager::~manager() { delete ui; }

//搜索商品
void manager::on_btn_searchG_clicked()
{
    //search in database
    QString curRow = ui->cb_selectRow->currentText();//
    QString relationship = ui->cb_selectRel->currentText();
    QString key = ui->keyWord->text();
    //组成sql语句查找
    qDebug() << "search:" << curRow << relationship << key;

    // NOTE: bug已修复
    if(key == "" || curRow == "") ptr->sql.selectGoods();   // 如果没输入内容，就显示所有商品
    else if (curRow == "商品名称") ptr->sql.selectGoods(key);
    else if (curRow == "商品编号ID") ptr->sql.selectGoods("", key.toInt());
    else if (curRow == "商品价格") {
        if (relationship == "等于") ptr->sql.selectGoods("", (int)NULL, key.toInt(), key.toInt());
        if (relationship == "小于") ptr->sql.selectGoods("", (int)NULL, 0, key.toInt());
        if (relationship == "大于") ptr->sql.selectGoods("", (int)NULL, key.toInt(), 10000);
    }

    ui->tableView->setModel(ptr->sql.model);
}

//初始化下拉选择框
void manager::InitComboBox() {
    ui->cb_selectRow->addItem("商品名称");
    ui->cb_selectRow->addItem("商品编号ID");
    ui->cb_selectRow->addItem("商品价格");

    ui->cb_selectRel->addItem("等于");
    ui->cb_selectRel->addItem("小于");
    ui->cb_selectRel->addItem("大于");
}

//增加商品
void manager::on_btn_addG_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("上架奶茶："));
    // Value1
    QString value1 = QString("名称: ");
    QLineEdit* input1 = new QLineEdit(&dialog);
    form.addRow(value1, input1);

    QString value3 = QString("价格: ");
    QLineEdit* input3 = new QLineEdit(&dialog);
    form.addRow(value3, input3);

    QString value4 = QString("描述: ");
    QTextEdit* input4 = new QTextEdit(&dialog);
    form.addRow(value4, input4);

    QString value5 = QString("图片：");
    QPushButton *selectPicture = new QPushButton("选择",&dialog);
    QString filePath="";
    connect(selectPicture, &QPushButton::clicked, [&](){
        filePath=on_selectPicture_clicked();
        selectPicture->setText(filePath);       //按钮文字设为当前路径
    });
    form.addRow(value5, selectPicture);

    // Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Process when OK button is clicked
    if (dialog.exec() == QDialog::Accepted) {
        Goods g1(input1->text(),input3->text().toInt(),input4->toPlainText(),filePath);
        ptr->sql.addGoods(&g1);
        ptr->sql.selectGoods("", (int)NULL, 0, 10000);
        ui->tableView->setModel(ptr->sql.model);
        qDebug()<<"新增商品:"<<input1->text()<<input3->text()<<input4->toPlainText()<<filePath;
    }

}

//删除商品
void manager::on_btn_deleteG_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("请输入想要删除的商品ID："));
    QString value1 = QString("商品ID: ");
    QLineEdit* input1 = new QLineEdit(&dialog);
    form.addRow(value1, input1);

    // Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "删除商品:" << input1->text();
        ptr->sql.deleteGoods(input1->text().toInt());
        ptr->sql.selectGoods("", (int)NULL, 0, 10000);
        ui->tableView->setModel(ptr->sql.model);
    }
}

//搜索订单
void manager::on_btn_searchO_clicked()
{
    //search in database
    QString maxDate = ui->maxDate->text();
    QString minDate = ui->minDate->text();
    QString key = ui->keyWord2->text();
    //组成sql语句查找
    qDebug() << "search:" << minDate << maxDate << key;

    // TODO: 显示界面(查询结果bug已修复)
    ptr->sql.selectOrder(key, minDate, maxDate);
    ui->tableView_2->setModel(ptr->sql.model1);
}

//新增订单
void manager::on_btn_addO_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("添加订单："));

    // Value2
    QString value2 = QString("用户名: ");
    QLineEdit* input2 = new QLineEdit(&dialog);
    form.addRow(value2, input2);

    QString value3 = QString("日期: ");
    QLineEdit* input3 = new QLineEdit(&dialog);
    form.addRow(value3, input3);

    QString value4 = QString("时间: ");
    QLineEdit* input4 = new QLineEdit(&dialog);
    form.addRow(value4, input4);

    QString value5 = QString("商品ID：");
    QLineEdit* input5 = new QLineEdit(&dialog);
    form.addRow(value5, input5);

    QString value6 = QString("杯型：");
    QComboBox* input6 = new QComboBox(&dialog);
    QStringList cupSize;
    cupSize << "medium" << "large" << "x-large";
    input6->addItems(cupSize);
    form.addRow(value6, input6);

    QString value7 = QString("温度：");
    QComboBox* input7 = new QComboBox(&dialog);
    QStringList tmp;
    tmp << "ice" << "few-ice" << "drop-ice" << "warm" << "hot";
    input7->addItems(tmp);
    form.addRow(value7, input7);

    QString value9 = QString("甜度：");
    QComboBox* input9 = new QComboBox(&dialog);
    QStringList swt;
    swt << "normal" << "seven" << "half" << "three" << "zero";
    input9->addItems(swt);
    form.addRow(value9, input9);

    QString value8 = QString("加料：");
    QComboBox* input8 = new QComboBox(&dialog);
    QStringList ad;
    ad << "pearls" << "coconut" << "sago" << "taro";
    input8->addItems(ad);
    form.addRow(value8, input8);

    // Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Process when OK button is clicked
    if (dialog.exec() == QDialog::Accepted) {
        qDebug()<<"add Order:"<<input2->text()<< input3->text()<< input4->text()<< input5->text()
                << input6->currentText()<< input7->currentText()<< input8->currentText()<<input9->currentText()<<QString("making");
        Order o1(input2->text(), input3->text(), input4->text(), input5->text().toInt()
            , input6->currentText(), input7->currentText(), input8->currentText(), input9->currentText(), QString("making"));
        if(ptr->sql.addOrder(&o1)) qDebug()<<"出错了！";
        ptr->sql.selectOrder("", "", "");
        ui->tableView_2->setModel(ptr->sql.model1);
    }
}
//删除订单
void manager::on_btn_deleteO_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("请输入想要删除的订单ID："));
    QString value1 = QString("订单ID: ");
    QLineEdit* input1 = new QLineEdit(&dialog);
    form.addRow(value1, input1);

    // Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "删除订单:" << input1->text();
        ptr->sql.deleteOrder(input1->text().toInt());
        ptr->sql.selectOrder("", "", "");
        ui->tableView_2->setModel(ptr->sql.model1);
    }
}

//搜索用户
void manager::on_btn_searchU_clicked()
{
    //search in database
    QString key = ui->keyWord3->text();
    //组成sql语句查找
    qDebug() << "search:" << key;

    ptr->sql.selectUser(key);
    ui->tableView_3->setModel(ptr->sql.model2);
}
//关闭窗口回调
void manager::closeEvent(QCloseEvent *event)
{
    this->hide();
    this->parentWidget()->show();
}
//选择商品图片按钮回调
QString manager::on_selectPicture_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this,tr("文件对话框！"),"F:",tr("图片文件(*png *jpg);;"));
    qDebug()<<"filename : "<<fileName;
    return fileName;
}
