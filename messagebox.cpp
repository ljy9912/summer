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


void MessageBox::ShowMessage(){
    m_messageList=g_backUp.m_List.SearchMessageforUser(g_backUp.m_User.GetID());
    for(int i=0;i<m_messageList.size();i++){
        QTextBrowser* window=new QTextBrowser;
        window->setText(m_messageList[i].GetContent());
        ui->toolBox->addItem(window,m_messageList[i].GetTitle());
    }

}

void MessageBox::on_main_clicked()
{
    MainWindow* r=new MainWindow;
    r->show();
    close();
}
