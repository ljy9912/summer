#include "backup.h"
#include "message.h"
#include <QList>
#include <QString>
#include <QDate>

BackUp::BackUp()
{

}

BackUp::BackUp(const BackUp& myBackUp):m_User(myBackUp.m_User),m_listMessage(myBackUp.m_listMessage),
    m_listSignUpForLeader(myBackUp.m_listSignUpForLeader),m_listSignUpForTranslater(myBackUp.m_listSignUpForTranslater),
    m_listTaskPublisher(myBackUp.m_listTaskPublisher),m_listTaskLeader(myBackUp.m_listTaskLeader),
    m_listTaskTranslater(myBackUp.m_listTaskTranslater),m_listUser(myBackUp.m_listUser){

}

BackUp::~BackUp(){

}

BackUp& BackUp::operator =(const BackUp& myBackUp){
    m_listMessage=myBackUp.m_listMessage.m_List;
    m_listSignUpForLeader=myBackUp.m_listSignUpForLeader.m_List;
    m_listSignUpForTranslater=myBackUp.m_listSignUpForTranslater.m_List;
    m_listTaskLeader=myBackUp.m_listTaskLeader.m_List;
    m_listTaskPublisher=myBackUp.m_listTaskPublisher.m_List;
    m_listTaskTranslater=myBackUp.m_listTaskTranslater.m_List;
    m_listUser=myBackUp.m_listUser.m_List;
    m_User=myBackUp.m_User;
    return *this;
}

void BackUp::SignUpForLeader(QString ID,int idTask){
    QDateTime time=QDateTime::currentDateTime();
    Message myMessage(m_listMessage.m_List.last().GetID()+1);
    myMessage.EditTitle("报名负责人成功！");
    int iNum=m_listTaskPublisher.SearchInList(idTask);
    myMessage.EditContent(QObject::tr("%1\n您刚才报名了%2翻译任务的负责人，请耐心等待发布者审核与选择！")
                          .arg(time.toString())
                          .arg(m_listTaskPublisher.m_List[iNum].GetTitle()));
    myMessage.EditUser(ID);
    m_listMessage.m_List.append(myMessage);
}

void BackUp::TaskPublish(QString ID, QString intro){
    QDateTime time=QDateTime::currentDateTime();
    Message myMessage;
    if(m_listMessage.m_List.isEmpty()){
        myMessage.EditID(0);
    }
    else{
        myMessage.EditID(m_listMessage.m_List.last().GetID()+1);
    }
    myMessage.EditTitle("创建新任务成功！");
    myMessage.EditContent(QObject::tr("%1\n您刚才创建了%2新任务，负责人正在火热报名中，记得在负责人报名截止时选择负责人噢！").arg(time.toString()).arg(intro));
    myMessage.EditUser(ID);
    m_listMessage.m_List.append(myMessage);
}

void BackUp::CheckDateSnupfrLeader(){
    QDateTime time=QDateTime::currentDateTime();
    for(int i=0;i<m_listTaskPublisher.m_List.size();i++){
        QDate date1(m_listTaskPublisher.m_List[i].GetLeaderYear(),m_listTaskPublisher.m_List[i].GetLeaderMonth(),
                    m_listTaskPublisher.m_List[i].GetLeaderDay());
        QDate currentdate;
        currentdate=QDate::currentDate();
        if(date1<currentdate&&m_listTaskPublisher.m_List[i].GetFlag()==101){
            Message newMessage(m_listMessage.m_List.last().GetID()+1);
            newMessage.EditTitle("负责人报名结束了");
            newMessage.EditContent(QObject::tr("%4\n负责人报名已于%1年%2月%3日结束，快点击“我是发布者”选择负责人吧！").
                                   arg(m_listTaskPublisher.m_List[i].GetLeaderYear())
                                   .arg(m_listTaskPublisher.m_List[i].GetLeaderMonth())
                                   .arg(m_listTaskPublisher.m_List[i].GetLeaderDay()).arg(time.toString()));
            newMessage.EditUser(m_listTaskPublisher.m_List[i].GetPublisher());
            m_listMessage.m_List.append(newMessage);
            m_listTaskPublisher.m_List[i].EditFlag(102);
        }
    }
}

