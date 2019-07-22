#include "sqlquery.h"
#include <QList>
#include "user.h"
#include "task.h"
#include <QDebug>
#include <QSqlError>
#include "tasktranslater.h"

SqlQuery::SqlQuery()
{

}

SqlQuery::~SqlQuery(){

}

void SqlQuery::createUser(){
    query.prepare("CREATE TABLE IF NOT EXISTS users(id int primary key,name varchar(20),"
          "phoneNum varchar(20),IDnum varchar(20),"
         "password varchar(20),English varchar(50),rewrdPoint int,money double"
                  ")");
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
    query.first();
    if(!query.next()){
        query.prepare("insert into users(id) values(?)");
        query.addBindValue(20180001);
        query.exec();
    }
}

void SqlQuery::createTasks(){
    query.prepare("CREATE TABLE IF NOT EXISTS tasks(id int primary key,taskclass int,"
               "task varchar(1000),introduction varchar(1000),"
               "publisher int,time int,leaderyear int,"
               "leadermonth int,leaderday int,money double,flag int,leader int"
                  "startyear int,startmonth int,startday int)");//flag=0为编辑状态，
    //101为发布状态，102为选择负责人状态，201为负责人定日期状态，202为负责人招募译者状态，203为负责人分配任务状态
    //301为译者翻译状态与负责人审查，302为译者修改译文，303为负责人修改并整合译文，401为发布人验收状态
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
}

void SqlQuery::createSignUpForLeader(){
    query.prepare("create table if not exists signupforleaders(id int primary key,name varchar(20),"
                  "phoneNum varchar(20),IDnum varchar(20),"
                 "password varchar(20),English varchar(50),rewrdPoint int,money double,idtask int)");
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
}

void SqlQuery::createSignUpForTranslater(){
    query.prepare("create table if not exists signupfortranslaters(id int primary key,name varchar(20),"
                  "phoneNum varchar(20),IDnum varchar(20),"
                 "password varchar(20),English varchar(50),rewrdPoint int,money double,idtask int)");
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
}

void SqlQuery::createTaskLeader(){
    query.prepare("CREATE TABLE IF NOT EXISTS taskleader(id int primary key,taskclass int,"
               "task varchar(1000),introduction varchar(1000),"
               "publisher int,time int,translateryear int,"
               "translatermonth int,translaterday int,money double,flag int,leader int"
                  "startyear int,startmonth int,startday int)");//flag=0为编辑状态，
    //101为发布状态，102为选择负责人状态，201为负责人定日期状态，202为负责人招募译者状态，203为负责人分配任务状态
    //301为译者翻译状态与负责人审查,译者修改译文，302为负责人修改并整合译文，401为发布人验收状态
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
}

void SqlQuery::createTaskTranslater(){
    query.prepare("CREATE TABLE IF NOT EXISTS tasktranslater(id int primary key,taskclass int,"
               "task varchar(1000),introduction varchar(1000),"
               "publisher int,time int,endyear int,"
               "endmonth int,endday int,money double,flag int,leader int"
                  "startyear int,startmonth int,startday int,translater int,taskid int,"
                  "result varchar(1000),comment varchar(1000),flagtoleader int)");//flag=0为编辑状态，
    //101为发布状态，102为选择负责人状态，201为负责人定日期状态，202为负责人招募译者状态，203为负责人分配任务状态
    //301为译者翻译状态与负责人审查,译者修改译文，302为负责人修改并整合译文，401为发布人验收状态
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
}


const QList<user> SqlQuery::GetUser(){
    query.exec("select * from users");
    query.first();
    int id=query.value(0).toInt();
    user myUser;
    myUser.attachIDToUser(id);
    QList <user> listUser;
    listUser.append(myUser);
    while(query.next()){
        int id=query.value(0).toInt();
        user myUser;
        myUser.attachIDToUser(id);
        listUser.append(myUser);
    }
    return listUser;
}

const QList<taskPublisher> SqlQuery::GetTasks(){
    query.exec("select * from tasks");
    query.first();
    int id=query.value(0).toInt();
    taskPublisher myTask;
    myTask.attachIDToTask(id);
    QList <taskPublisher> listTask;
    listTask.append(myTask);
    while(query.next()){
        int id=query.value(0).toInt();
        taskPublisher myTask;
        myTask.attachIDToTask(id);
        listTask.append(myTask);
    }
    return listTask;
}

const QList<signUpForLeader> SqlQuery::GetSignUpForLeader(){
    query.exec("select * from signupforleaders");
    query.first();
    int id=query.value(0).toInt();
    signUpForLeader myLeader;
    myLeader.attachIDToUser(id);
    QList <signUpForLeader> listLeader;
    listLeader.append(myLeader);
    while(query.next()){
        int id=query.value(0).toInt();
        signUpForLeader myLeader;
        myLeader.attachIDToUser(id);
        listLeader.append(myLeader);
    }
    return listLeader;
}

