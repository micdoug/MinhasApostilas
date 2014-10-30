/* ----------------------------------------------------------------------
 * Arquivo: documento.cpp
 * Descrição: Arquivo de implementação da classe Entidades::Documento.
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#include "documento.h"

/*!
 * \class Entidades::Documento
 * Representa um documento em pdf que é armazenado pela aplicação.
 * Os documentos são tratados na interface gráfica como apostilas.
 */

/*!
 * \struct Entidades::DocumentoInfo
 * Estrutura auxiliar utilizada para obter a quantidade de registros
 * atualmente no banco de dados utilizando a biblioteca ORM ODB.
 */

/*!
 * \variable Entidades::DocumentoInfo::quantidade
 * Quantidade de registros de documentos retornada pelo banco de dados
 * após aplicar uma consulta com filtros.
 */

/*!
 * \struct Entidades::DocumentoView
 * Estrutura auxiliar utilizada para exibir um conjunto de colunas
 * específico da tabela de documentos presente no banco de dados
 * utilizando a biblioteca ORM ODB.
 */

/*!
 * \variable Entidades::DocumentoView::codigo
 * Código de um documento.
*/

/*!
 * \variable Entidades::DocumentoView::descricao
 * Descrição de um documento.
*/

/*!
 * \variable Entidades::DocumentoView::nome
 * Nome de um documento.
*/

/*!
 * \variable Entidades::DocumentoView::ultimaAlteracao
 * Data/hora da última alteração de um documento.
*/

/*!
 * \ Entidades::DocumentoView::versao
 * Número da versão de um documento.
*/

/*!
 * Namespace base para a definição das funcionalidades da biblioteca
 * QxOrm.
 */
namespace qx
{
    /*!
     * Método criado para definir mapeamento da classe Entidades::Documento
     * utilizando a biblioteca ORM QxOrm.
     */
    template<> void register_class(QxClass<Entidades::Documento> &t)
    {
        t.setName("t_documento");
        t.id(&Entidades::Documento::m_codigo, "c_codigo");
        t.data(&Entidades::Documento::m_nome, "c_nome");
        t.data(&Entidades::Documento::m_descricao, "c_descricao");
        t.data(&Entidades::Documento::m_ultimaAlteracao, "c_ultimaalteracao");
        t.data(&Entidades::Documento::m_versao, "c_versao");
        t.data(&Entidades::Documento::m_arquivo, "c_arquivo");
    }
}


/*!
 * Engloba as classes e estruturas de dados utilizadas para representar
 * as entidades básicas do programa.
 */
