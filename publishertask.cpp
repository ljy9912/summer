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
#include <QScrollBar>
#include <QListWidgetItem>
#include <QSpacerItem>



publisherTask::publisherTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::publisherTask)
{
    ui->setupUi(this);
    SetStyle();
}

publisherTask::~publisherTask()
{
    delete ui;
    ui=NULL;
    delete[] m_nameedit;
    m_nameedit=NULL;
    delete[] m_confrmBtn;
    m_confrmBtn=NULL;
    delete[] m_table;
    m_table=NULL;
    delete[] m_leaderMoney;
    m_leaderMoney=NULL;
    delete[] m_prolongBtn;
    m_prolongBtn=NULL;
    delete[] m_TaskTranslaterList;
    m_TaskTranslaterList=NULL;
    delete[] m_CheckerMoney;
    m_CheckerMoney=NULL;
    delete[] m_CheckerEdit;
    m_CheckerEdit=NULL;
    delete[] m_leaderList;
    m_leaderList=NULL;
    delete[] m_CheckerList;
    m_CheckerList=NULL;
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
    m_prolongBtn=new QPushButton[m_taskList.size()];
    m_table=new QTableWidget[m_taskList.size()];
    m_leaderMoney=new QLineEdit[m_taskList.size()];
    m_TaskTranslaterList=new QList<taskTranslater>[m_taskList.size()];
    m_CheckerEdit=new QLineEdit[m_taskList.size()];
    m_leaderList=new QList<signUpForLeader>[m_taskList.size()];
    m_CheckerList=new QList<signUpForChecker>[m_taskList.size()];
    m_CheckerMoney=new QLineEdit[m_taskList.size()];
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
        case 201:
        case 202:
        case 203:
        case 301:
        case 302:
            ShowDefault(i);
            break;
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
    QTabWidget* Tab=new QTabWidget;
    SetTabStyle(Tab);
    QListWidgetItem* item=new QListWidgetItem;
    item->setText(tr("<负责人和审核人正在火热报名中>%1").arg(m_taskList[i].GetTitle()));
    item->setIcon(QIcon(":/images/baomingblue.svg"));
    ui->listWidget->insertItem(i,item);
    m_leaderList[i]=g_backUp.m_listSignUpForLeader.SearchLeaderForTask(m_taskList[i].GetID());
    QWidget *window1=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    QLabel *label=new QLabel(tr("已报名负责人："));
    label->setStyleSheet(m_LabelStyle);
    QTableWidget *table=new QTableWidget(m_leaderList[i].size(),3);
    SetTableStyle(table);
    table->verticalHeader()->setDefaultSectionSize(60);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setWindowTitle("已报名负责人");
    QStringList header;
    header<<"用户名"<<"英语资历"<<"积分";
    table->setHorizontalHeaderLabels(header);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table->horizontalHeader()->setStretchLastSection(true);

    for(int j=0;j<m_leaderList[i].size();j++){
        table->setItem(j,0,new QTableWidgetItem(m_leaderList[i][j].GetID()));
        table->setItem(j,1,new QTableWidgetItem(m_leaderList[i][j].GetEnglish()));
        table->setItem(j,2,new QTableWidgetItem(QString::number(m_leaderList[i][j].GetRewrdPoint())));
    }
    layout->addWidget(label);
    layout->addWidget(table);
    window1->setLayout(layout);
    window1->setStyleSheet("background:white;");
    Tab->addTab(window1,"负责人");
    QWidget* window2=new QWidget;
    QVBoxLayout* layout2=new QVBoxLayout;
    m_CheckerList[i]=g_backUp.m_listSignUpForChecker.SearchCheckerForTask(m_taskList[i].GetID());
    QLabel* label2=new QLabel("已报名审核人：");
    label2->setStyleSheet(m_LabelStyle);
    QTableWidget* table2=new QTableWidget(m_CheckerList[i].size(),3);
    SetTableStyle(table2);
    table2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table2->setWindowTitle("已报名审核人");
    table->verticalHeader()->setDefaultSectionSize(60);
    QStringList header2;
    header2<<"用户名"<<"英语资历"<<"积分";
    table2->setHorizontalHeaderLabels(header2);
    table2->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table2->horizontalHeader()->setStretchLastSection(true);
    for(int j=0;j<m_CheckerList[i].size();j++){
        table2->setItem(j,0,new QTableWidgetItem(m_CheckerList[i][j].GetID()));
        table2->setItem(j,1,new QTableWidgetItem(m_CheckerList[i][j].GetEnglish()));
        table2->setItem(j,2,new QTableWidgetItem(QString::number(m_CheckerList[i][j].GetRewrdPoint())));
    }
    layout2->addWidget(label2);
    layout2->addWidget(table2);
    window2->setLayout(layout2);
    window2->setStyleSheet("background:white;");
    Tab->addTab(window2,"审核人");
    ui->stackedWidget->addWidget(Tab);
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
    QListWidgetItem* item=new QListWidgetItem;
    item->setIcon(QIcon(":/images/choose1.svg"));
    item->setText(tr("<负责人和审核人报名完毕，请选择！>%1").arg(m_taskList[i].GetTitle()));
    ui->listWidget->insertItem(i,item);

    QTabWidget* Tab=new QTabWidget;
    SetTabStyle(Tab);
    m_leaderList[i]=g_backUp.m_listSignUpForLeader.SearchLeaderForTask(m_taskList[i].GetID());
    QWidget *window1=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    QLabel *label=new QLabel(tr("已报名负责人："));
    label->setStyleSheet(m_LabelStyle);
    QTableWidget *table=new QTableWidget(m_leaderList[i].size(),3);
    SetTableStyle(table);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setWindowTitle("已报名负责人");
    QStringList header;
    header<<"用户名"<<"英语资历"<<"积分";
    table->setHorizontalHeaderLabels(header);
    table->verticalHeader()->setDefaultSectionSize(60); //设置行高
    for(int j=0;j<m_leaderList[i].size();j++){
        table->setItem(j,0,new QTableWidgetItem(m_leaderList[i][j].GetID()));
        table->setItem(j,1,new QTableWidgetItem(m_leaderList[i][j].GetEnglish()));
        table->setItem(j,2,new QTableWidgetItem(QString::number(m_leaderList[i][j].GetRewrdPoint())));
    }
    layout->addWidget(label);
    layout->addWidget(table);
    QHBoxLayout *layoutName=new QHBoxLayout;
    QLabel *labelName=new QLabel(tr("负责人："));
    labelName->setStyleSheet(m_LabelStyle);
    layoutName->addSpacing(300);
    layoutName->addWidget(labelName);
    layoutName->addWidget(m_nameedit+i);
    layoutName->addSpacing(300);
    (m_nameedit+i)->setStyleSheet(m_LineEditStyle);
    (m_nameedit+i)->setFixedSize(240,51);
    layout->addLayout(layoutName);
    window1->setLayout(layout);
    Tab->addTab(window1,"负责人");

    m_CheckerList[i]=g_backUp.m_listSignUpForChecker.SearchCheckerForTask(m_taskList[i].GetID());
    QWidget *window2=new QWidget;
    QVBoxLayout *layout2=new QVBoxLayout();
    QLabel *label2=new QLabel(tr("已报名审核人："));
    label2->setStyleSheet(m_LabelStyle);
    QTableWidget *table2=new QTableWidget(m_CheckerList[i].size(),3);
    SetTableStyle(table2);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setWindowTitle("已报名审核人");
    QStringList header2;
    header2<<"用户名"<<"英语资历"<<"积分";
    table2->setHorizontalHeaderLabels(header2);
    table2->verticalHeader()->setDefaultSectionSize(60); //设置行高
    for(int j=0;j<m_CheckerList[i].size();j++){
        table2->setItem(j,0,new QTableWidgetItem(m_CheckerList[i][j].GetID()));
        table2->setItem(j,1,new QTableWidgetItem(m_CheckerList[i][j].GetEnglish()));
        table2->setItem(j,2,new QTableWidgetItem(QString::number(m_CheckerList[i][j].GetRewrdPoint())));
    }
    layout2->addWidget(label2);
    layout2->addWidget(table2);

    m_confrmBtn[i].setText(tr("确定"));
    m_confrmBtn[i].setStyleSheet(m_BtnStyle1);
    m_confrmBtn[i].setFixedSize(171,51);
    m_prolongBtn[i].setText(tr("延期"));
    m_prolongBtn[i].setStyleSheet(m_BtnStyle1);
    m_prolongBtn[i].setFixedSize(171,51);
    QHBoxLayout* check=new QHBoxLayout;
    QLabel* labelName2=new QLabel(tr("审核人："));
    labelName2->setStyleSheet(m_LabelStyle);
    (m_CheckerEdit+i)->setStyleSheet(m_LineEditStyle);
    (m_CheckerEdit+i)->setFixedSize(240,51);
    check->addSpacing(300);
    check->addWidget(labelName2);
    check->addWidget(m_CheckerEdit+i);
    check->addSpacing(300);
    layout2->addLayout(check);

    QHBoxLayout* Btn=new QHBoxLayout;
    Btn->addWidget(m_confrmBtn+i);
    Btn->addWidget(m_prolongBtn+i);
    layout2->addSpacing(30);
    layout2->addLayout(Btn);
    window2->setLayout(layout2);
    Tab->addTab(window2,"审核人");

    ui->stackedWidget->addWidget(Tab);
    connect((m_confrmBtn+i),SIGNAL(pressed()),this,SLOT(GetPage102confrm()));
    connect((m_prolongBtn+i),SIGNAL(pressed()),this,SLOT(GetPage102prolong()));
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
    QListWidgetItem* item=new QListWidgetItem;
    item->setIcon(QIcon(":/images/choose.svg"));
    item->setText(tr("<任务翻译完毕，请确认！>%1").arg(m_taskList[i].GetTitle()));
    ui->listWidget->insertItem(i,item);
    QTabWidget *Tab=new QTabWidget;
    SetTabStyle(Tab);
    QLabel *intro=new QLabel(tr("翻译标题：%1").arg(m_taskList[i].GetTitle()));
    intro->setStyleSheet(m_LabelStyle);
    QLabel* inform=new QLabel("翻译原文：");
    inform->setStyleSheet(m_LabelStyle);
    QLabel* inform4=new QLabel("翻译结果");
    QTextBrowser *myTask=new QTextBrowser;
    myTask->setText(m_taskList[i].GetTask());
    myTask->setStyleSheet(m_BrowserStyle);
    QTextBrowser *myResult=new QTextBrowser;
    myResult->setStyleSheet(m_TextEditStyle);
    QLabel *inform1=new QLabel(tr("负责人酬金："));
    inform1->setStyleSheet(m_LabelStyle);
    QLabel* inform2=new QLabel("审核人酬金：");
    inform2->setStyleSheet(m_LabelStyle);
    int iIDTask=m_taskList[i].GetID();
    for(int j=0;j<g_backUp.m_listTaskLeader.m_List.size();j++){
        if(iIDTask==g_backUp.m_listTaskLeader.m_List[j].GetID()){
            myResult->setText(g_backUp.m_listTaskLeader.m_List[j].GetResult());
        }
    }
    QVBoxLayout *layout1=new QVBoxLayout;
    layout1->addWidget(intro);
    layout1->addWidget(inform);
    layout1->addWidget(myTask);
    layout1->addWidget(inform4);
    layout1->addWidget(myResult);
    QWidget* window1=new QWidget;
    window1->setLayout(layout1);
    window1->setStyleSheet("background-color:white;");
    Tab->addTab(window1,tr("译文"));
    QHBoxLayout *leader=new QHBoxLayout;
    leader->addSpacing(200);
    leader->addWidget(inform1);
    (m_leaderMoney+i)->setStyleSheet(m_LineEditStyle);
    (m_leaderMoney+i)->setFixedSize(200,51);
    leader->addWidget(m_leaderMoney+i);
    leader->addSpacing(200);
    QHBoxLayout* checker=new QHBoxLayout;
    checker->addSpacing(200);
    checker->addWidget(inform2);
    (m_CheckerMoney+i)->setStyleSheet(m_LineEditStyle);
    (m_CheckerMoney+i)->setFixedSize(200,51);
    checker->addWidget(m_CheckerMoney+i);
    checker->addSpacing(200);
    QWidget *window2=new QWidget;
    QVBoxLayout *layout2=new QVBoxLayout();
    QLabel *inform3=new QLabel(tr("译者："));
    inform3->setStyleSheet(m_LabelStyle);
    m_TaskTranslaterList[i]=g_backUp.m_listTaskTranslater
            .SearchTaskForTranslater(m_taskList[i].GetID());
    SetTableStyle(m_table+i);
    (m_table+i)->setColumnCount(4);
    (m_table+i)->setRowCount(m_TaskTranslaterList[i].size());
    (m_table+i)->setWindowTitle("译者");
    (m_table+i)->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    (m_table+i)->horizontalHeader()->setStretchLastSection(true);
    (m_table+i)->verticalHeader()->setDefaultSectionSize(200); //设置行高
    QStringList header;
    header<<"用户名"<<"译文"<<"成果"<<"酬金";
    (m_table+i)->setHorizontalHeaderLabels(header);
    for(int j=0;j<m_TaskTranslaterList[i].size();j++){
        (m_table+i)->setItem(j,0,new QTableWidgetItem(QString::number(m_TaskTranslaterList[i][j].GetID())));
        (m_table+i)->setItem(j,1,new QTableWidgetItem(m_TaskTranslaterList[i][j].GetTask()));
        (m_table+i)->setItem(j,2,new QTableWidgetItem(m_TaskTranslaterList[i][j].GetResult()));
    }
    layout2->addLayout(leader);
    layout2->addLayout(checker);
    layout2->addWidget(inform3);
    layout2->addWidget((m_table+i));
    (m_confrmBtn+i)->setText(tr("确定"));
    (m_confrmBtn+i)->setStyleSheet(m_BtnStyle1);
    (m_confrmBtn+i)->setFixedSize(171,51);
    layout2->addWidget(m_confrmBtn+i,0,Qt::AlignCenter);
    window2->setLayout(layout2);
    window2->setStyleSheet("background-color:white;");
    Tab->addTab(window2,tr("分配酬金"));
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
    QListWidgetItem* item=new QListWidgetItem(QIcon(":/images/jinhangzhong.svg"),
                                              tr("<翻译任务进行中！>%1").arg(m_taskList[i].GetTitle()));
    ui->listWidget->insertItem(i,item);
    QLabel *inform=new QLabel(tr("翻译任务正在火热进行中，请耐心等待！"));
    inform->setStyleSheet(m_LabelStyle);
    QWidget *window=new QWidget();
    QLabel *taskClass;
    if(m_taskList[i].GetTaskClass()==0){
        taskClass=new QLabel(tr("翻译性质：中译英"));
    }
    else{
        taskClass=new QLabel(tr("翻译性质：英译中"));
    }
    taskClass->setStyleSheet(m_LabelStyle);
    QLabel* title=new QLabel(tr("翻译标题：%1").arg(m_taskList[i].GetTitle()));
    title->setStyleSheet(m_LabelStyle);
    QLabel *intro=new QLabel(tr("任务简介：%1").arg(m_taskList[i].GetIntroduction()));
    intro->setStyleSheet(m_LabelStyle);
    QLabel *tasks=new QLabel(tr("翻译内容：%1").arg(m_taskList[i].GetTask()));
    tasks->setStyleSheet(m_LabelStyle);
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(m_taskList[i].GetTime()));
    time->setStyleSheet(m_LabelStyle);
    QLabel *date=new QLabel(tr("负责人报名截至日期：%1年%2月%3日")
                            .arg(m_taskList[i].GetLeaderYear())
                            .arg(m_taskList[i].GetLeaderMonth())
                            .arg(m_taskList[i].GetLeaderDay()));
    date->setStyleSheet(m_LabelStyle);
    QLabel *money=new QLabel(tr("任务总金额：%1元")
                             .arg(m_taskList[i].GetMoney()));
    money->setStyleSheet(m_LabelStyle);
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
    window->setStyleSheet("background-color:white;");
    ui->stackedWidget->addWidget(window);
}




