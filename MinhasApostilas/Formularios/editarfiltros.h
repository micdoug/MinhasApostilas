#ifndef EDITARFILTROS_H
#define EDITARFILTROS_H

#include <QDialog>
#include <QMap>
#include <QString>
#include <QVariant>

namespace Ui {
class EditarFiltros;
}
namespace Formularios {
    class EditarFiltros : public QDialog
    {
        Q_OBJECT

    public:
        explicit EditarFiltros(QMap<QString, QVariant> *filtros, QWidget *parent = 0);
        ~EditarFiltros();

    private:
        Ui::EditarFiltros *ui;
        //Hash com dados de filtro
        QMap<QString, QVariant> *m_filtros;

        //Carrega filtros para campos da tela
        void carregarFiltros();
        //Carrega filtos dos campos da tela para o QMap
        void exportarFiltros();
    };
}
#endif // EDITARFILTROS_H
