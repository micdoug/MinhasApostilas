#include "inotifypropertychanged.h"

/*!
 * \class Utils::INotifyPropertyChanged
 * Interface that helps entities emit signals letting observers know about
 * property values changes at runtime.
 */

namespace Utils
{

/*!
 * Default constructor
 */
INotifyPropertyChanged::INotifyPropertyChanged()
{}

/*!
 * Default virtual destructor
 */
INotifyPropertyChanged::~INotifyPropertyChanged()
{}

/**
 * Register a new observer in the list of observers
 * @param function
 * A function object that will be called when properties change their values
 */
void INotifyPropertyChanged::addObserver(NotifyPropertyChangedFunction function)
{
    m_observers.append(function);
}

/*!
 * Remove all observers from the list of observers
 */
void INotifyPropertyChanged::clearObservers()
{
    m_observers.clear();
}

/**
 * Calls emitAllPropertiesChanged.
 */
void INotifyPropertyChanged::refresh()
{
    emitAllPropertiesChanged();
}

/*!
 * Call this property to emit a property changed signal
 * \param propertyName
 * The name of the property changed
 * \param newValue
 * The new value of the property
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
 * Emit several signals informing to the observers that all the properties changed their values
 */

} // namespace Utils
