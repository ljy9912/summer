#ifndef TASKPUBLISHEDIT_H
#define TASKPUBLISHEDIT_H

#include <QDialog>
#include "backup.h"

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


private slots:
    void on_canclBtn_clicked();

    void on_confrmBtn_clicked();

private:
    Ui::taskPublishEdit *ui;
    taskPublisher myTask;

    bool IsEmpty();

};

#endif // TASKPUBLISHEDIT_H
