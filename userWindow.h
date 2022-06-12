#ifndef USER_H
#define USER_H

#include <QMainWindow>
#include "specifications.h"
#include "sql.h"
#include "mainwindow.h"
#include <QButtonGroup>

namespace Ui { class user; }

class userWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit userWindow(UserInfo usr, QWidget *parent = 0);
    ~userWindow();
    void closeEvent(QCloseEvent *event);
private slots:
    void on_spec_Btn_clicked(Goods *good);      // 选择商品
    void pushcart(Goods *good);                  // 加入购物车
    void on_checkout_Btn_clicked();             // 结账
private:
    void fixedOptions(specifications *s, int y, int h);     // 显示固定选项
    Order getOrder(Goods *good);                // 由商品和选项生成订单
    void init();

    Ui::user *ui;
    MainWindow *ptr = NULL;
    QButtonGroup *bgCup;        // 杯型选项组
    QButtonGroup *bgTem;        // 温度选项组
    QButtonGroup *bgSweet;      // 甜度选项组
    QButtonGroup *bgAddi;       // 配料选项组
    QWidget *cart;              // 购物车界面
    int numGoods = 0;           // 购物车商品数

    UserInfo usr;               // 用户信息
    QList<Order> orders;        // 购物车内的订单
};

#endif // USER_H
