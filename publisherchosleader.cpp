#include "publisherchosleader.h"
#include "ui_publisherchosleader.h"
#include <QSqlQuery>

PublisherChosLeader::PublisherChosLeader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PublisherChosLeader)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.exec("select * from tasks");
    int len=0;
    query.first();
    if(query.value(4).toInt()==iduser){
        len++;
    }
    while(query.next())
    {
        if(query.value(4).toInt()==iduser){
            len++;
        }
    }
    newTasks=new task[len];
    query.first();
    if(query.value(4).toInt()==iduser){
        int id=query.value(0).toInt();
        newTasks[0].attachIDToTask(id);
    }
    for(int i=0;i<len;i++)
    {
        if(query.value(4).toInt()==iduser){
            int id=query.value(0).toInt();
            newTasks[len].attachIDToTask(id);
        }
    }

    for(int i=0;i<len;i++){
        ui->listWidget->insertItem(i,tr("%1").arg(newTasks[i].GetIntroduction()));
    }

        connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(setCurrentTable(int)));
    }



PublisherChosLeader::~PublisherChosLeader()
{
    delete ui;
}

void PublisherChosLeader::EditIDUser(int iid){
    iduser=iid;
}

/*void PublisherChosLeader::setCurrentTable(int item){
    int id=newTasks[i].getID();
    QSqlQuery queryCreate,querySignUp;
    queryCreate.prepare("CREATE TABLE IF NOT EXISTS ?(id int primary key,iduser int,name varchar(20)"
               "English varchar(20),crEditpoint varchar(20)");
    queryCreate.addBindValue(id);
    queryCreate.exec();
    querySignUp.prepare("select * from signupforleaders where idtask=?");
    querySignUp.addBindValue(id);
    querySignUp.exec();
    model = new QSqlTableModel(this);
    model->setTable("student");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行
    //不显示name属性列,如果这时添加记录，则该属性的值添加不上
    // model->removeColumn(1);
    ui->tableView->setModel(model);
    //使其不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}*/
