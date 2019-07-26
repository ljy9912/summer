#ifndef LISTSIGNUPFORLEADER_H
#define LISTSIGNUPFORLEADER_H
#include "signupforleader.h"

class listSignUpForLeader
{
public:
    listSignUpForLeader();
    listSignUpForLeader(const listSignUpForLeader& myList);
    ~listSignUpForLeader();
    listSignUpForLeader& operator =(const listSignUpForLeader& myList);
    void Update(signUpForLeader myTask);
    int SearchInList(signUpForLeader myTask);
    int SearchInList(int iID);
    void InsertIntoList(signUpForLeader myTask);
    void Delete(int iIDTask);

//private:
    QList<signUpForLeader> m_List;
};

#endif // LISTSIGNUPFORLEADER_H