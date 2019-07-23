#ifndef TRANSLATERTASK_H
#define TRANSLATERTASK_H

#include <QDialog>
#include "list.h"
#include <QTextEdit>
#include <QPushButton>

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

signals:
    void SendPage(int i);

private slots:
    void on_main_clicked();
    void OnClicked_301save(int i);
    void OnClicked_301confrm(int i);
    void GetPage301save();
    void GetPage301confrm();

private:
    Ui::translaterTask *ui;
    list m_List;
    user m_User;
    QList<taskTranslater> m_taskList;
    int m_iPage;

    QTextEdit *m_result;
    QPushButton *m_saveBtn;
    QPushButton *m_confrmBtn;
};

#endif // TRANSLATERTASK_H
