/*
 * Orm4Qt - An Object Relational Mapping Library for the Qt Framework
 * Copyright (c) 2014, Michael Dougras da Silva, All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 */

#ifndef ORM4QT_POSTGRESQLPROVIDER_H
#define ORM4QT_POSTGRESQLPROVIDER_H

#include "standardsqlprovider.h"

namespace Orm4Qt {

    class PostgreSqlProvider : public StandardSqlProvider
    {
    public:
        PostgreSqlProvider(const QString &user, const QString &password, const QString &database,
                           const QString &host = QString("localhost"), int port=5432);
        virtual ~PostgreSqlProvider();

        // SqlProvider interface
        virtual std::shared_ptr<QSqlQuery> generateCreateTable(Class *reflect);
    };

} // namespace Orm4Qt

#endif // ORM4QT_POSTGRESQLPROVIDER_H
