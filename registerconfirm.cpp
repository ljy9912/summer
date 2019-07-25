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
【函数功能】通过参数显示用户相关信息
【参数】QString namevalue,QString phonevalue,QString IDValue,QString Englishvalue,int id
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void registerConfirm::showValue()         // 自定义槽
{
    ui->id->setText(tr("账号：%1").arg(m_BackUp.m_User.GetID()));
    ui->phonenum->setText(tr("电话：%1").arg(m_BackUp.m_User.GetPhoneNum()));
    ui->idnum->setText(tr("身份证号：%1").arg(m_BackUp.m_User.GetIDNum()));
    ui->Englishedit->setText(tr("英语资历：%1").arg(m_BackUp.m_User.GetEnglish()));
    ui->nameconfirm->setText(tr("用户名：%1").arg(m_BackUp.m_User.GetName()));
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
    r.EditBackUp(m_BackUp);
    r.show();
}

/*************************************************************************
【函数名称】EditList
【函数功能】外部更改List
【参数】list newList
【返回值】 无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void registerConfirm::EditBackUp(BackUp myBackUp){
    m_BackUp=myBackUp;
}
