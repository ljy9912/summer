#include "userinfo.h"
#include "ui_userinfo.h"
#include "logindialog.h"
#include "userinfoedit.h"
#include <QMessageBox>
#include "usermoney.h"
#include <QSqlQuery>
#include "mainwindow.h"
#include <QInputDialog>
#include "sqlquery.h"

userInfo::userInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userInfo)
{
    ui->setupUi(this);
}

userInfo::~userInfo()
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
【函数名称】showValue
【函数功能】根据user对象显示用户信息
【参数】user m_BackUp.m_User
【返回值】 无
【开发者及日期】李佳芸 2019.7.14
【更改记录】
*************************************************************************/
void userInfo::showValue(user myUser){
    ui->ID->setText(tr("账号：%1").arg(myUser.GetID()));
    ui->name->setText(tr("用户名：%1").arg(myUser.GetName()));
    ui->phoneNum->setText(tr("电话：%1").arg(myUser.GetPhoneNum()));
    ui->IDNum->setText(tr("身份证号：%1").arg(myUser.GetIDNum()));
    ui->credit->setText(tr("积分：%1").arg(myUser.GetRewrdPoint()));
    ui->money->setText(tr("余额：%1").arg(myUser.GetMoney()));
}

/*************************************************************************
【函数名称】on_editBtn_clicked
【函数功能】按下editBtn后，进入用户信息编辑界面并通过id传递信息
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.14
【更改记录】
*************************************************************************/
void userInfo::on_editBtn_clicked()
{
    userInfoEdit r;
    r.EditBackUp(m_BackUp);
    r.showValue(m_BackUp.m_User);
    r.show();
    close();
}

/*************************************************************************
【函数名称】on_moneyBtn_clicked
【函数功能】按下充值按钮后，根据用户输入的金额增加用户余额
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.13
【更改记录】
*************************************************************************/
void userInfo::on_moneyBtn_clicked()
{
    double add= QInputDialog::getDouble(this, "充值",
                                                   "请输入充值钱数");

   int i=m_BackUp.m_List.searchUserInList(m_BackUp.m_User);
   double money=m_BackUp.m_List.User[i].GetMoney();
   money+=add;
   m_BackUp.m_List.User[i].EditMoney(money);
   m_BackUp.m_User.EditMoney(money);
   ui->money->setText(tr("余额：%1").arg(money));
   close();
   show();
}

/*************************************************************************
【函数名称】editUser
【函数功能】外部更改该类的myUser
【参数】user myNewUser
【返回值】 无
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
void userInfo::EditBackUp(BackUp myBackUp){
    m_BackUp=myBackUp;
}

/*************************************************************************
【函数名称】on_main_clicked
【函数功能】按下main后，返回主界面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void userInfo::on_main_clicked()
{
    MainWindow r;
    r.EditBackUp(m_BackUp);
    r.show();
    close();
}

