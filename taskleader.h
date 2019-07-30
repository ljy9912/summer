#ifndef TASKLEADER_H
#define TASKLEADER_H
#include "task.h"

class taskLeader : public task
{
public:
    taskLeader();
    ~taskLeader();
    taskLeader(const taskLeader& newTaskLeader);
    taskLeader& operator= (const taskLeader& newTaskLeader);
    
    int GetTranslaterYear();
    int GetTranslaterMonth();
    int GetTranslaterDay();
    QString GetResult();
    QString GetResultEditting();
    QString GetChecker();
    
    void EditTranslaterYear(int newYear);
    void EditTranslaterMonth(int newMonth);
    void EditTranslaterDay(int newDay);
    void EditResult(QString newResult);
    void EditResultEditting(QString newResult);
    void EditChecker(QString newChecker);
    
    void attachIDToTask(int id,QList<taskLeader> TaskList);
    void attachIDToTask(int id);
    
private:
    int m_iTranslaterYear;
    int m_iTranslaterMonth;
    int m_iTranslaterDay;
    QString m_Result;
    QString m_ResultEditting;
    QString m_Checker;
};

#endif // TASKLEADER_H
