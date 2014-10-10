#include "editardocumento.h"
#include "ui_editardocumento.h"
#include <functional>
#include <QFileDialog>
#include <QMessageBox>

namespace Formularios {

EditarDocumento::EditarDocumento(const Entidades::Documento &documento, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditarDocumento),
    m_documento(documento)
{
    //Iniciando componentes da interface
    ui->setupUi(this);

    //Preenchendo lista de propriedades
    m_propriedades << "codigo"
                   << "nome"
                   << "descricao"
                   << "ultimaAlteracao"
                   << "versao"
                   << "arquivo";
    //Fim preenchendo lista de propriedades

    //Ligando controles aos valores do documento
    bind();
    m_documento.refresh();

    //Conectando sinais
    connect(ui->botaoUpload, &QToolButton::clicked, this, &EditarDocumento::fazerUpload);
    connect(ui->botaoDownload, &QToolButton::clicked, this, &EditarDocumento::fazerDownload);
}

EditarDocumento::~EditarDocumento()
{
    delete ui;
}

Entidades::Documento EditarDocumento::documento() const
{
    return m_documento;
}

void EditarDocumento::fazerUpload()
{
    QString caminho = QFileDialog::getOpenFileName(this, "Escolha o arquivo para fazer upload", QDir::homePath(), "PDF (*.pdf)");
    if(!caminho.isNull())
    {
        setCursor(Qt::WaitCursor);
        QFile arquivo(caminho);
        if(arquivo.open(QIODevice::ReadOnly))
        {
            m_documento.setArquivo(arquivo.readAll());
            arquivo.close();
            QMessageBox::information(this, "Upload concluído!", "O upload do arquivo foi concluído com sucesso!");
        }
        else
        {
             QMessageBox::critical(this, "Erro ao abrir o arquivo indicado", arquivo.errorString());
        }
        unsetCursor();
    }
}

void EditarDocumento::fazerDownload()
{
    QString caminho = QFileDialog::getSaveFileName(this, "Escolha onde deseja salvar o documento", QDir::homePath(), "PDF (*.pdf)");
    if(!caminho.isNull())
    {
        setCursor(Qt::WaitCursor);
        QFile arquivo(caminho);
        if(arquivo.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            QDataStream stream(&arquivo);
            stream << m_documento.arquivo();
            arquivo.close();
            QMessageBox::information(this, "Download Concluído", "O arquivo foi salvo com sucesso!");
        }
        else
        {
            QMessageBox::critical(this, "Erro ao salvar arquivo", arquivo.errorString());
        }
        unsetCursor();
    }
}

void EditarDocumento::documentoAtualizado(const QString &propriedade, const QVariant &valor)
{
    qint32 indice = m_propriedades.indexOf(propriedade);
    if(indice >= 0)
    {
        switch(indice)
        {
            case 0:
                ui->editCodigo->setText(valor.toString());
                break;
            case 1:
                ui->editNome->setText(valor.toString());
                break;
            case 2:
                ui->editDescricao->setPlainText(valor.toString());
                break;
            case 3:
                ui->editUltimaAlteracao->setDateTime(valor.toDateTime());
                break;
            case 4:
                ui->editVersao->setValue(valor.toDouble());
                break;
            case 5:
                ui->botaoDownload->setEnabled(!m_documento.arquivo().isNull());
        }
    }
}

void EditarDocumento::bind()
{
    //Registrando método de atualização dos controles
    m_documento.addObserver(std::bind(std::mem_fn(&EditarDocumento::documentoAtualizado), this, std::placeholders::_1, std::placeholders::_2));

    //Conectando controles ao documento
    connect(ui->editCodigo, &QLineEdit::editingFinished, this,
            [this]{ m_documento.setPropertyValue("codigo", ui->editCodigo->text());});

    connect(ui->editNome, &QLineEdit::editingFinished, this,
            [this]{ m_documento.setPropertyValue("nome", ui->editNome->text());});

    connect(ui->editDescricao, &Utils::TextEditWatcher::editingFinished, this,
        [this]{ m_documento.setPropertyValue("descricao", ui->editDescricao->toPlainText()); });

    connect(ui->editVersao, (void (QSpinBox::*)(int))&QSpinBox::valueChanged, this,
            [this](int valor){ m_documento.setPropertyValue("versao", valor); });

    connect(ui->editUltimaAlteracao, &QDateTimeEdit::dateTimeChanged, this,
            [this](const QDateTime &valor){ m_documento.setPropertyValue("ultimaAlteracao", valor); });

}

} // namespace Formularios
