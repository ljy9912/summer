#ifndef LEADERTABLE_H
#define LEADERTABLE_H

#include <QDialog>
#include "list.h"
#include <QTableWidget>

namespace Ui {
class leaderTable;
}

class leaderTable : public QDialog
{
    Q_OBJECT

public:
    explicit leaderTable(QWidget *parent = 0);
    ~leaderTable();
    void EditList(list newList);
    void EditUser(user newUser);
    void showValue();

private slots:

    void on_confrmBtn_clicked();

private:
    Ui::leaderTable *ui;
    list List;
    user myUser;
    QTableWidget *table;
    int sum;
    QList<task> myTaskList;
};

#endif // LEADERTABLE_H
