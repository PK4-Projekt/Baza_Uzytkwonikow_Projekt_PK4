#include "invitation.h"
#include "ui_invitation.h"

Invitation::Invitation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Invitation)
{
    ui->setupUi(this);
}

Invitation::~Invitation()
{
    delete ui;
}
