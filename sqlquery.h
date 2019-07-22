#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QSqlQuery>
#include "user.h"
#include "taskpublisher.h"
#include "list.h"
#include "signupforleader.h"
#include "tasktranslater.h"

class SqlQuery
{
private:
    QSqlQuery query;

public:
    SqlQuery();
    ~SqlQuery();
    void createUser();
    void createTasks();
    void createSignUpForLeader();
    void createSignUpForTranslater();
    void createTaskLeader();
    void createTaskTranslater();
    
    const QList<user> GetUser();
    const QList<taskPublisher> GetTasks();
    const QList<signUpForLeader> GetSignUpForLeader();
    const QList<signUpForTranslater> GetSignUpForTranslater();
    const QList<taskLeader> GetTaskLeader();
    const QList<taskTranslater> GetTaskTranslater();
    
    void saveUser(QList<user> listUser);
    void saveTasks(QList<taskPublisher> listTask);
    void saveSignUpForLeader(QList<signUpForLeader> listSignUpForLeader);
    void saveSignUpForTranslater(QList<signUpForTranslater> listSignUpForTranslater);
    void saveTaskLeader(QList<taskLeader> listTask);
    void saveTaskTranslater(QList<taskTranslater> listTask);
};

#endif // SQLQUERY_H
