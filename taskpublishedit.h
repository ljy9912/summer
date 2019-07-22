#ifndef TASKPUBLISHEDIT_H
#define TASKPUBLISHEDIT_H

#include <QDialog>
#include "task.h"
#include "user.h"
#include "list.h"

namespace Ui {
class taskPublishEdit;
}

class taskPublishEdit : public QDialog
{
    Q_OBJECT

public:
    explicit taskPublishEdit(QWidget *parent = 0);
    ~taskPublishEdit();
    void EditTask(taskPublisher myNewTask);
    void showValue();
    void EditUser(user myUser);
   void EditList(list newList);

private slots:
    void on_canclBtn_clicked();

    void on_confrmBtn_clicked();

private:
    Ui::taskPublishEdit *ui;
    taskPublisher myTask;
    user myUser;
    list List;
};

#endif // TASKPUBLISHEDIT_H
