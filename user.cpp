#include "user.h"
#include "ui_user.h"
#include "qsteeing.h"
#include "specifications.h"
#include <qDebug>
#include <QRadioButton>

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

void user::on_spec_Btn_clicked()
{
    //创建窗口
    specifications *s = new specifications(this);

    //设置窗口大小
    int w=400;
    int h=500;
    s->setFixedSize(w,h);

    //添加图片
    QLabel *picture = new QLabel(s);
    picture->setPixmap(QPixmap(":/image/Resources/1.jpg"));
    picture->setScaledContents(true);
    picture->resize(400,150);
    picture->move(0,0);


    //添加标题
    QLabel *title = new QLabel(s);
    title->setText("超解辣杨梅栋");
    title->move(w/2-title->size().width()/2,picture->geometry().y()+picture->size().height()+20);  //居中处理

    //添加描述
    QLabel *describe = new  QLabel(s);
    describe->setText("[费大厨]认证，超解辣。优选当季杨梅，精细去核，冰爽爆汁。"
                      "哈哈哈哈哈哈哈哈哈哈或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或或");
    describe->setWordWrap(true);  //自动换行
    describe->setFixedWidth(w-50);
    describe->adjustSize();  //自动调节高度
    describe->move(20,title->geometry().y()+title->size().height());

    //添加选项，冰量
    int bingpos_h=describe->geometry().y()+describe->size().height()+20;
    QLabel *bing = new QLabel(s);
    bing->setText("冰量");
    bing->move(20,bingpos_h);
    QRadioButton *rb1 = new QRadioButton(s);
    QRadioButton *rb2 = new QRadioButton(s);
    QRadioButton *rb3 = new QRadioButton(s);
    rb1->setText("正常(推荐)");
    rb2->setText("少冰");
    rb3->setText("少少冰");
    rb1->move(20,bingpos_h+15);
    rb2->move(rb1->geometry().x()+rb1->width()+20,bingpos_h+15);
    rb3->move(rb2->geometry().x()+rb2->width()+20,bingpos_h+15);

    //添加选项，甜度
    int tianpos_h=rb3->geometry().y()+rb3->size().height()+15;
    QLabel *tian = new QLabel(s);
    tian->setText("甜度");
    tian->move(20,tianpos_h);
    QRadioButton *rb4 = new QRadioButton(s);
    QRadioButton *rb5 = new QRadioButton(s);
    QRadioButton *rb6 = new QRadioButton(s);
    rb4->setText("标准甜(推荐)");
    rb5->setText("少甜");
    rb6->setText("少少甜");
    rb4->move(20,tianpos_h+15);
    rb5->move(rb4->geometry().x()+rb4->width()+20,tianpos_h+15);
    rb6->move(rb5->geometry().x()+rb5->width()+20,tianpos_h+15);

    //添加选项，杯型
    int beipos_h=rb6->geometry().y()+rb6->size().height()+15;
    QLabel *bei = new QLabel(s);
    bei->setText("杯型");
    bei->move(20,beipos_h);
    QRadioButton *rb7 = new QRadioButton(s);
    QRadioButton *rb8 = new QRadioButton(s);
    QRadioButton *rb9 = new QRadioButton(s);
    rb7->setText("大杯(推荐)");
    rb8->setText("中杯");
    rb9->setText("小杯");
    rb7->move(20,beipos_h+15);
    rb8->move(rb7->geometry().x()+rb7->width()+20,beipos_h+15);
    rb9->move(rb8->geometry().x()+rb8->width()+20,beipos_h+15);

    //单选按钮分组
    QButtonGroup  *bg1 = new QButtonGroup(s);
    QButtonGroup  *bg2 = new QButtonGroup(s);
    QButtonGroup  *bg3 = new QButtonGroup(s);
    bg1->addButton(rb1);
    bg1->addButton(rb2);
    bg1->addButton(rb3);
    bg2->addButton(rb4);
    bg2->addButton(rb5);
    bg2->addButton(rb6);
    bg3->addButton(rb7);
    bg3->addButton(rb8);
    bg3->addButton(rb9);

    //添加按钮，加入购物车
    QPushButton *cart = new QPushButton(s);
    cart->setFixedSize(400,50);
    cart->setText("￥18 加入购物袋");
    cart->move(0,s->size().height()-50);

    //显示窗口
    s->show();
}
