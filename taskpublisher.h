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


    void EditLeaderYear(int yyear);
    void EditLeaderMonth(int mmonth);
    void EditLeaderDay(int dday);


    void attachIDToTask(int id);

private:
    int leaderYear;
    int leaderMonth;
    int leaderDay;
};

#endif // TASKPUBLISHER_H
