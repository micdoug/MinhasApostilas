/* ----------------------------------------------------------------------
 * Arquivo: texteditwatcher.cpp
 * Descrição: Arquivo de declaração da classe Utils::TextEditWatcher
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/


#include "texteditwatcher.h"

/*!
 * \class Utils::TextEditWatcher
 * Especialização do componente QPlainTextEdit do framework Qt.
 * Esta especialização mantém o texto digitado sempre em caixa alta,
 * ou seja, sempre com letras maiúsculas. Também adiciona um sinal para informar
 * que o usuário terminou de editar o texto, e ignora a tecla tab como inserção de
 * tabulação no texto (o componente perde o foco quando a tecla tab é pressionada).
 */

namespace Utils {

/*!
 * Construtor
 * \param parent
 * Método responsável por gerenciar a alocação desta instância.
 */
TextEditWatcher::TextEditWatcher(QWidget *parent) :
    QPlainTextEdit(parent)
{}

/*!
 * Destrutor.
 */
TextEditWatcher::~TextEditWatcher()
{}

/*!
 * Reimplementação do evento de perda de foco.
 * \param event
 * Descrição do evento de perda de foco.
 */
void TextEditWatcher::focusOutEvent(QFocusEvent *event)
{
    emit editingFinished(toPlainText());
    QPlainTextEdit::focusOutEvent(event);
}

/*!
 * Reimplementação do evento de pressionamento de tecla.
 * \param event
 * Descrição do evento de pressionamento de tecla.
 */
void TextEditWatcher::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Tab)
    {
        event->ignore();
    }
    else if ((event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z) || event->text().compare("ç", Qt::CaseInsensitive)==0)
    {
        QPlainTextEdit::keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, event->key(), event->modifiers(), event->text().toUpper()));
    }
    else
    {
        QPlainTextEdit::keyPressEvent(event);
    }
}

} // namespace Utils
