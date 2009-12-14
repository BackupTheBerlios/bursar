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

#ifndef BURDBCREATOR_H
#define BURDBCREATOR_H

#include "bursql.h"
#include "burdbcreationparams.h"


class BurDbCreator : public BurSql
{
    Q_OBJECT

public:
    BurDbCreator(const BurDebugLevel debugLevel);
    ~BurDbCreator();

    void setParameters(BurDbCreationParams *params);

    bool createDatabase(QSqlDatabase dbConnection,
                        const QString &fileName);

private:
    void deleteFile(const QString &fileName);
    bool createTables(QSqlDatabase dbConnection);
    bool addBaseCurrency(QSqlDatabase dbConnection);
    bool initSettings(QSqlDatabase dbConnection);

    QString sqlCreateTableSettings() const;
    QString sqlCreateTableCurrencies() const;
    QString sqlCreateTableCountries() const;
    QString sqlCreateTableAccountTypes() const;
    QString sqlCreateTableAccounts() const;
    QString sqlCreateTableTransactionTypes() const;
    QString sqlCreateTableCategories() const;
    QString sqlCreateTableTransactions() const;

    BurDbCreationParams *m_params;
};

#endif // BURDBCREATOR_H
