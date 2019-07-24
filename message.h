#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>

class Message
{
public:
    Message();
    int GetID();
    QString GetContent();
    QString GetTitle();
    int GetUser();

    void EditID(int iID);
    void EditContent(QString newContent);
    void EditTitle(QString newTitle);
    void EditUser(int newUser);

private:
    int m_iID;
    QString m_content;
    QString m_title;
    int m_iIDUser;


};

#endif // MESSAGE_H
