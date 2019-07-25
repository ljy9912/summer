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

int main(int argc, char *argv[])
{
    if(QT_VERSION>=QT_VERSION_CHECK(5,6,0))
            QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    if (!createConnection())
         return 1;
    //tasksPublished *r=new tasksPublished;
    //r->show();
    BackUp myBackup;
    LoginDialog r;
    SqlQuery query;
    query.createUser();
    query.createTasks();
    query.createSignUpForLeader();
    query.createSignUpForTranslater();
    query.createTaskLeader();
    query.createTaskTranslater();
    query.createMessage();
    myBackup.m_List.TaskPublisher=query.GetTasks();
    myBackup.m_List.User=query.GetUser();
    myBackup.m_List.SignUpForLeader=query.GetSignUpForLeader();
    myBackup.m_List.SignUpForTranslater=query.GetSignUpForTranslater();
    myBackup.m_List.TaskLeader=query.GetTaskLeader();
    myBackup.m_List.TaskTranslater=query.GetTaskTranslater();
    myBackup.m_List.message=query.GetMessage();

    r.EditBackUp(myBackup);
    r.show();
    return a.exec();
}
