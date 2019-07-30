#include "signupforchecker.h"
#include <QSqlQuery>

signUpForChecker::signUpForChecker():user()
{
    m_iIDTask=0;
    m_iIDThis=0;
}

signUpForChecker::signUpForChecker(user& myUser,int newIDTask,int newIDThis):user(myUser)
{
    m_iIDTask=newIDTask;
    m_iIDThis=newIDThis;
}

signUpForChecker::~signUpForChecker(){

}

signUpForChecker::signUpForChecker(const signUpForChecker &myChecker):user(myChecker),
    m_iIDTask(myChecker.m_iIDTask),m_iIDThis(myChecker.m_iIDThis)
{

}

signUpForChecker& signUpForChecker::operator =(const signUpForChecker& myChecker){
    user::operator =(myChecker);
    m_iIDTask=myChecker.m_iIDTask;
    m_iIDThis=myChecker.m_iIDThis;
    return *this;
}


void signUpForChecker::attachIDToUser(int id){
    QSqlQuery query;
    m_iIDThis=id;
    query.prepare("select * from signupforchecker where idthis=?");
    query.addBindValue(m_iIDThis);
    query.exec();
    if(query.first()){
        m_ID=query.value(0).toString();
        m_PhoneNum=query.value(1).toString();
        m_IDNum=query.value(2).toString();
        m_Passwrd=query.value(3).toString();
        m_English=query.value(4).toString();
        m_iRewrdPoint=query.value(5).toInt();
        m_dMoney=query.value(6).toInt();
        m_iIDTask=query.value(7).toInt();
    }
}

void signUpForChecker::EditIDTask(int idtask){
    m_iIDTask=idtask;
}

void signUpForChecker::EditIDThis(int idtask){
    m_iIDThis=idtask;
}

int signUpForChecker::GetIDTask(){
    return m_iIDTask;
}

int signUpForChecker::GetIDThis(){
    return m_iIDThis;
}
