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
    listUser& operator =(const QList<user>& myList);
    void Update(user myUser);
    int SearchInList(user myUser);
    int SearchInList(QString IDUser);
    void InsertIntoList(user myUser);
    bool NameExist(QString name);

//private:
    QList<user> m_List;
};

#endif // LISTUSER_H
