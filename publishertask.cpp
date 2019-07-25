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
#include "sqlquery.h"

publisherTask::publisherTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::publisherTask)
{
    ui->setupUi(this);
}

publisherTask::~publisherTask()
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
【函数功能】外部更改myUser
【参数】user myNewUser
【返回值】 无
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
void publisherTask::EditBackUp(BackUp myBackUp){
    m_BackUp=myBackUp;
}

/*************************************************************************
【函数名称】ShowValue
【函数功能】显示发布者任务界面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void publisherTask::ShowValue(){
    m_taskList=m_BackUp.m_List.SearchTaskForPublisher(m_BackUp.m_User);
    m_nameedit=new QLineEdit[m_taskList.size()];
    m_confrmBtn=new QPushButton[m_taskList.size()];
    m_table=new QTableWidget[m_taskList.size()];
    m_leaderMoney=new QLineEdit[m_taskList.size()];
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

/*************************************************************************
【函数名称】Show101
【函数功能】在flag为101状态时的界面的显示，显示已报名负责人
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void publisherTask::Show101(int i){
    ui->listWidget->insertItem(i,tr("<负责人报名火热进行中>%1").arg(m_taskList[i].GetIntroduction()));
    m_leaderList=m_BackUp.m_List.SearchLeaderForTask(m_taskList[i]);
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
        table->setItem(j,0,new QTableWidgetItem(QString::number(m_leaderList[j].GetID())));
        table->setItem(j,1,new QTableWidgetItem(m_leaderList[j].GetName()));
        table->setItem(j,2,new QTableWidgetItem(m_leaderList[j].GetEnglish()));
        table->setItem(j,3,new QTableWidgetItem(QString::number(m_leaderList[j].GetRewrdPoint())));
    }
    layout->addWidget(label);
    layout->addWidget(table);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);
}

/*************************************************************************
【函数名称】Show102
【函数功能】在flag为102状态时的界面的显示，显示发布者选择负责人的页面
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void publisherTask::Show102(int i){
    m_Page=i;
    ui->listWidget->insertItem(i,tr("<负责人报名完毕，请选择！>%1").arg(m_taskList[i].GetIntroduction()));
    m_leaderList=m_BackUp.m_List.SearchLeaderForTask(m_taskList[i]);
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
        table->setItem(j,0,new QTableWidgetItem(QString::number(m_leaderList[j].GetID())));
        table->setItem(j,1,new QTableWidgetItem(m_leaderList[j].GetName()));
        table->setItem(j,2,new QTableWidgetItem(m_leaderList[j].GetEnglish()));
        table->setItem(j,3,new QTableWidgetItem(QString::number(m_leaderList[j].GetRewrdPoint())));
    }
    layout->addWidget(label);
    layout->addWidget(table);
    QHBoxLayout *layoutName=new QHBoxLayout;
    QLabel *labelName=new QLabel(tr("账号："));
    layoutName->addWidget(labelName);
    layoutName->addWidget(m_nameedit+i);
    layout->addLayout(layoutName);
    m_confrmBtn[i].setText(tr("确定"));
    layout->addWidget(m_confrmBtn+i);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);
    connect((m_confrmBtn+i),SIGNAL(pressed()),this,SLOT(GetPage102()));
}

/*************************************************************************
【函数名称】Show401
【函数功能】在flag为401状态时的界面的显示，显示发布者的任务确认页面
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void publisherTask::Show401(int i){
    ui->listWidget->insertItem(i,tr("<任务翻译完毕，请确认！>%1").arg(m_taskList[i].GetIntroduction()));
    QTabWidget *Tab=new QTabWidget;
    QLabel *intro=new QLabel(tr("%1").arg(m_taskList[i].GetIntroduction()));
    QTextBrowser *myTask=new QTextBrowser;
    myTask->setText(m_taskList[i].GetTask());
    QTextBrowser *myResult=new QTextBrowser;
    QLabel *inform1=new QLabel(tr("负责人酬金："));
    int iIDTask=m_taskList[i].GetID();
    for(int j=0;j<m_BackUp.m_List.TaskLeader.size();j++){
        if(iIDTask==m_BackUp.m_List.TaskLeader[j].GetID()){
            myResult->setText(m_BackUp.m_List.TaskLeader[j].GetResult());
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
    leader->addWidget(m_leaderMoney+i);
    QWidget *window2=new QWidget;
    QVBoxLayout *layout2=new QVBoxLayout();
    QLabel *inform2=new QLabel(tr("译者："));
    m_TaskTranslaterList=m_BackUp.m_List.SearchTaskForTranslater_302(m_taskList[i].GetID());
    (m_table+i)->setColumnCount(4);
    (m_table+i)->setRowCount(m_TaskTranslaterList.size());
    (m_table+i)->setWindowTitle("译者");
    QStringList header;
    header<<"账号"<<"译文"<<"成果"<<"酬金";
    (m_table+i)->setHorizontalHeaderLabels(header);
    for(int j=0;j<m_TaskTranslaterList.size();j++){
        (m_table+i)->setItem(j,0,new QTableWidgetItem(QString::number(m_TaskTranslaterList[j].GetID())));
        (m_table+i)->setItem(j,1,new QTableWidgetItem(m_TaskTranslaterList[j].GetTask()));
        (m_table+i)->setItem(j,2,new QTableWidgetItem(m_TaskTranslaterList[j].GetResult()));
    }
    layout2->addLayout(leader);
    layout2->addWidget(inform2);
    layout2->addWidget((m_table+i));
    (m_confrmBtn+i)->setText(tr("确定"));
    layout2->addWidget(m_confrmBtn+i);
    window2->setLayout(layout2);
    Tab->addTab(window2,tr("分配酬金"));
    layout2->addWidget(m_confrmBtn+i);
    connect((m_confrmBtn+i),SIGNAL(pressed()),this,SLOT(GetPage401()));
    ui->stackedWidget->addWidget(Tab);
}

/*************************************************************************
【函数名称】ShowDefault
【函数功能】任务状态为401时，显示页面，显示发布者耐心等待的页面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
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

/*************************************************************************
【函数名称】on_main_clicked
【函数功能】点击main后，返回主页面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void publisherTask::on_main_clicked()
{
    MainWindow r;
    r.EditBackUp(m_BackUp);
    r.show();
    close();
}

/*************************************************************************
【函数名称】OnClicked
【函数功能】点击之后的函数处理
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void publisherTask::OnClicked(int i){
    int iIdLeader=m_nameedit[i].text().toInt();
    int iNum=ui->listWidget->currentRow();
    int iNumInList=m_BackUp.m_List.searchTaskInList(m_taskList[iNum]);
    m_BackUp.m_List.TaskPublisher[iNumInList].EditLeader(iIdLeader);
    m_BackUp.m_List.TaskPublisher[iNumInList].EditFlag(201);
    QMessageBox::information(this, tr("提示"),
                       tr("选择负责人成功！")
                      ,tr("确定"));
    int iSize=m_BackUp.m_List.SignUpForLeader.size();
    for(int j=iSize-1;j>=0;j--){
        if(m_BackUp.m_List.SignUpForLeader[j].GetIDTask()==m_taskList[iNum].GetID()){
            m_BackUp.m_List.SignUpForLeader.removeAt(j);
        }
    }
    m_taskList[iNum].EditLeader(iIdLeader);
    m_taskList[iNum].EditFlag(201);
    m_BackUp.m_List.updateList(m_taskList[iNum]);
    m_BackUp.m_List.TaskLeaderAppend(m_taskList[iNum]);
}

/*************************************************************************
【函数名称】ShowValue
【函数功能】显示发布者任务界面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void publisherTask::GetPage102(){
    for(int i=0;i<m_taskList.size();i++){
        if((m_confrmBtn+i)->isDown()){
            OnClicked(i);
        }
    }
}

void publisherTask::GetPage401(){
    for(int i=0;i<m_taskList.size();i++){
        if((m_confrmBtn+i)->isDown()){
            OnClicked401(i);
        }
    }
}
void publisherTask::OnClicked401(int i){
    //所有译者加5分
    QMessageBox::information(this, tr("提示"),
                       tr("任务确认成功！")
                      ,tr("确定"));
    //所有表中删除和该任务有关的所有数据
    int iIDLeader=m_taskList[i].GetLeader();
    int iNum=m_BackUp.m_List.searchUserInList(iIDLeader);
    //将负责人的余额加入表中
    m_BackUp.m_List.User[iNum].AddMoney((m_leaderMoney+i)->text().toDouble());//发消息确认
    //负责人加10分
    m_BackUp.m_List.User[iNum].AddPoint(10);
    for(int j=0;j<m_TaskTranslaterList.size();j++){
        iNum=m_BackUp.m_List.searchUserInList(m_TaskTranslaterList[j].GetTranslater());
        //将译者余额存入表中
        //(m_table+i)->item(j,3)->text().toDouble();
        m_BackUp.m_List.User[iNum].AddMoney((m_table+i)->item(j,3)->text().toDouble());//发消息确认
        //译者加5分
        m_BackUp.m_List.User[iNum].AddPoint(5);
    }
    m_BackUp.m_List.Delete(m_taskList[i].GetID());
}
