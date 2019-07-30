#ifndef LISTTASKTRANSLATER_H
#define LISTTASKTRANSLATER_H
#include "tasktranslater.h"
#include "user.h"
#include "taskleader.h"

class listTaskTranslater
{
public:
    listTaskTranslater();
    listTaskTranslater(const listTaskTranslater& myList);
    ~listTaskTranslater();
    listTaskTranslater& operator =(const listTaskTranslater& myList);
    listTaskTranslater& operator =(const QList<taskTranslater>& myList);
    void Update(taskTranslater myTask);
    void Delete(int iIDTask);
    int SearchInList(taskTranslater myTask);
    int SearchInList(int iID);
    void InsertIntoList(taskTranslater myTask);
    QList <taskTranslater> SearchTaskForTranslater(user myUser);
    QList <taskTranslater> SearchTaskForTranslater(int idTask);
    QList <taskTranslater> SearchTaskForTranslater_flag0(int idTask);
    QList <taskTranslater> SearchTaskForTranslater_flag13(int iIDTask);

    int GetSize_301(int iID);

    void TaskLeaderAppend(taskLeader myLeader, taskTranslater myTask);

    int GetID();

    QList<taskTranslater> m_List;
};

#endif // LISTTASKTRANSLATER_H
