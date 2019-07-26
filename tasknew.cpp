#include "tasknew.h"
#include "ui_tasknew.h"
#include <QSqlQuery>
#include "taskpublish.h"
#include <QMessageBox>
#include "task.h"
#include "mainwindow.h"
#include "sqlquery.h"
#include <QDate>



taskNew::taskNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taskNew)
{
    ui->setupUi(this);
}

taskNew::~taskNew()
{
    delete ui;

}

/*************************************************************************
【函数名称】on_canclBtn_clicked
【函数功能】当canclBtn被单击之后，提示用户并清空用户编辑的信息
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void taskNew::on_canclBtn_clicked()
{
    QMessageBox *msgbx=new QMessageBox(this);
    msgbx->setText("你确定要退出吗？这会使编辑的文本清空。");
    msgbx->setWindowTitle("警告");
    QPushButton *ysBtn=new QPushButton(tr("确定"));
    QPushButton *moreBtn=new QPushButton(tr("取消"));
    msgbx->addButton(ysBtn,QMessageBox::AcceptRole);
    msgbx->addButton(moreBtn,QMessageBox::ActionRole);
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->title,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->translateTask,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->introEdit,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->time,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->leaderYear,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->leaderMonth,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->leaderDay,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->title,SLOT(setFocus()));
    msgbx->show();
}

/*************************************************************************
【函数名称】on_confrmBtn_clicked
【函数功能】confrmBtn被单击后，将用户信息存入对象传递中并且显示信息确认页面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
void taskNew::on_confrmBtn_clicked()
{
    myTask.EditTaskClass(ui->comboBox->currentIndex());
    myTask.EditIntroduction(ui->introEdit->toPlainText());
    myTask.EditTitle(ui->title->text());
    myTask.EditTask(ui->translateTask->toPlainText());
    myTask.EditTime(ui->time->text().toInt());
    myTask.EditLeaderYear(ui->leaderYear->text().toInt());
    myTask.EditLeaderMonth(ui->leaderMonth->text().toInt());
    myTask.EditLeaderDay(ui->leaderDay->text().toInt());
    myTask.EditMoney(ui->money->text().toDouble());
    myTask.EditPublisher(g_backUp.m_User.GetID());
    QDate time=QDate::currentDate();
    myTask.EditStartYear(time.year());
    myTask.EditStartMonth(time.month());
    myTask.EditStartDay(time.day());
    int lastID;
    if(g_backUp.m_List.TaskPublisher.isEmpty()){
        lastID=0;
    }
    else{
        lastID=g_backUp.m_List.TaskPublisher.last().GetID()+1;
    }
    myTask.EditID(lastID);
    g_backUp.m_List.insertIntoList(myTask);
    close();
    taskPublish r;
    r.EditTask(myTask);
    r.showValue();
    r.exec();
}


/*************************************************************************
【函数名称】showValue
【函数功能】通过对象task的传递显示任务的信息方便用户编辑
【参数】task myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void taskNew::showValue(){
    ui->comboBox->setCurrentIndex(myTask.GetTaskClass());
    ui->translateTask->setText(myTask.GetTask());
    ui->time->setText(tr("%1").arg(myTask.GetTime()));
    ui->leaderYear->setText(tr("%1").arg(myTask.GetLeaderYear()));
    ui->leaderMonth->setText(tr("%1").arg(myTask.GetLeaderMonth()));
    ui->leaderDay->setText(tr("%1").arg(myTask.GetLeaderDay()));
    ui->money->setText(tr("%1").arg(myTask.GetMoney()));
    ui->title->setText(tr("%1").arg(myTask.GetTitle()));
}


void taskNew::on_main_clicked()
{
    MainWindow* r=new MainWindow;
    r->show();
    close();
}
