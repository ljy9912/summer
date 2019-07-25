#include "messagebox.h"
#include "ui_messagebox.h"
#include <QToolBox>
#include <QTextBrowser>
#include "sqlquery.h"

MessageBox::MessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageBox)
{
    ui->setupUi(this);
}

MessageBox::~MessageBox()
{
    delete ui;
    SqlQuery query;
    query.saveUser(m_BackUp.m_List.User);
    query.saveTasks(m_BackUp.m_List.TaskPublisher);
    query.saveSignUpForLeader(m_BackUp.m_List.SignUpForLeader);
    query.saveSignUpForTranslater(m_BackUp.m_List.SignUpForTranslater);
    query.saveTaskLeader(m_BackUp.m_List.TaskLeader);
    query.saveTaskTranslater(m_BackUp.m_List.TaskTranslater);
    query.saveMessage(m_BackUp.m_List.message);
}

void MessageBox::EditBackUp(BackUp myBackUp){
    m_BackUp=myBackUp;
}

void MessageBox::ShowMessage(){
    m_messageList=m_BackUp.m_List.SearchMessageforUser(m_BackUp.m_User.GetID());
    for(int i=0;i<m_messageList.size();i++){
        QTextBrowser* window=new QTextBrowser;
        window->setText(m_messageList[i].GetContent());
        ui->toolBox->addItem(window,m_messageList[i].GetTitle());
    }

}
