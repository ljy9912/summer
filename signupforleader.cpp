#include "signupforleader.h"
#include <QSqlQuery>

signUpForLeader::signUpForLeader()
{

}

signUpForLeader::signUpForLeader(const signUpForLeader& newLeader):user(newLeader),
    m_iIdTask(newLeader.m_iIdTask)
{

}

signUpForLeader::signUpForLeader(user& myUser,int newIDTask):user(myUser)
{
    m_iIdTask=newIDTask;
}

signUpForLeader::~signUpForLeader(){

}

signUpForLeader::operator =(const signUpForLeader& newLeader){

    m_iIdTask=newLeader.m_iIdTask;
}

void signUpForLeader::attachIDToUser(int ID){
    QSqlQuery query;
    m_iID=ID;
    query.prepare("select * from signupforleaders where id=?");
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

void signUpForLeader::EditIDTask(int idtask){
    m_iIdTask=idtask;
}

int signUpForLeader::GetIDTask(){
    return m_iIdTask;
}
