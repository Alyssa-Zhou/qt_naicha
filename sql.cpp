#include "sql.h"
#include "qlabel.h"
#include <QMessageBox>
#include <QCoreApplication>

// 除 ID 以外的键名
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, userCols, ({"name", "Upassword", "phone"}));
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, goodsCols, ({"name", "price", "introduction", "photoPath"}));
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, orderCols, ({"clientName", "goodsName", "orderDate", "orderTime",
                        "cupSize", "temperature",  "sweetness", "additionalIngredients", "orderState"}))

// 中文键名，包含ID
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, userColsCN, ({"用户编号", "用户名称", "用户密码", "手机号"}));
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, GoodsColsCN, ({"商品编号", "商品名", "价格", "介绍"})); // 图片单独处理
Q_GLOBAL_STATIC_WITH_ARGS(QStringList, orderColsCN, ({"订单编号", "用户名", "商品名", "订单日期",
                                        "订单时间", "杯型", "温度",  "甜度", "加料", "订单状态"}));

// Sql构造函数，初始化
Sql::Sql() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //存储为文件 路径为\build-naicha-Desktop_Qt_5_9_1_MinGW_32bit-Debug\下
    //第一次运行将addData取消注释，之后无需再添加数据即可注释掉
    // db.setDatabaseName("sqltest.db");

    if(db.open()){
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

    // 要输入的项的名称
    if(key[0] != "") str += QString("%1").arg(col[0]);
    for(int i = 1; i < key.length(); i++){
        if(key[i] != "") str += QString(", %1").arg(col[i]);
    }

    str += ") values(";

    // 要输入的项的值
    if(key[0] != "") str += QString("'%1'").arg(key[0]);
    for(int i = 1; i < key.length(); i++){
        if(key[i] != "") str += QString(", '%1'").arg(key[i]);
    }
    str += ")";
    return str;
}

// 可视化数据表
void Sql::visualizeTable(QStandardItemModel* mdl, QStringList* tbl){
    mdl->clear();                           // 清除当前表格数据
    mdl->setColumnCount(tbl->length());     // 设置表列数
    // 设置表头
    for(int col = 0; col < tbl->length(); col++){
        mdl->setHeaderData(col, Qt::Horizontal, tbl->value(col));
    }
    // 设置表中数据
    for(int row = 0; query->isValid(); query->next(), row++){
        for (int col = 0; col < tbl->length(); col++) {
            mdl->setItem(row, col, new QStandardItem(query->value(col).toString()));
        }
    }
}

// 创建数据表
void Sql::createTables() {
    query = new QSqlQuery;
    // 用户(用户名，密码，手机号)
    query->exec("create table UserTbl(ID INTEGER PRIMARY KEY AUTOINCREMENT, \
                                    name varchar(30), \
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
                                    additionalIngredients varchar(30) default 'null',\
                                    orderState varchar(10) default 'unpaid')");
}

// 添加一个用户
bool Sql::addUser(UserInfo* usr) {
    query = new QSqlQuery;
    QStringList key = {usr->name, usr->password, usr->phone};
    QString str = mergeToQuery(key, *userCols, "UserTbl");
    qDebug() << "addUser:" << str;
    return query->exec(str);
}

// 添加一个商品
bool Sql::addGoods(Goods* good) {
    query = new QSqlQuery;
    QStringList key = {good->name, QString::number(good->price), good->introduction, good->photoPath};
    QString str = mergeToQuery(key, *goodsCols, "GoodsTbl");
    qDebug() << "addGoods:" << str;
    return query->exec(str);
}

// 添加一个订单
bool Sql::addOrder(Order* order) {
    query = new QSqlQuery;
    QStringList key = {order->clientName, order->goodsName, order->orderDate, order->orderTime, order->cupSize,
                      order->temperature, order->sweetness, order->additionalIngredients, order->state};
    QString str = mergeToQuery(key, *orderCols, "OrderTbl");
    qDebug() << "addOrders" << str;
    return query->exec(str);
}

