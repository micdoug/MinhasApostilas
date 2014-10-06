#include "documentomodel.h"

namespace Entidades {

DocumentoModel::DocumentoModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_propriedades << "codigo"
                   << "nome"
                   << "descricao"
                   << "ultimaAlteracao"
                   << "versao";
}

DocumentoModel::~DocumentoModel()
{}

QList<Documento> DocumentoModel::documentos() const
{
    return m_documentos;
}

void DocumentoModel::setDocumentos(const QList<Documento> &documentos)
{
    beginResetModel();
    m_documentos = documentos;
    endResetModel();
}

int DocumentoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_documentos.count();
}

int DocumentoModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 5;
}

QVariant DocumentoModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid())
    {
        //Retorna o valor
        if(role==Qt::DisplayRole)
        {
            return static_cast<Documento>(m_documentos[index.row()]).getPropertyValue(m_propriedades[index.column()]);
        }
        //Retorna o nome da propriedade
        else if(role == Qt::ToolTipRole)
        {
            return m_propriedades[index.column()].toUpper();
        }
    }
    //Indíce inválido ou função de exibição não suportada
    return QVariant();
}

QVariant DocumentoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Vertical)
        {
            return section + 1;
        }
        else
        {
            switch (section)
            {
                case 0:
                    return "Código";
                case 1:
                    return "Nome";
                case 2:
                    return "Descrição";
                case 3:
                    return "Data Última Alteração";
                case 4:
                    return "Versão";
            }
        }
    }
    //Função de exibição não suportada
    return QVariant();
}


} // namespace Entidades
