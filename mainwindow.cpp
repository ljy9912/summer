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
    userInfo *r=new userInfo;
    r->showValue(myUser);
    r->EditUser(myUser);
    r->EditList(List);
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
void MainWindow::EditUser(user myNewUser){
    myUser=myNewUser;
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
    taskNew *r=new taskNew;
    r->EditUser(myUser);
    r->EditList(List);
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
    tasksPublished *r=new tasksPublished;
    r->EditUser(myUser);
    r->EditList(List);
    r->showValue(List);
    r->show();
    close();
}

void MainWindow::on_myTaskBtn_clicked()
{
    
}

void MainWindow::EditList(list newList){
    List=newList;
}

void MainWindow::on_myTableBtn_clicked()
{

    close();
}



void MainWindow::on_exitBtn_clicked()
{
    SqlQuery query;
    query.saveUser(List.User);
    query.saveTasks(List.TaskPublisher);
    query.saveSignUpForLeader(List.SignUpForLeader);
    query.saveSignUpForTranslater(List.SignUpForTranslater);
    query.saveTaskLeader(List.TaskLeader);
    query.saveTaskTranslater(List.TaskTranslater);
    close();
}

void MainWindow::on_publisher_clicked()
{
    publisherTask *r=new publisherTask;
    r->EditUser(myUser);
    r->EditList(List);
    r->ShowValue();
    r->show();
    close();
}
