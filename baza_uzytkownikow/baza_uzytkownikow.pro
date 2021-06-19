QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    State.cpp \
    contactgroupshare.cpp \
    database.cpp \
    invitation.cpp \
    main.cpp \
    mainwindow.cpp \
    sha1.cpp \
    userdashboard.cpp \
    userview.cpp

HEADERS += \
    Message.h \
    State.h \
    config.h \
    contactgroupshare.h \
    database.h \
    invitation.h \
    mainwindow.h \
    model.h \
    sha1.h \
    userdashboard.h \
    userview.h

FORMS += \
    contactgroupshare.ui \
    invitation.ui \
    mainwindow.ui \
    userdashboard.ui \
    userview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    CMakeLists.txt.user \
    baza_uzytkownikow.pro.user
