#ifndef USERINFOEDIT_H
#define USERINFOEDIT_H

#include <QDialog>
#include "backup.h"

namespace Ui {
class userInfoEdit;
}

class userInfoEdit : public QDialog
{
    Q_OBJECT

public:
    explicit userInfoEdit(QWidget *parent = 0);
    ~userInfoEdit();
    void showValue(user myUser);
    void EditBackUp(BackUp myBackUp);

private slots:
    void on_pushButton_3_clicked();

    void on_canclBtn_clicked();

    void on_confrmBtn_clicked();

private:
    Ui::userInfoEdit *ui;
    BackUp m_BackUp;
};

#endif // USERINFOEDIT_H
