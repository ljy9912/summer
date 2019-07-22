#include "registeridconfrm.h"
#include "ui_registeridconfrm.h"
#include "logindialog.h"

registerIDConfrm::registerIDConfrm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerIDConfrm)
{
    ui->setupUi(this);
}

registerIDConfrm::~registerIDConfrm()
{
    delete ui;
}

void registerIDConfrm::showValue(QString namevalue,QString Englishvalue,int id)         // 自定义槽
{
    ui->IDnum->setText(tr("用户名：%1").arg(namevalue));
    ui->English->setText(tr("英语资历：%1").arg(Englishvalue));
    ui->ID->setText(tr("账号：%1").arg(id));
}


void registerIDConfrm::on_main_clicked()
{
    close();
    LoginDialog *r=new LoginDialog;
    r->show();
}
