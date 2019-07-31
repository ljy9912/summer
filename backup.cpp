#include "backup.h"
#include "message.h"
#include <QList>
#include <QString>
#include <QDate>
#include <QTableWidget>

BackUp::BackUp()
{

}

/*************************************************************************
【函数名称】BackUp
【函数功能】BackUp类拷贝构造函数
【参数】const BackUp& myBackUp
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
BackUp::BackUp(const BackUp& myBackUp):m_User(myBackUp.m_User),m_listMessage(myBackUp.m_listMessage),
    m_listSignUpForLeader(myBackUp.m_listSignUpForLeader),m_listSignUpForTranslater(myBackUp.m_listSignUpForTranslater),
    m_listTaskPublisher(myBackUp.m_listTaskPublisher),m_listTaskLeader(myBackUp.m_listTaskLeader),
    m_listTaskTranslater(myBackUp.m_listTaskTranslater),m_listUser(myBackUp.m_listUser),
    m_listSignUpForChecker(myBackUp.m_listSignUpForChecker){

}

/*************************************************************************
【函数名称】~BackUp
【函数功能】BackUp类析构函数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
BackUp::~BackUp(){

}

/*************************************************************************
【函数名称】operator =
【函数功能】=重载
【参数】const BackUp& myBackUp
【返回值】 BackUp&
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
BackUp& BackUp::operator =(const BackUp& myBackUp){
    m_listMessage=myBackUp.m_listMessage.m_List;
    m_listSignUpForLeader=myBackUp.m_listSignUpForLeader.m_List;
    m_listSignUpForTranslater=myBackUp.m_listSignUpForTranslater.m_List;
    m_listTaskLeader=myBackUp.m_listTaskLeader.m_List;
    m_listTaskPublisher=myBackUp.m_listTaskPublisher.m_List;
    m_listTaskTranslater=myBackUp.m_listTaskTranslater.m_List;
    m_listUser=myBackUp.m_listUser.m_List;
    m_User=myBackUp.m_User;
    m_listSignUpForChecker=myBackUp.m_listSignUpForChecker;
    return *this;
}

/*************************************************************************
【函数名称】SignUpForLeader
【函数功能】在用户报名负责人成功后后台向译者发消息并且生成一个报名表中的对象存入报名表中
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::SignUpForLeader(int i){
    int idtask=m_listTaskPublisher.m_List[i].GetID();
    int idthis=m_listSignUpForLeader.m_List.last().GetIDThis()+1;
    signUpForLeader leader(m_User,idtask,idthis);
    m_listSignUpForLeader.m_List.append(leader);
    QDateTime time=QDateTime::currentDateTime();
    Message myMessage(m_listMessage.GetID());
    myMessage.EditTitle("报名负责人成功！");
    int iNum=m_listTaskPublisher.SearchInList(idtask);
    myMessage.EditContent(QObject::tr("%1\n您刚才报名了%2翻译任务的负责人，"
                                      "请耐心等待发布者审核与选择！")
                          .arg(time.toString())
                          .arg(m_listTaskPublisher.
                               m_List[iNum].GetTitle()));
    myMessage.EditUser(m_User.GetID());
    m_listMessage.m_List.append(myMessage);
}

/*************************************************************************
【函数名称】SignUpForChecker
【函数功能】在用户报名审核人之后，生成一个审核人报名对象并插入报名表中
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::SignUpForChecker(int i){
    int idtask=m_listTaskPublisher.m_List[i].GetID();
    int idthis=m_listSignUpForChecker.m_List.last().GetIDThis()+1;
    //生成一个报名的对象
    signUpForChecker leader(m_User,idtask,idthis);
    m_listSignUpForChecker.m_List.append(leader);
    //显示发消息的时间
    QDateTime time=QDateTime::currentDateTime();
    Message myMessage(m_listMessage.GetID());
    myMessage.EditTitle("报名审核人成功！");
    int iNum=m_listTaskPublisher.SearchInList(idtask);
    myMessage.EditContent(QObject::tr("%1\n您刚才报名了%2翻译任务的审核人，"
                                      "请耐心等待发布者审核与选择！")
                          .arg(time.toString())
                          .arg(m_listTaskPublisher
                               .m_List[iNum].GetTitle()));
    myMessage.EditUser(m_User.GetID());
    m_listMessage.m_List.append(myMessage);
}

/*************************************************************************
【函数名称】TaskPublish
【函数功能】用户发布一个任务之后，存入系统发布的时间即为任务的起始时间，并更改任务编号为
101开始招募负责人和审核人
【参数】taskPublisher myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::TaskPublish(taskPublisher myTask){
    myTask.EditFlag(101);
    QDate time=QDate::currentDate();
    myTask.EditStartYear(time.year());
    myTask.EditStartMonth(time.month());
    myTask.EditStartDay(time.day());
    m_listTaskPublisher.Update(myTask);
    //发消息
    Message myMessage(m_listMessage.GetID());
    myMessage.EditTitle("创建新任务成功！");
    myMessage.EditContent(QObject::tr("%1\n您刚才创建了%2新任务，负责人正在火热报名中，"
                                      "记得在负责人报名截止时选择负责人噢！").arg(time.toString()).arg(myTask.GetTitle()));
    myMessage.EditUser(m_User.GetID());
    m_listMessage.m_List.append(myMessage);
}

/*************************************************************************
【函数名称】CheckDateSnupfrLeader
【函数功能】在每次应用启动时检测所有的招募负责人任务是否到规定时间
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::CheckDateSnupfrLeader(){
    QDateTime time=QDateTime::currentDateTime();
    for(int i=0;i<m_listTaskPublisher.m_List.size();i++){
        QDate date1(m_listTaskPublisher.m_List[i].GetLeaderYear()
                    ,m_listTaskPublisher.m_List[i].GetLeaderMonth(),
                    m_listTaskPublisher.m_List[i].GetLeaderDay());
        QDate currentdate;
        currentdate=QDate::currentDate();
        //如果到截止时间，更改任务状态并向发布者发消息提醒选择负责人和审核人
        if(date1<currentdate&&m_listTaskPublisher.m_List[i].GetFlag()==101){
            Message newMessage(m_listMessage.GetID());
            newMessage.EditTitle("负责人报名结束了");
            newMessage.EditContent(QObject::tr("%4\n负责人报名已于%1年%2月%3"
                                               "日结束，快点击"
                                               "“我是发布者”选择负责人吧！").
                                   arg(m_listTaskPublisher.m_List[i]
                                       .GetLeaderYear())
                                   .arg(m_listTaskPublisher.m_List[i]
                                        .GetLeaderMonth())
                                   .arg(m_listTaskPublisher.m_List[i]
                                        .GetLeaderDay())
                                   .arg(time.toString()));
            newMessage.EditUser(m_listTaskPublisher.m_List[i].GetPublisher());
            m_listMessage.m_List.append(newMessage);
            m_listTaskPublisher.m_List[i].EditFlag(102);
        }
    }
}

/*************************************************************************
【函数名称】CheckDateSnupfrTranslater
【函数功能】在每次应用启动的时候检查所有译者的招募任务是否到截止时间
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::CheckDateSnupfrTranslater(){
    QDateTime time=QDateTime::currentDateTime();
    for(int i=0;i<m_listTaskLeader.m_List.size();i++){
        QDate date1(m_listTaskLeader.m_List[i].GetTranslaterYear()
                    ,m_listTaskLeader.m_List[i].GetTranslaterMonth(),
                    m_listTaskLeader.m_List[i].GetTranslaterDay());
        QDate currentdate;
        currentdate=QDate::currentDate();
        //如果到截止时间，发消息提醒负责人选择译者，并更改任务状态
        if(date1<currentdate&&m_listTaskLeader.m_List[i].GetFlag()==202){
            Message newMessage(m_listMessage.GetID());
            newMessage.EditTitle("译者报名结束了");
            newMessage.EditContent(QObject::tr("%4\n译者报名已于%1年%2月%3日"
                                               "结束，快点击“我是负责人"
                                               "”选择译者并分配任务吧！").
                                   arg(m_listTaskLeader.m_List[i]
                                       .GetTranslaterYear())
                                   .arg(m_listTaskLeader.m_List[i]
                                        .GetTranslaterMonth())
                                   .arg(m_listTaskLeader.m_List[i]
                                        .GetTranslaterDay())
                                   .arg(time.toString()));
            newMessage.EditUser(m_listTaskLeader.m_List[i].GetLeader());
            m_listMessage.m_List.append(newMessage);
            m_listTaskLeader.m_List[i].EditFlag(203);
            int iNum=m_listTaskPublisher.SearchInList(m_listTaskLeader.
                                                      m_List[i].GetID());
            m_listTaskPublisher.m_List[iNum].EditFlag(203);
        }
    }
}

/*************************************************************************
【函数名称】SelectLeaderDone
【函数功能】在发布者选择负责人结束时候，修改任务状态并且存储选择的负责人，删除报名表中的其
余信息
【参数】taskPublisher myTask,QString iIdLeader,QString iIDChecker
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::SelectLeaderDone(taskPublisher myTask,QString iIdLeader
                              ,QString iIDChecker){
    int iNumInList=m_listTaskPublisher.SearchInList(myTask);
    m_listTaskPublisher.m_List[iNumInList].EditLeader(iIdLeader);
    m_listTaskPublisher.m_List[iNumInList].EditTaskChecker(iIDChecker);
    m_listTaskPublisher.m_List[iNumInList].EditFlag(201);
    m_listSignUpForLeader.Delete(myTask.GetID());
    myTask.EditLeader(iIdLeader);
    myTask.EditTaskChecker(iIDChecker);
    myTask.EditFlag(201);
    //
    m_listTaskPublisher.Update(myTask);
    m_listTaskLeader.TaskLeaderAppend(myTask);


    //像发布人和负责人发消息提醒
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.GetID());
    newMessage.EditTitle("选择负责人和审核人成功！");
    newMessage.EditContent(QObject::tr("%3\n您成功为任务%1选择负责人%2和审核"
                                       "人%4,请耐心等待负责人和译者翻译任务吧！")
                          .arg(myTask.GetTitle()).arg(iIdLeader)
                           .arg(time.toString()).arg(iIDChecker));
    newMessage.EditUser(myTask.GetPublisher());
    m_listMessage.m_List.append(newMessage);
    newMessage.EditID(m_listMessage.GetID());
    newMessage.EditTitle("恭喜成功当选负责人！");
    newMessage.EditContent(QObject::tr("%2\n恭喜您被选为任务%1的负责人！快点击"
                                       "“我是负责人”设定译者报名结束日期"
                                       "开始招募译者吧！")
                          .arg(myTask.GetTitle()).arg(time.toString()));
    newMessage.EditUser(iIdLeader);
    m_listMessage.m_List.append(newMessage);
    newMessage.EditID(m_listMessage.GetID());
    newMessage.EditTitle("恭喜成功当选审核人！");
    newMessage.EditContent(QObject::tr("%2\n恭喜您被选为任务%1的审核人！请在任务"
                                       "开始后点击“我是审核人”和负责人共同"
                                       "审核译者的译文吧！")
                          .arg(myTask.GetTitle()).arg(time.toString()));
    newMessage.EditUser(iIDChecker);
    m_listMessage.m_List.append(newMessage);
}

/*************************************************************************
【函数名称】SetTranslaterDone
【函数功能】在设定译者招募日期之后，更改任务状态并将填写的日期，并发消息提醒负责人和译者
【参数】taskLeader myLeader,int iTranslaterYear,int iTranslaterMonth
,int iTranslaterDay
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::SetTranslaterDone(taskLeader myLeader,int iTranslaterYear
                               ,int iTranslaterMonth,int iTranslaterDay){

    myLeader.EditTranslaterYear(iTranslaterYear);
    myLeader.EditTranslaterMonth(iTranslaterMonth);
    myLeader.EditTranslaterDay(iTranslaterDay);
    myLeader.EditFlag(202);
    m_listTaskLeader.Update(myLeader);
    int iNumInList=m_listTaskPublisher.SearchInList(myLeader.GetID());
    m_listTaskPublisher.m_List[iNumInList].EditFlag(202);
    //发消息确认
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.GetID());
    newMessage.EditTitle("成功设定译者报名截止日期");
    newMessage.EditContent(QObject::tr("%2\n您刚才成功设定了%1任务"
                                       "译者报名截止日期，译者正在火热报名中，"
                                       "记得在译者报名截止时选择译者并分配任务噢！")
                           .arg(myLeader.GetTitle()).arg(time.toString()));
    newMessage.EditUser(m_User.GetID());
    m_listMessage.m_List.append(newMessage);
}

/*************************************************************************
【函数名称】SignUpForTranslaterDone
【函数功能】在用户报名译者结束之后，发消息确认并且生成一个对象存入报名表中
【参数】int i
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::SignUpForTranslaterDone(int i){
    int idtask=m_listTaskPublisher.m_List[i].GetID();
    int idthis=m_listSignUpForTranslater.m_List.last().GetIDThis()+1;
    signUpForTranslater translater(m_User,idtask,idthis);
    g_backUp.m_listSignUpForTranslater.m_List.append(translater);
    //发消息确认
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.GetID());
    newMessage.EditTitle("报名翻译任务成功！");
    newMessage.EditContent(QObject::tr("%2\n您刚才报名了%1任务，请耐心等待负责人审核与分配任务！")
                           .arg(m_listTaskPublisher.m_List[i].GetTitle())
                           .arg(time.toString()));
    newMessage.EditUser(m_User.GetID());
    m_listMessage.m_List.append(newMessage);
}

/*************************************************************************
【函数名称】SelectTranslaterDone_Leader
【函数功能】负责人选择译者结束并且分配任务结束之后，向负责人发消息确认，并且更改任务状态，
同时删除报名表中所有报名此任务的信息
【参数】taskLeader myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::SelectTranslaterDone_Leader(taskLeader myTask){
    //删除译者报名表中的所有该任务的报名信息
    m_listSignUpForTranslater.Delete(myTask.GetID());
    myTask.EditFlag(301);
    m_listTaskLeader.Update(myTask);

    QDateTime time=QDateTime::currentDateTime();
    //发消息确认
    Message newMessage(m_listMessage.GetID());
    newMessage.EditTitle("选择译者，分配任务成功！");
    newMessage.EditContent(QObject::tr("%2\n您刚才进行了%1任务的选择译者与"
                                       "分配任务的工作，翻译任务已经火热开始，"
                                       "记得适时"
                                       "登陆查看译者提交的译文并进行评价噢！")
                           .arg(myTask.GetTitle())
                           .arg(time.toString()));
    newMessage.EditUser(m_User.GetID());
    m_listMessage.m_List.append(newMessage);
}

/*************************************************************************
【函数名称】SelectTranslaterDone_Translater
【函数功能】在选择译者分配任务结束之后，生成一个译者对象并存进译者任务的表中，并且发消息
提醒译者
【参数】taskLeader Task,signUpForTranslater myTranslater,
int iEndYear,int iEndMonth,int iEndDay,QString newTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::SelectTranslaterDone_Translater(taskLeader Task,signUpForTranslater
                                             myTranslater,
                                             int iEndYear,int iEndMonth,int
                                             iEndDay,QString newTask){
    //生成译者对象
    taskTranslater myTask;
    myTask.EditEndYear(iEndYear);
    myTask.EditEndMonth(iEndMonth);
    myTask.EditEndDay(iEndDay);
    myTask.EditTask(newTask);
    //更改任务状态
    myTask.EditFlag(301);
    myTask.EditTranslater(myTranslater.GetID());
    myTask.EditID(m_listTaskTranslater.GetID());
    m_listTaskTranslater.TaskLeaderAppend(Task,myTask);

    //将译者任务对象插入list中
    m_listTaskTranslater.m_List.append(myTask);
    //发消息确认
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.GetID());
    newMessage.EditTitle("恭喜被选为译者！");
    newMessage.EditContent(QObject::tr("%2\n恭喜您被选为任务%1的译者！"
                                       "快点击“我是译者”查看您的翻译任务并"
                                       "开始翻译吧！")
                           .arg(Task.GetTitle()).arg(time.toString()));
    newMessage.EditUser(myTranslater.GetID());
    m_listMessage.m_List.append(newMessage);
}

/*************************************************************************
【函数名称】SubmitResultDone
【函数功能】在译者提交结果之后，更改译者任务的状态使得此任务对负责人和审核人可见而对译者
不可见，并且发消息向译者确认，并发消息提醒负责人
【参数】taskTranslater myTask, QString myResult
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::SubmitResultDone(taskTranslater myTask, QString myResult){
    //更改任务状态
    myTask.EditResult(myResult);
    if(myTask.GetFlagToLeader()==0){
        myTask.EditFlagToLeader(1);
    }
    else if(myTask.GetFlagToLeader()==2){
        myTask.EditFlagToLeader(3);
    }
    m_listTaskTranslater.Update(myTask);
    //发消息确认
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage1(m_listMessage.GetID());
    newMessage1.EditTitle("提交译文成功！");
    newMessage1.EditContent(QObject::tr("%2\n您翻译的任务%1提交译文成功！"
                                        "请耐心等待负责人的评价吧！")
                           .arg(myTask.GetTitle()).arg(time.toString()));
    newMessage1.EditUser(myTask.GetTranslater());
    m_listMessage.m_List.append(newMessage1);

    Message newMessage2(m_listMessage.GetID());
    newMessage2.EditTitle("有译者提交译文啦！");
    newMessage2.EditContent(QObject::tr("%3\n译者%1刚刚提交了任务%2的译文，"
                                        "快点击“我是负责人”查看译文并进行评价吧！")
                           .arg(myTask.GetTranslater()).arg(myTask.GetTitle())
                            .arg(time.toString()));
    newMessage2.EditUser(myTask.GetLeader());
    m_listMessage.m_List.append(newMessage2);
}


/*************************************************************************
【函数名称】SubmitCommentDone
【函数功能】在译者提交评价成功之后，改变任务状态使之对译者可见而对负责人和审核人不可见，
并且发消息向负责人或审核人确认，提醒译者修改译文
【参数】taskTranslater myTask, QString newComment
【返回值】无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::SubmitCommentDone(taskTranslater myTask, QString newComment){
    //存储译者提交的评价
    myTask.AddComment(newComment);
    myTask.EditCommentEditting(NULL);
    //更改任务状态使得评价在译者处显示
    myTask.EditFlagToLeader(2);
    //将更改的信息写入内存
    m_listTaskTranslater.Update(myTask);

    QDateTime time=QDateTime::currentDateTime();
    Message newMessage1(m_listMessage.GetID());
    newMessage1.EditTitle("提交评价成功！");
    newMessage1.EditContent(QObject::tr("%3\n您提交了任务%1的译者%2的评价，"
                                        "请耐心等待译者的修改吧！").
                           arg(myTask.GetTitle()).arg(myTask.GetTranslater())
                            .arg(time.toString()));
    newMessage1.EditUser(myTask.GetLeader());
    m_listMessage.m_List.append(newMessage1);
    Message newMessage2(m_listMessage.GetID());
    newMessage2.EditTitle("负责人有新的评价啦！");
    newMessage2.EditContent(QObject::tr("%2\n您翻译的任务%1有新的评价啦，"
                                        "快点击“我是译者”查看评价并修改吧！")
                           .arg(myTask.GetTitle()).arg(time.toString()));
    newMessage2.EditUser(myTask.GetTranslater());
    m_listMessage.m_List.append(newMessage2);
}

/*************************************************************************
【函数名称】EndTranslateDone_Leader
【函数功能】在负责人对某位译者收稿之后，更改该子任务的状态并且发消息向负责人确认
【参数】QString intro, QString TranslaterID, QString LeaderID
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::EndTranslateDone_Leader(QString intro, QString TranslaterID,
                                     QString LeaderID){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.GetID());
    newMessage.EditTitle("译文收稿成功！");
    newMessage.EditContent(QObject::tr("%3\n您负责的任务%1的译者%2的译文收稿成功！"
                                       "请继续和其它译者一起努力吧！")
                           .arg(intro).arg(TranslaterID).arg(time.toString()));
    newMessage.EditUser(LeaderID);
    m_listMessage.m_List.append(newMessage);

}

/*************************************************************************
【函数名称】EndTranslateDone_Translater
【函数功能】在负责人对此译者收稿之后，发消息向译者通知，并更改任务状态，检测是否所有译者
均已收稿，如果是，发消息提醒发布者可以整合译文了
【参数】taskLeader myTaskLeader, taskTranslater myTaskTranslater
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::EndTranslateDone_Translater(taskLeader myTaskLeader,
                                         taskTranslater myTaskTranslater){
    myTaskTranslater.EditFlagToLeader(5);
    m_listTaskTranslater.Update(myTaskTranslater);
    //发送信息告诉译者任务通过，不用修改，等酬金
    //检测是否所有任务都已经通过
    int flag=1;
    for(int t=0;t<m_listTaskTranslater.m_List.size();t++){
        if(m_listTaskTranslater.m_List[t].GetIDTask()==
                myTaskTranslater.GetIDTask()){
            if(m_listTaskTranslater.m_List[t].GetFlagToLeader()!=5){
                flag=0;
            }
        }
    }
    if(flag==1){
        //如果所有译文都已经通过，更改任务状态为译者整合译文
        myTaskLeader.EditFlag(302);
        //将更改的信息写入内存
        m_listTaskLeader.Update(myTaskLeader);
        //向负责人发送可以整合译文的信息
        StartIntegrate(myTaskLeader.GetTitle(),myTaskLeader.GetLeader());
    }
    else{
        //向负责人发送信息
        EndTranslateDone_Leader(myTaskLeader.GetTitle()
                                         ,myTaskTranslater.GetTranslater()
                                         ,myTaskLeader.GetLeader());
    }

    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.GetID());
    newMessage.EditTitle("恭喜您的译文已经通过！");
    newMessage.EditContent(QObject::tr("%2\n您翻译的任务%1的译文已经通过！"
                                       "请耐心等待发布者分配酬金吧！")
                           .arg(myTaskLeader.GetTitle()).arg(time.toString()));
    newMessage.EditUser(myTaskTranslater.GetTranslater());
    m_listMessage.m_List.append(newMessage);
}

/*************************************************************************
【函数名称】StartIntegrate
【函数功能】向负责人发消息提醒可以开始整合译文
【参数】QString intro, QString LeaderID
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::StartIntegrate(QString intro, QString LeaderID){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.GetID());
    newMessage.EditTitle("可以整合译文了！");
    newMessage.EditContent(QObject::tr("%2\n您负责的任务%1的译文已经全部通过！"
                                       "快点击“我是负责人”整合译文吧！")
                           .arg(intro).arg(time.toString()));
    newMessage.EditUser(LeaderID);
    m_listMessage.m_List.append(newMessage);
}

/*************************************************************************
【函数名称】IntegratingDone
【函数功能】在负责人整合译文之后，发消息向负责人确认并且发消息提醒发布者可以确认任务，
修改任务状态
【参数】taskLeader myTask, QString newResult
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::IntegratingDone(taskLeader myTask, QString newResult){
    myTask.EditResult(newResult);
    //更改任务状态为发布者确认任务，存储信息
    myTask.EditFlag(401);
    m_listTaskLeader.Update(myTask);
    int iNum=m_listTaskPublisher.SearchInList(myTask.GetID());
    m_listTaskPublisher.m_List[iNum].EditFlag(401);
    //发消息向负责人确认
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage1(m_listMessage.GetID());
    newMessage1.EditTitle("译文提交成功！");
    newMessage1.EditContent(QObject::tr("%2\n您负责的任务%1的译文提交成功！"
                                        "请耐心等待发布者审核并分配酬金吧！")
                           .arg(myTask.GetTitle()).arg(time.toString()));
    newMessage1.EditUser(myTask.GetLeader());
    m_listMessage.m_List.append(newMessage1);
    //发消息提醒发布者
    Message newMessage2(m_listMessage.GetID());
    newMessage2.EditTitle("负责人提交译文啦！");
    newMessage2.EditContent(QObject::tr("%2\n您发布的任务%1的译文已经提交！"
                                        "快点击“我是发布者”验收并分配酬金吧！")
                           .arg(myTask.GetTitle()).arg(time.toString()));
    newMessage2.EditUser(myTask.GetPublisher());
    m_listMessage.m_List.append(newMessage2);
}

/*************************************************************************
【函数名称】DistributeMoney_Publisher
【函数功能】在发布者分配酬金结束之后，向发布者发消息确认并且更改任务状态，删除表中的相关数据，
只保留发布者任务表中关于此任务的相关数据
【参数】taskPublisher myTask,double dMyMoney
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::DistributeMoney_Publisher(taskPublisher myTask,double dMyMoney){
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.GetID());
    newMessage.EditTitle("分配酬金成功！");
    newMessage.EditContent(QObject::tr("%3\n您发布的任务%1的酬金分配完毕，"
                                       "共支付%2元，请注意账户余额变动。")
                           .arg(myTask.GetTitle()).arg(dMyMoney).arg(time.toString()));
    newMessage.EditUser(m_User.GetID());
    m_listMessage.m_List.append(newMessage);

    //所有表中删除和该任务有关的所有数据
    g_backUp.m_listTaskLeader.Delete(myTask.GetID());
    g_backUp.m_listSignUpForLeader.Delete(myTask.GetID());
    g_backUp.m_listSignUpForTranslater.Delete(myTask.GetID());
    g_backUp.m_listTaskLeader.Delete(myTask.GetID());
    myTask.EditFlag(402);
    g_backUp.m_listTaskPublisher.Update(myTask);
}

/*************************************************************************
【函数名称】DistributeMoney_Leader
【函数功能】在发布者分配酬金结束之后，后台操作负责人账户变动，发消息提醒负责人确认酬金
【参数】double dMoney,taskPublisher myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::DistributeMoney_Leader(double dMoney,taskPublisher myTask){
    int iNum=m_listUser.SearchInList(myTask.GetLeader());
    m_listUser.m_List[iNum].AddMoney(dMoney);//发消息确认
    m_listUser.m_List[iNum].AddPoint(10);

    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.GetID());
    newMessage.EditTitle("酬金到账啦！");
    newMessage.EditContent(QObject::tr("%3\n您参与翻译的任务%1的酬金%2元已"
                                       "到账，请注意查收！")
                           .arg(myTask.GetTitle()).arg(dMoney)
                           .arg(time.toString()));
    newMessage.EditUser(myTask.GetLeader());
    m_listMessage.m_List.append(newMessage);
}

/*************************************************************************
【函数名称】DistributeMoney_Checker
【函数功能】在分配酬金之后，后台操作审核人账户变动，发消息提醒审核人确认
【参数】double dMoney, taskPublisher myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::DistributeMoney_Checker(double dMoney, taskPublisher myTask){
    int iNum=m_listUser.SearchInList(myTask.GetTaskChecker());
    m_listUser.m_List[iNum].AddMoney(dMoney);;
    m_listUser.m_List[iNum].AddPoint(10);
    //发消息提醒审核人
    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.GetID());
    newMessage.EditTitle("酬金到账啦！");
    newMessage.EditContent(QObject::tr("%3\n您参与翻译的任务%1的酬金"
                                       "%2元已到账，请注意查收！")
                           .arg(myTask.GetTitle()).arg(dMoney)
                           .arg(time.toString()));
    newMessage.EditUser(myTask.GetTaskChecker());
    m_listMessage.m_List.append(newMessage);
}

/*************************************************************************
【函数名称】DistributeMoney_Translater
【函数功能】分配酬金结束之后，后台对译者的账户信息进行操作，并且发消息提醒译者确认
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.26
【更改记录】
*************************************************************************/
void BackUp::DistributeMoney_Translater(double dMoney, taskTranslater myTask){
    int iNum=m_listUser.SearchInList(myTask.GetTranslater());
    //将译者余额存入表中
    m_listUser.m_List[iNum].AddMoney(dMoney);//发消息确认
    //译者加5分
    m_listUser.m_List[iNum].AddPoint(5);

    QDateTime time=QDateTime::currentDateTime();
    Message newMessage(m_listMessage.GetID());
    newMessage.EditTitle("酬金到账啦！");
    newMessage.EditContent(QObject::tr("%3\n您参与翻译的"
                                       "任务%1的酬金%2元已到账，请注意查收！")
                           .arg(myTask.GetTitle()).arg(dMoney)
                           .arg(time.toString()));
    newMessage.EditUser(myTask.GetLeader());
    m_listMessage.m_List.append(newMessage);
}

