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
#include "sqlquery.h"


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
【函数名称】ShowValue
【函数功能】显示整个界面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::ShowValue(){
    m_taskList=g_backUp.m_List.SearchTaskForLeader(g_backUp.m_User);
    m_yearEdit=new QLineEdit[m_taskList.size()];
    m_monthEdit=new QLineEdit[m_taskList.size()];
    m_dayEdit=new QLineEdit[m_taskList.size()];
    m_confrmBtn=new QPushButton*[m_taskList.size()];
    m_table=new QTableWidget*[m_taskList.size()];
    m_saveBtn=new QPushButton*[m_taskList.size()];
    m_NewComment=new QTextEdit*[m_taskList.size()];
    m_endBtn=new QPushButton*[m_taskList.size()];
    m_myResult=new QTextEdit;
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
    m_confrmBtn[i]=new QPushButton(tr("确定"));
    ui->listWidget->insertItem(i,tr("<设定译者招募结束日期>%1").arg(m_taskList[i].GetTitle()));
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
    QLabel* title=new QLabel(tr("翻译标题：%1").arg(m_taskList[i].GetTitle()));
    QLabel *intro=new QLabel(tr("任务简介：%1").arg(m_taskList[i].GetIntroduction()));
    QLabel *tasks=new QLabel(tr("翻译内容：%1").arg(m_taskList[i].GetTask()));
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(m_taskList[i].GetTime()));
    QLabel *date1=new QLabel(tr("任务开始日期：%1年%2月%3日").arg(m_taskList[i].GetStartYear()).arg(m_taskList[i].GetStartMonth()).arg(m_taskList[i].GetStartDay()));
    QLabel *money=new QLabel(tr("任务总金额：%1元").arg(m_taskList[i].GetMoney()));
    QLabel *date2=new QLabel(tr("译者招募结束日期："));
    QLabel *year=new QLabel(tr("年"));
    QLabel *month=new QLabel(tr("月"));
    QLabel *day=new QLabel(tr("日"));
    m_confrmBtn[i]->setText(tr("确定"));
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
    layout->addWidget(title);
    layout->addWidget(intro);
    layout->addWidget(tasks);
    layout->addWidget(time);
    layout->addWidget(date1);
    layout->addWidget(money);
    layout->addLayout(date);
    layout->addWidget(m_confrmBtn[i]);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);
    connect(m_confrmBtn[i],SIGNAL(pressed()),this,SLOT(GetPage201()));
}

