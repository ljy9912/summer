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

QList<taskTranslater> listTaskTranslater::SearchTaskForTranslater(int idTask){
    QList <taskTranslater> translaterTask;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDTask()==idTask&&m_List[i].GetFlagToLeader()==0){
            translaterTask.append(m_List[i]);
        }
    }
    return translaterTask;
}

QList<taskTranslater> listTaskTranslater::SearchTaskForTranslater_302(int idTask){
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
