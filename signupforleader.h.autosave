#ifndef signUp_H
#define signUp_H

#include "user.h"

class signUp: public user {
public:
    signUp();
    signUp(user& myUser,int idTask);
    signUp(const signUp& newLeader);
    virtual ~signUp();
    operator =(const signUp& newLeader);

    void attachIDToUser(int ID);
    void EditIDTask(int idtask);
    int GetIDTask();

private:
    int m_iIdTask;
};

#endif // signUp_H