/*************************************************************************
【函数名称】Register
【函数功能】注册之后，发消息提醒用户，为用户介绍平台，并且将用户数据存入内存
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.27
【更改记录】
*************************************************************************/
void BackUp::Register(QString passwordvalue,QString nameValue
                      ,QString phoneValue,QString IDNum,
                      QString English){
    m_User.EditPassWrd(passwordvalue);
    m_User.EditID(nameValue);
    m_User.EditPhoneNum(phoneValue);
    m_User.EditIDNum(IDNum);
    m_User.EditEnglish(English);
    m_listUser.InsertIntoList(m_User);
    //发消息欢迎新用户
    Message newMessage(m_listMessage.GetID());
    newMessage.EditTitle("欢迎使用众包翻译平台！");
    newMessage.EditContent(QObject::tr("您刚才注册并成为众包翻译平台的一名用户，"
                                       "本平台为中英互译平台，共有发布者，"
                                       "负责人，译者三种角色，负责人报名要求为110分，"
                                       "发布者和译者均为无门槛参与，"
                                       "快点击“成为任务发布者”发布任务，或者点击"
                                       "“所有任务”寻找新任务吧！"));
    newMessage.EditUser(m_User.GetID());
    m_listMessage.m_List.append(newMessage);
}

/*************************************************************************
【函数名称】UserInfoEdit
【函数功能】在用户更改个人信息后，存储新修改的信息
【参数】QString IDValue,QString PhoneValue,QString EnglishValue
【返回值】 无
【开发者及日期】李佳芸 2019.7.27
【更改记录】
*************************************************************************/
void BackUp::UserInfoEdit(QString IDValue,QString PhoneValue
                          ,QString EnglishValue,QString PassWord,QString Name){
    m_User.EditIDNum(IDValue);
    m_User.EditPhoneNum(PhoneValue);
    m_User.EditEnglish(EnglishValue);
    m_User.EditPassWrd(PassWord);
    m_User.EditID(Name);
    m_listUser.Update(m_User);
}

