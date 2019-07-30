#include "taskpublishedit.h"
#include "ui_taskpublishedit.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "taskpublish.h"
#include "task.h"
#include "sqlquery.h"
#include <QDate>



taskPublishEdit::taskPublishEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taskPublishEdit)
{
    ui->setupUi(this);
    SetStyle();
}

taskPublishEdit::~taskPublishEdit()
{
    delete ui;
    ui=NULL;
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
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    QPushButton *moreBtn=new QPushButton(tr("取消"));
    moreBtn->setStyleSheet(m_BtnStyle1);
    moreBtn->setFixedSize(171,51);
    msgbx->setStyleSheet("background:white;font:12pt,\"等线\";");
    msgbx->addButton(ysBtn,QMessageBox::AcceptRole);
    msgbx->addButton(moreBtn,QMessageBox::ActionRole);
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->title,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->introEdit,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->translateTask,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->time,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->leaderYear,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->leaderMonth,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->leaderDay,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->title,SLOT(setFocus()));
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
    if(!IsEmpty()){
    //判断输入日期是否有效
        QDate time;
        time.setDate(ui->leaderYear->text().toInt(),ui->leaderMonth->text().toInt(),
                     ui->leaderDay->text().toInt());
        QDate current=QDate::currentDate();
        //判断是否有效而且是否在当前日期之后
        if(time.isValid()&&current<=time){
            g_backUp.TaskPublishEdit(myTask,ui->comboBox->currentIndex(),ui->introEdit->toPlainText(),ui->title->text(),
                            ui->translateTask->toPlainText(),ui->time->text().toInt(),ui->leaderYear->text().toInt(),
                            ui->leaderMonth->text().toInt(),ui->leaderDay->text().toInt(),
                            ui->money->text().toDouble());
            close();
            taskPublish r;
            r.EditTask(myTask);
            r.showValue();
            r.exec();
        }
        //如果发生错误，输出警告
        else{
            SetWarningBox("输入日期无效，请重新输入！");
            //清空输入的无效日期
            ui->leaderYear->clear();
            ui->leaderMonth->clear();
            ui->leaderDay->clear();
            ui->leaderYear->setFocus();
        }
    }
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
    ui->title->setText(tr("%1").arg(myTask.GetTitle()));
}

bool taskPublishEdit::IsEmpty(){
    if(ui->title->text().isEmpty()){
        SetWarningBox("翻译标题不能为空！");
        return true;
    }
    else if(ui->introEdit->toPlainText().isEmpty()){
        SetWarningBox("任务简介不能为空！");
        return true;
    }
    else if(ui->translateTask->toPlainText().isEmpty()){
        SetWarningBox("翻译内容不能为空！");
        return true;
    }
    else if(ui->time->text().isEmpty()){
        SetWarningBox("任务周期不能为空！");
        return true;
    }
    else if(ui->leaderYear->text().isEmpty()||ui->leaderMonth->text().isEmpty()||
            ui->leaderDay->text().isEmpty()){
        SetWarningBox("负责人截止日期不能为空！");
        return true;
    }
    else if(ui->money->text().isEmpty()){
        SetWarningBox("任务总金额不能为空！");
        return true;
    }
    else if(ui->time->text().toInt()<=0){
        SetWarningBox("任务周期设定无效，请重新输入！");
        ui->time->clear();
        ui->time->setFocus();
        return true;
    }
    else if(ui->money->text().toDouble()<=0){
        SetWarningBox("任务总金额设定无效，请重新输入！");
        ui->money->clear();
        ui->money->setFocus();
        return true;
    }
    return false;
}

void taskPublishEdit::SetStyle(){
   m_BtnStyle1="QPushButton{background-color:rgb(0, 188, 212);\
            color: white;   border-radius: 10px; \
            border-style: outset;}"
           "QPushButton:hover{background-color:#198fb6; color: white;}"
          "QPushButton:pressed{background-color:#3F51B5;\
                           border-style: inset; }";
    ui->canclBtn->setStyleSheet(m_BtnStyle1);
    ui->confrmBtn->setStyleSheet(m_BtnStyle1);
    QString ComboBox="QComboBox{background-color:#B2EBF2;"
            "color: black;   border-radius: 10px;}"
             "QComboBox::drop-down {     subcontrol-origin:paddind;       subcontrol-position: top right;     width: 15px;"
             "border-left-width: 1px;     border-left-color: darkgray; "
            " border-left-style: solid;"
            "border-top-right-radius: 10px;"
              "border-bottom-right-radius: 10px;background-color:#B2EBF2; }"
             "QComboBox::down-arrow{border-image: url(:/images/arrowdown.png);border:white;}"
              "QComboBox QAbstractItemView {border: 2px solid darkgray;selection-background-color:##03A9F4;"
                     "selection-color:white;}";
    ui->comboBox->setStyleSheet(ComboBox);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
}

void taskPublishEdit::SetWarningBox(QString Text){
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
