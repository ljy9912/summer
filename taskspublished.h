#ifndef TASKSPUBLISHED_H
#define TASKSPUBLISHED_H

#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include "backup.h"

namespace Ui {
class tasksPublished;
}

class tasksPublished : public QDialog
{
    Q_OBJECT

public:
    explicit tasksPublished(QWidget *parent = 0);
    ~tasksPublished();
    void EditBackUp(BackUp myBackUp);
    void showValue(list List);

private slots:
    void on_applyBtn_clicked();
    
    void on_main_clicked();
    
private:
    Ui::tasksPublished *ui;
    BackUp m_BackUp;
    QList <taskPublisher> myTaskList;

signals:
    void SignUpForLeader(int iID,QList<Message>& myMessage);
};

#endif // TASKSPUBLISHED_H
