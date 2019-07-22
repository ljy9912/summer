#include "registerphoneconfrm.h"
#include "ui_registerphoneconfrm.h"
#include "logindialog.h"

registerPhoneConfrm::registerPhoneConfrm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerPhoneConfrm)
{
    ui->setupUi(this);
}

registerPhoneConfrm::~registerPhoneConfrm()
{
    delete ui;
}

void registerPhoneConfrm::showValue(QString phoneValue,QString Englishvalue,int id)         // 自定义槽
{
    ui->phoneNum->setText(tr("手机号：%1").arg(phoneValue));
    ui->English->setText(tr("英语资历：%1").arg(Englishvalue));
    ui->ID->setText(tr("账号：%1").arg(id));
}

void registerPhoneConfrm::on_main_clicked()
{
    close();
    LoginDialog *r=new LoginDialog;
    r->show();
}
