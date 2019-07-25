#ifndef LEADERTASK_H
#define LEADERTASK_H

#include <QDialog>
#include "list.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include "backup.h"

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
    void EditBackUp(BackUp myBackUp);
    void Show201(int i);
    void Show202(int i);
    void Show203(int i);
    void Show301(int i);
    void Show302(int i);

signals:
    void SendPage(int i);
    void SendPage301(int i,int j);

private slots:
    void on_main_clicked();
    void GetPage201();
    void GetPage203();
    void GetPage301save();
    void GetPage301confrm();
    void GetPage301end();
    void GetPage302save();
    void GetPage302confrm();
public:
    void OnClicked_201(int i);
    void OnClicked_203(int i);
    void OnClicked_301save(int i,int j);
    void OnClicked_301confrm(int i,int j);
    void OnClicked_301end(int i,int j);
    void OnClicked_302save(int i);
    void OnClicked_302confrm(int i);

private:
    Ui::leaderTask *ui;
    BackUp m_BackUp;
    QList<taskLeader> m_taskList;
    QList<signUpForTranslater> m_translaterList;
    QList<taskTranslater> m_translaterTaskList;
    int m_iPage;
    int m_iTab;
    QLineEdit *m_yearEdit;
    QLineEdit *m_monthEdit;
    QLineEdit *m_dayEdit;
    QPushButton **m_confrmBtn;
    QPushButton **m_saveBtn;
    QPushButton** m_endBtn;
    QTableWidget **m_table;
    QTextEdit** m_NewComment;
    QTextEdit* m_myResult;
};

#endif // LEADERTASK_H
