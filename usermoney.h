#ifndef MONEYINSERT_H
#define MONEYINSERT_H

#include <QDialog>
#include "user.h"
#include "task.h"

namespace Ui {
class userMoney;
}

class userMoney : public QDialog
{
    Q_OBJECT

public:
    explicit userMoney(QWidget *parent = 0);
    ~userMoney();
    void editUser(user myNewUser);

private slots:
    void on_confrmBtn_clicked();

private:
    Ui::userMoney *ui;
    user myUser;
};

#endif // MONEYINSERT_H
