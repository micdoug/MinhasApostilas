/* ----------------------------------------------------------------------
 * Arquivo: lineeditcheckcase.cpp
 * Descrição: Arquivo de implementação da classe Utils::LineEditCheckCase
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#include "lineeditcheckcase.h"
#include <QKeyEvent>

/*!
 * \class Utils::LineEditCheckCase
 * Especialização do componente QLineEdit do framework Qt.
 * Esta especialização cria uma caixa de texto que mantém o texto
 * digitado sempre em caixa alta, ou seja, mantém o texto em letras maiúsculas.
 */

namespace Utils {

/*!
 * Construtor.
 * \param parent
 * Objeto responsável pela gerência de alocação desta instância.
 */
LineEditCheckCase::LineEditCheckCase(QWidget *parent) :
    QLineEdit(parent)
{
}

/*!
 * Destrutor.
 */
LineEditCheckCase::~LineEditCheckCase()
{}

/*!
 * Especialização do evento de pressionamento de tecla.
 * \param event
 * Descrição do evento de pressionamento de tecla.
 */
void LineEditCheckCase::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z) || event->text().compare("ç", Qt::CaseInsensitive)==0)
    {
        QLineEdit::keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, event->key(), event->modifiers(), event->text().toUpper()));
    }
    else
    {
        QLineEdit::keyPressEvent(event);
    }
}

} // namespace Utils
