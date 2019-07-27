#ifndef LISTTASKLEADER_H
#define LISTTASKLEADER_H
#include "taskleader.h"
#include "user.h"
#include "taskpublisher.h"

class listTaskLeader
{
public:
    listTaskLeader();
    listTaskLeader(const listTaskLeader& myList);
    ~listTaskLeader();
    listTaskLeader& operator =(const listTaskLeader& myList);
    listTaskLeader& operator =(const QList<taskLeader>& myList);
    void Update(taskLeader myTask);
    void Delete(int iIDTask);
    int SearchInList(taskLeader myTask);
    int SearchInList(int iID);
    void InsertIntoList(taskLeader myTask);
    QList <taskLeader> SearchTaskForLeader(user myUser);
    void TaskLeaderAppend(taskPublisher myLeader);

//private:
    QList<taskLeader> m_List;
};

#endif // LISTTASKLEADER_H
