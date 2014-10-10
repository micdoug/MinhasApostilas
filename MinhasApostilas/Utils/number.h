#ifndef UTILS_NUMBER_H
#define UTILS_NUMBER_H

#include <QtGlobal>

namespace Utils {

class Number
{
public:
    Number();

    //Interface estática
public:
    static qint32 divRoundUp(qint32 a, qint32 b);
};

} // namespace Utils

#endif // UTILS_NUMBER_H
