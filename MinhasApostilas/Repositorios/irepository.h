#ifndef REPOSITORIES_IREPOSITORY_H
#define REPOSITORIES_IREPOSITORY_H

#include <QList>
#include <QMap>
#include <QString>
#include <QVariant>

namespace Repositorios {

    template<class T> class IRepository
    {
    public:
        IRepository(){}
        virtual ~IRepository(){}

        //Get the lastError
        QString lastError() const
        {
            return m_lastError;
        }

        //Abstract methods
        virtual bool createObject(T &object) = 0;
        virtual bool updateObject(T &object) = 0;
        virtual bool deleteObject(T &object) = 0;
        virtual bool selectObjects(QList<T> &list, QMap<QString, QVariant> filters) = 0;
        virtual bool countObjects(int &count, QMap<QString, QVariant> filters) = 0;
        virtual bool getObject(const QVariant &id, T &object) = 0;

    protected:
        //Set the last error description
        void setLastError(const QString &error)
        {
            m_lastError = error;
        }

    private:
        QString m_lastError;

    };

} // namespace Repositories

#endif // REPOSITORIES_IREPOSITORY_H
