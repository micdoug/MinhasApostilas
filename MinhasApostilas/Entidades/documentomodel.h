#ifndef ENTIDADES_DOCUMENTOMODEL_H
#define ENTIDADES_DOCUMENTOMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QStringList>
#include "documento.h"

namespace Entidades {

class DocumentoModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DocumentoModel(QObject *parent = 0);
    virtual ~DocumentoModel();

    QList<Documento> documentos() const;
    void setDocumentos(const QList<Documento> &documentos);

private:
    QList<Documento> m_documentos;
    QStringList m_propriedades;


    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

} // namespace Entidades

#endif // ENTIDADES_DOCUMENTOMODEL_H
