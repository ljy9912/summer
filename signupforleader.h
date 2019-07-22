#ifndef SIGNUPFORLEADER_H
#define SIGNUPFORLEADER_H

#include "user.h"

class signUpForLeader: public user {
public:
    signUpForLeader();
    signUpForLeader(user& myUser,int idTask);
    signUpForLeader(const signUpForLeader& newLeader);
    virtual ~signUpForLeader();
    operator =(const signUpForLeader& newLeader);

    void attachIDToUser(int ID);
    void EditIDTask(int idtask);
    int GetIDTask();

private:
    int m_iIdTask;
};

#endif // SIGNUPFORLEADER_H
