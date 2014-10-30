#------------------------------------------------------------------
# Autor: Michael Dougras da Silva
# Contato: micdoug.silva@gmail.com
# Descrição: Arquivo de configuração do projeto Minhas Apostilas.
# Aplicativo com interface gráfica que permite cadastrar apostilas
# em PDF, armazenando os dados no SGBD PostgreSql. Projeto criado
# para comparar 3 bibliotecas ORM (QxOrm, ODB, Orm4Qt).
#------------------------------------------------------------------

# Adicionando módulos do framework Qt que são utilizados no projeto
QT += core gui sql concurrent widgets

# Ativando suporte a especificação C++11
CONFIG += c++11

# Nome do executável gerado
TARGET = MinhasApostilas

# Tipo de projeto "aplicativo"
TEMPLATE = app

# Arquivos de implementação
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
           Repositorios/documentorepositorioodb.cpp \
           Repositorios/documentorepositorioqxorm.cpp \
           Entidades/documento-odb.cxx

# Arquivos de cabeçalho
HEADERS  += janelaprincipal.h \
            Utils/inotifypropertychanged.h \
            Utils/ipropertygetset.h \
            Entidades/documentomodel.h \
            Entidades/documento.h \
            Repositorios/irepository.h \
            Repositorios/documentorepositorioorm4qt.h \
            Utils/number.h \
            Formularios/editardocumento.h \
            Utils/lineeditcheckcase.h \
            Utils/texteditwatcher.h \
            Formularios/editarfiltros.h \
            Repositorios/documentorepositorioodb.h \
            Repositorios/documentorepositorioqxorm.h \
            Entidades/documento-odb.hxx

# Arquivos de design de interface
FORMS += janelaprincipal.ui \
         Formularios/editardocumento.ui \
         Formularios/editarfiltros.ui

# Incluindo arquivo de recursos
RESOURCES += Recursos.qrc

# Incluindo arquivo inline gerado pelo compilador odb
OTHER_FILES += Entidades/documento-odb.ixx

# Corrigindo problema de referência para classes personalizadas de interface pelo uic (user interface compiler)
INCLUDEPATH += $$PWD/Formularios

#-----------------------------------------
# Configurando a biblioteca QxOrm
#-----------------------------------------

# Inclui arquivo de configuração do QxOrm
include(../QxOrm/QxOrm.pri)

# Inclui pasta de cabeçalhos
INCLUDEPATH += ../QxOrm/include \
               $$PWD/../QxOrm

# Define que a biblioteca QxOrm deve ser compilada antes deste projeto
DEPENDPATH += $$PWD/../QxOrm
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QxOrm/release/libQxOrm.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QxOrm/debug/libQxOrm.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QxOrm/release/QxOrm.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QxOrm/debug/QxOrm.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../QxOrm/libQxOrm.a

# Adicionando diretivas do linker para adicionar biblioteca QxOrm
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QxOrm/release -lQxOrm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QxOrm/debug/ -lQxOrm
else:unix: LIBS += -L$$OUT_PWD/../QxOrm/lib -lQxOrm

#-----------------------------------------
# Configurando a biblioteca ODB
#-----------------------------------------

# Inclui pasta de cabeçalhos no windows
# No linux elas já ficam em pastas padrões
win32:{
INCLUDEPATH += C:/Qt/Bibliotecas/libodb-2.3.0 \
               C:/Qt/Bibliotecas/libodb-pgsql-2.3.1 \
               C:/Qt/Bibliotecas/libodb-qt-2.3.1
}

# Adicionando diretivas do linker para adicionar bibliotecas odb
unix: LIBS += -lodb-pgsql -lodb-qt -lodb
win32:CONFIG(release, debug|release): LIBS += -lodb-pgsql -LC:/Qt/Bibliotecas/libodb-pgsql-2.3.1/lib64 \
                                              -lodb-qt -LC:/Qt/Bibliotecas/libodb-qt-2.3.1/lib64 \
                                              -lodb -LC:/Qt/Bibliotecas/libodb-2.3.0/lib64
else:win32:CONFIG(debug, debug|release): LIBS += -lodb-pgsql-d -LC:/Qt/Bibliotecas/libodb-pgsql-2.3.1/lib64 \
                                              -lodb-qt-d -LC:/Qt/Bibliotecas/libodb-qt-2.3.1/lib64 \
                                              -lodb-d -LC:/Qt/Bibliotecas/libodb-2.3.0/lib64

# Desabilitando warnings de pragmas desconhecidos
unix: QMAKE_CXXFLAGS_WARN_ON = $$QMAKE_CXXFLAGS_WARN_ON -Wno-unknown-pragmas

# Incluindo pasta de entidades para arquivos gerados pelo odb conseguirem resolver dependências
INCLUDEPATH += ./Entidades

#-----------------------------------------
# Configurando a biblioteca Orm4Qt
#-----------------------------------------

# Incluindo diretivas do linker para adicionar biblioteca Orm4Qt
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Orm4Qt/release/ -lOrm4Qt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Orm4Qt/debug/ -lOrm4Qt
else:unix: LIBS += -L$$OUT_PWD/../Orm4Qt/ -lOrm4Qt

# Inclui pastas de cabeçalhos
INCLUDEPATH += $$PWD/../Orm4Qt

# Define que a biblioteca Orm4Qt deve ser compilada antes deste projeto
DEPENDPATH += $$PWD/../Orm4Qt
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Orm4Qt/release/libOrm4Qt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Orm4Qt/debug/libOrm4Qt.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Orm4Qt/release/Orm4Qt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Orm4Qt/debug/Orm4Qt.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Orm4Qt/libOrm4Qt.a

# Ativando modo debug Sql
DEFINES += ORM4QT_DEBUG_SL
