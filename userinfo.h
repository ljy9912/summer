#ifndef USERINFO_H
#define USERINFO_H

#include <QDialog>
#include "backup.h"

namespace Ui {
class userInfo;
}

class userInfo : public QDialog
{
    Q_OBJECT

public:
    explicit userInfo(QWidget *parent = 0);
    ~userInfo();
    void showValue();


private slots:
    void on_editBtn_clicked();

    void on_moneyBtn_clicked();

private:
    Ui::userInfo *ui;
    QList<Message> m_messageList;
    void SetStyle();
    void SetWarningBox(QString text);
    QString m_BtnStyle1;

signals:
    void dlgreturn(int);

private slots:
    void on_Main_clicked();
};

#endif // USERINFO_H
