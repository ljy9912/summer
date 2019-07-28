#include "register.h"
#include "ui_register.h"
#include <QMessageBox>
#include "registerconfirm.h"
#include "connection.h"
#include "logindialog.h"
#include "registerphonenum.h"
#include "registerid.h"
#include "user.h"
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
          if(g_backUp.m_listUser.NameExist(ui->nameedit->text())){
              QMessageBox::warning(this, tr("警告"),
                                 tr("用户名已被注册！")
                                ,tr("确定"));
              ui->nameedit->clear();
              ui->nameedit->setFocus();
              close();
              show();
            }
          else{
              close();
              g_backUp.Register(passwordvalue,ui->nameedit->text(),ui->phoneEdit->text(),
                                ui->ID->text(),ui->EnglishEdit->text());
              registerConfirm r;
              r.showValue();
              r.exec();
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
    LoginDialog* r=new LoginDialog;
    r->show();
}
