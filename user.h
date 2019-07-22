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

    void attachIDToUser(int iID);
    int GetID();
    QString GetName();
    QString GetPhoneNum();
    QString GetIDNum();
    QString GetEnglish();
    QString GetPassWrd();
    int GetRewrdPoint();
    double GetMoney();

    void EditID(int iID);
    void EditName(QString sNewName);
    void EditPhoneNum(QString sNewPhoneNum);
    void EditIDNum(QString sNewIDNum);
    void EditPassWrd(QString sNewPassWrd);
    void EditEnglish(QString sNewEnglish);
    void EditMoney(int sNewMoney);
    void EditRewrdPoint(double sNewRewrdPoint);

    bool userWithPasswrd(int iID,QString dPasswrd);

};

#endif // USER_H
