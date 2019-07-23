#ifndef LEADERTASK_H
#define LEADERTASK_H

#include <QDialog>
#include "list.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>

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

signals:
    void SendPage(int i);

private slots:
    void on_main_clicked();
    void GetPage201();
    void GetPage203();
    void GetPage301save();
    void GetPage301confrm();
    void GetPage301end();

    void OnClicked_201(int i);
    void OnClicked_203(int i);
    void OnClicked_301save(int i);
    void OnClicked_301confrm(int i);
    void OnClicked_301end(int i);

private:
    Ui::leaderTask *ui;
    user m_myUser;
    list m_List;
    QList<taskLeader> m_taskList;
    QList<signUpForTranslater> m_translaterList;
    QList<taskTranslater> m_translaterTaskList;
    int m_iPage;
    QLineEdit *m_yearEdit;
    QLineEdit *m_monthEdit;
    QLineEdit *m_dayEdit;
    QPushButton *m_confrmBtn;
    QPushButton *m_saveBtn;
    QPushButton* m_endBtn;
    QTableWidget *m_table;
    QTextEdit* m_NewComment;
};

#endif // LEADERTASK_H
