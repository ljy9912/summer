#ifndef PUBLISHNEW_H
#define PUBLISHNEW_H

#include <QDialog>
#include "taskpublish.h"
#include "task.h"
#include "backup.h"

namespace Ui {
class taskNew;
}

class taskNew : public QDialog
{
    Q_OBJECT

public:
    explicit taskNew(QWidget *parent = 0);
    ~taskNew();
    void EditBackUp(BackUp myBackUp);
    void showValue(taskPublisher);
    void EditIDTask(int iid);

private slots:
    void on_canclBtn_clicked();

    void on_confrmBtn_clicked();

    void on_main_clicked();
    
private:
    Ui::taskNew *ui;
    BackUp m_BackUp;
    taskPublisher myTask;
    list List;
};

#endif // PUBLISHNEW_H
