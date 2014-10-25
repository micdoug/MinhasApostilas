#include "editarfiltros.h"
#include "ui_editarfiltros.h"

namespace Formularios {


EditarFiltros::EditarFiltros(QMap<QString, QVariant> *filtros, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditarFiltros),
    m_filtros(filtros)
{
    ui->setupUi(this);
    carregarFiltros();

    //Ao fechar, caso tenha sido aceito a janela, os filtros são exportados
    connect(this, &QDialog::accepted, this, [this]{exportarFiltros();});
}



EditarFiltros::~EditarFiltros()
{
    delete ui;
}

void EditarFiltros::carregarFiltros()
{
    //Aplicando filtros nos campos da propriedade código
    if(m_filtros->contains("codigo="))
    {
        ui->codigoIg->setValue(m_filtros->value("codigo=").toInt());
        ui->codigoIg->setEnabled(true);
        ui->codigoIgCheck->setChecked(true);
    }
    if(m_filtros->contains("codigo>="))
    {
        ui->codigoMa->setValue(m_filtros->value("codigo>=").toInt());
        ui->codigoMa->setEnabled(true);
        ui->codigoMaCheck->setChecked(true);
    }
    if(m_filtros->contains("codigo<="))
    {
        ui->codigoMe->setValue(m_filtros->value("codigoMe").toInt());
        ui->codigoMe->setEnabled(true);
        ui->codigoMeCheck->setChecked(true);
    }
    //Fim aplicando filtros nos campos da propriedade código

    //Aplicando filtros na propriedade ultimaAlteracao
    if(m_filtros->contains("ultimaAlteracao="))
    {
        ui->ultimaAlteracaoIg->setDateTime(m_filtros->value("ultimaAlteracao=").toDateTime());
        ui->ultimaAlteracaoIg->setEnabled(true);
        ui->ultimaAlteracaoIgCheck->setChecked(true);
    }
    if(m_filtros->contains("ultimaAlteracao>="))
    {
        ui->ultimaAlteracaoMa->setDateTime(m_filtros->value("ultimaAlteracao>=").toDateTime());
        ui->ultimaAlteracaoMa->setEnabled(true);
        ui->ultimaAlteracaoMaCheck->setChecked(true);
    }
    if(m_filtros->contains("ultimaAlteracao<="))
    {
        ui->ultimaAlteracaoMe->setDateTime(m_filtros->value("ultimaAlteracao>=").toDateTime());
        ui->ultimaAlteracaoMe->setEnabled(true);
        ui->ultimaAlteracaoMeCheck->setChecked(true);
    }
    //Fim aplicando filtros na propriedade ultimaAlteracao

    //Aplicando filtros nos campos da propriedade versão
    if(m_filtros->contains("versao="))
    {
        ui->versaoIg->setValue(m_filtros->value("versao=").toInt());
        ui->versaoIg->setEnabled(true);
        ui->versaoIgCheck->setChecked(true);
    }
    if(m_filtros->contains("versao>="))
    {
        ui->versaoMa->setValue(m_filtros->value("versao>=").toInt());
        ui->versaoMaCheck->setChecked(true);
    }
    if(m_filtros->contains("versao<="))
    {
        ui->versaoMe->setValue(m_filtros->value("versaoMe").toInt());
        ui->versaoMe->setEnabled(true);
        ui->versaoMeCheck->setChecked(true);
    }
    //Fim aplicando filtros nos campos da propriedade versão

    //Aplicando filtros na propriedade nome
    if(m_filtros->contains("nomeContains"))
    {
        ui->nomeCont->setText(m_filtros->value("nomeContains").toString());
        ui->nomeCont->setEnabled(true);
        ui->nomeContCheck->setChecked(true);
    }
    if(m_filtros->contains("nomeStartsWith"))
    {
        ui->nomeIni->setText(m_filtros->value("nomeStartsWith").toString());
        ui->nomeIni->setEnabled(true);
        ui->nomeIniCheck->setChecked(true);
    }
    if(m_filtros->contains("nomeEndsWith"))
    {
        ui->nomeTerm->setText(m_filtros->value("nomeEndsWith").toString());
        ui->nomeTerm->setEnabled(true);
        ui->nomeTermCheck->setChecked(true);
    }
    //Fim aplicando filtros na propriedade nome

    //Aplicando filtros na propriedade descricao
    if(m_filtros->contains("descricaoContains"))
    {
        ui->descricaoCont->setText(m_filtros->value("descricaoContains").toString());
        ui->descricaoCont->setEnabled(true);
        ui->descricaoContCheck->setChecked(true);
    }
    if(m_filtros->contains("descricaoStartsWith"))
    {
        ui->descricaoIni->setText(m_filtros->value("descricaoStartsWith").toString());
        ui->descricaoIni->setEnabled(true);
        ui->descricaoIniCheck->setChecked(true);
    }
    if(m_filtros->contains("descricaoEndsWith"))
    {
        ui->descricaoTerm->setText(m_filtros->value("descricaoEndsWith").toString());
        ui->descricaoTerm->setEnabled(true);
        ui->descricaoTermCheck->setChecked(true);
    }
    //Fim aplicando filtros na propriedade descricao
}

void EditarFiltros::exportarFiltros()
{
    //Carregando filtros para o código
    if(ui->codigoIg->isEnabled())
    {
        (*m_filtros)["codigo="] = ui->codigoIg->value();
    }
    else
    {
        m_filtros->remove("codigo=");
    }
    if(ui->codigoMa->isEnabled())
    {
        (*m_filtros)["codigo>="] = ui->codigoMa->value();
    }
    else
    {
        m_filtros->remove("codigo>=");
    }
    if(ui->codigoMe->isEnabled())
    {
        (*m_filtros)["codigo<="] = ui->codigoMe->value();
    }
    else
    {
        m_filtros->remove("codigo<=");
    }
    //Fim carregando filtros para o código

    //Carregando filtros para a ultimaAlteracao
    if(ui->ultimaAlteracaoIg->isEnabled())
    {
        (*m_filtros)["ultimaAlteracao="] = ui->ultimaAlteracaoIg->dateTime();
    }
    else
    {
        m_filtros->remove("ultimaAlteracao=");
    }
    if(ui->ultimaAlteracaoMa->isEnabled())
    {
        (*m_filtros)["ultimaAlteracao>="] = ui->ultimaAlteracaoMa->dateTime();
    }
    else
    {
        m_filtros->remove("ultimaAlteracao>=");
    }
    if(ui->ultimaAlteracaoMe->isEnabled())
    {
        (*m_filtros)["ultimaAlteracao<="] = ui->ultimaAlteracaoMe->dateTime();
    }
    else
    {
        m_filtros->remove("ultimaAlteracaoMe");
    }
    //Fim carregando filtros para a ultimaAlteracao

    //Carregando filtros para a versão
    if(ui->versaoIg->isEnabled())
    {
        (*m_filtros)["versao="] = ui->versaoIg->value();
    }
    else
    {
        m_filtros->remove("versao=");
    }
    if(ui->versaoMa->isEnabled())
    {
        (*m_filtros)["versao>="] = ui->versaoMa->value();
    }
    else
    {
        m_filtros->remove("versao>=");
    }
    if(ui->versaoMe->isEnabled())
    {
        (*m_filtros)["versao<="] = ui->versaoMe->value();
    }
    else
    {
        m_filtros->remove("versao<=");
    }
    //Fim carregando filtros para a versão

    //Carregando filtros para o nome
    if(ui->nomeCont->isEnabled())
    {
        (*m_filtros)["nomeContains"] = ui->nomeCont->text();
    }
    else
    {
        m_filtros->remove("nomeContains");
    }
    if(ui->nomeIni->isEnabled())
    {
        (*m_filtros)["nomeStartsWith"] = ui->nomeIni->text();
    }
    else
    {
        m_filtros->remove("nomeStartsWith");
    }
    if(ui->nomeTerm->isEnabled())
    {
        (*m_filtros)["nomeEndsWith"] = ui->nomeTerm->text();
    }
    else
    {
        m_filtros->remove("nomeEndsWith");
    }
    //Fim carregando filtros para o nome

    //Carregando filtros para a descricao
    if(ui->descricaoCont->isEnabled())
    {
        (*m_filtros)["descricaoContains"] = ui->descricaoCont->text();
    }
    else
    {
        m_filtros->remove("descricaoContains");
    }
    if(ui->descricaoIni->isEnabled())
    {
        (*m_filtros)["descricaoStartsWith"] = ui->descricaoIni->text();
    }
    else
    {
        m_filtros->remove("descricaoStartsWith");
    }
    if(ui->descricaoTerm->isEnabled())
    {
        (*m_filtros)["descricaoEndsWith"] = ui->descricaoTerm->text();
    }
    else
    {
        m_filtros->remove("descricaoEndsWith");
    }
}

}
