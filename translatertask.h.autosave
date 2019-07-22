#ifndef TRANSLATERTASK_H
#define TRANSLATERTASK_H

#include <QDialog>
#include "list.h"

namespace Ui {
class translaterTask;
}

class translaterTask : public QDialog
{
    Q_OBJECT

public:
    explicit translaterTask(QWidget *parent = 0);
    ~translaterTask();
    void EditList(list myNewList);
    void EditUser(user myNewUser);
    void ShowValue();

private slots:
    void on_main_clicked();

private:
    Ui::translaterTask *ui;
    list m_List;
    user m_User;
    QList<taskTranslater> m_taskList;
};

#endif // TRANSLATERTASK_H
