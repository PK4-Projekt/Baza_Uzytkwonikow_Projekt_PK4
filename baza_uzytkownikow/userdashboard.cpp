#include <QWidget>
#include <QListWidget>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QList>
#include "userdashboard.h"
#include "ui_userdashboard.h"
#include "database.h"
#include "State.h"

UserDashboard::UserDashboard(QWidget *parent) :
        QDialog(parent, Qt::WindowMaximizeButtonHint |
                        Qt::WindowMinimizeButtonHint |
                        Qt::WindowCloseButtonHint |
                        Qt::WindowSystemMenuHint),
        ui(new Ui::UserDashboard) {
    ui->setupUi(this);

    updateContactGroupsList();
    updateUsersList();
    updateStatistics();
}


void UserDashboard::updateUsersList() {
    auto *db = Database::getInstance();
    auto users = db->getAllUsers();

    auto *model = new QStandardItemModel();
    QString str;

    for (auto *user : *users) {
        auto emails = user->getEmails();
        QString emailStr = "";
        if (!emails.empty()) {
            emailStr = "| " + emails[0]->getEmail();
        }

        str = user->getLastName() + " " + user->getFirstName() + " | " +
              user->getLogin() + " | " + user->getAddress()->getCity() + " " + emailStr;
        model->appendRow(new QStandardItem(str));

        delete user;
    }

    ui->allUsersList->setModel(model);
}

void UserDashboard::updateContactGroupsList() {
    auto *db = Database::getInstance();
    auto *currentUser = State::currentUser;
    std::vector<ContactGroup *> contactGroups = db->getContactGroups(currentUser->getUserId(), false);

    auto *model = new QStringListModel();
    QStringList list;

    for (auto *contactGroup : contactGroups) {
        list << contactGroup->getName();
        delete contactGroup;
    }


    model->setStringList(list);
    ui->contactGroupsList->setModel(model);
}

UserDashboard::~UserDashboard() {
    delete ui;
}

void UserDashboard::on_contactList_activated(const QModelIndex &index) {

}

void UserDashboard::on_contactGroupsList_activated(const QModelIndex &index) {

}

void UserDashboard::on_contactGroupsList_clicked(const QModelIndex &index) {
    auto *model = index.model();
    auto selectedGroupName = model->data(index).toString();
    auto userId = State::currentUser->getUserId();

    auto *db = Database::getInstance();
    auto *users = db->getContactsFromGroup(selectedGroupName, userId);

    auto *model2 = new QStringListModel();
    QStringList list;

    for (auto *user : *users) {
        list << user->toQString();
        delete user;
    }
    delete users;

    model2->setStringList(list);
    ui->contactList->setModel(model2);

}

void UserDashboard::newGroupClicked() {
    const QString &name = ui->addGroupEdit->text();

    if (name.isEmpty()) {
        Message::warning("Podaj nazwę grupy");
        return;
    }

    auto *db = Database::getInstance();
    db->insertContactGroup(name);
    updateContactGroupsList();
}

void UserDashboard::deleteGroupClicked() {
    auto *db = Database::getInstance();

    QItemSelectionModel *model = ui->contactGroupsList->selectionModel();
    const QModelIndexList &selectedIndexes = model->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        Message::warning("Zaznacz grupę");
        return;
    }
    QModelIndex index = selectedIndexes.first();
    const QString &selectedGroupName = index.data().value<QString>();

    db->deleteContactGroupByName(selectedGroupName);
    updateContactGroupsList();

}

void UserDashboard::on_findUserBtn_clicked()
{
    auto db = Database::getInstance();
    auto *model = new QStandardItemModel();
    if (ui->usersFilterEmail->text().size() > 0){
        QString email = ui->usersFilterEmail->text();
        auto user = db->getUserByMail(email);
        if (user != nullptr){
            auto email = user->getEmails();
            QString emailStr = "";
            if (!email.empty()) {
                emailStr = "| " + email[0]->getEmail();
            }
            QString str = user->getLastName() + " " + user->getFirstName() + " | " +
            user->getLogin() + " | " + user->getAddress()->getCity() + " " + emailStr;
            model->appendRow(new QStandardItem(str));
        }
    ui->allUsersList->setModel(model);
    }
    else if (ui->usersFilterName->text().size() > 0){
        QString name = ui->usersFilterName->text();
        auto user = db->getUserByFirstName(name);
        if (user != nullptr){
            auto email = user->getEmails();
            QString emailStr = "";
            if (!email.empty()) {
                emailStr = "| " + email[0]->getEmail();
            }
            QString str = user->getLastName() + " " + user->getFirstName() + " | " +
            user->getLogin() + " | " + user->getAddress()->getCity() + " " + emailStr;
            model->appendRow(new QStandardItem(str));
        }
        ui->allUsersList->setModel(model);
    }
    else if (ui->usersFilterSurname->text().size() > 0){
        QString name = ui->usersFilterSurname->text();
        auto user = db->getUserByLastName(name);
        if (user != nullptr){
            auto email = user->getEmails();
            QString emailStr = "";
            if (!email.empty()) {
                emailStr = "| " + email[0]->getEmail();
            }
            QString str = user->getLastName() + " " + user->getFirstName() + " | " +
            user->getLogin() + " | " + user->getAddress()->getCity() + " " + emailStr;
            model->appendRow(new QStandardItem(str));
        }
        ui->allUsersList->setModel(model);
    }
    else if (ui->usersFilterCity->text().size() > 0){
        QString city = ui->usersFilterCity->text();
        auto users = db->getUserByCity(city);
        if (users != nullptr){
            for(auto *user : *users){
            auto email = user->getEmails();
            QString emailStr = "";
            if (!email.empty()) {
                emailStr = "| " + email[0]->getEmail();
            }
            QString str = user->getLastName() + " " + user->getFirstName() + " | " +
            user->getLogin() + " | " + user->getAddress()->getCity() + " " + emailStr;
            model->appendRow(new QStandardItem(str));
            }
        }
        else model->appendRow(new QStandardItem("null??"));
        ui->allUsersList->setModel(model);
    }
    else updateUsersList();

    //delete model;
}

