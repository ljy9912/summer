#include "taskleader.h"
#include <QSqlQuery>

taskLeader::taskLeader()
{

}

taskLeader::~taskLeader()
{

}

taskLeader::taskLeader(const taskLeader& newTaskLeader){
    id=newTaskLeader.id;
    taskclass=newTaskLeader.taskclass;
    translateTask=newTaskLeader.translateTask;
    introduction=newTaskLeader.introduction;
    publisher=newTaskLeader.publisher;
    time=newTaskLeader.time;
    m_iTranslaterYear=newTaskLeader.m_iTranslaterYear;
    m_iTranslaterMonth=newTaskLeader.m_iTranslaterMonth;
    m_iTranslaterDay=newTaskLeader.m_iTranslaterDay;
    money=newTaskLeader.money;
    flag=newTaskLeader.flag;
    leader=newTaskLeader.leader;
    startYear=newTaskLeader.startYear;
    startMonth=newTaskLeader.startMonth;
    startDay=newTaskLeader.startDay;
    m_Result=newTaskLeader.m_Result;
    m_ResultEditting=newTaskLeader.m_ResultEditting;
}

taskLeader::operator =(const taskLeader& newTaskLeader){
    id=newTaskLeader.id;
    taskclass=newTaskLeader.taskclass;
    translateTask=newTaskLeader.translateTask;
    introduction=newTaskLeader.introduction;
    publisher=newTaskLeader.publisher;
    time=newTaskLeader.time;
    m_iTranslaterYear=newTaskLeader.m_iTranslaterYear;
    m_iTranslaterMonth=newTaskLeader.m_iTranslaterMonth;
    m_iTranslaterDay=newTaskLeader.m_iTranslaterDay;
    money=newTaskLeader.money;
    flag=newTaskLeader.flag;
    leader=newTaskLeader.leader;
    startYear=newTaskLeader.startYear;
    startMonth=newTaskLeader.startMonth;
    startDay=newTaskLeader.startDay;
    m_Result=newTaskLeader.m_Result;
    m_ResultEditting=newTaskLeader.m_ResultEditting;
}

int taskLeader::GetTranslaterYear(){
    return m_iTranslaterYear;
}

int taskLeader::GetTranslaterMonth(){
    return m_iTranslaterMonth;
}

int taskLeader::GetTranslaterDay(){
    return m_iTranslaterDay;
}

QString taskLeader::GetResult(){
    return m_Result;
}

QString taskLeader::GetResultEditting(){
    return m_ResultEditting;
}



void taskLeader::EditTranslaterYear(int newYear){
    m_iTranslaterYear=newYear;
}

void taskLeader::EditTranslaterMonth(int newMonth){
    m_iTranslaterMonth=newMonth;
}

void taskLeader::EditTranslaterDay(int newDay){
    m_iTranslaterDay=newDay;
}

void taskLeader::EditResult(QString newResult){
    m_Result=newResult;
}

void taskLeader::EditResultEditting(QString newResult){
    m_ResultEditting=newResult;
}



void taskLeader::attachIDToTask(int ID){
    QSqlQuery query;
    id=ID;
    query.prepare("select * from tasks where id=?");
    query.addBindValue(id);
    query.exec();
    if(query.first()){
        taskclass=query.value(1).toInt();
        translateTask=query.value(2).toString();
        introduction=query.value(3).toString();
        publisher=query.value(4).toInt();
        time=query.value(5).toInt();
        m_iTranslaterYear=query.value(6).toInt();
        m_iTranslaterMonth=query.value(7).toInt();
        m_iTranslaterDay=query.value(8).toInt();
        money=query.value(9).toDouble();
        flag=query.value(10).toInt();
        leader=query.value(11).toInt();
        startYear=query.value(12).toInt();
        startMonth=query.value(13).toInt();
        startDay=query.value(14).toInt();
        m_Result=query.value(15).toString();
        m_ResultEditting=query.value(16).toString();
    }
}
