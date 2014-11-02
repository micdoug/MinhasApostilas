/* ----------------------------------------------------------------------
 * Arquivo: documentorepositorioqxorm.cpp
 * Descrição: Arquivo de implementação da classe Repositorios::DocumentoRepositorioQxOrm
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/
#include "documentorepositorioqxorm.h"
#include "QxDao/QxSqlDatabase.h"
#include <QSqlError>

/*!
 * \class Repositorios::DocumentoRepositorioQxOrm
 * Implementa um repositório para armazenamento de registros de objetos do tipo
 * Entidades::Documento utilizando a biblioteca QxOrm. Este repositório utiliza
 * conexão com o SGBD PostgreSql.
 * \see Entidades::Documento
 * \see Repositorios::IRepository
 */

namespace Repositorios {

/*!
 * Construtor do repositório. Ele recebe informações para acesso ao banco de dados PostgreSql.
 * \param usuario
 * Usuário de acesso ao banco de dados.
 * \param senha
 * Senha de acesso ao banco de dados.
 * \param banco
 * Nome do banco de dados a acessar.
 * \param server
 * Nome ou IP do servidor a acessar.
 * \param port
 * Número da porta de comunicação com o servidor.
 */
DocumentoRepositorioQxOrm::DocumentoRepositorioQxOrm(const QString &usuario, const QString &senha, const QString &banco, const QString &server, int port)
{
    qx::QxSqlDatabase::getSingleton()->setDriverName("QPSQL");
    qx::QxSqlDatabase::getSingleton()->setDatabaseName(banco);
    qx::QxSqlDatabase::getSingleton()->setUserName(usuario);
    qx::QxSqlDatabase::getSingleton()->setPassword(senha);
    qx::QxSqlDatabase::getSingleton()->setHostName(server);
    qx::QxSqlDatabase::getSingleton()->setPort(port);
}

/*!
 * Destrutor.
 */
DocumentoRepositorioQxOrm::~DocumentoRepositorioQxOrm()
{}

bool DocumentoRepositorioQxOrm::createObject(Entidades::Documento &object)
{
    QSqlError erro = qx::dao::insert(object);
    if(erro.type() == QSqlError::NoError)
    {
        return true;
    }
    else
    {
        ajustarMensagemErro("Ocorreu um erro ao tentar inserir um documento no banco de dados.", erro);
        return false;
    }
}

bool DocumentoRepositorioQxOrm::updateObject(Entidades::Documento &object)
{
    QSqlError erro = qx::dao::update(object);
    if(erro.type() == QSqlError::NoError)
    {
        return true;
    }
    else
    {
        ajustarMensagemErro("Ocorreu um erro ao tentar atualizar um documento no banco de dados.", erro);
        return false;
    }
}

bool DocumentoRepositorioQxOrm::deleteObject(Entidades::Documento &object)
{
    QSqlError erro = qx::dao::delete_by_id(object);
    if(erro.type() == QSqlError::NoError)
    {
        return true;
    }
    else
    {
        ajustarMensagemErro("Ocorreu um erro ao tentar deletar um documento no banco de dados.", erro);
        return false;
    }
}

bool DocumentoRepositorioQxOrm::selectObjects(QList<Entidades::Documento> &list, QMap<QString, QVariant> filters)
{
    QSqlError erro = qx::dao::fetch_by_query(construirWhereOrderByLimit(filters), list, nullptr, QStringList({"c_nome", "c_descricao", "c_ultimaalteracao", "c_versao"}));
    if(erro.type() == QSqlError::NoError)
    {
        return true;
    }
    else
    {
        ajustarMensagemErro("Ocorreu um erro ao pesquisar documentos no banco de dados.", erro);
        return false;
    }
}

bool DocumentoRepositorioQxOrm::countObjects(int &count, QMap<QString, QVariant> filters)
{
    filters.remove("limit");
    filters.remove("offset");
    filters.remove("codigoOrderBy");
    filters.remove("nomeOrderBy");
    filters.remove("descricaoOrderBy");
    filters.remove("ultimaAlteracaoOrderBy");
    filters.remove("versaoOrderBy");
    long temp = 0;
    QSqlError erro = qx::dao::count<Entidades::Documento>(temp, construirWhereOrderByLimit(filters));
    if(erro.type() == QSqlError::NoError)
    {
        count = (int)temp;
        return true;
    }
    else
    {
        ajustarMensagemErro("Ocorreu um erro ao tentar deletar um documento no banco de dados.", erro);
        return false;
    }
}

bool DocumentoRepositorioQxOrm::getObject(const QVariant &id, Entidades::Documento &object)
{
    object.setCodigo(id.toLongLong());
    QSqlError erro = qx::dao::fetch_by_id(object);
    if(erro.type() == QSqlError::NoError)
    {
        return true;
    }
    else
    {
        ajustarMensagemErro("Ocorreu um erro ao tentar recuperar um documento no banco de dados.", erro);
        return false;
    }
}

/*!
 * Método utilizado para ajustar a mensagem de erro.
 * \param prefixo
 * Texto que deve vir antes da mensagem de descrição de erro do banco de dados.
 * \param erro
 * Objeto com a descrição do erro.
 */
void DocumentoRepositorioQxOrm::ajustarMensagemErro(const QString &prefixo, const QSqlError &erro)
{
    setLastError(QString("Descrição: %1 \n"
                         "Mensagem do ORM: %2 \n")
                         .arg(prefixo)
                 .arg(erro.text()));
}

/*!
 * Constrói a estrutura de filtro específica da biblioteca QxOrm utilizando os filtros informados.
 * \param filters
 * Lista de filtros a ser utilizada.
 * \return
 * Estrutura de filtro da biblioteca QxOrm que poderá ser utilizado durante uma operação de pesquisa.
 */
qx::QxSqlQuery DocumentoRepositorioQxOrm::construirWhereOrderByLimit(QMap<QString, QVariant> filters)
{
    qx::QxSqlQuery where;

    //Verificando filtros para a propriedade código
    if(filters.contains("codigo="))
    {
        where.and_("c_codigo").isEqualTo(filters["codigo="]);
    }
    if(filters.contains("codigo>="))
    {
        where.and_("c_codigo").isGreaterThanOrEqualTo(filters["codigo>="]);
    }
    if(filters.contains("codigo<="))
    {
        where.and_("c_codigo").isLessThanOrEqualTo(filters["codigo<="]);
    }
    if(filters.contains("codigoOrderBy"))
    {
        if(filters["codigoOrderBy"].toString() == "asc")
        {
            where.orderAsc("c_codigo");
        }
        else
        {
            where.orderDesc("c_codigo");
        }
    }
    //Fim verificando filtros para a propriedade código

    //Verificando filtros para a propriedade nome
    if(filters.contains("nome="))
    {
        where.and_("c_nome").isEqualTo(filters["nome="]);
    }
    if(filters.contains("nomeContains"))
    {
        where.and_("c_nome").containsString(filters["nomeContains"].toString());
    }
    if(filters.contains("nomeStartsWith"))
    {
        where.and_("c_nome").startsWith(filters["nomeStartsWith"].toString());
    }
    if(filters.contains("nomeEndsWith"))
    {
        where.and_("c_nome").endsWith(filters["nomeEndsWith"].toString());
    }
    if(filters.contains("nomeOrderBy"))
    {
        if(filters["nomeOrderBy"].toString() == "asc")
        {
            where.orderAsc("c_nome");
        }
        else
        {
            where.orderDesc("c_nome");
        }
    }
    //Fim verificando filtros para a propriedade nome

    //Verificando filtros para a propriedade descricao
    if(filters.contains("descricao="))
    {
        where.and_("c_descricao").isEqualTo(filters["descricao="]);
    }
    if(filters.contains("descricaoContains"))
    {
        where.and_("c_descricao").containsString(filters["descricaoContains"].toString());
    }
    if(filters.contains("descricaoStartsWith"))
    {
        where.and_("c_descricao").startsWith(filters["descricaoStartsWith"].toString());
    }
    if(filters.contains("descricaoEndsWith"))
    {
        where.and_("c_descricao").endsWith(filters["descricaoEndsWith"].toString());
    }
    if(filters.contains("descricaoOrderBy"))
    {
        if(filters["descricaoOrderBy"].toString() == "asc")
        {
            where.orderAsc("c_descricao");
        }
        else
        {
            where.orderDesc("c_descricao");
        }
    }
    //Fim verificando filtros para a propriedade descricao

    //Verificando filtros para a propriedade código
    if(filters.contains("ultimaAlteracao="))
    {
        where.and_("c_ultimaalteracao").isEqualTo(filters["ultimaAlteracao="]);
    }
    if(filters.contains("ultimaAlteracao>="))
    {
        where.and_("c_ultimaalteracao").isGreaterThanOrEqualTo(filters["ultimaAlteracao>="]);
    }
    if(filters.contains("ultimaAlteracao<="))
    {
        where.and_("c_ultimaalteracao").isLessThanOrEqualTo(filters["ultimaAlteracao<="]);
    }
    if(filters.contains("ultimaAlteracaoOrderBy"))
    {
        if(filters["ultimaAlteracaoOrderBy"].toString() == "asc")
        {
            where.orderAsc("c_ultimaalteracao");
        }
        else
        {
            where.orderDesc("c_ultimaalteracao");
        }
    }
    //Fim verificando filtros para a propriedade código

    //Verificando filtros para a propriedade código
    if(filters.contains("versao="))
    {
        where.and_("c_versao").isEqualTo(filters["versao="]);
    }
    if(filters.contains("versao>="))
    {
        where.and_("c_versao").isGreaterThanOrEqualTo(filters["versao>="]);
    }
    if(filters.contains("versao<="))
    {
        where.and_("c_versao").isLessThanOrEqualTo(filters["versao<="]);
    }
    if(filters.contains("versaoOrderBy"))
    {
        if(filters["versaoOrderBy"].toString() == "asc")
        {
            where.orderAsc("c_versao");
        }
        else
        {
            where.orderDesc("c_versao");
        }
    }
    //Fim verificando filtros para a propriedade código

    if(filters.contains("limit"))
    {
        int offset = filters["offset"].toInt();
        where.limit(filters["limit"].toInt(), offset);
    }

    return where;
}

} // namespace Repositorios
