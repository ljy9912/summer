#include "list.h"
#include <QDate>

list::list()
{

}

/*************************************************************************
【函数名称】list
【函数功能】构造函数
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.19
【更改记录】
*************************************************************************/
list::list(const list& newList):User(newList.User),TaskPublisher(newList.TaskPublisher),
    SignUpForLeader(newList.SignUpForLeader),TaskLeader(newList.TaskLeader),
    SignUpForTranslater(newList.SignUpForTranslater),TaskTranslater(newList.TaskTranslater),
    message(newList.message)
{

}

list::~list(){
    
}

/*************************************************************************
【函数名称】operator =
【函数功能】=符号重载
【参数】const list& newList
【返回值】 无
【开发者及日期】李佳芸 2019.7.19
【更改记录】
*************************************************************************/
list& list::operator =(const list& newList)
{
    User=newList.User;
    TaskPublisher=newList.TaskPublisher;
    SignUpForLeader=newList.SignUpForLeader;
    TaskLeader=newList.TaskLeader;
    SignUpForTranslater=newList.SignUpForTranslater;
    TaskTranslater=newList.TaskTranslater;
    message=newList.message;
    return *this;
}

/*************************************************************************
【函数名称】updateList
【函数功能】对User的list的更新
【参数】user myUser
【返回值】 无
【开发者及日期】李佳芸 2019.7.19
【更改记录】
*************************************************************************/
void list::updateList(user myUser){
    for(int i=0;i<User.size();i++){
        if(User[i].GetID()==myUser.GetID()){
            User[i]=myUser;
            break;
        }
    }
}

/*************************************************************************
【函数名称】updateList
【函数功能】对taskPublisher的list的更新
【参数】user myUser
【返回值】 无
【开发者及日期】李佳芸 2019.7.19
【更改记录】
*************************************************************************/
void list::updateList(taskPublisher myTask){
    for(int i=0;i<TaskPublisher.size();i++){
        if(TaskPublisher[i].GetID()==myTask.GetID()){
            TaskPublisher[i]=myTask;
            break;
        }
    }
}

/*************************************************************************
【函数名称】updateList
【函数功能】对taskLeader的list的更新
【参数】taskLeader myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.19
【更改记录】
*************************************************************************/
void list::updateList(taskLeader myTask){
    for(int i=0;i<TaskLeader.size();i++){
        if(TaskLeader[i].GetID()==myTask.GetID()){
            TaskLeader[i]=myTask;
            break;
        }
    }
}

/*************************************************************************
【函数名称】updateList
【函数功能】对taskTranslater的list的更新
【参数】taskTranslater myTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.19
【更改记录】
*************************************************************************/
void list::updateList(taskTranslater myTask){
    for(int i=0;i<TaskTranslater.size();i++){
        if(TaskTranslater[i].GetID()==myTask.GetID()){
            TaskTranslater[i]=myTask;
            break;
        }
    }
}

/*************************************************************************
【函数名称】insertIntoList
【函数功能】在一个list中插入一个节点
【参数】user myUser
【返回值】 无
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
void list::insertIntoList(user myUser){
    User.append(myUser);
}

/*************************************************************************
【函数名称】searchUserInList
【函数功能】在User的List中搜索myuser并返回所在位置
【参数】user myUser
【返回值】 无
【开发者及日期】李佳芸 2019.7.18
【更改记录】
*************************************************************************/
int list::searchUserInList(user myUser){
    int i=0;
    for(i=0;i<User.size();i++){
        if(User[i].GetID()==myUser.GetID()){
            return i;
        }
    }
}

