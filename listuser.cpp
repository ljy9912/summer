#include "listuser.h"

listUser::listUser()
{

}

listUser::~listUser(){

}

listUser::listUser(const listUser &myList){
    m_List=myList.m_List;
}

listUser& listUser::operator =(const listUser& myList){
    m_List=myList.m_List;
    return *this;
}

listUser& listUser::operator =(const QList<user>& myList){
    m_List=myList;
    return *this;
}


void listUser::Update(user myUser){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==myUser.GetID()){
            m_List[i]=myUser;
            break;
        }
    }
}

void listUser::InsertIntoList(user myUser){
    m_List.append(myUser);
}

int listUser::SearchInList(QString IDUser){
    for(int i=0;i<m_List.size();i++){
        if(IDUser==m_List[i].GetID()){
            return i;
        }
    }
}

int listUser::SearchInList(user myUser){
    for(int i=0;i<m_List.size();i++){
        if(myUser.GetID()==m_List[i].GetID()){
            return i;
        }
    }
}

bool listUser::NameExist(QString name){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==name){
            return true;
        }
    }
    return false;
}
