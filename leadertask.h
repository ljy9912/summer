#ifndef LEADERTASK_H
#define LEADERTASK_H

#include <QDialog>
#include "list.h"

namespace Ui {
class leaderTask;
}

class leaderTask : public QDialog
{
    Q_OBJECT

public:
    explicit leaderTask(QWidget *parent = 0);
    ~leaderTask();
    void ShowValue();
    void EditUser(user myNewUser);
    void EditList(list myNewList);
    void Show201(int i);
    void Show202(int i);
    void Show203(int i);
    void Show301(int i);
    void Show302(int i);

private slots:
    void on_main_clicked();

private:
    Ui::leaderTask *ui;
    user m_myUser;
    list m_List;
    QList<taskLeader> m_taskList;
    QList<signUpForTranslater> m_translaterList;
};

#endif // LEADERTASK_H
