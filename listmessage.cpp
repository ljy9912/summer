#include "listmessage.h"

listMessage::listMessage()
{

}

listMessage::~listMessage(){

}

listMessage::listMessage(const listMessage &myMessage){
    m_List=myMessage.m_List;
}

listMessage& listMessage::operator =(const listMessage& myMessage){
    m_List=myMessage.m_List;
    return *this;
}

listMessage& listMessage::operator =(const QList<Message>& myMessage){
    m_List=myMessage;
    return *this;
}

QList<Message> listMessage::SearchMessageforUser(QString idUser){
    QList<Message> myMessage;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetUser()==idUser){
            myMessage.append(m_List[i]);
        }
    }
    return myMessage;
}

void listMessage::Delete(int iID){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==iID){
            m_List.removeAt(i);
        }
    }
}

int listMessage::GetID(){
    if(m_List.isEmpty()){
        return 0;
    }
    else{
        return m_List.last().GetID()+1;
    }
}

void listMessage::Update(Message myMessage){
    for(int i=0;i<m_List.size();i++){
        if(myMessage.GetID()==m_List[i].GetID()){
            m_List[i]=myMessage;
            break;
        }
    }
}
