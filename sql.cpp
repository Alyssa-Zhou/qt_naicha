#include "sql.h"
#include <QMessageBox>

// Sql构造函数，初始化
Sql::Sql() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // db.setDatabaseName("milkTea.db");       // 存储为文件
    // 不知道是不是必要的，先注释掉
    /*db.setHostName("127.0.0.1");
    db.setUserName("admin");
    db.setPassword("password");*/
    if (db.open()) {
        qDebug() << "Database connected successfully!";
        createTables();
        addData();
    }
    else
        qDebug() << "Database connected failed!";
}

// 生成insert指令
QString mergeToQuery(QStringList key, QStringList col, QString tblName){
    Q_ASSERT(key.length() == col.length());
    QString str = QString("insert into %1 (").arg(tblName);

    if(key[0] != "") str += QString("%1").arg(col[0]);
    for(int i = 1; i < key.length(); i++){
        if(key[i] != "") str += QString(", %1").arg(col[i]);
    }

    str += ") values(";

    if(key[0] != "") str += QString("'%1'").arg(key[0]);
    for(int i = 1; i < key.length(); i++){
        if(key[i] != "") str += QString(", '%1'").arg(key[i]);
    }
    str += ")";
    return str;
}

// 创建数据表
// NOTE: ID的顺序调到前面了，原来Order的goodsID改成了goodsName
void Sql::createTables() {
    query = new QSqlQuery;
    // 用户(用户名，密码，手机号)
    query->exec("create table UserTbl(name varchar(30) primary key, \
                                    Upassword varchar(30) not null,\
                                    phone varchar(30))");
    // 商品(名称，编号，价格，简介，图片路径)
    query->exec("create table GoodsTbl(ID INTEGER PRIMARY KEY AUTOINCREMENT, \
                                    name varchar(30) unique not null, \
                                    price int not null, \
                                    introduction varchar(300), \
                                    photoPath varchar(100))");
    // 订单(订单号，下单用户，下单日期，下单时间，订单商品编号，订单商品名称，杯型，温度，甜度，加料，订单状态)
    query->exec("create table OrderTbl(ID INTEGER PRIMARY KEY AUTOINCREMENT,\
                                    clientName varchar(30) not null,\
                                    goodsName varchar(30) not null,\
                                    orderDate date not null,\
                                    orderTime time not null,\
                                    cupSize varchar(10) default 'medium',\
                                    temperature varchar(10) default 'warm',\
                                    sweetness varchar(10) default 'normal',\
                                    additionalIngredients varchar(10) default 'pearls',\
                                    orderState varchar(10) default 'unpaid')");

    // 添加管理员
    UserInfo admin(QString("admin"), QString("admin"), QString("12345678911"));
    addUser(&admin);

    UserInfo usr(QString("user1"), QString("123"), QString("12345678911"));
    addUser(&usr);

}

// 添加一个用户
bool Sql::addUser(UserInfo* usr) {
    query = new QSqlQuery;
    QString str = QString("insert into UserTbl values('%1', '%2', '%3')").arg(usr->name, usr->password, usr->phone);
    qDebug() << "addUser";
    return query->exec(str);
}

// 添加一个商品
bool Sql::addGoods(Goods* good) {
    query = new QSqlQuery;
    QStringList key = {good->name, QString::number(good->price), good->introduction, good->photoPath};
    QString str = mergeToQuery(key, goodsColumns, "GoodsTbl");
    qDebug() << "addGoods" << str;
    return query->exec(str);
}

// 添加一个订单
bool Sql::addOrder(Order* order) {
    query = new QSqlQuery;
    QStringList key = {order->clientName, order->goodsName, order->orderDate, order->orderTime, order->cupSize,
                      order->temperature, order->sweetness, order->additionalIngredients, order->state};
    QString str = mergeToQuery(key, orderColumns, "OrderTbl");
    qDebug() << "addOrders" << str;
    return query->exec(str);
}

