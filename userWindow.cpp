#include "userWindow.h"
#include "ui_user.h"
#include "qsteeing.h"
#include <QDebug>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QScrollArea>
#include <QDate>
#include <QTime>

// 商品选项
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, cupSizeOpt, ({"medium", "large", "x-large"}));
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, temOpt, ({"ice", "few-ice", "drop-ice", "warm", "hot"}));
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, sweetOpt, ({"normal", "seven", "half", "three", "zero"}));
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, addiOpt, ({"pearls", "coconut", "sago", "taro"}));
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, cupSizeOptCN, ({"中杯", "大杯", "超大杯"}));
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, temOptCN, ({"正常冰", "少冰", "去冰", "常温", "热"}));
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, sweetOptCN, ({"标准糖", "七分糖", "半塘", "三分糖", "零糖"}));
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, addiOptCN, ({"珍珠", "椰果", "西米", "芋圆"}));

userWindow::userWindow(UserInfo usr, QWidget *parent) : QMainWindow(parent), ui(new Ui::user){
    ui->setupUi(this);
    ui->tabWidget->tabBar()->setStyle(new QSteeing);

    this->usr.name = usr.name;
    this->usr.password = usr.password;
    this->usr.phone = usr.phone;

    this->ptr = (MainWindow*)parentWidget();
    this->cart = ui->scrollAreaWidgetContents_2;
    this->init();
}

userWindow::~userWindow(){
    delete ui;
}

void userWindow::init(){
    QWidget *sawc = ui->scrollAreaWidgetContents;
    int pos_x = sawc->geometry().x()+10;
    int pos_y = sawc->geometry().y()+10;
    int pic_size =75;

    for (int i=1; i <= ptr->sql.countGoods(); i++){
        QLabel *title = new QLabel(ptr->sql.findGood(i)->name, sawc);
        title->move(pic_size + 20, pos_y + (i-1)*80);

        QLabel *introduction = new QLabel(ptr->sql.findGood(i)->introduction, sawc);
        introduction->resize(200, introduction->size().height());
        introduction->setWordWrap(true);
        introduction->setAlignment(Qt::AlignTop);
        introduction->move(pic_size + 20,pos_y + 15 + (i-1)*80);

        QLabel *price = new QLabel("¥ " + QString::number(ptr->sql.findGood(i)->price), sawc);
        price->move(pic_size + 20, pos_y + 60 + (i-1)*80);

        QLabel *picture = new QLabel(sawc);
        picture->setPixmap(QPixmap(ptr->sql.findGood(i)->photoPath));
        picture->setScaledContents(true);
        picture->resize(pic_size, pic_size);
        picture->move(pos_x, pos_y + (i-1)*80);

        QPushButton *spec_Btn = new QPushButton("选规格", sawc);
        connect(spec_Btn, &QPushButton::clicked, this, [=](){on_spec_Btn_clicked(ptr->sql.findGood(i));});
        spec_Btn->move(200, pos_y + 50 + (i-1)*80);
    }
}

