#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_logging_Btn_clicked();

    void on_exit_Btn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
