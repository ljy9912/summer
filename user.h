#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>

class user{
private:

protected:
    QString m_ID;
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

    QString GetID();
    QString GetPhoneNum();
    QString GetIDNum();
    QString GetEnglish();
    QString GetPassWrd();
    int GetRewrdPoint();
    double GetMoney();

    void EditID(QString NewID);
    void EditPhoneNum(QString NewPhoneNum);
    void EditIDNum(QString NewIDNum);
    void EditPassWrd(QString NewPassWrd);
    void EditEnglish(QString NewEnglish);
    void EditMoney(double dNewMoney);
    void EditRewrdPoint(int iNewRewrdPoint);
    void AddMoney(double dAdd);
    void AddPoint(int iNewPoint);
    void LoseMoney(double dlose);

    void attachIDToUser(QString iID, QList<user> UserList);
    void attachIDToUser(QString iID);
    bool userWithPasswrd(QString iID, QString dPasswrd);

};

#endif // USER_H
