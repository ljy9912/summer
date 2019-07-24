#ifndef LIST_H
#define LIST_H
#include <QList>
#include "taskpublisher.h"
#include "signupforleader.h"
#include "user.h"
#include "signupfortranslater.h"
#include "taskleader.h"
#include "tasktranslater.h"
#include "message.h"

class list
{
public:
    list();
    list(const list& newList);
    virtual ~list();
    operator =(const list& newList);

    void updateList(user myUser);
    void updateList(taskPublisher myTask);
    void updateList(taskLeader myTask);
    void updateList(taskTranslater myTask);
    void insertIntoList(user myUser);
    int searchUserInList(user myUser);
    int searchUserInList(int iIDUser);
    void insertIntoList(taskPublisher myTask);
    int searchTaskInList(taskPublisher myTask);
    int searchTaskInList(int iIDTask);
    int searchLeaderInList(signUpForLeader myLeader);
    int searchTranslaterInList(signUpForTranslater myTranslater);

    QList <taskPublisher> SearchTaskForPublisher(user myUser);
    QList <taskLeader> SearchTaskForLeader(user myUser);
    QList <signUpForLeader> SearchLeaderForTask(taskPublisher myTask);
    QList <signUpForTranslater> SearchTranslaterForTask(taskLeader myTask);
    QList <taskTranslater> SearchTaskForTranslater(user myUser);
    QList <taskTranslater> SearchTaskForTranslater(int idTask);
    QList <taskTranslater> SearchTaskForTranslater_302(int idTask);
    QList <Message> SearchMessageforUser(int idUser);
    
    QList <taskPublisher> TaskPublisher;
    QList <user> User;
    QList <signUpForLeader> SignUpForLeader;
    QList <signUpForTranslater> SignUpForTranslater;
    QList <taskLeader> TaskLeader;
    QList <taskTranslater> TaskTranslater;
    QList <Message> message;
    
    void TaskLeaderAppend(taskPublisher myLeader);

    void Delete(int idTask);

};

#endif // LIST_H
