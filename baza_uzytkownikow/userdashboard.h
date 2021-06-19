#ifndef USERDASHBOARD_H
#define USERDASHBOARD_H

#include <QDialog>

namespace Ui {
class UserDashboard;
}

class UserDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit UserDashboard(QWidget *parent = nullptr);
    ~UserDashboard();

private slots:
    void on_contactList_activated(const QModelIndex &index);

    void on_contactGroupsList_activated(const QModelIndex &index);

    void on_contactGroupsList_clicked(const QModelIndex &index);

    void newGroupClicked();
    void deleteGroupClicked();

    void on_findUserBtn_clicked();

    void on_saveEditUser_clicked();

    void on_pushButton_7_clicked();

    void on_editProfileButton_clicked();

    void on_contactBase_clicked();

    void on_myContactGroupsButton_clicked();

    void on_statisticsButton_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::UserDashboard *ui;
    //MainWindow *window;

    void updateContactGroupsList();

    void updateUsersList();

    void updateStatistics();
};

#endif // USERDASHBOARD_H
