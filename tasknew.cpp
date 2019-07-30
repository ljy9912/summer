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
    SetStyle();
}

taskNew::~taskNew()
{
    delete ui;
    ui=NULL;
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
    msgbx->setStyleSheet("background:white;font:12pt,\"等线\";");
    QPushButton *ysBtn=new QPushButton(tr("确定"));
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    QPushButton *moreBtn=new QPushButton(tr("取消"));
    //确定默认按钮
    moreBtn->setStyleSheet(m_BtnStyle1);
    moreBtn->setFixedSize(171,51);
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
                            ui->translateTask->toPlainText(),ui->time->text().toInt(),ui->leaderYear->text().toInt(),
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
            SetWarningBox("输入日期无效，请重新输入！");
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



bool taskNew::IsEmpty(){
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
    else if(ui->money->text().isEmpty()){
        SetWarningBox("任务总金额不能为空！");
        return true;
    }
    return false;
}

void taskNew::on_Main_clicked()
{
    close();
    MainWindow r;
    r.exec();
}

void taskNew::SetStyle(){
    m_BtnStyle1="QPushButton{background-color:rgb(0, 188, 212);\
            color: white;   border-radius: 10px; \
            border-style: outset;}"
           "QPushButton:hover{background-color:#198fb6; color: white;}"
          "QPushButton:pressed{background-color:#3F51B5;\
                           border-style: inset; }";
    QString BtnStyle2="QPushButton{border:white;background-color:white; color:black;}"
            "QPushButton:hover{backgroud-color:white;color:#3F51B5;}"
            "QPushButton:pressed{background-color:white;color:#303F9F;}";

   ui->canclBtn->setStyleSheet(m_BtnStyle1);
   ui->confrmBtn->setStyleSheet(m_BtnStyle1);
   ui->Main->setStyleSheet(BtnStyle2);
   QString ComboBox="QComboBox{background-color:#B2EBF2;"
           "color: black;   border-radius: 10px;}"
            "QComboBox::drop-down {     subcontrol-origin:paddind;       subcontrol-position: top right;     width: 15px;"
            "border-left-width: 1px;     border-left-color: darkgray; "
           " border-left-style: solid;"
           "border-top-right-radius: 10px;"
             "border-bottom-right-radius: 10px;background-color:#B2EBF2; }"
            "QComboBox::down-arrow{border-image: url(:/images/arrowdown.png);border:white;}"
             "QComboBox QAbstractItemView {border: 2px solid darkgray;selection-background-color:#03A9F4;"
                    "selection-color:white;}";

   ui->comboBox->setStyleSheet(ComboBox);
   setWindowFlags(Qt::FramelessWindowHint);
   setAttribute(Qt::WA_TranslucentBackground,true);

}

void taskNew::SetWarningBox(QString Text){
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
