#ifndef USERVIEW_H
#define USERVIEW_H

#include <QDialog>

namespace Ui {
class UserView;
}

class UserView : public QDialog
{
    Q_OBJECT

public:
    explicit UserView(QWidget *parent = nullptr);
    ~UserView();

private:
    Ui::UserView *ui;
};

#endif // USERVIEW_H
