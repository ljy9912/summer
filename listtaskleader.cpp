#include "listtaskleader.h"

listTaskLeader::listTaskLeader()
{

}

listTaskLeader::~listTaskLeader(){

}

/*************************************************************************
【函数名称】listTaskLeader
【函数功能】listTaskLeader类的拷贝构造函数
【参数】const listTaskLeader &myList
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listTaskLeader::listTaskLeader(const listTaskLeader &myList){
    m_List=myList.m_List;
}

/*************************************************************************
【函数名称】operator =
【函数功能】重载=
【参数】const listTaskLeader& myList
【返回值】listTaskLeader&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listTaskLeader& listTaskLeader::operator =(const listTaskLeader& myList){
    m_List=myList.m_List;
    return *this;
}

/*************************************************************************
【函数名称】operator =
【函数功能】重载=
【参数】const QList<taskLeader>& myList
【返回值】listTaskLeader&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listTaskLeader& listTaskLeader::
operator =(const QList<taskLeader>& myList){
    m_List=myList;
    return *this;
}

/*************************************************************************
【函数名称】Update
【函数功能】taskLeader myTask
【参数】taskLeader myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listTaskLeader::Update(taskLeader myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetID()==m_List[i].GetID()){
            m_List[i]=myTask;
        }
    }
}

/*************************************************************************
【函数名称】InsertIntoList
【函数功能】向链表中插入新的节点
【参数】taskLeader myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listTaskLeader::InsertIntoList(taskLeader myTask){
    m_List.append(myTask);
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在链表中查找mytTask的节点并返回其所在的位置
【参数】taskLeader myTask
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listTaskLeader::SearchInList(taskLeader myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetID()==m_List[i].GetID()){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在链表中查找id为iID的节点并返回其所在位置
【参数】int iID
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listTaskLeader::SearchInList(int iID){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==iID){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】SearchTaskForLeader
【函数功能】在链表中寻找所有myUser是负责人的任务并返回一个List
【参数】user myUser
【返回值】QList<taskLeader>
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
QList<taskLeader> listTaskLeader::SearchTaskForLeader(user myUser){
    QList <taskLeader> leaderTask;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetLeader()==myUser.GetID()){
            leaderTask.append(m_List[i]);
        }
    }
    return leaderTask;
}

/*************************************************************************
【函数名称】SearchTaskForChecker
【函数功能】在链表中寻找所有myUser事审核人的任务并返回一个List
【参数】user myUser
【返回值】QList<taskLeader>
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
QList<taskLeader> listTaskLeader::SearchTaskForChecker(user myUser){
    QList<taskLeader> leaderTask;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetChecker()==myUser.GetID()){
            leaderTask.append(m_List[i]);
        }
    }
    return leaderTask;
}

/*************************************************************************
【函数名称】TaskLeaderAppend
【函数功能】将taskPublisher类型的对象提取相同信息并生成新的taskLeader对象存入list中
【参数】taskPublisher myLeader
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listTaskLeader::TaskLeaderAppend(taskPublisher myLeader){
    taskLeader leader;
    leader.EditID(myLeader.GetID());
    leader.EditIntroduction(myLeader.GetIntroduction());
    leader.EditLeader(myLeader.GetLeader());
    leader.EditFlag(myLeader.GetFlag());
    leader.EditMoney(myLeader.GetMoney());
    leader.EditPublisher(myLeader.GetPublisher());
    leader.EditTask(myLeader.GetTask());
    leader.EditTaskClass(myLeader.GetTaskClass());
    leader.EditTime(myLeader.GetTime());
    leader.EditStartYear(myLeader.GetStartYear());
    leader.EditStartMonth(myLeader.GetStartMonth());
    leader.EditStartDay(myLeader.GetStartDay());
    leader.EditTitle(myLeader.GetTitle());
    leader.EditChecker(myLeader.GetTaskChecker());
    m_List.append(leader);
}

/*************************************************************************
【函数名称】Delete
【函数功能】删除id为iIDTask的节点
【参数】int iIDTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listTaskLeader::Delete(int iIDTask){
    for(int i=m_List.size()-1;i>=0;i--){
        if(m_List[i].GetID()==iIDTask){
            m_List.removeAt(i);
        }
    }
}
