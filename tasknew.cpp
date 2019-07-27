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
    //显示messagebox询问是否要退出，有选项是和否
    QMessageBox *msgbx=new QMessageBox(this);
    msgbx->setText("你确定要退出吗？这会使编辑的文本清空。");
    msgbx->setWindowTitle("警告");
    QPushButton *ysBtn=new QPushButton(tr("确定"));
    QPushButton *moreBtn=new QPushButton(tr("取消"));
    //确定默认按钮
    msgbx->addButton(ysBtn,QMessageBox::AcceptRole);
    msgbx->addButton(moreBtn,QMessageBox::ActionRole);
    //按下确认按钮后清空所有信息
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->title,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->translateTask,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->introEdit,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->time,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->leaderYear,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->leaderMonth,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->leaderDay,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->title,SLOT(setFocus()));
    //显示
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
    //判断界面中是否有空未填
    if(!IsEmpty()){
    //判断输入日期是否有效
        QDate time;
        time.setDate(ui->leaderYear->text().toInt(),ui->leaderMonth->text().toInt()
                     ,ui->leaderDay->text().toInt());
        QDate current=QDate::currentDate();
        //判断是否有效而且是否在当前日期之后
        if(time.isValid()&&current<=time){
            myTask.EditInfo(ui->comboBox->currentIndex(),ui->introEdit->toPlainText(),ui->title->text(),
                            ui->title->text(),ui->time->text().toInt(),ui->leaderYear->text().toInt(),
                            ui->leaderMonth->text().toInt(),ui->leaderDay->text().toInt(),
                            ui->money->text().toDouble(),g_backUp.m_User.GetID());
            myTask.EditID(g_backUp.m_listTaskPublisher.GetID());
            g_backUp.m_listTaskPublisher.InsertIntoList(myTask);
            close();
            taskPublish r;
            r.EditTask(myTask);
            r.showValue();
            r.exec();
        }
        //如果发生错误，输出警告
        else{
            QMessageBox::warning(this, tr("警告"),
                               tr("输入日期无效，请重新输入！")
                              ,tr("确定"));
            //清空输入的无效日期
            ui->leaderYear->clear();
            ui->leaderMonth->clear();
            ui->leaderDay->clear();
            ui->leaderYear->setFocus();
        }
    }
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

bool taskNew::IsEmpty(){
    if(ui->title->text().isEmpty()){
        QMessageBox::warning(this, tr("警告"),
                           tr("翻译标题不能为空！")
                          ,tr("确定"));
        return true;
    }
    else if(ui->introEdit->toPlainText().isEmpty()){
        QMessageBox::warning(this, tr("警告"),
                           tr("任务简介不能为空！")
                          ,tr("确定"));
        return true;
    }
    else if(ui->translateTask->toPlainText().isEmpty()){
        QMessageBox::warning(this, tr("警告"),
                           tr("翻译内容不能为空！")
                          ,tr("确定"));
        return true;
    }
    else if(ui->time->text().isEmpty()){
        QMessageBox::warning(this, tr("警告"),
                           tr("任务周期不能为空！")
                          ,tr("确定"));
        return true;
    }
    else if(ui->leaderYear->text().isEmpty()||ui->leaderMonth->text().isEmpty()||
            ui->leaderDay->text().isEmpty()){
        QMessageBox::warning(this, tr("警告"),
                           tr("负责人截止日期不能为空！")
                          ,tr("确定"));
        return true;
    }
    else if(ui->time->text().toInt()<=0){
        QMessageBox::warning(this, tr("警告"),
                           tr("任务周期设定无效，请重新输入！")
                          ,tr("确定"));
        ui->time->clear();
        ui->time->setFocus();
        return true;
    }
    else if(ui->money->text().toDouble()<=0){
        QMessageBox::warning(this, tr("警告"),
                           tr("任务总金额设定无效，请重新输入！")
                          ,tr("确定"));
        ui->money->clear();
        ui->money->setFocus();
        return true;
    }
    else if(ui->money->text().isEmpty()){
        QMessageBox::warning(this, tr("警告"),
                           tr("任务总金额不能为空！")
                          ,tr("确定"));
        return true;
    }
    return false;
}
