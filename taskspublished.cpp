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
    m_applyBtn=new QPushButton[g_backUp.m_listTaskPublisher.m_List.size()];
    //对任务列表中的每一项做讨论，根据不同的状态显示不同的形式
    for(int i=0;i<g_backUp.m_listTaskPublisher.m_List.size();i++){
        switch(g_backUp.m_listTaskPublisher.m_List[i].GetFlag()){
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
            ui->listWidget->insertItem(i,tr("<翻译任务进行中>%1").arg(g_backUp.m_listTaskPublisher.m_List[i].GetTitle()));
            ShowValue203(i);
            break;
        case 401:
            ui->listWidget->insertItem(i,tr("<负责人确认中>%1").arg(g_backUp.m_listTaskPublisher.m_List[i].GetTitle()));
            ShowValue203(i);
            break;
        case 402:
            ui->listWidget->insertItem(i,tr("<任务已完成>%1").arg(g_backUp.m_listTaskPublisher.m_List[i].GetTitle()));
            ShowValue203(i);
            break;
        }
    }
}

void tasksPublished::ShowValue101(int i){
    //在页面左侧的listWidget中添加新的item
    ui->listWidget->insertItem(i,tr("<负责人火热报名中！>%1").arg(g_backUp.m_listTaskPublisher.m_List[i].GetTitle()));
    taskPublisher myTask=g_backUp.m_listTaskPublisher.m_List[i];
    //声明页面中需要的widget
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
    //在垂直布局中添加widget
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
    //为窗口设置垂直布局
    window->setLayout(layout);
    //将窗口添加到stackedWidget中
    ui->stackedWidget->addWidget(window);
    //将listWidget和stackedWidget连接
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    //将申请的button和getPage101连接
    connect((m_applyBtn+i),SIGNAL(pressed()),this,SLOT(GetPage101()));
}

void tasksPublished::ShowValue102(int i){
    //在listWidget中添加新的item
    ui->listWidget->insertItem(i,tr("<发布者正在筛选负责人！>%1").arg(g_backUp.m_listTaskPublisher.m_List[i].GetTitle()));
    //声明页面布置需要的widget
    taskPublisher myTask=g_backUp.m_listTaskPublisher.m_List[i];
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
    //在垂直布局中添加widget
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
    //设置窗口布局
    window->setLayout(layout);
    //将窗口添加到stackedWidget中
    ui->stackedWidget->addWidget(window);
    //连接页面左边的listWidget和右边的stackedWidget
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}


void tasksPublished::ShowValue201(int i){
    taskPublisher myTask=g_backUp.m_listTaskPublisher.m_List[i];
    //在listWidget中添加新的item
    ui->listWidget->insertItem(i,tr("<负责人正在制定翻译计划！>%1").arg(myTask.GetTitle()));
    //声明需要的widget
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
    //在垂直布局中添加widget
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
    //为窗口设定布局
    window->setLayout(layout);
    //将widget添加到stakcedwidget中
    ui->stackedWidget->addWidget(window);
    //连接listWiget和stackedWidget
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}

void tasksPublished::ShowValue202(int i){
    taskPublisher myTask=g_backUp.m_listTaskPublisher.m_List[i];
    //在页面左边的listWidget中添加新的item
    ui->listWidget->insertItem(i,tr("<译者正在火热报名中！>%1").arg(myTask.GetTitle()));
    //声明页面需要的控件
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
    //在垂直布局中添加控件
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
    //为窗口设定布局
    window->setLayout(layout);
    //将布局添加到stackedWidget中
    ui->stackedWidget->addWidget(window);
    //连接stackedWidget和listWidget
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    //连接申请的button和GetPage202函数
    connect((m_applyBtn+i),SIGNAL(pressed()),this,SLOT(GetPage202()));
}

