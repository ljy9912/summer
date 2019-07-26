#ifndef LISTUSER_H
#define LISTUSER_H
#include "user.h"
class listUser
{
public:
    listUser();
    listUser(const listUser& myList);
    ~listUser();
    listUser& operator =(const listUser& myList);
    void Update(user myUser);
    int SearchInList(user myUser);
    int SearchInList(QString IDUser);
    void InsertIntoList(user myUser);

//private:
    QList<user> m_List;
};

#endif // LISTUSER_H
