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

tasksPublished::tasksPublished(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tasksPublished)
{
    ui->setupUi(this);

}


tasksPublished::~tasksPublished()
{
    delete ui;
}


void tasksPublished::EditUser(user myNewUser){
    myUser=myNewUser;
}

void tasksPublished::on_applyBtn_clicked()
{
    if(myUser.GetRewrdPoint()<100){
        QMessageBox::warning(this, tr("提示"),
                           tr("积分不足，请努力完成更多翻译任务后再来申请吧！")
                          ,tr("确定"));
    }
    else{
        int row=ui->listWidget->currentRow();
        int idtask=myTaskList[row].GetID();
        signUpForLeader leader(myUser,idtask);
        List.SignUpForLeader.append(leader);
        QMessageBox::information(this, tr("提示"),
                           tr("报名成功！")
                          ,tr("确定"));
    }
}

void tasksPublished::on_main_clicked()
{
    MainWindow *r=new MainWindow;
    r->EditUser(myUser);
    r->EditList(List);
    r->show();
    close();
}

void tasksPublished::EditList(list newList){
    List=newList;
}

void tasksPublished::showValue(list List){
    for(int i=0;i<List.TaskPublisher.size();i++)
    {
        if(List.TaskPublisher[i].GetFlag()==101||List.TaskPublisher[i].GetFlag()==202){
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
        QLabel *tasks=new QLabel(tr("翻译内容：%1").arg(myTaskList[i].GetTask()));
        QLabel *time=new QLabel(tr("任务周期：%1天").arg(myTaskList[i].GetTime()));
        QLabel *date=new QLabel(tr("负责人报名截至日期：%1年%2月%3日").arg(myTaskList[i].GetLeaderYear()).arg(myTaskList[i].GetLeaderMonth()).arg(myTaskList[i].GetLeaderDay()));
        QLabel *money=new QLabel(tr("任务总金额：%1元").arg(myTaskList[i].GetMoney()));
        QVBoxLayout *layout=new QVBoxLayout();
        layout->addWidget(taskClass);
        layout->addWidget(intro);
        layout->addWidget(tasks);
        layout->addWidget(time);
        layout->addWidget(date);
        layout->addWidget(money);
        window->setLayout(layout);
        ui->stackedWidget->addWidget(window);

        connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    }
}
