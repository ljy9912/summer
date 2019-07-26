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
