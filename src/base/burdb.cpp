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
BurDb::BurDb(QString objectName, BurDebugLevel debugLevel)
    : BurSql(objectName, debugLevel)
{
}


/**
  * Destructor
  */
BurDb::~BurDb()
{
}


/**
  * Open existing Database
  */
bool BurDb::openDatabase(const QString &fileName)
{
    // close database first if open
    closeDatabase();

    // set database name
    m_dbConnection.setDatabaseName(fileName);
    
    // open database
    bool opened = m_dbConnection.open();

    // reset cache TODO
    //resetCache();

    if (opened) {
        // create models TODO
        //m_accountTreeModel  = new AccountTreeModel(this);
        //m_journalTableModel = new JournalTableModel(this);
    }

    debug("openDatabase: Database '" + fileName + "' opened", opened);

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
 
        debug("closeDatabase: Close database connection");
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


