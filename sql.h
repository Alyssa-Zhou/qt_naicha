#ifndef __SQL_H__
#define __SQL_H__

#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QStandardItemModel>

#define INTMAX 0x3f3f3f3f

// 用户类
struct UserInfo{
    UserInfo() {}
    UserInfo(QString name, QString password, QString phone): name(name), password(password), phone(phone) {}
    QString name, password, phone;
};

// 商品类
struct Goods{
    Goods() {}
    Goods(QString name, int p, QString introduction, QString photoPath)
        :name(name), introduction(introduction), photoPath(photoPath), price(p){}
    QString name, introduction, photoPath;
    int ID, price;
};

// 订单类
struct Order{
    Order(){}
    Order(QString clientName, QString goodsName, QString orderDate, QString orderTime, QString cupSize, QString temperature,
            QString sweetness, QString additionalIngredients, QString state):clientName(clientName), goodsName(goodsName),
            orderDate(orderDate), orderTime(orderTime), cupSize(cupSize), temperature(temperature), sweetness(sweetness),
            additionalIngredients(additionalIngredients), state(state){ }
    int ID;
    QString clientName, goodsName, orderDate, orderTime, cupSize, temperature, sweetness, additionalIngredients, state;
};

class Sql{
public:
    // 构造函数与初始化
    Sql();
    void createTables();    // 创建表
    void initData();        // 初始化表中数据用于测试
    // 添加数据
    bool addUser(UserInfo *usr);
    bool addGoods(Goods *good);
    bool addOrder(Order *order);
    // 搜索数据(根据筛选条件)并可视化
    void selectUser(QString name = "");
    void selectGoods(QString name = "", int id = (int)NULL, int minPrice = 0, int maxPrice = INTMAX);
    void selectOrder(QString clientName = "", QString minDate = "", QString maxDate = "");
    void visualizeTable(QStandardItemModel* mdl, QStringList* tbl); // 可视化数据表
    // 更新数据
    bool updateUser(UserInfo *usr);
    bool updateGoods(Goods *good);
    bool updateOrder(Order *order);
    // 删除数据
    bool deleteUser(QString name);
    bool deleteGoods(int id);
    bool deleteOrder(int id);
    // misc
    bool findUser(QString name);
    Goods* findGood(int id);
    int countGoods();
    void initCounts();

    // 成员变量
    QSqlQuery *query;
    QStandardItemModel* model = new QStandardItemModel();       // 商品model
    QStandardItemModel* model1 = new QStandardItemModel();      // 订单model
    QStandardItemModel* model2 = new QStandardItemModel();      // 用户model
};


#endif
