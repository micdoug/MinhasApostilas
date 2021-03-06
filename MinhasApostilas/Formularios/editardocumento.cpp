/* ----------------------------------------------------------------------
 * Arquivo: editardocumento.cpp
 * Descrição: Arquivo de implementação da classe Formularios::EditarDocumento.
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#include "editardocumento.h"
#include "ui_editardocumento.h"
#include <functional>
#include <QFileDialog>
#include <QMessageBox>

/*!
 * \class Formularios::EditarDocumento
 * Classe que cria um formulário para edição de registros de documentos.
 */

namespace Formularios {

/*!
 * Construtor.
 * \param documento
 * Registro de documento a ser editado.
 * \param parent
 * Objeto responsável pelo gerenciamento de alocação da instância deste objeto.
 */
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

/*!
 * Destrutor.
 */
EditarDocumento::~EditarDocumento()
{
    delete ui;
}

/*!
 * Registro de documento sendo editado pelo formulário.
 * \return
 * Documento editado.
 */
Entidades::Documento EditarDocumento::documento() const
{
    return m_documento;
}

/*!
 * Implementa a função de fazer upload de arquivos para serem armazenados no banco de dados.
 */
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

/*!
 * Implementa a função de fazer o download de arquivos a partir do banco de dados para a máquina local.
 */
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

/*!
 * Método utilizado como resposta a alterações em valores de propriedades da instância de documento sendo editada.
 * Este método é responsável por atualizar os dados da tela de edição quando ocorrer alterações por origens externas
 * no documento sendo editado.
 * \param propriedade
 * Nome da propriedade que teve seu valor modificado.
 * \param valor
 * Novo valor para a propriedade modificada.
 */
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

/*!
 * Efetua a ligação do documento com o método de resposta a atualizações.
 * Também efetua a ligação de alterações nos valores do formulário com
 * métodos de atualização dos valores das propriedades do documento sendo
 * editado.
 * \see Formularios::EditarDocumento::documentoAtualizado
 */
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
