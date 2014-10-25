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

DocumentoRepositorioODB::DocumentoRepositorioODB(const QString &usuario, const QString &senha, const QString &banco, const QString &server, int port)
{
    m_database = new odb::pgsql::database(usuario.toStdString(), senha.toStdString(), banco.toStdString(), server.toStdString(), port);
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

        //Carregando registro atual do banco de dados e atualizando o valor dos atributos
        DocumentoPtr documento(m_database->load<Entidades::Documento>(object.codigo()));
        documento->setCodigo(object.codigo());
        documento->setNome(object.nome());
        documento->setDescricao(object.descricao());
        documento->setUltimaAlteracao(object.ultimaAlteracao());
        documento->setArquivo(object.arquivo());
        documento->setVersao(object.versao());

        //Atualizando registro no banco de dados
        m_database->update<Entidades::Documento>(*documento);

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
        Where w;
        montarWhereOrderBy(filters, w);
        //Efetuando pesquisa no banco de dados
        Result res(m_database->query<Entidades::Documento>(w));
        //Preenchendo lista com resultados
        for(Entidades::Documento doc : res)
        {
            list.append(Entidades::Documento(doc));
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
        Where w;
        montarWhereOrderBy(filters, w);
        //Efetuando pesquisa no banco de dados
        odb::result<Entidades::DocumentoInfo> res(m_database->query<Entidades::DocumentoInfo>(w));
        count = res.begin()->quantidade;

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

void DocumentoRepositorioODB::montarWhereOrderBy(QMap<QString, QVariant> filters, odb::query<Entidades::Documento> &where)
{
    QList<Where> whereList;
    QList<Where> orderbyList;

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
    if(filters.contains("codigoOrderBy"))
    {
        orderbyList.append(Where::codigo + filters["codigoOrderBy"].toString().toUpper().toStdString());
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
    if(filters.contains("nomeOrderBy"))
    {
        orderbyList.append(Where::nome + filters["nomeOrderBy"].toString().toUpper().toStdString());
    }
    //Fim verificando filtros para a propriedade nome

    //Verificando filtros para a propriedade descricao
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
    if(filters.contains("descricaoOrderBy"))
    {
        orderbyList.append(Where::descricao + filters["descricaoOrderBy"].toString().toUpper().toStdString());
    }
    //Fim verificando filtros para a propriedade descricao

    //Verificando filtros para a propriedade ultimaAlteracao
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
    if(filters.contains("ultimaAlteracaoOrderBy"))
    {
        orderbyList.append(Where::ultimaAlteracao + filters["ultimaAlteracaoOrderBy"].toString().toUpper().toStdString());
    }
    //Fim verificando filtros para a propriedade ultimaAlteracao

    //Verificando filtros para a propriedade versao
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
    if(filters.contains("versaoOrderBy"))
    {
        orderbyList.append(Where::versao + filters["versaoOrderBy"].toString().toUpper().toStdString());
    }
    //Fim verificando filtros para a propriedade versao

    if(!whereList.isEmpty())
    {
        where = whereList.first();
        for(int i = 1; i<whereList.size(); ++i)
        {
            where = where && whereList[i];
        }
    }

    //Adicionando cláusula orderby
    if(!orderbyList.isEmpty())
    {
        if(whereList.isEmpty())
        {
            where = "ORDER BY" + orderbyList.first();
        }
        else
        {
            where = where + "ORDER BY" + orderbyList.first();
        }
        for(int i = 1; i<orderbyList.size(); ++i)
        {
            where = where + orderbyList[i];
        }
    }

    //Adicionando limit e offset
//    if(filters.contains("limit"))
//    {
//        if(whereList.isEmpty() && !addOrderby)
//            where = "LIMIT" + Where::_val(filters["limit"].toInt()) + "OFFSET" + Where::_val(filters["offset"].toInt());
//        else
//            where = where + "LIMIT" + Where::_val(filters["limit"].toInt()) + "OFFSET" + Where::_val(filters["offset"].toInt());
//    }
}

} // namespace Repositorios
