#include "signupforleader.h"
#include <QSqlQuery>

signUpForLeader::signUpForLeader():user()
{
    m_iIdTask=0;
    m_iIdTask=0;
}

/*************************************************************************
【函数名称】signUpForLeader
【函数功能】signUpForLeader类的构造函数
【参数】const signUpForLeader& newLeader
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
signUpForLeader::signUpForLeader(const signUpForLeader& newLeader):user(newLeader),
    m_iIdTask(newLeader.m_iIdTask),m_iIDThis(newLeader.m_iIDThis)
{

}

/*************************************************************************
【函数名称】signUpForLeader
【函数功能】signUpForLeader类的复制构造函数
【参数】user& myUser,int newIDTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
signUpForLeader::signUpForLeader(user& myUser,int newIDTask,int newIDThis):user(myUser)
{
    m_iIdTask=newIDTask;
    m_iIDThis=newIDThis;
}

/*************************************************************************
【函数名称】~signUpForLeader
【函数功能】析构函数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
signUpForLeader::~signUpForLeader(){

}

/*************************************************************************
【函数名称】operator =
【函数功能】= 重载函数
【参数】const signUpForLeader& newLeader
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
signUpForLeader& signUpForLeader::operator =(const signUpForLeader& newLeader){
    user::operator =(newLeader);
    m_iIdTask=newLeader.m_iIdTask;
    m_iIDThis=newLeader.m_iIDThis;
    return *this;
}

/*************************************************************************
【函数名称】attachIDToUser
【函数功能】通过id对一个对象初始化
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
void signUpForLeader::attachIDToUser(int ID){
    QSqlQuery query;
    m_iIDThis=ID;
    query.prepare("select * from signupforleaders where idthis=?");
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
        m_iIdTask=query.value(7).toInt();
    }
}

/*************************************************************************
【函数名称】EditIDTask
【函数功能】外部修改task的id
【参数】int idtask
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
void signUpForLeader::EditIDTask(int idtask){
    m_iIdTask=idtask;
}

/*************************************************************************
【函数名称】EditIDThis
【函数功能】外部修改task的idthis
【参数】int id
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
void signUpForLeader::EditIDThis(int id){
    m_iIDThis=id;
}

/*************************************************************************
【函数名称】GetIDTask
【函数功能】读入idtask
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
int signUpForLeader::GetIDTask(){
    return m_iIdTask;
}

/*************************************************************************
【函数名称】GetIDThis
【函数功能】外部修改task的id
【参数】int idtask
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
int signUpForLeader::GetIDThis(){
    return m_iIDThis;
}
