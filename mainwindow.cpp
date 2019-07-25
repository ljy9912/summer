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
    userInfo* r=new userInfo;
    r->showValue(m_BackUp.m_User);
    r->EditBackUp(m_BackUp);
    r->show();
    close();
}

/*************************************************************************
【函数名称】EditUser
【函数功能】 从外部改变类内myUser的参数
【参数】user myNewUser
【返回值】 无
【开发者及日期】李佳芸 2019.7.1
【更改记录】
*************************************************************************/
void MainWindow::EditBackUp(BackUp myBackUp){
    m_BackUp=myBackUp;
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
    taskNew* r=new taskNew;
    r->EditBackUp(m_BackUp);
    r->show();
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
    tasksPublished* r=new tasksPublished;
    r->EditBackUp(m_BackUp);
    r->showValue(m_BackUp.m_List);
    r->show();
    close();
}

void MainWindow::on_myTaskBtn_clicked()
{
    translaterTask* r=new translaterTask;
    r->EditBackUp(m_BackUp);
    r->ShowValue();
    r->show();
    close();
}

void MainWindow::on_myTableBtn_clicked()
{
    leaderTask* r=new leaderTask;
    r->EditBackUp(m_BackUp);
    r->ShowValue();
    r->show();
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
    publisherTask* r=new publisherTask;
    r->EditBackUp(m_BackUp);
    r->ShowValue();
    r->show();
    close();
}

void MainWindow::on_MessageBox_clicked()
{
    MessageBox* r=new MessageBox;
    r->EditBackUp(m_BackUp);
    r->ShowMessage();
    r->show();
    close();
}

void MainWindow::on_exitBtn_clicked()
{
    SqlQuery query;
    query.saveUser(m_BackUp.m_List.User);
    query.saveTasks(m_BackUp.m_List.TaskPublisher);
    query.saveSignUpForLeader(m_BackUp.m_List.SignUpForLeader);
    query.saveSignUpForTranslater(m_BackUp.m_List.SignUpForTranslater);
    query.saveTaskLeader(m_BackUp.m_List.TaskLeader);
    query.saveTaskTranslater(m_BackUp.m_List.TaskTranslater);
    query.saveMessage(m_BackUp.m_List.message);
    close();
}