/*************************************************************************
【函数名称】GetPage201
【函数功能】从leaderTask类中获得stackedwidget的i参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void leaderTask::GetPage201(){
    for(int i=0;i<m_taskList.size();i++){
        if(m_confrmBtn[i]->isDown()){
            OnClicked_201(i);
        }
    }
}

/*************************************************************************
【函数名称】OnClicked_201
【函数功能】在Show201中点击确定按钮之后并获得m_iPage的槽函数，存储用户填写的译者选择的截止日期
并更改任务状态为201
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void leaderTask::OnClicked_201(int i){
    int iTranslaterYear=m_yearEdit[i].text().toInt();
    int iTranslaterMonth=m_monthEdit[i].text().toInt();
    int iTranslaterDay=m_dayEdit[i].text().toInt();
    int iNum=ui->listWidget->currentRow();
    m_taskList[iNum].EditTranslaterYear(iTranslaterYear);
    m_taskList[iNum].EditTranslaterMonth(iTranslaterMonth);
    m_taskList[iNum].EditTranslaterDay(iTranslaterDay);
    m_taskList[iNum].EditFlag(202);
    g_backUp.m_List.updateList(m_taskList[iNum]);
    int iNumInList=g_backUp.m_List.searchTaskInList(m_taskList[iNum].GetID());
    g_backUp.m_List.TaskPublisher[iNumInList].EditFlag(202);
    QMessageBox::information(this, tr("提示"),
                       tr("译者报名截止时间设置成功！")
                      ,tr("确定"));
    g_backUp.SetTranslaterDone(g_backUp.m_User.GetID(),m_taskList[iNum].GetTitle());
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
    ui->listWidget->insertItem(i,tr("<译者报名火热进行中>%1").arg(m_taskList[i].GetTitle()));
    m_translaterList=g_backUp.m_List.SearchTranslaterForTask(m_taskList[i]);
    m_table[i]=new QTableWidget(m_translaterList.size(),3);
    QWidget *window=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    QLabel *label=new QLabel(tr("已报名译者："));
    m_table[i]->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table[i]->setWindowTitle("已报名译者");
    QStringList header;
    header<<"用户名"<<"英语资历"<<"积分";
    m_table[i]->setHorizontalHeaderLabels(header);
    for(int j=0;j<m_translaterList.size();j++){
        m_table[i]->setItem(j,0,new QTableWidgetItem(m_translaterList[j].GetID()));
        m_table[i]->setItem(j,1,new QTableWidgetItem(m_translaterList[j].GetEnglish()));
        m_table[i]->setItem(j,2,new QTableWidgetItem(QString::number(m_translaterList[j].GetRewrdPoint())));
    }
    layout->addWidget(label);
    layout->addWidget(m_table[i]);
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
    ui->listWidget->insertItem(i,tr("<译者报名完毕，请分配任务！>%1").arg(m_taskList[i].GetTitle()));
    m_translaterList=g_backUp.m_List.SearchTranslaterForTask(m_taskList[i]);
    m_table[i]=new QTableWidget(m_translaterList.size(),5);
    QWidget *window=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    QLabel *label1=new QLabel(tr("翻译原文"));
    QLabel *time=new QLabel(tr("任务周期：%1天").arg(m_taskList[i].GetTime()));
    QLabel *date1=new QLabel(tr("任务开始日期：%1年%2月%3日").arg(m_taskList[i].GetStartYear()).arg(m_taskList[i].GetStartMonth()).arg(m_taskList[i].GetStartDay()));
    QLabel *label2=new QLabel(tr("已报名译者："));
    QTextBrowser *Task=new QTextBrowser;
    Task->setText(m_taskList[i].GetTask());
    (m_table[i])->setWindowTitle("分配任务");
    QStringList header;
    header<<"用户名"<<"英语资历"<<"积分"<<"任务"<<"任务截止日期（年-月-日）";
    (m_table[i])->setHorizontalHeaderLabels(header);
    for(int j=0;j<m_translaterList.size();j++){
        (m_table[i])->setItem(j,0,new QTableWidgetItem(m_translaterList[j].GetID()));
        (m_table[i])->setItem(j,1,new QTableWidgetItem(m_translaterList[j].GetEnglish()));
        (m_table[i])->setItem(j,2,new QTableWidgetItem(QString::number(m_translaterList[j].GetRewrdPoint())));
    }
    layout->addWidget(label1);
    layout->addWidget(Task);
    layout->addWidget(time);
    layout->addWidget(date1);
    layout->addWidget(label2);
    layout->addWidget(m_table[i]);
    m_confrmBtn[i]=new QPushButton(tr("确定"));
    layout->addWidget(m_confrmBtn[i]);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);
    //如果负责人分配任务完成，确认按钮被点击，将表格中的内容存储
    connect(m_confrmBtn[i],SIGNAL(pressed()),this,SLOT(GetPage203()));

}

/*************************************************************************
【函数名称】GetPage203
【函数功能】从leaderTask类中获得stackedwidget的i参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void leaderTask::GetPage203(){
    for(int i=0;i<m_taskList.size();i++){
        if(m_confrmBtn[i]->isDown()){
            OnClicked_203(i);
        }
    }
}

/*************************************************************************
【函数名称】OnClicked_203
【函数功能】在Show203中点击确定按钮之后并获得m_iPage的槽函数，存储用户分配的任务并且
删除报名表中的该任务的报名信息，同时更改用户状态为301
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void leaderTask::OnClicked_203(int i){

    QMessageBox::information(this, tr("提示"),
                       tr("分配任务成功！")
                      ,tr("确定"));
    int iNum=ui->listWidget->currentRow();
    int iSize=g_backUp.m_List.SignUpForTranslater.size();
    for(int j=iSize-1;j>=0;j--){
        if(g_backUp.m_List.SignUpForTranslater[j].GetIDTask()==m_taskList[iNum].GetID()){
            g_backUp.m_List.SignUpForTranslater.removeAt(j);
        }
    }
    g_backUp.SelectTranslaterDone_Leader(g_backUp.m_User.GetID(),m_taskList[iNum].GetTitle());
    //改变任务状态为译者开始翻译状态
    m_taskList[iNum].EditFlag(301);
    g_backUp.m_List.updateList(m_taskList[iNum]);
    for(int j=0;j<m_translaterList.size();j++){
        //对表格的每一行，即每一个译者，生成一个译者的任务对象并且加入List当中
        if(m_table[i]->item(j,3)->text()!=NULL){
            taskTranslater myTask;
            myTask.EditIDTask(m_taskList[i].GetID());
            myTask.EditTaskClass(m_taskList[i].GetTaskClass());
            QString newTask=m_table[i]->item(j,3)->text();
            myTask.EditTask(newTask);
            myTask.EditTitle(m_taskList[i].GetTitle());
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
            if(g_backUp.m_List.TaskTranslater.isEmpty()){
                iID=0;
            }
            else{
                iID=g_backUp.m_List.TaskTranslater.last().GetID()+1;
            }
            myTask.EditID(iID);
            //从表格中用户填写的截至日期当中提取截至的年月日
            QString EndDate=m_table[i]->item(j,3)->text();
            int iEndYear=EndDate.mid(0,4).toInt();
            int iEndMonth=EndDate.mid(5,2).toInt();
            int iEndDay=EndDate.mid(8,2).toInt();
            myTask.EditEndYear(iEndYear);
            myTask.EditEndMonth(iEndMonth);
            myTask.EditEndDay(iEndDay);
            //将译者任务对象插入list中
            g_backUp.m_List.TaskTranslater.append(myTask);
            g_backUp.SelectTranslaterDone_Translater(m_taskList[iNum].GetTitle(),m_translaterList[j].GetID());
        }
    }
    //删除译者报名表中的所有该任务的报名信息
    iSize=g_backUp.m_List.SignUpForTranslater.size();
    for(int j=iSize-1;j>=0;j--){
        if(g_backUp.m_List.SignUpForTranslater[j].GetIDTask()==
                m_taskList[iNum].GetID()){
            g_backUp.m_List.SignUpForTranslater.removeAt(j);
        }
    }
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
    m_iPage=i;
    ui->listWidget->insertItem(i,tr("<译者的翻译出炉！请点评！>%1")
                               .arg(m_taskList[i].GetTitle()));
    //筛选已经提交的文章或已经修改并且提交的文章
    for(int j=0;j<g_backUp.m_List.TaskTranslater.size();j++){
        if(g_backUp.m_List.TaskTranslater[j].GetIDTask()==m_taskList[i].GetID()
                &&(g_backUp.m_List.TaskTranslater[j].GetFlagToLeader()==1||
                   (g_backUp.m_List.TaskTranslater[j].GetFlagToLeader())==3)){
            m_translaterTaskList.append(g_backUp.m_List.TaskTranslater[j]);
        }
    }
    //对每一个译者构建一个tabWidget来显示对应的译文并让负责人进行评价
    QTabWidget *Tab=new QTabWidget;
    m_NewComment[i]=new QTextEdit[m_translaterTaskList.size()];
    m_saveBtn[i]=new QPushButton[m_translaterTaskList.size()];
    m_confrmBtn[i]=new QPushButton[m_translaterTaskList.size()];
    m_endBtn[i]=new QPushButton[m_translaterTaskList.size()];
    for(int j=0;j<m_translaterTaskList.size();j++){
        m_iTab=j;
        //如果flag是1或3，表明译者完成翻译或者完成修改
       if(m_translaterTaskList[j].GetFlagToLeader()==1||
                m_translaterTaskList[j].GetFlagToLeader()==3){
            QString idUser=m_translaterTaskList[j].GetTranslater();
            QWidget *window=new QWidget;
            QLabel *title=new QLabel(tr("译者%1的翻译如下，请点评！").arg(idUser));
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
            (m_NewComment[i]+j)->setText(m_translaterTaskList[j].GetCommentEditting());
            (m_saveBtn[i]+j)->setText(tr("暂存"));
            (m_confrmBtn[i]+j)->setText(tr("确定"));
            (m_endBtn[i]+j)->setText(tr("收稿"));
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
            layout->addWidget(m_NewComment[i]+j);
            QHBoxLayout *Btn=new QHBoxLayout;
            Btn->addWidget(m_saveBtn[i]+j);
            Btn->addWidget(m_confrmBtn[i]+j);
            Btn->addWidget(m_endBtn[i]+j);
            layout->addLayout(Btn);
            window->setLayout(layout);
            Tab->addTab(window,idUser);
            //如果点击提交，改变flag使得译者可见，负责人页面不必显示
            //修改list当中译者的历史评价的内容
            connect(m_confrmBtn[i]+j,SIGNAL(pressed()),this,SLOT(GetPage301confrm()));
            connect(m_saveBtn[i]+j,SIGNAL(pressed()),this,SLOT(GetPage301save()));
            connect(m_endBtn[i]+j,SIGNAL(pressed()),this,SLOT(GetPage301end()));
        }
    ui->stackedWidget->addWidget(Tab);
    }
}

/*************************************************************************
【函数名称】GetPage301save
【函数功能】301，saveBtn被点击之后，从leaderTask类中获得stackedwidget的i参数和TabWidget的
j参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::GetPage301save(){
    for(int i=0;i<m_taskList.size();i++){
        for(int j=0;j<m_translaterTaskList.size();j++){
            if((m_saveBtn[i]+j)->isDown()){
                OnClicked_301save(i,j);
            }
        }
    }
}

/*************************************************************************
【函数名称】GetPage301confrm
【函数功能】301，confrmBtn被点击之后，从leaderTask类中获得stackedwidget的i参数和TabWidget的
j参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void leaderTask::GetPage301confrm(){
    for(int i=0;i<m_taskList.size();i++){
        for(int j=0;j<m_translaterTaskList.size();j++){
            if((m_confrmBtn[i]+j)->isDown()){
                OnClicked_301confrm(i,j);
            }
        }
    }
}

/*************************************************************************
【函数名称】GetPage301end
【函数功能】301，endBtn被点击之后，从leaderTask类中获得stackedwidget的i参数和TabWidget的
j参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void leaderTask::GetPage301end(){
    for(int i=0;i<m_taskList.size();i++){
        for(int j=0;j<m_translaterTaskList.size();j++){
            if((m_endBtn[i]+j)->isDown()){
                OnClicked_301end(i,j);
            }
        }
    }
}

/*************************************************************************
【函数名称】OnClicked_301save
【函数功能】301，saveBtn被点击之后，从leaderTask类中获得stackedwidget的i参数和TabWidget的
j参数
【参数】int i,int j
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void leaderTask::OnClicked_301save(int i,int j){
    QMessageBox::information(this, tr("提示"),
                       tr("评价暂存成功！")
                      ,tr("确定"));
    m_translaterTaskList[j].EditCommentEditting((m_NewComment[i]+j
                                                 )->toPlainText());
    m_translaterTaskList[j].EditFlagToLeader(3);
    g_backUp.m_List.updateList(m_translaterTaskList[j]);
    g_backUp.SubmitCommentDone_Leader(m_translaterTaskList[j].GetTitle(),
                                      m_translaterTaskList[j].GetLeader(),m_translaterTaskList[j].GetTranslater());
    g_backUp.SubmitCommentDone_Translater(m_translaterTaskList[j].GetTitle(),m_translaterTaskList[j].GetTranslater());
}

/*************************************************************************
【函数名称】OnClicked_301confrm
【函数功能】301，confrmBtn被点击之后，从leaderTask类中获得stackedwidget的i参数和TabWidget的
j参数
【参数】int i,int j
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void leaderTask::OnClicked_301confrm(int i,int j){
    QMessageBox::information(this, tr("提示"),
                       tr("评价成功！")
                      ,tr("确定"));
    m_translaterTaskList[j].AddComment((m_NewComment[i]+j)->toPlainText());
    m_translaterTaskList[j].EditCommentEditting(NULL);
    m_translaterTaskList[j].EditFlagToLeader(2);
    g_backUp.m_List.updateList(m_translaterTaskList[j]);
}

/*************************************************************************
【函数名称】OnClicked_301end
【函数功能】301，endBtn被点击之后，从leaderTask类中获得stackedwidget的i参数和TabWidget的
j参数
【参数】int i,int j
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void leaderTask::OnClicked_301end(int i,int j){
    QMessageBox::information(this, tr("提示"),
                       tr("收稿成功！")
                      ,tr("确定"));
    m_translaterTaskList[j].EditFlagToLeader(5);
    g_backUp.m_List.updateList(m_translaterTaskList[j]);
    //发送信息告诉译者任务通过，不用修改，等酬金
    //检测是否所有任务都已经通过
    int flag=1;
    for(int t=0;t<g_backUp.m_List.TaskTranslater.size();t++){
        if(g_backUp.m_List.TaskTranslater[t].GetIDTask()==
                m_translaterTaskList[j].GetIDTask()){
            if(g_backUp.m_List.TaskTranslater[t].GetFlagToLeader()!=5){
                flag=0;
            }
        }
    }
    if(flag==1){
        m_taskList[i].EditFlag(302);
        g_backUp.m_List.updateList(m_taskList[i]);
        g_backUp.EndTranslateDone_Leader(m_translaterTaskList[j].GetTitle()
                                         ,m_translaterTaskList[j].GetTranslater(),m_translaterTaskList[j].GetLeader());
    }
    else{
        g_backUp.StartIntegrate(m_translaterTaskList[j].GetTitle(),m_translaterTaskList[j].GetLeader());
    }
    g_backUp.EndTranslateDone_Translater(m_translaterTaskList[j].GetTitle()
                                         ,m_translaterTaskList[j].GetTranslater());
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
    ui->listWidget->insertItem(i,tr("<所有译者的翻译均已通过，请整合译文！>%1").arg(m_taskList[i].GetTitle()));
    m_translaterTaskList=g_backUp.m_List.SearchTaskForTranslater_302(m_taskList[i].GetID());
    QLabel *inform1=new QLabel(tr("所有译者的翻译均已通过，请整合译文！"));
    QLabel *inform2=new QLabel(tr("译文："));
    QLabel *inform3=new QLabel(tr("所有译文："));
    QHBoxLayout* Btn=new QHBoxLayout;
    m_confrmBtn[i]=new QPushButton(tr("确定"));
    m_saveBtn[i]=new QPushButton(tr("暂存"));
    (m_myResult+i)->setText(m_taskList[i].GetResultEditting());
    Btn->addWidget(m_confrmBtn[i]);
    Btn->addWidget(m_saveBtn[i]);
    QWidget *window=new QWidget;
    QVBoxLayout *layout=new QVBoxLayout();
    m_table[i]=new QTableWidget(m_translaterTaskList.size(),3);
    m_table[i]->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table[i]->setWindowTitle("翻译原文及译文");
    QStringList header;
    header<<"用户名"<<"原文"<<"译文";
    m_table[i]->setHorizontalHeaderLabels(header);
    for(int j=0;j<m_translaterTaskList.size();j++){
        m_table[i]->setItem(j,0,new QTableWidgetItem(m_translaterTaskList[j].GetTranslater()));
        m_table[i]->setItem(j,1,new QTableWidgetItem(m_translaterTaskList[j].GetTask()));
        m_table[i]->setItem(j,2,new QTableWidgetItem(m_translaterTaskList[j].GetResult()));
    }
    layout->addWidget(inform1);
    layout->addWidget(inform2);
    layout->addWidget(m_table[i]);
    layout->addWidget(inform3);
    layout->addWidget(m_myResult+i);
    layout->addLayout(Btn);
    window->setLayout(layout);
    ui->stackedWidget->addWidget(window);
    //如果负责人点击暂存，暂存负责人整合的任务
    connect(m_saveBtn[i],SIGNAL(pressed()),this,SLOT(GetPage302save()));
    //如果负责人点击提交，将完成的任务交给负责人，并编辑任务状态为401
    connect(m_confrmBtn[i],SIGNAL(pressed()),this,SLOT(GetPage302confrm()));
    ui->stackedWidget->addWidget(window);
}

/*************************************************************************
【函数名称】GetPage302save
【函数功能】在状态302下用户点击暂存按钮寻找用户正在按下的按钮
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.24
【更改记录】
*************************************************************************/
void leaderTask::GetPage302save(){
    for(int i=0;i<m_taskList.size();i++){
        if(m_saveBtn[i]->isDown()){
            OnClicked_302save(i);
        }
    }
}

