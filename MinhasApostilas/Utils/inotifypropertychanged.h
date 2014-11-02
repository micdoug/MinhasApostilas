/* ----------------------------------------------------------------------
 * Arquivo: inotifypropertychanged.h
 * Descrição: Arquivo de declaração da classe abstrata Utils::INotifyPropertyChanged
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#ifndef UTILS_INOTIFYPROPERTYCHANGED_H
#define UTILS_INOTIFYPROPERTYCHANGED_H

#include <QList>
#include <QString>
#include <QVariant>
#include <functional>

namespace Utils
{
    //Typedefs for function and list of functions that helps emiting signals about property changes
    typedef std::function<void(const QString &propertyName, const QVariant &newValue)> NotifyPropertyChangedFunction;
    typedef QList<NotifyPropertyChangedFunction> NotifyPropertyChangedObservers;

    class INotifyPropertyChanged
    {
    public:
        //Constructors and destructors
        INotifyPropertyChanged();
        virtual ~INotifyPropertyChanged();

        //Methods to manage observers
        void addObserver(NotifyPropertyChangedFunction function);
        void clearObservers();
        void refresh();

    protected:
        //Methods to emit signals about property changes
        void emitPropertyChanged(const QString &propertyName, const QVariant &newValue);
        virtual void emitAllPropertiesChanged() = 0;

    private:
        NotifyPropertyChangedObservers m_observers;
    };

} // namespace Utils

#endif // UTILS_INOTIFYPROPERTYCHANGED_H
