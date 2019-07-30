#ifndef REGISTERCONFIRM_H
#define REGISTERCONFIRM_H

#include <QDialog>
#include "user.h"
#include <QList>
#include "taskpublisher.h"
#include "backup.h"

namespace Ui {
class registerConfirm;
}

class registerConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit registerConfirm(QWidget *parent = 0);
    ~registerConfirm();

    void showValue();


private:
    Ui::registerConfirm *ui;
    void SetStyle();

private slots:
    void on_pushButton_clicked();
};

#endif // REGISTERCONFIRM_H
