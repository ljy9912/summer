#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>

class Message
{
public:
    Message();

private:
    int m_iID;
    QString m_content;
    QString m_title;
    int m_iIDUser;
};

#endif // MESSAGE_H
