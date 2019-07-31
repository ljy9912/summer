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
#include <QScrollBar>



tasksPublished::tasksPublished(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tasksPublished)
{
    ui->setupUi(this);
    SetStyle();
}


tasksPublished::~tasksPublished()
{
    delete ui;
    ui=NULL;
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
void tasksPublished::on_Main_clicked()
{
    close();
    MainWindow r;
    r.exec();
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
    m_CheckerBtn=new QPushButton[g_backUp.m_listTaskPublisher.m_List.size()];
    //对任务列表中的每一项做讨论，根据不同的状态显示不同的形式
    for(int i=0;i<g_backUp.m_listTaskPublisher.m_List.size();i++){
        QListWidgetItem* item=new QListWidgetItem[g_backUp.m_listTaskPublisher
                .m_List.size()];
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

            (item+i)->setIcon(QIcon(":/images/jinhangzhong.svg"));
            (item+i)->setText(tr("<翻译任务进行中>%1").arg(g_backUp.m_listTaskPublisher.m_List[i].GetTitle()));
            ui->listWidget->insertItem(i,(item+i));
            ShowValue203(i);
            break;
        case 401:

            (item+i)->setIcon(QIcon(":/images/confirm.svg"));
            (item+i)->setText(tr("<发布者确认中>%1").arg(g_backUp.m_listTaskPublisher.m_List[i].GetTitle()));
            ui->listWidget->insertItem(i,(item+i));
            ShowValue203(i);
            break;
        case 402:

            (item+i)->setIcon(QIcon(":/images/Done.svg"));
            (item+i)->setText(tr("<任务已完成>%1").arg(g_backUp.m_listTaskPublisher.m_List[i].GetTitle()));
            ui->listWidget->insertItem(i,(item+i));
            ShowValue203(i);
            break;
        }
    }
}

void tasksPublished::ShowValue101(int i){
    //在页面左侧的listWidget中添加新的item
    QListWidgetItem* item=new QListWidgetItem;
    item->setIcon(QIcon(":/images/baomingblue.svg"));
    item->setText(tr("<负责人和审核人火热报名中！>%1").arg(g_backUp.m_listTaskPublisher.m_List[i].GetTitle()));
    ui->listWidget->insertItem(i,item);
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
    taskClass->setStyleSheet(m_LabelStyle);
    QLabel* title=new QLabel(tr("翻译标题：%1").arg(myTask.GetTitle()));
    title->setStyleSheet(m_LabelStyle);
    QLabel *intro=new QLabel(tr("任务简介："));
    intro->setStyleSheet(m_LabelStyle);
    QTextBrowser* Intro=new QTextBrowser;
    Intro->setStyleSheet(m_BrowserStyle);
    Intro->setText(myTask.GetIntroduction());
    QLabel *tasks=new QLabel(tr("翻译内容："));
    tasks->setStyleSheet(m_LabelStyle);
    QTextBrowser *Task=new QTextBrowser;
    Task->setStyleSheet(m_BrowserStyle);
    Task->setText(myTask.GetTask());
    QLabel* publisher=new QLabel(tr("发布者：%1").arg(myTask.GetPublisher()));
    publisher->setStyleSheet(m_LabelStyle);
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(myTask.GetTime()));
    time->setStyleSheet(m_LabelStyle);
    QLabel *date=new QLabel(tr("负责人报名截止日期：%1年%2月%3日").arg(myTask
                                                          .GetLeaderYear())
                            .arg(myTask.GetLeaderMonth())
                            .arg(myTask.GetLeaderDay()));
    date->setStyleSheet(m_LabelStyle);
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(myTask.GetMoney()));
    money->setStyleSheet(m_LabelStyle);
    m_applyBtn[i].setText("申请负责人");
    m_applyBtn[i].setStyleSheet(m_BtnStyle1);
    m_applyBtn[i].setFixedSize(171,51);
    m_CheckerBtn[i].setText("申请审核人");
    m_CheckerBtn[i].setFixedSize(171,51);
    m_CheckerBtn[i].setStyleSheet(m_BtnStyle1);
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
    layout->addSpacing(30);
    QHBoxLayout* Btn=new QHBoxLayout;
    Btn->addSpacing(300);
    Btn->addWidget(m_applyBtn+i);
    Btn->addWidget(m_CheckerBtn+i);
    Btn->addSpacing(300);
    layout->addLayout(Btn);
    //为窗口设置垂直布局
    window->setLayout(layout);
    //将窗口添加到stackedWidget中
    ui->stackedWidget->addWidget(window);
    //将listWidget和stackedWidget连接
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    //将申请的button和getPage101连接
    connect((m_applyBtn+i),SIGNAL(pressed()),this,SLOT(GetPage101apply()));
    connect((m_CheckerBtn+i),SIGNAL(pressed()),this,SLOT(GetPage101check()));
}

