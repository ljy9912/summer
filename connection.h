#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include "sqlquery.h"
#include "logindialog.h"
#include "list.h"

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection."
                     ), QMessageBox::Cancel);
        return false;
    }
    list List;
    SqlQuery query;
    query.createUser();
    query.createTasks();
    query.createSignUpForLeader();
    query.createSignUpForTranslater();
    query.createTaskLeader();
    query.createTaskTranslater();
    List.TaskPublisher=query.GetTasks();
    List.User=query.GetUser();
    List.SignUpForLeader=query.GetSignUpForLeader();
    List.SignUpForTranslater=query.GetSignUpForTranslater();
    List.TaskLeader=query.GetTaskLeader();
    List.TaskTranslater=query.GetTaskTranslater();
    LoginDialog *r=new LoginDialog;
    r->EditList(List);
    r->show();
    /*if(query.value(0).toInt()<20180001){
        query.prepare("insert into users(id)values(20180001)");
        if(!query.exec())
            qDebug()<<query.lastError();
        else
            qDebug()<<"Table created!";
    }*/
    return true;
}

#endif // CONNECTION_H
