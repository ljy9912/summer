#include "registerphonenum.h"
#include "ui_registerphonenum.h"
#include "register.h"
#include "registerid.h"
#include <QSqlQuery>
#include <QDebug>
#include "logindialog.h"
#include <QSqlError>

registerPhoneNum::registerPhoneNum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerPhoneNum)
{
    ui->setupUi(this);
    dlg=new registerPhoneConfrm;
    connect(this,SIGNAL(dlgreturn(QString,QString,int)),dlg,SLOT(showValue(QString,QString,int)));
}

registerPhoneNum::~registerPhoneNum()
{
    delete ui;
}

void registerPhoneNum::on_pushButton_clicked()
{
    int flag=0;
    QString passwordvalue=ui->passwrdEdit->text();
    QString confirmpswrdvalue=ui->confrmPswrdEdit->text();
    if(passwordvalue!=confirmpswrdvalue){
        QMessageBox::warning(this, tr("警告"),
                           tr("密码与确认密码不符，请重新输入！")
                          ,tr("确定"));
        ui->passwrdEdit->clear();
        ui->confrmPswrdEdit->clear();
        ui->passwrdEdit->setFocus();
        close();
        show();
        }
        else{
          QString PhoneValue = ui->phoneNumEdit->text();
          QString Englishvalue=ui->EnglishEdit->text();
          QSqlQuery query;
          query.exec("select * from users");
          while(query.next()){
              if(PhoneValue==query.value(2).toString()){
                  QMessageBox::warning(this, tr("警告"),
                                     tr("手机号已被注册！")
                                    ,tr("确定"));
                  ui->phoneNumEdit->clear();
                  ui->phoneNumEdit->setFocus();
                  close();
                  show();
                  flag=1;
              }
          }
          if(flag==0){
              close();
              query.last();
              int idnum=query.value(0).toInt()+1;
              int idtask=query.value(8).toInt()+1;
              query.prepare("insert into users(idtask,id,phoneNum,password,English,rewrdPoint,money)"
                         "values(?,?,?,?,?,?,?)");
               query.addBindValue(idtask);
              query.addBindValue(idnum);
              query.addBindValue(PhoneValue);
              query.addBindValue(passwordvalue);
              query.addBindValue(Englishvalue);
              query.addBindValue(100);
              query.addBindValue(0);
              if(!query.exec())
                  qDebug() << query.lastError();
                else
                  qDebug() << "Inserted!";
              emit dlgreturn(PhoneValue,Englishvalue,idnum);
              dlg->show();
          }
    }
}

void registerPhoneNum::on_pushButton_2_clicked()
{
    QMessageBox *msgbx=new QMessageBox(this);
    msgbx->setText("你确定要退出吗？这会使编辑的文本清空。");
    msgbx->setWindowTitle("警告");
    QPushButton *ysBtn=new QPushButton(tr("确定"));
    QPushButton *moreBtn=new QPushButton(tr("取消"));
    msgbx->addButton(ysBtn,QMessageBox::AcceptRole);
    msgbx->addButton(moreBtn,QMessageBox::ActionRole);
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->phoneNumEdit,SLOT(setFocus()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->phoneNumEdit,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->passwrdEdit,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->confrmPswrdEdit,SLOT(clear()));
    msgbx->show();
}

void registerPhoneNum::on_pushButton_3_clicked()
{
    close();
    LoginDialog *l=new LoginDialog;
    l->show();
}

void registerPhoneNum::on_usrnameRegistrBtn_clicked()
{
    close();
    Register *r=new Register;
    r->show();
}
