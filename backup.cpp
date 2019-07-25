#include "backup.h"
#include "message.h"
#include <QList>
#include <QString>
#include <QDate>
#include "list.h"

BackUp::BackUp()
{

}

BackUp::BackUp(const BackUp& myBackUp):m_List(myBackUp.m_List),m_User(myBackUp.m_User){

}

BackUp::~BackUp(){

}

BackUp& BackUp::operator =(const BackUp& myBackUp){
    m_List=myBackUp.m_List;
    m_User=myBackUp.m_User;
    return *this;
}

void BackUp::SignUpForLeader(int iID,int idTask){
    Message myMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    myMessage.EditTitle("报名负责人成功！");
    int iNum=m_List.searchTaskInList(idTask);
    myMessage.EditContent(QObject::tr("您刚才报名了%1翻译任务的负责人，请耐心等待发布者审核与选择！").arg(m_List.TaskPublisher[iNum].GetIntroduction()));
    myMessage.EditUser(iID);
    m_List.message.append(myMessage);
}

void BackUp::TaskPublish(int iID, QString intro){
    Message myMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    myMessage.EditTitle("创建新任务成功！");
    myMessage.EditContent(QObject::tr("您刚才创建了%1新任务，负责人正在火热报名中，记得在负责人报名截止时选择负责人噢！").arg(intro));
    myMessage.EditUser(iID);
}

void BackUp::CheckDateSnupfrLeader(){
    for(int i=0;i<m_List.TaskPublisher.size();i++){
        QDate date1(m_List.TaskPublisher[i].GetLeaderYear(),m_List.TaskPublisher[i].GetLeaderMonth(),
                    m_List.TaskPublisher[i].GetLeaderDay());
        QDate currentdate;
        currentdate=QDate::currentDate();
        if(date1<currentdate){
            Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
            newMessage.EditTitle("负责人报名结束了");
            newMessage.EditContent(QObject::tr("负责人报名已于%1年%2月%3日结束，快点击“我是发布者”选择负责人吧！").
                                   arg(m_List.TaskPublisher[i].GetLeaderYear())
                                   .arg(m_List.TaskPublisher[i].GetLeaderMonth())
                                   .arg(m_List.TaskPublisher[i].GetLeaderDay()));
            newMessage.EditUser(m_List.TaskPublisher[i].GetPublisher());
            m_List.message.append(newMessage);
        }
        m_List.TaskPublisher[i].EditFlag(102);
    }
}

void BackUp::CheckDateSnupfrTranslater(){
    for(int i=0;i<m_List.TaskLeader.size();i++){
        QDate date1(m_List.TaskLeader[i].GetTranslaterYear(),m_List.TaskLeader[i].GetTranslaterMonth(),
                    m_List.TaskLeader[i].GetTranslaterDay());
        QDate currentdate;
        currentdate=QDate::currentDate();
        if(date1<currentdate){
            Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
            newMessage.EditTitle("译者报名结束了");
            newMessage.EditContent(QObject::tr("译者报名已于%1年%2月%3日结束，快点击“我是负责人”选择译者并分配任务吧！").
                                   arg(m_List.TaskLeader[i].GetTranslaterYear())
                                   .arg(m_List.TaskLeader[i].GetTranslaterMonth())
                                   .arg(m_List.TaskLeader[i].GetTranslaterDay()));
            newMessage.EditUser(m_List.TaskLeader[i].GetLeader());
            m_List.message.append(newMessage);
        }
        m_List.TaskLeader[i].EditFlag(203);
    }
}

