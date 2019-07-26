#ifndef LISTMESSAGE_H
#define LISTMESSAGE_H
#include <QList>
#include "message.h"

class listMessage
{
public:
    listMessage();
    listMessage(const listMessage& myMessage);
    ~listMessage();
    listMessage& operator=(const listMessage& myMessage);
    QList <Message> SearchMessageforUser(QString idUser);

    QList<Message> m_List;
};

#endif // LISTMESSAGE_H
