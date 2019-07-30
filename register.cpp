#include "register.h"
#include "ui_register.h"
#include <QMessageBox>
#include "registerconfirm.h"
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
    SetStyle();


}

Register::~Register()
{
    delete ui;
    ui=NULL;
    delete dlg;
    dlg=NULL;
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
    SetCanclBox();
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
    if(!IsEmpty()){
        if(passwordvalue!=confirmpswrdvalue){
            SetWarningBox("密码与确认密码不符，请重新输入！");
            ui->pswrdedit->clear();
            ui->cnfrmpswrdedit->clear();
            ui->pswrdedit->setFocus();
            }
            else{
              if(g_backUp.m_listUser.NameExist(ui->nameedit->text())){
                  SetWarningBox("用户名已被注册！");
                  ui->nameedit->clear();
                  ui->nameedit->setFocus();
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
    r.exec();
}

bool Register::IsEmpty(){
    if(ui->nameedit->text().isEmpty()){
        SetWarningBox("用户名不能为空！");
        return true;
    }
    else if(ui->EnglishEdit->text().isEmpty()){
        SetWarningBox("英语资历不能为空！");
        return true;
    }
    else if(ui->pswrdedit->text().isEmpty()){
        SetWarningBox("密码不能为空！");
        return true;
    }
    else if(ui->cnfrmpswrdedit->text().isEmpty()){
        SetWarningBox("确认密码不能为空！");
        return true;
    }
    return false;
}

void Register::SetStyle(){
    m_BtnStyle1="QPushButton{background-color:rgb(0, 188, 212);\
            color: white;   border-radius: 10px; \
            border-style: outset;}"
           "QPushButton:hover{background-color:#198fb6; color: white;}"
          "QPushButton:pressed{background-color:#3F51B5;\
                           border-style: inset; }";
    QString BtnStyle2="QPushButton{border:white;background-color:white; color:black;}"
          "QPushButton:hover{backgroud-color:white;color:#3F51B5;}"
          "QPushButton:pressed{background-color:white;color:#303F9F;}";
    ui->confrmbtn->setStyleSheet(m_BtnStyle1);
    ui->canclbtn->setStyleSheet(m_BtnStyle1);
    ui->pushButton->setStyleSheet(BtnStyle2);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
}

void Register::SetCanclBox(){
    QMessageBox *msgbx=new QMessageBox(this);
    msgbx->setText("你确定要退出吗？这会使编辑的文本清空。");
    msgbx->setIconPixmap(QPixmap(":/images/warning.svg"));
    msgbx->setWindowTitle("警告");
    QPushButton *ysBtn=new QPushButton(tr("确定"));
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    QPushButton *moreBtn=new QPushButton(tr("取消"));
    moreBtn->setStyleSheet(m_BtnStyle1);
    moreBtn->setFixedSize(171,51);
    msgbx->addButton(ysBtn,QMessageBox::AcceptRole);
    msgbx->addButton(moreBtn,QMessageBox::ActionRole);
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->nameedit,SLOT(setFocus()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->nameedit,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->pswrdedit,SLOT(clear()));
    msgbx->show();
}

void Register::SetWarningBox(QString text){
    QMessageBox message(this);
    message.setIconPixmap(QPixmap(":/images/warning.svg"));
    message.setStyleSheet("font:12pt,\"等线\";background:white;");
    message.setText(text);
    QPushButton* ysBtn=new QPushButton("确定");
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    message.addButton(ysBtn,QMessageBox::AcceptRole);
    message.setWindowTitle("警告");
    message.exec();
}
