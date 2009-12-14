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

#include "burdbcreator.h"
#include "constants.h"

#include <QFile>
#include <QSqlQuery>
#include <QVariant>


/*************************************************************************
 *  PUBLIC FUNCTIONS
 *************************************************************************/

/**
  * Constructor
  */
BurDbCreator::BurDbCreator(const BurDebugLevel debugLevel)
    : BurSql(debugLevel)
{
    // set object name
    setObjectName("BurDbCreator");

    // create parameters
    m_params = new BurDbCreationParams();
}


/**
  * Destructor
  */
BurDbCreator::~BurDbCreator()
{
    // delete pointers
    delete m_params;
}


/**
  * Set parameters
  */
void BurDbCreator::setParameters(BurDbCreationParams *params)
{
    m_params = params;
}


/**
  * Create database
  */
bool BurDbCreator::createDatabase(QSqlDatabase dbConnection,
                                  const QString &fileName)
{
    // delete file if it already exists
    deleteFile(fileName);

    // set database name
    dbConnection.setDatabaseName(fileName);

    // open database which will automatically create it
    bool created = dbConnection.open();

    // create tables
    if (created) created = createTables(dbConnection);

    // add base currency
    if (created) created = addBaseCurrency(dbConnection);

    if (created) {
        // initialise settings
        created = initSettings(dbConnection);
    }

    if (created) {
        // import initial data from xml
//        created = importFromXml(DB_TEMPLATES_DIR "en_gb.xml");
    }
}




/*************************************************************************
 *  PRIVATE FUNCTIONS
 *************************************************************************/

/**
  * Delete file if it already exists
  */
void BurDbCreator::deleteFile(const QString &fileName)
{
    if (QFile::exists(fileName)) {
        debug(MINIMAL, "Delete file '" + fileName + "'");
        QFile::remove(fileName);
    }
}


/**
  * Create tables for a new database
  */
bool BurDbCreator::createTables(QSqlDatabase dbConnection)
{
    bool created = executeQuery(dbConnection, sqlCreateTableCurrencies());

    if (created) created = executeQuery(dbConnection, sqlCreateTableCountries());
    if (created) created = executeQuery(dbConnection, sqlCreateTableAccountTypes());
    if (created) created = executeQuery(dbConnection, sqlCreateTableAccounts());
    if (created) created = executeQuery(dbConnection, sqlCreateTableTransactionTypes());
    if (created) created = executeQuery(dbConnection, sqlCreateTableCategories());
    if (created) created = executeQuery(dbConnection, sqlCreateTableTransactions());
    if (created) created = executeQuery(dbConnection, sqlCreateTableSettings());

    debug(FULL, "createTables: Created tables", created);

    return created;
}


/**
  * Add base currency
  */
bool BurDbCreator::addBaseCurrency(QSqlDatabase dbConnection)
{
    QSqlQuery sql(dbConnection);
    bool result = false;

    // build sql statement
    sql.prepare("INSERT INTO " TBL_CURRENCIES "("
                FLD_CURRENCY_CODE "," FLD_CURRENCY_NAME "," FLD_CURRENCY_SYMBOL ")"
                "VALUES (:code, :name, :symbol)");

    sql.bindValue(":code", m_params->currencyCode());
    sql.bindValue(":name", m_params->currencyName());
    sql.bindValue(":symbol", m_params->currencySymbol());

    debug(FULL, "addBaseCurrency: " + sql.lastQuery());

    // run statement
    if (sql.exec()) {
        result = true;
    } else {
        // set last error text
        setLastErrorText(sql.lastError());
    }

    debug(FULL, "addBaseCurrency", result);

    return result;
}


/**
  * Initialise settings
  */
bool BurDbCreator::initSettings(QSqlDatabase dbConnection)
{
    QSqlQuery sql;

    // prepare sql statement
    sql.prepare("INSERT INTO " TBL_SETTINGS " (" FLD_DB_TITLE "," FLD_DB_DESCR "," FLD_DB_VERSION ","
                FLD_DECIMAL_DIGITS "," FLD_CURRENCY_CODE ") "
                "VALUES(:title, :descr, :version, :digits, :currency)");
    sql.bindValue(":title", m_params->databaseTitle());
    sql.bindValue(":descr", m_params->databaseDescr());
    sql.bindValue(":version", DB_VERSION);
    sql.bindValue(":digits", m_params->decimalDigits());
    sql.bindValue(":currency", m_params->currencyCode());

    // run statement
    if (sql.exec()) {
        return true;
    } else {
        // set last error text
        setLastErrorText(sql.lastError());

        return false;
    }
}


/**
  * Returns create statement for table SETTINGS
  */
QString BurDbCreator::sqlCreateTableSettings() const
{
    return "CREATE TABLE " + QString(TBL_SETTINGS) + " (" +
           sqlField(FLD_DB_TITLE, "TEXT", MAX_DB_TITLE) + "," +
           sqlField(FLD_DB_VERSION, "TEXT", MAX_DB_VERSION) + "," +
           sqlField(FLD_DB_DESCR, "TEXT", MAX_DB_DESCR) + "," +
           sqlField(FLD_CURRENCY_CODE, "TEXT", MAX_CURRENCY_CODE) + "," +
           sqlField(FLD_DECIMAL_DIGITS, "INTEGER") +
           ")";
}


/**
  * Returns create statement for table CURRENCIES
  */
