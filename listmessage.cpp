#include "listmessage.h"

listMessage::listMessage()
{

}

listMessage::~listMessage(){

}

/*************************************************************************
【函数名称】listMessage
【函数功能】listMessage类拷贝构造函数
【参数】const listMessage &myMessage
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listMessage::listMessage(const listMessage &myMessage){
    m_List=myMessage.m_List;
}

/*************************************************************************
【函数名称】operator =
【函数功能】=重载形式1
【参数】const listMessage& myMessage
【返回值】listMessage&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listMessage& listMessage::operator =(const listMessage& myMessage){
    m_List=myMessage.m_List;
    return *this;
}

/*************************************************************************
【函数名称】operator =
【函数功能】=重载
【参数】const QList<Message>& myMessage
【返回值】listMessage&
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
listMessage& listMessage::operator =(const QList<Message>& myMessage){
    m_List=myMessage;
    return *this;
}

/*************************************************************************
【函数名称】SearchMessageforUser
【函数功能】在message的list中寻找发给id为iduser的消息并生成一个List返回
【参数】QString Text
【返回值】QList<Message>
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
QList<Message> listMessage::SearchMessageforUser(QString idUser){
    QList<Message> myMessage;
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetUser()==idUser){
            myMessage.append(m_List[i]);
        }
    }
    return myMessage;
}

/*************************************************************************
【函数名称】Delete
【函数功能】删除id为iID的消息
【参数】int iID
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listMessage::Delete(int iID){
    for(int i=0;i<m_List.size();i++){
        if(m_List[i].GetID()==iID){
            m_List.removeAt(i);
        }
    }
}

/*************************************************************************
【函数名称】GetID
【函数功能】返回扩充List的时应该设定的唯一编号，即为表中最后一位的编号+1
【参数】无
【返回值】int
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
int listMessage::GetID(){
    if(m_List.isEmpty()){
        return 0;
    }
    else{
        return m_List.last().GetID()+1;
    }
}

/*************************************************************************
【函数名称】Update
【函数功能】将myMessage在表中找到对应并升级信息
【参数】Message myMessage
【返回值】 无
【开发者及日期】李佳芸 2019.7.25
【更改记录】
*************************************************************************/
void listMessage::Update(Message myMessage){
    for(int i=0;i<m_List.size();i++){
        if(myMessage.GetID()==m_List[i].GetID()){
            m_List[i]=myMessage;
            break;
        }
    }
}
