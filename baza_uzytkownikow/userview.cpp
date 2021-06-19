#include "userview.h"
#include "ui_userview.h"
#include <QAbstractButton>

UserView::UserView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserView)
{
    ui->setupUi(this);
}

UserView::~UserView()
{
    delete ui;
}
