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
    explicit tasksPublished(QWidget *parent = 0);
    ~tasksPublished();

    void ShowValue();
    void ShowValue101(int i);
    void ShowValue102(int i);
    void ShowValue201(int i);
    void ShowValue202(int i);
    void ShowValue203(int i);

    void OnClicked101(int i);
    void OnClicked202(int i);


private slots:


    void GetPage101();

    void GetPage202();

    void on_Main_clicked();

private:
    Ui::tasksPublished *ui;

    QPushButton* m_applyBtn;
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
