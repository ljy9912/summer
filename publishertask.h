#ifndef PUBLISHERTASK_H
#define PUBLISHERTASK_H

#include <QDialog>
#include "user.h"
#include "list.h"
#include <QLineEdit>
#include <QPushButton>

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
    void EditUser(user myNewUser);
    void EditList(list myNewList);
    void Show101(int i);
    void Show102(int i);
    void Show401(int i);
    void ShowDefault(int i);

private slots:
    void on_main_clicked();
    void OnClicked(int i);
    void getPage();

signals:
    void SendPage(int m_page);

private:
    Ui::publisherTask *ui;
    user m_myUser;
    list m_List;
    QList<taskPublisher> m_taskList;
    QList<signUpForLeader> m_leaderList;
    int m_Page;

    QLineEdit *m_nameedit;
    QPushButton *m_confrmBtn;
};

#endif // PUBLISHERTASK_H
