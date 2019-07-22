#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include "register.h"
#include "connection.h"
#include "taskspublished.h"
#include <QList>
#include "user.h"
#include "task.h"

int main(int argc, char *argv[])
{
    if(QT_VERSION>=QT_VERSION_CHECK(5,6,0))
            QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    if (!createConnection())
         return 1;
    //tasksPublished *r=new tasksPublished;
    //r->show();
    return a.exec();
}
