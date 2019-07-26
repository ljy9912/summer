#include "listsignupforleader.h".h"

listSignUpForLeader::listSignUpForLeader()
{

}

listSignUpForLeader::~listSignUpForLeader(){

}

listSignUpForLeader::listSignUpForLeader(const listSignUpForLeader &myList){
    m_List=myList.m_List;
}

listSignUpForLeader& listSignUpForLeader::operator =(const listSignUpForLeader& myList){
    m_List=myList.m_List;
}

void listSignUpForLeader::Update(signUpForLeader myTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDThis()==myTask.GetIDThis()){
            m_List[i]=myTask;
        }
    }
}

int listSignUpForLeader::SearchInList(signUpForLeader myTask){
    for(int i=0;i<m_List.size();i++){
        if(myTask.GetIDThis()==m_List[i].GetIDThis()){
            return i;
        }
    }
}

void listSignUpForLeader::InsertIntoList(signUpForLeader myTask){
    m_List.append(myTask);
}

int listSignUpForLeader::SearchInList(int iIDTask){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetIDThis()==iIDTask){
            return i;
        }
    }
}

void listSignUpForLeader::Delete(int iIDTask){
    for(int i=m_List.size()-1;i>=0;i--){
        if(m_List[i].GetIDTask()==iIDTask){
            m_List.removeAt(i);
        }
    }
}
