#ifndef REPOSITORIOS_DOCUMENTOREPOSITORIOODB_H
#define REPOSITORIOS_DOCUMENTOREPOSITORIOODB_H

#include <string>
#include "irepository.h"
#include "../Entidades/documento.h"
#include <odb/database.hxx>
#include "documento-odb.hxx"

namespace Repositorios {

class DocumentoRepositorioODB : public IRepository<Entidades::Documento>
{
public:
    DocumentoRepositorioODB(std::string usuario, std::string senha, std::string banco, std::string server = "localhost", int port = 5432);
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

    //Método utilizado para montar a cláusula where
    odb::query<Entidades::Documento> *construirWhere(QMap<QString, QVariant> filters);
    //Método utilizado pra montar a cláusula orderby
    odb::query<Entidades::Documento> *construirOrderBy(QMap<QString,QVariant> filters);
    //Método utilizado para combinar a cláusula limit offset
    odb::query<Entidades::Documento> *construirLimitOffset(QMap<QString,QVariant> filters);
};

} // namespace Repositorios

#endif // REPOSITORIOS_DOCUMENTOREPOSITORIOODB_H
