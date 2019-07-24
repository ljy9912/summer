#include "messagebox.h"
#include "ui_messagebox.h"
#include <QToolBox>
#include <QTextBrowser>

MessageBox::MessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageBox)
{
    ui->setupUi(this);
}

MessageBox::~MessageBox()
{
    delete ui;
}

void MessageBox::EditList(list NewList){
    m_List=NewList;
}

void MessageBox::EditUser(user NewUser){
    m_User=NewUser;
}


void MessageBox::ShowMessage(){
    m_messageList=m_List.SearchMessageforUser(m_User.GetID());
    for(int i=0;i<m_messageList.size();i++){
        QTextBrowser* window=new QTextBrowser;
        window->setText(m_messageList[i].GetContent());
        ui->toolBox->addItem(window,m_messageList[i].GetTitle());
    }

}
