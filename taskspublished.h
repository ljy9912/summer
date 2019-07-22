#ifndef TASKSPUBLISHED_H
#define TASKSPUBLISHED_H

#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include "user.h"
#include "task.h"
#include "list.h"

namespace Ui {
class tasksPublished;
}

class tasksPublished : public QDialog
{
    Q_OBJECT

public:
    explicit tasksPublished(QWidget *parent = 0);
    ~tasksPublished();
    void EditUser(user myNewUser);
    void EditList(list newList);
    void showValue(list List);

private slots:
    void on_applyBtn_clicked();
    
    void on_main_clicked();
    
private:
    Ui::tasksPublished *ui;
    user myUser;
    list List;
    QList <taskPublisher> myTaskList;
};

#endif // TASKSPUBLISHED_H
