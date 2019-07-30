#include "listsignupforchecker.h"

listSignUpForChecker::listSignUpForChecker()
{

}

listSignUpForChecker::~listSignUpForChecker(){

}

/*************************************************************************
【函数名称】listSignUpForChecker
【函数功能】listSignUpForChecker类拷贝构造函数
【参数】const listSignUpForChecker &myList
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listSignUpForChecker::listSignUpForChecker(const listSignUpForChecker &myList){
    m_List=myList.m_List;
}

/*************************************************************************
【函数名称】operator =
【函数功能】=重载
【参数】const listSignUpForChecker& myList
【返回值】listSignUpForChecker&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listSignUpForChecker& listSignUpForChecker::operator =
(const listSignUpForChecker& myList){
    m_List=myList.m_List;
    return *this;
}

/*************************************************************************
【函数名称】operator =
【函数功能】=重载运算符
【参数】const QList<signUpForChecker>& myList
【返回值】listSignUpForChecker&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listSignUpForChecker& listSignUpForChecker::operator =
(const QList<signUpForChecker>& myList){
    m_List=myList;
    return *this;
}

/*************************************************************************
【函数名称】Update
【函数功能】将myTask在表中找到对应并升级信息
【参数】signUpForChecker myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listSignUpForChecker::Update(signUpForChecker myTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDThis()==myTask.GetIDThis()){
            m_List[i]=myTask;
        }
    }
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在list中寻找myTask并返回所在的Int位置
【参数】signUpForChecker myTask
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listSignUpForChecker::SearchInList(signUpForChecker myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetIDThis()==m_List[i].GetIDThis()){
            return i;
        }
    }
}

/*************************************************************************
【函数名称】InsertIntoList
【函数功能】将myTask插入List中
【参数】signUpForChecker myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listSignUpForChecker::InsertIntoList(signUpForChecker myTask){
    m_List.append(myTask);
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在list中查找id为iIDTask的对象并返回所在位置int
【参数】int iIDTask
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listSignUpForChecker::SearchInList(int iIDTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDThis()==iIDTask){
            return i;
        }
    }
}

/*************************************************************************
【函数名称】Delete
【函数功能】删除idtask为iIDTask的对象
【参数】int iIDTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listSignUpForChecker::Delete(int iIDTask){
    for(int i=m_List.size()-1;i>=0;i--){
        if(m_List[i].GetIDTask()==iIDTask){
            m_List.removeAt(i);
        }
    }
}

/*************************************************************************
【函数名称】UserExists
【函数功能】判断user在list中是否存在
【参数】QString iIDUser, int iIDTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
bool listSignUpForChecker::UserExists(QString iIDUser, int iIDTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==iIDUser&&m_List[i].GetIDTask()==iIDTask){
            return true;
        }
    }
    return false;
}

/*************************************************************************
【函数名称】SearchCheckerForTask
【函数功能】在list中寻找id为myTaskid的对象并返回一个list
【参数】int myTaskid
【返回值】QList<signUpForChecker> listSignUpForChecker
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
QList<signUpForChecker> listSignUpForChecker::SearchCheckerForTask(int myTaskid){
    QList<signUpForChecker> myList;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDTask()==myTaskid){
            myList.append(m_List[i]);
        }
    }
    return myList;
}