// 查找商品，每当商品列表或筛选条件有变化，调用此函数更新页面
void Sql::selectGoods(QString name, int id, int minPrice, int maxPrice) {
    query = new QSqlQuery;
    QString str = QString("select * from GoodsTbl where (price between %1 and %2)").arg(minPrice).arg(maxPrice);
    if (name != "") str = str.append(QString(" and (name = '%1')").arg(name));
    if (id != (int)NULL) str = str.append(QString(" and (id = %1)").arg(id));
    qDebug() << str;
    query->exec(str);
    qDebug() << "selectGoods";
    // 如果无，显示没有查找到符合条件的商品的页面
    if (!query->first()) {
        model->clear();
        qDebug() << "no goods";
        return;
    }

    // 显示每一项
    int cnt = 0;//计数
    //设置表头
    model->clear();
    model->setColumnCount(5);
    model->setHeaderData(0, Qt::Horizontal, "商品名称");
    model->setHeaderData(1, Qt::Horizontal, "ID");
    model->setHeaderData(2, Qt::Horizontal, "价格");
    model->setHeaderData(3, Qt::Horizontal, "简介");
    model->setHeaderData(4, Qt::Horizontal, "图片");

    do {
        QString name = query->value(0).toString();
        int ID = query->value(1).toInt();
        int price = query->value(2).toInt();
        QString introduction = query->value(3).toString();
        QString photoPath = query->value(4).toString();

        for (int i = 0; i < 5; i++) {
            model->setItem(cnt, i, new QStandardItem(query->value(i).toString()));
        }
        cnt++;

        qDebug() << name << ID << price << introduction << photoPath;
    } while (query->next());

}

// 查找订单，需要查的时候再用，输入为筛选条件
void Sql::selectOrder(QString clientName, QString minDate, QString maxDate) {
    query = new QSqlQuery;
    if(minDate == "") minDate = "1900-01-01";
    if(maxDate == "") maxDate = "2100-01-01";
    QString str = QString("select * from OrderTbl where (orderDate between '%1' and '%2')").arg(minDate, maxDate);
    if (clientName != "") str = str.append(QString(" and (clientName = '%1')").arg(clientName));
    qDebug() << str;
    query->exec(str);

    // 如果无，显示没有查找到符合条件的商品的页面
    if (!query->first()) {
        model1->clear();
        qDebug() << "no order";
        return;
    }

    // 显示每一项
    int cnt = 0;//计数
    //设置表头
    model1->clear();
    model1->setColumnCount(10);
    model1->setHeaderData(0, Qt::Horizontal, "订单ID");
    model1->setHeaderData(1, Qt::Horizontal, "用户名");
    model1->setHeaderData(2, Qt::Horizontal, "日期");
    model1->setHeaderData(3, Qt::Horizontal, "时间");
    model1->setHeaderData(4, Qt::Horizontal, "商品ID");
    model1->setHeaderData(5, Qt::Horizontal, "杯型");
    model1->setHeaderData(6, Qt::Horizontal, "温度");
    model1->setHeaderData(7, Qt::Horizontal, "甜度");
    model1->setHeaderData(8, Qt::Horizontal, "备注");
    model1->setHeaderData(9, Qt::Horizontal, "订单状态");
    do {
        for (int i = 0; i < 10; i++) {
            model1->setItem(cnt, i, new QStandardItem(query->value(i).toString()));
            qDebug() << query->value(i).toString();
        }
        cnt++;
    } while (query->next());
}

// 查找用户信息，需要查的时候再用，只能根据name查
void Sql::selectUser(QString name) {
    query = new QSqlQuery;
    QString str = QString("select * from UserTbl");
    if (name != "") str = str.append(" where name = '%1'").arg(name);
    qDebug() << str;
    query->exec(str);

    // 如果无，显示没有查找到符合条件的商品的页面
    if (!query->first()) {
        model2->clear();
        qDebug() << "no user";
        return;
    }

    // 显示每一项
    int cnt = 0;//计数
    //设置表头
    model2->clear();
    model2->setColumnCount(3);
    model2->setHeaderData(0, Qt::Horizontal, "用户名");
    model2->setHeaderData(1, Qt::Horizontal, "ID");
    model2->setHeaderData(2, Qt::Horizontal, "电话号码");

    do {
        QString name = query->value(0).toString();
        QString Upassword = query->value(1).toString();
        QString phone = query->value(2).toString();

        // 显示这一项的内容页面
        for (int i = 0; i < 3; i++) {
            model2->setItem(cnt, i, new QStandardItem(query->value(i).toString()));
            qDebug() << query->value(i).toString();
        }
        cnt++;
        qDebug() << name << Upassword << phone;
    } while (query->next());
}

