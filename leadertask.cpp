#include "leadertask.h"
#include "ui_leadertask.h"
#include "list.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include "mainwindow.h"
#include "signupfortranslater.h"
#include <QTableWidget>
#include <QTextBrowser>
#include <QMessageBox>
#include <QTabWidget>

leaderTask::leaderTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::leaderTask)
{
    ui->setupUi(this);
}

leaderTask::~leaderTask()
{
    delete ui;
}

/*************************************************************************
【函数名称】EditUser
【函数功能】外部改变类内的m_myUser参数
【参数】user myNewUser
【返回值】 无
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
void leaderTask::EditUser(user myNewUser){
    m_myUser=myNewUser;
}

/*************************************************************************
【函数名称】EditList
【函数功能】外部改变类内的m_myUserm_List参数
【参数】list myNewList
【返回值】 无
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
void leaderTask::EditList(list myNewList){
    m_List=myNewList;
}

/*************************************************************************
【函数名称】ShowValue
【函数功能】显示整个界面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::ShowValue(){
    m_taskList=m_List.SearchTaskForLeader(m_myUser);
    m_yearEdit=new QLineEdit[m_taskList.size()];
    m_monthEdit=new QLineEdit[m_taskList.size()];
    m_dayEdit=new QLineEdit[m_taskList.size()];
    m_confrmBtn=new QPushButton[m_taskList.size()];
    m_table=new QTableWidget[m_taskList.size()];
    for(int i=0;i<m_taskList.size();i++){
        connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
        switch(m_taskList[i].GetFlag()){
        case 201:
            Show201(i);
            break;
        case 202:
            Show202(i);
            break;
        case 203:
            Show203(i);
            break;
        case 301:
            Show301(i);
            break;
        case 302:
            Show302(i);
            break;
        }
    }
}

/*************************************************************************
【函数名称】Show201
【函数功能】如果flag是201，显示界面
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::Show201(int i){
    m_iPage=i;
    ui->listWidget->insertItem(i,tr("<设定译者招募结束日期>%1").arg(m_taskList[i].GetIntroduction()));
    QWidget *window=new QWidget();
    QLabel *inform1=new QLabel(tr("恭喜成为负责人！请设定译者招募结束日期"));
    QLabel *inform2=new QLabel(tr("翻译任务详情如下："));
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
    QLabel *date1=new QLabel(tr("任务开始日期：%1年%2月%3日").arg(m_taskList[i].GetStartYear()).arg(m_taskList[i].GetStartMonth()).arg(m_taskList[i].GetStartDay()));
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(m_taskList[i].GetMoney()));
    QLabel *date2=new QLabel(tr("译者招募结束日期："));
    QLabel *year=new QLabel(tr("年"));
    QLabel *month=new QLabel(tr("月"));
    QLabel *day=new QLabel(tr("日"));
    (m_confrmBtn+i)->setText(tr("确定"));
    QHBoxLayout *date=new QHBoxLayout;
    date->addWidget(date2);
    date->addWidget(m_yearEdit+i);
    date->addWidget(year);
    date->addWidget(m_monthEdit+i);
    date->addWidget(month);
    date->addWidget(m_dayEdit+i);
    date->addWidget(day);
    QVBoxLayout *layout=new QVBoxLayout();
    layout->addWidget(inform1);
    layout->addWidget(inform2);
    layout->addWidget(taskClass);
    layout->addWidget(intro);
    layout->addWidget(tasks);
    layout->addWidget(time);
    layout->addWidget(date1);
    layout->addWidget(money);
    layout->addLayout(date);
    layout->addWidget(m_confrmBtn+i);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);
    connect(m_confrmBtn+i,SIGNAL(clicked()),this,SLOT(GetPage201()));
}

/*************************************************************************
【函数名称】Show202
【函数功能】如果flag是202，显示界面
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::Show202(int i){
    ui->listWidget->insertItem(i,tr("<译者报名火热进行中>%1").arg(m_taskList[i].GetIntroduction()));
    m_translaterList=m_List.SearchTranslaterForTask(m_taskList[i]);
    QWidget *window=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    QLabel *label=new QLabel(tr("已报名译者："));
    (m_table+i)->setColumnCount(4);
    (m_table+i)->setRowCount(m_translaterList.size());
    (m_table+i)->setEditTriggers(QAbstractItemView::NoEditTriggers);
    (m_table+i)->setWindowTitle("已报名译者");
    QStringList header;
    header<<"账号"<<"用户名"<<"英语资历"<<"积分";
    (m_table+i)->setHorizontalHeaderLabels(header);
    for(int j=0;j<m_translaterList.size();j++){
        (m_table+i)->setItem(j,0,new QTableWidgetItem(QString::number(m_translaterList[j].GetID())));
        (m_table+i)->setItem(j,1,new QTableWidgetItem(m_translaterList[j].GetName()));
        (m_table+i)->setItem(j,2,new QTableWidgetItem(m_translaterList[j].GetEnglish()));
        (m_table+i)->setItem(j,3,new QTableWidgetItem(QString::number(m_translaterList[j].GetRewrdPoint())));
    }
    layout->addWidget(label);
    layout->addWidget((m_table+i));
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);
}

/*************************************************************************
【函数名称】Show203
【函数功能】如果flag是203，显示界面
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::Show203(int i){
    m_iPage=i;
    ui->listWidget->insertItem(i,tr("<译者报名完毕，请分配任务！>%1").arg(m_taskList[i].GetIntroduction()));
    m_translaterList=m_List.SearchTranslaterForTask(m_taskList[i]);
    QWidget *window=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    QLabel *label1=new QLabel(tr("翻译原文"));
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(m_taskList[i].GetTime()));
    QLabel *date1=new QLabel(tr("任务开始日期：%1年%2月%3日").arg(m_taskList[i].GetStartYear()).arg(m_taskList[i].GetStartMonth()).arg(m_taskList[i].GetStartDay()));
    QLabel *label2=new QLabel(tr("已报名译者："));
    QTextBrowser *Task=new QTextBrowser;
    Task->setText(m_taskList[i].GetTask());
    (m_table+i)->setColumnCount(6);
    (m_table+i)->setRowCount(m_translaterList.size());
    (m_table+i)->setWindowTitle("分配任务");
    QStringList header;
    header<<"账号"<<"用户名"<<"英语资历"<<"积分"<<"任务"<<"任务截止日期（年-月-日）";
    (m_table+i)->setHorizontalHeaderLabels(header);
    for(int j=0;j<m_translaterList.size();j++){
        (m_table+i)->setItem(j,0,new QTableWidgetItem(QString::number(m_translaterList[j].GetID())));
        (m_table+i)->setItem(j,1,new QTableWidgetItem(m_translaterList[j].GetName()));
        (m_table+i)->setItem(j,2,new QTableWidgetItem(m_translaterList[j].GetEnglish()));
        (m_table+i)->setItem(j,3,new QTableWidgetItem(QString::number(m_translaterList[j].GetRewrdPoint())));
    }
    layout->addWidget(label1);
    layout->addWidget(Task);
    layout->addWidget(time);
    layout->addWidget(date1);
    layout->addWidget(label2);
    layout->addWidget(m_table+i);
    (m_confrmBtn+i)->setText(tr("确定"));
    layout->addWidget(m_confrmBtn+i);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);
    //如果负责人分配任务完成，确认按钮被点击，将表格中的内容存储
    connect(m_confrmBtn+i,SIGNAL(clicked()),this,SLOT(GetPage203()));

}

/*************************************************************************
【函数名称】Show301
【函数功能】如果flag是301，显示界面
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::Show301(int i){
    ui->listWidget->insertItem(i,tr("<译者的翻译出炉！请点评！>%1").arg(m_taskList[i].GetIntroduction()));
    QList<taskTranslater> myTask;
    //筛选已经提交的文章或已经修改并且提交的文章
    for(int j=0;j<m_List.TaskTranslater.size();j++){
        if(m_List.TaskTranslater[j].GetIDTask()==m_taskList[i].GetID()
                &&m_List.TaskTranslater[j].GetFlagToLeader()==1){
            myTask.append(m_List.TaskTranslater[j]);
        }
    }
    //对每一个译者构建一个tabWidget来显示对应的译文并让负责人进行评价
    QTabWidget *Tab=new QTabWidget;
    m_translaterTaskList=m_List.SearchTaskForTranslater(m_taskList[i].GetID());
    for(int j=0;j<m_translaterTaskList.size();j++){
        //如果flag是1或3，表明译者完成翻译或者完成修改
       if(m_translaterTaskList[j].GetFlagToLeader()==1||
                m_translaterTaskList[j].GetFlagToLeader()==3){
            int idUser=m_translaterTaskList[j].GetTranslater();
            QString userName;
            for(int t=0;t<m_List.User.size();t++){
                if(m_List.User[t].GetID()==idUser){
                    userName=m_List.User[t].GetName();
                }
            }
            QWidget *window=new QWidget;
            QLabel *title=new QLabel(tr("译者%1的翻译如下，请点评！").arg(userName));
            QLabel *date=new QLabel(tr("翻译截止日期：%1年%2月%3日").arg(m_translaterTaskList[j].GetEndYear()).arg(m_translaterTaskList[i].GetEndMonth()).arg(m_translaterTaskList[i].GetEndDay()));
            QLabel *inform1=new QLabel(tr("翻译原文："));
            QLabel *inform2=new QLabel(tr("译者翻译结果"));
            QLabel *inform3=new QLabel(tr("历史评价："));
            QLabel *inform4=new QLabel(tr("我的评价："));
            QTextBrowser *Task=new QTextBrowser;
            Task->setText(m_translaterTaskList[j].GetTask());
            QTextBrowser *Result=new QTextBrowser;
            Result->setText(m_translaterTaskList[j].GetResult());
            QTextBrowser *comment=new QTextBrowser;
            comment->setText(m_translaterTaskList[j].GetComment());
            QTextEdit *newComment=new QTextEdit;
            newComment->setText(m_translaterTaskList[j].GetCommentEditting());
            QPushButton *saveBtn=new QPushButton(tr("暂存"));
            QPushButton *confrmBtn=new QPushButton(tr("确定"));
            QPushButton *endBtn=new QPushButton(tr("收稿"));
            QVBoxLayout *layout=new QVBoxLayout;
            layout->addWidget(title);
            layout->addWidget(date);
            layout->addWidget(inform1);
            layout->addWidget(Task);
            layout->addWidget(inform2);
            layout->addWidget(Result);
            layout->addWidget(inform3);
            layout->addWidget(comment);
            layout->addWidget(inform4);
            layout->addWidget(newComment);
            QHBoxLayout *Btn=new QHBoxLayout;
            Btn->addWidget(saveBtn);
            Btn->addWidget(confrmBtn);
            Btn->addWidget(endBtn);
            layout->addLayout(Btn);
            window->setLayout(layout);
            Tab->addTab(window,userName);
            //如果点击提交，改变flag使得译者可见，负责人页面不必显示
            //修改list当中译者的历史评价的内容
            if(confrmBtn->isEnabled()){
                m_translaterTaskList[j].AddComment(comment->toPlainText());
                m_translaterTaskList[j].EditCommentEditting(NULL);
                m_translaterTaskList[j].EditFlagToLeader(2);
                m_List.updateList(m_translaterTaskList[j]);
            }
            //如果点击暂存，维持flag不变并储存译者
            else if(saveBtn->isEnabled()){
                m_translaterTaskList[j].EditCommentEditting(comment->toPlainText());
                m_translaterTaskList[j].EditFlagToLeader(3);
                m_List.updateList(m_translaterTaskList[j]);
            }
            else if(endBtn->isEnabled()){
                m_translaterTaskList[j].EditFlagToLeader(5);
                m_List.updateList(m_translaterTaskList[j]);
                //发送信息告诉译者任务通过，不用修改，等酬金
                //检测是否所有任务都已经通过
                int flag=1;
                for(int t=0;t<m_List.TaskTranslater.size();i++){
                    if(m_List.TaskTranslater[j].GetIDTask()==
                            m_translaterTaskList[j].GetIDTask()){
                        if(m_List.TaskTranslater[j].GetFlagToLeader()!=5){
                            flag=0;
                        }
                    }
                }
                if(flag==1){
                    m_translaterTaskList[j].EditFlag(302);
                    m_List.updateList(m_translaterTaskList[j]);
                }
            }
            ui->stackedWidget->addWidget(Tab);
        }
    }
}

/*************************************************************************
【函数名称】Show302
【函数功能】如果flag是302，显示界面
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::Show302(int i){
    ui->listWidget->insertItem(i,tr("<所有译者的翻译均已通过，请整合译文！>%1").arg(m_taskList[i].GetIntroduction()));
    m_translaterTaskList=m_List.SearchTaskForTranslater(m_taskList[i].GetID());
    QLabel *inform1=new QLabel(tr("所有译者的翻译均已通过，请整合译文！"));
    QLabel *inform2=new QLabel(tr("译文："));
    QLabel *inform3=new QLabel(tr("所有译文："));
    QTextEdit *myResult=new QTextEdit;
    myResult->setText(m_taskList[i].GetResultEditting());
    QPushButton *confrmBtn=new QPushButton;
    QPushButton *saveBtn=new QPushButton;
    QHBoxLayout *Btn=new QHBoxLayout;
    Btn->addWidget(confrmBtn);
    Btn->addWidget(saveBtn);
    QWidget *window=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    QTableWidget *table=new QTableWidget(m_translaterTaskList.size(),4);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setWindowTitle("翻译原文及译文");
    QStringList header;
    header<<"账号"<<"用户名"<<"原文"<<"译文";
    table->setHorizontalHeaderLabels(header);
    for(int j=0;j<m_translaterTaskList.size();j++){
        table->setItem(i,0,new QTableWidgetItem(QString::number
                                                (m_translaterTaskList[j].GetTranslater())));
        QString userName;
        for(int t=0;t<m_List.User.size();t++){
            if(m_List.User[t].GetID()==m_translaterTaskList[j].GetTranslater()){
                userName=m_List.User[t].GetName();
            }
        }
        table->setItem(i,1,new QTableWidgetItem(userName));
        table->setItem(i,2,new QTableWidgetItem(m_translaterTaskList[j].GetTask()));
        table->setItem(i,3,new QTableWidgetItem(m_translaterTaskList[j].GetResult()));
    }
    layout->addWidget(inform1);
    layout->addWidget(inform2);
    layout->addWidget(table);
    layout->addWidget(inform3);
    layout->addWidget(myResult);
    layout->addLayout(Btn);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);
    //如果负责人点击暂存，暂存负责人整合的任务
    if(saveBtn->isEnabled()){
        m_taskList[i].EditResultEditting(myResult->toPlainText());
        m_List.updateList(m_taskList[i]);
    }
    //如果负责人点击提交，将完成的任务交给负责人，并编辑任务状态为401
    else if(confrmBtn->isEnabled()){
        m_taskList[i].EditResult(myResult->toPlainText());
        m_taskList[i].EditFlag(401);
        m_List.updateList(m_taskList[i]);
    }
    ui->stackedWidget->addWidget(window);
}

/*************************************************************************
【函数名称】on_main_clicked
【函数功能】如果main按钮被按下，显示mainwindow
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::on_main_clicked()
{
    MainWindow *r=new MainWindow;
    r->EditList(m_List);
    r->EditUser(m_myUser);
    r->show();
    close();
}

void leaderTask::GetPage201(){
    connect(this,SIGNAL(SendPage(int)),this,SLOT(OnClicked_201(int)));
    emit SendPage(m_iPage);
}

void leaderTask::GetPage203(){
    connect(this,SIGNAL(SendPage(int)),this,SLOT(OnClicked_203(int)));
    emit SendPage(m_iPage);
}

void leaderTask::OnClicked_201(int i){
    int iTranslaterYear=m_yearEdit[i].text().toInt();
    int iTranslaterMonth=m_monthEdit[i].text().toInt();
    int iTranslaterDay=m_dayEdit[i].text().toInt();
    int iNum=ui->listWidget->currentRow();
    m_taskList[iNum].EditTranslaterYear(iTranslaterYear);
    m_taskList[iNum].EditTranslaterMonth(iTranslaterMonth);
    m_taskList[iNum].EditTranslaterDay(iTranslaterDay);
    m_taskList[iNum].EditFlag(202);
    m_List.updateList(m_taskList[iNum]);
    int iNumInList=m_List.searchTaskInList(m_taskList[iNum].GetID());
    m_List.TaskPublisher[iNumInList].EditFlag(202);
    QMessageBox::information(this, tr("提示"),
                       tr("译者报名截止时间设置成功！")
                      ,tr("确定"));
}

void leaderTask::OnClicked_203(int i){

    QMessageBox::information(this, tr("提示"),
                       tr("分配任务成功！")
                      ,tr("确定"));
    int iNum=ui->listWidget->currentRow();
    int iSize=m_List.SignUpForTranslater.size();
    for(int j=iSize-1;j>=0;j--){
        if(m_List.SignUpForTranslater[j].GetIDTask()==m_taskList[iNum].GetID()){
            m_List.SignUpForTranslater.removeAt(j);
        }
    }
    //改变任务状态为译者开始翻译状态
    m_taskList[iNum].EditFlag(301);
    m_List.updateList(m_taskList[iNum]);
    for(int j=0;j<m_translaterList.size();j++){
        //对表格的每一行，即每一个译者，生成一个译者的任务对象并且加入List当中
        if((m_table+i)->item(j,4)->text()!=NULL){
            taskTranslater myTask;
            myTask.EditIDTask(m_taskList[i].GetID());
            myTask.EditTaskClass(m_taskList[i].GetTaskClass());
            QString newTask=(m_table+i)->item(j,4)->text();
            myTask.EditTask(newTask);
            myTask.EditIntroduction(m_taskList[i].GetIntroduction());
            myTask.EditTime(m_taskList[i].GetTime());
            myTask.EditStartYear(m_taskList[i].GetStartYear());
            myTask.EditStartMonth(m_taskList[i].GetStartMonth());
            myTask.EditStartDay(m_taskList[i].GetStartDay());
            myTask.EditMoney(m_taskList[i].GetMoney());
            myTask.EditFlag(301);
            myTask.EditPublisher(m_taskList[i].GetPublisher());
            myTask.EditLeader(m_taskList[i].GetLeader());
            myTask.EditTranslater(m_translaterList[j].GetID());
            int iID;
            if(m_List.TaskTranslater.isEmpty()){
                iID=0;
            }
            else{
                iID=m_List.TaskTranslater.last().GetID()+1;
            }
            myTask.EditID(iID);
            //从表格中用户填写的截至日期当中提取截至的年月日
            QString EndDate=(m_table+i)->item(j,5)->text();
            int iEndYear=EndDate.mid(0,4).toInt();
            int iEndMonth=EndDate.mid(5,2).toInt();
            int iEndDay=EndDate.mid(8,2).toInt();
            myTask.EditEndYear(iEndYear);
            myTask.EditEndMonth(iEndMonth);
            myTask.EditEndDay(iEndDay);
            //将译者任务对象插入list中
            m_List.TaskTranslater.append(myTask);
        }
    }
    //删除译者报名表中的所有该任务的报名信息
    iSize=m_List.SignUpForTranslater.size();
    for(int j=iSize-1;j>=0;j--){
        if(m_List.SignUpForTranslater[j].GetIDTask()==
                m_taskList[iNum].GetID()){
            m_List.SignUpForTranslater.removeAt(j);
        }
    }
}
