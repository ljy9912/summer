#include "taskpublisher.h"
#include <QSqlQuery>

taskPublisher::taskPublisher(){
    id=0;
    taskclass=0;
    publisher=0;
    time=0;
    leaderYear=0;
    leaderMonth=0;
    leaderDay=0;
    startYear=0;
    startMonth=0;
    startDay=0;
    money=0;
    flag=0;
}

taskPublisher::taskPublisher(const taskPublisher &myNewTask)
    :task(myNewTask){
    leaderYear=myNewTask.leaderYear;
    leaderMonth=myNewTask.leaderMonth;
    leaderDay=myNewTask.leaderDay;
    m_result=myNewTask.m_result;
    m_resultEditting=myNewTask.m_resultEditting;
}

/*************************************************************************
【函数名称】~taskPublisher
【函数功能】taskPublisher类的默认析构函数
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
taskPublisher::~taskPublisher(){

}

taskPublisher& taskPublisher::operator = (const taskPublisher& myNewTask){
    id=myNewTask.id;
    taskclass=myNewTask.taskclass;
    translateTask=myNewTask.translateTask;
    introduction=myNewTask.introduction;
    publisher=myNewTask.publisher;
    time=myNewTask.time;
    leaderYear=myNewTask.leaderYear;
    leaderMonth=myNewTask.leaderMonth;
    leaderDay=myNewTask.leaderDay;
    startYear=myNewTask.startYear;
    startMonth=myNewTask.startMonth;
    startDay=myNewTask.startDay;
    money=myNewTask.money;
    flag=myNewTask.flag;
    leader=myNewTask.leader;
}

/*************************************************************************
【函数名称】Get**
【函数功能】返回类内的private参数
【参数】无
【返回值】**
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/


int taskPublisher::GetLeaderYear(){
    return leaderYear;
}
int taskPublisher::GetLeaderMonth(){
    return leaderMonth;
}
int taskPublisher::GetLeaderDay(){
    return leaderDay;
}

/*************************************************************************
【函数名称】Edit**
【函数功能】 更改类内private的参数
【参数】**
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/

void taskPublisher::EditLeaderYear(int yyear){
    leaderYear=yyear;
}
void taskPublisher::EditLeaderMonth(int mmonth){
    leaderMonth=mmonth;
}
void taskPublisher::EditLeaderDay(int dday){
    leaderDay=dday;
}


/*************************************************************************
【函数名称】 attachIDToTask
【函数功能】 将task的对象根据id初始化
【参数】 int ID
【返回值】无
【开发者及日期】李佳芸 2019.7.15
【更改记录】
*************************************************************************/
void taskPublisher::attachIDToTask(int ID,QList<taskPublisher> TaskList){
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
    leaderYear=TaskList[i].GetLeaderYear();
    leaderMonth=TaskList[i].GetLeaderMonth();
    leaderDay=TaskList[i].GetLeaderDay();
    money=TaskList[i].GetMoney();
    flag=TaskList[i].GetFlag();
    leader=TaskList[i].GetLeader();
    startYear=TaskList[i].GetStartYear();
    startMonth=TaskList[i].GetStartMonth();
    startDay=TaskList[i].GetStartDay();
}

void taskPublisher::attachIDToTask(int ID){
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
        leaderYear=query.value(6).toInt();
        leaderMonth=query.value(7).toInt();
        leaderDay=query.value(8).toInt();
        money=query.value(9).toDouble();
        flag=query.value(10).toInt();
        leader=query.value(11).toInt();
        startYear=query.value(12).toInt();
        startMonth=query.value(13).toInt();
        startDay=query.value(14).toInt();
    }
}
