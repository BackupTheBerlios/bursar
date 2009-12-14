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

#include "burdb.h"


/*************************************************************************
 *  PUBLIC FUNCTIONS
 *************************************************************************/

/**
  * Constructor
  */
BurDb::BurDb(BurDebugLevel debugLevel)
    : BurSql(debugLevel)
{
    // initialise database connection
    initDbConnection();
}


/**
  * Destructor
  */
BurDb::~BurDb()
{
}


/**
  * Returns the DB connection
  */
QSqlDatabase BurDb::dbConnection() const
{
    return m_dbConnection;
}


/**
  * Open existing Database
  */
bool BurDb::openDatabase(const QString &fileName)
{
    // close database first if open
    closeDatabase();

    // set file name
    setFileName(fileName);
    
    // open database
    bool opened = m_dbConnection.open();

    // reset cache TODO
    //resetCache();

    if (opened) {
        // create models TODO
        //m_accountTreeModel  = new AccountTreeModel(this);
        //m_journalTableModel = new JournalTableModel(this);
    } else {
        setLastErrorText(m_dbConnection.lastError());
    }

    debug(FULL, "openDatabase: Database '" + fileName + "' opened", opened);

    return opened;
}


/**
  * Close Database
  */
void BurDb::closeDatabase()
{
    if (isOpen()) {
        // close connection
        m_dbConnection.close();
 
        debug(FULL, "closeDatabase: Closed database connection");
   }
}


/**
  * Returns if a database is open
  */
bool BurDb::isOpen() const
{
    return m_dbConnection.isOpen();
}




/*************************************************************************
 *  PROTECTED FUNCTIONS
 *************************************************************************/




/*************************************************************************
 *  PRIVATE FUNCTIONS
 *************************************************************************/

/**
  * Initialize db connection
  */
void BurDb::initDbConnection()
{
    m_dbConnection = QSqlDatabase::addDatabase("QSQLITE");
}


/**
  * Set file name of database
  */
void BurDb::setFileName(const QString &fileName)
{
    debug(FULL, "setFileName: " + fileName);

    m_dbConnection.setDatabaseName(fileName);
}
