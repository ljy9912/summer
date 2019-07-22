#ifndef TASKTRANLATER_H
#define TASKTRANLATER_H
#include "task.h"

class taskTranslater : public task
{
public:
    taskTranslater();
    virtual ~taskTranslater();
    taskTranslater(const taskTranslater& myNewTask);
    operator =(const taskTranslater& myNewTask);
    int GetEndYear();
    int GetEndMonth();
    int GetEndDay();
    int GetTranslater();
    int GetIDTask();
    QString GetResult();
    QString GetComment();
    int GetFlagToLeader();
    
    void EditEndYear(int newYear);
    void EditEndMonth(int newMonth);
    void EditEndDay(int newDay);
    void EditTranslater(int newTranslater);
    void EditIDTask(int newIDTask);
    void EditResult(QString newResult);
    void EditComment(QString newComment);
    void EditFlagToLeader(int newFlagToLeader);
    
    void attachIDToTask(int id);
    
private:
    int m_iEndYear;
    int m_iEndMonth;
    int m_iEndDay;
    int m_iTranslater;
    int m_iIDTask;
    QString m_result;
    QString m_comment;
    int m_flagToLeader;
};

#endif // TASKTRANLATER_H
