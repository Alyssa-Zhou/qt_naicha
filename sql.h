#ifndef __SQL_H__
#define __SQL_H__

#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

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
    Goods(QString name, int ID, int p, QString introduction, QString photoPath)
        :name(name), introduction(introduction), photoPath(photoPath), ID(ID), price(p){}
    QString name, introduction, photoPath;
    int ID, price;
};

// 订单类
struct Order{
    Order(){}
    Order(int ID, QString clientName, QString orderDate, QString orderTime, int goodsID, QString cupSize, QString temperature,
            QString sweetness, QString additionalIngredients, QString state): ID(ID), goodsID(goodsID), clientName(clientName),
            orderDate(orderDate), orderTime(orderTime), cupSize(cupSize), temperature(temperature), sweetness(sweetness),
            additionalIngredients(additionalIngredients), state(state){ }
    int ID, goodsID;
    QString clientName, orderDate, orderTime, cupSize, temperature, sweetness, additionalIngredients, state;
};

class Sql{
public:
    Sql();
    void createTables();

    bool addUser(UserInfo *usr);
    bool addGoods(Goods *good);
    bool addOrder(Order *order);

    void selectUser(QString name);
    void selectGoods(QString name, int id, int minPrice, int maxPrice);
    void selectOrder(QString minDate, QString maxDate, QString clientName);

    bool updateUser(UserInfo *usr);
    bool updateGoods(Goods *good);
    bool updateOrder(Order *order);

    bool deleteUser(QString name);
    bool deleteGoods(int id);
    bool deleteOrder(int id);

    QSqlQuery *query;

};

#endif
