#-------------------------------------------------
#
# Project created by QtCreator 2017-04-17T14:46:22
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BankSystem
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


SOURCES += main.cpp\
        mainwindow.cpp \
    customerlist.cpp \
    customerdetails.cpp \
    transactionlist.cpp \
    transactiondetails.cpp \
    dbmanager.cpp \
    objects.cpp \
    deletecustomer.cpp \
    accountlist.cpp \
    accountdelete.cpp \
    accountcreate.cpp

HEADERS  += mainwindow.h \
    customerlist.h \
    customerdetails.h \
    transactionlist.h \
    transactiondetails.h \
    dbmanager.h \
    objects.h \
    deletecustomer.h \
    accountlist.h \
    accountdelete.h \
    accountcreate.h

FORMS    += mainwindow.ui \
    customerlist.ui \
    customerdetails.ui \
    transactionlist.ui \
    transactiondetails.ui \
    deletecustomer.ui \
    accountlist.ui \
    accountdelete.ui \
    accountcreate.ui