/*************************************************************************
【函数名称】OnClicked_302save
【函数功能】用户按下i层的暂存按钮，进行数据存储等工作，并发消息
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.24
【更改记录】
*************************************************************************/
void leaderTask::OnClicked_302save(int i){
    QMessageBox::information(this, tr("提示"),
                       tr("译文整合暂存成功！")
                      ,tr("确定"));
    m_taskList[i].EditResultEditting((m_myResult+i)->toPlainText());
    g_backUp.m_List.updateList(m_taskList[i]);
}

/*************************************************************************
【函数名称】GetPage302confrm
【函数功能】如果用户在302状态按下确定按钮，寻找按下的按钮的所在层数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.24
【更改记录】
*************************************************************************/
void leaderTask::GetPage302confrm(){
    for(int i=0;i<m_taskList.size();i++){
        if(m_confrmBtn[i]->isDown()){
            OnClicked_302confrm(i);
        }
    }
}

/*************************************************************************
【函数名称】OnClicked_302confrm
【函数功能】用户按下i层的确定按钮，进行数据存储等工作，并发消息
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.24
【更改记录】
*************************************************************************/
void leaderTask::OnClicked_302confrm(int i){
    QMessageBox::information(this, tr("提示"),
                       tr("译文提交成功！")
                      ,tr("确定"));
    m_taskList[i].EditResult((m_myResult+i)->toPlainText());
    m_taskList[i].EditFlag(401);
    g_backUp.m_List.updateList(m_taskList[i]);
    int iNum=g_backUp.m_List.searchTaskInList(m_taskList[i].GetID());
    g_backUp.m_List.TaskPublisher[iNum].EditFlag(401);
    g_backUp.IntegratingDone_Leader(m_taskList[i].GetTitle(),m_taskList[i].GetLeader());
    g_backUp.IntegratingDone_Publisher(m_taskList[i].GetTitle(),m_taskList[i].GetPublisher());
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
    MainWindow* r=new MainWindow;
    r->show();
    close();
}
