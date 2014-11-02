/* ----------------------------------------------------------------------
 * Arquivo: ipropertygetset.cpp
 * Descrição: Arquivo de implementação parcial da classe abstrata Utils::IPropertyGetSet
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#include "ipropertygetset.h"

/*!
 * \class Utils::IPropertyGetSet
 * Interface que permite atribuir e consultar valores de
 * propriedades a partir de seus nomes.
 */

namespace Utils {

/*!
 * Construtor padrão.
 */
IPropertyGetSet::IPropertyGetSet()
{}

/*!
 * Destrutor.
 */
IPropertyGetSet::~IPropertyGetSet()
{}

/*!
 * \fn Utils::IPropertyGetSet::getPropertyValue
 * Método de consulta ao valor atual de uma propriedade.
 * \param propertyName
 * O nome da propriedade a ser consultada.
 * \return
 * O valor atual da propriedade consultada. Retorna um QVariant inválido no caso de um nome
 * inválido de propriedade ter sido informado. Este método deve ser implementado pelas classes
 * que utilizam esta interface.
 */

/*!
 * \fn Utils::IPropertyGetSet::setPropertyValue
 * Método de ajuste do valor de propriedades.
 * \param propertyName
 * Nome da propriedade a ser ajustada.
 * \param newValue
 * Novo valor para a propriedade
 * \return
 * Se o valor foi ou não ajustado com sucesso.
 */

} // namespace Utils
