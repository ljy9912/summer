#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include "register.h"
#include "connection.h"
#include "taskspublished.h"
#include <QList>
#include "user.h"
#include "task.h"
#include <QSqlQuery>
#include "backup.h"


BackUp g_backUp;
int main(int argc, char *argv[])
{
    if(QT_VERSION>=QT_VERSION_CHECK(5,6,0))
            QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    if (!createConnection())
         return 1;
    //tasksPublished *r=new tasksPublished;
    //r->show();

    LoginDialog r;
    SqlQuery query;
    query.createUser();
    query.createTasks();
    query.createSignUpForLeader();
    query.createSignUpForTranslater();
    query.createTaskLeader();
    query.createTaskTranslater();
    query.createMessage();
    g_backUp.m_List.TaskPublisher=query.GetTasks();
    g_backUp.m_List.User=query.GetUser();
    g_backUp.m_List.SignUpForLeader=query.GetSignUpForLeader();
    g_backUp.m_List.SignUpForTranslater=query.GetSignUpForTranslater();
    g_backUp.m_List.TaskLeader=query.GetTaskLeader();
    g_backUp.m_List.TaskTranslater=query.GetTaskTranslater();
    g_backUp.m_List.message=query.GetMessage();
    g_backUp.CheckDateSnupfrLeader();
    g_backUp.CheckDateSnupfrTranslater();

    r.show();
    return a.exec();
}