/*************************************************************************
【函数名称】insertIntoList
【函数功能】将taskPublisher对象插入list中
【参数】无
【返回值】 无
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
void list::insertIntoList(taskPublisher myTask){
    TaskPublisher.append(myTask);
}

/*************************************************************************
【函数名称】searchTaskInList
【函数功能】在TaskPublish的List当中寻找myTask，并返回其所在位置
【参数】taskPublisher myTask
【返回值】 int
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
int list::searchTaskInList(taskPublisher myTask){
    int i=0;
    for(i=0;i<TaskPublisher.size();i++){
        if(TaskPublisher[i].GetID()==myTask.GetID()){
            return i;
        }
    }
}

/*************************************************************************
【函数名称】searchLeaderInList
【函数功能】在SignUpForLeader中寻找myLeader并返回所在位置，如果该成员不存在，返回-1
【参数】signUpForLeader myLeader
【返回值】 int
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
int list::searchLeaderInList(signUpForLeader myLeader){
    int i=0;
    for(i=0;i<SignUpForLeader.size();i++){
        if((myLeader.GetID())==(SignUpForLeader[i].GetID())){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】searchUserInList
【函数功能】在User中寻找id为iIDUser的用户并返回位置
【参数】int iIDUser
【返回值】 int
【开发者及日期】李佳芸 2019.7.20
【更改记录】
*************************************************************************/
int list::searchUserInList(QString IDUser){
    int i=0;
    for(i=0;i<User.size();i++){
        if(IDUser==User[i].GetID()){
            return i;
        }
    }
}

