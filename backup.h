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


    void SignUpForLeader(int iID, int idTask);
    void TaskPublish(int iID, QString intro);
    void CheckDateSnupfrLeader();
    void CheckDateSnupfrTranslater();
    void SelectLeaderDone(int iPublisherID, int idLeader, QString intro);
    void SetTranslaterDone(int iLeaderID);
    void SignUpForTranslaterDone(int iID, QString intro);
    void SelectTranslaterDone_Leader(int iLeaderID, QString intro);
    void SelectTranslaterDone_Translater(QString intro, int iTranslaterID);
    void SubmitResultDone_Translater(QString intro,int iTranslaterID);
    void SubmitResultDone_Leader(QString intro,int iTranslaterID,int iLeaderID);
    void SubmitCommentDone_Leader(QString intro, int iLeaderID, int iTranslaterID);
    void SubmitCommentDone_Translater(QString intro, int iTranslaterID);
    void EndTranslateDone_Leader(QString intro, int iTranslaterID, int iLeaderID);
    void EndTranslateDone_Translater(QString intro, int iTranslaterID);
    void StartIntegrate(QString intro,int iLeaderID);
    void IntegratingDone_Leader(QString intro,int iLeaderID);
    void IntegratingDone_Publisher(QString intro,int iPublisherID);
    void DistributeMoney_Publisher(QString intro,int iPublisherID,double dMyMoney);
    void DistributeMoney_Translater(QString intro,double dMyMoney,int iLeaderID);

    list m_List;
    user m_User;
};

#endif // MESSAGEBACKUP_H
