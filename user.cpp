#include "user.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QList>

/*************************************************************************
【函数名称】user
【函数功能】user类的默认构造函数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
user::user(){
    m_iID=0;
    m_iRewrdPoint=100;
    m_dMoney=0;
}

user::user(const user& myNewUser){
    m_iID=myNewUser.m_iID;
    m_Name=myNewUser.m_Name;
    m_PhoneNum=myNewUser.m_PhoneNum;
    m_IDNum=myNewUser.m_IDNum;
    m_Passwrd=myNewUser.m_Passwrd;
    m_English=myNewUser.m_English;
    m_iRewrdPoint=myNewUser.m_iRewrdPoint;
    m_dMoney=myNewUser.m_dMoney;
}

/*************************************************************************
【函数名称】~user
【函数功能】user类的默认析构函数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
user::~user(){

}

user& user::operator = (const user& myNewUser){
    m_iID=myNewUser.m_iID;
    m_Name=myNewUser.m_Name;
    m_PhoneNum=myNewUser.m_PhoneNum;
    m_IDNum=myNewUser.m_IDNum;
    m_Passwrd=myNewUser.m_Passwrd;
    m_English=myNewUser.m_English;
    m_iRewrdPoint=myNewUser.m_iRewrdPoint;
    m_dMoney=myNewUser.m_dMoney;
    return *this;
}

/*************************************************************************
【函数名称】Get**
【函数功能】返回类内的private参数
【参数】无
【返回值】**
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
int user::GetID(){
    return m_iID;
}
QString user::GetName(){
    return m_Name;
}
QString user::GetPhoneNum(){
    return m_PhoneNum;
}
QString user::GetIDNum(){
    return m_IDNum;
}
QString user::GetPassWrd(){
    return m_Passwrd;
}

QString user::GetEnglish(){
    return m_English;
}
int user::GetRewrdPoint(){
    return m_iRewrdPoint;
}
double user::GetMoney(){
    return m_dMoney;
}

/*************************************************************************
【函数名称】Edit**
【函数功能】 更改类内private的参数
【参数】**
【返回值】 无
【开发者及日期】李佳芸 2019.7.12
【更改记录】
*************************************************************************/
void user::EditID(int iid){
    m_iID=iid;
}

void user::EditName(QString newName){
    m_Name=newName;
}
void user::EditPhoneNum(QString newPhoneNum){
    m_PhoneNum=newPhoneNum;
}
void user::EditIDNum(QString newIDNum){
    m_IDNum=newIDNum;
}
void user::EditPassWrd(QString newPassWrd){
    m_Passwrd=newPassWrd;
}
void user::EditEnglish(QString newEnglish){
    m_English=newEnglish;
}
void user::EditMoney(int iNewMoney){
    m_dMoney=iNewMoney;
}
void user::EditRewrdPoint(double dNewRewrdPoint){
    m_iRewrdPoint=dNewRewrdPoint;
}

/*************************************************************************
【函数名称】attachIDToUser
【函数功能】将task的对象根据m_iID初始化
【参数】int ID
【返回值】 无
【开发者及日期】李佳芸 2019.7.13
【更改记录】
*************************************************************************/
void user::attachIDToUser(int iID){
    QSqlQuery query;
    m_iID=iID;
    query.prepare("select * from users where id=?");
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
    }
}

bool user::userWithPasswrd(int iInputId,QString inputPasswrd){
    if(m_iID==iInputId&&m_Passwrd==inputPasswrd){
        return true;
    }
    else{
        return false;
    }
}


