#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "user.h"
#include <QList>
#include "taskpublisher.h"
#include "list.h"
#include "backup.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::LoginDialog *ui;
    int id;
    BackUp m_BackUp;

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void EditBackUp(BackUp myBackUp);

private slots:
    void on_loginBtn_clicked();

    void on_RegisterBtn_clicked();
    void on_exitBtn_clicked();
};

#endif // LOGINDIALOG_H
