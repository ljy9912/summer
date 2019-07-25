#include "message.h"
#include <QSqlQuery>
#include <QList>

Message::Message()
{
    m_iFlag=0;
    m_iID=0;
    m_iIDUser=0;
}

Message::Message(int iNum){
    m_iID=iNum;
    m_iFlag=0;
    m_iIDUser=0;
}

Message::~Message(){

}

Message::Message(const Message &myMessage){
    m_iID=myMessage.m_iID;
    m_title=myMessage.m_title;
    m_content=myMessage.m_content;
    m_iIDUser=myMessage.m_iIDUser;
    m_iFlag=myMessage.m_iFlag;
}

Message& Message::operator =(const Message &myMessage){
    m_iID=myMessage.m_iID;
    m_title=myMessage.m_title;
    m_content=myMessage.m_content;
    m_iIDUser=myMessage.m_iIDUser;
    m_iFlag=myMessage.m_iFlag;
    return *this;
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

int Message::GetFlag(){
    return m_iFlag;
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

void Message::EditFlag(int newFlag){
    m_iFlag=newFlag;
}

void Message::AttachIDToMessage(int iID){
    QSqlQuery query;
    m_iID=iID;
    query.prepare("select * from message where id=?");
    query.addBindValue(m_iID);
    query.exec();
    if(query.first()){
        m_title=query.value(1).toString();
        m_content=query.value(2).toString();
        m_iIDUser=query.value(3).toInt();
        m_iFlag=query.value(4).toInt();
    }
}
