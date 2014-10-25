#ifndef REPOSITORIOS_DOCUMENTOREPOSITORIOODB_H
#define REPOSITORIOS_DOCUMENTOREPOSITORIOODB_H

#include <QString>

#include "irepository.h"
#include "../Entidades/documento.h"
#include <odb/database.hxx>
#include "documento-odb.hxx"

namespace Repositorios {

class DocumentoRepositorioODB : public IRepository<Entidades::Documento>
{
public:
    DocumentoRepositorioODB(const QString &usuario, const QString &senha, const QString &banco, const QString &server = "localhost", int port = 5432);
    virtual ~DocumentoRepositorioODB();

    //IRepository<Entidades::Documento> interface
public:
    bool createObject(Entidades::Documento &object) override;
    bool updateObject(Entidades::Documento &object) override;
    bool deleteObject(Entidades::Documento &object) override;
    bool selectObjects(QList<Entidades::Documento> &list, QMap<QString, QVariant> filters) override;
    bool countObjects(int &count, QMap<QString, QVariant> filters) override;
    bool getObject(const QVariant &id, Entidades::Documento &object) override;

private:
    odb::database *m_database;

    //Método utilizado para montar a lista de where e orderby
    void montarWhereOrderBy(QMap<QString, QVariant> filters, odb::query<Entidades::Documento> &where);
};

} // namespace Repositorios

#endif // REPOSITORIOS_DOCUMENTOREPOSITORIOODB_H