#include "documento.h"

namespace Entidades {

Documento::Documento()
{
    m_propriedades << "codigo"
                   << "nome"
                   << "descricao"
                   << "ultimaAlteracao"
                   << "versao"
                   << "arquivo";
}

Documento::~Documento()
{}

qlonglong Documento::codigo() const
{
    return m_codigo;
}

void Documento::setCodigo(const qlonglong &codigo)
{
    if(codigo != m_codigo)
    {
        m_codigo = codigo;
        emitPropertyChanged("codigo", this->codigo());
    }
}

QString Documento::nome() const
{
    return m_nome;
}

void Documento::setNome(const QString &nome)
{
    if(nome != m_nome)
    {
        m_nome = nome;
        emitPropertyChanged("nome", this->nome());
    }
}

QString Documento::descricao() const
{
    return m_descricao;
}

void Documento::setDescricao(const QString &descricao)
{
    if(descricao != m_descricao)
    {
        m_descricao = descricao;
        emitPropertyChanged("descricao", this->descricao());
    }
}

QDateTime Documento::ultimaAlteracao() const
{
    return m_ultimaAlteracao;
}

void Documento::setUltimaAlteracao(const QDateTime &ultimaAlteracao)
{
    if(ultimaAlteracao != m_ultimaAlteracao)
    {
        m_ultimaAlteracao = ultimaAlteracao;
        emitPropertyChanged("ultimaAlteracao", this->ultimaAlteracao());
    }
}
quint16 Documento::versao() const
{
    return m_versao;
}

void Documento::setVersao(const quint16 &versao)
{
    if(versao != m_versao)
    {
        m_versao = versao;
        emitPropertyChanged("versao", this->versao());
    }
}

QByteArray Documento::arquivo() const
{
    return m_arquivo;
}

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
