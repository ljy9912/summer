#include "registerconfirm.h"
#include "ui_registerconfirm.h"
#include "register.h"
#include "logindialog.h"
#include <QSqlQuery>
#include "sqlquery.h"



registerConfirm::registerConfirm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerConfirm)
{
    ui->setupUi(this);

}

registerConfirm::~registerConfirm()
{
    delete ui;

}

/*************************************************************************
【函数名称】showValue
【函数功能】通过参数显示用户相关信息
【参数】QString namevalue,QString phonevalue,QString IDValue,QString Englishvalue,int id
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void registerConfirm::showValue()         // 自定义槽
{
    ui->id->setText(tr("用户名：%1").arg(g_backUp.m_User.GetID()));
    ui->phonenum->setText(tr("电话：%1").arg(g_backUp.m_User.GetPhoneNum()));
    ui->idnum->setText(tr("身份证号：%1").arg(g_backUp.m_User.GetIDNum()));
    ui->Englishedit->setText(tr("英语资历：%1").arg(g_backUp.m_User.GetEnglish()));
}

/*************************************************************************
【函数名称】on_pushButton_clicked
【函数功能】按下pushButton后，打开新页面LoginDialog返回登陆页面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void registerConfirm::on_pushButton_clicked()
{
    close();
    LoginDialog r;
    r.exec();
}

