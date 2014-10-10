#include "janelaprincipal.h"
#include <QApplication>

#ifdef ORM_ORM4QT
#include "Repositorios/documentorepositorioorm4qt.h"
#include "sqliteprovider.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef ORM_ORM4QT
    JanelaPrincipal w(new Repositorios::DocumentoRepositorioOrm4Qt(new Orm4Qt::Repository(new Orm4Qt::SqliteProvider("teste.sqlite"))));
#endif

    w.show();
    w.atualizar();
    return a.exec();
}
