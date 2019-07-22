#include "registerid.h"
#include "ui_registerid.h"
#include "register.h"
#include "registerphonenum.h"
#include <QSqlQuery>
#include <QDebug>
#include "logindialog.h"
#include <QSqlError>

registerID::registerID(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerID)
{
    ui->setupUi(this);
    dlg=new registerIDConfrm;
    connect(this,SIGNAL(dlgreturn(QString,QString,QString)),dlg,SLOT(showValue(QString,QString,QString)));
}

registerID::~registerID()
{
    delete ui;
}

void registerID::on_confrmBtn_clicked()
{
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
          int flag=0;
          QString IDValue = ui->IDEdit->text();
          QString Englishvalue=ui->EnglishEdit->text();
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
                QString IDValue = ui->IDEdit->text();
                QString Englishvalue=ui->EnglishEdit->text();
                QSqlQuery query;
                query.exec("select * from users");
                while(query.next()){
                    if(IDValue==query.value(3).toString()){
                        QMessageBox::warning(this, tr("警告"),
                                           tr("身份证号已被注册！")
                                          ,tr("确定"));
                        ui->IDEdit->clear();
                        ui->IDEdit->setFocus();
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
                    query.prepare("insert into users(idtask,id,idnum,password,English,rewrdPoint,money)"
                               "values(?,?,?,?,?,?,?)");
                    query.addBindValue(idtask);
                    query.addBindValue(idnum);
                    query.addBindValue(IDValue);
                    query.addBindValue(passwordvalue);
                    query.addBindValue(Englishvalue);
                    query.addBindValue(100);
                    query.addBindValue(0);
                    if(!query.exec())
                        qDebug() << query.lastError();
                      else
                        qDebug() << "Inserted!";
                    emit dlgreturn(IDValue,Englishvalue,idnum);
                    dlg->show();
                }
            }
    }
}

void registerID::on_canclBtn_clicked()
{
    QMessageBox *msgbx=new QMessageBox(this);
    msgbx->setText("你确定要退出吗？这会使编辑的文本清空。");
    msgbx->setWindowTitle("警告");
    QPushButton *ysBtn=new QPushButton(tr("确定"));
    QPushButton *moreBtn=new QPushButton(tr("取消"));
    msgbx->addButton(ysBtn,QMessageBox::AcceptRole);
    msgbx->addButton(moreBtn,QMessageBox::ActionRole);
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->IDEdit,SLOT(setFocus()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->IDEdit,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->passwrdEdit,SLOT(clear()));
    QObject::connect(ysBtn,SIGNAL(clicked()),ui->confrmPswrdEdit,SLOT(clear()));
    msgbx->show();
}

void registerID::on_rtrnLoginBtn_clicked()
{
    close();
    LoginDialog *l=new LoginDialog;
    l->show();
}

void registerID::on_usrnameRegisterBtn_clicked()
{
    close();
    Register *r=new Register;
    r->show();
}

void registerID::on_phonenumRgstrBtn_clicked()
{
    registerPhoneNum *r=new registerPhoneNum;

    r->show();
    close();
}
