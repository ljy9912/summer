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
    QString GetResultEditting();
    QString GetComment();
    QString GetCommentEditting();
    int GetFlagToLeader();
    
    void EditEndYear(int newYear);
    void EditEndMonth(int newMonth);
    void EditEndDay(int newDay);
    void EditTranslater(int newTranslater);
    void EditIDTask(int newIDTask);
    void EditResult(QString newResult);
    void EditResultEditting(QString newResult);
    void EditComment(QString newComment);
    void EditCommentEditting(QString newComment);
    void EditFlagToLeader(int newFlagToLeader);
    void AddComment(QString newComment);
    
    void attachIDToTask(int id,QList<taskTranslater> TaskList);
    void attachIDToTask(int id);
    
private:
    int m_iEndYear;
    int m_iEndMonth;
    int m_iEndDay;
    int m_iTranslater;
    int m_iIDTask;
    QString m_result;
    QString m_resultEditting;
    QString m_comment;
    QString m_commentEditting;
    int m_flagToLeader;//0为译者翻译，1为译者提交与负责人进行评价，2为负责人评价提交与译者进行修改，
    //3为译者提交修改与负责人再次审核
};

#endif // TASKTRANLATER_H
