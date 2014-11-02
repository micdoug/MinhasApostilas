/* ----------------------------------------------------------------------
 * Arquivo: editardocumento.h
 * Descrição: Arquivo de implementação da classe Formularios::EditarDocumento.
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#ifndef FORMULARIOS_EDITARDOCUMENTO_H
#define FORMULARIOS_EDITARDOCUMENTO_H

#include <QDialog>
#include <QStringList>
#include "../Entidades/documento.h"

namespace Ui {
    class EditarDocumento;
}

namespace Formularios {

class EditarDocumento : public QDialog
{
    Q_OBJECT
public:
    EditarDocumento(const Entidades::Documento &documento, QWidget *parent=0);
    virtual ~EditarDocumento();
    Entidades::Documento documento() const;

private slots:
    void fazerUpload();
    void fazerDownload();
    
private:
    Ui::EditarDocumento *ui;
    Entidades::Documento m_documento;
    QStringList m_propriedades;

    //Métodos auxiliares
    void documentoAtualizado(const QString &propriedade, const QVariant &valor);
    void bind();
};

} // namespace Formularios

#endif // FORMULARIOS_EDITARDOCUMENTO_H