/*************************************************************************
【函数名称】TaskPublishEdit
【函数功能】在用户发布新任务时重新修改的信息存储入内存
【参数】taskPublisher myTask,int iTaskClass,QString intro,QString title,
QString NewTask,int iTime,int iLeaderYear,int iLeaderMonth,int iLeaderDay,
double dMoney
【返回值】 无
【开发者及日期】李佳芸 2019.7.27
【更改记录】
*************************************************************************/
void BackUp::TaskPublishEdit(taskPublisher myTask,int iTaskClass,
                             QString intro,QString title,
                             QString NewTask,int iTime,int iLeaderYear,
                             int iLeaderMonth,int iLeaderDay,
                             double dMoney){
    myTask.EditInfo(iTaskClass,intro,title,
                    NewTask,iTime,iLeaderYear,
                    iLeaderMonth,iLeaderDay,
                    dMoney,m_User.GetID());
    myTask.EditID(m_listTaskPublisher.GetID());
    m_listTaskPublisher.Update(myTask);
}

/*************************************************************************
【函数名称】CheckDateForLeader
【函数功能】在应用启动时检测时间，在离发布者设定的截止日期7天、1天和到截止日期以及超过
截止日期时均设置提醒
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.27
【更改记录】
*************************************************************************/
void BackUp::CheckDateForLeader(){
    QDateTime time=QDateTime::currentDateTime();
    for(int i=0;i<m_listTaskPublisher.m_List.size();i++){
        QDate date1(m_listTaskPublisher.m_List[i].GetStartYear(),
                    m_listTaskPublisher.m_List[i].GetStartMonth(),
                    m_listTaskPublisher.m_List[i].GetStartDay());
        date1.addDays(m_listTaskPublisher.m_List[i].GetTime());
        QDate currentdate;
        currentdate=QDate::currentDate();
        if((currentdate.year()==date1.year()&&currentdate.month()==date1.month()&&
            currentdate.day()-date1.day()==1)
                &&(m_listTaskPublisher.m_List[i].GetFlag()==201||
                                    m_listTaskPublisher.m_List[i].GetFlag()==202||
                                    m_listTaskPublisher.m_List[i].GetFlag()==203||
                                    m_listTaskPublisher.m_List[i].GetFlag()==301||
                                    m_listTaskPublisher.m_List[i].GetFlag()==302)){
            Message newMessage(m_listMessage.GetID());
            newMessage.EditTitle("距发布者定的截止日期还剩1天，请抓紧时间！");
            newMessage.EditContent(QObject::tr("%4\n距发布者定的截止日期还剩1天，请抓紧时间！").
                                  arg(time.toString()));
            newMessage.EditUser(m_listTaskLeader.m_List[i].GetLeader());
            m_listMessage.m_List.append(newMessage);
        }
        else if((currentdate.year()==date1.year()&&currentdate.month()==date1.month()&&
                 currentdate.day()-date1.day()==7)&&(m_listTaskPublisher.m_List[i].GetFlag()==201||
                                         m_listTaskPublisher.m_List[i].GetFlag()==202||
                                         m_listTaskPublisher.m_List[i].GetFlag()==203||
                                         m_listTaskPublisher.m_List[i].GetFlag()==301||
                                         m_listTaskPublisher.m_List[i].GetFlag()==302)){
            Message newMessage(m_listMessage.GetID());
            newMessage.EditTitle("距发布者定的截止日期还剩7天，请抓紧时间！");
            newMessage.EditContent(QObject::tr("%4\n距发布者定的截止日期还剩7天，请抓紧时间！").
                                  arg(time.toString()));
            newMessage.EditUser(m_listTaskLeader.m_List[i].GetLeader());
            m_listMessage.m_List.append(newMessage);
        }
        else if((currentdate.year()==date1.year()&&currentdate.month()==date1.month()&&
                 currentdate.day()-date1.day()<=0)&&(m_listTaskPublisher.m_List[i].GetFlag()==201||
                                                          m_listTaskPublisher.m_List[i]
                                                     .GetFlag()==202||
                                         m_listTaskPublisher.m_List[i].GetFlag()==203||
                                         m_listTaskPublisher.m_List[i].GetFlag()==301||
                                         m_listTaskPublisher.m_List[i].GetFlag()==302)){
            Message newMessage(m_listMessage.GetID());
            newMessage.EditTitle("发布者规定时间已到，请抓紧时间提交译文！");
            newMessage.EditContent(QObject::tr("%4\n发布者规定时间已到，请抓紧时间提交译文！").
                                  arg(time.toString()));
            newMessage.EditUser(m_listTaskPublisher.m_List[i].GetLeader());
            m_listMessage.m_List.append(newMessage);
        }
    }
}

