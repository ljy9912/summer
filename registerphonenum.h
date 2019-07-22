#ifndef REGISTERPHONENUM_H
#define REGISTERPHONENUM_H

#include <QDialog>
#include "registerphoneconfrm.h"

namespace Ui {
class registerPhoneNum;
}

class registerPhoneNum : public QDialog
{
    Q_OBJECT

public:
    explicit registerPhoneNum(QWidget *parent = 0);
    ~registerPhoneNum();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_usrnameRegistrBtn_clicked();

    void on_IDRgstrBtn_clicked();

private:
    Ui::registerPhoneNum *ui;
    registerPhoneConfrm *dlg;

signals:
    void dlgreturn(QString value,QString,int);
};

#endif // REGISTERPHONENUM_H
