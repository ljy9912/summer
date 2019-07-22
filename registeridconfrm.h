#ifndef IDREGISTERCONFRM_H
#define IDREGISTERCONFRM_H

#include <QDialog>

namespace Ui {
class registerIDConfrm;
}

class registerIDConfrm : public QDialog
{
    Q_OBJECT

public:
    explicit registerIDConfrm(QWidget *parent = 0);
    ~registerIDConfrm();

private slots:
    void on_main_clicked();
    void showValue(QString namevalue,QString Englishvalue,int id);

private:
    Ui::registerIDConfrm *ui;
};

#endif // IDREGISTERCONFRM_H
