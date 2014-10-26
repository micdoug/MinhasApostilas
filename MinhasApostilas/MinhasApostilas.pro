#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T15:45:11
#
#-------------------------------------------------

#Adicionando módulos do framework Qt que são utilizados no projeto
QT       += core gui sql concurrent

#Ativando suporte a especificação C++11
CONFIG += c++11

#Se a versão for Qt5 é necessário incluir o módulo widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#Nome do executável gerado
TARGET = MinhasApostilas

#Tipo de projeto "aplicativo"
TEMPLATE = app

#Arquivos de implementação
SOURCES += main.cpp\
        janelaprincipal.cpp \
    Entidades/documento.cpp \
    Utils/inotifypropertychanged.cpp \
    Utils/ipropertygetset.cpp \
    Entidades/documentomodel.cpp \
    Repositorios/documentorepositorioorm4qt.cpp \
    Utils/number.cpp \
    Formularios/editardocumento.cpp \
    Utils/lineeditcheckcase.cpp \
    Utils/texteditwatcher.cpp \
    Formularios/editarfiltros.cpp \
    Repositorios/documentorepositorioodb.cpp

#Arquivos de cabeçalho
HEADERS  += janelaprincipal.h \
    Entidades/documento.h \
    Utils/inotifypropertychanged.h \
    Utils/ipropertygetset.h \
    Entidades/documentomodel.h \
    Repositorios/irepository.h \
    Repositorios/documentorepositorioorm4qt.h \
    Utils/number.h \
    Formularios/editardocumento.h \
    Utils/lineeditcheckcase.h \
    Utils/texteditwatcher.h \
    Formularios/editarfiltros.h \
    Repositorios/documentorepositorioodb.h

#Arquivos de design de interface
FORMS    += janelaprincipal.ui \
    Formularios/editardocumento.ui \
    Formularios/editarfiltros.ui

#Corrigindo problema de referência para classes personalizadas de interface pelo uic (user interface compiler)
INCLUDEPATH += $$PWD/Formularios

#Incluindo arquivo de recursos
RESOURCES += \
    Recursos.qrc

#############################################################################################
################# Incluindo biblioteca estática da Orm4Qt  ##################################
#############################################################################################

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

#############################################################################################
################# Fim incluindo biblioteca estática da Orm4Qt  ##############################
#############################################################################################

#############################################################################################
################# Configurações para usar o ODB Orm  ########################################
#############################################################################################

#Adicionando dependencia de execução do odb compiler antes de compilar o projeto
#Desabilitando warnings de pragmas desconhecidos
unix: QMAKE_CXXFLAGS_WARN_ON = $$QMAKE_CXXFLAGS_WARN_ON -Wno-unknown-pragmas

#Lista de arquivos que devem ser compilados pelo odb compiler
ODB_FILES += Entidades/documento.h

#Flags do odb compiler
ODB_FLAGS = --database pgsql --profile qt --generate-query --std c++11

# Adicionando diretivas do linker para adicionar bibliotecas odb
LIBS += -lodb-pgsql -lodb-qt -lodb

#Adicionado diretório de headers do framework Qt ao comando do odb compiler
ODB_FLAGS += -I$$[QT_INSTALL_HEADERS] -I$$[QT_INSTALL_HEADERS]/QtCore

#Incluindo pastas onde entidades são definidas nas diretivas de compilação para o odb conseguir resolver as referências
INCLUDEPATH += ./Entidades

#Ajustando caminho dos arquivos a serem compilados
for(dir, ODB_FILES) {
  ODB_PWD_FILES += $$PWD/$${dir}
}

#Ajustando outras propriedades do comando odb compiler
odb.name = odb ${QMAKE_FILE_IN}
odb.input = ODB_PWD_FILES
odb.output = ${QMAKE_FILE_BASE}-odb.cxx
odb.commands = odb $$ODB_FLAGS ${QMAKE_FILE_IN}
odb.depends = $$ODB_PWD_FILES
odb.variable_out = SOURCES
odb.clean = ${QMAKE_FILE_BASE}-odb.cxx ${QMAKE_FILE_BASE}-odb.hxx ${QMAKE_FILE_BASE}-odb.ixx ${QMAKE_FILE_BASE}.sql
QMAKE_EXTRA_COMPILERS += odb

odbh.name = odb ${QMAKE_FILE_IN}
odbh.input = ODB_PWD_FILES
odbh.output = ${QMAKE_FILE_BASE}-odb.hxx
odbh.commands = @true
odbh.CONFIG = no_link
odbh.depends = ${QMAKE_FILE_BASE}-odb.cxx
QMAKE_EXTRA_COMPILERS += odbh

#############################################################################################
################# Fim configurações para usar o ODB Orm  ####################################
#############################################################################################

#Escolher qual orm usar
#DEFINES += ORM_ORM4QT
DEFINES += ORM_ODB

DEFINES += COMPILANDO
DEFINES += ORM4QT_DEBUG_SL
