#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "user.h"
#include <QList>
#include "taskpublisher.h"
#include "list.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::LoginDialog *ui;
    int id;
    list List;

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    user myUser;
    void EditList(list newList);

private slots:
    void on_loginBtn_clicked();

    void on_RegisterBtn_clicked();
    void on_exitBtn_clicked();
};

#endif // LOGINDIALOG_H