void BackUp::CheckDateSnupfrTranslater(){
    QDateTime time=QDateTime::currentDateTime();
    for(int i=0;i<m_listTaskLeader.m_List.size();i++){
        QDate date1(m_listTaskLeader.m_List[i].GetTranslaterYear(),m_listTaskLeader.m_List[i].GetTranslaterMonth(),
                    m_listTaskLeader.m_List[i].GetTranslaterDay());
        QDate currentdate;
        currentdate=QDate::currentDate();
        if(date1<currentdate&&m_listTaskLeader.m_List[i].GetFlag()==202){
            Message newMessage(m_listMessage.m_List.last().GetID()+1);
            newMessage.EditTitle("译者报名结束了");
            newMessage.EditContent(QObject::tr("%4\n译者报名已于%1年%2月%3日结束，快点击“我是负责人”选择译者并分配任务吧！").
                                   arg(m_listTaskLeader.m_List[i].GetTranslaterYear())
                                   .arg(m_listTaskLeader.m_List[i].GetTranslaterMonth())
                                   .arg(m_listTaskLeader.m_List[i].GetTranslaterDay()).arg(time.toString()));
            newMessage.EditUser(m_listTaskLeader.m_List[i].GetLeader());
            m_listMessage.m_List.append(newMessage);
            m_listTaskLeader.m_List[i].EditFlag(203);
            int iNum=m_listTaskPublisher.SearchInList(m_listTaskLeader.m_List[i].GetID());
            m_listTaskPublisher.m_List[i].EditFlag(203);
        }
    }
}

