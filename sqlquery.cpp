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
               "leadermonth int,leaderday int,money double,flag int,leader int,"
                  "startyear int,startmonth int,startday int)");//flag=0为编辑状态，
    //101为发布状态，102为选择负责人状态，201为负责人定日期状态，202为负责人招募译者状态，203为负责人分配任务状态
    //301为译者翻译状态与负责人审查,译者修改译文，302为负责人修改并整合译文，401为发布人验收状态
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
}

void SqlQuery::createSignUpForLeader(){
    query.prepare("create table if not exists signupforleaders(id int,name varchar(20),"
                  "phoneNum varchar(20),IDnum varchar(20),"
                 "password varchar(20),English varchar(50),rewrdPoint int,"
                  "money double,idtask int,idthis int primary key)");
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
}

void SqlQuery::createSignUpForTranslater(){
    query.prepare("create table if not exists signupfortranslaters(id int,"
                  "name varchar(20),"
                  "phoneNum varchar(20),IDnum varchar(20),"
                 "password varchar(20),English varchar(50),rewrdPoint int,"
                  "money double,idtask int,idthis int primary key)");
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
}

void SqlQuery::createTaskLeader(){
    query.prepare("CREATE TABLE IF NOT EXISTS taskleader(id int primary key,taskclass int,"
               "task varchar(1000),introduction varchar(1000),"
               "publisher int,time int,translateryear int,"
               "translatermonth int,translaterday int,money double,flag int,leader int,"
                  "startyear int,startmonth int,startday int,result varchar(1000),"
                  "resulteditting varchar(1000))");//flag=0为编辑状态，
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
               "endmonth int,endday int,money double,flag int,leader int,"
                  "startyear int,startmonth int,startday int,translater int,taskid int,"
                  "result varchar(1000),comment varchar(1000),flagtoleader int,"
                  "commenteditting varchar(1000),resulteditting varchar(1000))");//flag=0为编辑状态，
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
    if(!query.exec("select * from tasks"))
        qDebug() << query.lastError();
      else
        qDebug() << "get tasks";
    QList <taskPublisher> listTask;
    query.first();
    int id=query.value(0).toInt();
    taskPublisher myTask;
    myTask.attachIDToTask(id);
    listTask.append(myTask);
    while(query.next()){
        int id=query.value(0).toInt();
        taskPublisher myTask;
        myTask.attachIDToTask(id);
        //myTask.EditFlag(203);
        //listTask.append(myTask);
        //myTask.EditFlag(201);
        listTask.append(myTask);
    }
    return listTask;
}

const QList<signUpForLeader> SqlQuery::GetSignUpForLeader(){
    QList <signUpForLeader> listLeader;
    query.exec("select * from signupforleaders");
    query.first();
    int id=query.value(9).toInt();
    signUpForLeader myLeader;
    myLeader.attachIDToUser(id);
    listLeader.append(myLeader);
    myLeader.EditIDTask(1);
    listLeader.append(myLeader);
    while(query.next()){
        int id=query.value(9).toInt();
        signUpForLeader myLeader;
        myLeader.attachIDToUser(id);
        //myLeader.EditFlag(1);
        listLeader.append(myLeader);
        //listLeader.append(myLeader);
    }
    return listLeader;
}

const QList<signUpForTranslater> SqlQuery::GetSignUpForTranslater(){
    query.exec("select * from signupfortranslaters");
    query.first();
    QList <signUpForTranslater> listTranslater;
    int id=query.value(9).toInt();
    signUpForTranslater myTranslater;
    myTranslater.attachIDToUser(id);
    listTranslater.append(myTranslater);
    while(query.next()){
        int id=query.value(9).toInt();
        signUpForTranslater myTranslater;
        myTranslater.attachIDToUser(id);
        listTranslater.append(myTranslater);
    }
    return listTranslater;
}

const QList<taskLeader> SqlQuery::GetTaskLeader(){
    query.exec("select * from taskleader");
    QList <taskLeader> listTask;
    query.first();
    int id=query.value(0).toInt();
    taskLeader myTask;
    myTask.attachIDToTask(id);
    listTask.append(myTask);
    while(query.next()){
        int id=query.value(0).toInt();
        taskLeader myTask;
        myTask.attachIDToTask(id);
        //myTask.EditFlag(302);
        listTask.append(myTask);
    }
    return listTask;
}

