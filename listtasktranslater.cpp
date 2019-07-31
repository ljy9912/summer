#include "listtasktranslater.h"
#include "tasktranslater.h"
#include "user.h"

listTaskTranslater::listTaskTranslater()
{

}

listTaskTranslater::~listTaskTranslater(){

}

/*************************************************************************
【函数名称】listTaskTranslater
【函数功能】listTaskTranslater类的拷贝构造函数
【参数】const listTaskTranslater &myList
【返回值】无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listTaskTranslater::listTaskTranslater(const listTaskTranslater &myList){
    m_List=myList.m_List;
}

/*************************************************************************
【函数名称】operator =
【函数功能】重载=
【参数】const listTaskTranslater& myList
【返回值】listTaskTranslater&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listTaskTranslater& listTaskTranslater::
operator =(const listTaskTranslater& myList){
    m_List=myList.m_List;
    return *this;
}

/*************************************************************************
【函数名称】GetIDoperator =
【函数功能】重载=
【参数】const QList<taskTranslater>& myList
【返回值】listTaskTranslater&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listTaskTranslater& listTaskTranslater::
operator =(const QList<taskTranslater>& myList){
    m_List=myList;
    return *this;
}

/*************************************************************************
【函数名称】Update
【函数功能】在list中查找myTask所在的节点并更新该节点的信息
【参数】taskTranslater myTask
【返回值】无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listTaskTranslater::Update(taskTranslater myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetID()==m_List[i].GetID()){
            m_List[i]=myTask;
        }
    }
}

/*************************************************************************
【函数名称】InsertIntoList
【函数功能】将myTask插入list中
【参数】taskTranslater myTask
【返回值】无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listTaskTranslater::InsertIntoList(taskTranslater myTask){
    m_List.append(myTask);
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在表中查询myTask的节点并返回其所在位置
【参数】taskTranslater myTask
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listTaskTranslater::SearchInList(taskTranslater myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetID()==m_List[i].GetID()){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在链表中查询id为iID的节点并返回其所在位置
【参数】int iID
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listTaskTranslater::SearchInList(int iID){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==iID){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】SearchTaskForTranslater_flag0
【函数功能】在list中查找所有母任务编号为idTask且任务状态为0的任务
【参数】int idTask
【返回值】QList<taskTranslater>
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
QList<taskTranslater> listTaskTranslater::
SearchTaskForTranslater_flag0(int idTask){
    QList <taskTranslater> translaterTask;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDTask()==idTask&&m_List[i].GetFlagToLeader()==0){
            translaterTask.append(m_List[i]);
        }
    }
    return translaterTask;
}

/*************************************************************************
【函数名称】SearchTaskForTranslater
【函数功能】在list中查找所有id为idTask的用户的任务并返回一个list
【参数】int idTask
【返回值】QList<taskTranslater>
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
QList<taskTranslater> listTaskTranslater::
SearchTaskForTranslater(int idTask){
    QList <taskTranslater> translaterTask;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDTask()==idTask){
            translaterTask.append(m_List[i]);
        }
    }
    return translaterTask;
}

/*************************************************************************
【函数名称】SearchTaskForTranslater
【函数功能】在List中查找myUser为译者的所有任务并返回一个List
【参数】user myUser
【返回值】QList<taskTranslater>
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
QList<taskTranslater> listTaskTranslater::
SearchTaskForTranslater(user myUser){
    QList <taskTranslater> translaterTask;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetTranslater()==myUser.GetID()){
            translaterTask.append(m_List[i]);
        }
    }
    return translaterTask;
}

/*************************************************************************
【函数名称】Delete
【函数功能】删除母任务id为iIDTask的所有子任务
【参数】int iIDTask
【返回值】无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listTaskTranslater::Delete(int iIDTask){
    for(int i=m_List.size()-1;i>=0;i--){
        if(m_List[i].GetIDTask()==iIDTask){
            m_List.removeAt(i);
        }
    }
}

/*************************************************************************
【函数名称】GetSize_301
【函数功能】返回母任务id为iID且任务状态为1或3的所有任务的数量
【参数】int iID
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listTaskTranslater::GetSize_301(int iID){
    int iNum=0;
    for(int j=0;j<m_List.size();j++){
        if(m_List[j].GetIDTask()==iID
                &&(m_List[j].GetFlagToLeader()==1||
                   (m_List[j].GetFlagToLeader())==3)){
            iNum++;
        }
    }
    return iNum;
}

/*************************************************************************
【函数名称】TaskLeaderAppend
【函数功能】将myLeader中的有效信息提取放入myTask中并将myTask存入List
【参数】taskLeader myLeader,taskTranslater myTask
【返回值】无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listTaskTranslater::
TaskLeaderAppend(taskLeader myLeader,taskTranslater myTask){
    myTask.EditIDTask(myLeader.GetID());
    myTask.EditTaskClass(myLeader.GetTaskClass());
    myTask.EditTitle(myLeader.GetTitle());
    myTask.EditIntroduction(myLeader.GetIntroduction());
    myTask.EditTime(myLeader.GetTime());
    myTask.EditStartYear(myLeader.GetStartYear());
    myTask.EditStartMonth(myLeader.GetStartMonth());
    myTask.EditStartDay(myLeader.GetStartDay());
    myTask.EditMoney(myLeader.GetMoney());
    myTask.EditPublisher(myLeader.GetPublisher());
    myTask.EditLeader(myLeader.GetLeader());
    m_List.append(myTask);
}

/*************************************************************************
【函数名称】GetID
【函数功能】返回扩充链表的下一个主键编号
【参数】无
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listTaskTranslater::GetID(){
    int iID;
    //整合：生成id
    if(m_List.isEmpty()){
        iID=0;
    }
    else{
        iID=m_List.last().GetID()+1;
    }
    return iID;
}

/*************************************************************************
【函数名称】SearchTaskForTranslater_flag13
【函数功能】在list中查找所有母任务编号为iIDTask且任务状态为1或3的任务
【参数】int iIDTask
【返回值】QList<taskTranslater>
【开发者及日期】李佳芸 2019.7.30
【更改记录】
*************************************************************************/
QList<taskTranslater> listTaskTranslater::
SearchTaskForTranslater_flag13(int iIDTask){
    QList<taskTranslater> translaterTaskList;
    for(int j=0;j<m_List.size();j++){
        if(m_List[j].GetIDTask()==iIDTask
                &&(m_List[j].GetFlagToLeader()==1||
                   m_List[j].GetFlagToLeader()==3)){
            translaterTaskList.append(m_List[j]);
        }
    }
    return translaterTaskList;
}
