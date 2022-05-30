#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>

namespace Ui {
class manager;
}

class manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit manager(QWidget *parent = 0);
    ~manager();

private:
    Ui::manager *ui;
};

#endif // MANAGER_H
