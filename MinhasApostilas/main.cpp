#include "janelaprincipal.h"
#include <QApplication>
#include <QInputDialog>

#include "Repositorios/documentorepositorioorm4qt.h"
#include "postgresqlprovider.h"

#include "Repositorios/documentorepositorioodb.h"
#include "Repositorios/documentorepositorioqxorm.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JanelaPrincipal *w = nullptr;


    bool escolheu = false;
    QString escolha;
    while(!escolheu)
        escolha = QInputDialog::getItem(nullptr, "Biblioteca ORM utilizada", "Escolha qual biblioteca ORM deseja utilizar", QStringList({"ODB", "Orm4Qt", "QxORM"}), 0, false, &escolheu);

    if(escolha == "ODB")
        w = new JanelaPrincipal(new Repositorios::DocumentoRepositorioODB("postgres", "postgres", "MinhasApostilas"));
    else if(escolha == "Orm4Qt")
        w = new JanelaPrincipal(new Repositorios::DocumentoRepositorioOrm4Qt(new Orm4Qt::Repository(new Orm4Qt::PostgreSqlProvider("postgres", "postgres", "MinhasApostilas"))));
    else
        w = new JanelaPrincipal(new Repositorios::DocumentoRepositorioQxOrm("postgres", "postgres", "MinhasApostilas"));

    w->show();
    w->atualizar();
    return a.exec();
}
