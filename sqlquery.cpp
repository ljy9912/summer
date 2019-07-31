#include "sqlquery.h"
#include <QList>
#include "user.h"
#include "task.h"
#include <QDebug>
#include <QSqlError>
#include "tasktranslater.h"
#include "message.h"

SqlQuery::SqlQuery()
{

}

SqlQuery::~SqlQuery(){

}

void SqlQuery::createUser(){
    query.prepare("CREATE TABLE IF NOT EXISTS users(id varchar(20) primary key,"
          "phoneNum varchar(20),IDnum varchar(20),"
         "password varchar(20),English varchar(50),rewrdPoint int,money double)");
    if(!query.exec()){
        qDebug() << query.lastError();
    }
      else{
        qDebug() << "Table created!";
    }
}

void SqlQuery::createTasks(){
    query.prepare("CREATE TABLE IF NOT EXISTS tasks(id int primary key,taskclass int,"
               "task varchar(1000),introduction varchar(1000),"
               "publisher varchar(20),time int,leaderyear int,"
               "leadermonth int,leaderday int,money double,flag int,leader varchar(20),"
                  "startyear int,startmonth int,startday int,title varchar(20),checker varchar(20))");//flag=0为编辑状态，
    //101为发布状态，102为选择负责人状态，201为负责人定日期状态，202为负责人招募译者状态，203为负责人分配任务状态
    //301为译者翻译状态与负责人审查,译者修改译文，302为负责人修改并整合译文，401为发布人验收状态
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
}

void SqlQuery::createSignUpForLeader(){
    query.prepare("create table if not exists signupforleaders(id varchar(20),"
                  "phoneNum varchar(20),IDnum varchar(20),"
                 "password varchar(20),English varchar(50),rewrdPoint int,"
                  "money double,idtask int,idthis int primary key)");
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
}

void SqlQuery::createSignUpForTranslater(){
    query.prepare("create table if not exists signupfortranslaters(id varchar(20),"
                  "phoneNum varchar(20),IDnum varchar(20),"
                 "password varchar(20),English varchar(50),rewrdPoint int,"
                  "money double,idtask int,idthis int primary key)");
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
}

void SqlQuery::createSignUpForChecker(){
    query.prepare("create table if not exists signupforchecker(id varchar(20),"
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
               "publisher varhcar(20),time int,translateryear int,"
               "translatermonth int,translaterday int,money double,flag int,leader varchar(20),"
                  "startyear int,startmonth int,startday int,result varchar(1000),"
                  "resulteditting varchar(1000),title varchar(20),checker varchar(20))");//flag=0为编辑状态，
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
               "publisher varchar(20),time int,endyear int,"
               "endmonth int,endday int,money double,flag int,leader varchar(20),"
                  "startyear int,startmonth int,startday int,translater varchar(20),taskid int,"
                  "result varchar(1000),comment varchar(1000),flagtoleader int,"
                  "commenteditting varchar(1000),resulteditting varchar(1000),title varchar(20))");//flag=0为编辑状态，
    //101为发布状态，102为选择负责人状态，201为负责人定日期状态，202为负责人招募译者状态，203为负责人分配任务状态
    //301为译者翻译状态与负责人审查,译者修改译文，302为负责人修改并整合译文，401为发布人验收状态
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
}

void SqlQuery::createMessage(){
    query.prepare("create table if not exists message(id int primary key,title varchar(100),"
                  "content varchar(1000),iduser varchar(20),flag int)");
    if(!query.exec())
        qDebug() << query.lastError();
      else
        qDebug() << "Table created!";
}

const QList<user> SqlQuery::GetUser(){
    QList <user> listUser;
    query.exec("select * from users");
    query.first();
    QString id=query.value(0).toString();
    user myUser;
    myUser.attachIDToUser(id);
    listUser.append(myUser);
    while(query.next()){
        QString id=query.value(0).toString();
        user myUser;
        myUser.attachIDToUser(id);
        listUser.append(myUser);
    }
    return listUser;
}

