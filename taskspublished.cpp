#include "taskspublished.h"
#include "ui_taskspublished.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "task.h"
#include <QLabel>
#include <QVBoxLayout>
#include <mainwindow.h>
#include <QMessageBox>
#include "signupforleader.h"
#include <QTextBrowser>
#include "backup.h"
#include "sqlquery.h"

tasksPublished::tasksPublished(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tasksPublished)
{
    ui->setupUi(this);

}


tasksPublished::~tasksPublished()
{
    delete ui;
    SqlQuery query;
    query.saveUser(m_BackUp.m_List.User);
    query.saveTasks(m_BackUp.m_List.TaskPublisher);
    query.saveSignUpForLeader(m_BackUp.m_List.SignUpForLeader);
    query.saveSignUpForTranslater(m_BackUp.m_List.SignUpForTranslater);
    query.saveTaskLeader(m_BackUp.m_List.TaskLeader);
    query.saveTaskTranslater(m_BackUp.m_List.TaskTranslater);
    query.saveMessage(m_BackUp.m_List.message);
}

/*************************************************************************
【函数名称】EditUser
【函数功能】外部更改user类
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void tasksPublished::EditBackUp(BackUp myBackUp){
    m_BackUp=myBackUp;
}

/*************************************************************************
【函数名称】on_applyBtn_clicked
【函数功能】当点击applyBtn后，查询用户是否有资格申请，并进行相关数据存储工作
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void tasksPublished::on_applyBtn_clicked()
{
    int row=ui->listWidget->currentRow();
    if(myTaskList[row].GetFlag()==101){
        if(m_BackUp.m_User.GetRewrdPoint()<100){
            QMessageBox::warning(this, tr("提示"),
                               tr("积分不足，请努力完成更多翻译任务后再来申请吧！")
                              ,tr("确定"));
        }
        else{
            int idtask=myTaskList[row].GetID();
            int idthis=m_BackUp.m_List.SignUpForLeader.size();
            signUpForLeader leader(m_BackUp.m_User,idtask,idthis);
            m_BackUp.m_List.SignUpForLeader.append(leader);
            QMessageBox::information(this, tr("提示"),
                               tr("报名成功！")
                              ,tr("确定"));
            BackUp myMessage;
            myMessage.SignUpForLeader(m_BackUp.m_User.GetID(),idtask);
        }
    }
    else if(myTaskList[row].GetFlag()==202){
        int idtask=myTaskList[row].GetID();
        int idthis=m_BackUp.m_List.SignUpForTranslater.size();
        signUpForTranslater translater(m_BackUp.m_User,idtask,idthis);
        m_BackUp.m_List.SignUpForTranslater.append(translater);
        QMessageBox::information(this, tr("提示"),
                           tr("报名成功！")
                          ,tr("确定"));
    }
}

/*************************************************************************
【函数名称】on_main_clicked
【函数功能】点击main之后，显示mainwindow
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void tasksPublished::on_main_clicked()
{
    MainWindow r;
    r.EditBackUp(m_BackUp);
    r.show();
    close();
}


/*************************************************************************
【函数名称】showValue
【函数功能】显示界面
【参数】list m_BackUp.m_List
【返回值】无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void tasksPublished::showValue(list  List){
    for(int i=0;i<List.TaskPublisher.size();i++)
    {
        if(List.TaskPublisher[i].GetFlag()==101
                ||List.TaskPublisher[i].GetFlag()==202){
            myTaskList.append(List.TaskPublisher[i]);
        }
    }

    for(int i=0;i<myTaskList.size();i++){
        ui->listWidget->insertItem(i,tr("%1").arg(myTaskList[i].GetIntroduction()));
        QWidget *window=new QWidget();
        QLabel *taskClass;
        if(myTaskList[i].GetTaskClass()==0){
            taskClass=new QLabel(tr("翻译性质：中译英"));
        }
        else{
            taskClass=new QLabel(tr("翻译性质：英译中"));
        }
        QLabel *intro=new QLabel(tr("任务简介：%1").arg(myTaskList[i].GetIntroduction()));
        QLabel *tasks=new QLabel(tr("翻译内容："));
        QTextBrowser *myTask=new QTextBrowser;
        myTask->setText(myTaskList[i].GetTask());
        QLabel *time=new QLabel(tr("任务周期：%1天").arg(myTaskList[i].GetTime()));
        QLabel *date=new QLabel(tr("负责人报名截至日期：%1年%2月%3日").arg(myTaskList[i].GetLeaderYear()).arg(myTaskList[i].GetLeaderMonth()).arg(myTaskList[i].GetLeaderDay()));
        QLabel *money=new QLabel(tr("任务总金额：%1元").arg(myTaskList[i].GetMoney()));
        QVBoxLayout *layout=new QVBoxLayout();
        layout->addWidget(taskClass);
        layout->addWidget(intro);
        layout->addWidget(tasks);
        layout->addWidget(myTask);
        layout->addWidget(time);
        layout->addWidget(date);
        layout->addWidget(money);
        window->setLayout(layout);
        ui->stackedWidget->addWidget(window);

        connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    }
}
