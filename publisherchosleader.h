#ifndef PUBLISHERCHOSLEADER_H
#define PUBLISHERCHOSLEADER_H

#include <QDialog>
#include <QSqlTableModel>
#include "task.h"
#include "list.h"

namespace Ui {
class PublisherChosLeader;
}

class PublisherChosLeader : public QDialog
{
    Q_OBJECT

public:
    explicit PublisherChosLeader(QWidget *parent = 0);
    ~PublisherChosLeader();
    void EditIDUser(int iid);
    void setCurrentTable(int);

private:
    Ui::PublisherChosLeader *ui;
    QSqlTableModel *model;
    int iduser;
    task* newTasks;
};

#endif // PUBLISHERCHOSLEADER_H
