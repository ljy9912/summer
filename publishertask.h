#ifndef PUBLISHERTASK_H
#define PUBLISHERTASK_H

#include <QDialog>
#include "backup.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>

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
    void on_main_clicked();
    void OnClicked(int i);
    void OnClicked401(int i);

    void GetPage102();
    void GetPage401();


private:
    Ui::publisherTask *ui;

    QList<taskPublisher> m_taskList;
    QList<signUpForLeader> m_leaderList;
    int m_Page;

    QLineEdit *m_nameedit;
    QPushButton *m_confrmBtn;
    QList<taskTranslater> m_TaskTranslaterList;
    QTableWidget* m_table;
    QLineEdit* m_leaderMoney;
};

#endif // PUBLISHERTASK_H