/*************************************************************************
【函数名称】OnClicked
【函数功能】点击之后的函数处理
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void publisherTask::OnClicked102confrm(int i){
    QString iIdLeader=m_nameedit[i].text().trimmed();
    QString iIDChecker=m_CheckerEdit[i].text().trimmed();
    if(g_backUp.m_listSignUpForLeader.UserExists(iIdLeader,m_taskList[i].GetID())&&
            g_backUp.m_listSignUpForChecker.UserExists(iIDChecker,m_taskList[i].GetID())){
        if(iIdLeader!=iIDChecker){
            SetInformBox("选择负责人和审核人成功！");
            g_backUp.SelectLeaderDone(m_taskList[i],iIdLeader,iIDChecker);

            close();
            publisherTask r;
            r.ShowValue();
            r.exec();
        }
        else{
            SetWarningBox("负责人和审核人不能相同！");
            m_nameedit[i].clear();
            m_nameedit[i].setFocus();
            m_CheckerEdit[i].clear();
        }
    }
    else{
        SetWarningBox("表中无此用户！");
        m_nameedit[i].clear();
        m_nameedit[i].setFocus();
        m_CheckerEdit[i].clear();
    }
}

/*************************************************************************
【函数名称】ShowValue
【函数功能】显示发布者任务界面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void publisherTask::GetPage102confrm(){
    for(int i=0;i<m_taskList.size();i++){
        if((m_confrmBtn+i)->isDown()){
            OnClicked102confrm(i);
        }
    }
}

void publisherTask::GetPage102prolong(){
    for(int i=0;i<m_taskList.size();i++){
        if((m_prolongBtn+i)->isDown()){
            OnClicked102prolong(i);
        }
    }
}

void publisherTask::OnClicked102prolong(int i){
    int iAdd= QInputDialog::getInt(this, "延期","请输入延期天数");
    if(iAdd>=0){
        g_backUp.Prolong_102(iAdd,m_taskList[i]);
        SetInformBox("延期成功！");
    }
    else{
        SetWarningBox("延期天数不能为负!");
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
    int iFlag=1;
    //译者分配钱数总和相加
    if(!((m_leaderMoney+i)->text().isEmpty())){
        if(!(m_CheckerMoney+i)->text().isEmpty()){
            moneySum+=((m_leaderMoney+i)->text().toDouble());
            moneySum+=((m_CheckerMoney+i)->text().toDouble());
            for(int j=0;j<m_TaskTranslaterList[i].size();j++){
                if((m_table+i)->item(j,3)!=NULL&&(m_table+i)->item(j,3)->text()!=""){
                     moneySum+=(m_table+i)->item(j,3)->text().toDouble();
                }
                else{
                    SetWarningBox("用户酬金不能为空！");
                    iFlag=0;
                    break;
                }
            }
        }
        else{
            SetWarningBox("审核人酬金不能为空！");
            iFlag=0;
        }
    }
    else{
        SetWarningBox("负责人酬金不能为空！");
        iFlag=0;
    }
    if(iFlag==1){
        while(g_backUp.m_User.GetMoney()<moneySum){
            double add= QInputDialog::getDouble(this, "充值",
                                                            "余额不足，请充值！");
            g_backUp.m_User.AddMoney(add);
        }
        SetInformBox("任务确认成功！");
        g_backUp.m_User.LoseMoney(moneySum);
        //将负责人的余额加入表中
        double dMyMoney=(m_leaderMoney+i)->text().toDouble();
        double dMyMoney2=(m_CheckerMoney+i)->text().toDouble();

        //发消息确认
        g_backUp.DistributeMoney_Leader(dMyMoney,m_taskList[i]);
        g_backUp.DistributeMoney_Checker(dMyMoney2,m_taskList[i]);
        //负责人加10分
        for(int j=0;j<m_TaskTranslaterList[i].size();j++){

            g_backUp.DistributeMoney_Translater((m_table+i)->item(j,3)->text().toDouble()
                                                ,m_TaskTranslaterList[i][j]);
        }
        g_backUp.DistributeMoney_Publisher(m_taskList[i],moneySum);


        close();
        publisherTask r;
        r.ShowValue();
        r.exec();
    }
}

void publisherTask::SetStyle(){
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

void publisherTask::SetTableStyle(QTableWidget *table){
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table->horizontalHeader()->setStretchLastSection(true);
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

void publisherTask::SetListStyle(QListWidget* list){
    list->setIconSize(QSize(50,30));
    list->setStyleSheet("QListWidget{color:black; }"
                        "QListWidget::Item{padding-top:4px; padding-bottom:4px; font:12pt,\"等线\";}"
                        "QListWidget::Item:hover{background:#B2EBF2; }"
                        "QListWidget::item:selected{background:#03A9F4; color:white; }");
}

void publisherTask::SetTabStyle(QTabWidget* tab){
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

/*************************************************************************
【函数名称】on_Main_clicked
【函数功能】点击main后，返回主页面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void publisherTask::on_Main_clicked()
{
    close();
    MainWindow r;
    r.exec();
}

void publisherTask::SetWarningBox(QString Text){
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

void publisherTask::SetInformBox(QString Text){
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

void publisherTask::on_exitBtn_clicked()
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
