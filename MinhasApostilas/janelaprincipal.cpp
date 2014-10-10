#include "janelaprincipal.h"
#include "ui_janelaprincipal.h"
#include "Utils/number.h"
#include "Formularios/editardocumento.h"
#include <QtConcurrent>
#include <QFutureWatcher>
#include <QFuture>
#include <QMessageBox>
#include <QProgressBar>

JanelaPrincipal::JanelaPrincipal(Repositorios::IRepository<Entidades::Documento> *repositorio, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JanelaPrincipal),
    m_repositorio(repositorio)
{
    ui->setupUi(this);

    //Ajustando barra de status
    statusBar()->showMessage("Bem vindo!");
    m_barraProgresso = new QProgressBar(this);
    m_barraProgresso->setRange(0, 0);
    m_barraProgresso->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    statusBar()->addPermanentWidget(m_barraProgresso);
    m_barraProgresso->hide();
    //Fim ajustando barra de status

    //Configurando model
    ui->tableView->setModel(&m_model);

    //Conectando ações dos componentes da interface
    connect(ui->actionAtualizar, &QAction::triggered, this, &JanelaPrincipal::atualizar);
    connect(ui->botaoPaginaAnterior, &QToolButton::clicked, this, &JanelaPrincipal::irParaPaginaAnterior);
    connect(ui->botaoProximaPagina, &QToolButton::clicked, this, &JanelaPrincipal::irParaProximaPagina);
    connect(ui->botaoPrimeiraPagina, &QToolButton::clicked, this, &JanelaPrincipal::irParaPrimeiraPagina);
    connect(ui->botaoUltimaPagina, &QToolButton::clicked, this, &JanelaPrincipal::irParaUltimaPagina);
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentChanged, this, &JanelaPrincipal::ajustarActions);
    connect(ui->tableView, &QTableView::doubleClicked, ui->actionEditarDocumento, &QAction::trigger);
    connect(ui->actionAdicionarDocumento, &QAction::triggered, this, &JanelaPrincipal::adicionarDocumento);
    connect(ui->actionEditarDocumento, &QAction::triggered, this, &JanelaPrincipal::editarDocumento);
    connect(ui->actionSobreQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    //Fim conectando ações dos componentes da interface

    //Connectando sinais das tarefas assíncronas
    connect(this, &JanelaPrincipal::atualizado, this, &JanelaPrincipal::aposAtualizar);
    connect(this, &JanelaPrincipal::atualizado, this, &JanelaPrincipal::ajustarActions);
    connect(this, &JanelaPrincipal::documentoAdicionado, this, &JanelaPrincipal::aposDocumentoAdicionado);
    connect(this, &JanelaPrincipal::documentoEditado, this, &JanelaPrincipal::aposDocumentoEditado);
    //Fim conectando sinais das tarefas assíncronas
}

JanelaPrincipal::~JanelaPrincipal()
{
    delete ui;
    delete m_repositorio;
}

void JanelaPrincipal::atualizar()
{
    //Verificando se não existem operações pendentes
    if(aguardarOperacoesPendentes())
        return;

    //Ajustando limit e offset
    m_filtros["limit"] = m_itensPorPagina;
    m_filtros["offset"] = m_itensPorPagina * (m_paginaAtual-1);

    //Criando conector de tarefa assíncrona
    QFutureWatcher<bool> *watcher = new QFutureWatcher<bool>(this);
    connect(watcher, &QFutureWatcher<bool>::finished, this, [this, watcher]{
        emit atualizado(watcher->result());
        watcher->deleteLater();
    });
    //Fim criando conector de tarefa assíncrona

    //Criando tarefa assíncrona
    setOcupado(true);
    QFuture<bool> future = QtConcurrent::run([this]{
        return m_repositorio->selectObjects(m_documentos, m_filtros) &&
                m_repositorio->countObjects(m_qtdPaginas, m_filtros);
    });
    //Fim Criando tarefa assíncrona

    //Conectando watcher
    watcher->setFuture(future);
}

void JanelaPrincipal::aposAtualizar(bool sucesso)
{
    //Se a operação foi bem sucedida atualiza lista do model
    if(sucesso)
    {
        m_model.setDocumentos(m_documentos);
        //Ajustando a quantidade de páginas, neste momento m_qtdPaginas contém a quantidade total de registros
        m_qtdPaginas = Utils::Number::divRoundUp(m_qtdPaginas, m_itensPorPagina);
        //Ajustando label de páginas
        ajustarLabelPaginas();
    }
    //Caso a operação falhe, mostra janela com descrição do erro
    else
    {
        QMessageBox::critical(this, "Erro ao pesquisar registros", m_repositorio->lastError());
    }
    //Limpa a lista de documentos
    m_documentos.clear();
    //Redimensiona colunas da tableview
    ui->tableView->resizeColumnsToContents();
    //Desativa notificação na statusbar
    setOcupado(false);
}

void JanelaPrincipal::aposDocumentoAdicionado(bool sucesso)
{
    if(sucesso)
    {
        atualizar();
    }
    else
    {
        QMessageBox::critical(this, "Erro ao adicionar documento", m_repositorio->lastError());
    }
}

void JanelaPrincipal::aposDocumentoEditado(bool sucesso)
{
    if(sucesso)
    {
        atualizar();
    }
    else
    {
        QMessageBox::critical(this, "Erro ao editar documento", m_repositorio->lastError());
    }
}

