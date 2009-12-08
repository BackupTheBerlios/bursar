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

#include "bursql.h"
#include "burobject.h"

#include <QSqlQuery>


/*************************************************************************
 *  PUBLIC FUNCTIONS
 *************************************************************************/

/**
  * Constructor
  */
BurSql::BurSql(QString objectName, BurDebugLevel debugLevel)
    : BurObject(objectName, debugLevel)
{
    // initialise last error text
    m_lastErrorText = new QString();
}


/**
  * Constructor
  */
BurSql::~BurSql()
{
    // delete pointers
    delete m_lastErrorText;
}


/**
  * Returns last error text
  */
QString *BurSql::lastErrorText() const
{
    return m_lastErrorText;
}




/*************************************************************************
 *  PROTECTED FUNCTIONS
 *************************************************************************/

/**
  * Execute a sql query
  */
bool BurSql::executeQuery(const QString &query)
{
    QSqlQuery sql(m_dbConnection);

    // reset last error text
    resetLastErrorText();

    // run query
    sql.exec(query);

    // debug information
    if (debugLevel() == FULL) {
        debug("executeQuery: " + query);
    } 

    // check result
    if (sql.lastError().type() == QSqlError::NoError) {
        return true;
    } else {
        // set last error text
        setLastErrorText(sql.lastError());

        return false;
    }
}


/**
  * Reset last error text
  */
void BurSql::resetLastErrorText()
{
    m_lastErrorText->clear();
}


/**
  * Set last errror text from sql error
  */
void BurSql::setLastErrorText(const QSqlError &error)
{
    m_lastErrorText->clear();
    m_lastErrorText->append(error.text());

    if (debugLevel() == FULL) {
        debug("setLastErrorText: " + error.text() + " (" +
              QString::number(error.number()) + ")");
    }
}


/**
  * Set last errror text from string
  */
void BurSql::setLastErrorText(const QString &error)
{
    m_lastErrorText->clear();
    m_lastErrorText->append(error);

    if (debugLevel() == FULL) {
        debug("setLastErrorText: " + error);
    }
}
