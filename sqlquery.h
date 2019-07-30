#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QSqlQuery>
#include "user.h"
#include "taskpublisher.h"
#include "signupforleader.h"
#include "tasktranslater.h"
#include "signupfortranslater.h"
#include "taskleader.h"
#include "message.h"
#include "signupforchecker.h"

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
    void createSignUpForChecker();
    void createTaskLeader();
    void createTaskTranslater();
    void createMessage();
    
    const QList<user> GetUser();
    const QList<taskPublisher> GetTasks();
    const QList<signUpForLeader> GetSignUpForLeader();
    const QList<signUpForTranslater> GetSignUpForTranslater();
    const QList<taskLeader> GetTaskLeader();
    const QList<taskTranslater> GetTaskTranslater();
    const QList<Message> GetMessage();
    const QList<signUpForChecker> GetSignUpForChecker();
    
    void saveUser(QList<user> listUser);
    void saveTasks(QList<taskPublisher> listTask);
    void saveSignUpForLeader(QList<signUpForLeader> listSignUpForLeader);
    void saveSignUpForTranslater(QList<signUpForTranslater> listSignUpForTranslater);
    void saveTaskLeader(QList<taskLeader> listTask);
    void saveTaskTranslater(QList<taskTranslater> listTask);
    void saveMessage(QList<Message> messageList);
    void saveSignUpForChecker(QList<signUpForChecker> listSignUpForChecker);
};

#endif // SQLQUERY_H
