#include "taskpublish.h"
#include "ui_taskpublish.h"
#include "QMessageBox"
#include "tasknew.h"
#include "taskpublishedit.h"
#include "task.h"
#include "mainwindow.h"
#include <QDate>
#include "backup.h"
#include "sqlquery.h"


taskPublish::taskPublish(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taskPublish)
{
    ui->setupUi(this);
    SetStyle();
}

taskPublish::~taskPublish()
{
    delete ui;
    ui=NULL;
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
    ui->taskBrowser->setText(myTask.GetTask());
    ui->introBrowser->setText(myTask.GetIntroduction());
    ui->time->setText(tr("任务周期：%1").arg(myTask.GetTime()));
    ui->leaderDate->setText(tr("负责人报名截止时间：%1年%2月%3日").arg(myTask.GetLeaderYear())
                            .arg(myTask.GetLeaderMonth()).arg(myTask.GetLeaderDay()));
    ui->money->setText(tr("任务总金额：%1").arg(myTask.GetMoney()));
    ui->title->setText(tr("翻译标题：%1").arg(myTask.GetTitle()));
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
    close();
    taskPublishEdit r;
    r.EditTask(myTask);
    r.showValue();
    r.exec();

}


/*************************************************************************
【函数名称】EditTask
【函数功能】外部更改该类的task
【参数】int iid
【返回值】 无
【开发者及日期】李佳芸 2019.7.15
【更改记录】
*************************************************************************/
void taskPublish::EditTask(taskPublisher myNewTask){
    myTask=myNewTask;
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
    SetInformBox("任务已发布！");

    g_backUp.TaskPublish(myTask);
    close();
    MainWindow r;
    r.exec();
}

void taskPublish::SetStyle(){
    m_BtnStyle1="QPushButton{background-color:rgb(0, 188, 212);\
            color: white;   border-radius: 10px; \
            border-style: outset;}"
           "QPushButton:hover{background-color:#198fb6; color: white;}"
          "QPushButton:pressed{background-color:#3F51B5;\
                           border-style: inset; }";
    ui->publishBtn->setStyleSheet(m_BtnStyle1);
    ui->editBtn->setStyleSheet(m_BtnStyle1);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
}

void taskPublish::SetInformBox(QString Text){
    QMessageBox message(this);
    message.setIconPixmap(QPixmap(":/images/information.svg"));
    message.setStyleSheet("font:12pt,\"等线\";background:white;");
    message.setText(Text);
    message.setWindowTitle("提示");
    QPushButton* ysBtn=new QPushButton("确定");
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    message.addButton(ysBtn,QMessageBox::AcceptRole);
    message.exec();
}
