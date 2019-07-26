#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QMessageBox>
#include <registerconfirm.h>
#include <QList>
#include "task.h"
#include "backup.h"

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

    
private slots:
    void on_canclbtn_clicked();


    void on_confrmbtn_clicked();


    void on_pushButton_clicked();

private:
    Ui::Register *ui;
    registerConfirm *dlg;

};

#endif // REGISTER_H
