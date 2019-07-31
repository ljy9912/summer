#include "listtaskpublisher.h"

listTaskPublisher::listTaskPublisher()
{

}

listTaskPublisher::~listTaskPublisher(){

}

/*************************************************************************
【函数名称】listTaskPublisher
【函数功能】listTaskPublisher类拷贝构造函数
【参数】const listTaskPublisher &myList
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listTaskPublisher::listTaskPublisher(const listTaskPublisher &myList){
    m_List=myList.m_List;
}

/*************************************************************************
【函数名称】operator =
【函数功能】=重载
【参数】const listTaskPublisher& myList
【返回值】listTaskPublisher&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listTaskPublisher& listTaskPublisher::
operator =(const listTaskPublisher& myList){
    m_List=myList.m_List;
    return *this;
}

/*************************************************************************
【函数名称】operator =
【函数功能】重载=
【参数】const QList<taskPublisher>& myList
【返回值】listTaskPublisher&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listTaskPublisher& listTaskPublisher::
operator =(const QList<taskPublisher>& myList){
    m_List=myList;
    return *this;
}

/*************************************************************************
【函数名称】Update
【函数功能】在链表中查找myTask对应的节点并升级信息
【参数】taskPublisher myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listTaskPublisher::Update(taskPublisher myTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==myTask.GetID()){
            m_List[i]=myTask;
        }
    }
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在链表中查找myTask所在位置并返回其位置
【参数】taskPublisher myTask
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listTaskPublisher::SearchInList(taskPublisher myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetID()==m_List[i].GetID()){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】InsertIntoList
【函数功能】将myTask插入链表中
【参数】taskPublisher myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listTaskPublisher::InsertIntoList(taskPublisher myTask){
    m_List.append(myTask);
}

/*************************************************************************
【函数名称】SearchInList
【函数功能】在链表中查找id为iIDTask的节点并返回所在位置
【参数】int iIDTask
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listTaskPublisher::SearchInList(int iIDTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==iIDTask){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】SearchTaskForPublisher
【函数功能】在链表中查找所有myUser用户发布的任务并返回一个list
【参数】user myUser
【返回值】QList<taskPublisher>
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
QList<taskPublisher> listTaskPublisher::
SearchTaskForPublisher(user myUser){
    QList<taskPublisher> publisherTask;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetPublisher()==myUser.GetID()){
            publisherTask.append(m_List[i]);
        }
    }
    return publisherTask;
}

/*************************************************************************
【函数名称】Delete
【函数功能】删除与id为iIDTask相关的链表中的所有任务信息
【参数】int iIDTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listTaskPublisher::Delete(int iIDTask){
    for(int i=m_List.size()-1;i>=0;i--){
        if(m_List[i].GetID()==iIDTask){
            m_List.removeAt(i);
        }
    }
}

/*************************************************************************
【函数名称】GetID
【函数功能】返回扩充链表的下一个主键编号
【参数】无
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listTaskPublisher::GetID(){
    int lastID;
    if(m_List.isEmpty()){
        lastID=0;
    }
    else{
        lastID=m_List.last().GetID()+1;
    }
    return lastID;
}
