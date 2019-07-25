#include "messagebox.h"
#include "ui_messagebox.h"
#include <QToolBox>
#include <QTextBrowser>
#include "sqlquery.h"
#include "mainwindow.h"

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

void MessageBox::on_main_clicked()
{
    MainWindow* r=new MainWindow;
    r->EditBackUp(m_BackUp);
    r->show();
    close();
}
