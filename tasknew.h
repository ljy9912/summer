#ifndef PUBLISHNEW_H
#define PUBLISHNEW_H

#include <QDialog>
#include "taskpublish.h"
#include "task.h"
#include "user.h"
#include "list.h"

namespace Ui {
class taskNew;
}

class taskNew : public QDialog
{
    Q_OBJECT

public:
    explicit taskNew(QWidget *parent = 0);
    ~taskNew();
    void EditUser(user myNewUser);
    void showValue(taskPublisher);
    void EditIDTask(int iid);
    void EditList(list newList);

private slots:
    void on_canclBtn_clicked();

    void on_confrmBtn_clicked();

    void on_main_clicked();
    
private:
    Ui::taskNew *ui;
    user myUser;
    int idtask;
    taskPublisher myTask;
    list List;
};

#endif // PUBLISHNEW_H
