#include "signupfortranslater.h"
#include <QSqlQuery>

signUpForTranslater::signUpForTranslater()
{

}

/*************************************************************************
【函数名称】GetIDTask
【函数功能】读入idtask
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
signUpForTranslater::signUpForTranslater(const signUpForTranslater& newTranslater):user(newTranslater),
    m_iIdTask(newTranslater.m_iIdTask),m_iIDThis(newTranslater.m_iIDThis)
{

}

/*************************************************************************
【函数名称】GetIDTask
【函数功能】读入idtask
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
signUpForTranslater::signUpForTranslater(user& myUser,int newIDTask,int newIDThis):user(myUser)
{
    m_iIdTask=newIDTask;
    m_iIDThis=newIDThis;
}

/*************************************************************************
【函数名称】GetIDTask
【函数功能】读入idtask
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
signUpForTranslater::~signUpForTranslater(){

}

/*************************************************************************
【函数名称】GetIDTask
【函数功能】读入idtask
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
signUpForTranslater::operator =(const signUpForTranslater& newTranslater){
    user::operator =(newTranslater);
    m_iIdTask=newTranslater.m_iIdTask;
    m_iIDThis=newTranslater.m_iIDThis;
}

/*************************************************************************
【函数名称】GetIDTask
【函数功能】读入idtask
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void signUpForTranslater::attachIDToUser(int ID){
    QSqlQuery query;
    m_iIDThis=ID;
    query.prepare("select * from signupfortranslaters where idthis=?");
    query.addBindValue(m_iIDThis);
    query.exec();
    if(query.first()){
        m_iID=query.value(0).toInt();
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

/*************************************************************************
【函数名称】GetIDTask
【函数功能】读入idtask
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void signUpForTranslater::EditIDTask(int idtask){
    m_iIdTask=idtask;
}
void signUpForTranslater::EditIDThis(int idTask){
    m_iIDThis=idTask;
}

/*************************************************************************
【函数名称】GetIDTask
【函数功能】读入idtask
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
int signUpForTranslater::GetIDTask(){
    return m_iIdTask;
}
int signUpForTranslater::GetIDThis(){
    return m_iIDThis;
}
