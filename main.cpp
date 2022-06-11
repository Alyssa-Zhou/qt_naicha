#include "mainwindow.h"
#include <QApplication>

#pragma execution_character_set("utf-8")    // UTF-8编码以显示中文

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
