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
#include <QInputDialog>



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

/*************************************************************************
【函数名称】ShowValue
【函数功能】显示发布者任务界面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void publisherTask::ShowValue(){
    m_taskList=g_backUp.m_listTaskPublisher.SearchTaskForPublisher(g_backUp.m_User);
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
    ui->listWidget->insertItem(i,tr("<负责人报名火热进行中>%1").arg(m_taskList[i].GetTitle()));
    m_leaderList=g_backUp.m_listSignUpForLeader.SearchLeaderForTask(m_taskList[i].GetID());
    QWidget *window=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    QLabel *label=new QLabel(tr("已报名负责人："));
    QTableWidget *table=new QTableWidget(m_leaderList.size(),3);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setWindowTitle("已报名负责人");
    QStringList header;
    header<<"用户名"<<"英语资历"<<"积分";
    table->setHorizontalHeaderLabels(header);
    for(int j=0;j<m_leaderList.size();j++){
        table->setItem(j,0,new QTableWidgetItem(m_leaderList[j].GetID()));
        table->setItem(j,1,new QTableWidgetItem(m_leaderList[j].GetEnglish()));
        table->setItem(j,2,new QTableWidgetItem(QString::number(m_leaderList[j].GetRewrdPoint())));
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
    ui->listWidget->insertItem(i,tr("<负责人报名完毕，请选择！>%1").arg(m_taskList[i].GetTitle()));
    m_leaderList=g_backUp.m_listSignUpForLeader.SearchLeaderForTask(m_taskList[i].GetID());
    QWidget *window=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    QLabel *label=new QLabel(tr("已报名负责人："));
    QTableWidget *table=new QTableWidget(m_leaderList.size(),3);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setWindowTitle("已报名负责人");
    QStringList header;
    header<<"用户名"<<"英语资历"<<"积分";
    table->setHorizontalHeaderLabels(header);
    for(int j=0;j<m_leaderList.size();j++){
        table->setItem(j,0,new QTableWidgetItem(m_leaderList[j].GetID()));
        table->setItem(j,1,new QTableWidgetItem(m_leaderList[j].GetEnglish()));
        table->setItem(j,2,new QTableWidgetItem(QString::number(m_leaderList[j].GetRewrdPoint())));
    }
    layout->addWidget(label);
    layout->addWidget(table);
    QHBoxLayout *layoutName=new QHBoxLayout;
    QLabel *labelName=new QLabel(tr("用户名："));
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
    ui->listWidget->insertItem(i,tr("<任务翻译完毕，请确认！>%1").arg(m_taskList[i].GetTitle()));
    QTabWidget *Tab=new QTabWidget;
    QLabel *intro=new QLabel(tr("%1").arg(m_taskList[i].GetTitle()));
    QTextBrowser *myTask=new QTextBrowser;
    myTask->setText(m_taskList[i].GetTask());
    QTextBrowser *myResult=new QTextBrowser;
    QLabel *inform1=new QLabel(tr("负责人酬金："));
    int iIDTask=m_taskList[i].GetID();
    for(int j=0;j<g_backUp.m_listTaskLeader.m_List.size();j++){
        if(iIDTask==g_backUp.m_listTaskLeader.m_List[j].GetID()){
            myResult->setText(g_backUp.m_listTaskLeader.m_List[j].GetResult());
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
    m_TaskTranslaterList=g_backUp.m_listTaskTranslater.SearchTaskForTranslater(m_taskList[i].GetID());
    (m_table+i)->setColumnCount(4);
    (m_table+i)->setRowCount(m_TaskTranslaterList.size());
    (m_table+i)->setWindowTitle("译者");
    QStringList header;
    header<<"用户名"<<"译文"<<"成果"<<"酬金";
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
    ui->listWidget->insertItem(i,tr("<翻译任务进行中！>%1").arg(m_taskList[i].GetTitle()));
    QLabel *inform=new QLabel(tr("翻译任务正在火热进行中，请耐心等待！"));
    QWidget *window=new QWidget();
    QLabel *taskClass;
    if(m_taskList[i].GetTaskClass()==0){
        taskClass=new QLabel(tr("翻译性质：中译英"));
    }
    else{
        taskClass=new QLabel(tr("翻译性质：英译中"));
    }
    QLabel* title=new QLabel(tr("翻译标题：%1").arg(m_taskList[i].GetTitle()));
    QLabel *intro=new QLabel(tr("任务简介：%1").arg(m_taskList[i].GetIntroduction()));
    QLabel *tasks=new QLabel(tr("翻译内容：%1").arg(m_taskList[i].GetTask()));
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(m_taskList[i].GetTime()));
    QLabel *date=new QLabel(tr("负责人报名截至日期：%1年%2月%3日").arg(m_taskList[i].GetLeaderYear()).arg(m_taskList[i].GetLeaderMonth()).arg(m_taskList[i].GetLeaderDay()));
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(m_taskList[i].GetMoney()));
    QVBoxLayout *layout=new QVBoxLayout();
    layout->addWidget(inform);
    layout->addWidget(taskClass);
    layout->addWidget(title);
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
    MainWindow* r=new MainWindow;
    r->show();
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
    QString iIdLeader=m_nameedit[i].text().trimmed();
    int iNum=ui->listWidget->currentRow();
    int iNumInList=g_backUp.m_listTaskPublisher.SearchInList(m_taskList[iNum]);
    g_backUp.m_listTaskPublisher.m_List[iNumInList].EditLeader(iIdLeader);
    g_backUp.m_listTaskPublisher.m_List[iNumInList].EditFlag(201);
    QMessageBox::information(this, tr("提示"),
                       tr("选择负责人成功！")
                      ,tr("确定"));
    g_backUp.SelectLeaderDone(g_backUp.m_User.GetID(),iIdLeader,m_taskList[iNum].GetTitle());
    g_backUp.m_listSignUpForLeader.Delete(m_taskList[iNum].GetID());
    m_taskList[iNum].EditLeader(iIdLeader);
    m_taskList[iNum].EditFlag(201);
    //
    g_backUp.m_listTaskPublisher.Update(m_taskList[iNum]);
    g_backUp.m_listTaskLeader.TaskLeaderAppend(m_taskList[iNum]);
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
    double moneySum=0;
    //译者分配钱数总和相加
    moneySum+=((m_leaderMoney+i)->text().toDouble());
    for(int j=0;j<m_TaskTranslaterList.size();j++){
        moneySum+=(m_table+i)->item(j,2)->text().toDouble();
    }
    while(g_backUp.m_User.GetMoney()<moneySum){
        double add= QInputDialog::getDouble(this, "充值",
                                                        "余额不足，请充值！");
        g_backUp.m_User.AddMoney(add);
    }
    QMessageBox::information(this, tr("提示"),
                       tr("任务确认成功！")
                      ,tr("确定"));
    g_backUp.m_User.LoseMoney(moneySum);
    QString iIDLeader=m_taskList[i].GetLeader();
    int iNum=g_backUp.m_listUser.SearchInList(iIDLeader);
    //将负责人的余额加入表中
    g_backUp.m_listUser.m_List[iNum].AddMoney((m_leaderMoney+i)->text().toDouble());
    //发消息确认
    g_backUp.DistributeMoney_Translater(m_taskList[i].GetTitle(),
                                        (m_leaderMoney+i)->text().toDouble(),m_taskList[i].GetLeader());
    //负责人加10分
    g_backUp.m_listUser.m_List[iNum].AddPoint(10);
    for(int j=0;j<m_TaskTranslaterList.size();j++){
        iNum=g_backUp.m_listUser.SearchInList(m_TaskTranslaterList[j].GetTranslater());
        //将译者余额存入表中
        //(m_table+i)->item(j,3)->text().toDouble();
        g_backUp.m_listUser.m_List[iNum].AddMoney((m_table+i)->item(j,3)->text().toDouble());//发消息确认
        //译者加5分
        g_backUp.m_listUser.m_List[iNum].AddPoint(5);
        g_backUp.DistributeMoney_Translater(m_taskList[i].GetTitle(),
                                            (m_table+i)->item(j,2)->text().toDouble(),
                                            m_TaskTranslaterList[j].GetTranslater());
    }
    g_backUp.DistributeMoney_Publisher(m_taskList[i].GetTitle(),m_taskList[i].GetPublisher()
                                       ,moneySum);
    //所有表中删除和该任务有关的所有数据
    g_backUp.m_listTaskLeader.Delete(m_taskList[i].GetID());
    g_backUp.m_listSignUpForLeader.Delete(m_taskList[i].GetID());
    g_backUp.m_listSignUpForTranslater.Delete(m_taskList[i].GetID());
    g_backUp.m_listTaskLeader.Delete(m_taskList[i].GetID());
    g_backUp.m_listTaskPublisher.Delete(m_taskList[i].GetID());
}
