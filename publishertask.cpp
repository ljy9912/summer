#include "publishertask.h"
#include "ui_publishertask.h"
#include <QTableWidget>
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextBrowser>
#include <QTabWidget>

publisherTask::publisherTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::publisherTask)
{
    ui->setupUi(this);
}

publisherTask::~publisherTask()
{
    delete ui;
}

void publisherTask::EditUser(user myNewUser){
    m_myUser=myNewUser;
}

void publisherTask::EditList(list myNewList){
    m_List=myNewList;
}

void publisherTask::ShowValue(){
    m_taskList=m_List.SearchTaskForPublisher(m_myUser);
    for(int i=0;i<m_taskList.size();i++){
        connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
        switch(m_taskList[i].GetFlag()){
        case 101:
            Show101(i);
            break;
        case 102:
            Show102(i);
            break;
        case 401:
            Show401(i);
            break;
        default:
            ShowDefault(i);
        }
    }
}

void publisherTask::Show101(int i){
    ui->listWidget->insertItem(i,tr("<负责人报名火热进行中>%1").arg(m_taskList[i].GetIntroduction()));
    m_leaderList=m_List.SearchLeaderForTask(m_taskList[i]);
    QWidget *window=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    QLabel *label=new QLabel(tr("已报名负责人："));
    QTableWidget *table=new QTableWidget(m_leaderList.size(),4);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setWindowTitle("已报名负责人");
    QStringList header;
    header<<"账号"<<"用户名"<<"英语资历"<<"积分";
    table->setHorizontalHeaderLabels(header);
    for(int j=0;j<m_leaderList.size();j++){
        table->setItem(i,0,new QTableWidgetItem(QString::number(m_leaderList[j].GetID())));
        table->setItem(i,1,new QTableWidgetItem(m_leaderList[j].GetName()));
        table->setItem(i,2,new QTableWidgetItem(m_leaderList[j].GetEnglish()));
        table->setItem(i,3,new QTableWidgetItem(QString::number(m_leaderList[j].GetRewrdPoint())));
    }
    layout->addWidget(label);
    layout->addWidget(table);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);
}


void publisherTask::Show102(int i){
    ui->listWidget->insertItem(i,tr("<负责人报名完毕，请选择！>%1").arg(m_taskList[i].GetIntroduction()));
    m_leaderList=m_List.SearchLeaderForTask(m_taskList[i]);
    QWidget *window=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    QLabel *label=new QLabel(tr("已报名负责人："));
    QTableWidget *table=new QTableWidget(m_leaderList.size(),4);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setWindowTitle("已报名负责人");
    QStringList header;
    header<<"账号"<<"用户名"<<"英语资历"<<"积分";
    table->setHorizontalHeaderLabels(header);
    for(int j=0;j<m_leaderList.size();j++){
        table->setItem(i,0,new QTableWidgetItem(QString::number(m_leaderList[j].GetID())));
        table->setItem(i,1,new QTableWidgetItem(m_leaderList[j].GetName()));
        table->setItem(i,2,new QTableWidgetItem(m_leaderList[j].GetEnglish()));
        table->setItem(i,3,new QTableWidgetItem(QString::number(m_leaderList[j].GetRewrdPoint())));
    }
    layout->addWidget(label);
    layout->addWidget(table);
    QHBoxLayout *layoutName=new QHBoxLayout;
    QLabel *labelName=new QLabel(tr("账号："));
    QLineEdit *nameEdit=new QLineEdit;
    layoutName->addWidget(labelName);
    layoutName->addWidget(nameEdit);
    layout->addLayout(layoutName);
    QPushButton *confrmBtn=new QPushButton(tr("确定"));
    layout->addWidget(confrmBtn);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);
    if(confrmBtn->isEnabled()){
        int iIdLeader=nameEdit->text().toInt();
        int iNum=ui->listWidget->currentRow();
        int iNumInList=m_List.searchTaskInList(m_taskList[iNum]);
        m_List.TaskPublisher[iNumInList].EditLeader(iIdLeader);
        QMessageBox::information(this, tr("提示"),
                           tr("选择负责人成功！")
                          ,tr("确定"));
        int iSize=m_List.SignUpForLeader.size();
        for(int j=iSize-1;j>=0;i++){
            if(m_List.SignUpForLeader[j].GetIDTask()==m_taskList[iNum].GetID()){
                m_List.SignUpForLeader.removeAt(j);
            }
        }
        m_taskList[iNum].EditFlag(201);
        m_List.updateList(m_taskList[iNum]);
        m_List.TaskLeaderAppend(m_taskList[iNum]);
    }
}

