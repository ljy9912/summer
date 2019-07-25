#include "register.h"
#include "ui_register.h"
#include <QMessageBox>
#include "registerconfirm.h"
#include "connection.h"
#include "logindialog.h"
#include "registerphonenum.h"
#include "registerid.h"
#include "user.h"
#include "list.h"
#include "sqlquery.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
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
【函数名称】on_canclbtn_clicked
【函数功能】 当canclbtn被单击之后，提示用户并清空用户编辑的信息
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void Register::on_canclbtn_clicked()
{
    QMessageBox *msgbx=new QMessageBox(this);
    msgbx->setText("你确定要退出吗？这会使编辑的文本清空。");
    msgbx->setWindowTitle("警告");
    QPushButton *ysBtn=new QPushButton(tr("确定"));
    QPushButton *moreBtn=new QPushButton(tr("取消"));
    msgbx->addButton(ysBtn,QMessageBox::AcceptRole);
    msgbx->addButton(moreBtn,QMessageBox::ActionRole);
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->nameedit,SLOT(setFocus()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->nameedit,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->pswrdedit,SLOT(clear()));
    msgbx->show();
}



/*************************************************************************
【函数名称】on_confrmbtn_clicked
【函数功能】在confrmbtn被按下之后，检验该用户名是否被注册过。若被注册过，清空用户名
的输入并提示用户重新输入；若没有被注册过，打开新页面registerConfirm并且将用户信息存入数据库
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void Register::on_confrmbtn_clicked()
{
    QString passwordvalue=ui->pswrdedit->text();
    QString confirmpswrdvalue=ui->cnfrmpswrdedit->text();
    if(passwordvalue!=confirmpswrdvalue){
        QMessageBox::warning(this, tr("警告"),
                           tr("密码与确认密码不符，请重新输入！")
                          ,tr("确定"));
        ui->pswrdedit->clear();
        ui->cnfrmpswrdedit->clear();
        ui->pswrdedit->setFocus();
        close();
        show();
        }
        else{
          int flag=0;
          m_BackUp.m_User.EditPassWrd(passwordvalue);
          m_BackUp.m_User.EditName(ui->nameedit->text());
          m_BackUp.m_User.EditPhoneNum(ui->phoneEdit->text());
          m_BackUp.m_User.EditIDNum(ui->ID->text());
          m_BackUp.m_User.EditEnglish(ui->EnglishEdit->text());
          for(int i=0;i<m_BackUp.m_List.User.size();i++){
              if((m_BackUp.m_List.User[i].GetName()==m_BackUp.m_User.GetName())){
                  QMessageBox::warning(this, tr("警告"),
                                     tr("用户名已被注册！")
                                    ,tr("确定"));
                  ui->nameedit->clear();
                  ui->nameedit->setFocus();
                  close();
                  show();
                  flag=1;
                }
          }
          if(flag==0){
              close();
              m_BackUp.m_User.EditID(m_BackUp.m_List.User[m_BackUp.m_List.User.size()-1].GetID()+1);
              m_BackUp.m_List.insertIntoList(m_BackUp.m_User);
              registerConfirm r;
              r.EditBackUp(m_BackUp);
              r.showValue();
              r.show();
          }
    }
}

/*************************************************************************
【函数名称】on_pushButton_clicked
【函数功能】按下pushButton后，打开新页面LoginDialog返回登陆页面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void Register::on_pushButton_clicked()
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
void Register::EditBackUp(BackUp myBackUp){
    m_BackUp=myBackUp;
}
