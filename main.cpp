#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include "register.h"
#include "taskspublished.h"
#include <QList>
#include "user.h"
#include "task.h"
#include <QSqlQuery>
#include "backup.h"
#include <QMessageBox>
#include "sqlquery.h"

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection."
                     ), QMessageBox::Cancel);
        return false;
    }

    return true;
}

BackUp g_backUp;
int main(int argc, char *argv[])
{
    /*if(QT_VERSION>=QT_VERSION_CHECK(5,6,0))
            QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);*/
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
    g_backUp.m_listTaskPublisher=query.GetTasks();
    g_backUp.m_listUser=query.GetUser();
    g_backUp.m_listSignUpForLeader=query.GetSignUpForLeader();
    g_backUp.m_listSignUpForTranslater=query.GetSignUpForTranslater();
    g_backUp.m_listTaskLeader=query.GetTaskLeader();
    g_backUp.m_listTaskTranslater=query.GetTaskTranslater();
    g_backUp.m_listMessage=query.GetMessage();
    g_backUp.CheckDateSnupfrLeader();
    g_backUp.CheckDateSnupfrTranslater();

    r.show();
    return a.exec();
}


