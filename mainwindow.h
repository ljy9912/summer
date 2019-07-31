#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include <QList>
#include "taskpublisher.h"
#include "backup.h"
#include <QDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
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

    void on_Checker_clicked();

    void SetStyle();

private:

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