/*************************************************************************
【函数名称】searchTaskInList
【函数功能】在Task的List当中寻找id为iIDTask的成员并返回位置
【参数】int iIDTask
【返回值】 int
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
int list::searchTaskInList(int iIDTask){
    int i=0;
    for(i=0;i<TaskPublisher.size();i++){
        if(iIDTask==TaskPublisher[i].GetID()){
            return i;
        }
    }
}

/*************************************************************************
【函数名称】searchTranslaterInList
【函数功能】在SignUpForTranslater的报名表中寻找myTranslager的成员，并返回位置
【参数】signUpForTranslater myTranslater
【返回值】 int
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
int list::searchTranslaterInList(signUpForTranslater myTranslater){
    int i=0;
    for(i=0;i<SignUpForTranslater.size();i++){
        if((myTranslater.GetID())==(SignUpForTranslater[i].GetID())){
            return i;
        }
    }
    return -1;
}

/*************************************************************************
【函数名称】SearchTaskForPublisher
【函数功能】在TaskPublisher中寻找所有myUser的发布的任务并返回一个list
【参数】user myUser
【返回值】 QList <taskPublisher>
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
QList <taskPublisher> list::SearchTaskForPublisher(user myUser){
    QList<taskPublisher> publisherTask;
    for(int i=0;i<TaskPublisher.size();i++){
        if(TaskPublisher[i].GetPublisher()==myUser.GetID()){
            publisherTask.append(TaskPublisher[i]);
        }
    }
    return publisherTask;
}

/*************************************************************************
【函数名称】SearchTaskForLeader
【函数功能】在TaskLeader的list中寻找myUser作为负责人的任务并返回一个list
【参数】user myUser
【返回值】 QList <taskLeader>
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
QList <taskLeader> list::SearchTaskForLeader(user myUser){
    QList <taskLeader> leaderTask;
    for(int i=0;i<TaskLeader.size();i++){
        if(TaskLeader[i].GetLeader()==myUser.GetID()){
            leaderTask.append(TaskLeader[i]);
        }
    }
    return leaderTask;
}

/*************************************************************************
【函数名称】SearchTaskForTranslater
【函数功能】在TaskTranslater中寻找myUser作为译者的任务并返回一个List
【参数】user myUser
【返回值】QList <taskTranslater>
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
QList <taskTranslater> list::SearchTaskForTranslater(user myUser){
    QList <taskTranslater> translaterTask;
    for(int i=0;i<TaskTranslater.size();i++){
        if(TaskTranslater[i].GetTranslater()==myUser.GetID()){
            translaterTask.append(TaskTranslater[i]);
        }
    }
    return translaterTask;
}

/*************************************************************************
【函数名称】SearchTaskForTranslater
【函数功能】寻找TaskTranslater中翻译idTask任务的所有子任务并返回一个List
【参数】int idTask
【返回值】 QList <taskTranslater>
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
QList <taskTranslater> list::SearchTaskForTranslater(int idTask){
    QList <taskTranslater> translaterTask;
    for(int i=0;i<TaskTranslater.size();i++){
        if(TaskTranslater[i].GetIDTask()==idTask&&TaskTranslater[i].GetFlagToLeader()==0){
            translaterTask.append(TaskTranslater[i]);
        }
    }
    return translaterTask;
}

/*************************************************************************
【函数名称】SearchTaskForTranslater_302
【函数功能】寻找TaskTranslater中翻译idTask任务的所有子任务并返回一个List
【参数】int idTask
【返回值】 QList <taskTranslater>
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
QList <taskTranslater> list::SearchTaskForTranslater_302(int idTask){
    QList <taskTranslater> translaterTask;
    for(int i=0;i<TaskTranslater.size();i++){
        if(TaskTranslater[i].GetIDTask()==idTask){
            translaterTask.append(TaskTranslater[i]);
        }
    }
    return translaterTask;
}

/*************************************************************************
【函数名称】SearchLeaderForTask
【函数功能】在SignUpForLeader中寻找报名myTask负责人的人，并返回一个list
【参数】taskPublisher myTask
【返回值】 QList <signUpForLeader>
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
QList <signUpForLeader> list::SearchLeaderForTask(taskPublisher myTask){
    QList <signUpForLeader> myLeader;
    for(int i=0;i<SignUpForLeader.size();i++){
        if(myTask.GetID()==SignUpForLeader[i].GetIDTask()){
            myLeader.append(SignUpForLeader[i]);
        }
    }
    return myLeader;
}

/*************************************************************************
【函数名称】SearchTranslaterForTask
【函数功能】在SignUpForTranslater中寻找报名myTask译者的人并返回一个list
【参数】taskLeader myTask
【返回值】QList <signUpForTranslater>
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
QList <signUpForTranslater> list::SearchTranslaterForTask(taskLeader myTask){
    QList <signUpForTranslater> myLeader;
    for(int i=0;i<SignUpForTranslater.size();i++){
        if(myTask.GetID()==SignUpForTranslater[i].GetIDTask()){
            myLeader.append(SignUpForTranslater[i]);
        }
    }
    return myLeader;
}

/*************************************************************************
【函数名称】SearchMessageforUser
【函数功能】在message的list中寻找idUser的消息并返回一个List
【参数】int idUser
【返回值】QList<Message>
【开发者及日期】李佳芸 2019.7.24
【更改记录】
*************************************************************************/
QList<Message> list::SearchMessageforUser(QString idUser){
    QList<Message> myMessage;
    for(int i=0;i<message.size();i++){
        if(message[i].GetUser()==idUser){
            myMessage.append(message[i]);
        }
    }
    return myMessage;
}
/*************************************************************************
【函数名称】TaskLeaderAppend
【函数功能】在TaskLeader中添加TaskPublisher对象（只筛选相同信息）
【参数】taskPublisher myLeader
【返回值】 无
【开发者及日期】李佳芸 2019.7.21
【更改记录】
*************************************************************************/
void list::TaskLeaderAppend(taskPublisher myLeader){
    taskLeader leader;
    leader.EditID(myLeader.GetID());    
    leader.EditIntroduction(myLeader.GetIntroduction());
    leader.EditLeader(myLeader.GetLeader());
    leader.EditFlag(myLeader.GetFlag());
    leader.EditMoney(myLeader.GetMoney());
    leader.EditPublisher(myLeader.GetPublisher());
    leader.EditTask(myLeader.GetTask());
    leader.EditTaskClass(myLeader.GetTaskClass());
    leader.EditTime(myLeader.GetTime());
    leader.EditStartYear(myLeader.GetStartYear());
    leader.EditStartMonth(myLeader.GetStartMonth());
    leader.EditStartDay(myLeader.GetStartDay());
    leader.EditTitle(myLeader.GetTitle());
    TaskLeader.append(leader);

}

/*************************************************************************
【函数名称】Delete
【函数功能】任务完成结束后，在list中删除所有关于idTask的数据
【参数】int idTask
【返回值】 无
【开发者及日期】李佳芸 2019.7.22
【更改记录】
*************************************************************************/
void list::Delete(int idTask){
    for(int i=m_List.size()-1;i>=0;i--){
        if(m_List[i].GetID()==idTask){
            m_List.removeAt(i);
        }
    }
}
