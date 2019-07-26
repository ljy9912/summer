#include "leadertable.h"
#include "ui_leadertable.h"
#include <QTableWidget>
#include "signup.h"
#include <QMessageBox>

leaderTable::leaderTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::leaderTable)
{
    ui->setupUi(this);
}

leaderTable::~leaderTable()
{
    delete ui;
}

void leaderTable::EditList(list newList){
    List=newList;
}

void leaderTable::EditUser(user newUser){
    myUser=newUser;
}

void leaderTable::showValue(){
    for(int i=0;i<List.Task.size();i++){
        if(List.Task[i].GetPublisher()==myUser.GetID()){
            myTaskList.append(List.Task[i]);
        }
    }

    for(int i=0;i<myTaskList.size();i++){
        if(myTaskList[i].GetFlag()==102){
            QList<signUp> myLeaderList;
            for(int j=0;j<List.signUp.size();j++){
                if(List.signUp[j].GetIDTask()==myTaskList[i].GetID()){
                    myLeaderList.append(List.signUp[j]);
                }
            }
        }

        ui->listWidget->insertItem(i,tr("%1").arg(myTaskList[i].GetIntroduction()));
        connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
        if(myTaskList[i].GetFlag()==102){
            QTableWidget *table=new QTableWidget(myLeaderList.size(),4);
            table->setEditTriggers(QAbstractItemView::NoEditTriggers);
            table->setWindowTitle("选择负责人");
            QStringList header;
            header<<"账号"<<"用户名"<<"英语资历"<<"积分";
            table->setHorizontalHeaderLabels(header);
            sum=myLeaderList.size();
            for(int i=0;i<myLeaderList.size();i++){
                table->setItem(i,0,new QTableWidgetItem(QString::number(myLeaderList[i].GetID())));
                table->setItem(i,1,new QTableWidgetItem(myLeaderList[i].GetName()));
                table->setItem(i,2,new QTableWidgetItem(myLeaderList[i].GetEnglish()));
                table->setItem(i,3,new QTableWidgetItem(QString::number(myLeaderList[i].GetRewrdPoint())));
            }
        }
        ui->stackedWidget->addWidget(table);

    }
}

void leaderTable::on_confrmBtn_clicked()
{
    int iIdLeader=ui->IDEdit->text().toInt();
    int iNum=ui->listWidget->currentRow();
    int iNumInList=List.searchTaskInList(myTaskList[iNum]);
    List.Task[iNumInList].EditLeader(iIdLeader);
    QMessageBox::information(this, tr("提示"),
                       tr("选择负责人成功！")
                      ,tr("确定"));
    int iSize=List.signUp.size();
    for(int i=iSize-1;i>=0;i++){
        if(List.signUp[i].GetIDTask()==myTaskList[iNum].GetID()){
            List.signUp.removeAt(i);
        }
    }
    myTaskList[iNum].EditFlag(201);
}
