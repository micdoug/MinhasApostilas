/* ----------------------------------------------------------------------
 * Arquivo: number.cpp
 * Descrição: Arquivo de implementação da classe Utils::Number
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#include "number.h"

/*!
 * \class Utils::Number
 * Classe com métodos estáticos que auxiliam no tratamento de valores numéricos.
 * Este classe não pode ser instanciada.
 */

namespace Utils {

/*!
 * Construtor privado.
 */
Number::Number()
{
}

/*!
 * Divide dois números inteiros retornando o resultado com
 * arredondamento sempre para a borda superior. Por exemplo,
 * se for executado com os valores 5 e 2, o método retorna 3.
 * \param a
 * Primeiro termo da divisão.
 * \param b
 * Segundo termo da divisão.
 * \return
 * Resultado com arredondamento para borda superior.
 */
qint32 Number::divRoundUp(qint32 a, qint32 b)
{
    double result = 0, rounded = 0;
    result = a * 1.0 / b;
    rounded = qRound(result);
    if(result == rounded || rounded > result)
    {
        return static_cast<qint32>(rounded);
    }
    else
    {
        return static_cast<qint32>(rounded)+1;
    }
}

} // namespace Utils
