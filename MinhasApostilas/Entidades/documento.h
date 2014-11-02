/* ----------------------------------------------------------------------
 * Arquivo: documento.h
 * Descrição: Arquivo de declaração da classe Entidades::Documento.
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#ifndef ENTIDADES_DOCUMENTO_H
#define ENTIDADES_DOCUMENTO_H

#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QByteArray>
#include "../Utils/inotifypropertychanged.h"
#include "../Utils/ipropertygetset.h"

//Anotações Orm4Qt
#include "annotations.h"

//Biblioteca QxOrm
#include <QxOrm.h>

//Definições de pragmas do ODB Orm
#include <odb/core.hxx>

namespace Entidades {

class Documento: public Utils::INotifyPropertyChanged, public Utils::IPropertyGetSet
{
   QX_REGISTER_FRIEND_CLASS(Entidades::Documento)
    public:
        Documento();
        virtual ~Documento();
        qlonglong codigo() const;
        void setCodigo(const qlonglong &codigo);
        QString nome() const;
        void setNome(const QString &nome);
        QString descricao() const;
        void setDescricao(const QString &descricao);
        QDateTime ultimaAlteracao() const;
        void setUltimaAlteracao(const QDateTime &ultimaAlteracao);
        quint16 versao() const;
        void setVersao(const quint16 &versao);
        QByteArray arquivo() const;
        void setArquivo(const QByteArray &arquivo);

    private:
        //Atributos privados
        qlonglong m_codigo;
        QString m_nome;
        QString m_descricao;
        QDateTime m_ultimaAlteracao;
        quint16 m_versao;
        QByteArray m_arquivo;

        //Estruturas de ajuda
        QStringList m_propriedades;

    // IPropertyGetSet interface
    public:
        virtual bool setPropertyValue(const QString &propertyName, const QVariant &newValue) override;
        virtual QVariant getPropertyValue(const QString &propertyName) override;

    // INotifyPropertyChanged interface
    protected:
        virtual void emitAllPropertiesChanged() override;

        //Orm4Qt annotations
        ORM4QT_BEGIN
            CLASS(name="Documento", autocolumn="codigo", table="t_documento")
            PROPERTY(m_codigo, name="codigo", column="c_codigo", key=true)
            PROPERTY(m_nome, name="nome", column="c_nome", required=true, maxlength=200, unique=true)
            PROPERTY(m_descricao, name="descricao", column="c_descricao", required=false, maxlength=1000)
            PROPERTY(m_ultimaAlteracao, name="ultimaAlteracao", column="c_ultimaalteracao", required=true)
            PROPERTY(m_versao, name="versao", column="c_versao", required=true)
            PROPERTY(m_arquivo, name="arquivo", column="c_arquivo", required=true)
        ORM4QT_END

    };

    //Mapeamento com o ODB Orm
    #pragma db object(Documento) table("t_documento") pointer(std::unique_ptr)
    #pragma db member(Documento::m_codigo) id auto column("c_codigo")
    #pragma db member(Documento::m_nome) not_null unique column("c_nome")
    #pragma db member(Documento::m_descricao) null column("c_descricao")
    #pragma db member(Documento::m_ultimaAlteracao) not_null column("c_ultimaalteracao")
    #pragma db member(Documento::m_versao) not_null column("c_versao")
    #pragma db member(Documento::m_arquivo) not_null column("c_arquivo")
    #pragma db member(Documento::m_propriedades) transient

    #pragma db view object(Documento)
    struct DocumentoInfo
    {
        #pragma db column("count(" + Documento::m_codigo + ")")
        std::size_t quantidade;
    };

    #pragma db view object(Documento)
    struct DocumentoView
    {
        #pragma db column(Documento::m_codigo)
        qlonglong codigo;
        #pragma db column(Documento::m_nome)
        QString nome;
        #pragma db column(Documento::m_descricao)
        QString descricao;
        #pragma db column(Documento::m_ultimaAlteracao)
        QDateTime ultimaAlteracao;
        #pragma db column(Documento::m_versao)
        quint16 versao;
    };

} // namespace Entidades

QX_REGISTER_PRIMARY_KEY(Entidades::Documento, qlonglong)
#if  defined(Q_OS_WIN32)
    QX_REGISTER_COMPLEX_CLASS_NAME_HPP_EXPORT_DLL(Entidades::Documento, qx::trait::no_base_class_defined, 0, Documento)
#elif  defined(Q_OS_LINUX)
    QX_REGISTER_COMPLEX_CLASS_NAME_HPP(Entidades::Documento, qx::trait::no_base_class_defined, 0, Documento)
#endif

#endif // ENTIDADES_DOCUMENTO_H
