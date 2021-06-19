#ifndef INVITATION_H
#define INVITATION_H

#include <QDialog>

namespace Ui {
class Invitation;
}

class Invitation : public QDialog
{
    Q_OBJECT

public:
    explicit Invitation(QWidget *parent = nullptr);
    ~Invitation();

private:
    Ui::Invitation *ui;
};

#endif // INVITATION_H
