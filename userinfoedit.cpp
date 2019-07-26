#include "userinfoedit.h"
#include "ui_userinfoedit.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "userinfo.h"
#include "logindialog.h"
#include "sqlquery.h"



userInfoEdit::userInfoEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userInfoEdit)
{
    ui->setupUi(this);
}

userInfoEdit::~userInfoEdit()
{
    delete ui;

}

/*************************************************************************
【函数名称】showValue
【函数功能】通过user的对象显示用户信息方便用户编辑
【参数】user g_backUp.m_User
【返回值】 无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void userInfoEdit::showValue(user myUser){
    ui->ID->setText(tr("账号：%1").arg(myUser.GetID()));
    ui->phoneEdit->setText(myUser.GetPhoneNum());
    ui->IDNumEdit->setText(myUser.GetIDNum());
    ui->EnglishEdit->setText(myUser.GetEnglish());
    ui->credit->setText(tr("积分：%1").arg(myUser.GetRewrdPoint()));
    ui->money->setText(tr("余额：%1").arg(myUser.GetMoney()));
}

/*************************************************************************
【函数名称】on_pushButton_3_clicked
【函数功能】按下pushButton_3后，返回主界面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.15
【更改记录】
*************************************************************************/
void userInfoEdit::on_pushButton_3_clicked()
{
    MainWindow* r=new MainWindow;
    r->show();
    close();
}

/*************************************************************************
【函数名称】on_canclBtn_clicked
【函数功能】按下取消按钮后，提示用户信息将被清空，并询问用户是否继续，如果继续，清空用户填写的信息
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.15
【更改记录】
*************************************************************************/
void userInfoEdit::on_canclBtn_clicked()
{
    QMessageBox *msgbx=new QMessageBox(this);
    msgbx->setText("你确定要退出吗？这会使编辑的文本清空。");
    msgbx->setWindowTitle("警告");
    QPushButton *ysBtn=new QPushButton(tr("确定"));
    QPushButton *moreBtn=new QPushButton(tr("取消"));
    msgbx->addButton(ysBtn,QMessageBox::AcceptRole);
    msgbx->addButton(moreBtn,QMessageBox::ActionRole);
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->phoneEdit,SLOT(setText(tr("手机号：%1").arg(g_backUp.m_User.GetPhoneNum()))));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->IDNumEdit,SLOT(setText(tr("身份证号：%1").arg(g_backUp.m_User.GetIDNum()))));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->EnglishEdit,SLOT(setText(tr("英语资历：%1").arg(g_backUp.m_User.GetEnglish()))));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->phoneEdit,SLOT(setFocus()));
    msgbx->show();
}

/*************************************************************************
【函数名称】on_confrmBtn_clicked
【函数功能】按下确定后，提示用户信息修改成功并且储存信息
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.15
【更改记录】
*************************************************************************/
void userInfoEdit::on_confrmBtn_clicked()
{
    g_backUp.m_User.EditIDNum(ui->IDNumEdit->text());
    g_backUp.m_User.EditPhoneNum(ui->phoneEdit->text());
    g_backUp.m_User.EditEnglish(ui->EnglishEdit->text());
    g_backUp.m_List.updateList(g_backUp.m_User);
    QMessageBox::information(this, tr("提示"),
                       tr("信息修改成功！")
                      ,tr("确定"));
    userInfo r;
    r.showValue(g_backUp.m_User);
    r.exec();
    close();
}
