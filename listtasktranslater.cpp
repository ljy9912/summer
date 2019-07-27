#include "listtasktranslater.h"
#include "tasktranslater.h"
#include "user.h"

listTaskTranslater::listTaskTranslater()
{

}

listTaskTranslater::~listTaskTranslater(){

}

listTaskTranslater::listTaskTranslater(const listTaskTranslater &myList){
    m_List=myList.m_List;
}

listTaskTranslater& listTaskTranslater::operator =(const listTaskTranslater& myList){
    m_List=myList.m_List;
    return *this;
}

listTaskTranslater& listTaskTranslater::operator =(const QList<taskTranslater>& myList){
    m_List=myList;
    return *this;
}

void listTaskTranslater::Update(taskTranslater myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetID()==m_List[i].GetID()){
            m_List[i]=myTask;
        }
    }
}

void listTaskTranslater::InsertIntoList(taskTranslater myTask){
    m_List.append(myTask);
}

int listTaskTranslater::SearchInList(taskTranslater myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetID()==m_List[i].GetID()){
            return i;
        }
    }
}

int listTaskTranslater::SearchInList(int iID){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==iID){
            return i;
        }
    }
}

QList<taskTranslater> listTaskTranslater::SearchTaskForTranslater_flag0(int idTask){
    QList <taskTranslater> translaterTask;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDTask()==idTask&&m_List[i].GetFlagToLeader()==0){
            translaterTask.append(m_List[i]);
        }
    }
    return translaterTask;
}

QList<taskTranslater> listTaskTranslater::SearchTaskForTranslater(int idTask){
    QList <taskTranslater> translaterTask;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDTask()==idTask){
            translaterTask.append(m_List[i]);
        }
    }
    return translaterTask;
}

QList<taskTranslater> listTaskTranslater::SearchTaskForTranslater(user myUser){
    QList <taskTranslater> translaterTask;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetTranslater()==myUser.GetID()){
            translaterTask.append(m_List[i]);
        }
    }
    return translaterTask;
}

void listTaskTranslater::Delete(int iIDTask){
    for(int i=m_List.size()-1;i>=0;i--){
        if(m_List[i].GetIDTask()==iIDTask){
            m_List.removeAt(i);
        }
    }
}

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

void listTaskTranslater::TaskLeaderAppend(taskLeader myLeader,taskTranslater myTask){
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
