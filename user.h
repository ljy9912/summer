#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>

class user{
private:

protected:
    int m_iID;
    QString m_Name;
    QString m_PhoneNum;
    QString m_IDNum;
    QString m_English;
    int m_iRewrdPoint;
    double m_dMoney;
    QString m_Passwrd;


public:
    user();
    user(const user& myNewUser);
    virtual ~user();
    user& operator = (const user& myNewUser);

    int GetID();
    QString GetName();
    QString GetPhoneNum();
    QString GetIDNum();
    QString GetEnglish();
    QString GetPassWrd();
    int GetRewrdPoint();
    double GetMoney();

    void EditID(int iID);
    void EditName(QString NewName);
    void EditPhoneNum(QString NewPhoneNum);
    void EditIDNum(QString NewIDNum);
    void EditPassWrd(QString NewPassWrd);
    void EditEnglish(QString NewEnglish);
    void EditMoney(double dNewMoney);
    void EditRewrdPoint(int iNewRewrdPoint);
    void AddMoney(double dAdd);
    void AddPoint(int iNewPoint);

    void attachIDToUser(int iID,QList<user> UserList);
    void attachIDToUser(int iID);
    bool userWithPasswrd(int iID,QString dPasswrd);

};

#endif // USER_H
