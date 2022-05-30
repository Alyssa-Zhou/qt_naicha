#ifndef USER_H
#define USER_H

#include <QMainWindow>

namespace Ui {
class user;
}

class user : public QMainWindow
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = 0);
    ~user();

private:
    Ui::user *ui;


};

#endif // USER_H
