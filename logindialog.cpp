#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include "register.h"
#include "mainwindow.h"
#include "user.h"
#include "sqlquery.h"
#include <QTextStream>



LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    SetStyle();
}

LoginDialog::~LoginDialog()
{
    delete ui;
    ui=nullptr;
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
{   if(!IsEmpty()){
        QString idnum=ui->usrLineEdit->text().trimmed();
        QString pswrdvalue=ui->pswLineEdit->text();
        int flag=0;
        for(int i=0;i<g_backUp.m_listUser.m_List.size();i++){
            if(g_backUp.m_listUser.m_List[i].userWithPasswrd(idnum,pswrdvalue)){
                accept();
                flag=1;
                m_id=idnum;
                g_backUp.m_User.attachIDToUser(m_id,g_backUp.m_listUser.m_List);
                close();
                MainWindow r;
                r.exec();
                break;
            }
        }
        if(flag==0){
              SetWarningBox("用户名或密码错误！");
              ui->usrLineEdit->clear();
              ui->pswLineEdit->clear();
              ui->usrLineEdit->setFocus();
        }
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
    close();
    Register r;
    r.exec();

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
    SetCanclBox();

}

/*************************************************************************
【函数名称】SetStyle
【函数功能】设置页面的样式表
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.29
【更改记录】
*************************************************************************/
void LoginDialog::SetStyle(){
    m_BtnStyle1="QPushButton{background-color:rgb(0, 188, 212);\
            color: white;   border-radius: 10px; \
            border-style: outset;}"
           "QPushButton:hover{background-color:#198fb6; color: white;}"
          "QPushButton:pressed{background-color:#3F51B5;\
                           border-style: inset; }";
    QString EditStyle="QLineEdit{border-radius:2px groove #BDBDBD;border:1px groove #BDBDBD;}";
    ui->loginBtn->setStyleSheet(m_BtnStyle1);
    ui->exitBtn->setStyleSheet(m_BtnStyle1);
    ui->usrLineEdit->setStyleSheet(EditStyle);
    ui->pswLineEdit->setStyleSheet(EditStyle);
    QString BtnStyle2="QPushButton{border:white;background-color:white; color:black;}"
    "QPushButton:hover{backgroud-color:white;color:#3F51B5;}"
                      "QPushButton:pressed{background-color:white;color:#303F9F;}";
    ui->RegisterBtn->setStyleSheet(BtnStyle2);
    ui->exitBtn_2->setStyleSheet(BtnStyle2);
    setMaximumSize(600,800);
    setMinimumSize(600,800);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
}

/*************************************************************************
【函数名称】SetWarningBox
【函数功能】显示警告的MessageBox
【参数】QString Text
【返回值】 无
【开发者及日期】李佳芸 2019.7.31
【更改记录】
*************************************************************************/
void LoginDialog::SetWarningBox(QString Text){
    QMessageBox message(this);
    message.setIconPixmap(QPixmap(":/images/warning.svg"));
    message.setStyleSheet("font:12pt,\"等线\";background:white;");
    message.setText(Text);
    QPushButton* ysBtn=new QPushButton("确定");
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    message.addButton(ysBtn,QMessageBox::AcceptRole);
    message.setWindowTitle("警告");
    message.exec();
}

/*************************************************************************
【函数名称】SetCanclBox
【函数功能】显示点击取消之后的QMessageBox
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void LoginDialog::SetCanclBox(){
    QMessageBox msgbx;
    msgbx.setText("你确定要退出吗？这会使编辑的文本清空。");
    msgbx.setIconPixmap(QPixmap(":/images/warning.svg"));
    QPushButton *ysBtn=new QPushButton(tr("确定"));
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    QPushButton *moreBtn=new QPushButton(tr("取消"));
    moreBtn->setStyleSheet(m_BtnStyle1);
    moreBtn->setFixedSize(171,51);
    msgbx.addButton(ysBtn,QMessageBox::AcceptRole);
    msgbx.addButton(moreBtn,QMessageBox::ActionRole);
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->usrLineEdit,SLOT(setFocus()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->usrLineEdit,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->pswLineEdit,SLOT(clear()));
    msgbx.setWindowTitle("警告");
    msgbx.setStyleSheet("background:white;font:\"等线\";");
    msgbx.exec();
}

/*************************************************************************
【函数名称】IsEmpty
【函数功能】判断用户的输入是否有空
【参数】无
【返回值】bool
【开发者及日期】李佳芸 2019.7.30
【更改记录】
*************************************************************************/
bool LoginDialog::IsEmpty(){
    if(ui->usrLineEdit->text().isEmpty()){
        SetWarningBox("用户名不能为空！");
    }
    else if(ui->pswLineEdit->text().isEmpty()){
        SetWarningBox("密码不能为空！!");
    }
}

/*************************************************************************
【函数名称】on_exitBtn_2_clicked
【函数功能】当点击退出按钮之后，存储所有数据
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void LoginDialog::on_exitBtn_2_clicked()
{
    SqlQuery query;
    query.saveUser(g_backUp.m_listUser.m_List);
    query.saveTasks(g_backUp.m_listTaskPublisher.m_List);
    query.saveSignUpForLeader(g_backUp.m_listSignUpForLeader.m_List);
    query.saveSignUpForTranslater(g_backUp.m_listSignUpForTranslater.m_List);
    query.saveTaskLeader(g_backUp.m_listTaskLeader.m_List);
    query.saveTaskTranslater(g_backUp.m_listTaskTranslater.m_List);
    query.saveMessage(g_backUp.m_listMessage.m_List);
    query.saveSignUpForChecker(g_backUp.m_listSignUpForChecker.m_List);
    close();
    exit(0);
}
