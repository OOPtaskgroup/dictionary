#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T14:04:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dictionary
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controller.cpp \
    datacontroller.cpp \
    logging.cpp \
    logindlg.cpp \
    usercontroller.cpp \
    wordcontroller.cpp \
    regdlg.cpp \
    configdlg.cpp \
    configuration.cpp \
    data.cpp \
    exception.cpp \
    userdata.cpp \
    worddata.cpp \
    recitewindow.cpp \
    userdatabase.cpp \
    worddatabase.cpp \
    consts.cpp \
    database.cpp \
    lookupwindow.cpp \
    pwdchangedlg.cpp \
    exmanagedlg.cpp \
    addexdlg.cpp

HEADERS  += mainwindow.h \
    consts.h \
    controller.h \
    datacontroller.h \
    logging.h \
    logindlg.h \
    usercontroller.h \
    wordcontroller.h \
    regdlg.h \
    configdlg.h \
    configuration.h \
    data.h \
    exception.h \
    exceptions.h \
    nosuchfileexception.h \
    outofrangeexception.h \
    userdata.h \
    worddata.h \
    recitewindow.h \
    itemalreadyexistexception.h \
    itemnotfoundexception.h \
    passwordnotcorrectexception.h \
    database.h \
    userdatabase.h \
    worddatabase.h \
    lookupwindow.h \
    pwdchangedlg.h \
    wordshavebeenrecitedexception.h \
    exmanagedlg.h \
    addexdlg.h

FORMS    += mainwindow.ui \
    logindlg.ui \
    regdlg.ui \
    configdlg.ui \
    recitewindow.ui \
    lookupwindow.ui \
    pwdchangedlg.ui \
    exmanagedlg.ui \
    addexdlg.ui

DISTFILES += \
    .gitignore \
    dictionary.pro.user \
    LICENSE \
    README.md \
    Easy.txt \
    Extra.txt \
    Hard.txt \
    Lunatic.txt \
    Normal.txt \
    makefile \
    debug.log \
    userdatas.txt

RESOURCES += \
    image.qrc \
    buttons.qrc

CONFIG += C++11
