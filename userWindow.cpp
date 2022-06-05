#include "userWindow.h"
#include "ui_user.h"
#include "qsteeing.h"
#include <QDebug>
#include <QRadioButton>
#include <QButtonGroup>

userWindow::userWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::user){
    ui->setupUi(this);
    ui->tabWidget->tabBar()->setStyle(new QSteeing);
}

userWindow::~userWindow(){
    delete ui;
}

// 所有商品固定的选型
void userWindow::fixedOptions(specifications *s, int y, int h){
    // 添加选项，杯型
    int cupPos_h = y + h + 20;
    QLabel *cupLabel = new QLabel("甜度", s);
    cupLabel->move(20, cupPos_h);
    QRadioButton *rbCup1 = new QRadioButton("中杯(推荐)", s);
    QRadioButton *rbCup2 = new QRadioButton("大杯", s);
    QRadioButton *rbCup3 = new QRadioButton("超大杯", s);
    rbCup1->move(20, cupPos_h + 15);
    rbCup2->move(rbCup1->x() + rbCup1->width() + 20, cupPos_h + 15);
    rbCup3->move(rbCup2->x() + rbCup2->width() + 20, cupPos_h + 15);
    QButtonGroup *bgCup = new QButtonGroup(s);
    bgCup->addButton(rbCup1);
    bgCup->addButton(rbCup2);
    bgCup->addButton(rbCup3);

    // 添加选项，温度(冰量)
    int temPos_h = rbCup3->y() + rbCup3->height() + 15;
    QLabel *temLabel = new QLabel("温度", s);
    temLabel->move(20, temPos_h);
    QRadioButton *rbTem1 = new QRadioButton("正常冰(推荐)", s);
    QRadioButton *rbTem2 = new QRadioButton("少冰", s);
    QRadioButton *rbTem3 = new QRadioButton("去冰", s);
    QRadioButton *rbTem4 = new QRadioButton("常温", s);
    QRadioButton *rbTem5 = new QRadioButton("热", s);
    rbTem1->move(20, temPos_h + 15);
    rbTem2->move(rbTem1->x() + rbTem1->width() + 20, temPos_h + 15);
    rbTem3->move(rbTem2->x() + rbTem2->width() + 20, temPos_h + 15);
    rbTem4->move(rbTem3->x() + rbTem3->width() + 20, temPos_h + 15);
    rbTem5->move(rbTem4->x() + rbTem4->width() + 20, temPos_h + 15);
    QButtonGroup *bgTem = new QButtonGroup(s);
    bgTem->addButton(rbTem1);
    bgTem->addButton(rbTem2);
    bgTem->addButton(rbTem3);
    bgTem->addButton(rbTem4);
    bgTem->addButton(rbTem5);

    // 添加选项，甜度
    int sweetPos_h = rbTem5->y() + rbTem5->height() + 15;
    QLabel *sweetLabel = new QLabel("甜度", s);
    sweetLabel->move(20, sweetPos_h);
    QRadioButton *rbSweet1 = new QRadioButton("标准糖(推荐)", s);
    QRadioButton *rbSweet2 = new QRadioButton("七分糖", s);
    QRadioButton *rbSweet3 = new QRadioButton("半糖", s);
    QRadioButton *rbSweet4 = new QRadioButton("三分糖", s);
    QRadioButton *rbSweet5 = new QRadioButton("零糖", s);
    rbSweet1->move(20, sweetPos_h + 15);
    rbSweet2->move(rbSweet1->x() + rbSweet1->width() + 20, sweetPos_h + 15);
    rbSweet3->move(rbSweet2->x() + rbSweet2->width() + 20, sweetPos_h + 15);
    rbSweet4->move(rbSweet3->x() + rbSweet3->width() + 20, sweetPos_h + 15);
    rbSweet5->move(rbSweet4->x() + rbSweet4->width() + 20, sweetPos_h + 15);
    QButtonGroup *bgSweet = new QButtonGroup(s);
    bgSweet->addButton(rbSweet1);
    bgSweet->addButton(rbSweet2);
    bgSweet->addButton(rbSweet3);
    bgSweet->addButton(rbSweet4);
    bgSweet->addButton(rbSweet5);

    // 添加选项，配料
    int addiPos_h = rbSweet5->y() + rbSweet5->height() + 15;
    QLabel *addiLabel = new QLabel("配料", s);
    addiLabel->move(20, addiPos_h);
    QRadioButton *rbAddi1 = new QRadioButton("珍珠", s);
    QRadioButton *rbAddi2 = new QRadioButton("椰果", s);
    QRadioButton *rbAddi3 = new QRadioButton("西米", s);
    QRadioButton *rbAddi4 = new QRadioButton("芋圆", s);
    rbAddi1->move(20, addiPos_h + 15);
    rbAddi2->move(rbAddi1->x() + rbAddi1->width() + 20, addiPos_h + 15);
    rbAddi3->move(rbAddi2->x() + rbAddi2->width() + 20, addiPos_h + 15);
    rbAddi4->move(rbAddi3->x() + rbAddi3->width() + 20, addiPos_h + 15);
<<<<<<< Updated upstream
=======
    QButtonGroup *bgAddi = new QButtonGroup(s);
    bgAddi->addButton(rbAddi1);
    bgAddi->addButton(rbAddi2);
    bgAddi->addButton(rbAddi3);
    bgAddi->addButton(rbAddi4);
>>>>>>> Stashed changes
}

void userWindow::on_spec_Btn_clicked(Goods *good){
    // 创建窗口
    specifications *s = new specifications(this);

    // 设置窗口大小
    int w = 400, h = 500;
    s->setFixedSize(w, h);

    // 添加图片
    QLabel *picture = new QLabel(s);
    picture->setPixmap(QPixmap(good->photoPath));
    picture->setScaledContents(true);
    picture->resize(400, 150);
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
    QPushButton *cart = new QPushButton(s);
    cart->setText(QString("￥%1 加入购物袋").arg(good->price));
    cart->setFixedSize(400, 50);
    cart->move(0, s->height() - 50);

    // 固定选项
    fixedOptions(s, describe->y(), describe->height());

    // 显示窗口
    s->show();
}
