#ifndef SIGNUPFORTRANSLATER_H
#define SIGNUPFORTRANSLATER_H
#include "user.h"

class signUpForTranslater : public user
{
public:
    signUpForTranslater();
    signUpForTranslater(user& myUser,int idTask,int idThis);
    signUpForTranslater(const signUpForTranslater& newTranslater);
    virtual ~signUpForTranslater();
    operator =(const signUpForTranslater& newTranslater);

    void attachIDToUser(int ID);
    void EditIDTask(int idtask);
    void EditIDThis(int idTask);
    int GetIDTask();
    int GetIDThis();

private:
    int m_iIdTask;
    int m_iIDThis;
};

#endif // SIGNUPFORTRANSLATER_H
