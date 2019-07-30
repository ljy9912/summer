#include "listtaskleader.h"

listTaskLeader::listTaskLeader()
{

}

listTaskLeader::~listTaskLeader(){

}

listTaskLeader::listTaskLeader(const listTaskLeader &myList){
    m_List=myList.m_List;
}

listTaskLeader& listTaskLeader::operator =(const listTaskLeader& myList){
    m_List=myList.m_List;
    return *this;
}

listTaskLeader& listTaskLeader::operator =(const QList<taskLeader>& myList){
    m_List=myList;
    return *this;
}

void listTaskLeader::Update(taskLeader myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetID()==m_List[i].GetID()){
            m_List[i]=myTask;
        }
    }
}

void listTaskLeader::InsertIntoList(taskLeader myTask){
    m_List.append(myTask);
}

int listTaskLeader::SearchInList(taskLeader myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetID()==m_List[i].GetID()){
            return i;
        }
    }
}

int listTaskLeader::SearchInList(int iID){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==iID){
            return i;
        }
    }
}

QList<taskLeader> listTaskLeader::SearchTaskForLeader(user myUser){
    QList <taskLeader> leaderTask;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetLeader()==myUser.GetID()){
            leaderTask.append(m_List[i]);
        }
    }
    return leaderTask;
}

QList<taskLeader> listTaskLeader::SearchTaskForChecker(user myUser){
    QList<taskLeader> leaderTask;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetChecker()==myUser.GetID()){
            leaderTask.append(m_List[i]);
        }
    }
    return leaderTask;
}
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

void listTaskLeader::Delete(int iIDTask){
    for(int i=m_List.size()-1;i>=0;i--){
        if(m_List[i].GetID()==iIDTask){
            m_List.removeAt(i);
        }
    }
}
