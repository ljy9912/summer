#ifndef USERINFO_H
#define USERINFO_H

#include <QDialog>
#include "user.h"
#include "task.h"
#include "list.h"

namespace Ui {
class userInfo;
}

class userInfo : public QDialog
{
    Q_OBJECT

public:
    explicit userInfo(QWidget *parent = 0);
    ~userInfo();
    void showValue(user);
    void EditUser(user myNewUser);
   void EditList(list newList);

private slots:
    void on_editBtn_clicked();

    void on_moneyBtn_clicked();

private:
    Ui::userInfo *ui;
    user myUser;
    list List;

signals:
    void dlgreturn(int);

private slots:
    void on_main_clicked();
};

#endif // USERINFO_H
