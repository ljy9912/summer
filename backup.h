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
#include "listsignupforchecker.h"

class BackUp
{
public:
    BackUp();
    BackUp(const BackUp& myBackUp);
    ~BackUp();
    BackUp& operator =(const BackUp& myBackUp);


    void SignUpForLeader(int i);
    void SignUpForChecker(int i);
    void TaskPublish(taskPublisher myTask);
    void CheckDateForLeader();
    void CheckDateForTranslater();
    void CheckDateSnupfrLeader();
    void CheckDateSnupfrTranslater();
    void SelectLeaderDone(taskPublisher myTask, QString iIdLeader, QString iIDChecker);
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
    void DistributeMoney_Publisher(taskPublisher myTask, double dMyMoney);
    void DistributeMoney_Translater(double dMoney, taskTranslater myTask);
    void DistributeMoney_Leader(double dMoney,taskPublisher myTask);
    void DistributeMoney_Checker(double dMoney,taskPublisher myTask);

    void Register(QString passwordvalue, QString nameValue, QString phoneValue,
                  QString IDNum, QString English);
    void UserInfoEdit(QString IDValue, QString PhoneValue, QString EnglishValue);
    void TaskPublishEdit(taskPublisher myTask, int iTaskClass, QString intro, QString title, QString NewTask, int iTime, int iLeaderYear, int iLeaderMonth, int iLeaderDay, double dMoney);
    void Prolong_102(int iAdd,taskPublisher myTask);
    void Prolong_203(int iAdd,taskLeader myTask);

    listMessage m_listMessage;
    listSignUpForLeader m_listSignUpForLeader;
    listSignUpForTranslater m_listSignUpForTranslater;
    listTaskPublisher m_listTaskPublisher;
    listTaskLeader m_listTaskLeader;
    listTaskTranslater m_listTaskTranslater;
    listUser m_listUser;
    listSignUpForChecker m_listSignUpForChecker;
    user m_User;
};
extern BackUp g_backUp;
#endif // MESSAGEBACKUP_H
