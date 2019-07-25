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
    void EditBackUp(BackUp myBackUp);

private slots:
    void on_pushButton_clicked();
    void on_Publish_clicked();

    void on_getTask_clicked();

    void on_myTableBtn_clicked();
    
    void on_publisher_clicked();

    void on_myTaskBtn_clicked();
    
private:
    
    Ui::MainWindow *ui;
    BackUp m_BackUp;
};

#endif // MAINWINDOW_H
