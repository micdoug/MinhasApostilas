/* ----------------------------------------------------------------------
 * Arquivo: texteditwatcher.h
 * Descrição: Arquivo de declaração da classe JanelaPrincipal
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#ifndef JANELAPRINCIPAL_H
#define JANELAPRINCIPAL_H

#include <QMainWindow>
#include <QMap>
#include <QVariant>
#include <QString>
#include "Repositorios/irepository.h"
#include "Entidades/documento.h"
#include "Entidades/documentomodel.h"

namespace Ui {
class JanelaPrincipal;
}

//Forward declarations
class QProgressBar;


class JanelaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit JanelaPrincipal(Repositorios::IRepository<Entidades::Documento> *repositorio, QWidget *parent = 0);
    virtual ~JanelaPrincipal();

public slots:
    void atualizar();
    void adicionarDocumento();
    void editarDocumento();
    void excluirDocumento();
    void filtrar();
    void limparFiltros();
    void irParaPagina();
    void alterarQtdItensPagina();
    void sobreEstePrograma();

private slots:
    void aposAtualizar(bool sucesso);
    void aposDocumentoAdicionado(bool sucesso);
    void aposDocumentoEditado(bool sucesso);
    void aposDocumentoExcluido(bool sucesso);
    void ajustarActions();
    void ajustarLabelPaginas();
    void irParaPaginaAnterior();
    void irParaProximaPagina();
    void irParaPrimeiraPagina();
    void irParaUltimaPagina();
    void ajustarOrdernacao(int indice, Qt::SortOrder ordem);

signals:
    void atualizado(bool sucesso);
    void documentoAdicionado(bool sucesso);
    void documentoEditado(bool sucesso);
    void documentoExcluido(bool sucesso);

private:
    //Atributos internos
    Ui::JanelaPrincipal *ui;
    QMap<QString,QVariant> m_filtros;
    Repositorios::IRepository<Entidades::Documento> *m_repositorio;
    Entidades::DocumentoModel m_model;
    QList<Entidades::Documento> m_documentos;
    QProgressBar *m_barraProgresso;
    qint32 m_qtdPaginas;
    qint32 m_itensPorPagina = 10;
    qint32 m_paginaAtual = 1;
    QStringList m_nomesColunasOrdenacao;

    //Métodos privados
    void setOcupado(bool ocupado);
    bool isOcupado() const;
    bool aguardarOperacoesPendentes();
};

#endif // JANELAPRINCIPAL_H
