#ifndef TASKWHOLE_H
#define TASKWHOLE_H

#include <QDialog>
#include "task.h"
#include "user.h"
#include "list.h"
#include <QList>
#include "message.h"

namespace Ui {
class taskPublish;
}

class taskPublish : public QDialog
{
    Q_OBJECT

public:
    explicit taskPublish(QWidget *parent = 0);
    ~taskPublish();
    void showValue();
    void EditTask(taskPublisher myNewTask);
    void EditUser(user myNewUser);
    void EditList(list newList);

private slots:
    void on_editBtn_clicked();

    void on_publishBtn_clicked();

private:
    Ui::taskPublish *ui;
    taskPublisher myTask;
    user myUser;
    list List;

signals:
    void PublishTask(int iID,QString intro,QList<Message> listMessage);
};

#endif // TASKWHOLE_H