void publisherTask::Show401(int i){
    ui->listWidget->insertItem(i,tr("<任务翻译完毕，请确认！>%1").arg(m_taskList[i].GetIntroduction()));
    QTabWidget *Tab=new QTabWidget;
    QLabel *intro=new QLabel(tr("%1").arg(m_taskList[i].GetIntroduction()));
    QTextBrowser *myTask=new QTextBrowser;
    myTask->setText(m_taskList[i].GetTask());
    QTextBrowser *myResult=new QTextBrowser;
    QLabel *inform1=new QLabel(tr("负责人酬金："));
    QLineEdit *leaderMoney=new QLineEdit;
    int iIDTask=m_taskList[i].GetID();
    for(int j=0;j<m_List.TaskLeader.size();j++){
        if(iIDTask==m_List.TaskLeader[j].GetID()){
            myResult->setText(m_List.TaskLeader[j].GetResult());
        }
    }
    QVBoxLayout *layout1=new QVBoxLayout;
    layout1->addWidget(intro);
    layout1->addWidget(myTask);
    layout1->addWidget(myResult);
    QWidget* window1=new QWidget;
    window1->setLayout(layout1);
    Tab->addTab(window1,tr("译文"));
    QHBoxLayout *leader=new QHBoxLayout;
    leader->addWidget(inform1);
    leader->addWidget(leaderMoney);
    QWidget *window2=new QWidget;
    QVBoxLayout *layout2=new QVBoxLayout();
    QLabel *inform2=new QLabel(tr("译者："));
    QList<taskTranslater> TaskTranslaterList=m_List.SearchTaskForTranslater
            (m_taskList[i].GetID());
    QTableWidget *table=new QTableWidget(TaskTranslaterList.size(),4);
    table->setWindowTitle("译者");
    QStringList header;
    header<<"账号"<<"译文"<<"成果"<<"酬金";
    table->setHorizontalHeaderLabels(header);
    for(int j=0;j<TaskTranslaterList.size();j++){
        table->setItem(i,0,new QTableWidgetItem(QString::number(TaskTranslaterList[j].GetID())));
        table->setItem(i,1,new QTableWidgetItem(TaskTranslaterList[j].GetTask()));
        table->setItem(i,2,new QTableWidgetItem(TaskTranslaterList[j].GetResult()));
    }
    layout2->addLayout(leader);
    layout2->addWidget(inform2);
    layout2->addWidget(table);
    QPushButton *confrmBtn=new QPushButton(tr("确定"));
    layout2->addWidget(confrmBtn);
    window2->setLayout(layout2);
    Tab->addTab(window2,tr("分配酬金"));
    layout2->addLayout(leader);
    layout2->addWidget(confrmBtn);
    if(confrmBtn->isEnabled()){
        //所有译者加5分

        //所有表中删除和该任务有关的所有数据
        int iIDLeader=m_taskList[i].GetLeader();
        int iNum=m_List.searchUserInList(iIDLeader);
        //将负责人的余额加入表中
        m_List.User[iNum].AddMoney(leaderMoney->text().toDouble());//发消息确认
        //负责人加10分
        m_List.User[iNum].AddPoint(10);
        for(int j=0;j<TaskTranslaterList.size();j++){
            iNum=m_List.searchUserInList(TaskTranslaterList[j].GetTranslater());
            //将译者余额存入表中
            m_List.User[iNum].AddMoney(table->item(j,3)->text().toDouble());//发消息确认
            //译者加5分
            m_List.User[iNum].AddPoint(5);
        }
        m_List.Delete(m_taskList[i].GetID());
    }
}

void publisherTask::ShowDefault(int i){
    ui->listWidget->insertItem(i,tr("<翻译任务进行中！>%1").arg(m_taskList[i].GetIntroduction()));
    QLabel *inform=new QLabel(tr("翻译任务正在火热进行中，请耐心等待！"));
    QWidget *window=new QWidget();
    QLabel *taskClass;
    if(m_taskList[i].GetTaskClass()==0){
        taskClass=new QLabel(tr("翻译性质：中译英"));
    }
    else{
        taskClass=new QLabel(tr("翻译性质：英译中"));
    }
    QLabel *intro=new QLabel(tr("任务简介：%1").arg(m_taskList[i].GetIntroduction()));
    QLabel *tasks=new QLabel(tr("翻译内容：%1").arg(m_taskList[i].GetTask()));
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(m_taskList[i].GetTime()));
    QLabel *date=new QLabel(tr("负责人报名截至日期：%1年%2月%3日").arg(m_taskList[i].GetLeaderYear()).arg(m_taskList[i].GetLeaderMonth()).arg(m_taskList[i].GetLeaderDay()));
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(m_taskList[i].GetMoney()));
    QVBoxLayout *layout=new QVBoxLayout();
    layout->addWidget(inform);
    layout->addWidget(taskClass);
    layout->addWidget(intro);
    layout->addWidget(tasks);
    layout->addWidget(time);
    layout->addWidget(date);
    layout->addWidget(money);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);
}

void publisherTask::on_main_clicked()
{
    MainWindow *r=new MainWindow;
    r->EditList(m_List);
    r->EditUser(m_myUser);
    r->show();
    close();
}
