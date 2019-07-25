#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>

class Message
{
public:
    Message();
    Message(int iNum);
    ~Message();
    Message(const Message& myMessage);
    Message& operator =(const Message& myMessage);
    int GetID();
    QString GetContent();
    QString GetTitle();
    int GetUser();
    int GetFlag();

    void EditID(int iID);
    void EditContent(QString newContent);
    void EditTitle(QString newTitle);
    void EditUser(int newUser);
    void EditFlag(int newFlag);

    void AttachIDToMessage(int iID);

private:
    int m_iID;
    QString m_content;
    QString m_title;
    int m_iIDUser;
    int m_iFlag;

};

#endif // MESSAGE_H
