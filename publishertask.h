#ifndef PUBLISHERTASK_H
#define PUBLISHERTASK_H

#include <QDialog>
#include "backup.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QListWidget>

namespace Ui {
class publisherTask;
}

class publisherTask : public QDialog
{
    Q_OBJECT

public:
    explicit publisherTask(QWidget *parent = 0);
    ~publisherTask();
    void ShowValue();

    void Show101(int i);
    void Show102(int i);
    void Show401(int i);
    void ShowDefault(int i);

private slots:
    void OnClicked102confrm(int i);
    void OnClicked102prolong(int i);
    void OnClicked401(int i);

    void GetPage102confrm();
    void GetPage102prolong();
    void GetPage401();

    void on_Main_clicked();

private:
    Ui::publisherTask *ui;

    QList<taskPublisher> m_taskList;
    QList<signUpForLeader> m_leaderList;
    int m_Page;

    QLineEdit *m_nameedit;
    QPushButton *m_confrmBtn;
    QPushButton* m_prolongBtn;
    QList<taskTranslater>* m_TaskTranslaterList;
    QTableWidget* m_table;
    QLineEdit* m_leaderMoney;

    QString m_BtnStyle1;
    QString m_LabelStyle;
    QString m_LineEditStyle;
    QString m_TextEditStyle;
    QString m_TableWidgetStyle;
    QString m_BrowserStyle;

    void SetTableStyle(QTableWidget* table);
    void SetListStyle(QListWidget* list);
    void SetTabStyle(QTabWidget* tab);

    void SetStyle();
};

#endif // PUBLISHERTASK_H
