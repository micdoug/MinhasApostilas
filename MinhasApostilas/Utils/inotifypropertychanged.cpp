/* ----------------------------------------------------------------------
 * Arquivo: inotifypropertychanged.h
 * Descrição: Arquivo de implementação parcial da classe abstrata Utils::INotifyPropertyChanged
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#include "inotifypropertychanged.h"

/*!
 * \typedef Utils::NotifyPropertyChangedFunction
 * Tipo de "function object" que deve ser registrada como um observador.
 */

/*!
 * \typedef Utils::NotifyPropertyChangedObservers
 * Apelido para uma lista de "function objects" registrada como observadores.
 */

/*!
 * \class Utils::INotifyPropertyChanged
 * Interface que permite a uma classe herdada que informe uma lista de observadores
 * sobre mudanças de valores em suas propriedades.
 */

/*!
 * Engloba classes de uso geral no projeto.
 */
namespace Utils
{

/*!
 * Construtor padrão.
 */
INotifyPropertyChanged::INotifyPropertyChanged()
{}

/*!
 * Destrutor.
 */
INotifyPropertyChanged::~INotifyPropertyChanged()
{}

/*!
 * Registra um novo observador na lista de observadores.
 * @param function
 * Uma "function object" que será chamada quando alguma propriedade tiver seu valor modificado.
 */
void INotifyPropertyChanged::addObserver(NotifyPropertyChangedFunction function)
{
    m_observers.append(function);
}

/*!
 * Remove todos os observadores registrados anteriormente.
 */
void INotifyPropertyChanged::clearObservers()
{
    m_observers.clear();
}

/*!
 * Executa o método Utils::INotifyPropertyChanged::emitAllPropertiesChanged.
 */
void INotifyPropertyChanged::refresh()
{
    emitAllPropertiesChanged();
}

/*!
 * Método que deve ser chamado para informar os observadores sobre mudanças de valores em propriedades.
 * \param propertyName
 * Nome da propriedade que teve seu valor modificado.
 * \param newValue
 * Novo valor adquirido pela propriedade.
 */
void INotifyPropertyChanged::emitPropertyChanged(const QString &propertyName, const QVariant &newValue)
{
    for(NotifyPropertyChangedFunction func : m_observers)
    {
        func(propertyName, newValue);
    }
}

/*!
 * \fn Utils::INotifyPropertyChanged::emitAllPropertiesChanged
 * Emite vários sinais informando aos observadores de que todas as propriedades do objeto tiveram seus valores
 * modificados. Este método deve ser reimplementado pelas classes que herdam esta interface.
 */

} // namespace Utils
