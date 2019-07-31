#ifndef TASKSPUBLISHED_H
#define TASKSPUBLISHED_H

#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include "backup.h"
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidget>

namespace Ui {
class tasksPublished;
}

class tasksPublished : public QDialog
{
    Q_OBJECT

public:
    explicit tasksPublished(QWidget *parent = nullptr);
    ~tasksPublished();

    void ShowValue();
    void ShowValue101(int i);
    void ShowValue102(int i);
    void ShowValue201(int i);
    void ShowValue202(int i);
    void ShowValue301(int i);

    void OnClicked101apply(int i);
    void OnClicked101check(int i);
    void OnClicked202(int i);


private slots:


    void GetPage101apply();
    void GetPage101check();

    void GetPage202();

    void on_Main_clicked();

    void on_exitBtn_clicked();

private:
    Ui::tasksPublished *ui;

    QPushButton* m_applyBtn;
    QPushButton* m_CheckerBtn;
    void SetTableStyle(QTableWidget* table);
    void SetListStyle(QListWidget* list);
    void SetTabStyle(QTabWidget* tab);
    void SetWarningBox(QString Text);
    void SetInformBox(QString Text);

    void SetStyle();
    QString m_BtnStyle1;
    QString m_LabelStyle;
    QString m_LineEditStyle;
    QString m_TextEditStyle;
    QString m_TableWidgetStyle;
    QString m_BrowserStyle;

signals:
    void SignUpForLeader(int iID,QList<Message>& myMessage);
};

#endif // TASKSPUBLISHED_H
