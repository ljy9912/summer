#-------------------------------------------------
#
# Project created by QtCreator 2019-07-10T08:33:42
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Translate
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    logindialog.cpp \
    register.cpp \
    user.cpp \
    userinfo.cpp \
    userinfoedit.cpp \
    tasknew.cpp \
    taskpublish.cpp \
    task.cpp \
    taskpublishedit.cpp \
    taskspublished.cpp \
    registerconfirm.cpp \
    sqlquery.cpp \
    list.cpp \
    signupforleader.cpp \
    signupfortranslater.cpp \
    publishertask.cpp \
    taskpublisher.cpp \
    taskleader.cpp \
    leadertask.cpp \
    tasktranslater.cpp \
    translatertask.cpp \
    messagebox.cpp \
    message.cpp \
    backup.cpp \
    listuser.cpp \
    listtaskpublisher.cpp \
    listtaskleader.cpp \
    listtasktranslater.cpp \
    listsignupforleader.cpp \
    listsignupfortranslater.cpp \
    listmessage.cpp

HEADERS += \
        mainwindow.h \
    logindialog.h \
    register.h \
    connection.h \
    userinfo.h \
    userinfoedit.h \
    tasknew.h \
    taskpublish.h \
    task.h \
    taskpublishedit.h \
    taskspublished.h \
    registerconfirm.h \
    sqlquery.h \
    user.h \
    list.h \
    signupforleader.h \
    signupfortranslater.h \
    publishertask.h \
    taskpublisher.h \
    taskleader.h \
    leadertask.h \
    tasktranslater.h \
    translatertask.h \
    messagebox.h \
    message.h \
    backup.h \
    listuser.h \
    listtaskpublisher.h \
    listtaskleader.h \
    listtasktranslater.h \
    listsignupforleader.h \
    listsignupfortranslater.h \
    listmessage.h

FORMS += \
        mainwindow.ui \
    logindialog.ui \
    register.ui \
    userinfo.ui \
    userinfoedit.ui \
    usermoney.ui \
    tasknew.ui \
    taskpublish.ui \
    taskpublishedit.ui \
    taskspublished.ui \
    registerconfirm.ui \
    publishertask.ui \
    leadertask.ui \
    translatertask.ui \
    messagebox.ui
