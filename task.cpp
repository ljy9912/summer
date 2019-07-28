#include "task.h"
#include <QSqlQuery>
#include <QVariant>

/*************************************************************************
【函数名称】task
【函数功能】task类的默认构造函数
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
task::task(){
    id=0;
    taskclass=0;
    translateTask="";
    introduction="";
    title="";
    time=0;
    startYear=0;
    startMonth=0;
    startDay=0;
    money=0;
    flag=0;
    publisher="";
    leader="";
}

/*************************************************************************
【函数名称】task
【函数功能】task类的拷贝构造函数
【参数】const task &myNewTask
【返回值】无
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
task::task(const task &myNewTask){
    id=myNewTask.id;
    taskclass=myNewTask.taskclass;
    translateTask=myNewTask.translateTask;
    introduction=myNewTask.introduction;
    time=myNewTask.time;
    startYear=myNewTask.startYear;
    startMonth=myNewTask.startMonth;
    startDay=myNewTask.startDay;
    money=myNewTask.money;
    flag=myNewTask.flag;
    leader=myNewTask.leader;
    publisher=myNewTask.publisher;
    title=myNewTask.title;
}

/*************************************************************************
【函数名称】~task
【函数功能】task类的默认析构函数
【参数】无
【返回值】无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
task::~task(){

}

/*************************************************************************
【函数名称】operator =
【函数功能】重载“=”函数
【参数】const task& myNewTask
【返回值】无
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
task& task::operator = (const task& myNewTask){
    id=myNewTask.id;
    taskclass=myNewTask.taskclass;
    translateTask=myNewTask.translateTask;
    introduction=myNewTask.introduction;
    time=myNewTask.time;
    startYear=myNewTask.startYear;
    startMonth=myNewTask.startMonth;
    startDay=myNewTask.startDay;
    money=myNewTask.money;
    flag=myNewTask.flag;
    leader=myNewTask.leader;
    publisher=myNewTask.publisher;
    title=myNewTask.title;
    return *this;
}

/*************************************************************************
【函数名称】Get**
【函数功能】返回类内的private参数
【参数】无
【返回值】**
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/


int task::GetID(){
    return id;
}
int task::GetTaskClass(){
    return taskclass;
}
QString task::GetTask(){
    return translateTask;
}
QString task::GetIntroduction(){
    return introduction;
}
QString task::GetTitle(){
    return title;
}
int task::GetTime(){
    return time;
}
int task::GetStartYear(){
    return startYear;
}
int task::GetStartMonth(){
    return startMonth;
}
int task::GetStartDay(){
    return startDay;
}
double task::GetMoney(){
    return money;
}
int task::GetFlag(){
    return flag;
}
QString task::GetLeader(){
    return leader;
}
QString task::GetPublisher(){
    return publisher;
}

/*************************************************************************
【函数名称】Edit**
【函数功能】 更改类内private的参数
【参数】**
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void task::EditID(int iid){
    id=iid;
}
void task::EditTaskClass(int taskClass){
    taskclass=taskClass;
}
void task::EditTask(QString taskk){
    translateTask=taskk;
}
void task::EditIntroduction(QString iintroduction){
    introduction=iintroduction;
}
void task::EditTitle(QString newTitle){
    title=newTitle;
}
void task::EditTime(int ttime){
    time=ttime;
}
void task::EditStartYear(int nYear){
    startYear=nYear;
}
void task::EditStartMonth(int nMonth){
    startMonth=nMonth;
}
void task::EditStartDay(int nDay){
    startDay=nDay;
}
void task::EditMoney(double mmoney){
    money=mmoney;
}
void task::EditFlag(int fflag){
    flag=fflag;
}
void task::EditLeader(QString iLeader){
    leader=iLeader;
}
void task::EditPublisher(QString ppublisher){
    publisher=ppublisher;
}




