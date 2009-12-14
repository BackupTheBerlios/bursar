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

#ifndef BURDBCREATIONPARAMS_H
#define BURDBCREATIONPARAMS_H

#include "burobject.h"


class BurDbCreationParams : public BurObject
{
    Q_OBJECT

public:
    BurDbCreationParams();

    QString databaseTitle() const;
    QString databaseDescr() const;

    int decimalDigits() const;

    QString& currencyCode() const;
    QString currencyName() const;
    QString currencySymbol() const;

    void setDatabaseTitle(const QString &databaseTitle);
    void setDatabaseDescr(const QString &databaseDescr);

    void setDecimalDigits(const int decimalDigits);

    void setCurrencyCode(const QString &currencyCode);
    void setCurrencyName(const QString &currencyName);
    void setCurrencySymbol(const QString &currencySymbol);

private:
    QString m_databaseTitle;
    QString m_databaseDescr;

    int m_decimalDigits;

    QString m_currencyCode;
    QString m_currencyName;
    QString m_currencySymbol;
};

#endif // BURDBCREATIONPARAMS_H
