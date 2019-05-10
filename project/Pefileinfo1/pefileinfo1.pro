#-------------------------------------------------
#
# Project created by QtCreator 2018-11-29T21:58:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pefileinfo1
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
        main.cpp \
        dialog.cpp \
    dos.cpp \
    file.cpp \
    optional.cpp \
    section.cpp \
    import.cpp \
    other.cpp \
    export.cpp \
    relocation.cpp \
    dialog.cpp

HEADERS += \
        dialog.h \
    pe.h \
    class.h \
    dos.h \
    file.h \
    optional.h \
    section.h \
    import.h \
    other.h \
    export.h \
    relocation.h

FORMS += \
    dos.ui \
    file.ui \
    optional.ui \
    section.ui \
    import.ui \
    other.ui \
    export.ui \
    relocation.ui \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc

DISTFILES +=
