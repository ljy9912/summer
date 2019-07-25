#include "taskpublishedit.h"
#include "ui_taskpublishedit.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "taskpublish.h"
#include "task.h"
#include "sqlquery.h"

taskPublishEdit::taskPublishEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taskPublishEdit)
{
    ui->setupUi(this);
}

taskPublishEdit::~taskPublishEdit()
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
【函数名称】on_canclBtn_clicked
【函数功能】当canclBtn被单击之后，提示用户并清空用户编辑的信息
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.15
【更改记录】
*************************************************************************/
void taskPublishEdit::on_canclBtn_clicked()
{
    QMessageBox *msgbx=new QMessageBox(this);
    msgbx->setText("你确定要退出吗？这会使编辑的文本清空。");
    msgbx->setWindowTitle("警告");
    QPushButton *ysBtn=new QPushButton(tr("确定"));
    QPushButton *moreBtn=new QPushButton(tr("取消"));
    msgbx->addButton(ysBtn,QMessageBox::AcceptRole);
    msgbx->addButton(moreBtn,QMessageBox::ActionRole);
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->introEdit,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->translateTask,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->time,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->leaderYear,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->leaderMonth,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->leaderDay,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->translateTask,SLOT(setFocus()));
    msgbx->show();
}

/*************************************************************************
【函数名称】on_confrmBtn_clicked
【函数功能】当按下confrmBtn后，将信息存储至task的对象中并将其传入用户信息确认页面中
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.15
【更改记录】
*************************************************************************/
void taskPublishEdit::on_confrmBtn_clicked()
{
    myTask.EditTaskClass(ui->comboBox->currentIndex());
    myTask.EditIntroduction(ui->introEdit->toPlainText());
    myTask.EditTask(ui->translateTask->toPlainText());
    myTask.EditTime(ui->time->text().toInt());
    myTask.EditLeaderYear(ui->leaderYear->text().toInt());
    myTask.EditLeaderMonth(ui->leaderMonth->text().toInt());
    myTask.EditLeaderDay(ui->leaderDay->text().toInt());
    myTask.EditMoney(ui->money->text().toDouble());
    myTask.EditPublisher(m_BackUp.m_User.GetID());
    m_BackUp.m_List.updateList(myTask);
    close();
    taskPublish r;
    r.EditBackUp(m_BackUp);
    r.showValue();
    r.show();
}

/*************************************************************************
【函数名称】editTask
【函数功能】外部更改该类的task
【参数】taskPublisher myNewTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.15
【更改记录】
*************************************************************************/
void taskPublishEdit::EditBackUp(BackUp myBackUp){
    m_BackUp=myBackUp;
}

void taskPublishEdit::EditTask(taskPublisher myNewTask){
    myTask=myNewTask;
}

/*************************************************************************
【函数名称】showValue
【函数功能】通过task的对象储存的信息显示任务确认信息
【参数】task myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.15
【更改记录】
*************************************************************************/
void taskPublishEdit::showValue(){
    ui->comboBox->setCurrentIndex(myTask.GetTaskClass());
    ui->introEdit->setText(myTask.GetIntroduction());
    ui->translateTask->setText(myTask.GetTask());
    ui->time->setText(tr("%1").arg(myTask.GetTime()));
    ui->leaderYear->setText(tr("%1").arg(myTask.GetLeaderYear()));
    ui->leaderMonth->setText(tr("%1").arg(myTask.GetLeaderMonth()));
    ui->leaderDay->setText(tr("%1").arg(myTask.GetLeaderDay()));
    ui->money->setText(tr("%1").arg(myTask.GetMoney()));
}