const QList<taskTranslater> SqlQuery::GetTaskTranslater(){
    query.exec("select * from tasktranslater");
    QList <taskTranslater> listTask;
    query.first();
    int id=query.value(0).toInt();
    taskTranslater myTask;
    myTask.attachIDToTask(id);
    listTask.append(myTask);
    while(query.next()){
        int id=query.value(0).toInt();
        taskTranslater myTask;
        myTask.attachIDToTask(id);
        //myTask.EditFlagToLeader(3);
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
                      "leadermonth,leaderday,money,flag,leader,"
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
            qDebug() << "tasks save";
    }
}

void SqlQuery::saveSignUpForLeader(QList<signUpForLeader> listSignUpForLeader){
    QSqlQuery query;
    query.exec("delete from signupforleaders");
    for(int i=0;i<listSignUpForLeader.size();i++){
        query.prepare("insert into signupforleaders(id,name,phonenum,idnum,password,"
                      "english,rewrdpoint,money,idtask,idthis)"
                      "values(?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(listSignUpForLeader[i].GetID());
        query.addBindValue(listSignUpForLeader[i].GetName());
        query.addBindValue(listSignUpForLeader[i].GetPhoneNum());
        query.addBindValue(listSignUpForLeader[i].GetIDNum());
        query.addBindValue(listSignUpForLeader[i].GetPassWrd());
        query.addBindValue(listSignUpForLeader[i].GetEnglish());
        query.addBindValue(listSignUpForLeader[i].GetRewrdPoint());
        query.addBindValue(listSignUpForLeader[i].GetMoney());
        query.addBindValue(listSignUpForLeader[i].GetIDTask());
        query.addBindValue(listSignUpForLeader[i].GetIDThis());
        if(!query.exec())
            qDebug() << query.lastError();
          else
            qDebug() << "signupforleader save";
    }
}

void SqlQuery::saveSignUpForTranslater(QList<signUpForTranslater> listSignUpForTranslater){
    QSqlQuery query;
    query.exec("delete from signupfortranslaters");
    for(int i=0;i<listSignUpForTranslater.size();i++){
        query.prepare("insert into signupfortranslaters(id,name,phonenum,idnum,password,"
                      "english,rewrdpoint,money,idtask,idthis)"
                      "values(?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(listSignUpForTranslater[i].GetID());
        query.addBindValue(listSignUpForTranslater[i].GetName());
        query.addBindValue(listSignUpForTranslater[i].GetPhoneNum());
        query.addBindValue(listSignUpForTranslater[i].GetIDNum());
        query.addBindValue(listSignUpForTranslater[i].GetPassWrd());
        query.addBindValue(listSignUpForTranslater[i].GetEnglish());
        query.addBindValue(listSignUpForTranslater[i].GetRewrdPoint());
        query.addBindValue(listSignUpForTranslater[i].GetMoney());
        query.addBindValue(listSignUpForTranslater[i].GetIDTask());
        query.addBindValue(listSignUpForTranslater[i].GetIDThis());
        
        if(!query.exec())
            qDebug() << query.lastError();
          else
            qDebug() << "signupfortranslater save";
    }
}

void SqlQuery::saveTaskLeader(QList<taskLeader> listTask){
    QSqlQuery query;
    query.exec("delete from taskleader");
    for(int i=0;i<listTask.size();i++){
        query.prepare("insert into taskleader(id,taskclass,task,"
                      "introduction,publisher,time,translateryear,"
                      "translatermonth,translaterday,money,flag,leader,"
                      "startyear,startmonth,startday,result,resulteditting)"
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
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
        query.addBindValue(listTask[i].GetResult());
        query.addBindValue(listTask[i].GetResultEditting());
        if(!query.exec())
            qDebug() << query.lastError();
          else
            qDebug() << "taskleader saved";
    }
}

void SqlQuery::saveTaskTranslater(QList<taskTranslater> listTask){
    QSqlQuery query;
    query.exec("delete from tasktranslater");
    for(int i=0;i<listTask.size();i++){
        query.prepare("insert into tasktranslater(id,taskclass,task,"
                      "introduction,publisher,time,endyear,"
                      "endmonth,endday,money,flag,leader,"
                      "startyear,startmonth,startday,translater,taskid,result,comment,"
                      "flagtoleader,commenteditting,resulteditting)"
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
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
        query.addBindValue(listTask[i].GetCommentEditting());
        query.addBindValue(listTask[i].GetResultEditting());
        if(!query.exec())
            qDebug() << query.lastError();
          else
            qDebug() << "tasktranslater save";
    }
}
