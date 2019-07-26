#ifndef LISTTASKTRANSLATER_H
#define LISTTASKTRANSLATER_H
#include "tasktranslater.h"
#include "user.h"

class listTaskTranslater
{
public:
    listTaskTranslater();
    listTaskTranslater(const listTaskTranslater& myList);
    ~listTaskTranslater();
    listTaskTranslater& operator =(const listTaskTranslater& myList);
    void Update(taskTranslater myTask);
    void Delete(int iIDTask);
    int SearchInList(taskTranslater myTask);
    int SearchInList(int iID);
    void InsertIntoList(taskTranslater myTask);
    QList <taskTranslater> SearchTaskForTranslater(user myUser);
    QList <taskTranslater> SearchTaskForTranslater(int idTask);
    QList <taskTranslater> SearchTaskForTranslater_302(int idTask);

    QList<taskTranslater> m_List;
};

#endif // LISTTASKTRANSLATER_H
