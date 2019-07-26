#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "user.h"
#include "userinfo.h"
#include "logindialog.h"
#include "tasknew.h"
#include "taskspublished.h"
#include "sqlquery.h"
#include "publishertask.h"
#include "leadertask.h"
#include "translatertask.h"
#include "sqlquery.h"
#include "messagebox.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;

}

/*************************************************************************
【函数名称】on_pushButton_clicked
【函数功能】 当pushButton被单击之后，进入显示用户信息的窗口，并传递用户id的参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void MainWindow::on_pushButton_clicked()
{
    userInfo r;
    r.showValue(g_backUp.m_User);
    r.exec();
    close();
}


/*************************************************************************
【函数名称】on_Publish_clicked
【函数功能】 当Publish被按下后，打开taskNew页面并且传递id参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.13
【更改记录】
*************************************************************************/
void MainWindow::on_Publish_clicked()
{
    taskNew r;
    r.exec();
    close();
}

/*************************************************************************
【函数名称】on_getTask_clicked
【函数功能】 在按下getTask之后，打开tasksPublished页面，并且传递id参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void MainWindow::on_getTask_clicked()
{
    tasksPublished r;
    r.ShowValue();
    r.exec();
    close();
}

void MainWindow::on_myTaskBtn_clicked()
{
    translaterTask r;
    r.ShowValue();
    r.exec();
    close();
}

void MainWindow::on_myTableBtn_clicked()
{
    leaderTask r;
    r.ShowValue();
    r.exec();
    close();
}

/*************************************************************************
【函数名称】on_publisher_clicked
【函数功能】在点击publisher之后，显示发布者任务页面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void MainWindow::on_publisher_clicked()
{
    publisherTask r;
    r.ShowValue();
    r.exec();
    close();
}

void MainWindow::on_MessageBox_clicked()
{
    MessageBox r;
    r.ShowMessage();
    r.exec();
    close();
}

void MainWindow::on_exitBtn_clicked()
{
    SqlQuery query;
    query.saveUser(g_backUp.m_List.User);
    query.saveTasks(g_backUp.m_List.TaskPublisher);
    query.saveSignUpForLeader(g_backUp.m_List.SignUpForLeader);
    query.saveSignUpForTranslater(g_backUp.m_List.SignUpForTranslater);
    query.saveTaskLeader(g_backUp.m_List.TaskLeader);
    query.saveTaskTranslater(g_backUp.m_List.TaskTranslater);
    query.saveMessage(g_backUp.m_List.message);
    close();
}
