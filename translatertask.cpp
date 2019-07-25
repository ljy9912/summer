#include "translatertask.h"
#include "ui_translatertask.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QTextBrowser>
#include <QPushButton>
#include <QHBoxLayout>
#include "mainwindow.h"
#include <QMessageBox>
#include "sqlquery.h"

translaterTask::translaterTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::translaterTask)
{
    ui->setupUi(this);
}

/*************************************************************************
【函数名称】~translaterTask
【函数功能】translatertTask的析构函数
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
translaterTask::~translaterTask()
{
    delete ui;
    delete m_confrmBtn;
    m_confrmBtn=NULL;
    delete m_saveBtn;
    m_saveBtn=NULL;
    delete m_result;
    m_result=NULL;
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
【函数名称】EditList
【函数功能】外部更改List参数
【参数】list myNewList
【返回值】无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
void translaterTask::EditBackUp(BackUp myBackUp){
    m_BackUp=myBackUp;
}

/*************************************************************************
【函数名称】ShowValue
【函数功能】显示界面
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void translaterTask::ShowValue(){
    m_taskList=m_BackUp.m_List.SearchTaskForTranslater(m_BackUp.m_User);
    m_result=new QTextEdit[m_taskList.size()];
    m_saveBtn=new QPushButton[m_taskList.size()];
    m_confrmBtn=new QPushButton[m_taskList.size()];
    for(int i=0;i<m_taskList.size();i++){
        connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,
                SLOT(setCurrentIndex(int)));
        m_iPage=i;
        if(m_taskList[i].GetFlag()==301){
            //译者第一次翻译的界面，没有负责人的评价
            if(m_taskList[i].GetFlagToLeader()==0){
                ui->listWidget->insertItem(i,tr("<任务来啦！>%1").arg(m_taskList[i].GetIntroduction()));
            
            
                QWidget *window=new QWidget();
                QLabel *label=new QLabel(tr("任务来啦！注意截止日期噢！"));
                QLabel *taskClass;
                if(m_taskList[i].GetTaskClass()==0){
                    taskClass=new QLabel(tr("翻译性质：中译英"));
                }
                else{
                    taskClass=new QLabel(tr("翻译性质：英译中"));
                }
                QLabel *intro=new QLabel(tr("任务简介：%1").arg(m_taskList[i].GetIntroduction()));
                QLabel *tasks=new QLabel(tr("翻译内容："));
                QTextBrowser *myTask=new QTextBrowser;
                myTask->setText(m_taskList[i].GetTask());
                QLabel *date=new QLabel(tr("翻译截止日期：%1年%2月%3日").arg(m_taskList[i].GetEndYear()).arg(m_taskList[i].GetEndMonth()).arg(m_taskList[i].GetEndDay()));
                QLabel *money=new QLabel(tr("任务总金额：%1元").arg(m_taskList[i].GetMoney()));
                QLabel *label2=new QLabel(tr("我的译文："));
                //对window添加排版
                QVBoxLayout *layout=new QVBoxLayout();
                layout->addWidget(label);
                layout->addWidget(taskClass);
                layout->addWidget(intro);
                layout->addWidget(tasks);
                layout->addWidget(myTask);
                layout->addWidget(date);
                layout->addWidget(money);
                layout->addWidget(label2);
                (m_result+i)->setText(m_taskList[i].GetResultEditting());
                layout->addWidget(m_result+i);
                QHBoxLayout *btn=new QHBoxLayout;
                (m_saveBtn+i)->setText(tr("暂存"));
                (m_confrmBtn+i)->setText(tr("提交"));
                btn->addWidget(m_saveBtn+i);
                btn->addWidget(m_confrmBtn+i);
                layout->addLayout(btn);
                window->setLayout(layout);
                ui->stackedWidget->addWidget(window);
                connect(m_saveBtn+i,SIGNAL(clicked()),this,SLOT(GetPage301save()));
                connect(m_confrmBtn+i,SIGNAL(clicked()),this,SLOT(GetPage301confrm()));
            }
            //译者修改翻译的界面，显示译者原来的翻译和历史评价
            else if(m_taskList[i].GetFlagToLeader()==2){
                ui->listWidget->insertItem(i,tr("<负责人有新的修改意见啦！>%1").arg(m_taskList[i].GetIntroduction()));
            
            
                QWidget *window=new QWidget();
                QLabel *label=new QLabel(tr("负责人有新的修改意见啦！请及时修改并提交！"));
                QLabel *taskClass;
                if(m_taskList[i].GetTaskClass()==0){
                    taskClass=new QLabel(tr("翻译性质：中译英"));
                }
                else{
                    taskClass=new QLabel(tr("翻译性质：英译中"));
                }
                QLabel *intro=new QLabel(tr("任务简介：%1").arg(m_taskList[i].GetIntroduction()));
                QLabel *tasks=new QLabel(tr("翻译内容：%1").arg(m_taskList[i].GetTask()));
                QLabel *money=new QLabel(tr("任务总金额：%1元").arg(m_taskList[i].GetMoney()));
                QLabel *label1=new QLabel(tr("负责人评论："));
                QLabel *label2=new QLabel(tr("我的译文："));
                QTextBrowser *comment=new QTextBrowser;
                comment->setText(m_taskList[i].GetComment());
                (m_saveBtn+i)->setText(tr("暂存"));
                (m_confrmBtn+i)->setText(tr("提交"));
                //对window添加排版
                QVBoxLayout *layout=new QVBoxLayout();
                layout->addWidget(label);
                layout->addWidget(taskClass);
                layout->addWidget(intro);
                layout->addWidget(tasks);
                layout->addWidget(money);
                layout->addWidget(label1);
                layout->addWidget(comment);
                layout->addWidget(label2);
                (m_result+i)->setText(m_taskList[i].GetResultEditting());
                layout->addWidget(m_result+i);
                QHBoxLayout *btn=new QHBoxLayout;
                btn->addWidget(m_saveBtn+i);
                btn->addWidget(m_confrmBtn+i);
                layout->addLayout(btn);
                window->setLayout(layout);
                ui->stackedWidget->addWidget(window);
                connect(m_saveBtn+i,SIGNAL(pressed()),this,SLOT(GetPage301save()));
                connect(m_confrmBtn+i,SIGNAL(pressed()),this,SLOT(GetPage301confrm()));
            }
        }
    }
}

/*************************************************************************
【函数名称】on_main_clicked
【函数功能】点击main之后，显示mainwindow
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.19
【更改记录】
*************************************************************************/
void translaterTask::on_main_clicked()
{
    MainWindow r;
    r.EditBackUp(m_BackUp);
    r.show();
    close();
}

