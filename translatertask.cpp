#include "translatertask.h"
#include "ui_translatertask.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QTextBrowser>
#include <QPushButton>
#include <QHBoxLayout>

translaterTask::translaterTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::translaterTask)
{
    ui->setupUi(this);
}

translaterTask::~translaterTask()
{
    delete ui;
}

void translaterTask::EditList(list myNewList){
    m_List=myNewList;
}

void translaterTask::EditUser(user myNewUser){
    m_User=myNewUser;
}

void translaterTask::ShowValue(){
    m_taskList=m_List.SearchTaskForTranslater(m_User);
    for(int i=0;i<m_taskList.size();i++){
        connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
        switch(m_taskList[i].GetFlag()){
        case 301:
            Show301(i);
            break;
        case 401:
            Show401(i);
            break;
        }
    }
}

void translaterTask::Show301(int i){
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
        QLabel *tasks=new QLabel(tr("翻译内容：%1").arg(m_taskList[i].GetTask()));
        QLabel *date=new QLabel(tr("翻译截止日期：%1年%2月%3日").arg(m_taskList[i].GetEndYear()).arg(m_taskList[i].GetEndMonth()).arg(m_taskList[i].GetEndDay()));
        QLabel *money=new QLabel(tr("任务总金额：%1元").arg(m_taskList[i].GetMoney()));
        QLabel *label2=new QLabel(tr("我的译文："));
        QTextBrowser *comment=new QTextBrowser;
        QTextEdit *result=new QTextEdit;
        QPushButton *saveBtn=new QPushButton;
        QPushButton *confrmBtn=new QPushButton;
        //对window添加排版
        QVBoxLayout *layout=new QVBoxLayout();
        layout->addWidget(taskClass);
        layout->addWidget(intro);
        layout->addWidget(tasks);
        layout->addWidget(date);
        layout->addWidget(money);
        layout->addWidget(label2);
        layout->addWidget(result);
        QHBoxLayout *btn=new QHBoxLayout;
        btn->addWidget(saveBtn);
        btn->addWidget(confrmBtn);
        layout->addLayout(btn);
        window->setLayout(layout);
        ui->stackedWidget->addWidget(window);
        if(saveBtn->isEnabled()){
            QString myResult=result->toPlainText();
            m_taskList[i].EditResult(myResult);
            m_taskList[i].EditFlagToLeader(0);
            m_List.updateList(m_taskList[i]);
        }
        else if(confrmBtn->isEnabled()){
            QString myResult=result->toPlainText();
            m_taskList[i].EditResult(myResult);
            m_taskList[i].EditFlagToLeader(1);
            m_List.updateList(m_taskList[i]);
        }
    }
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
        QTextEdit *result=new QTextEdit;
        comment->setText(m_taskList[i].GetResult());
        QPushButton *saveBtn=new QPushButton;
        QPushButton *confrmBtn=new QPushButton;
        //对window添加排版
        QVBoxLayout *layout=new QVBoxLayout();
        layout->addWidget(taskClass);
        layout->addWidget(intro);
        layout->addWidget(tasks);
        layout->addWidget(date);
        layout->addWidget(money);
        layout->addWidget(label1);
        layout->addWidget(comment);
        layout->addWidget(label2);
        layout->addWidget(result);
        QHBoxLayout *btn=new QHBoxLayout;
        btn->addWidget(saveBtn);
        btn->addWidget(confrmBtn);
        layout->addLayout(btn);
        window->setLayout(layout);
        ui->stackedWidget->addWidget(window);
        if(saveBtn->isEnabled()){
            QString myResult=result->toPlainText();
            m_taskList[i].EditResult(myResult);
            m_taskList[i].EditFlagToLeader(2);
            m_List.updateList(m_taskList[i]);
        }
        else if(confrmBtn->isEnabled()){
            QString myResult=result->toPlainText();
            m_taskList[i].EditResult(myResult);
            m_taskList[i].EditFlagToLeader(3);
            m_List.updateList(m_taskList[i]);
        }
    }
}


void translaterTask::Show401(int i){

}
