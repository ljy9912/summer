#include "signUp.h"
#include <QSqlQuery>

signUp::signUp()
{

}

signUp::signUp(const signUp& newLeader):user(newLeader),
    m_iIdTask(newLeader.m_iIdTask)
{

}

signUp::signUp(user& myUser,int newIDTask):user(myUser)
{
    m_iIdTask=newIDTask;
}

signUp::~signUp(){

}

signUp::operator =(const signUp& newLeader){

    m_iIdTask=newLeader.m_iIdTask;
}

void signUp::attachIDToUser(int ID){
    QSqlQuery query;
    m_iID=ID;
    query.prepare("select * from signUps where id=?");
    query.addBindValue(m_iID);
    query.exec();
    if(query.first()){
        m_Name=query.value(1).toString();
        m_PhoneNum=query.value(2).toString();
        m_IDNum=query.value(3).toString();
        m_Passwrd=query.value(4).toString();
        m_English=query.value(5).toString();
        m_iRewrdPoint=query.value(6).toInt();
        m_dMoney=query.value(7).toInt();
        m_iIdTask=query.value(8).toInt();
    }
}

void signUp::EditIDTask(int idtask){
    m_iIdTask=idtask;
}

int signUp::GetIDTask(){
    return m_iIdTask;
}
