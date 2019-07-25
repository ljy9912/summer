#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include "register.h"
#include "mainwindow.h"
#include "user.h"
#include "sqlquery.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;

}

/*************************************************************************
【函数名称】on_loginBtn_clicked
【函数功能】 当loginBtn被单击之后，验证账号与密码是否匹配，若匹配，则进入主界面，否则告
诉用户账号与密码不匹配
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void LoginDialog::on_loginBtn_clicked()
{
    int idnum=ui->usrLineEdit->text().toInt();
    QString pswrdvalue=ui->pswLineEdit->text();
    int flag=0;
    for(int i=0;i<m_BackUp.m_List.User.size();i++){
        if(m_BackUp.m_List.User[i].userWithPasswrd(idnum,pswrdvalue)){
            accept();
            flag=1;
            id=idnum;
            m_BackUp.m_User.attachIDToUser(id,m_BackUp.m_List.User);
            MainWindow *r=new MainWindow;
            r->EditBackUp(m_BackUp);
            r->show();
            close();
            break;
        }
    }
    if(flag==0){
          QMessageBox::warning(this, tr("警告"),
                               tr("账号或密码错误！"),
                                QMessageBox::tr("确定"));
          ui->usrLineEdit->clear();
          ui->pswLineEdit->clear();
          ui->usrLineEdit->setFocus();
       }
}

/*************************************************************************
【函数名称】on_RegisterBtn_clicked
【函数功能】 当RegisterBtn被单击之后，进入注册界面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/

void LoginDialog::on_RegisterBtn_clicked()
{
    Register *r=new Register;
    r->EditBackUp(m_BackUp);
    r->show();
    close();
}

/*************************************************************************
【函数名称】on_exitBtn_clicked
【函数功能】 当exitBtn被单击之后，提示用户并清空用户编辑的信息
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void LoginDialog::on_exitBtn_clicked()
{
    QMessageBox *msgbx=new QMessageBox(this);
    msgbx->setText("你确定要退出吗？这会使编辑的文本清空。");
    msgbx->setWindowTitle("警告");
    QPushButton *ysBtn=new QPushButton(tr("确定"));
    QPushButton *moreBtn=new QPushButton(tr("取消"));
    msgbx->addButton(ysBtn,QMessageBox::AcceptRole);
    msgbx->addButton(moreBtn,QMessageBox::ActionRole);
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->usrLineEdit,SLOT(setFocus()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->usrLineEdit,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->pswLineEdit,SLOT(clear()));
    msgbx->show();
}

/*************************************************************************
【函数名称】EditList
【函数功能】外部更改list接口
【参数】list newList
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void LoginDialog::EditBackUp(BackUp myBackUp){
    m_BackUp=myBackUp;
}
