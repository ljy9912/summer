#ifndef LISTTASKPUBLISHER_H
#define LISTTASKPUBLISHER_H
#include "taskpublisher.h"
#include "user.h"

class listTaskPublisher
{
public:
    listTaskPublisher();
    listTaskPublisher(const listTaskPublisher& myList);
    ~listTaskPublisher();
    listTaskPublisher& operator =(const listTaskPublisher &myList);
    listTaskPublisher& operator =(const QList<taskPublisher>& myList);
    void Update(taskPublisher myTask);
    int SearchInList(taskPublisher myTask);
    void InsertIntoList(taskPublisher myTask);
    int SearchInList(int iIDTask);
    QList <taskPublisher> SearchTaskForPublisher(user myUser);
    void Delete(int iIDTask);

    int GetID();

//private:
    QList<taskPublisher> m_List;
};

#endif // LISTTASKPUBLISHER_H
