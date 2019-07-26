#include "listtaskpublisher.h"

listTaskPublisher::listTaskPublisher()
{

}

listTaskPublisher::~listTaskPublisher(){

}

listTaskPublisher::listTaskPublisher(const listTaskPublisher &myList){
    m_List=myList.m_List;
}

listTaskPublisher& listTaskPublisher::operator =(const listTaskPublisher& myList){
    m_List=myList.m_List;
}

void listTaskPublisher::Update(taskPublisher myTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==myTask.GetID()){
            m_List[i]=myTask;
        }
    }
}

int listTaskPublisher::SearchInList(taskPublisher myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetID()==m_List[i].GetID()){
            return i;
        }
    }
}

void listTaskPublisher::InsertIntoList(taskPublisher myTask){
    m_List.append(myTask);
}

int listTaskPublisher::SearchInList(int iIDTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==iIDTask){
            return i;
        }
    }
}

QList<taskPublisher> listTaskPublisher::SearchTaskForPublisher(user myUser){
    QList<taskPublisher> publisherTask;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetPublisher()==myUser.GetID()){
            publisherTask.append(m_List[i]);
        }
    }
    return publisherTask;
}

void listTaskPublisher::Delete(int iIDTask){
    for(int i=m_List.size()-1;i>=0;i--){
        if(m_List[i].GetID()==iIDTask){
            m_List.removeAt(i);
        }
    }
}
