/* ----------------------------------------------------------------------
 * Arquivo: documentorepositorioorm4qt.h
 * Descrição: Arquivo de declaração da classe Repositorios::DocumentoRepositorioOrm4Qt
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#ifndef REPOSITORIOS_DOCUMENTOREPOSITORIOORM4QT_H
#define REPOSITORIOS_DOCUMENTOREPOSITORIOORM4QT_H

#include "../Entidades/documento.h"
#include "repository.h"
#include "where.h"
#include "orderbylist.h"
#include "irepository.h"

namespace Repositorios {

class DocumentoRepositorioOrm4Qt : public IRepository<Entidades::Documento>
{
public:
    DocumentoRepositorioOrm4Qt(Orm4Qt::Repository *repository);
    virtual ~DocumentoRepositorioOrm4Qt();

    //IRepository<Entidades::Documento> interface
public:
    bool createObject(Entidades::Documento &object) override;
    bool updateObject(Entidades::Documento &object) override;
    bool deleteObject(Entidades::Documento &object) override;
    bool selectObjects(QList<Entidades::Documento> &list, QMap<QString, QVariant> filters) override;
    bool countObjects(int &count, QMap<QString, QVariant> filters) override;
    bool getObject(const QVariant &id, Entidades::Documento &object) override;

private:
    //Repositório do orm orm4qt usado para executar operações no banco de dados
    Orm4Qt::Repository *m_repository;

    //Método utilizado para setar uma mensagem de erro padrão
    void ajustarMensagemErro(const QString &prefixo);
    //Método utilizado para montar a lista de where e orderby
    void montarWhereOrderBy(QMap<QString, QVariant> filters, Orm4Qt::Where &where, Orm4Qt::OrderByList &orderby);
};

} // namespace Repositorios

#endif // REPOSITORIOS_DOCUMENTOREPOSITORIOORM4QT_H
