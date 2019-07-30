#ifndef CHECKERTASK_H
#define CHECKERTASK_H

#include <QDialog>
#include "taskleader.h"
#include "signupfortranslater.h"
#include "tasktranslater.h"
#include <QTextEdit>
#include <QTableWidget>
#include <QListWidget>
#include <QTabWidget>

namespace Ui {
class CheckerTask;
}

class CheckerTask : public QDialog
{
    Q_OBJECT

public:
    explicit CheckerTask(QWidget *parent = 0);
    ~CheckerTask();
    void OnClicked_301save(int i,int j);
    void OnClicked_301confrm(int i,int j);
    void OnClicked_301end(int i,int j);
    void ShowValue();
    void Show301(int i);

private slots:
    void on_Main_clicked();
    void GetPage301save();
    void GetPage301confrm();
    void GetPage301end();

    void on_exitBtn_clicked();

private:
    Ui::CheckerTask *ui;

    QList<taskLeader> m_taskList;
    QList<taskTranslater>* m_translaterTaskList;
    int m_iPage;
    int m_iTab;

    QPushButton **m_confrmBtn;
    QPushButton **m_saveBtn;
    QPushButton** m_endBtn;
    QTextEdit** m_NewComment;

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

#endif // CHECKERTASK_H