const QList<signUpForTranslater> SqlQuery::GetSignUpForTranslater(){
    query.exec("select * from signupfortranslaters");
    query.first();
    int id=query.value(0).toInt();
    signUpForTranslater myTranslater;
    myTranslater.attachIDToUser(id);
    QList <signUpForTranslater> listTranslater;
    listTranslater.append(myTranslater);
    while(query.next()){
        int id=query.value(0).toInt();
        signUpForTranslater myTranslater;
        myTranslater.attachIDToUser(id);
        listTranslater.append(myTranslater);
    }
    return listTranslater;
}

const QList<taskLeader> SqlQuery::GetTaskLeader(){
    query.exec("select * from taskleader");
    query.first();
    int id=query.value(0).toInt();
    taskLeader myTask;
    myTask.attachIDToTask(id);
    QList <taskLeader> listTask;
    listTask.append(myTask);
    while(query.next()){
        int id=query.value(0).toInt();
        taskLeader myTask;
        myTask.attachIDToTask(id);
        listTask.append(myTask);
    }
    return listTask;
}

const QList<taskTranslater> SqlQuery::GetTaskTranslater(){
    query.exec("select * from tasktranslater");
    query.first();
    int id=query.value(0).toInt();
    taskTranslater myTask;
    myTask.attachIDToTask(id);
    QList <taskTranslater> listTask;
    listTask.append(myTask);
    while(query.next()){
        int id=query.value(0).toInt();
        taskTranslater myTask;
        myTask.attachIDToTask(id);
        listTask.append(myTask);
    }
    return listTask;
}

void SqlQuery::saveUser(QList<user> listUser){
    QSqlQuery query;
    query.exec("delete from users");
    for(int i=0;i<listUser.size();i++){
        query.prepare("insert into users(id,name,phonenum,idnum,password,"
                      "english,rewrdpoint,money)"
                      "values(?,?,?,?,?,?,?,?)");
        query.addBindValue(listUser[i].GetID());
        query.addBindValue(listUser[i].GetName());
        query.addBindValue(listUser[i].GetPhoneNum());
        query.addBindValue(listUser[i].GetIDNum());
        query.addBindValue(listUser[i].GetPassWrd());
        query.addBindValue(listUser[i].GetEnglish());
        query.addBindValue(listUser[i].GetRewrdPoint());
        query.addBindValue(listUser[i].GetMoney());
        query.exec();
    }
}

