#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include <QList>
#include "taskpublisher.h"
#include "backup.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_Publish_clicked();

    void on_getTask_clicked();

    void on_myTableBtn_clicked();
    
    void on_publisher_clicked();

    void on_myTaskBtn_clicked();
    
    void on_MessageBox_clicked();

    void on_exitBtn_clicked();

private:
    
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
