#include "tasktranslater.h"
#include <QSqlQuery>
#include <QDateTime>

taskTranslater::taskTranslater()
{
    m_flagToLeader=0;
}

taskTranslater::~taskTranslater(){

}

taskTranslater::taskTranslater(const taskTranslater& newTaskTranslater){
    id=newTaskTranslater.id;
    taskclass=newTaskTranslater.taskclass;
    translateTask=newTaskTranslater.translateTask;
    introduction=newTaskTranslater.introduction;
    publisher=newTaskTranslater.publisher;
    time=newTaskTranslater.time;
    m_iEndYear=newTaskTranslater.m_iEndYear;
    m_iEndMonth=newTaskTranslater.m_iEndMonth;
    m_iEndDay=newTaskTranslater.m_iEndDay;
    money=newTaskTranslater.money;
    flag=newTaskTranslater.flag;
    leader=newTaskTranslater.leader;
    startYear=newTaskTranslater.startYear;
    startMonth=newTaskTranslater.startMonth;
    startDay=newTaskTranslater.startDay;
    m_iTranslater=newTaskTranslater.m_iTranslater;
    m_iIDTask=newTaskTranslater.m_iIDTask;
    m_result=newTaskTranslater.m_result;
    m_resultEditting=newTaskTranslater.m_resultEditting;
    m_comment=newTaskTranslater.m_comment;
    m_flagToLeader=newTaskTranslater.m_flagToLeader;
    m_commentEditting=newTaskTranslater.m_commentEditting;
}

taskTranslater::operator =(const taskTranslater& newTaskTranslater){
    id=newTaskTranslater.id;
    taskclass=newTaskTranslater.taskclass;
    translateTask=newTaskTranslater.translateTask;
    introduction=newTaskTranslater.introduction;
    publisher=newTaskTranslater.publisher;
    time=newTaskTranslater.time;
    m_iEndYear=newTaskTranslater.m_iEndYear;
    m_iEndMonth=newTaskTranslater.m_iEndMonth;
    m_iEndDay=newTaskTranslater.m_iEndDay;
    money=newTaskTranslater.money;
    flag=newTaskTranslater.flag;
    leader=newTaskTranslater.leader;
    startYear=newTaskTranslater.startYear;
    startMonth=newTaskTranslater.startMonth;
    startDay=newTaskTranslater.startDay;
    m_iTranslater=newTaskTranslater.m_iTranslater;
    m_iIDTask=newTaskTranslater.m_iIDTask;
    m_result=newTaskTranslater.m_result;
    m_resultEditting=newTaskTranslater.m_resultEditting;
    m_comment=newTaskTranslater.m_comment;
    m_flagToLeader=newTaskTranslater.m_flagToLeader;
    m_commentEditting=newTaskTranslater.m_commentEditting;
}

int taskTranslater::GetEndYear(){
    return m_iEndYear;
}

int taskTranslater::GetEndMonth(){
    return m_iEndMonth;
}

int taskTranslater::GetEndDay(){
    return m_iEndDay;
}
int taskTranslater::GetTranslater(){
    return m_iTranslater;
}

int taskTranslater::GetIDTask(){
    return m_iIDTask;
}

QString taskTranslater::GetResult(){
    return m_result;
}
QString taskTranslater::GetComment(){
    return m_comment;
}

int taskTranslater::GetFlagToLeader(){
    return m_flagToLeader;
}

QString taskTranslater::GetCommentEditting(){
    return m_commentEditting;
}

QString taskTranslater::GetResultEditting(){
    return m_resultEditting;
}



void taskTranslater::EditEndYear(int newYear){
    m_iEndYear=newYear;
}

void taskTranslater::EditEndMonth(int newMonth){
    m_iEndMonth=newMonth;
}

void taskTranslater::EditEndDay(int newDay){
    m_iEndDay=newDay;
}
void taskTranslater::EditTranslater(int newTranslater){
    m_iTranslater=newTranslater;
}

void taskTranslater::EditIDTask(int newIDTask){
    m_iIDTask=newIDTask;
}

void taskTranslater::EditResult(QString newResult){
    m_result=newResult;
}

void taskTranslater::EditComment(QString newComment){
    m_comment=newComment;
}

void taskTranslater::EditFlagToLeader(int newFlagToLeader){
    m_flagToLeader=newFlagToLeader;
}

void taskTranslater::EditCommentEditting(QString newComment){
    m_commentEditting=newComment;
}

void taskTranslater::AddComment(QString newComment){
    QDateTime time;
    QString myTime=time.currentDateTime().toString();
    m_comment.append(myTime);
    m_comment.append("：\n");
    m_comment.append(newComment);
    m_comment.append("\n");
}

void taskTranslater::EditResultEditting(QString newResult){
    m_resultEditting=newResult;
}


void taskTranslater::attachIDToTask(int ID,QList<taskTranslater> TaskList){
    int i=0;
    for(i=0;i<TaskList.size();i++){
        if(TaskList[i].GetID()==ID){
            break;
        }
    }
    taskclass=TaskList[i].GetTaskClass();
    translateTask=TaskList[i].GetTask();
    introduction=TaskList[i].GetIntroduction();
    publisher=TaskList[i].GetPublisher();
    time=TaskList[i].GetTime();
    money=TaskList[i].GetMoney();
    flag=TaskList[i].GetFlag();
    leader=TaskList[i].GetLeader();
    startYear=TaskList[i].GetStartYear();
    startMonth=TaskList[i].GetStartMonth();
    startDay=TaskList[i].GetStartDay();
    m_iEndYear=TaskList[i].GetEndYear();
    m_iEndMonth=TaskList[i].GetEndMonth();
    m_iEndDay=TaskList[i].GetEndDay();
    m_iTranslater=TaskList[i].GetTranslater();
    m_iIDTask=TaskList[i].GetIDTask();
    m_resultEditting=TaskList[i].GetResultEditting();
}

void taskTranslater::attachIDToTask(int ID){
    QSqlQuery query;
    id=ID;
    query.prepare("select * from tasktranslater where id=?");
    query.addBindValue(id);
    query.exec();
    if(query.first()){
        taskclass=query.value(1).toInt();
        translateTask=query.value(2).toString();
        introduction=query.value(3).toString();
        publisher=query.value(4).toInt();
        time=query.value(5).toInt();
        m_iEndYear=query.value(6).toInt();
        m_iEndMonth=query.value(7).toInt();
        m_iEndDay=query.value(8).toInt();
        money=query.value(9).toDouble();
        flag=query.value(10).toInt();
        leader=query.value(11).toInt();
        startYear=query.value(12).toInt();
        startMonth=query.value(13).toInt();
        startDay=query.value(14).toInt();
        m_iTranslater=query.value(15).toInt();
        m_iIDTask=query.value(16).toInt();
        m_result=query.value(17).toString();
        m_comment=query.value(18).toString();
        m_flagToLeader=query.value(19).toInt();
        m_commentEditting=query.value(20).toString();
        m_resultEditting=query.value(21).toString();
    }
}
