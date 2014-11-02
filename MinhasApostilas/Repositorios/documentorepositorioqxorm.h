/* ----------------------------------------------------------------------
 * Arquivo: documentorepositorioqxorm.h
 * Descrição: Arquivo de declaração da classe Repositorios::DocumentoRepositorioQxOrm
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/
#ifndef REPOSITORIOS_DOCUMENTOREPOSITORIOQXORM_H
#define REPOSITORIOS_DOCUMENTOREPOSITORIOQXORM_H

#include "../Entidades/documento.h"
#include "irepository.h"
#include "QxDao/QxSqlQuery.h"

namespace Repositorios {

class DocumentoRepositorioQxOrm : public IRepository<Entidades::Documento>
{
public:
    DocumentoRepositorioQxOrm(const QString &usuario, const QString &senha, const QString &banco, const QString &server = "localhost", int port = 5432);
    virtual ~DocumentoRepositorioQxOrm();

    //IRepository<Entidades::Documento> interface
public:
    bool createObject(Entidades::Documento &object) override;
    bool updateObject(Entidades::Documento &object) override;
    bool deleteObject(Entidades::Documento &object) override;
    bool selectObjects(QList<Entidades::Documento> &list, QMap<QString, QVariant> filters) override;
    bool countObjects(int &count, QMap<QString, QVariant> filters) override;
    bool getObject(const QVariant &id, Entidades::Documento &object) override;

private:
    //Método utilizado para setar uma mensagem de erro padrão
    void ajustarMensagemErro(const QString &prefixo, const QSqlError &erro);
    //Método utilizado para montar a cláusula de restrição
    qx::QxSqlQuery construirWhereOrderByLimit(QMap<QString, QVariant> filters);
};

} // namespace Repositorios

#endif // REPOSITORIOS_DOCUMENTOREPOSITORIOQXORM_H
