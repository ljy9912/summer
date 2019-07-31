#include "listuser.h"

listUser::listUser()
{

}

listUser::~listUser(){

}

/*************************************************************************
【函数名称】listUser
【函数功能】该类的拷贝构造函数
【参数】const listUser &myList
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listUser::listUser(const listUser &myList){
    m_List=myList.m_List;
}

/*************************************************************************
【函数名称】operator =
【函数功能】重载=
【参数】const listUser& myList
【返回值】return *this;
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listUser& listUser::operator =(const listUser& myList){
    m_List=myList.m_List;
    return *this;
}

/*************************************************************************
【函数名称】operator =
【函数功能】重载=
【参数】const QList<user>& myList
【返回值】listUser&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listUser& listUser::operator =(const QList<user>& myList){
    m_List=myList;
    return *this;
}

/*************************************************************************
【函数名称】Update
【函数功能】将myUser在表中找到对应的节点并升级信息
【参数】user myUser
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listUser::Update(user myUser){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==myUser.GetID()){
            m_List[i]=myUser;
            break;
        }
    }
}

/*************************************************************************
【函数名称】InsertIntoList
【函数功能】在链表中插入新节点
【参数】user myUser
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listUser::InsertIntoList(user myUser){
    m_List.append(myUser);
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在链表中寻找id为IDUser的对象并返回对象所在节点的位置
【参数】QString IDUser
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listUser::SearchInList(QString IDUser){
    for(int i=0;i<m_List.size();i++){
        if(IDUser==m_List[i].GetID()){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在链表中寻找myUser对象并返回对象所在的节点位置
【参数】user myUser
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listUser::SearchInList(user myUser){
    for(int i=0;i<m_List.size();i++){
        if(myUser.GetID()==m_List[i].GetID()){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】NameExist
【函数功能】判断某个用户名在链表中是否存在
【参数】QString name
【返回值】bool
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
bool listUser::NameExist(QString name){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==name){
            return true;
        }
    }
    return false;
}
