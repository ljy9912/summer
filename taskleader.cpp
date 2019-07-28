#include "taskleader.h"
#include <QSqlQuery>

taskLeader::taskLeader():task()
{
    m_iTranslaterYear=0;
    m_iTranslaterMonth=0;
    m_iTranslaterDay=0;
    m_Result="";
    m_ResultEditting="";
}

taskLeader::~taskLeader()
{

}

/*************************************************************************
【函数名称】taskLeader
【函数功能】taskLeader的拷贝构造函数
【参数】const taskLeader& newTaskLeader
【返回值】 无
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
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
    title=newTaskLeader.title;
}

/*************************************************************************
【函数名称】operator =
【函数功能】重载“=”函数
【参数】const taskLeader& newTaskLeader
【返回值】 无
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
taskLeader& taskLeader::operator =(const taskLeader& newTaskLeader){
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
    title=newTaskLeader.title;
    return *this;
}

/*************************************************************************
【函数名称】Get**
【函数功能】得到类内的private参数
【参数】无
【返回值】**
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
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



/*************************************************************************
【函数名称】Edit**
【函数功能】更改类内private的参数
【参数】**
【返回值】 无
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
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



/*************************************************************************
【函数名称】attachIDToTask
【函数功能】通过ID和tasklist内的数据初始化taskLeader对象
【参数】int ID,QList<taskLeader> TaskList
【返回值】 无
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
void taskLeader::attachIDToTask(int ID,QList<taskLeader> TaskList){
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
    m_iTranslaterYear=TaskList[i].GetTranslaterYear();
    m_iTranslaterMonth=TaskList[i].GetTranslaterMonth();
    m_iTranslaterDay=TaskList[i].GetTranslaterDay();
    m_Result=TaskList[i].GetResult();
    m_ResultEditting=TaskList[i].GetResultEditting();
    title=TaskList[i].GetTitle();
}

/*************************************************************************
【函数名称】attachIDToTask
【函数功能】通过id和数据库数据初始化taskLeader对象
【参数】int ID
【返回值】 无
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
void taskLeader::attachIDToTask(int ID){
    QSqlQuery query;
    id=ID;
    query.prepare("select * from taskleader where id=?");
    query.addBindValue(id);
    query.exec();
    if(query.first()){
        taskclass=query.value(1).toInt();
        translateTask=query.value(2).toString();
        introduction=query.value(3).toString();
        publisher=query.value(4).toString();
        time=query.value(5).toInt();
        m_iTranslaterYear=query.value(6).toInt();
        m_iTranslaterMonth=query.value(7).toInt();
        m_iTranslaterDay=query.value(8).toInt();
        money=query.value(9).toDouble();
        flag=query.value(10).toInt();
        leader=query.value(11).toString();
        startYear=query.value(12).toInt();
        startMonth=query.value(13).toInt();
        startDay=query.value(14).toInt();
        m_Result=query.value(15).toString();
        m_ResultEditting=query.value(16).toString();
        title=query.value(17).toString();
    }
}