void UserDashboard::updateStatistics(){
    auto db = Database::getInstance();
    auto *currentUser = State::currentUser;
    auto users = db->getAllUsers();
    int numberOfUsers = users->size();
    ui->numberOfUsersEdit->insert(QString::number(numberOfUsers));
    auto groups = db->getAllGroups();
    int numberOfGroups = groups->size();
    ui->numberOfGroupsEdit->insert(QString::number(numberOfGroups));
    auto userGroups = db->getContactGroups(currentUser->getUserId(), false);
    int numberOfUserGroups = userGroups.size();
    ui->numberOfUserGroupsEdit->insert(QString::number(numberOfUserGroups));
    int photos = db->numberOfUserWithPhotos();
    ui->numberOfUsersWithPhotoEdit->insert(QString::number(photos));
    int numberOfFeeds = db->numberOfFeeds(currentUser->getUserId());
    ui->numberOfUserFeedMessagesEdit->insert(QString::number(numberOfFeeds));
    int numberOfContacts = 0;
    for(auto group : userGroups){
        auto contacts = db->getContactsFromGroup(group->getName(),currentUser->getUserId());
        numberOfContacts += contacts->size();
    }
    ui->numberOfFriendsEdit->insert(QString::number(numberOfContacts));
    int numberOfShares = db->numberOfContactShare(currentUser->getUserId());
    ui->numberOfGroupSharesEdit->insert(QString::number(numberOfShares));
    int numberOfInvitations = db->numberOfInvitations(currentUser->getUserId());
    ui->waitingUserInvitationsEdit->insert(QString::number(numberOfInvitations));
}

void UserDashboard::on_saveEditUser_clicked()
{
    auto db = Database::getInstance();
    auto *currentUser = State::currentUser;
    if (ui->passwordEdit->text().length() >0 && ui->passwordRepeatEdit->text().length() == ui->passwordEdit->text().length()){
        db->changePassword(currentUser->getUserId(), ui->passwordEdit->text());
    }
    if (ui->nameEdit->text().length() > 0){
        db->changeName(currentUser->getUserId(), ui->nameEdit->text());
    }
    if (ui->surnameEdit->text().length() > 0){
       db->changeSurname(currentUser->getUserId(), ui->surnameEdit->text());
    }
    if (ui->cityEdit->text().length() > 0){
       db->changeCity(currentUser->getUserId(), ui->cityEdit->text());
    }
    if (ui->streetEdit->text().length() > 0){
       db->changeStreet(currentUser->getUserId(), ui->streetEdit->text());
    }
    if (ui->homeNumberEdit->text().length() > 0){
        db->changeHomeNumber(currentUser->getUserId(), ui->homeNumberEdit->text());
     }
    if (ui->postalCodeEdit->text().length() > 0){
        db->changePostalCode(currentUser->getUserId(), ui->postalCodeEdit->text());
     }
    if (ui->postOfficeEdit->text().length() > 0){
       db->changePostOffice(currentUser->getUserId(), ui->postOfficeEdit->text());
    }
}

void UserDashboard::on_pushButton_7_clicked()
{
    ui->nameEdit->clear();
    ui->surnameEdit->clear();
    ui->cityEdit->clear();
    ui->streetEdit->clear();
    ui->homeNumberEdit->clear();
    ui->postalCodeEdit->clear();
    ui->postOfficeEdit->clear();
    ui->passwordEdit->clear();
    ui->passwordRepeatEdit->clear();
}

void UserDashboard::on_editProfileButton_clicked()
{
   ui->tabWidget->setCurrentIndex(4);
}



void UserDashboard::on_contactBase_clicked()
{
   ui->tabWidget->setCurrentIndex(2);
}

void UserDashboard::on_myContactGroupsButton_clicked()
{
   ui->tabWidget->setCurrentIndex(1);
}

void UserDashboard::on_statisticsButton_clicked()
{
   ui->tabWidget->setCurrentIndex(5);
}

void UserDashboard::on_tabWidget_currentChanged(int index)
{
    auto db = Database::getInstance();
    auto user = State::currentUser;
    if (index == 5) {
        ui->numberOfUsersEdit->clear();
        ui->numberOfGroupsEdit->clear();
        ui->numberOfUserGroupsEdit->clear();
        ui->numberOfUsersWithPhotoEdit->clear();
        ui->numberOfUserFeedMessagesEdit->clear();
        ui->numberOfFriendsEdit->clear();
        ui->numberOfGroupSharesEdit->clear();
        ui->waitingUserInvitationsEdit->clear();
        updateStatistics();
    }
    if(index == 2){
        auto groups = db->getContactGroups(user->getUserId(), false);
        for (auto *grup : groups){
            ui->myGroupSendInvitationCombo->addItem(QString(grup->getName()));
        }
        updateUsersList();
    }
}