// NOTE: 原来ButtonGroup的ID是从1开始的，后面读数组从0开始，现已将ID修改为从0开始
// NOTE: 常规选项增加了默认选中
// 所有商品固定的选型
void userWindow::fixedOptions(specifications *s, int y, int h){
    int rowSep = 20, colSep = 15;

    // 添加选项，杯型
    int cupPos_h = y + h + rowSep;
    QLabel *cupLabel = new QLabel("杯型", s);
    cupLabel->move(rowSep, cupPos_h);
    QRadioButton *rbCup1 = new QRadioButton("中杯(推荐)", s);
    QRadioButton *rbCup2 = new QRadioButton("大杯", s);
    QRadioButton *rbCup3 = new QRadioButton("超大杯", s);
    rbCup1->move(rowSep, cupPos_h + colSep);
    rbCup2->move(rbCup1->x() + rbCup1->width() + rowSep, cupPos_h + colSep);
    rbCup3->move(rbCup2->x() + rbCup2->width() + rowSep, cupPos_h + colSep);

    bgCup = new QButtonGroup(s);
    bgCup->addButton(rbCup1, 0);
    bgCup->addButton(rbCup2, 1);
    bgCup->addButton(rbCup3, 2);
    rbCup1->setChecked(true);   // 默认选中1

    // 添加选项，温度(冰量)
    int temPos_h = rbCup3->y() + rbCup3->height() + colSep;
    QLabel *temLabel = new QLabel("温度", s);
    temLabel->move(rowSep, temPos_h);
    QRadioButton *rbTem1 = new QRadioButton("正常冰(推荐)", s);
    QRadioButton *rbTem2 = new QRadioButton("少冰", s);
    QRadioButton *rbTem3 = new QRadioButton("去冰", s);
    QRadioButton *rbTem4 = new QRadioButton("常温", s);
    QRadioButton *rbTem5 = new QRadioButton("热", s);
    rbTem1->move(rowSep, temPos_h + 15);
    rbTem2->move(rbTem1->x() + rbTem1->width() + rowSep, temPos_h + colSep);
    rbTem3->move(rbTem2->x() + rbTem2->width() + rowSep, temPos_h + colSep);
    rbTem4->move(rbTem3->x() + rbTem3->width() + rowSep, temPos_h + colSep);
    rbTem5->move(rbTem4->x() + rbTem4->width() + rowSep, temPos_h + colSep);

    bgTem = new QButtonGroup(s);
    bgTem->addButton(rbTem1, 0);
    bgTem->addButton(rbTem2, 1);
    bgTem->addButton(rbTem3, 2);
    bgTem->addButton(rbTem4, 3);
    bgTem->addButton(rbTem5, 4);
    rbTem1->setChecked(true);   // 默认选中1

    // 添加选项，甜度
    int sweetPos_h = rbTem5->y() + rbTem5->height() + colSep;
    QLabel *sweetLabel = new QLabel("甜度", s);
    sweetLabel->move(rowSep, sweetPos_h);
    QRadioButton *rbSweet1 = new QRadioButton("标准糖(推荐)", s);
    QRadioButton *rbSweet2 = new QRadioButton("七分糖", s);
    QRadioButton *rbSweet3 = new QRadioButton("半糖", s);
    QRadioButton *rbSweet4 = new QRadioButton("三分糖", s);
    QRadioButton *rbSweet5 = new QRadioButton("零糖", s);
    rbSweet1->move(rowSep, sweetPos_h + colSep);
    rbSweet2->move(rbSweet1->x() + rbSweet1->width() + rowSep, sweetPos_h + colSep);
    rbSweet3->move(rbSweet2->x() + rbSweet2->width() + rowSep, sweetPos_h + colSep);
    rbSweet4->move(rbSweet3->x() + rbSweet3->width() + rowSep, sweetPos_h + colSep);
    rbSweet5->move(rbSweet4->x() + rbSweet4->width() + rowSep, sweetPos_h + colSep);

    bgSweet = new QButtonGroup(s);
    bgSweet->addButton(rbSweet1, 0);
    bgSweet->addButton(rbSweet2, 1);
    bgSweet->addButton(rbSweet3, 2);
    bgSweet->addButton(rbSweet4, 3);
    bgSweet->addButton(rbSweet5, 4);
    rbSweet1->setChecked(true); // 默认选中1

    // 添加选项，配料
    int addiPos_h = rbSweet5->y() + rbSweet5->height() + colSep;
    QLabel *addiLabel = new QLabel("配料", s);
    addiLabel->move(rowSep, addiPos_h);
    QCheckBox *cbAddi1 = new QCheckBox("珍珠", s);
    QCheckBox *cbAddi2 = new QCheckBox("椰果", s);
    QCheckBox *cbAddi3 = new QCheckBox("西米", s);
    QCheckBox *cbAddi4 = new QCheckBox("芋圆", s);
    cbAddi1->move(rowSep, addiPos_h + colSep);
    cbAddi2->move(cbAddi1->x() + cbAddi1->width() + rowSep, addiPos_h + colSep);
    cbAddi3->move(cbAddi2->x() + cbAddi2->width() + rowSep, addiPos_h + colSep);
    cbAddi4->move(cbAddi3->x() + cbAddi3->width() + rowSep, addiPos_h + colSep);

    bgAddi = new QButtonGroup(s);
    bgAddi->setExclusive(false);        // 设置互斥模式为false
    bgAddi->addButton(cbAddi1, 0);
    bgAddi->addButton(cbAddi2, 1);
    bgAddi->addButton(cbAddi3, 2);
    bgAddi->addButton(cbAddi4, 3);
}

