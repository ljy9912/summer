#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "user.h"
#include "userinfo.h"
#include "logindialog.h"
#include "tasknew.h"
#include "taskspublished.h"
#include "sqlquery.h"
#include "publishertask.h"
#include "leadertask.h"
#include "translatertask.h"
#include "sqlquery.h"
#include "messagebox.h"
#include <QDesktopWidget>
#include <QRect>



MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMaximumSize(1920,1080);
    setMinimumSize(1920,1080);
    QString BtnStyle1="QPushButton{background-color:rgb(0, 188, 212);\
            color: white;   border-radius: 10px; \
            border-style: outset;}"
           "QPushButton:hover{background-color:#198fb6; color: white;}"
          "QPushButton:pressed{background-color:#3F51B5;\
                           border-style: inset; }";
    QString BtnStyle2="QPushButton{background-color:#607D8B;\
            color: white;   border-radius: 10px; \
            border-style: outset;}"
           "QPushButton:hover{background-color:#198fb6; color: white;}"
          "QPushButton:pressed{background-color:#3F51B5;\
                           border-style: inset; }";
    ui->exitBtn->setStyleSheet(BtnStyle2);
    ui->MessageBox->setStyleSheet(BtnStyle1);
    ui->myTableBtn->setStyleSheet(BtnStyle1);
    ui->myTaskBtn->setStyleSheet(BtnStyle1);
    ui->pushButton->setStyleSheet(BtnStyle1);
    ui->getTask->setStyleSheet(BtnStyle1);
    ui->Publish->setStyleSheet(BtnStyle1);
    ui->publisher->setStyleSheet(BtnStyle1);
    QDesktopWidget *deskdop = QApplication::desktop();
    move((deskdop->width() - this->width())/2, (deskdop->height() - this->height())/2);

}

MainWindow::~MainWindow()
{
    delete ui;
    ui=NULL;
}

/*************************************************************************
【函数名称】on_pushButton_clicked
【函数功能】 当pushButton被单击之后，进入显示用户信息的窗口，并传递用户id的参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void MainWindow::on_pushButton_clicked()
{
    close();
    userInfo r;
    r.showValue();
    r.exec();
}


/*************************************************************************
【函数名称】on_Publish_clicked
【函数功能】 当Publish被按下后，打开taskNew页面并且传递id参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.13
【更改记录】
*************************************************************************/
void MainWindow::on_Publish_clicked()
{
    close();
    taskNew r;
    r.exec();
}

/*************************************************************************
【函数名称】on_getTask_clicked
【函数功能】 在按下getTask之后，打开tasksPublished页面，并且传递id参数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void MainWindow::on_getTask_clicked()
{
    close();
    tasksPublished r;
    r.ShowValue();
    r.exec();
}

void MainWindow::on_myTaskBtn_clicked()
{
    close();
    translaterTask r;
    r.ShowValue();
    r.exec();
}

void MainWindow::on_myTableBtn_clicked()
{
    close();
    leaderTask r;
    r.ShowValue();
    r.exec();

}

/*************************************************************************
【函数名称】on_publisher_clicked
【函数功能】在点击publisher之后，显示发布者任务页面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void MainWindow::on_publisher_clicked()
{
    close();
    publisherTask r;
    r.ShowValue();
    r.exec();

}

void MainWindow::on_MessageBox_clicked()
{
    close();
    MessageBox r;
    r.ShowMessage();
    r.exec();

}

void MainWindow::on_exitBtn_clicked()
{
    SqlQuery query;
    query.saveUser(g_backUp.m_listUser.m_List);
    query.saveTasks(g_backUp.m_listTaskPublisher.m_List);
    query.saveSignUpForLeader(g_backUp.m_listSignUpForLeader.m_List);
    query.saveSignUpForTranslater(g_backUp.m_listSignUpForTranslater.m_List);
    query.saveTaskLeader(g_backUp.m_listTaskLeader.m_List);
    query.saveTaskTranslater(g_backUp.m_listTaskTranslater.m_List);
    query.saveMessage(g_backUp.m_listMessage.m_List);
    close();
}