QString BurDbCreator::sqlCreateTableCurrencies() const
{
    return "CREATE TABLE " + QString(TBL_CURRENCIES) + "(" +
           sqlField(FLD_CURRENCY_CODE, "TEXT", MAX_CURRENCY_CODE, true) + "," +
           sqlField(FLD_CURRENCY_NAME, "TEXT", MAX_CURRENCY_NAME, true) + "," +
           sqlField(FLD_CURRENCY_SYMBOL, "TEXT", MAX_CURRENCY_SYMBOL) + "," +
           "PRIMARY KEY(" + QString(FLD_CURRENCY_CODE) + ")"
           ")";
}


/**
  * Returns create statement for table COUNTRIES
  */
QString BurDbCreator::sqlCreateTableCountries() const
{
    return "CREATE TABLE " + QString(TBL_COUNTRIES) + "(" +
           sqlField(FLD_COUNTRY_CODE, "TEXT", MAX_COUNTRY_CODE, true) + "," +
           sqlField(FLD_COUNTRY_NAME, "TEXT", MAX_COUNTRY_NAME, true) + ","
           "PRIMARY KEY(" + QString(FLD_COUNTRY_CODE) + ")"
           ")";
}


/**
  * Returns create statement for table ACCOUNT_TYPES
  */
QString BurDbCreator::sqlCreateTableAccountTypes() const
{
    return "CREATE TABLE " + QString(TBL_ACCOUNT_TYPES) + "(" +
           sqlField(FLD_ACCOUNT_TYPE_CODE, "TEXT", MAX_ACCOUNT_TYPE_CODE, true) + "," +
           sqlField(FLD_ACCOUNT_TYPE_NAME, "TEXT", MAX_ACCOUNT_TYPE_NAME, true) + ","
           "PRIMARY KEY(" + QString(FLD_ACCOUNT_TYPE_CODE) + ")"
           ")";
}


/**
  * Returns create statement for table TRANSACTION_TYPES
  */
QString BurDbCreator::sqlCreateTableTransactionTypes() const
{
    return "CREATE TABLE " + QString(TBL_TRANSACTION_TYPES) + "(" +
           sqlField(FLD_TRANSACTION_TYPE_CODE, "TEXT", MAX_TRANSACTION_TYPE_CODE, true) + "," +
           sqlField(FLD_TRANSACTION_TYPE_NAME, "TEXT", MAX_TRANSACTION_TYPE_NAME, true) + "," +
           "PRIMARY KEY(" + QString(FLD_TRANSACTION_TYPE_CODE) + ")"
           ")";
}


/**
  * Returns create statement for table ACCOUNTS
  */
QString BurDbCreator::sqlCreateTableAccounts() const
{
    return "CREATE TABLE ACCOUNTS ("
           "   ACT_ID INTEGER PRIMARY KEY,"
           "   ACT_NAME VARCHAR(30) NOT NULL,"
           "   ACT_TYPE_CODE VARCHAR(3) NOT NULL,"
           "   ACT_CODE VARCHAR(20),"
           "   BANK_NAME VARCHAR(30),"
           "   BANK_CODE VARCHAR(20),"
           "   CUR_CODE VARCHAR(3) NOT NULL,"
           "   CTY_CODE VARCHAR(3) NOT NULL,"
           "   ACT_NOTES VARCHAR(1024),"
           "   ACT_BALANCE DECIMAL(8, 2),"
           "   CONSTRAINT COUNTRIES_FK FOREIGN KEY (CTY_CODE) REFERENCES COUNTRIES (CTY_CODE) ON DELETE RESTRICT,"
           "   CONSTRAINT CURRENCIES_FK FOREIGN KEY (CUR_CODE) REFERENCES CURRENCIES (CUR_CODE) ON DELETE RESTRICT,"
           "   CONSTRAINT ACCOUNT_TYPES_FK FOREIGN KEY (ACT_TYPE_CODE) REFERENCES ACCOUNT_TYPES (ACT_TYPE_CODE) ON DELETE RESTRICT"
           ")";
}





/**
  * Returns create statement for table CATEGRORIES
  */
QString BurDbCreator::sqlCreateTableCategories() const
{
    return "CREATE TABLE CATEGORIES ("
           "   CAT_ID INTEGER PRIMARY KEY,"
           "   CAT_NAME VARCHAR(30) NOT NULL,"
           "   CAT_TYPE VARCHAR(1) NOT NULL"
           ")";
}


/**
  * Returns create statement for table TRANSACIONS
  */
QString BurDbCreator::sqlCreateTableTransactions() const
{
    return "CREATE TABLE TRANSACTIONS ("
           "   TRN_ID INTEGER PRIMARY KEY,"
           "   ACT_ID INTEGER NOT NULL,"
           "   CAT_ID INTEGER NOT NULL,"
           "   TRN_DATE DATE NOT NULL,"
           "   TRN_TYPE_CODE VARCHAR(3) NOT NULL,"
           "   TRN_MEMO VARCHAR(300),"
           "   TRN_AMOUNT DECIMAL(8, 2),"
           "   TRN_RECONCILED VARCHAR(1) DEFAULT 'N',"
           "   TRN_CHEQUE_NO VARCHAR(15),"
           "   CONSTRAINT ACCOUNTS_FK FOREIGN KEY (ACT_ID) REFERENCES ACCOUNTS (ACT_ID) ON DELETE CASCADE,"
         //  "   CONSTRAINT TRANSACTION_TYPES_FK FOREIGN KEY (TRN_TYPE_CODE) REFERENCES TRANSACTION_TYPES (TRN_TYPE_CODE) ON DELETE RESTRICT,"
           "   CONSTRAINT CATEGORIES_FK FOREIGN KEY (CAT_ID) REFERENCES CATEGORIES (CAT_ID) ON DELETE RESTRICT"
           ")";
}