void JanelaPrincipal::ajustarActions()
{
    //Validando se há algum item selecionado na tabela
    if(!ui->tableView->currentIndex().isValid())
    {
        ui->actionEditarDocumento->setEnabled(false);
        ui->actionExcluirDocumento->setEnabled(false);
    }
    else
    {
        ui->actionEditarDocumento->setEnabled(true);
        ui->actionExcluirDocumento->setEnabled(true);
    }
    //Fim validando se há algum item selecionado na tabela

    //Validando o número atual da página
    if(m_paginaAtual > 1)
    {
        ui->botaoPaginaAnterior->setEnabled(true);
        ui->botaoPrimeiraPagina->setEnabled(true);
    }
    else
    {
        ui->botaoPaginaAnterior->setEnabled(false);
        ui->botaoPrimeiraPagina->setEnabled(false);
    }
    if(m_paginaAtual < m_qtdPaginas)
    {
        ui->botaoProximaPagina->setEnabled(true);
        ui->botaoUltimaPagina->setEnabled(true);
    }
    else
    {
        ui->botaoProximaPagina->setEnabled(false);
        ui->botaoUltimaPagina->setEnabled(false);
    }
    //Fim validando o número atual da página

}

void JanelaPrincipal::ajustarLabelPaginas()
{
    ui->labelPaginas->setText(QString("Página %1 de %2")
                              .arg(m_qtdPaginas > 0 ? m_paginaAtual : 0)
                              .arg(m_qtdPaginas));
}

void JanelaPrincipal::adicionarDocumento()
{
    Formularios::EditarDocumento form(Entidades::Documento(), this);
    if(form.exec() == QDialog::Accepted)
    {
        QFutureWatcher<bool> *watcher = new QFutureWatcher<bool>(this);
        connect(watcher, &QFutureWatcher<bool>::finished, this, [this, watcher]{
            emit documentoAdicionado(watcher->result());
            watcher->deleteLater();
        });
        auto doc = form.documento();
        QFuture<bool> future = QtConcurrent::run([this, doc]{
            auto doctemp = doc;
            return m_repositorio->createObject(doctemp);
        });
        watcher->setFuture(future);
    }
}

void JanelaPrincipal::editarDocumento()
{
    //Capturando o índice atual e validando
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    if(!index.isValid())
    {
        QMessageBox::warning(this, "Operação ilegal", "Você deve selecionar um item na lista antes de editar.");
        return;
    }
    //Fim capturando o índice atual e validando

    //Capturando o registro a ser editado
    qlonglong codigo = m_model.documentos()[index.row()].codigo();
    QFutureWatcher<bool> *watcher = new QFutureWatcher<bool>(this);
    QEventLoop loop(this);
    connect(watcher, &QFutureWatcher<bool>::finished, &loop, &QEventLoop::quit);
    Entidades::Documento *documento = new Entidades::Documento();
    QFuture<bool> future = QtConcurrent::run([documento, codigo, this]{
        return m_repositorio->getObject(codigo, *documento);
    });
    watcher->setFuture(future);
    setOcupado(true);
    loop.exec();
    setOcupado(false);
    if(!watcher->result())
    {
        QMessageBox::critical(this, "Erro ao pesquisar registro", m_repositorio->lastError());
        delete documento;
        delete watcher;
        return;
    }
    delete watcher;
    Entidades::Documento doc = Entidades::Documento(*documento);
    delete documento;
    //Fim capturando o registro a ser editado

    //Criando formulário de edição
    Formularios::EditarDocumento form(doc, this);
    if(form.exec() != QDialog::Accepted)
    {
        return;
    }
    doc = form.documento();

    //Criando tarefa assíncrona
    watcher = new QFutureWatcher<bool>(this);
    connect(watcher, &QFutureWatcher<bool>::finished, this, [this, watcher]{
        emit documentoEditado(watcher->result());
        watcher->deleteLater();
    });
    future = QtConcurrent::run([this, doc]{
        auto temp = doc;
        return m_repositorio->updateObject(temp);
    });
    watcher->setFuture(future);
    //Fim criando tarefa assíncrona
}

void JanelaPrincipal::irParaPaginaAnterior()
{
    --m_paginaAtual;
    atualizar();
}

void JanelaPrincipal::irParaProximaPagina()
{
    ++m_paginaAtual;
    atualizar();
}

void JanelaPrincipal::irParaPrimeiraPagina()
{
    m_paginaAtual = 1;
    atualizar();
}

void JanelaPrincipal::irParaUltimaPagina()
{
    m_paginaAtual = m_qtdPaginas;
    atualizar();
}

void JanelaPrincipal::setOcupado(bool ocupado)
{
    //Se setar como ocupado
    if(ocupado)
    {
        //Ajusta mensagem da status bar
        statusBar()->showMessage("Trocando informações com o banco de dados");
        //Mostra barra de progresso
        m_barraProgresso->show();
    }
    //Se setar como não ocupado
    else
    {
        //Limpa mensagem da status bar
        statusBar()->showMessage("");
        //Esconde barra de progresso
        m_barraProgresso->hide();
    }
}

bool JanelaPrincipal::isOcupado() const
{
    return m_barraProgresso->isVisible();
}

bool JanelaPrincipal::aguardarOperacoesPendentes()
{
    if(isOcupado())
    {
        QMessageBox::information(this, "Aguarde as operações pendentes", "Aguarde o fim do processamento das operações solicitadas!");
    }
    return isOcupado();
}