const QList<taskPublisher> SqlQuery::GetTasks(){
    QList <taskPublisher> listTask;
    query.exec("select * from tasks");
    query.first();
    int id=query.value(0).toInt();
    taskPublisher myTask;
    myTask.attachIDToTask(id);
    //myTask.EditFlag(102);
    listTask.append(myTask);
    while(query.next()){
        int id=query.value(0).toInt();
        taskPublisher myTask;
        myTask.attachIDToTask(id);
        myTask.EditFlag(102);
        //listTask.append(myTask);
        //myTask.EditFlag(402);
        //myTask.EditLeaderDay(31);
        listTask.append(myTask);
    }
    return listTask;
}

const QList<signUpForLeader> SqlQuery::GetSignUpForLeader(){
    QList <signUpForLeader> listLeader;
    query.exec("select * from signupforleaders");
    query.first();
    int id=query.value(8).toInt();
    signUpForLeader myLeader;
    myLeader.attachIDToUser(id);
    listLeader.append(myLeader);
    //myLeader.EditIDTask(1);
    listLeader.append(myLeader);
    while(query.next()){
        int id=query.value(8).toInt();
        signUpForLeader myLeader;
        myLeader.attachIDToUser(id);
        //myLeader.EditFlag(1);
        //myLeader.EditIDTask(4);
        listLeader.append(myLeader);
        //listLeader.append(myLeader);
    }
    return listLeader;
}

const QList<signUpForTranslater> SqlQuery::GetSignUpForTranslater(){
    QList <signUpForTranslater> listTranslater;
    query.exec("select * from signupfortranslaters");
    query.first();

    int id=query.value(8).toInt();
    signUpForTranslater myTranslater;
    myTranslater.attachIDToUser(id);
    listTranslater.append(myTranslater);
    while(query.next()){
        int id=query.value(8).toInt();
        signUpForTranslater myTranslater;
        myTranslater.attachIDToUser(id);
        listTranslater.append(myTranslater);
    }
    return listTranslater;
}

const QList<signUpForChecker> SqlQuery::GetSignUpForChecker(){
    QList <signUpForChecker> listChecker;
    query.exec("select * from signupforchecker");
    query.first();

    int id=query.value(8).toInt();
    signUpForChecker myChecker;
    myChecker.attachIDToUser(id);
    listChecker.append(myChecker);
    while(query.next()){
        int id=query.value(8).toInt();
        signUpForChecker myChecker;
        myChecker.attachIDToUser(id);
        listChecker.append(myChecker);
    }
    return listChecker;
}

const QList<taskLeader> SqlQuery::GetTaskLeader(){
    QList <taskLeader> listTask;
    query.exec("select * from taskleader");

    query.first();
    int id=query.value(0).toInt();
    taskLeader myTask;
    myTask.attachIDToTask(id);
    listTask.append(myTask);
    while(query.next()){
        int id=query.value(0).toInt();
        taskLeader myTask;
        myTask.attachIDToTask(id);
        //myTask.EditFlag(401);
        //myTask.EditTranslaterDay(25);
        listTask.append(myTask);
    }
    return listTask;
}

