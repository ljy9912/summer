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
#include <QTextBrowser>



userInfo::userInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userInfo)
{
    ui->setupUi(this);
}

userInfo::~userInfo()
{
    delete ui;
    ui=NULL;
}

/*************************************************************************
【函数名称】showValue
【函数功能】根据user对象显示用户信息
【参数】user g_backUp.m_User
【返回值】 无
【开发者及日期】李佳芸 2019.7.14
【更改记录】
*************************************************************************/
void userInfo::showValue(){
    ui->ID->setText(tr("用户名：%1").arg(g_backUp.m_User.GetID()));
    ui->phoneNum->setText(tr("电话：%1").arg(g_backUp.m_User.GetPhoneNum()));
    ui->IDNum->setText(tr("身份证号：%1").arg(g_backUp.m_User.GetIDNum()));
    ui->credit->setText(tr("积分：%1").arg(g_backUp.m_User.GetRewrdPoint()));
    ui->money->setText(tr("余额：%1").arg(g_backUp.m_User.GetMoney()));
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
    close();
    userInfoEdit r;
    r.showValue();
    r.exec();

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

   int i=g_backUp.m_listUser.SearchInList(g_backUp.m_User);
   double money=g_backUp.m_listUser.m_List[i].GetMoney();
   money+=add;
   g_backUp.m_listUser.m_List[i].EditMoney(money);
   g_backUp.m_User.EditMoney(money);
   ui->money->setText(tr("余额：%1").arg(money));
   close();
   userInfo r;
   r.showValue();
   r.exec();
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
    close();
    MainWindow r;
    r.exec();
}

void userInfo::ShowMessage(){
    QList<Message> messageList;
    messageList=g_backUp.m_listMessage.SearchMessageforUser(g_backUp.m_User.GetID());
    for(int i=0;i<messageList.size();i++){
        QTextBrowser* window=new QTextBrowser;
        window->setText(messageList[i].GetContent());
        ui->toolBox->addItem(window,messageList[i].GetTitle());
    }

}
