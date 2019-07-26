#include "listsignupfortranslater.h"
#include "tasktranslater.h"

listSignUpForTranslater::listSignUpForTranslater()
{

}

listSignUpForTranslater::~listSignUpForTranslater(){

}

listSignUpForTranslater::listSignUpForTranslater(const listSignUpForTranslater &myList){
    m_List=myList.m_List;
}

listSignUpForTranslater& listSignUpForTranslater::operator =(const listSignUpForTranslater& myList){
    m_List=myList.m_List;
}

void listSignUpForTranslater::Update(signUpForTranslater myTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDThis()==myTask.GetIDThis()){
            m_List[i]=myTask;
        }
    }
}

int listSignUpForTranslater::SearchInList(signUpForTranslater myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetIDThis()==m_List[i].GetIDThis()){
            return i;
        }
    }
}

void listSignUpForTranslater::InsertIntoList(signUpForTranslater myTask){
    m_List.append(myTask);
}

int listSignUpForTranslater::SearchInList(int iIDTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDThis()==iIDTask){
            return i;
        }
    }
}

QList<signUpForTranslater> listSignUpForTranslater::SearchTranslaterForTask(taskLeader myTask){
    QList <signUpForTranslater> myLeader;
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetID()==m_List[i].GetIDTask()){
            myLeader.append(m_List[i]);
        }
    }
    return myLeader;
}

void listSignUpForTranslater::Delete(int iIDTask){
    for(int i=m_List.size()-1;i>=0;i--){
        if(m_List[i].GetIDTask()==iIDTask){
            m_List.removeAt(i);
        }
    }
}
