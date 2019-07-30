#ifndef TASKPUBLISHER_H
#define TASKPUBLISHER_H
#include "task.h"

class taskPublisher:public task
{
public:
    taskPublisher();
    taskPublisher(const taskPublisher& myNewTask);
    virtual ~taskPublisher();
    taskPublisher& operator = (const taskPublisher& myNewTask);

    int GetLeaderYear();
    int GetLeaderMonth();
    int GetLeaderDay();
    QString GetResult();
    QString GetResultEditting();
    QString GetTaskChecker();


    void EditLeaderYear(int yyear);
    void EditLeaderMonth(int mmonth);
    void EditLeaderDay(int dday);
    void EditResult(QString newResult);
    void EditResultEditting(QString newResult);
    void EditTaskChecker(QString newChecker);


    void attachIDToTask(int id,QList<taskPublisher> TaskList);
    void attachIDToTask(int id);

    void EditInfo(int taskClass, QString intro, QString title,
                  QString task, int iTime, int iLeaderYear, int iLeaderMonth,
                  int iLeaderDay, double dMoney, QString Publisher);

private:
    int leaderYear;
    int leaderMonth;
    int leaderDay;
    QString m_result;
    QString m_resultEditting;
    QString m_checker;
};

#endif // TASKPUBLISHER_H
