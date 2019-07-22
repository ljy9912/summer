#ifndef REGISTERCONFIRM_H
#define REGISTERCONFIRM_H

#include <QDialog>
#include "user.h"
#include <QList>
#include "taskpublisher.h"
#include "list.h"

namespace Ui {
class registerConfirm;
}

class registerConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit registerConfirm(QWidget *parent = 0);
    ~registerConfirm();
    void EditList(list newList);
    void showValue();
    void EditUser(user myUser);

private:
    Ui::registerConfirm *ui;
    user myUser;
    list List;


private slots:
    void on_pushButton_clicked();
};

#endif // REGISTERCONFIRM_H