namespace Entidades {

/*!
 * Construtor da classe. Inicializa o código do documento com o valor 0,
 * a data e hora da última alteração com a hora atual e versão com o valor
 * 1.
 */
Documento::Documento() :
    m_codigo(0L),
    m_ultimaAlteracao(QDateTime::currentDateTime()),
    m_versao(1)
{
    m_propriedades << "codigo"
                   << "nome"
                   << "descricao"
                   << "ultimaAlteracao"
                   << "versao"
                   << "arquivo";
}

/*!
 * Destrutor.
 */
Documento::~Documento()
{}

/*!
 * Código identificador único do documento.
 * \return
 * Valor atual do código.
 */
qlonglong Documento::codigo() const
{
    return m_codigo;
}

/*!
 * Ajusta o código do documento.
 * \param codigo
 * Novo valor para o código.
 */
void Documento::setCodigo(const qlonglong &codigo)
{
    if(codigo != m_codigo)
    {
        m_codigo = codigo;
        emitPropertyChanged("codigo", this->codigo());
    }
}

/*!
 * Nome do documento. Descrição breve da utilidade do documento.
 * \return
 * Valor atual do nome.
 */
QString Documento::nome() const
{
    return m_nome;
}

/*!
 * Ajusta o nome do documento.
 * \param nome
 * Novo valor para o nome.
 */
void Documento::setNome(const QString &nome)
{
    if(nome != m_nome)
    {
        m_nome = nome;
        emitPropertyChanged("nome", this->nome());
    }
}

/*!
 * Texto descritivo sobre o documento. Informação mais detalhada da utilidade do mesmo.
 * \return
 * Valor atual da descrição.
 */
QString Documento::descricao() const
{
    return m_descricao;
}

/*!
 * Ajusta a descrição do documento.
 * \param descricao
 * Novo valor para descrição.
 */
void Documento::setDescricao(const QString &descricao)
{
    if(descricao != m_descricao)
    {
        m_descricao = descricao;
        emitPropertyChanged("descricao", this->descricao());
    }
}

/*!
 * Data e hora em que o documento foi alterado pela última vez.
 * \return
 * Valor atual da ultimaAlteracao.
 */
QDateTime Documento::ultimaAlteracao() const
{
    return m_ultimaAlteracao;
}

/*!
 * Ajusta a data/hora da última alteração do documento.
 * \param ultimaAlteracao
 * Novo valor para ultimaAlteracao.
 */
void Documento::setUltimaAlteracao(const QDateTime &ultimaAlteracao)
{
    if(ultimaAlteracao != m_ultimaAlteracao)
    {
        m_ultimaAlteracao = ultimaAlteracao;
        emitPropertyChanged("ultimaAlteracao", this->ultimaAlteracao());
    }
}

/*!
 * Número de versão do documento armazenado.
 * \return
 * Valor atual da versão.
 */
quint16 Documento::versao() const
{
    return m_versao;
}

/*!
 * Ajusta a versão do documento.
 * \param versao
 * Novo valor para versão.
 */
void Documento::setVersao(const quint16 &versao)
{
    if(versao != m_versao)
    {
        m_versao = versao;
        emitPropertyChanged("versao", this->versao());
    }
}

/*!
 * Dados em binário do arquivo armazenado.
 * \return
 * Valor atual de arquivo.
 */
QByteArray Documento::arquivo() const
{
    return m_arquivo;
}

/*!
 * Ajusta os dados do arquivo armazenado.
 * \param arquivo
 * Novos dados para armazenar.
 */
void Documento::setArquivo(const QByteArray &arquivo)
{
    if(arquivo != m_arquivo)
    {
        m_arquivo = arquivo;
        emitPropertyChanged("arquivo", this->arquivo());
    }
}

bool Documento::setPropertyValue(const QString &propertyName, const QVariant &newValue)
{
    int index = m_propriedades.indexOf(propertyName);
    if(index > -1)
    {
        switch (index)
        {
            case 0:
                setCodigo(newValue.value<qlonglong>());
                return true;
            case 1:
                setNome(newValue.value<QString>());
                return true;
            case 2:
                setDescricao(newValue.value<QString>());
                return true;
            case 3:
                setUltimaAlteracao(newValue.value<QDateTime>());
                return true;
            case 4:
                setVersao(newValue.value<quint16>());
                return true;
            case 5:
                setArquivo(newValue.value<QByteArray>());
                return true;
        }
    }
    return false;
}

QVariant Documento::getPropertyValue(const QString &propertyName)
{
    int index = m_propriedades.indexOf(propertyName);
    if(index > -1)
    {
        switch(index)
        {
            case 0:
                return qVariantFromValue<qlonglong>(this->codigo());
            case 1:
                return qVariantFromValue<QString>(this->nome());
            case 2:
                return qVariantFromValue<QString>(this->descricao());
            case 3:
                return qVariantFromValue<QDateTime>(this->ultimaAlteracao());
            case 4:
                return qVariantFromValue<quint16>(this->versao());
            case 5:
                return qVariantFromValue<QByteArray>(this->arquivo());
        }
    }
    return QVariant();
}

void Documento::emitAllPropertiesChanged()
{
    emitPropertyChanged("codigo", this->codigo());
    emitPropertyChanged("nome", this->nome());
    emitPropertyChanged("descricao", this->descricao());
    emitPropertyChanged("ultimaAlteracao", this->ultimaAlteracao());
    emitPropertyChanged("versao", this->versao());
    emitPropertyChanged("arquivo", this->arquivo());
}

} // namespace Entidades
