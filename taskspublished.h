#ifndef TASKSPUBLISHED_H
#define TASKSPUBLISHED_H

#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include "backup.h"
#include <QPushButton>

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
    
    void on_main_clicked();

    void GetPage101();

    void GetPage202();
    
private:
    Ui::tasksPublished *ui;

    QPushButton* m_applyBtn;

signals:
    void SignUpForLeader(int iID,QList<Message>& myMessage);
};

#endif // TASKSPUBLISHED_H