const QList<taskTranslater> SqlQuery::GetTaskTranslater(){
    QList <taskTranslater> listTask;
    query.exec("select * from tasktranslater");

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

const QList<Message> SqlQuery::GetMessage(){
    QList <Message> listMessage;

    query.exec("select * from message");

    query.first();
    int id=query.value(0).toInt();
    Message myMessage;
    myMessage.AttachIDToMessage(id);
    listMessage.append(myMessage);
    while(query.next()){
        int id=query.value(0).toInt();
        Message myMessage;
        myMessage.AttachIDToMessage(id);
        //myTask.EditFlagToLeader(3);
        listMessage.append(myMessage);
    }
    return listMessage;
}

void SqlQuery::saveUser(QList<user> listUser){
    query.exec("delete from users");
    for(int i=0;i<listUser.size();i++){
        query.prepare("insert into users(id,phonenum,idnum,password,"
                      "english,rewrdpoint,money)"
                      "values(?,?,?,?,?,?,?)");
        query.addBindValue(listUser[i].GetID());
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
    query.exec("delete from tasks");
    for(int i=0;i<listTask.size();i++){
        query.prepare("insert into tasks(id,taskclass,task,"
                      "introduction,publisher,time,leaderyear,"
                      "leadermonth,leaderday,money,flag,leader,"
                      "startyear,startmonth,startday,title,checker)"
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
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
        query.addBindValue(listTask[i].GetTitle());
        query.addBindValue(listTask[i].GetTaskChecker());
        if(!query.exec())
            qDebug() << query.lastError();
          else
            qDebug() << "tasks save";
    }
}

void SqlQuery::saveSignUpForLeader(QList<signUpForLeader> listSignUpForLeader){
    query.exec("delete from signupforleaders");
    for(int i=0;i<listSignUpForLeader.size();i++){
        query.prepare("insert into signupforleaders(id,phonenum,idnum,password,"
                      "english,rewrdpoint,money,idtask,idthis)"
                      "values(?,?,?,?,?,?,?,?,?)");
        query.addBindValue(listSignUpForLeader[i].GetID());
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
    query.exec("delete from signupfortranslaters");
    for(int i=0;i<listSignUpForTranslater.size();i++){
        query.prepare("insert into signupfortranslaters(id,phonenum,idnum,password,"
                      "english,rewrdpoint,money,idtask,idthis)"
                      "values(?,?,?,?,?,?,?,?,?)");
        query.addBindValue(listSignUpForTranslater[i].GetID());
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

void SqlQuery::saveSignUpForChecker(QList<signUpForChecker> listSignUpForChecker){
    query.exec("delete from signupforchecker");
    for(int i=0;i<listSignUpForChecker.size();i++){
        query.prepare("insert into signupforchecker(id,phonenum,idnum,password,"
                      "english,rewrdpoint,money,idtask,idthis)"
                      "values(?,?,?,?,?,?,?,?,?)");
        query.addBindValue(listSignUpForChecker[i].GetID());
        query.addBindValue(listSignUpForChecker[i].GetPhoneNum());
        query.addBindValue(listSignUpForChecker[i].GetIDNum());
        query.addBindValue(listSignUpForChecker[i].GetPassWrd());
        query.addBindValue(listSignUpForChecker[i].GetEnglish());
        query.addBindValue(listSignUpForChecker[i].GetRewrdPoint());
        query.addBindValue(listSignUpForChecker[i].GetMoney());
        query.addBindValue(listSignUpForChecker[i].GetIDTask());
        query.addBindValue(listSignUpForChecker[i].GetIDThis());

        if(!query.exec())
            qDebug() << query.lastError();
          else
            qDebug() << "signupforchecker save";
    }
}

void SqlQuery::saveTaskLeader(QList<taskLeader> listTask){
    query.exec("delete from taskleader");
    for(int i=0;i<listTask.size();i++){
        query.prepare("insert into taskleader(id,taskclass,task,"
                      "introduction,publisher,time,translateryear,"
                      "translatermonth,translaterday,money,flag,leader,"
                      "startyear,startmonth,startday,result,"
                      "resulteditting,title,checker)"
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
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
        query.addBindValue(listTask[i].GetTitle());
        query.addBindValue(listTask[i].GetChecker());
        if(!query.exec())
            qDebug() << query.lastError();
          else
            qDebug() << "taskleader saved";
    }
}

void SqlQuery::saveTaskTranslater(QList<taskTranslater> listTask){
    query.exec("delete from tasktranslater");
    for(int i=0;i<listTask.size();i++){
        query.prepare("insert into tasktranslater(id,taskclass,task,"
                      "introduction,publisher,time,endyear,"
                      "endmonth,endday,money,flag,leader,"
                      "startyear,startmonth,startday,translater,taskid,result,comment,"
                      "flagtoleader,commenteditting,resulteditting,title)"
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
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
        query.addBindValue(listTask[i].GetTitle());
        if(!query.exec()){
            qDebug() << query.lastError();
        }
          else{
            qDebug() << "tasktranslater save";
        }
    }
}

void SqlQuery::saveMessage(QList<Message> messageList){
    query.exec("delete from message");
    for(int i=0;i<messageList.size();i++){
        if(messageList[i].GetFlag()==0){
            query.prepare("insert into message (id,title,content,iduser,flag) values(?,?,?,?,?)");
            query.addBindValue(messageList[i].GetID());
            query.addBindValue(messageList[i].GetTitle());
            query.addBindValue(messageList[i].GetContent());
            query.addBindValue(messageList[i].GetUser());
            query.addBindValue(messageList[i].GetFlag());
            if(!query.exec()){
                qDebug()<<query.lastError();
            }
            else{
                qDebug()<<"message save";
            }
        }
    }
}
