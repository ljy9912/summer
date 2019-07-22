#include "usermoney.h"
#include "ui_usermoney.h"
#include "logindialog.h"
#include <QSqlQuery>
#include "userinfo.h"

userMoney::userMoney(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userMoney)
{
    ui->setupUi(this);
}

userMoney::~userMoney()
{
    delete ui;
}

void userMoney::on_confrmBtn_clicked()
{
    myUser.editMoney(newMoney);
    myUser.updateList(List.User);
    userInfo *r=new userInfo;
    r->editUser(myUser);
    r->showValue(myUser);
    r->editList(List);
    r->show();
    close();
}

void userMoney::editUser(user myNewUser){
    myUser=myNewUser;
}

void userMoney::editList(list newList){
    List=newList;
}
