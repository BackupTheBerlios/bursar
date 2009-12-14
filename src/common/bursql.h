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

#ifndef BURSQL_H
#define BURSQL_H

#include "burobject.h"

#include <QString>
#include <QSqlError>
#include <QSqlDatabase>


class BurSql : public BurObject
{
    Q_OBJECT

public:
    BurSql(BurDebugLevel debugLevel);
    ~BurSql();

    QSqlDatabase dbConnection() const;

    QString *lastErrorText() const;

protected:
    bool executeQuery(const QSqlDatabase dbConnection, const QString &query);

    void resetLastErrorText();
    void setLastErrorText(const QSqlError &error);
    void setLastErrorText(const QString &text);

    QString sqlField(const QString &name, const QString &type,
                     int size = 0, bool notNull = false) const;
private:
    // last error text
    QString *m_lastErrorText;
};

#endif // BURSQL_H
