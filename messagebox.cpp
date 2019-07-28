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
    ui=NULL;
}


void MessageBox::ShowMessage(){
    QToolBox* toolBox=new QToolBox;
    m_messageList=g_backUp.m_listMessage.SearchMessageforUser(g_backUp.m_User.GetID());
    for(int i=0;i<m_messageList.size();i++){
        QTextBrowser* window=new QTextBrowser;
        window->setText(m_messageList[i].GetContent());
        toolBox->addItem(window,m_messageList[i].GetTitle());
    }
    connect(toolBox,SIGNAL(currentChanged(int)),this,SLOT(OnClicked(int)));
    ui->stackedWidget->addWidget(toolBox);
}

void MessageBox::on_main_clicked()
{
    close();
    MainWindow r;
    r.exec();
}

void MessageBox::OnClicked(int i){
    g_backUp.m_listMessage.Delete(m_messageList[i-1].GetID());
}
