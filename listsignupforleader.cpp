#include "listsignupforleader.h"

listSignUpForLeader::listSignUpForLeader()
{

}

listSignUpForLeader::~listSignUpForLeader(){

}

/*************************************************************************
【函数名称】listSignUpForLeader
【函数功能】该类的拷贝构造函数
【参数】const listSignUpForLeader &myList
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listSignUpForLeader::listSignUpForLeader(const listSignUpForLeader
                                         &myList){
    m_List=myList.m_List;
}

/*************************************************************************
【函数名称】operator =
【函数功能】=重载
【参数】const listSignUpForLeader& myList
【返回值】listSignUpForLeader&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listSignUpForLeader& listSignUpForLeader::operator =(const
                                                     listSignUpForLeader&
                                                     myList){
    m_List=myList.m_List;
    return *this;
}

/*************************************************************************
【函数名称】operator =
【函数功能】=重载
【参数】const QList<signUpForLeader>& myList
【返回值】listSignUpForLeader&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listSignUpForLeader& listSignUpForLeader::operator =(
        const QList<signUpForLeader>& myList){
    m_List=myList;
    return *this;
}

/*************************************************************************
【函数名称】Update
【函数功能】将myTask在表中找到对应并升级信息
【参数】signUpForLeader myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listSignUpForLeader::Update(signUpForLeader myTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDThis()==myTask.GetIDThis()){
            m_List[i]=myTask;
        }
    }
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在链表中寻找myTask对象并且返回其所在位置
【参数】signUpForLeader myTask
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listSignUpForLeader::SearchInList(signUpForLeader myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetIDThis()==m_List[i].GetIDThis()){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】InsertIntoList
【函数功能】向链表中插入myTask对象
【参数】signUpForLeader myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listSignUpForLeader::InsertIntoList(signUpForLeader myTask){
    m_List.append(myTask);
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在链表中寻找id为iID的对象并且返回其所在位置
【参数】int iIDTask
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listSignUpForLeader::SearchInList(int iIDTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDThis()==iIDTask){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】Delete
【函数功能】删除idtask为iIDTask的所有节点
【参数】int iIDTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listSignUpForLeader::Delete(int iIDTask){
    for(int i=m_List.size()-1;i>=0;i--){
        if(m_List[i].GetIDTask()==iIDTask){
            m_List.removeAt(i);
        }
    }
}

/*************************************************************************
【函数名称】SearchLeaderForTask
【函数功能】在表中搜索所有idtask为myTaskid的对象并且组成一个链表返回
【参数】int myTaskid
【返回值】QList<signUpForLeader>
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
QList<signUpForLeader> listSignUpForLeader::SearchLeaderForTask(int
                                                                myTaskid){
    QList<signUpForLeader> myList;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDTask()==myTaskid){
            myList.append(m_List[i]);
        }
    }
    return myList;
}

/*************************************************************************
【函数名称】UserExists
【函数功能】判断id为iIDUser的用户是否报名过id为iIDTask的任务
【参数】QString iIDUser, int iIDTask
【返回值】bool
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
bool listSignUpForLeader::UserExists(QString iIDUser, int iIDTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==iIDUser&&m_List[i].GetIDTask()==iIDTask){
            return true;
        }
    }
    return false;
}
