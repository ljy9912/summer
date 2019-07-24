#include "taskpublish.h"
#include "ui_taskpublish.h"
#include "QMessageBox"
#include "tasknew.h"
#include "taskpublishedit.h"
#include "task.h"
#include "mainwindow.h"
#include <QDate>
#include "messagebackup.h"

taskPublish::taskPublish(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taskPublish)
{
    ui->setupUi(this);
}

taskPublish::~taskPublish()
{
    delete ui;
}

/*************************************************************************
【函数名称】showValue
【函数功能】通过对象task的传递的信息显示任务的信息方便用户编辑
【参数】int iid
【返回值】 无
【开发者及日期】李佳芸 2019.7.15
【更改记录】
*************************************************************************/
void taskPublish::showValue(){

    if(myTask.GetTaskClass()==0){
        ui->taskclass->setText("翻译性质：中译英");
    }
    else{
        ui->taskclass->setText("翻译性质：英译中");
    }
    ui->task->setText(tr("翻译任务：%1").arg(myTask.GetTask()));
    ui->intro->setText(tr("任务简介：%1").arg(myTask.GetIntroduction()));
    ui->time->setText(tr("任务周期：%1").arg(myTask.GetTime()));
    ui->leaderYear->setText(tr("%1年").arg(myTask.GetLeaderYear()));
    ui->leaderMonth->setText(tr("%1月").arg(myTask.GetLeaderMonth()));
    ui->leaderDay->setText(tr("%1日").arg(myTask.GetLeaderDay()));
    ui->money->setText(tr("任务总金额：%1").arg(myTask.GetMoney()));
}

/*************************************************************************
【函数名称】on_editBtn_clicked
【函数功能】当按下editBtn后显示任务信息编辑页面，并且传递idtask和iduser参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.15
【更改记录】
*************************************************************************/
void taskPublish::on_editBtn_clicked()
{
    taskPublishEdit *r=new taskPublishEdit;
    r->EditTask(myTask);
    r->EditUser(myUser);
    r->EditList(List);
    r->showValue();
    r->show();
    close();
}


/*************************************************************************
【函数名称】EditIDTask
【函数功能】外部更改该类的idtask
【参数】int iid
【返回值】 无
【开发者及日期】李佳芸 2019.7.15
【更改记录】
*************************************************************************/
void taskPublish::EditTask(taskPublisher myNewTask){
    myTask=myNewTask;
}

/*************************************************************************
【函数名称】EditIDUser
【函数功能】外部更改该类的iduser
【参数】int iid
【返回值】 无
【开发者及日期】李佳芸 2019.7.15
【更改记录】
*************************************************************************/
void taskPublish::EditUser(user myNewUser){
    myUser=myNewUser;
}


/*************************************************************************
【函数名称】on_publishBtn_clicked
【函数功能】当按下publishBtn后，告知用户任务已经发布并且在数据库中改变任务状态，设置flag为1
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.15
【更改记录】2019.7.17 将存入数据库的操作封装至task类中
*************************************************************************/
void taskPublish::on_publishBtn_clicked()
{
    QMessageBox::information(this, tr("提示"),
                       tr("任务已发布！")
                      ,tr("确定"));
    myTask.EditFlag(101);
    QDate time=QDate::currentDate();
    myTask.EditStartYear(time.year());
    myTask.EditStartMonth(time.month());
    myTask.EditStartDay(time.day());
    List.updateList(myTask);
    MainWindow *r=new MainWindow();
    r->EditUser(myUser);
    r->EditList(List);
    r->show();
    close();
    MessageBackUp* myMessage;
    connect(this,SIGNAL(PublishTask(int,QString,QList<Message>)),myMessage,SLOT(PublishTask(int,QString,QList<Message>)));
    emit PublishTask(myUser.GetID(),myTask.GetIntroduction(),List.message);
}

void taskPublish::EditList(list newList){
    List=newList;
}
