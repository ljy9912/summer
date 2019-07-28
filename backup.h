#ifndef MESSAGEBACKUP_H
#define MESSAGEBACKUP_H
#include <QString>
#include "message.h"
#include "listmessage.h"
#include "listsignupforleader.h"
#include "listsignupfortranslater.h"
#include "listtaskleader.h"
#include "listtaskpublisher.h"
#include "listtasktranslater.h"
#include "listuser.h"

class BackUp
{
public:
    BackUp();
    BackUp(const BackUp& myBackUp);
    ~BackUp();
    BackUp& operator =(const BackUp& myBackUp);


    void SignUpForLeader(int i);
    void TaskPublish(taskPublisher myTask);
    void CheckDateSnupfrLeader();
    void CheckDateSnupfrTranslater();
    void SelectLeaderDone(QString PublisherID, QString idLeader, QString intro);
    void SetTranslaterDone(taskLeader myLeader, int iTranslaterYear, int iTranslaterMonth, int iTranslaterDay);
    void SignUpForTranslaterDone(int i);
    void SelectTranslaterDone_Leader(taskLeader myTask);
    void SelectTranslaterDone_Translater(taskLeader Task, signUpForTranslater myTranslater,
                                         int iEndYear, int iEndMonth, int iEndDay, QString newTask);
    void SubmitResultDone(taskTranslater myTask, QString myResult);
    void SubmitCommentDone(taskTranslater myTask,QString newComment);
    void SubmitCommentDone_Translater(QString intro, QString TranslaterID);
    void EndTranslateDone_Leader(QString intro, QString TranslaterID, QString LeaderID);
    void EndTranslateDone_Translater(taskLeader myTaskLeader, taskTranslater myTaskTranslater);
    void StartIntegrate(QString intro,QString LeaderID);
    void IntegratingDone(taskLeader myTask, QString newResult);
    void DistributeMoney_Publisher(QString intro,QString PublisherID,double dMyMoney);
    void DistributeMoney_Translater(QString intro, double dMyMoney, QString LeaderID);

    void Register(QString passwordvalue, QString nameValue, QString phoneValue,
                  QString IDNum, QString English);
    void UserInfoEdit(QString IDValue, QString PhoneValue, QString EnglishValue);

    listMessage m_listMessage;
    listSignUpForLeader m_listSignUpForLeader;
    listSignUpForTranslater m_listSignUpForTranslater;
    listTaskPublisher m_listTaskPublisher;
    listTaskLeader m_listTaskLeader;
    listTaskTranslater m_listTaskTranslater;
    listUser m_listUser;
    user m_User;
};
extern BackUp g_backUp;
#endif // MESSAGEBACKUP_H
