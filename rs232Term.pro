# -------------------------------------------------
# Project created by QtCreator 2010-01-16T17:05:36
# -------------------------------------------------

QT  += core gui serialport widgets printsupport
TARGET = rs232Term
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    dialogconfigport.cpp
HEADERS += mainwindow.h \
    dialogconfigport.h
FORMS += mainwindow.ui \
    dialogconfigport.ui
win32:RC_FILE = rs232Term.rc

RESOURCES += \
    rs232Term.qrc
