#include "list.h"


list::list()
{

}

list::list(const list& newList):User(newList.User),TaskPublisher(newList.TaskPublisher),
    SignUpForLeader(newList.SignUpForLeader)
{

}

list::~list(){
    
}

list::operator =(const list& newList)
{
    User=newList.User;
    TaskPublisher=newList.TaskPublisher;
    SignUpForLeader=newList.SignUpForLeader;
}

void list::updateList(user myUser){
    for(int i=0;i<User.size();i++){
        if(User[i].GetID()==myUser.GetID()){
            User[i]=myUser;
            break;
        }
    }
}

void list::updateList(taskPublisher myTask){
    for(int i=0;i<TaskPublisher.size();i++){
        if(TaskPublisher[i].GetID()==myTask.GetID()){
            TaskPublisher[i]=myTask;
            break;
        }
    }
}

void list::updateList(taskLeader myTask){
    for(int i=0;i<TaskLeader.size();i++){
        if(TaskLeader[i].GetID()==myTask.GetID()){
            TaskLeader[i]=myTask;
            break;
        }
    }
}

void list::updateList(taskTranslater myTask){
    for(int i=0;i<TaskTranslater.size();i++){
        if(TaskTranslater[i].GetID()==myTask.GetID()){
            TaskTranslater[i]=myTask;
            break;
        }
    }
}

void list::insertIntoList(user myUser){
    User.append(myUser);
}

int list::searchUserInList(user myUser){
    int i=0;
    for(i=0;i<User.size();i++){
        if(User[i].GetID()==myUser.GetID()){
            return i;
        }
    }
}

void list::insertIntoList(taskPublisher myTask){
    TaskPublisher.append(myTask);
}

int list::searchTaskInList(taskPublisher myTask){
    int i=0;
    for(i=0;i<TaskPublisher.size();i++){
        if(TaskPublisher[i].GetID()==myTask.GetID()){
            return i;
        }
    }
}

int list::searchLeaderInList(signUpForLeader myLeader){
    int i=0;
    for(i=0;i<SignUpForLeader.size();i++){
        if((myLeader.GetID())==(SignUpForLeader[i].GetID())){
            return i;
        }
    }
    return -1;
}

int list::searchUserInList(int iIDUser){
    int i=0;
    for(i=0;i<User.size();i++){
        if(iIDUser==User[i].GetID()){
            return i;
        }
    }
}

int list::searchTaskInList(int iIDTask){
    int i=0;
    for(i=0;i<TaskPublisher.size();i++){
        if(iIDTask==TaskPublisher[i].GetID()){
            return i;
        }
    }
}

int list::searchTranslaterInList(signUpForTranslater myTranslater){
    int i=0;
    for(i=0;i<SignUpForTranslater.size();i++){
        if((myTranslater.GetID())==(SignUpForTranslater[i].GetID())){
            return i;
        }
    }
    return -1;
}

QList <taskPublisher> list::SearchTaskForPublisher(user myUser){
    QList<taskPublisher> publisherTask;
    for(int i=0;i<TaskPublisher.size();i++){
        if(TaskPublisher[i].GetPublisher()==myUser.GetID()){
            publisherTask.append(TaskPublisher[i]);
        }
    }
    return publisherTask;
}

QList <taskLeader> list::SearchTaskForLeader(user myUser){
    QList <taskLeader> leaderTask;
    for(int i=0;i<TaskLeader.size();i++){
        if(TaskLeader[i].GetLeader()==myUser.GetID()){
            leaderTask.append(TaskLeader[i]);
        }
    }
    return leaderTask;
}

QList <taskTranslater> list::SearchTaskForTranslater(user myUser){
    QList <taskTranslater> translaterTask;
    for(int i=0;i<TaskTranslater.size();i++){
        if(TaskTranslater[i].GetTranslater()==myUser.GetID()){
            translaterTask.append(TaskTranslater[i]);
        }
    }
    return translaterTask;
}

QList <taskTranslater> list::SearchTaskForTranslater(int idTask){
    QList <taskTranslater> translaterTask;
    for(int i=0;i<TaskTranslater.size();i++){
        if(TaskTranslater[i].GetIDTask()==idTask&&TaskTranslater[i].GetFlagToLeader()==0){
            translaterTask.append(TaskTranslater[i]);
        }
    }
    return translaterTask;
}

QList <signUpForLeader> list::SearchLeaderForTask(taskPublisher myTask){
    QList <signUpForLeader> myLeader;
    for(int i=0;i<SignUpForLeader.size();i++){
        if(myTask.GetID()==SignUpForLeader[i].GetIDTask()){
            myLeader.append(SignUpForLeader[i]);
        }
    }
    return myLeader;
}

QList <signUpForTranslater> list::SearchTranslaterForTask(taskLeader myTask){
    QList <signUpForTranslater> myLeader;
    for(int i=0;i<SignUpForTranslater.size();i++){
        if(myTask.GetID()==SignUpForTranslater[i].GetIDTask()){
            myLeader.append(SignUpForTranslater[i]);
        }
    }
    return myLeader;
}

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
    TaskLeader.append(leader);
}
