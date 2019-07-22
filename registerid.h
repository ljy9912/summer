#ifndef IDREGISTER_H
#define IDREGISTER_H

#include <QDialog>
#include "registeridconfrm.h"

namespace Ui {
class registerID;
}

class registerID : public QDialog
{
    Q_OBJECT

public:
    explicit registerID(QWidget *parent = 0);
    ~registerID();

private slots:
    void on_confrmBtn_clicked();

    void on_canclBtn_clicked();

    void on_rtrnLoginBtn_clicked();

    void on_usrnameRegisterBtn_clicked();

    void on_phonenumRgstrBtn_clicked();

private:
    Ui::registerID *ui;
    registerIDConfrm *dlg;

signals:
    void dlgreturn(QString value,QString,int);
};

#endif // IDREGISTER_H
