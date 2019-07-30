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
    SetStyle();
}

MessageBox::~MessageBox()
{
    delete ui;
    ui=NULL;
}


void MessageBox::ShowMessage(){
    QToolBox* toolBox=new QToolBox;
    SetBoxStyle(toolBox);
    m_messageList=g_backUp.m_listMessage.SearchMessageforUser(g_backUp.m_User.GetID());
    for(int i=0;i<m_messageList.size();i++){
        QTextBrowser* window=new QTextBrowser;
        window->setStyleSheet("border:white 0px;font:12pt,\"等线\";}");
        window->setText(m_messageList[i].GetContent());
        toolBox->addItem(window,m_messageList[i].GetTitle());
    }
    connect(toolBox,SIGNAL(currentChanged(int)),this,SLOT(OnClicked(int)));
    ui->stackedWidget->addWidget(toolBox);
}

void MessageBox::on_Main_clicked()
{
    close();
    MainWindow r;
    r.exec();
}

void MessageBox::OnClicked(int i){
    m_messageList[i].EditFlag(1);
    g_backUp.m_listMessage.Update(m_messageList[i]);
}

void MessageBox::SetStyle(){
    QString BtnStyle2="QPushButton{border:white;background-color:white; color:black;}"
          "QPushButton:hover{backgroud-color:white;color:#3F51B5;}"
          "QPushButton:pressed{background-color:white;color:#303F9F;}";
    ui->Main->setStyleSheet(BtnStyle2);
}

void MessageBox::SetBoxStyle(QToolBox* box){
    box->setStyleSheet("QToolBox::tab{background:#B2EBF2;font:12pt,\"等线\";"
                       "border-radius:5px;height:50px;}"
                       "QToolBox::tab:selected{color:white;background:#03A9F4;}"
                       "QToolBox::tab:hover{background:rgb(0, 188, 212);color:white;}"
                       "QToolBoxButton{min-height:50px;}");


}
