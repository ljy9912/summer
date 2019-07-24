#ifndef MESSAGEBACKUP_H
#define MESSAGEBACKUP_H
#include <QString>
#include "message.h"

class MessageBackUp
{
public:
    MessageBackUp();

public slots:
    void SignUpForLeader(int iID);
    void TaskPublish(int iID,QString intro);

private:
    Message m_message;
};

#endif // MESSAGEBACKUP_H