void tasksPublished::ShowValue102(int i){
    //在listWidget中添加新的item
    QListWidgetItem* item=new QListWidgetItem;
    item->setIcon(QIcon(":/images/choose1.svg"));
    item->setText(tr("<发布者正在筛选负责人和审核人！>%1").arg(g_backUp.m_listTaskPublisher.m_List[i].GetTitle()));
    ui->listWidget->insertItem(i,item);
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
    taskClass->setStyleSheet(m_LabelStyle);
    QLabel* title=new QLabel(tr("翻译标题：%1").arg(myTask.GetTitle()));
    title->setStyleSheet(m_LabelStyle);
    QLabel *intro=new QLabel(tr("任务简介："));
    intro->setStyleSheet(m_LabelStyle);
    QTextBrowser* Intro=new QTextBrowser;
    Intro->setStyleSheet(m_BrowserStyle);
    Intro->setText(myTask.GetIntroduction());
    QLabel *tasks=new QLabel(tr("翻译内容："));
    tasks->setStyleSheet(m_LabelStyle);
    QTextBrowser *Task=new QTextBrowser;
    Task->setText(myTask.GetTask());
    Task->setStyleSheet(m_BrowserStyle);
    QLabel* publisher=new QLabel(tr("发布者：%1").arg(myTask.GetPublisher()));
    publisher->setStyleSheet(m_LabelStyle);
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(myTask.GetTime()));
    time->setStyleSheet(m_LabelStyle);
    QLabel *date=new QLabel(tr("负责人报名截止日期：%1年%2月%3日").arg(myTask
                                                          .GetLeaderYear())
                            .arg(myTask.GetLeaderMonth())
                            .arg(myTask.GetLeaderDay()));
    date->setStyleSheet(m_LabelStyle);
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(myTask.GetMoney()));
    money->setStyleSheet(m_LabelStyle);
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
    QListWidgetItem* item=new QListWidgetItem;
    item->setIcon(QIcon(":/images/plan.svg"));
    item->setText(tr("<负责人正在制定翻译计划！>%1").arg(myTask.GetTitle()));
    ui->listWidget->insertItem(i,item);
    //声明需要的widget
    QWidget *window=new QWidget();
    QLabel *taskClass;

    if(myTask.GetTaskClass()==0){
        taskClass=new QLabel(tr("翻译性质：中译英"));
    }
    else{
        taskClass=new QLabel(tr("翻译性质：英译中"));
    }
    taskClass->setStyleSheet(m_LabelStyle);
    QLabel* title=new QLabel(tr("翻译标题：%1").arg(myTask.GetTitle()));
    title->setStyleSheet(m_LabelStyle);
    QLabel *intro=new QLabel(tr("任务简介："));
    intro->setStyleSheet(m_LabelStyle);
    QTextBrowser* Intro=new QTextBrowser;
    Intro->setText(myTask.GetIntroduction());
    Intro->setStyleSheet(m_BrowserStyle);
    QLabel *tasks=new QLabel(tr("翻译内容："));
    tasks->setStyleSheet(m_LabelStyle);
    QLabel* publisher=new QLabel(tr("发布者：%1").arg(myTask.GetPublisher()));
    publisher->setStyleSheet(m_LabelStyle);
    QTextBrowser *Task=new QTextBrowser;
    Task->setText(myTask.GetTask());
    Task->setStyleSheet(m_BrowserStyle);
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(myTask.GetTime()));
    time->setStyleSheet(m_LabelStyle);
    QLabel* leader=new QLabel(tr("负责人：%1").arg(myTask.GetLeader()));
    leader->setStyleSheet(m_LabelStyle);
    QLabel* checker=new QLabel(tr("审核人：%1").arg(myTask.GetTaskChecker()));
    checker->setStyleSheet(m_LabelStyle);
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(myTask.GetMoney()));
    money->setStyleSheet(m_LabelStyle);
    //在垂直布局中添加widget
    QVBoxLayout *layout=new QVBoxLayout();

    layout->addWidget(title);
    layout->addWidget(taskClass);
    layout->addWidget(intro);
    layout->addWidget(Intro);
    layout->addWidget(publisher);
    layout->addWidget(leader);
    layout->addWidget(checker);
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
    QListWidgetItem* item=new QListWidgetItem;
    item->setIcon(QIcon(":/images/baomingblue.svg"));
    item->setText(tr("<译者正在火热报名中！>%1").arg(myTask.GetTitle()));
    ui->listWidget->insertItem(i,item);
    //声明页面需要的控件
    QWidget *window=new QWidget();
    QLabel* taskClass;
    if(myTask.GetTaskClass()==0){
        taskClass=new QLabel(tr("翻译性质：中译英"));
    }
    else{
        taskClass=new QLabel(tr("翻译性质：英译中"));
    }
    taskClass->setStyleSheet(m_LabelStyle);
    QLabel* title=new QLabel(tr("翻译标题：%1").arg(myTask.GetTitle()));
    title->setStyleSheet(m_LabelStyle);
    int iNum=g_backUp.m_listTaskLeader.SearchInList(myTask.GetID());
    QLabel *date=new QLabel(tr("译者报名截止日期：%1年%2月%3日").arg(g_backUp.m_listTaskLeader.m_List[iNum]
                                                          .GetTranslaterYear())
                            .arg(g_backUp.m_listTaskLeader.m_List[iNum].GetTranslaterMonth())
                            .arg(g_backUp.m_listTaskLeader.m_List[iNum].GetTranslaterDay()));
    date->setStyleSheet(m_LabelStyle);
    QLabel *intro=new QLabel(tr("任务简介："));
    intro->setStyleSheet(m_LabelStyle);
    QTextBrowser* Intro=new QTextBrowser;
    Intro->setText(myTask.GetIntroduction());
    Intro->setStyleSheet(m_BrowserStyle);
    QLabel *tasks=new QLabel(tr("翻译内容："));
    tasks->setStyleSheet(m_LabelStyle);
    QLabel* publisher=new QLabel(tr("发布者：%1").arg(myTask.GetPublisher()));
    publisher->setStyleSheet(m_LabelStyle);
    QTextBrowser *Task=new QTextBrowser;
    Task->setText(myTask.GetTask());
    Task->setStyleSheet(m_BrowserStyle);
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(myTask.GetTime()));
    time->setStyleSheet(m_LabelStyle);
    QLabel* leader=new QLabel(tr("负责人：%1").arg(myTask.GetLeader()));
    leader->setStyleSheet(m_LabelStyle);
    QLabel* checker=new QLabel(tr("审核人：%1").arg(myTask.GetTaskChecker()));
    checker->setStyleSheet(m_LabelStyle);
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(myTask.GetMoney()));
    money->setStyleSheet(m_LabelStyle);
    m_applyBtn[i].setText("申请译者");
    m_applyBtn[i].setStyleSheet(m_BtnStyle1);
    m_applyBtn[i].setFixedSize(171,51);
    //在垂直布局中添加控件
    QVBoxLayout *layout=new QVBoxLayout();
    layout->addWidget(title);
    layout->addWidget(taskClass);
    layout->addWidget(intro);
    layout->addWidget(Intro);
    layout->addWidget(publisher);
    layout->addWidget(leader);
    layout->addWidget(checker);
    layout->addWidget(time);
    layout->addWidget(date);
    layout->addWidget(money);
    layout->addWidget(tasks);
    layout->addWidget(Task);
    layout->addSpacing(30);
    layout->addWidget((m_applyBtn+i),0,Qt::AlignCenter);
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
    taskClass->setStyleSheet(m_LabelStyle);
    QLabel* title=new QLabel(tr("翻译标题：%1").arg(myTask.GetTitle()));
    title->setStyleSheet(m_LabelStyle);
    QLabel* publisher=new QLabel(tr("发布者：%1").arg(myTask.GetPublisher()));
    publisher->setStyleSheet(m_LabelStyle);
    QLabel *intro=new QLabel(tr("任务简介："));
    intro->setStyleSheet(m_LabelStyle);
    QTextBrowser* Intro=new QTextBrowser;
    Intro->setText(myTask.GetIntroduction());
    Intro->setStyleSheet(m_BrowserStyle);
    QLabel *tasks=new QLabel(tr("翻译内容："));
    tasks->setStyleSheet(m_LabelStyle);
    QTextBrowser *Task=new QTextBrowser;
    Task->setStyleSheet(m_BrowserStyle);
    Task->setText(myTask.GetTask());
    QLabel* date=new QLabel(tr("任务起始时间：%1年%2月%3日").arg(myTask.GetStartYear())
                            .arg(myTask.GetStartMonth())
                            .arg(myTask.GetStartDay()));
    date->setStyleSheet(m_LabelStyle);
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(myTask.GetTime()));
    time->setStyleSheet(m_LabelStyle);
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(myTask.GetMoney()));
    money->setStyleSheet(m_LabelStyle);
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
    inform2->setStyleSheet(m_LabelStyle);
    QList<taskTranslater> translaterList=g_backUp.m_listTaskTranslater.SearchTaskForTranslater(myTask.GetID());
    //声明一个tableWidget
    QTableWidget* table=new QTableWidget((translaterList.size()+1),5);
    SetTableStyle(table);
    table->setWindowTitle("译者");
    //设置表格为不可编辑
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
    table->setItem(0,4,new QTableWidgetItem(QString::number(myLeader.GetRewrdPoint())));
    table->setItem(1,0,new QTableWidgetItem(myTask.GetPublisher()));;
    table->setItem(1,1,new QTableWidgetItem("审核人"));
    iNum=g_backUp.m_listUser.SearchInList(myTask.GetTaskChecker());
    user myChecker=g_backUp.m_listUser.m_List[iNum];
    table->setItem(1,2,new QTableWidgetItem(myChecker.GetPhoneNum()));
    table->setItem(1,3,new QTableWidgetItem(myChecker.GetEnglish()));
    table->setItem(1,4,new QTableWidgetItem(QString::number(myChecker.GetRewrdPoint())));
    table->setItem(1,5,new QTableWidgetItem(myTask.GetPublisher()));
    for(int j=2;j<(translaterList.size()+2);j++){
        table->setItem(j,0,new QTableWidgetItem(translaterList[j-1].GetTranslater()));
        table->setItem(j,1,new QTableWidgetItem("译者"));
        iNum=g_backUp.m_listUser.SearchInList(myTask.GetLeader());
        user myTranslater=g_backUp.m_listUser.m_List[iNum];
        table->setItem(j,2,new QTableWidgetItem(myTranslater.GetPhoneNum()));
        table->setItem(j,3,new QTableWidgetItem(myTranslater.GetEnglish()));
        table->setItem(j,4,new QTableWidgetItem(QString::number(myTranslater.GetRewrdPoint())));
    }
    layout2->addWidget(inform2);
    layout2->addWidget(table);
    window2->setLayout(layout2);
    Tab->addTab(window2,tr("译者信息"));
    SetTabStyle(Tab);
    ui->stackedWidget->addWidget(Tab);
    //连接listWidget和stackedWidget
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}

