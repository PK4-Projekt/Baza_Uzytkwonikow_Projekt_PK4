#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include "Message.h"
#include "database.h"
#include "userdashboard.h"
#include "State.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addPhoneButton_clicked() {
}

void MainWindow::on_addEmailButton_clicked() {

}

void MainWindow::on_loginButton_clicked() {
    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (login.isEmpty()) {
        Message::warning("Podaj login!");
        return;
    }

    if (password.isEmpty()) {
        Message::warning("Podaj hasło!");
        return;
    }

    auto *db = Database::getInstance();
    if (!db->isUser(login, password)) {
        Message::warning("Podany login lub hasło są błędne");
    } else {
        Message::info("Poprawnie zalogowano do systemu");

        State::currentUser = db->getUserByName(login);

        showMainWindow();
    }
}

void MainWindow::showMainWindow() {
    dashboardWindow = new UserDashboard();
    dashboardWindow->show();
    dashboardWindow->showMaximized();
    dashboardWindow->setWindowTitle("Baza kontaktów");
    close();
}

void MainWindow::on_registerBtn_clicked() {
    auto *db = Database::getInstance();

    auto name = ui->nameLineEdit->text();
    auto surname = ui->surnameLineEdit->text();

    auto login = ui->logowanieLineEdit_2->text();
    auto password = ui->passwordLineEdit_2->text();
    auto passwordRepeat = ui->passwordRepeatLineEdit->text();

    auto street = ui->streetLineEdit->text();
    auto homeNumber = ui->homeNumberLineEdit->text();
    auto city = ui->cityLineEdit->text();
    auto postalCode = ui->postalCodeLineEdit->text();
    auto postOffice = ui->postOfficeLineEdit->text();

    if (password != passwordRepeat) {
        Message::warning("Podane hasła różnią się!");
        return;
    }

    if (db->isUser(login)) {
        Message::warning("Użytkownik o podanym loginie już istnieje!");
        return;
    }

    db->insertUser(name, surname,
                   login, password,
                   street, homeNumber, city, postalCode, postOffice);
}
