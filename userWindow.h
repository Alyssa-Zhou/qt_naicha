#ifndef USER_H
#define USER_H

#include <QMainWindow>
#include "specifications.h"
#include "sql.h"
#include "mainwindow.h"
#include <QButtonGroup>

namespace Ui { class user; }

// TODO: 初始化的时候，调用Sql::selectGoods显示商品概要信息，而不是一个个设置

// TODO: 建议取消购物车，因为这将导致一个Order内有多个商品和选项信息，相应的数据库比较麻烦。单个商品选好选项后直接购买
/* TODO: 增加选项被选择之后的回调，即用选项数据和商品数据建立Order对象，
   再传入Sql::updateOrder，建立成功后在页面内有相应窗口*/

class userWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit userWindow(QWidget *parent = 0);
    ~userWindow();

        void closeEvent(QCloseEvent *event);

private slots:
    // NOTE: 选择任何一个商品的“选项”按钮时，它的回调函数都是这个，只是传入的Goods不一样
    void on_spec_Btn_clicked(Goods *good);
    void pushcart(Goods *good, int i);

private:
    void fixedOptions(specifications *s, int y, int h);
    void init();
    Ui::user *ui;
    MainWindow *ptr = NULL;
    QButtonGroup *bgCup;
    QButtonGroup *bgTem;
    QButtonGroup *bgSweet;
    QButtonGroup *bgAddi;
    int index = 0;

};

#endif // USER_H