/*************************************************************************
【函数名称】OnClicked_301save
【函数功能】点击暂存按钮并且获得i参数之后，显示存数据成功并且存储数据
【参数】int i
【返回值】无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void translaterTask::OnClicked_301save(int i){
    QMessageBox::information(this, tr("提示"),
                       tr("翻译暂存成功！")
                      ,tr("确定"));
    QString myResult=(m_result+i)->toPlainText();
    m_taskList[i].EditResultEditting(myResult);
    m_BackUp.m_List.updateList(m_taskList[i]);
}

/*************************************************************************
【函数名称】OnClicked_301confrm
【函数功能】点击确定按钮并且获得i参数之后，显示存数据成功并且存储数据
【参数】int i
【返回值】无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void translaterTask::OnClicked_301confrm(int i){
    QMessageBox::information(this, tr("提示"),
                       tr("翻译提交成功！")
                      ,tr("确定"));
    QString myResult=(m_result+i)->toPlainText();
    m_taskList[i].EditResult(myResult);
    if(m_taskList[i].GetFlagToLeader()==0){
        m_taskList[i].EditFlagToLeader(1);
    }
    else if(m_taskList[i].GetFlagToLeader()==2){
        m_taskList[i].EditFlagToLeader(3);
    }
    m_BackUp.m_List.updateList(m_taskList[i]);
}

/*************************************************************************
【函数名称】GetPage301save
【函数功能】得到按钮点击在stackedwidget中的page数
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void translaterTask::GetPage301save(){
    for(int i=0;i<m_taskList.size();i++){
        if(m_saveBtn[i].isDown()){
            OnClicked_301save(i);
        }
    }
}

/*************************************************************************
【函数名称】GetPage301confrm
【函数功能】得到按钮点击在stackedwidget中的page数
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void translaterTask::GetPage301confrm(){
    for(int i=0;i<m_taskList.size();i++){
        if(m_confrmBtn[i].isDown()){
            OnClicked_301confrm(i);
        }
    }
}
