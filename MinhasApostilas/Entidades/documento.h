#ifndef ENTIDADES_DOCUMENTO_H
#define ENTIDADES_DOCUMENTO_H

#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QByteArray>
#include "../Utils/inotifypropertychanged.h"
#include "../Utils/ipropertygetset.h"

#ifdef ORM_ORM4QT
#include "annotations.h"
#endif

namespace Entidades {

class Documento: public Utils::INotifyPropertyChanged, public Utils::IPropertyGetSet
{
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
    #ifdef ORM_ORM4QT
        ORM4QT_BEGIN
            CLASS(name="Documento", autocolumn="codigo", table="t_documento")
            PROPERTY(m_codigo, name="codigo", column="c_codigo", key=true)
            PROPERTY(m_nome, name="nome", column="c_nome", required=true, maxlength=200, unique=true)
            PROPERTY(m_descricao, name="descricao", column="c_descricao", required=false, maxlength=1000)
            PROPERTY(m_ultimaAlteracao, name="ultimaAlteracao", column="c_ultimaAlteracao", required=true)
            PROPERTY(m_versao, name="versao", column="c_versao", required=true)
            PROPERTY(m_arquivo, name="arquivo", column="c_arquivo", required=true)
        ORM4QT_END
    #endif

    };
} // namespace Entidades

#endif // ENTIDADES_DOCUMENTO_H
