#ifndef REGISTERPNONECONFRM_H
#define REGISTERPNONECONFRM_H

#include <QDialog>

namespace Ui {
class registerPhoneConfrm;
}

class registerPhoneConfrm : public QDialog
{
    Q_OBJECT

public:
    explicit registerPhoneConfrm(QWidget *parent = 0);
    ~registerPhoneConfrm();

private slots:
    void showValue(QString namevalue,QString Englishvalue,int id);
    void on_main_clicked();

private:
    Ui::registerPhoneConfrm *ui;
};

#endif // REGISTERPNONECONFRM_H
