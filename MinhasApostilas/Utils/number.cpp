#include "number.h"

namespace Utils {

Number::Number()
{
}

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