void BackUp::SelectLeaderDone(int iPublisherID, user myLeader, QString intro){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("选择负责人成功！");
    newMessage.EditContent(QObject::tr("您成功为任务%1选择负责人%2,请耐心等待负责人和译者翻译任务吧！")
                          .arg(intro).arg(myLeader.GetName()));
    newMessage.EditUser(iPublisherID);
    m_List.message.append(newMessage);
    newMessage.EditID(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("恭喜成功当选负责人！");
    newMessage.EditContent(QObject::tr("恭喜您被选为任务%1的负责人！快点击“我是负责人”设定译者报名结束日期开始招募译者吧！")
                          .arg(intro));
    newMessage.EditUser(myLeader.GetID());
    m_List.message.append(newMessage);
}

void BackUp::SetTranslaterDone(int iLeaderID){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("成功设定译者报名截止日期");
    newMessage.EditContent(QObject::tr("您刚才成功设定了%1任务译者报名截止日期，译者正在火热报名中，记得在译者报名截止时选择译者并分配任务噢！"));
    newMessage.EditUser(iLeaderID);
    m_List.message.append(newMessage);
}

void BackUp::SignUpForTranslaterDone(int iID, QString intro){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("报名翻译任务成功！");
    newMessage.EditContent(QObject::tr("您刚才报名了%1任务，请耐心等待负责人审核与分配任务！").arg(intro));
    newMessage.EditUser(iID);
    m_List.message.append(newMessage);
}

void BackUp::SelectTranslaterDone_Leader(int iLeaderID, QString intro){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("选择译者，分配任务成功！");
    newMessage.EditContent(QObject::tr("您刚才进行了%1任务的选择译者与分配任务的工作，翻译任务已经火热开始，记得适时"
                                       "登陆查看译者提交的译文并进行评价噢！").arg(intro));
    newMessage.EditUser(iLeaderID);
    m_List.message.append(newMessage);
}

void BackUp::SelectTranslaterDone_Translater(QString intro,int iTranslaterID){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("恭喜被选为译者！");
    newMessage.EditContent(QObject::tr("恭喜您被选为任务%1的译者！快点击“我是译者”查看您的翻译任务并开始翻译吧！").arg(intro));
    newMessage.EditUser(iTranslaterID);
    m_List.message.append(newMessage);
}

void BackUp::SubmitResultDone_Translater(QString intro, int iTranslaterID){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("提交译文成功！");
    newMessage.EditContent(QObject::tr("您翻译的任务%1提交译文成功！请耐心等待负责人的评价吧！").arg(intro));
    newMessage.EditUser(iTranslaterID);
    m_List.message.append(newMessage);
}

void BackUp::SubmitResultDone_Leader(QString intro, int iTranslaterID, int iLeaderID){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("有译者提交译文啦！");
    newMessage.EditContent(QObject::tr("译者%1刚刚提交了任务%2的译文，快点击“我是负责人”查看译文并进行评价吧！").arg(iTranslaterID).arg(intro));
    newMessage.EditUser(iLeaderID);
    m_List.message.append(newMessage);
}

void BackUp::SubmitCommentDone_Leader(QString intro, int iLeaderID,int iTranslaterID){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("提交评价成功！");
    newMessage.EditContent(QObject::tr("您提交了任务%1的译者%2的评价，请耐心等待译者的修改吧！").
                           arg(intro).arg(iTranslaterID));
    newMessage.EditUser(iLeaderID);
    m_List.message.append(newMessage);
}

void BackUp::SubmitCommentDone_Translater(QString intro, int iTranslaterID){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("负责人有新的评价啦！");
    newMessage.EditContent(QObject::tr("您翻译的任务%1有新的评价啦，快点击“我是译者”查看评价并修改吧！").arg(intro));
    newMessage.EditUser(iTranslaterID);
    m_List.message.append(newMessage);
}

void BackUp::EndTranslateDone_Leader(QString intro, int iTranslaterID, int iLeaderID){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("译文收稿成功！");
    newMessage.EditContent(QObject::tr("您负责的任务%1的译者%2的译文收稿成功！请继续和其它译者一起努力吧！").arg(intro)
                           .arg(iTranslaterID));
    newMessage.EditUser(iLeaderID);
    m_List.message.append(newMessage);

}

void BackUp::EndTranslateDone_Translater(QString intro, int iTranslaterID){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("恭喜您的译文已经通过！");
    newMessage.EditContent(QObject::tr("您翻译的任务%1的译文已经通过！请耐心等待发布者分配酬金吧！").arg(intro));
    newMessage.EditUser(iTranslaterID);
    m_List.message.append(newMessage);
}

void BackUp::StartIntegrate(QString intro, int iLeaderID){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("可以整合译文了！");
    newMessage.EditContent(QObject::tr("您负责的任务%1的译文已经全部通过！快点击“我是负责人”整合译文吧！").arg(intro));
    newMessage.EditUser(iLeaderID);
    m_List.message.append(newMessage);
}

void BackUp::IntegratingDone_Leader(QString intro, int iLeaderID){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("译文提交成功！");
    newMessage.EditContent(QObject::tr("您负责的任务%1的译文提交成功！请耐心等待发布者审核并分配酬金吧！").arg(intro));
    newMessage.EditUser(iLeaderID);
    m_List.message.append(newMessage);
}

void BackUp::IntegratingDone_Publisher(QString intro, int iPublisherID){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("负责人提交译文啦！");
    newMessage.EditContent(QObject::tr("您发布的任务%1的译文已经提交！快点击“我是发布者”验收并分配酬金吧！").arg(intro));
    newMessage.EditUser(iPublisherID);
    m_List.message.append(newMessage);
}

void BackUp::DistributeMoney_Publisher(QString intro, int iPublisherID, double dMyMoney){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("分配酬金成功！");
    newMessage.EditContent(QObject::tr("您发布的任务%1的酬金分配完毕，共支付%2元，请注意账户余额变动。").arg(intro).arg(dMyMoney));
    newMessage.EditUser(iPublisherID);
    m_List.message.append(newMessage);
}

void BackUp::DistributeMoney_Translater(QString intro, double dMyMoney, int iLeaderID){
    Message newMessage(m_List.message[m_List.message.size()-1].GetID()+1);
    newMessage.EditTitle("酬金到账啦！");
    newMessage.EditContent(QObject::tr("您参与翻译的任务%1的酬金%2元已到账，请注意查收！").arg(dMyMoney));
    m_List.message.append(iLeaderID);
}
