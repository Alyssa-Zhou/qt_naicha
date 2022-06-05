#include "sql.h"

// Sql构造函数，初始化
Sql::Sql(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // 不知道是不是必要的，先注释掉
    /*db.setHostName("127.0.0.1");
    db.setUserName("admin");
    db.setPassword("password");
    db.setDatabaseName("Milk Tea");*/
    if(db.open()){
        qDebug() << "Database connected successfully!" << Qt::endl;
        createTables();
    }
    else 
        qDebug() << "Database connected failed!" << Qt::endl;
}

// 创建数据表
void Sql::createTables(){
    query = new QSqlQuery;
    // 用户(用户名，密码，手机号)
    query->exec("create table UserTbl(name varchar(30) primary key, \
                                    Upassword varchar(30) not null,\
                                    phone varchar(30))");
    // 商品(名称，编号，价格，简介，图片路径)
    query->exec("create table GoodsTbl(name varchar(30) unique not null, \
                                    ID int primary key, \
                                    price int not null, \
                                    introduction varchar(300), \
                                    photoPath varchar(100))");
    // 订单(订单号，下单用户，下单日期，下单时间，订单商品编号，订单商品名称，杯型，温度，甜度，加料，订单状态)
    query->exec("create table OrderTbl(ID int primary key,\
                                    clientName varchar(30) not null,\
                                    orderDate date not null,\
                                    orderTime time not null,\
                                    goodsID int not null,\
                                    cupSize enum('medium', 'large', 'x-large') default 'medium',\
                                    temperature enum('ice', 'few-ice', 'drop-ice', 'warm', 'hot') default 'warm',\
                                    sweetness enum('normal', 'seven', 'half', 'three', 'zero') default 'nomal',\
                                    additionalIngredients enum('pearls', 'coconut', 'sago', 'taro') default 'null',\
                                    orderState enum('unpaid', 'making', 'waiting', 'completed') default 'unpaid')");
    
    // 添加管理员
    UserInfo admin(QString("admin"), QString("admin"), QString("12345678911"));
    addUser(&admin);

    UserInfo usr(QString("user1"), QString("123"), QString("12345678911"));
    addUser(&usr);

}

// 添加一个用户
bool Sql::addUser(UserInfo *usr){
    query = new QSqlQuery;
    QString str = QString("insert into UserTbl values('%1', '%2', '%3')").arg(usr->name, usr->password, usr->phone);
    return query->exec(str);
}

// 添加一个商品
bool Sql::addGoods(Goods *good){
    query = new QSqlQuery;
    QString str = QString("insert into GoodsTbl values('%1', '%2', '%3', '%4', '%5')").arg(good->name)
                    .arg(good->ID).arg(good->price).arg(good->introduction).arg(good->photoPath);
    return query->exec(str);
}

// 添加一个订单
bool Sql::addOrder(Order *order){
    query = new QSqlQuery;
    QString str = QString("insert into OrderTbl values('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10')")
                    .arg(order->ID).arg(order->clientName).arg(order->orderDate).arg(order->orderTime).arg(order->goodsID)
                    .arg(order->cupSize).arg(order->temperature).arg(order->sweetness).arg(order->additionalIngredients)
                    .arg(order->state);
    return query->exec(str);
}

// NOTE: 查找商品，每当商品列表或筛选条件有变化，调用此函数更新页面
void Sql::selectGoods(QString name = "", int id = (int)NULL, int minPrice = 0, int maxPrice = INTMAX){
    query = new QSqlQuery;
    QString str = QString("selece * from GoodsTbl where (price between %1 and %2)").arg(minPrice).arg(maxPrice);
    if(name != "") str = str.append(QString(" and (name = '%1')").arg(name));
    if(id != (int)NULL) str = str.append(QString(" and (id == %1)").arg(id));
    query->exec(str);

    // 如果无，显示没有查找到符合条件的商品的页面
    if(!query->first()){
        // TODO: 添加没有查找到符合条件的商品的页面
        return;
    }

    // 显示每一项
    while(query->next()){
        QString name = query->value(0).toString();
        int ID = query->value(1).toInt();
        int price = query->value(2).toInt();
        QString introduction = query->value(3).toString();
        QString photoPath = query->value(4).toString();
        // TODO: 显示这一项的内容页面

    }

}