/*************************************************************************
【函数名称】CheckDateForTranslater
【函数功能】在距离负责人设定的截止日期7天、1天、到截止日期以及超过截止日期时分别发消息提醒
译者
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.27
【更改记录】
*************************************************************************/
void BackUp::CheckDateForTranslater(){
    QDateTime time=QDateTime::currentDateTime();
    for(int i=0;i<m_listTaskTranslater.m_List.size();i++){
        QDate date1(m_listTaskTranslater.m_List[i].GetEndYear(),
                    m_listTaskTranslater.m_List[i].GetEndMonth(),
                    m_listTaskTranslater.m_List[i].GetEndDay());
        QDate currentdate;
        currentdate=QDate::currentDate();
        if((currentdate.year()==date1.year()&&currentdate.month()==date1.month()&&
            currentdate.day()-date1.day()==1)&&(m_listTaskTranslater
                                                .m_List[i].GetFlag()==201||
                                    m_listTaskTranslater.m_List[i].GetFlag()==202||
                                    m_listTaskTranslater.m_List[i].GetFlag()==203||
                                    m_listTaskTranslater.m_List[i].GetFlag()==301||
                                    m_listTaskTranslater.m_List[i].GetFlag()==302)){
            Message newMessage(m_listMessage.GetID());
            newMessage.EditTitle("距负责人定的截止日期还剩1天，请抓紧时间！");
            newMessage.EditContent(QObject::tr("%4\n距负责人定的截止日期还剩1天，请抓紧时间！").
                                  arg(time.toString()));
            newMessage.EditUser(m_listTaskTranslater.m_List[i].GetLeader());
            m_listMessage.m_List.append(newMessage);
        }
        else if((currentdate.year()==date1.year()&&currentdate.month()==date1.month()&&
                 currentdate.day()-date1.day()==7)&&(m_listTaskTranslater
                                                     .m_List[i].GetFlag()==201||
                                         m_listTaskTranslater.m_List[i].GetFlag()==202||
                                         m_listTaskTranslater.m_List[i].GetFlag()==203||
                                         m_listTaskTranslater.m_List[i].GetFlag()==301||
                                         m_listTaskTranslater.m_List[i].GetFlag()==302)){
            Message newMessage(m_listMessage.GetID());
            newMessage.EditTitle("距负责人定的截止日期还剩7天，请抓紧时间！");
            newMessage.EditContent(QObject::tr("%4\n距负责人定的截止日期还剩7天，请抓紧时间！").
                                  arg(time.toString()));
            newMessage.EditUser(m_listTaskTranslater.m_List[i].GetLeader());
            m_listMessage.m_List.append(newMessage);
        }
        else if((currentdate.year()==date1.year()&&currentdate.month()==date1.month()&&
                 currentdate.day()-date1.day()<=0)&&(m_listTaskTranslater
                                                     .m_List[i].GetFlag()==201
                                                          ||m_listTaskTranslater
                                                     .m_List[i].GetFlag()==202||
                                         m_listTaskTranslater.m_List[i].GetFlag()==203||
                                         m_listTaskTranslater.m_List[i].GetFlag()==301||
                                         m_listTaskTranslater.m_List[i].GetFlag()==302)){
            Message newMessage(m_listMessage.GetID());
            newMessage.EditTitle("负责人规定时间已到，请抓紧时间提交译文！");
            newMessage.EditContent(QObject::tr("%4\n负责人规定时间已到，请抓紧时间提交译文！").
                                  arg(time.toString()));
            newMessage.EditUser(m_listTaskTranslater.m_List[i].GetLeader());
            m_listMessage.m_List.append(newMessage);
        }
    }
}

