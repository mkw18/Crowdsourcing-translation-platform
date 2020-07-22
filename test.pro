#-------------------------------------------------
#
# Project created by QtCreator 2019-07-22T07:07:02
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        assigndlg.cpp \
        assignment.cpp \
        assignprincipal.cpp \
        assignpublisher.cpp \
        assigntranslator.cpp \
        auditdlg.cpp \
        book.cpp \
        confirmdlg.cpp \
        contrastdlg.cpp \
        database.cpp \
        depositdlg.cpp \
        employmentdlg.cpp \
        enrolldlg.cpp \
        feedbackdlg.cpp \
        infomaintaindlg.cpp \
        logindlg.cpp \
        main.cpp \
        mainwindow.cpp \
        msgbox.cpp \
        msgboxdlg.cpp \
        msgdetaildlg.cpp \
        newmissiondlg.cpp \
        passworddlg.cpp \
        person.cpp \
        personalmainwindow.cpp \
        platform.cpp \
        pncpassigndlg.cpp \
        pncpdlg.cpp \
        pubdlg.cpp \
        signupdlg.cpp \
        transddldlg.cpp \
        transdlg.cpp \
        translanguage.cpp \
        user.cpp

HEADERS += \
        assigndlg.h \
        assignment.h \
        assignprincipal.h \
        assignpublisher.h \
        assigntranslator.h \
        auditdlg.h \
        book.h \
        confirmdlg.h \
        contrastdlg.h \
        database.h \
        depositdlg.h \
        employmentdlg.h \
        enrolldlg.h \
        feedbackdlg.h \
        infomaintaindlg.h \
        logindlg.h \
        mainwindow.h \
        msgbox.h \
        msgboxdlg.h \
        msgdetaildlg.h \
        newmissiondlg.h \
        passworddlg.h \
        person.h \
        personalmainwindow.h \
        platform.h \
        pncpassigndlg.h \
        pncpdlg.h \
        pubdlg.h \
        signupdlg.h \
        system.h \
        transddldlg.h \
        transdlg.h \
        translanguage.h \
        user.h

FORMS += \
        assigndlg.ui \
        auditdlg.ui \
        book.ui \
        confirmdlg.ui \
        contrastdlg.ui \
        depositdlg.ui \
        employmentdlg.ui \
        enrolldlg.ui \
        feedbackdlg.ui \
        infomaintaindlg.ui \
        logindlg.ui \
        mainwindow.ui \
        msgboxdlg.ui \
        msgdetaildlg.ui \
        newmissiondlg.ui \
        passworddlg.ui \
        personalmainwindow.ui \
        pncpassigndlg.ui \
        pncpdlg.ui \
        pubdlg.ui \
        signupdlg.ui \
        transddldlg.ui \
        transdlg.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    myResource.qrc