void SqlQuery::saveTasks(QList<taskPublisher> listTask){
    QSqlQuery query;
    query.exec("delete from tasks");
    for(int i=0;i<listTask.size();i++){
        query.prepare("insert into tasks(id,taskclass,task,"
                      "introduction,publisher,time,leaderyear,"
                      "leadermonth,leaderday,money,flag,leader"
                      "startyear,startmonth,startday)"
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(listTask[i].GetID());
        query.addBindValue(listTask[i].GetTaskClass());
        query.addBindValue(listTask[i].GetTask());
        query.addBindValue(listTask[i].GetIntroduction());
        query.addBindValue(listTask[i].GetPublisher());
        query.addBindValue(listTask[i].GetTime());
        query.addBindValue(listTask[i].GetLeaderYear());
        query.addBindValue(listTask[i].GetLeaderMonth());
        query.addBindValue(listTask[i].GetLeaderDay());
        query.addBindValue(listTask[i].GetMoney());
        query.addBindValue(listTask[i].GetFlag());
        query.addBindValue(listTask[i].GetLeader());
        query.addBindValue(listTask[i].GetStartYear());
        query.addBindValue(listTask[i].GetStartMonth());
        query.addBindValue(listTask[i].GetStartDay());
        if(!query.exec())
            qDebug() << query.lastError();
          else
            qDebug() << "Table created!";
    }
}

void SqlQuery::saveSignUpForLeader(QList<signUpForLeader> listSignUpForLeader){
    QSqlQuery query;
    query.exec("delete from signupforleaders");
    for(int i=0;i<listSignUpForLeader.size();i++){
        query.prepare("insert into signupforleaders(id,name,phonenum,idnum,password,"
                      "english,rewrdpoint,money,idtask)"
                      "values(?,?,?,?,?,?,?,?,?)");
        query.addBindValue(listSignUpForLeader[i].GetID());
        query.addBindValue(listSignUpForLeader[i].GetName());
        query.addBindValue(listSignUpForLeader[i].GetPhoneNum());
        query.addBindValue(listSignUpForLeader[i].GetIDNum());
        query.addBindValue(listSignUpForLeader[i].GetPassWrd());
        query.addBindValue(listSignUpForLeader[i].GetEnglish());
        query.addBindValue(listSignUpForLeader[i].GetRewrdPoint());
        query.addBindValue(listSignUpForLeader[i].GetMoney());
        query.addBindValue(listSignUpForLeader[i].GetIDTask());
        if(!query.exec())
            qDebug() << query.lastError();
          else
            qDebug() << "Table created!";
    }
}

void SqlQuery::saveSignUpForTranslater(QList<signUpForTranslater> listSignUpForTranslater){
    QSqlQuery query;
    query.exec("delete from signupfortranslaters");
    for(int i=0;i<listSignUpForTranslater.size();i++){
        query.prepare("insert into signupfortranslaters(id,name,phonenum,idnum,password,"
                      "english,rewrdpoint,money,idtask)"
                      "values(?,?,?,?,?,?,?,?,?)");
        query.addBindValue(listSignUpForTranslater[i].GetID());
        query.addBindValue(listSignUpForTranslater[i].GetName());
        query.addBindValue(listSignUpForTranslater[i].GetPhoneNum());
        query.addBindValue(listSignUpForTranslater[i].GetIDNum());
        query.addBindValue(listSignUpForTranslater[i].GetPassWrd());
        query.addBindValue(listSignUpForTranslater[i].GetEnglish());
        query.addBindValue(listSignUpForTranslater[i].GetRewrdPoint());
        query.addBindValue(listSignUpForTranslater[i].GetMoney());
        query.addBindValue(listSignUpForTranslater[i].GetIDTask());
        
        if(!query.exec())
            qDebug() << query.lastError();
          else
            qDebug() << "Table created!";
    }
}

void SqlQuery::saveTaskLeader(QList<taskLeader> listTask){
    QSqlQuery query;
    query.exec("delete from taskleader");
    for(int i=0;i<listTask.size();i++){
        query.prepare("insert into tasks(id,taskclass,task,"
                      "introduction,publisher,time,translateryear,"
                      "translatermonth,translaterday,money,flag,leader"
                      "startyear,startmonth,startday)"
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(listTask[i].GetID());
        query.addBindValue(listTask[i].GetTaskClass());
        query.addBindValue(listTask[i].GetTask());
        query.addBindValue(listTask[i].GetIntroduction());
        query.addBindValue(listTask[i].GetPublisher());
        query.addBindValue(listTask[i].GetTime());
        query.addBindValue(listTask[i].GetTranslaterYear());
        query.addBindValue(listTask[i].GetTranslaterMonth());
        query.addBindValue(listTask[i].GetTranslaterDay());
        query.addBindValue(listTask[i].GetMoney());
        query.addBindValue(listTask[i].GetFlag());
        query.addBindValue(listTask[i].GetLeader());
        query.addBindValue(listTask[i].GetStartYear());
        query.addBindValue(listTask[i].GetStartMonth());
        query.addBindValue(listTask[i].GetStartDay());
        if(!query.exec())
            qDebug() << query.lastError();
          else
            qDebug() << "Table created!";
    }
}

void SqlQuery::saveTaskTranslater(QList<taskTranslater> listTask){
    QSqlQuery query;
    query.exec("delete from tasktranslater");
    for(int i=0;i<listTask.size();i++){
        query.prepare("insert into tasks(id,taskclass,task,"
                      "introduction,publisher,time,endyear,"
                      "endmonth,endday,money,flag,leader"
                      "startyear,startmonth,startday,translater,idtask,result,comment,"
                      "flagtoleader)"
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(listTask[i].GetID());
        query.addBindValue(listTask[i].GetTaskClass());
        query.addBindValue(listTask[i].GetTask());
        query.addBindValue(listTask[i].GetIntroduction());
        query.addBindValue(listTask[i].GetPublisher());
        query.addBindValue(listTask[i].GetTime());
        query.addBindValue(listTask[i].GetEndYear());
        query.addBindValue(listTask[i].GetEndMonth());
        query.addBindValue(listTask[i].GetEndDay());
        query.addBindValue(listTask[i].GetMoney());
        query.addBindValue(listTask[i].GetFlag());
        query.addBindValue(listTask[i].GetLeader());
        query.addBindValue(listTask[i].GetStartYear());
        query.addBindValue(listTask[i].GetStartMonth());
        query.addBindValue(listTask[i].GetStartDay());
        query.addBindValue(listTask[i].GetTranslater());
        query.addBindValue(listTask[i].GetIDTask());
        query.addBindValue(listTask[i].GetResult());
        query.addBindValue(listTask[i].GetComment());
        query.addBindValue(listTask[i].GetFlagToLeader());
        if(!query.exec())
            qDebug() << query.lastError();
          else
            qDebug() << "Table created!";
    }
}
