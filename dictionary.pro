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
    test.cpp \
    usercontroller.cpp \
    wordcontroller.cpp \
    regdlg.cpp \
    wordnumdlg.cpp

HEADERS  += mainwindow.h \
    consts.h \
    controller.h \
    datacontroller.h \
    logging.h \
    logindlg.h \
    usercontroller.h \
    wordcontroller.h \
    regdlg.h \
    wordnumdlg.h

FORMS    += mainwindow.ui \
    logindlg.ui \
    regdlg.ui \
    wordnumdlg.ui

DISTFILES += \
    .gitignore \
    dictionary.pro.user \
    LICENSE \
    README.md