// NOTE: 查找订单，需要查的时候再用，输入为筛选条件
void Sql::selectOrder(QString minDate = "0000/01/01", QString maxDate = "9999/01/01", QString clientName = ""){
    query = new QSqlQuery;
    QString str = QString("select * from OrderTbl where (orderDate between '%1' and '%2')").arg(minDate, maxDate);
    if(clientName != "") str = str.append(QString(" and (clientName = '%1')").arg(clientName));
    query->exec(str);

    // 如果无，显示没有查找到符合条件的商品的页面
    if(!query->first()){
        // TODO: 添加没有查找到符合条件的商品的页面
        return;
    }

    // 显示每一项
    while(query->next()){
        int orderID = query->value(0).toInt();
        QString clientName = query->value(1).toString();
        QString orderDate = query->value(2).toString();
        QString orderTime = query->value(3).toString();
        int goodsID = query->value(4).toInt();
        QString cupSize = query->value(5).toString();
        QString temperature = query->value(6).toString();
        QString sweetness = query->value(7).toString();
        QString additionalIngredients = query->value(8).toString();
        QString orderState = query->value(9).toString();

        // TODO: 显示这一项的内容页面

    }
}

// NOTE: 查找用户信息，需要查的时候再用，只能根据name查
void Sql::selectUser(QString name=""){
    query = new QSqlQuery;
    QString str = QString("select * from UserTbl");
    if(name != "") str = str.append(" where name = '%1'").arg(name);
    query->exec(str);

    // 如果无，显示没有查找到符合条件的商品的页面
    if(!query->first()){
        // TODO: 添加没有查找到符合条件的商品的页面
        return;
    }

    // 显示每一项
    while(query->next()){
        QString name = query->value(0).toString();
        QString Upassword = query->value(1).toString();
        QString phone = query->value(2).toString();

        // TODO: 显示这一项的内容页面
    }

}

// 更新用户信息
bool Sql::updateUser(UserInfo *usr){
    query = new QSqlQuery;
    QString str = QString("select * from UserTbl where name = '%1'").arg(usr->name);
    query->exec(str);

    if(query->first()){ deleteUser(usr->name); }    // 找到了，说明已有这个用户，把它删除
    return addUser(usr);    // 即可添加一条用户信息
}

// 更新商品信息
bool Sql::updateGoods(Goods *good){
    query = new QSqlQuery;
    QString str = QString("select * from GoodsTbl where ID = %1").arg(good->ID);
    query->exec(str);

    if(query->first()){ deleteGoods(good->ID); }    // 找到了，说明已有这个商品，把它删除
    return addGoods(good);    // 即可添加一条商品信息
}

// 更新订单信息
bool Sql::updateOrder(Order *order){
    query = new QSqlQuery;
    QString str = QString("select * from OrdersTbl where ID = %1").arg(order->ID);
    query->exec(str);

    if(query->first()){ deleteOrder(order->ID); }    // 找到了，说明已有这个订单，把它删除
    return addOrder(order);    // 即可添加一条用户信息
}

// 删除用户
bool Sql::deleteUser(QString name){
    query = new QSqlQuery;
    return query->exec(QString("delete from UserTbl where name = %1").arg(name));
}

// 删除商品
bool Sql::deleteGoods(int id){
    query = new QSqlQuery;
    return query->exec(QString("delete from GoodsTbl where ID = %1").arg(id));
}

// 删除订单
bool Sql::deleteOrder(int id){
    query = new QSqlQuery;
    return query->exec(QString("delete from OrderTbl where ID = %1").arg(id));
}
