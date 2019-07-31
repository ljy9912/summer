#ifndef LISTSIGNUPFORTRANSLATER_H
#define LISTSIGNUPFORTRANSLATER_H
#include "signupfortranslater.h"
#include "taskleader.h"

class listSignUpForTranslater
{
public:
    listSignUpForTranslater();
    listSignUpForTranslater(const listSignUpForTranslater& myList);
    ~listSignUpForTranslater();
    listSignUpForTranslater& operator =(const QList<signUpForTranslater> &myList);
    listSignUpForTranslater& operator =(const listSignUpForTranslater& myList);
    void Update(signUpForTranslater myUser);
    int SearchInList(signUpForTranslater myUser);
    int SearchInList(int iID);
    void InsertIntoList(signUpForTranslater myUser);
    QList <signUpForTranslater> SearchTranslaterForTask(taskLeader myUser);
    void Delete(int iIDTask);

    bool UserExists(QString iIDUser,int iIDTask);

    QList<signUpForTranslater> m_List;
};

#endif // LISTSIGNUPFORTRANSLATER_H