/*************************************************************************
【函数名称】Prolong_102
【函数功能】在发布者招募负责人时，若发现负责人为达标准，存储发布者选择延长的时间并且重新修改
任务状态
【参数】int iAdd, taskPublisher myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.27
【更改记录】
*************************************************************************/
void BackUp::Prolong_102(int iAdd, taskPublisher myTask){
    QDate time;
    time.setDate(myTask.GetLeaderYear(),myTask.GetLeaderMonth(),myTask.GetLeaderDay());
    time.addDays(iAdd);
    myTask.EditLeaderYear(time.year());
    myTask.EditLeaderMonth(time.month());
    myTask.EditLeaderDay(time.day());
    myTask.EditFlag(101);
    m_listTaskPublisher.Update(myTask);
}

/*************************************************************************
【函数名称】Prolong_203
【函数功能】在负责人招募译者结束时，选择延长招募时间，存储延长的时间并且更改任务状态
为招募译者
【参数】int iAdd, taskLeader myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.27
【更改记录】
*************************************************************************/
void BackUp::Prolong_203(int iAdd, taskLeader myTask){
    QDate time;
    time.setDate(myTask.GetTranslaterYear(),myTask.GetTranslaterMonth(),
                 myTask.GetTranslaterDay());
    time.addDays(iAdd);
    myTask.EditTranslaterYear(time.year());
    myTask.EditTranslaterMonth(time.month());
    myTask.EditTranslaterDay(time.day());
    myTask.EditFlag(202);
    m_listTaskLeader.Update(myTask);
}
