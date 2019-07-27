#include "signupfortranslater.h"
#include <QSqlQuery>

signUpForTranslater::signUpForTranslater()
{

}

/*************************************************************************
【函数名称】signUpForTranslater
【函数功能】类的拷贝构造函数
【参数】const signUpForTranslater& newTranslater
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
signUpForTranslater::signUpForTranslater(const signUpForTranslater& newTranslater):user(newTranslater),
    m_iIdTask(newTranslater.m_iIdTask),m_iIDThis(newTranslater.m_iIDThis)
{

}

/*************************************************************************
【函数名称】signUpForTranslater
【函数功能】类的有参数的构造函数
【参数】user& myUser,int newIDTask,int newIDThis
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
signUpForTranslater::signUpForTranslater(user& myUser,int newIDTask,int newIDThis):user(myUser)
{
    m_iIdTask=newIDTask;
    m_iIDThis=newIDThis;
}

/*************************************************************************
【函数名称】~signUpForTranslater
【函数功能】类的析构函数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
signUpForTranslater::~signUpForTranslater(){

}

/*************************************************************************
【函数名称】operator =
【函数功能】重载“=”
【参数】const signUpForTranslater& newTranslater
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
signUpForTranslater& signUpForTranslater::operator =(const signUpForTranslater& newTranslater){
    user::operator =(newTranslater);
    m_iIdTask=newTranslater.m_iIdTask;
    m_iIDThis=newTranslater.m_iIDThis;
    return *this;
}

/*************************************************************************
【函数名称】attachIDToUser
【函数功能】通过id和数据库的数据初始化类的对象
【参数】int ID
【返回值】 无
【开发者及日期】李佳芸 2019.7.17
【更改记录】
*************************************************************************/
void signUpForTranslater::attachIDToUser(int ID){
    QSqlQuery query;
    m_iIDThis=ID;
    query.prepare("select * from signupfortranslaters where idthis=?");
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
【函数功能】外部修改m_IdTask
【参数】int idtask
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void signUpForTranslater::EditIDTask(int idtask){
    m_iIdTask=idtask;
}

/*************************************************************************
【函数名称】EditIDThis
【函数功能】外部修改idthis
【参数】int idtask
【返回值】 无
【开发者及日期】李佳芸 2019.7.23
【更改记录】
*************************************************************************/
void signUpForTranslater::EditIDThis(int idTask){
    m_iIDThis=idTask;
}

/*************************************************************************
【函数名称】GetIDTask
【函数功能】读入idtask
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
int signUpForTranslater::GetIDTask(){
    return m_iIdTask;
}

/*************************************************************************
【函数名称】GetIDThis
【函数功能】读入m_iIDThis
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
int signUpForTranslater::GetIDThis(){
    return m_iIDThis;
}
