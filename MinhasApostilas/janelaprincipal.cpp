/* ----------------------------------------------------------------------
 * Arquivo: texteditwatcher.cpp
 * Descrição: Arquivo de implementação da classe JanelaPrincipal
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#include "janelaprincipal.h"
#include "ui_janelaprincipal.h"
#include "Utils/number.h"
#include "Formularios/editardocumento.h"
#include "Formularios/editarfiltros.h"
#include <QtConcurrent>
#include <QFutureWatcher>
#include <QFuture>
#include <QMessageBox>
#include <QProgressBar>
#include <QPair>
#include <QInputDialog>

/*!
 * \class JanelaPrincipal
 * Janela principal do programa. Esta classe utiliza um repositório de objetos
 * do tipo Entidades::Documento para executar as principais funções do programa.
 * \see Repositorios::IRepository
 * \see Entidades::Documento
 * \see Repositorios::DocumentoRepositorioOrm4Qt
 * \see Repositorios::DocumentoRepositorioQxOrm
 * \see Repositorios::DocumentoRepositorioODB
 */

/*!
 * Construtor.
 * \param repositorio
 * Instância de um repositório de objetos do tipo Entidades::Documento.
 * \param parent
 * Objeto responsável pela gerência de alocação desta instância.
 */
JanelaPrincipal::JanelaPrincipal(Repositorios::IRepository<Entidades::Documento> *repositorio, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JanelaPrincipal),
    m_repositorio(repositorio)
{
    setAttribute(Qt::WA_DeleteOnClose);
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
    connect(ui->tableView->horizontalHeader(), &QHeaderView::sortIndicatorChanged, this, &JanelaPrincipal::ajustarOrdernacao);
    connect(ui->actionAdicionarDocumento, &QAction::triggered, this, &JanelaPrincipal::adicionarDocumento);
    connect(ui->actionEditarDocumento, &QAction::triggered, this, &JanelaPrincipal::editarDocumento);
    connect(ui->actionExcluirDocumento, &QAction::triggered, this, &JanelaPrincipal::excluirDocumento);
    connect(ui->actionFiltrar, &QAction::triggered, this, &JanelaPrincipal::filtrar);
    connect(ui->actionIrParaPagina, &QAction::triggered, this, &JanelaPrincipal::irParaPagina);
    connect(ui->actionItensPorPagina, &QAction::triggered, this, &JanelaPrincipal::alterarQtdItensPagina);
    connect(ui->actionLimparFiltros, &QAction::triggered, this, &JanelaPrincipal::limparFiltros);
    connect(ui->actionSobreQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(ui->actionSobreEstePrograma, &QAction::triggered, this, &JanelaPrincipal::sobreEstePrograma);
    //Fim conectando ações dos componentes da interface

    //Connectando sinais das tarefas assíncronas
    connect(this, &JanelaPrincipal::atualizado, this, &JanelaPrincipal::aposAtualizar);
    connect(this, &JanelaPrincipal::atualizado, this, &JanelaPrincipal::ajustarActions);
    connect(this, &JanelaPrincipal::documentoAdicionado, this, &JanelaPrincipal::aposDocumentoAdicionado);
    connect(this, &JanelaPrincipal::documentoEditado, this, &JanelaPrincipal::aposDocumentoEditado);
    connect(this, &JanelaPrincipal::documentoExcluido, this, &JanelaPrincipal::aposDocumentoExcluido);
    //Fim conectando sinais das tarefas assíncronas

    //Preenchendo lista de nomes de colunas
    m_nomesColunasOrdenacao << "codigoOrderBy"
                   << "nomeOrderBy"
                   << "descricaoOrderBy"
                   << "ultimaAlteracaoOrderBy"
                   << "versaoOrderBy";
    //Fim preenchendo lista de nomes de colunas
}

/*!
 * Destrutor
 */
JanelaPrincipal::~JanelaPrincipal()
{
    delete ui;
    delete m_repositorio;
}

/*!
 * Efetua a pesquisa no banco de dados e atualiza os registros exibidos na tela do programa.
 */
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

/*!
 * Ajusta os componentes após a atualização dos registros pesquisados.
 * \param sucesso
 * Informa se a pesquisa ocorreu com sucesso ou não (ocorreu algum erro).
 */
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

/*!
 * Ajusta os componentes após um documento ter sido adicionado.
 * \param sucesso
 * Informa se a adição ocorreu com sucesso ou não (ocorreu algum erro).
 */
void JanelaPrincipal::aposDocumentoAdicionado(bool sucesso)
{
    setOcupado(false);
    if(sucesso)
    {
        atualizar();
    }
    else
    {
        QMessageBox::critical(this, "Erro ao adicionar documento", m_repositorio->lastError());
    }
}

/*!
 * Ajusta os componentes após um documento ter sido editado.
 * \param sucesso
 * Informa se a edição ocorreu com sucesso ou não (ocorreu algum erro).
 */
void JanelaPrincipal::aposDocumentoEditado(bool sucesso)
{
    setOcupado(false);
    if(sucesso)
    {
        atualizar();
    }
    else
    {
        QMessageBox::critical(this, "Erro ao editar documento", m_repositorio->lastError());
    }
}

/*!
 * Ajusta os componentes após um documento ter sido excluído.
 * \param sucesso
 * Informa se a exclusão ocorreu com sucesso ou não (ocorreu algum erro).
 */
void JanelaPrincipal::aposDocumentoExcluido(bool sucesso)
{
    setOcupado(false);
    if(sucesso)
    {
        if(m_model.documentos().size() == 1)
        {
            m_paginaAtual = 1;
        }
        atualizar();
    }
    else
    {
        QMessageBox::critical(this, "Erro ao excluir veículo", m_repositorio->lastError());
    }
}

/*!
 * Ajusta os componentes da tela de acordo com a situação atual.
 */
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

/*!
 * Ajusta o texto do paginador.
 */
void JanelaPrincipal::ajustarLabelPaginas()
{
    ui->labelPaginas->setText(QString("Página %1 de %2")
                              .arg(m_qtdPaginas > 0 ? m_paginaAtual : 0)
                              .arg(m_qtdPaginas));
}

/*!
 * Adiciona um novo documento no banco de dados.
 */
void JanelaPrincipal::adicionarDocumento()
{
    //Verificando se não existem operações pendentes
    if(aguardarOperacoesPendentes())
        return;

    Formularios::EditarDocumento form(Entidades::Documento(), this);
    if(form.exec() == QDialog::Accepted)
    {
        QFutureWatcher<bool> *watcher = new QFutureWatcher<bool>(this);
        connect(watcher, &QFutureWatcher<bool>::finished, this, [this, watcher]{
            emit documentoAdicionado(watcher->result());
            watcher->deleteLater();
        });
        auto doc = form.documento();
        doc.clearObservers();
        QFuture<bool> future = QtConcurrent::run([this, doc]{
            auto doctemp = doc;
            return m_repositorio->createObject(doctemp);
        });
        watcher->setFuture(future);
        setOcupado(true);
    }
}

/*!
 * Edita um documento previamente cadastrado.
 */
void JanelaPrincipal::editarDocumento()
{
    //Verificando se não existem operações pendentes
    if(aguardarOperacoesPendentes())
        return;

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
    doc.clearObservers();

    //Criando tarefa assíncrona
    watcher = new QFutureWatcher<bool>(this);
    connect(watcher, &QFutureWatcher<bool>::finished, this, [this, watcher]{
        emit documentoEditado(watcher->result());
        watcher->deleteLater();
    });
    future = QtConcurrent::run([this, doc]{
        auto temp = doc;
        temp.setUltimaAlteracao(QDateTime::currentDateTime());
        return m_repositorio->updateObject(temp);
    });
    watcher->setFuture(future);
    //Fim criando tarefa assíncrona
    setOcupado(true);
}

/*!
 * Exclui um documento previamente cadastrado.
 */
void JanelaPrincipal::excluirDocumento()
{
    //Verificando se não existem operações pendentes
    if(aguardarOperacoesPendentes())
        return;

    //Capturando o índice atual e validando
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    if(!index.isValid())
    {
        QMessageBox::warning(this, "Operação ilegal", "Você deve selecionar um item na lista antes de excluir.");
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

    //Exibindo mensagem de alerta de exclusão
    setOcupado(true);
    if(QMessageBox::question(this, "Confirmar exclusão de documento", QString("Você confirma a exclusão do documento \"%1\"?").arg(doc.nome()), QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes)
    {
        //Criando tarefa assíncrona
        watcher = new QFutureWatcher<bool>(this);
        connect(watcher, &QFutureWatcher<bool>::finished, this, [this, watcher]{
            emit documentoExcluido(watcher->result());
            watcher->deleteLater();
        });
        future = QtConcurrent::run([this, doc]{
            //Se só existir um elemento na tela e ele for excluído, o número da página atual deve ser decrementado
            if(m_model.documentos().size() == 1 && m_paginaAtual > 1)
            {
                m_paginaAtual--;
            }
            auto temp = doc;
            return m_repositorio->deleteObject(temp);
        });
        watcher->setFuture(future);
        //Fim criando tarefa assíncrona
    }
    else
    {
        setOcupado(false);
    }
}

/*!
 * Abre o formulário de edição dos filtros de busca.
 */
void JanelaPrincipal::filtrar()
{
    //Verificando se há operações pendentes
    if(aguardarOperacoesPendentes())
        return;

    //Criando janela de edição de filtros
    Formularios::EditarFiltros formulario(&m_filtros, this);
    if (formulario.exec() == QDialog::Accepted)
    {
        if(m_model.documentos().size() == 1)
        {
            m_paginaAtual = 1;
        }
        atualizar();
    }
}

/*!
 * Remove todos os filtros em uso
 */
void JanelaPrincipal::limparFiltros()
{
    //Verificando se há tarefas pendentes
    if(aguardarOperacoesPendentes())
        return;

    //Guarda valor de ordenação antes de limpar
    QPair<QString, QVariant> ordenar;
    for(QString str : m_nomesColunasOrdenacao)
    {
        if(m_filtros.contains(str))
        {
            ordenar.first = str;
            ordenar.second = m_filtros[str];
            break;
        }
    }
    m_filtros.clear();
    if(!ordenar.first.isNull())
    {
        m_filtros.insert(ordenar.first, ordenar.second);
    }
    atualizar();
}

/*!
 * Navega para determinada página.
 */
void JanelaPrincipal::irParaPagina()
{
    //Verificando se há operações pendentes
    if(aguardarOperacoesPendentes())
        return;

    //Aplica o número da página escolhida
    bool escolheu;
    int pagina = QInputDialog::getInt(this, "Ir para a página", "Defina o número da página para a qual deseja ir.", m_paginaAtual, 1, m_qtdPaginas, 1, &escolheu);
    if(escolheu)
    {
        m_paginaAtual = pagina;
        atualizar();
    }
}

/*!
 * Altera a quantidade de itens exibidos por página.
 */
void JanelaPrincipal::alterarQtdItensPagina()
{
    //Verificando se há operações pendentes
    if(aguardarOperacoesPendentes())
        return;

    //Aplica o número da página escolhida
    bool escolheu;
    int qtd = QInputDialog::getInt(this, "Quantidade de itens por página", "Defina a quantidade de itens por página.", m_itensPorPagina, 1, 999999, 1, &escolheu);
    if(escolheu)
    {
        m_itensPorPagina = qtd;
        if(m_model.documentos().size() == 1)
        {
            m_paginaAtual = 1;
        }
        atualizar();
    }
}

/*!
 * Exibe uma janela com informações sobre este programa.
 */
void JanelaPrincipal::sobreEstePrograma()
{
    QMessageBox::about(this, "Minhas Apostilas", "Programa desenvolvido com o objetivo de comparar bibliotecas ORM para a linguagem C++. \n"
                                                 "Desenvolvido por: Michael Dougras da Silva \n"
                                                 "Contato: micdoug.silva@gmail.com");
}

/*!
 * Navega para a página anterior.
 */
void JanelaPrincipal::irParaPaginaAnterior()
{
    --m_paginaAtual;
    atualizar();
}

/*!
 * Navega para a próxima página
 */
void JanelaPrincipal::irParaProximaPagina()
{
    ++m_paginaAtual;
    atualizar();
}

/*!
 * Navega para a primeira página.
 */
void JanelaPrincipal::irParaPrimeiraPagina()
{
    m_paginaAtual = 1;
    atualizar();
}

/*!
 * Navega para a última página.
 */
void JanelaPrincipal::irParaUltimaPagina()
{
    m_paginaAtual = m_qtdPaginas;
    atualizar();
}

/*!
 * Método chamado quando o usuário clica em uma coluna solicitando a ordenação de elementos.
 * \param indice
 * Número da coluna a ser ordenada.
 * \param ordem
 * Informa se a ordenação é crescente ou decrescente.
 */
void JanelaPrincipal::ajustarOrdernacao(int indice, Qt::SortOrder ordem)
{
    //Limpa os filtros de ordenação
    for(QString str : m_nomesColunasOrdenacao)
    {
        m_filtros.remove(str);
    }

    //Adicionando novo filtro de ordenação
    m_filtros.insert(m_nomesColunasOrdenacao[indice], ordem == Qt::AscendingOrder ? QString("asc") : QString("desc"));

    //Atualizando grid
    atualizar();
}

/*!
 * Ajusta o status da janela em ocupado ou livre. Usado para controlar a espera pelo término de tarefas
 * assíncronas.
 * \param ocupado
 * Se true a janela fica em modo ocupado, se false a janela fica em modo normal.
 */
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

/*!
 * Informa se a janela está em modo ocupado ou não,
 * ou seja, se há alguma tarefa assíncrona em execução.
 * \return
 * Se a janela está em modo ocupado.
 */
bool JanelaPrincipal::isOcupado() const
{
    return m_barraProgresso->isVisible();
}

/*!
 * Exibe mensagens de espera por tarefas pendentes.
 * \return
 * Se a jenela está em modo ocupado ou não.
 */
bool JanelaPrincipal::aguardarOperacoesPendentes()
{
    if(isOcupado())
    {
        QMessageBox::information(this, "Aguarde as operações pendentes", "Aguarde o fim do processamento das operações solicitadas!");
    }
    return isOcupado();
}
