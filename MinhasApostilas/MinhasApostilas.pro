#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T15:45:11
#
#-------------------------------------------------

QT       += core gui sql
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MinhasApostilas
TEMPLATE = app


SOURCES += main.cpp\
        janelaprincipal.cpp \
    Entidades/documento.cpp \
    Utils/inotifypropertychanged.cpp \
    Utils/ipropertygetset.cpp \
    Entidades/documentomodel.cpp \
    Repositorios/documentorepositorioorm4qt.cpp

HEADERS  += janelaprincipal.h \
    Entidades/documento.h \
    Utils/inotifypropertychanged.h \
    Utils/ipropertygetset.h \
    Entidades/documentomodel.h \
    Repositorios/irepository.h \
    Repositorios/documentorepositorioorm4qt.h

FORMS    += janelaprincipal.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Orm4Qt/release/ -lOrm4Qt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Orm4Qt/debug/ -lOrm4Qt
else:unix: LIBS += -L$$OUT_PWD/../Orm4Qt/ -lOrm4Qt

INCLUDEPATH += $$PWD/../Orm4Qt
DEPENDPATH += $$PWD/../Orm4Qt

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Orm4Qt/release/libOrm4Qt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Orm4Qt/debug/libOrm4Qt.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Orm4Qt/release/Orm4Qt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Orm4Qt/debug/Orm4Qt.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Orm4Qt/libOrm4Qt.a

#Escolher qual orm usar
DEFINES += ORM_ORM4QT
