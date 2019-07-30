#ifndef LISTSIGNUPFORCHECKER_H
#define LISTSIGNUPFORCHECKER_H
#include "signupforchecker.h"

class listSignUpForChecker
{
public:
    listSignUpForChecker();
    listSignUpForChecker(const listSignUpForChecker &myList);
    ~listSignUpForChecker();
    listSignUpForChecker& operator =(const listSignUpForChecker& myList);
    listSignUpForChecker& operator =(const QList<signUpForChecker>& myList);

    void Update(signUpForChecker myTask);
    int SearchInList(signUpForChecker myTask);
    int SearchInList(int iID);
    void InsertIntoList(signUpForChecker myTask);
    void Delete(int iIDTask);
    QList<signUpForChecker> SearchCheckerForTask(int myTaskid);


    bool UserExists(QString iIDUser,int iIDTask);

    QList<signUpForChecker> m_List;
};

#endif // LISTSIGNUPFORCHECKER_H
