#ifndef SIGNUPFORLEADER_H
#define SIGNUPFORLEADER_H

#include "user.h"

class signUpForLeader: public user {
public:
    signUpForLeader();
    signUpForLeader(user& myUser,int idTask,int idThis);
    signUpForLeader(const signUpForLeader& newLeader);
    virtual ~signUpForLeader();
    operator =(const signUpForLeader& newLeader);

    void attachIDToUser(int ID);
    void EditIDTask(int idtask);
    void EditIDThis(int idtask);
    int GetIDTask();
    int GetIDThis();

private:
    int m_iIdTask;
    int m_iIDThis;
};

#endif // SIGNUPFORLEADER_H
