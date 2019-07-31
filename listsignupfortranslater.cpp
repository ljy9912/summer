#include "listsignupfortranslater.h"
#include "tasktranslater.h"

listSignUpForTranslater::listSignUpForTranslater()
{

}

listSignUpForTranslater::~listSignUpForTranslater(){

}

/*************************************************************************
【函数名称】listSignUpForTranslater
【函数功能】listSignUpForTranslater类拷贝构造函数
【参数】const listSignUpForTranslater &myList
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listSignUpForTranslater::listSignUpForTranslater(const
                                                 listSignUpForTranslater
                                                 &myList){
    m_List=myList.m_List;
}

/*************************************************************************
【函数名称】operator =
【函数功能】重载=
【参数】const listSignUpForTranslater& myList
【返回值】listSignUpForTranslater&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listSignUpForTranslater& listSignUpForTranslater::
operator =(const listSignUpForTranslater& myList){
    m_List=myList.m_List;
    return *this;
}

/*************************************************************************
【函数名称】operator =
【函数功能】重载=
【参数】const QList<signUpForTranslater>& myList
【返回值】listSignUpForTranslater&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listSignUpForTranslater& listSignUpForTranslater::
operator =(const QList<signUpForTranslater>& myList){
    m_List=myList;
    return *this;
}

/*************************************************************************
【函数名称】Update
【函数功能】在链表中找到对应的节点并升级信息
【参数】signUpForTranslater myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listSignUpForTranslater::Update(signUpForTranslater myUser){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDThis()==myUser.GetIDThis()){
            m_List[i]=myUser;
        }
    }
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在链表中找到对应的节点并返回所在位置
【参数】signUpForTranslater myTask
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listSignUpForTranslater::SearchInList(signUpForTranslater myUser){
    for(int i=0;i<m_List.size();i++){
        if(myUser.GetIDThis()==m_List[i].GetIDThis()){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】InsertIntoList
【函数功能】向链表中插入新的节点
【参数】signUpForTranslater myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listSignUpForTranslater::InsertIntoList(signUpForTranslater myUser){
    m_List.append(myUser);
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在链表中找到id为iID的节点并返回所在位置
【参数】int iIDTask
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listSignUpForTranslater::SearchInList(int iIDTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDThis()==iIDTask){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】SearchTranslaterForTask
【函数功能】在链表中查询所有报名了myTask任务的用户并返回一个list
【参数】taskLeader myTask
【返回值】QList<signUpForTranslater>
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
QList<signUpForTranslater> listSignUpForTranslater::
SearchTranslaterForTask(taskLeader myUser){
    QList <signUpForTranslater> myLeader;
    for(int i=0;i<m_List.size();i++){
        if(myUser.GetID()==m_List[i].GetIDTask()){
            myLeader.append(m_List[i]);
        }
    }
    return myLeader;
}

/*************************************************************************
【函数名称】Delete
【函数功能】删除所有关于id为iIDTask的报名信息
【参数】int iIDTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listSignUpForTranslater::Delete(int iIDTask){
    for(int i=m_List.size()-1;i>=0;i--){
        if(m_List[i].GetIDTask()==iIDTask){
            m_List.removeAt(i);
        }
    }
}

/*************************************************************************
【函数名称】UserExists
【函数功能】判断Id为iIDUser的用户是否已经报名了id为iIDTask的任务
【参数】QString iIDUser, int iIDTask
【返回值】bool
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
bool listSignUpForTranslater::UserExists(QString iIDUser, int iIDTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==iIDUser&&m_List[i].GetIDTask()==iIDTask){
            return true;
        }
    }
    return false;
}