// 更新用户信息
bool Sql::updateUser(UserInfo* usr) {
    query = new QSqlQuery;
    QString str = QString("select * from UserTbl where name = '%1'").arg(usr->name);
    query->exec(str);

    if (query->first()) { deleteUser(usr->name); }    // 找到了，说明已有这个用户，把它删除
    return addUser(usr);    // 即可添加一条用户信息
}

// 更新商品信息
bool Sql::updateGoods(Goods* good) {
    query = new QSqlQuery;
    QString str = QString("select * from GoodsTbl where ID = %1").arg(good->ID);
    query->exec(str);

    if (query->first()) { deleteGoods(good->ID); }    // 找到了，说明已有这个商品，把它删除
    return addGoods(good);    // 即可添加一条商品信息
}

// 更新订单信息
bool Sql::updateOrder(Order* order) {
    query = new QSqlQuery;
    QString str = QString("select * from OrdersTbl where ID = %1").arg(order->ID);
    query->exec(str);

    if (query->first()) { deleteOrder(order->ID); }    // 找到了，说明已有这个订单，把它删除
    return addOrder(order);    // 即可添加一条用户信息
}

// 删除用户
bool Sql::deleteUser(QString name) {
    query = new QSqlQuery;
    return query->exec(QString("delete from UserTbl where name = '%1'").arg(name));
}

// 删除商品
bool Sql::deleteGoods(int id) {
    query = new QSqlQuery;
    return query->exec(QString("delete from GoodsTbl where ID = %1").arg(id));
}

// 删除订单
bool Sql::deleteOrder(int id) {
    query = new QSqlQuery;
    return query->exec(QString("delete from OrderTbl where ID = %1").arg(id));
}

void Sql::addData() {
    UserInfo usr2("user2", "123", "12345678911");
    UserInfo usr3("user3", "123", "12345678911");
    if (!addUser(&usr2)) qDebug() << "err";
    if (!addUser(&usr3)) qDebug() << "err";

    Goods g1("芋泥啵啵", 15, "123", "123");
    Goods g2("芝芝莓莓", 14, "123", "123");
    Goods g3("经典奶茶", 10, "123", "123");
    if (!addGoods(&g1)) qDebug() << "err";
    if (!addGoods(&g2)) qDebug() << "err";
    if (!addGoods(&g3)) qDebug() << "err";

    Order o1("user1", "芋泥啵啵", "2022-01-01", "14:45:11", "medium", "few-ice", "half", "pearls", "making");
    if (!addOrder(&o1)) qDebug() << "err";
}

// 注册查找用户，防止重复
bool Sql::findUser(QString name) {
    query = new QSqlQuery;
    query->exec(QString("select * from UserTbl where name = '%1'").arg(name));
    return query->first();
}

// 获取商品信息
Goods* Sql::findGood(int id){
    query = new QSqlQuery;
    Goods* good = new Goods;

    QString str = QString("select * from GoodsTbl where ID = %1").arg(id);
    query->exec(str);

    query->first();

    good->name = query->value(1).toString();
    good->price = query->value(2).toInt();
    good->introduction = query->value(3).toString();
    good->photoPath = query->value(4).toString();

    qDebug() << "findGood:" << query->value(0) << query->value(1) << query->value(2) << query->value(3) << query->value(4);
    return good;
}


// 获取商品总数
int Sql::countGoods() {
    query = new QSqlQuery;
    query->exec(QString("select count(*) from GoodsTbl"));
    query->first();
    return query->value(0).toInt();
}
