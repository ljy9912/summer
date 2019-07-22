#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include <QList>
#include "taskpublisher.h"
#include "list.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void EditUser(user myNewUser);
    void EditList(list newList);

private slots:
    void on_pushButton_clicked();
    void on_Publish_clicked();

    void on_getTask_clicked();

    void on_myTableBtn_clicked();
    
    void on_exitBtn_clicked();
    
    void on_publisher_clicked();
    
private:
    void on_myTaskBtn_clicked();
    
    Ui::MainWindow *ui;
    user myUser;
    list List;
};

#endif // MAINWINDOW_H
