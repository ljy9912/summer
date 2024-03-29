#include "userinfoedit.h"
#include "ui_userinfoedit.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "userinfo.h"
#include "logindialog.h"
#include "sqlquery.h"
#include <QInputDialog>



userInfoEdit::userInfoEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userInfoEdit)
{
    ui->setupUi(this);
    SetStyle();
}

userInfoEdit::~userInfoEdit()
{
    delete ui;
    ui=NULL;
}

/*************************************************************************
【函数名称】showValue
【函数功能】通过user的对象显示用户信息方便用户编辑
【参数】user g_backUp.m_User
【返回值】 无
【开发者及日期】李佳芸 2019.7.16
【更改记录】
*************************************************************************/
void userInfoEdit::showValue(){
    ui->usrName->setText(g_backUp.m_User.GetID());
    ui->phoneEdit->setText(g_backUp.m_User.GetPhoneNum());
    ui->IDNumEdit->setText(g_backUp.m_User.GetIDNum());
    ui->EnglishEdit->setText(g_backUp.m_User.GetEnglish());
    ui->paswrd->setText(g_backUp.m_User.GetPassWrd());
    ui->confrmpaswrd->setText(g_backUp.m_User.GetPassWrd());
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
    close();
    MainWindow r;
    r.exec();
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
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    QPushButton *moreBtn=new QPushButton(tr("取消"));
    moreBtn->setStyleSheet(m_BtnStyle1);
    moreBtn->setFixedSize(171,51);
    msgbx->setStyleSheet("background:white;font:12pt,\"等线\";");
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
    if(!IsEmpty()){
        if(ui->usrName->text().trimmed()!=g_backUp.m_User.GetID()){
            if(g_backUp.m_listUser.NameExist(ui->usrName->text().trimmed())){
                SetWarningBox("用户名已存在！");
                ui->usrName->clear();
                ui->usrName->setFocus();
            }
        }
        else if(ui->confrmpaswrd->text()!=ui->paswrd->text()){
            SetWarningBox("密码和确认密码不同！");
            ui->paswrd->clear();
            ui->confrmpaswrd->clear();
            ui->paswrd->setFocus();
        }
        else{
            g_backUp.UserInfoEdit(ui->IDNumEdit->text(),ui->phoneEdit->text(),
                                  ui->EnglishEdit->text(),ui->paswrd->text(),
                                  ui->usrName->text());
            SetInformBox("信息修改成功！");
            close();
            userInfo r;
            r.showValue();
            r.exec();
        }
    }

}

bool userInfoEdit::IsEmpty(){
    if(ui->EnglishEdit->text().isEmpty()){
        SetWarningBox("英语资历不能为空！");
        return true;
    }
    else if(ui->usrName->text().isEmpty()){
        SetWarningBox("用户名不能为空！");
        return true;
    }
    else if(ui->paswrd->text().isEmpty()){
        SetWarningBox("密码不能为空！");
        return true;
    }
    else if(ui->confrmpaswrd->text().isEmpty()){
        SetWarningBox("确认密码不能为空!");
        return true;
    }
    else if(!ui->IDNumEdit->text().isEmpty()){
        if(ui->IDNumEdit->text().size()!=18){
            SetWarningBox("身份证号格式不正确！");
            return true;
        }
    }
    return false;
}

void userInfoEdit::SetStyle(){
    m_BtnStyle1="QPushButton{background-color:rgb(0, 188, 212);\
            color: white;   border-radius: 10px; \
            border-style: outset;}"
           "QPushButton:hover{background-color:#198fb6; color: white;}"
          "QPushButton:pressed{background-color:#3F51B5;\
                           border-style: inset; }";
    QString BtnStyle2="QPushButton{border:white;background-color:white; color:black;}"
          "QPushButton:hover{backgroud-color:white;color:#3F51B5;}"
          "QPushButton:pressed{background-color:white;color:#303F9F;}";
    ui->confrmBtn->setStyleSheet(m_BtnStyle1);
    ui->canclBtn->setStyleSheet(m_BtnStyle1);
    ui->pushButton_3->setStyleSheet(BtnStyle2);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
}

void userInfoEdit::SetWarningBox(QString Text){
    QMessageBox message(this);
    message.setIconPixmap(QPixmap(":/images/warning.svg"));
    message.setStyleSheet("font:12pt,\"等线\";background:white;");
    message.setText(Text);
    message.setWindowTitle("警告");
    QPushButton* ysBtn=new QPushButton("确定");
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    message.addButton(ysBtn,QMessageBox::AcceptRole);
    message.exec();
}

void userInfoEdit::SetInformBox(QString Text){
    QMessageBox message(this);
    message.setIconPixmap(QPixmap(":/images/information.svg"));
    message.setStyleSheet("font:12pt,\"等线\";background:white;");
    message.setText(Text);
    message.setWindowTitle("提示");
    QPushButton* ysBtn=new QPushButton("确定");
    ysBtn->setStyleSheet(m_BtnStyle1);
    ysBtn->setFixedSize(171,51);
    message.addButton(ysBtn,QMessageBox::AcceptRole);
    message.exec();
}
