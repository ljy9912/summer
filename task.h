#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QList>

class task{
private:

protected:
    int id;
    int taskclass;
    QString translateTask;
    QString introduction;
    int time;
    int startYear;
    int startMonth;
    int startDay;
    double money;
    int flag;
    int publisher;
    int leader;

    /*************************************************************************
    【函数名称】Get**
    【函数功能】返回类内的private参数
    【参数】无
    【返回值】**
    【开发者及日期】李佳芸 2019.7.12
    【更改记录】
    *************************************************************************/

public:
    task();
    task(const task& myNewTask);
    virtual ~task();
    task& operator = (const task& myNewTask);

    int GetID();
    int GetTaskClass();
    QString GetTask();
    QString GetIntroduction();
    int GetPublisher();
    int GetTime();
    int GetStartYear();
    int GetStartMonth();
    int GetStartDay();
    double GetMoney();
    int GetFlag();
    int GetLeader();


    void EditID(int iid);
    void EditTaskClass(int taskClass);
    void EditTask(QString taskk);
    void EditIntroduction(QString iintroduction);
    void EditPublisher(int ppublisher);
    void EditTime(int ttime);
    void EditStartYear(int nYear);
    void EditStartMonth(int nMonth);
    void EditStartDay(int nDay);
    void EditMoney(double mmoney);
    void EditFlag(int fflag);
    void EditLeader(int iLeader);

    void attachIDToTask(int id);


};

#endif // TASK_H
