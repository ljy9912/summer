#ifndef LEADERTASK_H
#define LEADERTASK_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include "backup.h"
#include <QTabWidget>
#include <QListWidget>
#include <QMessageBox>

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
    void Show201(int i);
    void Show202(int i);
    void Show203(int i);
    void Show301(int i);
    void Show302(int i);

signals:
    void SendPage(int i);
    void SendPage301(int i,int j);

private slots:
    void GetPage201();
    void GetPage203confrm();
    void GetPage203prolong();
    void GetPage301save();
    void GetPage301confrm();
    void GetPage301end();
    void GetPage302save();
    void GetPage302confrm();
    void on_Main_clicked();

public:
    void OnClicked_201(int i);
    void OnClicked_203confrm(int i);
    void OnClicked_203prolong(int i);
    void OnClicked_301save(int i,int j);
    void OnClicked_301confrm(int i,int j);
    void OnClicked_301end(int i,int j);
    void OnClicked_302save(int i);
    void OnClicked_302confrm(int i);

private:
    Ui::leaderTask *ui;

    QList<taskLeader> m_taskList;
    QList<signUpForTranslater>* m_translaterList;
    QList<taskTranslater>* m_translaterTaskList;
    int m_iPage;
    int m_iTab;
    QLineEdit *m_yearEdit;
    QLineEdit *m_monthEdit;
    QLineEdit *m_dayEdit;
    QPushButton **m_confrmBtn;
    QPushButton* m_prolongBtn;
    QPushButton **m_saveBtn;
    QPushButton** m_endBtn;
    QTableWidget **m_table;
    QTextEdit** m_NewComment;
    QTextEdit* m_myResult;

    QString m_BtnStyle1;
    QString m_LabelStyle;
    QString m_LineEditStyle;
    QString m_TextEditStyle;
    QString m_TableWidgetStyle;
    QString m_BrowserStyle;

    void SetTableStyle(QTableWidget* table);
    void SetListStyle(QListWidget* list);

    void SetStyle();
    void SetTabStyle(QTabWidget* tab);
    void SetInformBox(QString text);
    void SetWarningBox(QString Text);
};

#endif // LEADERTASK_H
