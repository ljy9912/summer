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
#include <QTableWidget>



tasksPublished::tasksPublished(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tasksPublished)
{
    ui->setupUi(this);

}


tasksPublished::~tasksPublished()
{
    delete ui;
    delete m_applyBtn;
    m_applyBtn=NULL;
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
    MainWindow* r=new MainWindow;
    r->show();
    close();
}


/*************************************************************************
【函数名称】showValue
【函数功能】显示界面
【参数】list g_backUp.m_List
【返回值】无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void tasksPublished::ShowValue(){
    m_applyBtn=new QPushButton[g_backUp.m_List.TaskPublisher.size()];
    for(int i=0;i<g_backUp.m_List.TaskPublisher.size();i++){
        switch(g_backUp.m_List.TaskPublisher[i].GetFlag()){
        case 101:

            ShowValue101(i);
            break;
        case 102:
            ShowValue102(i);
            break;
        case 201:
            ShowValue201(i);
            break;
        case 202:
            ShowValue202(i);
            break;
        case 203:
            ui->listWidget->insertItem(i,tr("<翻译任务进行中>%1").arg(g_backUp.m_List.TaskPublisher[i].GetTitle()));
            ShowValue203(i);
            break;
        case 401:
            ui->listWidget->insertItem(i,tr("<负责人确认中>%1").arg(g_backUp.m_List.TaskPublisher[i].GetTitle()));
            ShowValue203(i);
            break;
        }
    }
}

void tasksPublished::ShowValue101(int i){
    ui->listWidget->insertItem(i,tr("<负责人火热报名中！>%1").arg(g_backUp.m_List.TaskPublisher[i].GetTitle()));
    taskPublisher myTask=g_backUp.m_List.TaskPublisher[i];
    QWidget *window=new QWidget();
    QLabel *taskClass;
    if(myTask.GetTaskClass()==0){
        taskClass=new QLabel(tr("翻译性质：中译英"));
    }
    else{
        taskClass=new QLabel(tr("翻译性质：英译中"));
    }
    QLabel* title=new QLabel(tr("翻译标题：%1").arg(myTask.GetTitle()));
    QLabel *intro=new QLabel(tr("任务简介："));
    QTextBrowser* Intro=new QTextBrowser;
    Intro->setText(myTask.GetIntroduction());
    QLabel *tasks=new QLabel(tr("翻译内容："));
    QTextBrowser *Task=new QTextBrowser;
    Task->setText(myTask.GetTask());
    QLabel* publisher=new QLabel(tr("发布者：%1").arg(myTask.GetPublisher()));
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(myTask.GetTime()));
    QLabel *date=new QLabel(tr("负责人报名截止日期：%1年%2月%3日").arg(myTask
                                                          .GetLeaderYear())
                            .arg(myTask.GetLeaderMonth())
                            .arg(myTask.GetLeaderDay()));
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(myTask.GetMoney()));
    m_applyBtn[i].setText("申请负责人");
    QVBoxLayout *layout=new QVBoxLayout();

    layout->addWidget(title);
    layout->addWidget(taskClass);
    layout->addWidget(intro);
    layout->addWidget(Intro);
    layout->addWidget(publisher);
    layout->addWidget(time);
    layout->addWidget(date);
    layout->addWidget(money);
    layout->addWidget(tasks);
    layout->addWidget(Task);
    layout->addWidget(m_applyBtn+i);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);

    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));

    connect((m_applyBtn+i),SIGNAL(pressed()),this,SLOT(GetPage101()));
}

void tasksPublished::ShowValue102(int i){
    ui->listWidget->insertItem(i,tr("<发布者正在筛选负责人！>%1").arg(g_backUp.m_List.TaskPublisher[i].GetTitle()));
    taskPublisher myTask=g_backUp.m_List.TaskPublisher[i];
    QWidget *window=new QWidget();
    QLabel *taskClass;
    if(myTask.GetTaskClass()==0){
        taskClass=new QLabel(tr("翻译性质：中译英"));
    }
    else{
        taskClass=new QLabel(tr("翻译性质：英译中"));
    }
    QLabel* title=new QLabel(tr("翻译标题：%1").arg(myTask.GetTitle()));
    QLabel *intro=new QLabel(tr("任务简介："));
    QTextBrowser* Intro=new QTextBrowser;
    Intro->setText(myTask.GetIntroduction());
    QLabel *tasks=new QLabel(tr("翻译内容："));
    QTextBrowser *Task=new QTextBrowser;
    Task->setText(myTask.GetTask());
    QLabel* publisher=new QLabel(tr("发布者：%1").arg(myTask.GetPublisher()));
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(myTask.GetTime()));
    QLabel *date=new QLabel(tr("负责人报名截止日期：%1年%2月%3日").arg(myTask
                                                          .GetLeaderYear())
                            .arg(myTask.GetLeaderMonth())
                            .arg(myTask.GetLeaderDay()));
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(myTask.GetMoney()));
    QVBoxLayout *layout=new QVBoxLayout();

    layout->addWidget(title);
    layout->addWidget(taskClass);
    layout->addWidget(intro);
    layout->addWidget(Intro);
    layout->addWidget(publisher);
    layout->addWidget(time);
    layout->addWidget(date);
    layout->addWidget(money);
    layout->addWidget(tasks);
    layout->addWidget(Task);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);

    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}


void tasksPublished::ShowValue201(int i){
    taskPublisher myTask=g_backUp.m_List.TaskPublisher[i];
    ui->listWidget->insertItem(i,tr("<负责人正在制定翻译计划！>%1").arg(myTask.GetTitle()));
    QWidget *window=new QWidget();
    QLabel *taskClass;
    if(myTask.GetTaskClass()==0){
        taskClass=new QLabel(tr("翻译性质：中译英"));
    }
    else{
        taskClass=new QLabel(tr("翻译性质：英译中"));
    }
    QLabel* title=new QLabel(tr("翻译标题：%1").arg(myTask.GetTitle()));
    QLabel *intro=new QLabel(tr("任务简介："));
    QTextBrowser* Intro=new QTextBrowser;
    Intro->setText(myTask.GetIntroduction());
    QLabel *tasks=new QLabel(tr("翻译内容："));
    QLabel* publisher=new QLabel(tr("发布者：%1").arg(myTask.GetPublisher()));
    QTextBrowser *Task=new QTextBrowser;
    Task->setText(myTask.GetTask());
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(myTask.GetTime()));
    QLabel* leader=new QLabel(tr("负责人：%1").arg(myTask.GetLeader()));
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(myTask.GetMoney()));
    QVBoxLayout *layout=new QVBoxLayout();

    layout->addWidget(title);
    layout->addWidget(taskClass);
    layout->addWidget(intro);
    layout->addWidget(Intro);
    layout->addWidget(publisher);
    layout->addWidget(leader);
    layout->addWidget(time);
    layout->addWidget(money);
    layout->addWidget(tasks);
    layout->addWidget(Task);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);

    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}

void tasksPublished::ShowValue202(int i){
    taskPublisher myTask=g_backUp.m_List.TaskPublisher[i];
    ui->listWidget->insertItem(i,tr("<译者正在火热报名中！>%1").arg(myTask.GetTitle()));
    QWidget *window=new QWidget();
    QLabel* taskClass;
    if(myTask.GetTaskClass()==0){
        taskClass=new QLabel(tr("翻译性质：中译英"));
    }
    else{
        taskClass=new QLabel(tr("翻译性质：英译中"));
    }
    QLabel* title=new QLabel(tr("翻译标题：%1").arg(myTask.GetTitle()));
    QLabel *intro=new QLabel(tr("任务简介："));
    QTextBrowser* Intro=new QTextBrowser;
    Intro->setText(myTask.GetIntroduction());
    QLabel *tasks=new QLabel(tr("翻译内容："));
    QLabel* publisher=new QLabel(tr("发布者：%1").arg(myTask.GetPublisher()));
    QTextBrowser *Task=new QTextBrowser;
    Task->setText(myTask.GetTask());
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(myTask.GetTime()));
    QLabel *date=new QLabel(tr("译者报名截止日期：%1年%2月%3日").arg(myTask
                                                          .GetLeaderYear())
                            .arg(myTask.GetLeaderMonth())
                            .arg(myTask.GetLeaderDay()));
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(myTask.GetMoney()));
    QLabel* leader=new QLabel(tr("负责人：%1").arg(myTask.GetLeader()));
    m_applyBtn[i].setText("申请译者");
    QVBoxLayout *layout=new QVBoxLayout();


    layout->addWidget(title);
    layout->addWidget(taskClass);
    layout->addWidget(intro);
    layout->addWidget(Intro);
    layout->addWidget(publisher);
    layout->addWidget(leader);
    layout->addWidget(time);
    layout->addWidget(date);
    layout->addWidget(money);
    layout->addWidget(tasks);
    layout->addWidget(Task);
    layout->addWidget(m_applyBtn+i);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);

    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));

    connect((m_applyBtn+i),SIGNAL(pressed()),this,SLOT(GetPage202()));
}

void tasksPublished::ShowValue203(int i){
    //左边listwidget上面的任务描述信息
    taskPublisher myTask=g_backUp.m_List.TaskPublisher[i];
    //使用tabwidget，第一页显示任务的所有信息，第二页显示负责人和译者
    QTabWidget *Tab=new QTabWidget;
    QLabel* taskClass;
    if(myTask.GetTaskClass()==0){
        taskClass=new QLabel(tr("翻译性质：中译英"));
    }
    else{
        taskClass=new QLabel(tr("翻译性质：英译中"));
    }
    QLabel* title=new QLabel(tr("翻译标题：%1").arg(myTask.GetTitle()));
    QLabel* publisher=new QLabel(tr("发布者：%1").arg(myTask.GetPublisher()));
    QLabel *intro=new QLabel(tr("任务简介："));
    QTextBrowser* Intro=new QTextBrowser;
    Intro->setText(myTask.GetIntroduction());
    QLabel *tasks=new QLabel(tr("翻译内容："));
    QTextBrowser *Task=new QTextBrowser;
    Task->setText(myTask.GetTask());
    QLabel* date=new QLabel(tr("任务起始时间：%1年%2月%3日").arg(myTask.GetStartYear())
                            .arg(myTask.GetStartMonth())
                            .arg(myTask.GetStartDay()));
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(myTask.GetTime()));
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(myTask.GetMoney()));
    QVBoxLayout *layout1=new QVBoxLayout;
    layout1->addWidget(title);
    layout1->addWidget(taskClass);
    layout1->addWidget(intro);
    layout1->addWidget(Intro);
    layout1->addWidget(publisher);
    layout1->addWidget(date);
    layout1->addWidget(time);
    layout1->addWidget(money);
    layout1->addWidget(tasks);
    layout1->addWidget(Task);
    QWidget* window1=new QWidget;
    window1->setLayout(layout1);
    Tab->addTab(window1,tr("任务信息"));
    //第二个页面的显示
    QWidget *window2=new QWidget;
    QVBoxLayout *layout2=new QVBoxLayout();
    QLabel *inform2=new QLabel(tr("译者："));
    QList<taskTranslater> translaterList=g_backUp.m_List.SearchTaskForTranslater_302(myTask.GetID());
    QTableWidget* table=new QTableWidget((translaterList.size()+1),5);
    table->setWindowTitle("译者");
    QStringList header;
    header<<"用户名"<<"角色"<<"电话"<<"英语资历"<<"积分";
    table->setHorizontalHeaderLabels(header);
    table->setItem(0,0,new QTableWidgetItem(myTask.GetLeader()));
    table->setItem(0,1,new QTableWidgetItem("负责人"));
    int iNum=g_backUp.m_List.searchUserInList(myTask.GetLeader());
    user myLeader=g_backUp.m_List.User[iNum];
    table->setItem(0,2,new QTableWidgetItem(myLeader.GetPhoneNum()));
    table->setItem(0,3,new QTableWidgetItem(myLeader.GetEnglish()));
    table->setItem(0,4,new QTableWidgetItem(myLeader.GetRewrdPoint()));
    for(int j=0;j<translaterList.size();j++){
        table->setItem(j,0,new QTableWidgetItem(translaterList[j].GetTranslater()));
        table->setItem(j,1,new QTableWidgetItem("译者"));
        iNum=g_backUp.m_List.searchUserInList(myTask.GetLeader());
        user myTranslater=g_backUp.m_List.User[iNum];
        table->setItem(j,2,new QTableWidgetItem(myTranslater.GetPhoneNum()));
        table->setItem(j,3,new QTableWidgetItem(myTranslater.GetEnglish()));
        table->setItem(j,4,new QTableWidgetItem(myTranslater.GetRewrdPoint()));
    }
    layout2->addWidget(inform2);
    layout2->addWidget(table);
    window2->setLayout(layout2);
    Tab->addTab(window2,tr("译者信息"));
    ui->stackedWidget->addWidget(Tab);

    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}

void tasksPublished::GetPage101(){
    for(int i=0;i<g_backUp.m_List.TaskPublisher.size();i++){
        if((m_applyBtn+i)->isDown()){
            OnClicked101(i);
        }
    }
}

void tasksPublished::GetPage202(){
    for(int i=0;i<g_backUp.m_List.TaskPublisher.size();i++){
        if((m_applyBtn+i)->isDown()){
            OnClicked202(i);
        }
    }
}

void tasksPublished::OnClicked101(int i){
    taskPublisher myTask=g_backUp.m_List.TaskPublisher[i];
    if(g_backUp.m_User.GetRewrdPoint()<100){
        QMessageBox::warning(this, tr("提示"),
                           tr("积分不足，请努力完成更多翻译任务后再来申请吧！")
                          ,tr("确定"));
    }
    else{
        int idtask=myTask.GetID();
        int idthis=g_backUp.m_List.SignUpForLeader.last().GetIDThis()+1;
        signUpForLeader leader(g_backUp.m_User,idtask,idthis);
        g_backUp.m_List.SignUpForLeader.append(leader);
        QMessageBox::information(this, tr("提示"),
                           tr("报名成功！")
                          ,tr("确定"));
        g_backUp.SignUpForLeader(g_backUp.m_User.GetID(),idtask);
    }
}

void tasksPublished::OnClicked202(int i){
    taskPublisher myTask=g_backUp.m_List.TaskPublisher[i];
    int idtask=myTask.GetID();
    int idthis=g_backUp.m_List.SignUpForTranslater.last().GetIDThis()+1;
    signUpForTranslater translater(g_backUp.m_User,idtask,idthis);
    g_backUp.m_List.SignUpForTranslater.append(translater);
    QMessageBox::information(this, tr("提示"),
                       tr("报名成功！")
                      ,tr("确定"));
    g_backUp.SignUpForTranslaterDone(g_backUp.m_User.GetID(),myTask.GetTitle());
}
