#include "messagebackup.h"
#include "message.h"
#include <QList>
#include <QString>

MessageBackUp::MessageBackUp()
{

}

void MessageBackUp::SignUpForLeader(int iID,QList<Message>& MessageList,QString PublisherName
                                    ,QString intro){
    m_message.EditID(MessageList.size());
    m_message.EditTitle("报名负责人成功！");
    m_message.EditContent(tr("您刚才报名了%1发布的%2任务，请耐心等待发布者审核与选择！").arg(PublisherName).
                          arg(intro));
    m_message.EditUser(iID);
    MessageList.append(m_message);
}

void MessageBackUp::TaskPublish(int iID, QString intro,QList<Message>& MessageList){
     m_message.EditID(MessageList.size());
    m_message.EditTitle("创建新任务成功！");
    m_message.EditContent(tr("您刚才创建了%1新任务，负责人正在火热报名中，记得在负责人报名截止时选择负责人噢！").arg(intro));
    m_message.EditUser(iID);
}