void BackUp::SelectLeaderDone(QString PublisherID, QString idLeader, QString intro){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("选择负责人成功！");
    newMessage.EditContent(QObject::tr("%3\n您成功为任务%1选择负责人%2,请耐心等待负责人和译者翻译任务吧！")
                          .arg(intro).arg(idLeader).arg(time.toString()));
    newMessage.EditUser(PublisherID);
    m_listMessage.m_List.append(newMessage);
    newMessage.EditID(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("恭喜成功当选负责人！");
    newMessage.EditContent(QObject::tr("%2\n恭喜您被选为任务%1的负责人！快点击“我是负责人”设定译者报名结束日期开始招募译者吧！")
                          .arg(intro).arg(time.toString()));
    newMessage.EditUser(idLeader);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::SetTranslaterDone(QString LeaderID,QString intro){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("成功设定译者报名截止日期");
    newMessage.EditContent(QObject::tr("%2\n您刚才成功设定了%1任务译者报名截止日期，译者正在火热报名中，记得在译者报名截止时选择译者并分配任务噢！")
                           .arg(intro).arg(time.toString()));
    newMessage.EditUser(LeaderID);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::SignUpForTranslaterDone(QString ID, QString intro){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("报名翻译任务成功！");
    newMessage.EditContent(QObject::tr("%2\n您刚才报名了%1任务，请耐心等待负责人审核与分配任务！").arg(intro)
                           .arg(time.toString()));
    newMessage.EditUser(ID);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::SelectTranslaterDone_Leader(QString LeaderID, QString intro){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("选择译者，分配任务成功！");
    newMessage.EditContent(QObject::tr("%2\n您刚才进行了%1任务的选择译者与分配任务的工作，翻译任务已经火热开始，记得适时"
                                       "登陆查看译者提交的译文并进行评价噢！").arg(intro).arg(time.toString()));
    newMessage.EditUser(LeaderID);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::SelectTranslaterDone_Translater(QString intro,QString TranslaterID){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("恭喜被选为译者！");
    newMessage.EditContent(QObject::tr("%2\n恭喜您被选为任务%1的译者！快点击“我是译者”查看您的翻译任务并开始翻译吧！")
                           .arg(intro).arg(time.toString()));
    newMessage.EditUser(TranslaterID);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::SubmitResultDone_Translater(QString intro, QString TranslaterID){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("提交译文成功！");
    newMessage.EditContent(QObject::tr("%2\n您翻译的任务%1提交译文成功！请耐心等待负责人的评价吧！")
                           .arg(intro).arg(time.toString()));
    newMessage.EditUser(TranslaterID);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::SubmitResultDone_Leader(QString intro, QString TranslaterID, QString LeaderID){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("有译者提交译文啦！");
    newMessage.EditContent(QObject::tr("%3\n译者%1刚刚提交了任务%2的译文，快点击“我是负责人”查看译文并进行评价吧！")
                           .arg(TranslaterID).arg(intro).arg(time.toString()));
    newMessage.EditUser(LeaderID);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::SubmitCommentDone_Leader(QString intro, QString LeaderID,QString TranslaterID){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("提交评价成功！");
    newMessage.EditContent(QObject::tr("%3\n您提交了任务%1的译者%2的评价，请耐心等待译者的修改吧！").
                           arg(intro).arg(TranslaterID).arg(time.toString()));
    newMessage.EditUser(LeaderID);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::SubmitCommentDone_Translater(QString intro, QString TranslaterID){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("负责人有新的评价啦！");
    newMessage.EditContent(QObject::tr("%2\n您翻译的任务%1有新的评价啦，快点击“我是译者”查看评价并修改吧！")
                           .arg(intro).arg(time.toString()));
    newMessage.EditUser(TranslaterID);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::EndTranslateDone_Leader(QString intro, QString TranslaterID, QString LeaderID){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("译文收稿成功！");
    newMessage.EditContent(QObject::tr("%3\n您负责的任务%1的译者%2的译文收稿成功！请继续和其它译者一起努力吧！")
                           .arg(intro).arg(TranslaterID).arg(time.toString()));
    newMessage.EditUser(LeaderID);
    m_listMessage.m_List.append(newMessage);

}

void BackUp::EndTranslateDone_Translater(QString intro, QString TranslaterID){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("恭喜您的译文已经通过！");
    newMessage.EditContent(QObject::tr("%2\n您翻译的任务%1的译文已经通过！请耐心等待发布者分配酬金吧！")
                           .arg(intro).arg(time.toString()));
    newMessage.EditUser(TranslaterID);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::StartIntegrate(QString intro, QString LeaderID){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("可以整合译文了！");
    newMessage.EditContent(QObject::tr("%2\n您负责的任务%1的译文已经全部通过！快点击“我是负责人”整合译文吧！")
                           .arg(intro).arg(time.toString()));
    newMessage.EditUser(LeaderID);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::IntegratingDone_Leader(QString intro, QString LeaderID){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("译文提交成功！");
    newMessage.EditContent(QObject::tr("%2\n您负责的任务%1的译文提交成功！请耐心等待发布者审核并分配酬金吧！")
                           .arg(intro).arg(time.toString()));
    newMessage.EditUser(LeaderID);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::IntegratingDone_Publisher(QString intro, QString PublisherID){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("负责人提交译文啦！");
    newMessage.EditContent(QObject::tr("%2\n您发布的任务%1的译文已经提交！快点击“我是发布者”验收并分配酬金吧！")
                           .arg(intro).arg(time.toString()));
    newMessage.EditUser(PublisherID);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::DistributeMoney_Publisher(QString intro, QString PublisherID, double dMyMoney){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("分配酬金成功！");
    newMessage.EditContent(QObject::tr("%3\n您发布的任务%1的酬金分配完毕，共支付%2元，请注意账户余额变动。")
                           .arg(intro).arg(dMyMoney).arg(time.toString()));
    newMessage.EditUser(PublisherID);
    m_listMessage.m_List.append(newMessage);
}

void BackUp::DistributeMoney_Translater(QString intro, double dMyMoney, QString LeaderID){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.m_List.last().GetID()+1);
    newMessage.EditTitle("酬金到账啦！");
    newMessage.EditContent(QObject::tr("%3\n您参与翻译的任务%1的酬金%2元已到账，请注意查收！")
                           .arg(intro).arg(dMyMoney).arg(time.toString()));
    newMessage.EditUser(LeaderID);
    m_listMessage.m_List.append(newMessage);
}
