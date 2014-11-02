/* ----------------------------------------------------------------------
 * Arquivo: irepository.h
 * Descrição: Arquivo de declaração da classe abstrata Repositorios::IRepository.
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#ifndef REPOSITORIES_IREPOSITORY_H
#define REPOSITORIES_IREPOSITORY_H

#include <QList>
#include <QMap>
#include <QString>
#include <QVariant>

/*!
 * Engloba todas as estruturas que implementam operações de armazenamento de registros
 * de objetos no banco de dados, utilizando bibliotecas de mapeamento objeto relacional.
 */
namespace Repositorios {

    /*!
     * Interface básica para armazenamento e pesquisa de registros de objetos no banco de dados.
     */
    template<class T> class IRepository
    {
    public:
        /*!
         * Construtor.
         */
        IRepository(){}
        /*!
         * Destrutor.
         */
        virtual ~IRepository(){}

        /*!
         * Retorna um texto com a descrição do último erro ocorrido.
         * \return
         * Texto com descrição do último erro.
         */
        QString lastError() const
        {
            return m_lastError;
        }

        /*!
         * Cria um novo registro para armazenamento dos dados de um objeto no banco de dados.
         * \param object
         * Objeto a ser persistido.
         * \return
         * Se a operação foi bem sucedida.
         */
        virtual bool createObject(T &object) = 0;
        /*!
         * Atualiza o registro de armazenamento deste objeto no banco de dados com as novas informações
         * do objeto informado.
         * \param object
         * Objeto a ser atualizado no banco de dados.
         * \return
         * Se a operação foi bem sucedida.
         */
        virtual bool updateObject(T &object) = 0;
        /*!
         * Deleta o registro de armazenamento de um objeto no banco de dados.
         * \param object
         * Objeto a ser deletado no banco de dados.
         * \return
         * Se a operação foi bem sucedida.
         */
        virtual bool deleteObject(T &object) = 0;
        /*!
         * Seleciona uma lista de objetos do banco de dados que obedecem os filtros informados.
         * \param list
         * A lista a ser preenchida com os registros encontrados.
         * \param filters
         * Lista de filtros a serem utilizados. Para informar filtros você deve adicionar elementos
         * seguindo o padrão "nomePropriedade=" (valor da propriedade é exatamente igual ao valor informado),
         * "nomePropriedade>=" (valor da propriedade é maior ou igual), "nomePropriedade<=" (valor da propriedade
         * é menor ou igual), "nomePropriedadeContains" (valor de propriedade em string contém o trecho informado),
         * "nomePropriedadeStartsWith" (valor de propriedade em string começa com o trecho informado),
         * "nomePropriedadeEndsWith" (valor de propriedade em string termina com o trecho informado),
         * "nomePropriedadeOrderBy" (ordernar a propriedade informada em ordem crescente quando valor é "asc" ou em
         * ordem decrescente quando o valor é "desc".
         * \return
         * Se a operação foi bem sucedida.
         */
        virtual bool selectObjects(QList<T> &list, QMap<QString, QVariant> filters) = 0;
        /*!
         * Retorna a quantidade de registros de objetos no banco de dados que obedecem os filtros informados.
         * \param count
         * Variável a ser preenchida com o valor de contagem encontrado.
         * \param filters
         * Lista de filtros a serem utilizados. Para informar filtros você deve adicionar elementos
         * seguindo o padrão "nomePropriedade=" (valor da propriedade é exatamente igual ao valor informado),
         * "nomePropriedade>=" (valor da propriedade é maior ou igual), "nomePropriedade<=" (valor da propriedade
         * é menor ou igual), "nomePropriedadeContains" (valor de propriedade em string contém o trecho informado),
         * "nomePropriedadeStartsWith" (valor de propriedade em string começa com o trecho informado),
         * "nomePropriedadeEndsWith" (valor de propriedade em string termina com o trecho informado),
         * "nomePropriedadeOrderBy" (ordernar a propriedade informada em ordem crescente quando valor é "asc" ou em
         * ordem decrescente quando o valor é "desc".
         * \return
         * Se a operação foi bem sucedida.
         */
        virtual bool countObjects(int &count, QMap<QString, QVariant> filters) = 0;
        /*!
         * Pesquisa um registro específico do banco de dados a partir do id informado.
         * \param id
         * Identificador único do registro procurado.
         * \param object
         * Objeto a ser preenchido com o registro informado.
         * \return
         * Se a operação foi bem sucedida.
         */
        virtual bool getObject(const QVariant &id, T &object) = 0;

    protected:
        /*!
         * Ajusta o texto do último erro.
         * \param error
         * Texto descritivo do erro.
         */
        void setLastError(const QString &error)
        {
            m_lastError = error;
        }

    private:
        QString m_lastError;

    };

} // namespace Repositories

#endif // REPOSITORIES_IREPOSITORY_H
