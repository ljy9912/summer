#ifndef MONEYINSERT_H
#define MONEYINSERT_H

#include <QDialog>
#include "user.h"
#include "task.h"
#include "list.h"

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
    void editList(list newList);

private slots:
    void on_confrmBtn_clicked();

private:
    Ui::userMoney *ui;
    user myUser;
    list List;
};

#endif // MONEYINSERT_H
