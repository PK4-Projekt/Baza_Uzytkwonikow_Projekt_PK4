#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "userdashboard.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_addPhoneButton_clicked();

    void on_addEmailButton_clicked();

    void on_loginButton_clicked();

    void on_registerBtn_clicked();

private:

    Ui::MainWindow *ui;
    UserDashboard *dashboardWindow;

    void showMainWindow();
};

#endif // MAINWINDOW_H
