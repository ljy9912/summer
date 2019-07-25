#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include "sqlquery.h"
#include "logindialog.h"
#include "list.h"

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

#endif // CONNECTION_H
