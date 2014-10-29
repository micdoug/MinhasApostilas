#include "documentorepositorioodb.h"
#include <odb/pgsql/database.hxx>
#include <odb/core.hxx>
#include <odb/transaction.hxx>
#include <memory>

//Apelidos para tipos que serão muito utilizados
typedef odb::query<Entidades::Documento> Where;
typedef odb::result<Entidades::Documento> Result;
typedef std::unique_ptr<Entidades::Documento> DocumentoPtr;

using namespace odb::core;

namespace Repositorios {

DocumentoRepositorioODB::DocumentoRepositorioODB(std::string usuario, std::string senha, std::string banco, std::string server, int port)
{
    m_database = new odb::pgsql::database(usuario, senha, banco, server, port);
    //m_database = new odb::pgsql::database("postgres", "postgres", "MinhasApostilas");
}

DocumentoRepositorioODB::~DocumentoRepositorioODB()
{
    delete m_database;
}

bool DocumentoRepositorioODB::createObject(Entidades::Documento &object)
{
    try
    {
        //Criando transação
        transaction t(m_database->begin());
        //Ativando debug
        t.tracer(stderr_tracer);

        m_database->persist<Entidades::Documento>(object);
        t.commit();
        return true;
    }
    catch (const odb::exception& exception)
    {
        setLastError(QString("%1 \n Erro: %2").arg("Ocorreu um erro ao tentar adicionar um novo documento.").arg(exception.what()));
        return false;
    }
}

bool DocumentoRepositorioODB::updateObject(Entidades::Documento &object)
{
    try
    {
        //Criando transação
        transaction t(m_database->begin());
        //Ativando debug
        t.tracer(stderr_tracer);

        //Atualizando registro no banco de dados
        m_database->update<Entidades::Documento>(object);

        //Concluindo transação
        t.commit();

        return true;
    }
    //Capturando erros
    catch (const odb::exception& exception)
    {
        setLastError(QString("%1 \n Erro: %2").arg("Ocorreu um erro ao tentar atualizar um documento.").arg(exception.what()));
        return false;
    }
}

bool DocumentoRepositorioODB::deleteObject(Entidades::Documento &object)
{
    try
    {
        //Criando transação
        transaction t(m_database->begin());
        //Ativando debug
        t.tracer(stderr_tracer);

        //Deletando registro do banco de dados
        m_database->erase<Entidades::Documento>(object.codigo());

        //Concluindo transação
        t.commit();

        return true;
    }
    //Capturando erros
    catch (const odb::exception& exception)
    {
        setLastError(QString("%1 \n Erro: %2").arg("Ocorreu um erro ao tentar deletar um documento.").arg(exception.what()));
        return false;
    }
}

bool DocumentoRepositorioODB::selectObjects(QList<Entidades::Documento> &list, QMap<QString, QVariant> filters)
{
    try
    {
        //Criando transação
        transaction t(m_database->begin());
        //Ativando debug
        t.tracer(stderr_tracer);

        //Construindo cláusula where e orderby
        std::unique_ptr<Where> where(construirWhere(filters));
        std::unique_ptr<Where> orderby(construirOrderBy(filters));
        std::unique_ptr<Where> limitOffset(construirLimitOffset(filters));

        odb::result<Entidades::DocumentoView> resultado;
        if(where != nullptr)
        {
            Where filtro = *where;
            if(orderby != nullptr)
            {
                filtro = filtro + (*orderby);
            }
            if(limitOffset != nullptr)
            {
                filtro = filtro + (*limitOffset);
            }
            resultado = m_database->query<Entidades::DocumentoView>(filtro);
        }
        else if(orderby != nullptr)
        {
            Where filtro = "true" + (*orderby);
            if(limitOffset != nullptr)
            {
                filtro = filtro + (*limitOffset);
            }
            resultado = m_database->query<Entidades::DocumentoView>(filtro);
        }
        else if(limitOffset != nullptr)
        {
            resultado = m_database->query<Entidades::DocumentoView>("true"+(*limitOffset));
        }
        else
        {
            resultado = m_database->query<Entidades::DocumentoView>();
        }

        //Preenchendo lista com resultados
        for(Entidades::DocumentoView docview : resultado)
        {
            Entidades::Documento doc;
            doc.setCodigo(docview.codigo);
            doc.setNome(docview.nome);
            doc.setDescricao(docview.descricao);
            doc.setUltimaAlteracao(docview.ultimaAlteracao);
            doc.setVersao(docview.versao);
            list.append(doc);
        }

        //Concluindo transação
        t.commit();

        return true;
    }
    //Capturando erros
    catch (const odb::exception& exception)
    {
        setLastError(QString("%1 \n Erro: %2").arg("Ocorreu um erro ao tentar pesquisar documentos.").arg(exception.what()));
        return false;
    }
}

bool DocumentoRepositorioODB::countObjects(int &count, QMap<QString, QVariant> filters)
{
    try
    {
        //Criando transação
        transaction t(m_database->begin());
        //Ativando debug
        t.tracer(stderr_tracer);

        //Construindo cláusula where e orderby
        std::unique_ptr<Where> where(construirWhere(filters));
        odb::result<Entidades::DocumentoInfo> resultado;
        if(where != nullptr)
        {
            resultado = m_database->query<Entidades::DocumentoInfo>(*where);
        }
        else
        {
            resultado = m_database->query<Entidades::DocumentoInfo>();
        }

        count = resultado.begin()->quantidade;

        //Concluindo transação
        t.commit();

        return true;
    }
    //Capturando erros
    catch (const odb::exception& exception)
    {
        setLastError(QString("%1 \n Erro: %2").arg("Ocorreu um erro ao tentar pesquisar documentos.").arg(exception.what()));
        return false;
    }
}

bool DocumentoRepositorioODB::getObject(const QVariant &id, Entidades::Documento &object)
{
    try
    {
        //Criando transação
        transaction t(m_database->begin());
        //Ativando debug
        t.tracer(stderr_tracer);

        //Buscando objeto no banco de dados a partir do id
        DocumentoPtr temp =  m_database->load<Entidades::Documento>(id.toLongLong());
        object = Entidades::Documento(*temp);

        //Concluindo transação
        t.commit();

        return true;
    }
    //Capturando erros
    catch (const odb::exception& exception)
    {
        setLastError(QString("%1 \n Erro: %2").arg("Ocorreu um erro ao tentar deletar um documento.").arg(exception.what()));
        return false;
    }
}

odb::query<Entidades::Documento> *DocumentoRepositorioODB::construirWhere(QMap<QString, QVariant> filters)
{
    QList<Where> whereList;

    //Verificando filtros para a propriedade código
    if(filters.contains("codigo="))
    {
        whereList.append(Where::codigo == Where::_val(filters["codigo="].toLongLong()));
    }
    if(filters.contains("codigo>="))
    {
        whereList.append(Where::codigo >= Where::_val(filters["codigo>="].toLongLong()));
    }
    if(filters.contains("codigo<="))
    {
        whereList.append(Where::codigo <= Where::_val(filters["codigo<="].toLongLong()));
    }
    //Fim verificando filtros para a propriedade código

    //Verificando filtros para a propriedade nome
    if(filters.contains("nome="))
    {
        whereList.append(Where::nome == Where::_val(filters["nome="].toString()));
    }
    if(filters.contains("nomeContains"))
    {
        whereList.append(Where::nome.like("%"+filters["nomeContains"].toString()+"%"));
    }
    if(filters.contains("nomeStartsWith"))
    {
        whereList.append(Where::nome.like(filters["nomeStartsWith"].toString()+"%"));
    }
    if(filters.contains("nomeEndsWith"))
    {
        whereList.append(Where::nome.like("%"+filters["nomeEndsWith"].toString()));
    }
    //Fim verificando filtros para a propriedade nome

    //Verificando filtros para a propriedade descrição
    if(filters.contains("descricao="))
    {
        whereList.append(Where::descricao == Where::_val(filters["descricao="].toString()));
    }
    if(filters.contains("descricaoContains"))
    {
        whereList.append(Where::descricao.like("%"+filters["descricaoContains"].toString()+"%"));
    }
    if(filters.contains("descricaoStartsWith"))
    {
        whereList.append(Where::descricao.like(filters["descricaoStartsWith"].toString()+"%"));
    }
    if(filters.contains("descricaoEndsWith"))
    {
        whereList.append(Where::descricao.like("%"+filters["descricaoEndsWith"].toString()));
    }
    //Fim verificando filtros para a propriedade descrição

    //Verificando filtros para a propriedade ultima alteração
    if(filters.contains("ultimaAlteracao="))
    {
        whereList.append(Where::ultimaAlteracao == Where::_val(filters["ultimaAlteracao="].toDateTime()));
    }
    if(filters.contains("ultimaAlteracao>="))
    {
        whereList.append(Where::ultimaAlteracao >= Where::_val(filters["ultimaAlteracao>="].toDateTime()));
    }
    if(filters.contains("ultimaAlteracao<="))
    {
        whereList.append(Where::ultimaAlteracao <= Where::_val(filters["ultimaAlteracao<="].toDateTime()));
    }
    //Fim verificando filtros para a propriedade ultima alteração

    //Verificando filtros para a propriedade versão
    if(filters.contains("versao="))
    {
        whereList.append(Where::versao == Where::_val(filters["versao="].value<quint16>()));
    }
    if(filters.contains("versao>="))
    {
        whereList.append(Where::versao >= Where::_val(filters["versao>="].value<quint16>()));
    }
    if(filters.contains("versao<="))
    {
        whereList.append(Where::versao <= Where::_val(filters["versao<="].value<quint16>()));
    }
    //Fim verificando filtros para a propriedade versão

    //Verificando se é necessário montar objeto de pesquisa
    if(whereList.isEmpty())
    {
        return nullptr;
    }
    else
    {
        Where where = whereList.first();
        //Combinando clásulas where
        for(int i = 1; i<whereList.size(); ++i)
        {
            where = where && whereList[i];
        }
        return new Where(where);
    }
}

odb::query<Entidades::Documento> *DocumentoRepositorioODB::construirOrderBy(QMap<QString, QVariant> filters)
{
    QList<Where> orderbyList;

    //Verificando ordenação para a propriedade código
    if(filters.contains("codigoOrderBy"))
    {
        orderbyList.append(Where::codigo + filters["codigoOrderBy"].toString().toUpper().toStdString());
    }

    //Verificando ordenação para a propriedade nome
    if(filters.contains("nomeOrderBy"))
    {
        orderbyList.append(Where::nome + filters["nomeOrderBy"].toString().toUpper().toStdString());
    }

    //Verificando ordenação para a propriedade descrição
    if(filters.contains("descricaoOrderBy"))
    {
        orderbyList.append(Where::descricao + filters["descricaoOrderBy"].toString().toUpper().toStdString());
    }

    //Verificando ordenação para a propriedade última alteração
    if(filters.contains("ultimaAlteracaoOrderBy"))
    {
        orderbyList.append(Where::ultimaAlteracao + filters["ultimaAlteracaoOrderBy"].toString().toUpper().toStdString());
    }

    //Verificando ordenação para a propriedade versão
    if(filters.contains("versaoOrderBy"))
    {
        orderbyList.append(Where::versao + filters["versaoOrderBy"].toString().toUpper().toStdString());
    }

    //Verificando se é necessário montar cláusula
    if(orderbyList.isEmpty())
    {
        return nullptr;
    }
    else
    {
        Where where = "ORDER BY" + orderbyList.first();
        //Combinando cláusulas orderby
        for(int i = 1; i<orderbyList.size(); ++i)
        {
            where = where + orderbyList[i];
        }
        return new Where(where);
    }

}

odb::query<Entidades::Documento> *DocumentoRepositorioODB::construirLimitOffset(QMap<QString, QVariant> filters)
{
    //Adicionando limit e offset
    if(filters.contains("limit"))
    {
        return new Where("LIMIT" + Where::_val(filters["limit"].toInt()) + "OFFSET" + Where::_val(filters["offset"].toInt()));
    }
    else
    {
        return nullptr;
    }
}

} // namespace Repositorios
