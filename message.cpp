#include "message.h"
#include <QSqlQuery>
#include <QList>

/*************************************************************************
【函数名称】on_myTaskBtn_clicked
【函数功能】 在按下myTaskBtn点击之后，打开translaterTask页面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
Message::Message()
{
    m_iFlag=0;
    m_iID=0;
    m_IDUser="";
    m_content="";
    m_title="";
}

/*************************************************************************
【函数名称】on_myTaskBtn_clicked
【函数功能】 在按下myTaskBtn点击之后，打开translaterTask页面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
Message::Message(int iNum){
    m_iID=iNum;
    m_iFlag=0;
    m_IDUser="";
    m_content="";
    m_title="";
}

Message::~Message(){

}

/*************************************************************************
【函数名称】on_myTaskBtn_clicked
【函数功能】 在按下myTaskBtn点击之后，打开translaterTask页面
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
Message::Message(const Message &myMessage){
    m_iID=myMessage.m_iID;
    m_title=myMessage.m_title;
    m_content=myMessage.m_content;
    m_IDUser=myMessage.m_IDUser;
    m_iFlag=myMessage.m_iFlag;
}

Message& Message::operator =(const Message &myMessage){
    m_iID=myMessage.m_iID;
    m_title=myMessage.m_title;
    m_content=myMessage.m_content;
    m_IDUser=myMessage.m_IDUser;
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

QString Message::GetUser(){
    return m_IDUser;
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

void Message::EditUser(QString newUser){
    m_IDUser=newUser;
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
        m_IDUser=query.value(3).toString();
        m_iFlag=query.value(4).toInt();
    }
}