void tasksPublished::GetPage101apply(){
    for(int i=0;i<g_backUp.m_listTaskPublisher.m_List.size();i++){
        if((m_applyBtn+i)->isDown()){
            OnClicked101apply(i);
        }
    }
}

void tasksPublished::GetPage101check(){
    for(int i=0;i<g_backUp.m_listTaskPublisher.m_List.size();i++){
        if((m_CheckerBtn+i)->isDown()){
            OnClicked101check(i);
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

void tasksPublished::OnClicked101apply(int i){
    taskPublisher myTask=g_backUp.m_listTaskPublisher.m_List[i];
    //判断用户是否已经报过名了
    if(!g_backUp.m_listSignUpForLeader.UserExists(g_backUp.m_User.GetID(),myTask.GetID())){
        if(g_backUp.m_User.GetRewrdPoint()<100){
            SetWarningBox("积分不足，请努力完成更多翻译任务后再来申请吧！");
        }
        else if(g_backUp.m_User.GetID()==myTask.GetPublisher()){
            SetWarningBox("您是发布者，不能报名负责人！");
        }
        else{
            SetInformBox("报名成功！");
            //后台执行负责人报名操作
            g_backUp.SignUpForLeader(i);
            close();
            tasksPublished r;
            r.ShowValue();;
            r.exec();
        }
    }
    else{
        SetWarningBox("您已经报过名了！");
    }
}

void tasksPublished::OnClicked101check(int i){
    taskPublisher myTask=g_backUp.m_listTaskPublisher.m_List[i];
    //判断用户是否已经报过名了
    if(!g_backUp.m_listSignUpForChecker.UserExists(g_backUp.m_User.GetID(),myTask.GetID())){
        if(g_backUp.m_User.GetRewrdPoint()<110){
            SetWarningBox("积分不足，请努力完成更多翻译任务后再来申请吧！");
        }
        else if(g_backUp.m_User.GetID()==myTask.GetPublisher()){
            SetWarningBox("您是发布者，不能报名审核人！");
        }
        else{
            SetInformBox("报名成功！");
            //后台执行负责人报名操作
            g_backUp.SignUpForChecker(i);
            close();
            tasksPublished r;
            r.ShowValue();;
            r.exec();
        }
    }
    else{
        SetWarningBox("您已经报过名了！");
    }
}

void tasksPublished::OnClicked202(int i){
    taskPublisher myTask=g_backUp.m_listTaskPublisher.m_List[i];
    //判断用户是否已经报过名了
    if(g_backUp.m_listSignUpForTranslater.
            UserExists(g_backUp.m_User.GetID(),myTask.GetID())){
        SetWarningBox("您已经报过名了！");
    }
    else if(g_backUp.m_User.GetID()==myTask.GetLeader()){
        SetWarningBox("您是该任务负责人，不能报名译者！");
    }
    else if(g_backUp.m_User.GetID()==myTask.GetTaskChecker()){
        SetWarningBox("您是该任务审核人，不能报名译者！");
    }
    else if(g_backUp.m_User.GetID()==myTask.GetPublisher()){
        SetWarningBox("您是该任务发布者，不能报名译者！");
    }
    else{
        SetInformBox("报名成功！");
        //后台执行译者报名操作
        g_backUp.SignUpForTranslaterDone(i);
        close();
        tasksPublished r;
        r.ShowValue();
        r.exec();
    }
}

void tasksPublished::SetStyle(){
    m_BtnStyle1="QPushButton{"
                "background-color:rgb(0, 188, 212);\
                 color: white;   "
                "border-radius: 10px; \
                 border-style: outset;font:12pt,\"等线\";}"
                 "QPushButton:hover{background-color:#198fb6; color: white;}"
                 "QPushButton:pressed{background-color:#3F51B5;\
                  border-style: inset; }";
    m_LabelStyle="QLabel{font:12pt,\"等线\";}";
    m_LineEditStyle="QLineEdit{font:12pt,\"等线\";}";
    m_TextEditStyle="QTextEdit{font:12pt,\"等线\";}";
    m_BrowserStyle="QTextBrowser{font:12pt,\"等线\";}";
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    SetListStyle(ui->listWidget);
    QString BtnStyle2="QPushButton{border:white;background-color:white; color:black;}"
          "QPushButton:hover{backgroud-color:white;color:#3F51B5;}"
          "QPushButton:pressed{background-color:white;color:#303F9F;}";
    ui->Main->setStyleSheet(BtnStyle2);
    ui->exitBtn->setStyleSheet(BtnStyle2);
}

void tasksPublished::SetTableStyle(QTableWidget *table){
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setDefaultSectionSize(60); //设置行高
    table->setFrameShape(QFrame::NoFrame); //设置无边框
    //table->setShowGrid(false); //设置不显示格子线
    table->horizontalHeader()->setFixedHeight(70); //设置表头的高度
    table->setStyleSheet("selection-background-color:#03A9F4;font:12pt,\"等线\";"); //设置选中背景色
    table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#B2EBF2;border:0px;font:12pt,\"等线\";}");
    table->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
      "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
      "QScrollBar::handle:hover{background:gray;}"
      "QScrollBar::sub-line{background:transparent;}"
      "QScrollBar::add-line{background:transparent;}");
    table->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
      "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
      "QScrollBar::handle:hover{background:gray;}"
      "QScrollBar::sub-line{background:transparent;}"
      "QScrollBar::add-line{background:transparent;}");
    QString BtnStyle2="QPushButton{border:white;background-color:white; color:black;}"
          "QPushButton:hover{backgroud-color:white;color:#3F51B5;}"
          "QPushButton:pressed{background-color:white;color:#303F9F;}";
    ui->Main->setStyleSheet(BtnStyle2);

}

void tasksPublished::SetListStyle(QListWidget* list){
    list->setIconSize(QSize(50,30));
    list->setStyleSheet("QListWidget{color:black; }"
                        "QListWidget::Item{padding-top:4px; padding-bottom:4px; font:12pt,\"等线\";}"
                        "QListWidget::Item:hover{background:#B2EBF2; }"
                        "QListWidget::item:selected{background:#03A9F4; color:white; }");
}

void tasksPublished::SetTabStyle(QTabWidget* tab){
    tab->setIconSize(QSize(50,30));
    tab->setStyleSheet("QTabWidget::pane{top:60px;border:none;}"
                       "QTabWidget::tab-bar{alignment:left;top:10px;left:30px;}");
    tab->tabBar()->setStyleSheet("QTabBar::tab{color:black;background:transparent;font:12pt,\"等线\";"
                                 "padding-right:30px;padding-left:30px;"
                                 "margin-right:0px;margin-left:0px;min-width:75px;min-height:30px;"
                                 "max-width:75px;max-height:30px;}"
                                 "QTabBar::tab:selected{color:#00BCD4;background:transparent;"
                                 "font:12pt,\"等线\";border-bottom:2px solid rgb(0, 188, 212);}"
                                 "QTabBar::hover:{color:rgb(0, 188, 212);background:transparent;"
                                 "font:12pt,\"等线\";}");
}

void tasksPublished::SetWarningBox(QString Text){
    QMessageBox message(this);
    message.setIconPixmap(QPixmap(":/images/warning.svg"));
    message.setStyleSheet("font:12pt,\"等线\";background:white;");
    message.setText(Text);
    message.setWindowTitle("警告");
    QPushButton* ysBtn=new QPushButton("确定");
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    message.addButton(ysBtn,QMessageBox::AcceptRole);
    message.exec();
}

void tasksPublished::SetInformBox(QString Text){
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

void tasksPublished::on_exitBtn_clicked()
{
    SqlQuery query;
    query.saveUser(g_backUp.m_listUser.m_List);
    query.saveTasks(g_backUp.m_listTaskPublisher.m_List);
    query.saveSignUpForLeader(g_backUp.m_listSignUpForLeader.m_List);
    query.saveSignUpForTranslater(g_backUp.m_listSignUpForTranslater.m_List);
    query.saveTaskLeader(g_backUp.m_listTaskLeader.m_List);
    query.saveTaskTranslater(g_backUp.m_listTaskTranslater.m_List);
    query.saveMessage(g_backUp.m_listMessage.m_List);
    query.saveSignUpForChecker(g_backUp.m_listSignUpForChecker.m_List);
    close();
    exit(0);
}
