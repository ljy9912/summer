#ifndef MESSAGEBACKUP_H
#define MESSAGEBACKUP_H
#include <QString>
#include "message.h"
#include "list.h"

class BackUp
{
public:
    BackUp();
    BackUp(const BackUp& myBackUp);
    ~BackUp();
    BackUp& operator =(const BackUp& myBackUp);


    void SignUpForLeader(QString ID, int idTask);
    void TaskPublish(QString ID, QString intro);
    void CheckDateSnupfrLeader();
    void CheckDateSnupfrTranslater();
    void SelectLeaderDone(QString PublisherID, QString idLeader, QString intro);
    void SetTranslaterDone(QString LeaderID, QString intro);
    void SignUpForTranslaterDone(QString ID, QString intro);
    void SelectTranslaterDone_Leader(QString LeaderID, QString intro);
    void SelectTranslaterDone_Translater(QString intro, QString TranslaterID);
    void SubmitResultDone_Translater(QString intro, QString TranslaterID);
    void SubmitResultDone_Leader(QString intro, QString TranslaterID, QString LeaderID);
    void SubmitCommentDone_Leader(QString intro, QString LeaderID, QString TranslaterID);
    void SubmitCommentDone_Translater(QString intro, QString TranslaterID);
    void EndTranslateDone_Leader(QString intro, QString TranslaterID, QString LeaderID);
    void EndTranslateDone_Translater(QString intro, QString iTranslaterID);
    void StartIntegrate(QString intro,QString LeaderID);
    void IntegratingDone_Leader(QString intro, QString LeaderID);
    void IntegratingDone_Publisher(QString intro, QString PublisherID);
    void DistributeMoney_Publisher(QString intro,QString PublisherID,double dMyMoney);
    void DistributeMoney_Translater(QString intro, double dMyMoney, QString LeaderID);

    list m_List;
    user m_User;
};
extern BackUp g_backUp;
#endif // MESSAGEBACKUP_H