void tasksPublished::ShowValue203(int i){
    //左边listwidget上面的任务描述信息
    taskPublisher myTask=g_backUp.m_listTaskPublisher.m_List[i];
    //使用tabwidget，第一页显示任务的所有信息，第二页显示负责人和译者
    //声明页面需要的插件
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
    //在垂直布局中添加需要的插件
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
    //为窗口设定布局
    QWidget* window1=new QWidget;
    window1->setLayout(layout1);
    //添加新的tab页面
    Tab->addTab(window1,tr("任务信息"));
    //第二个页面的显示
    //声明所需控件
    QWidget *window2=new QWidget;
    QVBoxLayout *layout2=new QVBoxLayout();
    QLabel *inform2=new QLabel(tr("译者："));
    QList<taskTranslater> translaterList=g_backUp.m_listTaskTranslater.SearchTaskForTranslater(myTask.GetID());
    //声明一个tableWidget
    QTableWidget* table=new QTableWidget((translaterList.size()+1),5);
    table->setWindowTitle("译者");
    //声明表头
    QStringList header;
    header<<"用户名"<<"角色"<<"电话"<<"英语资历"<<"积分";
    table->setHorizontalHeaderLabels(header);
    //设定表格的内容
    table->setItem(0,0,new QTableWidgetItem(myTask.GetLeader()));
    table->setItem(0,1,new QTableWidgetItem("负责人"));
    int iNum=g_backUp.m_listUser.SearchInList(myTask.GetLeader());
    user myLeader=g_backUp.m_listUser.m_List[iNum];
    table->setItem(0,2,new QTableWidgetItem(myLeader.GetPhoneNum()));
    table->setItem(0,3,new QTableWidgetItem(myLeader.GetEnglish()));
    table->setItem(0,4,new QTableWidgetItem(myLeader.GetRewrdPoint()));
    for(int j=0;j<translaterList.size();j++){
        table->setItem(j,0,new QTableWidgetItem(translaterList[j].GetTranslater()));
        table->setItem(j,1,new QTableWidgetItem("译者"));
        iNum=g_backUp.m_listUser.SearchInList(myTask.GetLeader());
        user myTranslater=g_backUp.m_listUser.m_List[iNum];
        table->setItem(j,2,new QTableWidgetItem(myTranslater.GetPhoneNum()));
        table->setItem(j,3,new QTableWidgetItem(myTranslater.GetEnglish()));
        table->setItem(j,4,new QTableWidgetItem(myTranslater.GetRewrdPoint()));
    }
    layout2->addWidget(inform2);
    layout2->addWidget(table);
    window2->setLayout(layout2);
    Tab->addTab(window2,tr("译者信息"));
    ui->stackedWidget->addWidget(Tab);
    //连接listWidget和stackedWidget
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}

void tasksPublished::GetPage101(){
    for(int i=0;i<g_backUp.m_listTaskPublisher.m_List.size();i++){
        if((m_applyBtn+i)->isDown()){
            OnClicked101(i);
        }
    }
}

void tasksPublished::GetPage202(){
    for(int i=0;i<g_backUp.m_listTaskPublisher.m_List.size();i++){
        if((m_applyBtn+i)->isDown()){
            OnClicked202(i);
        }
    }
}

void tasksPublished::OnClicked101(int i){
    taskPublisher myTask=g_backUp.m_listTaskPublisher.m_List[i];
    //判断用户是否已经报过名了
    if(!g_backUp.m_listSignUpForLeader.UserExists(g_backUp.m_User.GetID(),myTask.GetID())){
        if(g_backUp.m_User.GetRewrdPoint()<100){
            QMessageBox::warning(this, tr("警告"),
                               tr("积分不足，请努力完成更多翻译任务后再来申请吧！")
                              ,tr("确定"));
        }
        else{
            QMessageBox::information(this, tr("提示"),
                               tr("报名成功！")
                              ,tr("确定"));
            //后台执行负责人报名操作
            g_backUp.SignUpForLeader(i);
        }
    }
    else{
        QMessageBox::warning(this, tr("警告"),
                           tr("您已经报过名了！")
                          ,tr("确定"));
    }
}

void tasksPublished::OnClicked202(int i){
    taskPublisher myTask=g_backUp.m_listTaskPublisher.m_List[i];
    //判断用户是否已经报过名了
    if(!g_backUp.m_listSignUpForTranslater.UserExists(g_backUp.m_User.GetID(),myTask.GetID())){

        QMessageBox::information(this, tr("提示"),
                           tr("报名成功！")
                          ,tr("确定"));
        //后台执行译者报名操作
        g_backUp.SignUpForTranslaterDone(i);
    }
    else{
        QMessageBox::warning(this, tr("警告"),
                           tr("您已经报过名了！")
                          ,tr("确定"));
    }
}
