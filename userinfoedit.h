#ifndef USERINFOEDIT_H
#define USERINFOEDIT_H

#include <QDialog>
#include "user.h"
#include "task.h"
#include "list.h"

namespace Ui {
class userInfoEdit;
}

class userInfoEdit : public QDialog
{
    Q_OBJECT

public:
    explicit userInfoEdit(QWidget *parent = 0);
    ~userInfoEdit();
    void showValue(user);
    void EditUser(user myUser);
    void EditList(list newList);

private slots:
    void on_pushButton_3_clicked();

    void on_canclBtn_clicked();

    void on_confrmBtn_clicked();

private:
    Ui::userInfoEdit *ui;
    user myUser;
    list List;
};

#endif // USERINFOEDIT_H