// 查找商品，每当商品列表或筛选条件有变化，调用此函数更新页面
void Sql::selectGoods(QString name, int id, int minPrice, int maxPrice) {
    query = new QSqlQuery;

    // 构造SQL指令
    QString str = QString("select * from GoodsTbl where (price between %1 and %2)").arg(minPrice).arg(maxPrice);
    if (name != "") str = str.append(QString(" and (name = '%1')").arg(name));
    if (id != (int)NULL) str = str.append(QString(" and (id = %1)").arg(id));
    qDebug() << "selectGoods: "<< str;

    // 执行指令并显示结果
    if(!query->exec(str)) qDebug() << "fail in exec";           // 执行指令
    else if(!query->first()) qDebug() << "no goods found";      // query指向表头
    visualizeTable(model, GoodsColsCN);                         // 可视化当前数据表

    // 单独添加图片
    // BUG: 图片加载失败
    int colNum = GoodsColsCN->length();
    model->insertColumn(colNum);
    model->setHeaderData(colNum, Qt::Horizontal, "图片");
    query->first();
    for(int row = 0; query->isValid(); query->next(), row++){
        QString path = query->value(colNum).toString();
        QImage image(path);
        if(image.isNull()) qDebug() << "fail in load image";
        QStandardItem *item = new QStandardItem();
        item->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);
        if(path != "") model->setItem(row, colNum, item);
        // 有path知乎用下面这一句就行
        // if(path != "") model->setItem(row, colNum, new QStandardItem(QIcon(path), " "));
    }

}

// 查找订单，需要查的时候再用，输入为筛选条件
void Sql::selectOrder(QString clientName, QString minDate, QString maxDate) {
    query = new QSqlQuery;

    // 构造SQL指令
    if(minDate == "") minDate = "1900-01-01";
    if(maxDate == "") maxDate = "2100-01-01";
    QString str = QString("select * from OrderTbl where (orderDate between '%1' and '%2')").arg(minDate, maxDate);
    if (clientName != "") str = str.append(QString(" and (clientName = '%1')").arg(clientName));
    qDebug() << "selectOrder" << str;

    // 执行指令并显示结果
    if(!query->exec(str)) qDebug() << "fail in exec";           // 执行指令
    else if(!query->first()) qDebug() << "no order found";      // query指向表头
    visualizeTable(model1, orderColsCN);                        // 可视化当前数据表
}

// 查找用户信息，需要查的时候再用，只能根据name查
void Sql::selectUser(QString name) {
    query = new QSqlQuery;

    // 构造SQL指令
    QString str = QString("select * from UserTbl");
    if (name != "") str = str.append(" where name = '%1'").arg(name);
    qDebug() << "selectUser" << str;

    // 执行指令并显示结果
    if(!query->exec(str)) qDebug() << "fail in exec";           // 执行指令
    else if(!query->first()) qDebug() << "no order found";      // query指向表头
    visualizeTable(model2, userColsCN);                         // 可视化当前数据表
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

void Sql::addData(){
    // 添加管理员
    UserInfo admin(QString("admin"), QString("admin"), QString("12345678911"));
    addUser(&admin);

    // 添加测试成员
    UserInfo usr(QString("user1"), QString("123"), QString("12345678911"));
    UserInfo usr2(QString("user2"), QString("123"), QString("12345678911"));
    UserInfo usr3(QString("user3"), QString("123"), QString("12345678911"));
    if(!addUser(&usr)) qDebug()<<"err";
    if(!addUser(&usr2)) qDebug()<<"err";
    if(!addUser(&usr3)) qDebug()<<"err";

    // 添加商品
    Goods g1(QString("多肉桃桃"),19, QString("优选当季新鲜水蜜桃，皮薄汁多，果肉柔软细嫩，桃香饱满，去皮去核新鲜现制，充分保留果感，清晰释放新鲜桃肉的甜净。搭配幽香琥珀兰，香甜醇净。"),QString("./Resources/多肉桃桃.jpg"));
    Goods g2(QString("轻芒芒甘露"),18, QString("当季芒果香甜浓郁，加入红柚果粒、西米与胶原脆波波，口感丰富。芒果绿烟冰沙与椰浆的比例完美平衡，带来清新的热带之风。整体口感顺滑清新，爽快过瘾"),QString("./Resources/轻芒芒甘露.jpg"));
    Goods g3(QString("多肉葡萄冻"),19, QString("2018年首创品种，当季夏黑葡萄精细处理，保留果肉完整口感。搭配清新绿妍茶底与弹弹冻，鲜爽可口"),QString("./Resources/多肉葡萄冻.jpg"));
    if(!addGoods(&g1)) qDebug()<<"err";
    if(!addGoods(&g2)) qDebug()<<"err";
    if(!addGoods(&g3)) qDebug()<<"err";

    // 添加测试订单
    Order o1("user1", "芋泥啵啵", "2022-01-01", "14:45:11", "medium", "few-ice", "half", "pearls", "down");
    Order o2("user1", "多肉桃桃", "2022-01-01", "14:45:00", "large", "few-ice", "half", "pearls", "making");
    Order o3("user1", "经典奶茶", "2022-01-02", "13:45:11", "medium", "few-ice", "half", "pearls", "making");
    if (!addOrder(&o1)) qDebug() << "err";
    if (!addOrder(&o2)) qDebug() << "err";
    if (!addOrder(&o3)) qDebug() << "err";
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