void userWindow::on_spec_Btn_clicked(Goods *good){
    // 创建窗口
    specifications *s = new specifications(this);

    // 设置窗口大小
    int w = 550, h = 650;
    s->setFixedSize(w, h);

    // 添加图片
    QLabel *picture = new QLabel(s);
    picture->setPixmap(QPixmap(good->photoPath));
    picture->setScaledContents(true);
    picture->resize(w, 250);
    picture->move(0,0);

    // 添加标题
    QLabel *title = new QLabel(good->name, s);
    title->move(w/2 - title->width()/2, picture->y() + picture->height() + 20);  //居中处理

    // 添加描述
    QLabel *describe = new QLabel(good->introduction, s);
    describe->setWordWrap(true);        // 自动换行
    describe->setFixedWidth(w - 50);    // 固定宽度
    describe->adjustSize();             // 自动调节高度
    describe->move(20, title->y() + title->height());

    // 添加按钮，加入购物车
    QPushButton *cartBtn = new QPushButton(QString("￥%1 加入购物袋").arg(good->price), s);
    cartBtn->setFixedSize(w, 50);
    cartBtn->move(0, s->height() - 50);
    // 加入购物车并关闭选项窗口
    connect(cartBtn, &QPushButton::clicked, this, [=](){pushcart(good); s->close();});

    // 固定选项
    fixedOptions(s, describe->y(), describe->height());

    // 显示窗口
    s->show();
}

// NOTE: 由于常规选项有默认选项，无需对其合法性检测
// 购物车
void userWindow::pushcart(Goods *good){
    orders.append(getOrder(good));
    QMessageBox::information(this, tr("提示 "), tr("已加入购物车"), QMessageBox::Ok);   // 提示界面

    // 几何参数设置
    int picSize = 75, picSep = 10;                  // 图片尺寸， 图片边缘的间隙
    int leftPic = cart->x() + picSep, upPic = cart->y() + picSep + 80 * (orders.length() - 1); // 图片左部和上部位置
    int leftText = leftPic + picSize + picSep;      // 文本左部位置

    // 加载图片
    QLabel *picture = new QLabel(cart);
    picture->setPixmap(QPixmap(good->photoPath));
    picture->setScaledContents(true);
    picture->resize(picSize, picSize);
    picture->move(leftPic, upPic);

    // 显示商品名和价格
    QLabel *title = new QLabel(good->name, cart);
    QLabel *price = new QLabel("¥ " + QString::number(good->price), cart);
    title->move(leftText, upPic);
    price->move(leftText, upPic + 60);

    // 商品常规选项
    QString normalOptText = cupSizeOptCN->value(bgCup->checkedId()) + "、" +
            temOptCN->value(bgTem->checkedId()) + "、" + sweetOptCN->value(bgSweet->checkedId());
    QLabel *normalOptLbl = new QLabel(normalOptText, cart);
    normalOptLbl->move(leftText, upPic + 20);

    // 商品配料选项
    QString addOptText = "配料：";
    if(bgAddi->checkedId() == -1)  addOptText += "无";
    else{
        for(int i = 0; i < bgAddi->checkedId(); i++)
            if(bgAddi->button(i)->isChecked()) addOptText += (addiOptCN->value(i) + "、");
        addOptText += addiOptCN->value(bgAddi->checkedId());
    }
    QLabel *addOptLbl = new QLabel(addOptText, cart);
    addOptLbl->move(leftText, upPic + 40);
}

// 由商品和选项生成订单
Order userWindow::getOrder(Goods *good){
    QString date = QDate::currentDate().toString("yyyy-MM-dd"); // 获取当前日期
    QString t = QTime::currentTime().toString("hh:mm:ss");      // 获取当前时间
    QString addOpt = "";    // 配料
    if(bgAddi->checkedId() != -1){
        for(int i = 0; i < bgAddi->checkedId(); i++)
            if(bgAddi->button(i)->isChecked()) addOpt += (addiOpt->value(i) + ", ");
        addOpt += addiOpt->value(bgAddi->checkedId());
    }
    return Order(usr.name, good->name, date, t, cupSizeOpt->value(bgCup->checkedId()),
                 temOpt->value(bgTem->checkedId()), sweetOpt->value(bgSweet->checkedId()),
                 addOpt, "making");
}

// 结账
void userWindow::on_checkout_Btn_clicked(){
    foreach(Order order, orders) ptr->sql.addOrder(&order);         // 数据库添加订单
    orders.clear();                                                 // 清空订单表
    foreach(QLabel* btn, cart->findChildren<QLabel*>()) delete btn; // 清空购物车界面
    QMessageBox::information(this, tr("提示 "), tr("已购买"), QMessageBox::Ok);  // 提示界面
}

void userWindow::closeEvent(QCloseEvent *event){
    Q_UNUSED(event);
    this->hide();
    this->parentWidget()->show();
}

