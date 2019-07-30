#ifndef SIGNUPFORCHECKER_H
#define SIGNUPFORCHECKER_H
#include "user.h"

class signUpForChecker : public user
{
public:
    signUpForChecker();
    signUpForChecker(const signUpForChecker& myChecker);
    ~signUpForChecker();
    signUpForChecker& operator =(const signUpForChecker& myChecker);
    signUpForChecker(user& myUser,int newIDTask,int newIDThis);

    void EditIDTask(int idtask);
    void EditIDThis(int idtask);
    int GetIDTask();
    int GetIDThis();
    void attachIDToUser(int id);

private:
    int m_iIDTask;
    int m_iIDThis;
};

#endif // SIGNUPFORCHECKER_H
