#include "documentorepositorioorm4qt.h"

namespace Repositorios {

DocumentoRepositorioOrm4Qt::DocumentoRepositorioOrm4Qt(const Orm4Qt::Repository &repository) :
    m_repository(repository)
{}

DocumentoRepositorioOrm4Qt::~DocumentoRepositorioOrm4Qt()
{}

bool DocumentoRepositorioOrm4Qt::createObject(Entidades::Documento &object)
{
    //Assegura que o objeto será criado novamente no banco e não atualizado
    object.reflection()->replaceTag("scope", Orm4Qt::Local);
    if(m_repository.saveObject<Entidades::Documento>(object))
    {
        return true;
    }
    else
    {
        ajustarMensagemErro("Erro ao criar novo registro de documento no banco de dados.");
        return false;
    }
}

bool DocumentoRepositorioOrm4Qt::updateObject(Entidades::Documento &object)
{
    //Assegura que o objeto será atualizado e não criado novamente no banco de dados
    object.reflection()->replaceTag("scope", Orm4Qt::Remote);
    if(m_repository.saveObject<Entidades::Documento>(object))
    {
        return true;
    }
    else
    {
        ajustarMensagemErro("Erro ao atualizar registro de documento no banco de dados.");
        return false;
    }
}

bool DocumentoRepositorioOrm4Qt::deleteObject(Entidades::Documento &object)
{
    //Assegura que o objeto existe no banco de dados
    object.reflection()->replaceTag("scope", Orm4Qt::Remote);
    if(m_repository.deleteObject<Entidades::Documento>(object))
    {
        return true;
    }
    else
    {
        ajustarMensagemErro("Erro ao deletar registro de documento no banco de dados.");
        return false;
    }
}

bool DocumentoRepositorioOrm4Qt::selectObjects(QList<Entidades::Documento> &list, QMap<QString, QVariant> filters)
{
    //Construindo sentenças where e orderby
    Orm4Qt::Where where;
    Orm4Qt::OrderByList orderby;
    montarWhereOrderBy(filters, where, orderby);
    //Fim construindo sentenças where e orderby

    //Efetuando a consulta
    if(m_repository.select<Entidades::Documento>(list,
                                                 where.joined() != nullptr ? *where.joined() : where,
                                                 QStringList({"codigo", "nome", "descricao", "ultimaAlteracao", "versao"}),
                                                 orderby,
                                                 filters["limit"].toInt(),
                                                 filters["offset"].toInt()))
    {
        return true;
    }
    else
    {
        ajustarMensagemErro("Erro ao pesquisar registros de documentos no banco de dados");
        return false;
    }

}

bool DocumentoRepositorioOrm4Qt::countObjects(int &count, QMap<QString, QVariant> filters)
{
    //Construindo sentenças where e orderby
    Orm4Qt::Where where;
    Orm4Qt::OrderByList orderby;
    montarWhereOrderBy(filters, where, orderby);
    //Fim construindo sentenças where e orderby

    //Efetuando a consulta
    if(m_repository.count<Entidades::Documento>(count,where.joined() != nullptr ? *where.joined() : where))
    {
        return true;
    }
    else
    {
        ajustarMensagemErro("Erro ao pesquisar registros de documentos no banco de dados");
        return false;
    }
}

bool DocumentoRepositorioOrm4Qt::getObject(const QVariant &id, Entidades::Documento &object)
{
    QList<Entidades::Documento> list;
    if(m_repository.select<Entidades::Documento>(list, Orm4Qt::Where("codigo", Orm4Qt::Equals, {id})))
    {
        if(list.empty())
        {
            ajustarMensagemErro(QString("Não foi encontrado um documento no banco de dados com id '%1'.").arg(id.toLongLong()));
        }
        else
        {
            object = Entidades::Documento(list.first());
            return true;
        }
    }
    else
    {
        ajustarMensagemErro("Erro ao pesquisar registro de documento no banco de dados.");
    }

    return false;
}

void DocumentoRepositorioOrm4Qt::ajustarMensagemErro(const QString &prefixo)
{
    setLastError(QString("Descrição: %1 \n"
                         "Mensagem do ORM: %2 \n"
                         "Mensagem do banco de dados: %3")
                         .arg(prefixo)
                         .arg(m_repository.lastError()->description())
                         .arg(m_repository.lastError()->sqlError().text()));
}

void DocumentoRepositorioOrm4Qt::montarWhereOrderBy(QMap<QString, QVariant> filters, Orm4Qt::Where &where, Orm4Qt::OrderByList &orderby)
{
    //Verificando filtros para a propriedade código
    if(filters.contains("codigo="))
    {
        where.And("codigo", Orm4Qt::Equals,  {filters["codigo="]});
    }
    if(filters.contains("codigo>="))
    {
        where.And("codigo", Orm4Qt::GreaterEquals, {filters["codigo>="]});
    }
    if(filters.contains("codigo<="))
    {
        where.And("codigo", Orm4Qt::LessEquals, {filters["codigo<="]});
    }
    if(filters.contains("codigoOrderBy"))
    {
        orderby.add("codigo",
                    filters["codigoOrderBy"].toString() == "asc" ? Orm4Qt::Asc : Orm4Qt::Desc);
    }
    //Fim verificando filtros para a propriedade código

    //Verificando filtros para a propriedade nome
    if(filters.contains("nome="))
    {
        where.And("nome", Orm4Qt::Equals, {filters["nome="]});
    }
    if(filters.contains("nomeContains"))
    {
        where.And("nome", Orm4Qt::Contains, {filters["nomeContains"]});
    }
    if(filters.contains("nomeStartsWith"))
    {
        where.And("nome", Orm4Qt::StartsWith, {filters["nomeStartsWith"]});
    }
    if(filters.contains("nomeEndsWith"))
    {
        where.And("nome", Orm4Qt::EndsWith, {filters["nomeEndsWith"]});
    }
    if(filters.contains("nomeOrderBy"))
    {
        orderby.add("nome",
                    filters["nomeOrderBy"].toString() == "asc" ? Orm4Qt::Asc : Orm4Qt::Desc);
    }
    //Fim verificando filtros para a propriedade nome

    //Verificando filtros para a propriedade descricao
    if(filters.contains("descricao="))
    {
        where.And("descricao", Orm4Qt::Equals, {filters["descricao="]});
    }
    if(filters.contains("descricaoContains"))
    {
        where.And("descricao", Orm4Qt::Contains, {filters["descricaoContains"]});
    }
    if(filters.contains("descricaoStartsWith"))
    {
        where.And("descricao", Orm4Qt::StartsWith, {filters["descricaoStartsWith"]});
    }
    if(filters.contains("descricaoEndsWith"))
    {
        where.And("descricao", Orm4Qt::EndsWith, {filters["descricaoEndsWith"]});
    }
    if(filters.contains("descricaoOrderBy"))
    {
        orderby.add("descricao",
                    filters["descricaoOrderBy"].toString() == "asc" ? Orm4Qt::Asc : Orm4Qt::Desc);
    }
    //Fim verificando filtros para a propriedade descricao

    //Verificando filtros para a propriedade código
    if(filters.contains("ultimaAlteracao="))
    {
        where.And("ultimaAlteracao", Orm4Qt::Equals,  {filters["ultimaAlteracao="]});
    }
    if(filters.contains("ultimaAlteracao>="))
    {
        where.And("ultimaAlteracao", Orm4Qt::GreaterEquals, {filters["ultimaAlteracao>="]});
    }
    if(filters.contains("ultimaAlteracao<="))
    {
        where.And("ultimaAlteracao", Orm4Qt::LessEquals, {filters["ultimaAlteracao<="]});
    }
    if(filters.contains("ultimaAlteracaoOrderBy"))
    {
        orderby.add("ultimaAlteracao",
                    filters["ultimaAlteracaoOrderBy"].toString() == "asc" ? Orm4Qt::Asc : Orm4Qt::Desc);
    }
    //Fim verificando filtros para a propriedade código

    //Verificando filtros para a propriedade código
    if(filters.contains("versao="))
    {
        where.And("versao", Orm4Qt::Equals,  {filters["versao="]});
    }
    if(filters.contains("versao>="))
    {
        where.And("versao", Orm4Qt::GreaterEquals, {filters["versao>="]});
    }
    if(filters.contains("versao<="))
    {
        where.And("versao", Orm4Qt::LessEquals, {filters["versao<="]});
    }
    if(filters.contains("versaoOrderBy"))
    {
        orderby.add("versao",
                    filters["versaoOrderBy"].toString() == "asc" ? Orm4Qt::Asc : Orm4Qt::Desc);
    }
    //Fim verificando filtros para a propriedade código
}

} // namespace Repositorios
