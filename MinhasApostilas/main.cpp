#include "janelaprincipal.h"
#include <QApplication>

#ifdef ORM_ORM4QT
#include "Repositorios/documentorepositorioorm4qt.h"
#include "postgresqlprovider.h"
#endif

#ifdef ORM_ODB
#include "Repositorios/documentorepositorioodb.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef ORM_ORM4QT
    JanelaPrincipal w(new Repositorios::DocumentoRepositorioOrm4Qt(new Orm4Qt::Repository(new Orm4Qt::PostgreSqlProvider("postgres", "postgres", "MinhasApostilas"))));
#endif

#ifdef ORM_ODB
    JanelaPrincipal w(new Repositorios::DocumentoRepositorioODB("postgres", "postgres", "MinhasApostilas"));
#endif

    w.show();
    w.atualizar();
    return a.exec();
}
