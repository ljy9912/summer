#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "user.h"
#include <QList>
#include "taskpublisher.h"
#include "backup.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::LoginDialog *ui;
    QString m_id;
    QString m_BtnStyle1;


public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_loginBtn_clicked();

    void on_RegisterBtn_clicked();
    void on_exitBtn_clicked();

    void SetStyle();
    void SetWarningBox(QString text);
    void SetCanclBox();
    bool IsEmpty();
    void on_exitBtn_2_clicked();
};

#endif // LOGINDIALOG_H
