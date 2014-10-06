#ifndef UTILS_IPROPERTYGETSET_H
#define UTILS_IPROPERTYGETSET_H

#include <QString>
#include <QVariant>

namespace Utils
{
    class IPropertyGetSet
    {
    public:
        //Constructors and destructors
        IPropertyGetSet();
        virtual ~IPropertyGetSet();

        //Methods to set and get property values
        virtual bool setPropertyValue(const QString &propertyName, const QVariant &newValue) = 0;
        virtual QVariant getPropertyValue(const QString &propertyName) = 0;
    };
} // namespace Utils

#endif // UTILS_IPROPERTYGETSET_H
