#ifndef SIGNUPFORTRANSLATER_H
#define SIGNUPFORTRANSLATER_H
#include "user.h"

class signUpForTranslater : public user
{
public:
    signUpForTranslater();
    signUpForTranslater(user& myUser,int idTask);
    signUpForTranslater(const signUpForTranslater& newTranslater);
    virtual ~signUpForTranslater();
    operator =(const signUpForTranslater& newTranslater);

    void attachIDToUser(int ID);
    void EditIDTask(int idtask);
    int GetIDTask();

private:
    int m_iIdTask;
};

#endif // SIGNUPFORTRANSLATER_H
