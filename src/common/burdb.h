/*************************************************************************
 *
 *                   Bursar - Personal Finance Manager
 *
 *  Copyright (c) 2009 by Marco Auer <marco@marcoauer.com>
 *
 *  This file is part of the Bursar project <http://bursar.berlios.de>
 *
 *  Bursar is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Bursar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Bursar. If not, see <http://www.gnu.org/licenses/>.
 *
 *************************************************************************/

#ifndef BURDB_H
#define BURDB_H

#include "bursql.h"

#include <QString>
#include <QSqlDatabase>

class BurDb : public BurSql
{
    Q_OBJECT

public:
    BurDb(BurDebugLevel debugLevel);
    ~BurDb();

    QSqlDatabase dbConnection() const;

    bool openDatabase(const QString &fileName);
    void closeDatabase();

    bool isOpen() const;

protected:

private:
    void initDbConnection();
    void setFileName(const QString &fileName);

    // database connection
    QSqlDatabase m_dbConnection;
};

#endif // BURSQL_H
