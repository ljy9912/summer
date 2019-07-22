#ifndef TASKLEADER_H
#define TASKLEADER_H
#include "task.h"

class taskLeader : public task
{
public:
    taskLeader();
    ~taskLeader();
    taskLeader(const taskLeader& newTaskLeader);
    operator= (const taskLeader& newTaskLeader);
    
    int GetTranslaterYear();
    int GetTranslaterMonth();
    int GetTranslaterDay();
    QString GetResult();
    QString GetResultEditting();
    
    void EditTranslaterYear(int newYear);
    void EditTranslaterMonth(int newMonth);
    void EditTranslaterDay(int newDay);
    void EditResult(QString newResult);
    void EditResultEditting(QString newResult);
    
    void attachIDToTask(int id);
    
private:
    int m_iTranslaterYear;
    int m_iTranslaterMonth;
    int m_iTranslaterDay;
    QString m_Result;
    QString m_ResultEditting;
};

#endif // TASKLEADER_H
