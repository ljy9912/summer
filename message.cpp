#include "message.h"

Message::Message()
{

}

int Message::GetID(){
    return m_iID;
}

QString Message::GetContent(){
    return m_content;
}

QString Message::GetTitle(){
    return m_title;
}

int Message::GetUser(){
    return m_iIDUser;
}





void Message::EditID(int iID){
    m_iID=iID;
}

void Message::EditTitle(QString newTitle){
    m_title=newTitle;
}

void Message::EditContent(QString newContent){
    m_content=newContent;
}

void Message::EditUser(int newUser){
    m_iIDUser=newUser;
}

