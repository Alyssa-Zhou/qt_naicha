#ifndef SPECIFICATIONS_H
#define SPECIFICATIONS_H

#include <QDialog>

namespace Ui {
class specifications;
}

class specifications : public QDialog {
    Q_OBJECT

public:
    explicit specifications(QWidget *parent = 0);
    ~specifications();

private:
    Ui::specifications *ui;
};

#endif // SPECIFICATIONS_H
