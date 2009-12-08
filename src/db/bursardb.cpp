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

#include "bursardb.h"

#include "constants.h"
#include "config.h"
#include "utils.h"

#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QIcon>
#include <QSqlDriverCreator>
#include <QSqlQuery>
#include <QVariant>


/*************************************************************************
 *  PUBLIC FUNCTIONS
 *************************************************************************/

/**
  * Constructor
  */
BursarDb::BursarDb()
{
    // initialise database connection
    m_dbConnection = QSqlDatabase::addDatabase("QSQLITE");

    // initialise last error text
    m_lastErrorText = new QString();

    // initialise system locale
    m_locale = new QLocale(QLocale::system());

    // reset cache
    resetCache();
}


/**
  * Destructor
  */
BursarDb::~BursarDb()
{
    QStringList connections = QSqlDatabase::connectionNames();

    for (int i = 0; i < connections.count(); i++) {
        qDebug() << connections.at(i);
        QSqlDatabase::removeDatabase(connections.at(i));
    }

    delete m_lastErrorText;
    delete m_locale;
}


/**
  * Create new database
  */
bool BursarDb::createDatabase(const QString &dbTitle, const QString &dbDescr,
                              const QString &fileName, const int decDigits,
                              const QString &curCode, const QString &curName,
                              const QString &curSymbol)
{
    // delete file if already existing
    if (QFile::exists(fileName)) {
        QFile::remove(fileName);
    }

    // set database name
    m_dbConnection.setDatabaseName(fileName);

    // open database which will automatically create it
    bool created = m_dbConnection.open();

    debug("createDatabase: Database '" + fileName + "' created", created);

    if (created) {
        // create tables
        created = createTables();
    }

    if (created) {
        // add base currency
        created = addBaseCurrency(curCode, curName, curSymbol);
    }

    if (created) {
        // initialise settings
        created = initSettings(dbTitle, dbDescr, decDigits, curCode);
    }

    if (created) {
        // import initial data from xml
        created = importFromXml(DB_TEMPLATES_DIR "en_gb.xml");
    }

    // reset cache
    resetCache();

    return created;
}


/**
  * Open existing Database
  */
bool BursarDb::openDatabase(const QString &fileName)
{
    if (isOpen()) {
        closeDatabase();
    }

    // set database name
    m_dbConnection.setDatabaseName(fileName);
    
    // open database
    bool opened = m_dbConnection.open();

    // reset cache
    resetCache();

    if (opened) {
        // create models
        m_accountTreeModel  = new AccountTreeModel(this);
        m_journalTableModel = new JournalTableModel(this);
    }

    debug("openDatabase: Database '" + fileName + "' opened", opened);

    return opened;
}


/**
  * Close Database
  */
void BursarDb::closeDatabase()
{
    debug("Close database connection");

    if (isOpen()) {
        // release models
        //delete m_accountTreeModel;
        m_journalTableModel->clear();
        //delete m_journalTableModel;

        // close connection
        m_dbConnection.close();
    }
}


/**
  * Returns the DB connection
  */
QSqlDatabase BursarDb::dbConnection() const
{
    return m_dbConnection;
}


/**
  * Returns last error text
  */
QString *BursarDb::lastErrorText() const
{
    return m_lastErrorText;
}


/**
  * Returns if a database is open
  */
bool BursarDb::isOpen() const
{
    return m_dbConnection.isOpen();
}


/**
  * Returns the database title
  */
QString BursarDb::databaseTitle()
{
    QSqlQuery query(m_dbConnection);

    // build sql statement
    query.prepare("SELECT " FLD_DB_TITLE " FROM " TBL_SETTINGS);

    // run statement
    if (query.exec()) {
        // go to first record
        query.first();

        // return value
         return query.value(0).toString();
    } else {
        // set last error text
        setLastErrorText(query.lastError());

        // return empty string as fallback
        return "";
    }
}


/**
  * Returns the database description
  */
QString BursarDb::databaseDescr()
{
    QSqlQuery query(m_dbConnection);

    // build sql statement
    query.prepare("SELECT " FLD_DB_DESCR " FROM " TBL_SETTINGS);

    // run statement
    if (query.exec()) {
        // go to first record
        query.first();

        // return value
        return query.value(0).toString();
    } else {
        // set last error text
        setLastErrorText(query.lastError());

        // return empty string as fallback
        return "";
    }
}


/**
  * Returns the account tree model
  */
AccountTreeModel *BursarDb::accountTreeModel()
{
    return m_accountTreeModel;
}


/**
  * Returns the journal table model
  */
JournalTableModel *BursarDb::journalTableModel()
{
    return m_journalTableModel;
}


/**
  * Returns the decimal digits
  */
int BursarDb::decimalDigits()
{
    if (m_decimalDigits == -1) {
        QSqlQuery query(m_dbConnection);

        // build sql statement
        query.prepare("SELECT " FLD_DECIMAL_DIGITS " FROM " TBL_SETTINGS);

        // run statement
        if (query.exec()) {
            // go to first record
            query.first();

            // set cache to improve performance
            m_decimalDigits = query.value(0).toInt();

            // return value
            return m_decimalDigits;
        } else {
            // set last error text
            setLastErrorText(query.lastError());

            // return 2 as fallback
            return 2;
        }
    } else {
        return m_decimalDigits;
    }
}


/**
  * Set database title
  */
bool BursarDb::setDatabaseTitle(const QString &title)
{
    QSqlQuery query;
    bool result = false;

    // build sql statement
    query.prepare("UPDATE " TBL_SETTINGS " SET " FLD_DB_TITLE "=:title");
    query.bindValue(":title", title);

    // run statement
    if (query.exec()) {
        result = true;
    } else {
        // set last error text
        setLastErrorText(query.lastError());
    }

   debug("setDatabaseTitle: Set database title", result);

   return result;
}


/**
  * Add a new account
  */
bool BursarDb::addAccount(const QString &accountName, const QString &accountType,
                          const QString &countryCode, const QString &currencyCode)
{
    QSqlQuery query;
    bool result = false;

    // build sql statement
    query.prepare("INSERT INTO " TBL_ACCOUNTS "("
                  FLD_ACCOUNT_NAME "," FLD_ACCOUNT_TYPE_CODE ","
                  FLD_COUNTRY_CODE "," FLD_CURRENCY_CODE ","
                  FLD_ACCOUNT_BALANCE ")"
                  "VALUES (:name, :type, :country, :currency, :balance)");
    query.bindValue(":name", accountName);
    query.bindValue(":type", accountType);
    query.bindValue(":country", countryCode);
    query.bindValue(":currency", currencyCode);
    query.bindValue(":balance", 0);

    debug("addAccount " + query.lastQuery());

    // run statement
    if (query.exec()) {
        result = true;
    } else {
        // set last error text
        setLastErrorText(query.lastError());
    }

    debug("addAccount: Add new account", result);

    return result;
}


/**
  * Add base currency
  */
bool BursarDb::addBaseCurrency(const QString &code, const QString &name,
                               const QString &symbol)
{
    QSqlQuery sql;
    bool result = false;

    // build sql statement
    sql.prepare("INSERT INTO " TBL_CURRENCIES "("
                FLD_CURRENCY_CODE "," FLD_CURRENCY_NAME "," FLD_CURRENCY_SYMBOL ")"
                "VALUES (:code, :name, :symbol)");
    sql.bindValue(":code", code);
    sql.bindValue(":name", name);
    sql.bindValue(":symbol", symbol);

    // run statement
    if (sql.exec()) {
        result = true;
    } else {
        // set last error text
        setLastErrorText(sql.lastError());
    }

    debug("createDatabase: Add base currency", result);

    return result;
}


/**
  * Get list of all account names of the selected type
  */
QList<QStandardItem *> BursarDb::accountNames(const QString &accountType)
{
    QList<QStandardItem *> list;
    QSqlQuery query(m_dbConnection);
    QStandardItem *item;
    
    // prepare sql statement
    query.prepare("SELECT " FLD_ACCOUNT_NAME "," FLD_ACCOUNT_ID " FROM " TBL_ACCOUNTS " "
                  "WHERE " FLD_ACCOUNT_TYPE_CODE "='" + accountType + "'");

    // run query
    if (query.exec()) {
        // get result
        while(query.next()) {
            item = new QStandardItem(query.value(0).toString());

            // set item properties
            item->setData(query.value(1).toString(), Qt::UserRole);
            item->setIcon(QIcon(":/icons/account.svg"));

            list.append(item);
        }
    } else {
        if (query.lastError().number() != -1)
            // set last error text
            setLastErrorText(query.lastError());
    }

    return list;
}


/**
  * Get list of all account banks of the selected type
  */
QList<QStandardItem *> BursarDb::accountBanks(const QString &accountType)
{
    QList<QStandardItem *> list;
    QSqlQuery query(m_dbConnection);
    QStandardItem *item;

    // create a red brush for negative values
    QBrush brush = QBrush(Qt::SolidPattern);
    brush.setColor(Qt::red);

    // prepare sql statement
    query.prepare("SELECT A." FLD_BANK_NAME "," FLD_ACCOUNT_ID " FROM " TBL_ACCOUNTS " "
                  "WHERE " FLD_ACCOUNT_TYPE_CODE " = '" + accountType + "'");

    // run query
    if (query.exec()) {
        // get result
        while(query.next()) {
            item = new QStandardItem(query.value(0).toString());

            // set item properties
            item->setData(query.value(1).toInt(), Qt::UserRole);
            item->setTextAlignment(Qt::AlignRight);

            list.append(item);
        }
    } else {
        if (query.lastError().number() != -1)
            // set last error text
            setLastErrorText(query.lastError());
    }

    return list;
}


/**
  * Get list of all account countries of the selected type
  */
QList<QStandardItem *> BursarDb::accountCountries(const QString &accountType)
{
    QList<QStandardItem *> list;
    QSqlQuery query(m_dbConnection);
    QStandardItem *item;

    // create a red brush for negative values
    QBrush brush = QBrush(Qt::SolidPattern);
    brush.setColor(Qt::red);

    // prepare sql statement
    query.prepare("SELECT A." FLD_ACCOUNT_BALANCE ","
                  "CASE WHEN LENGTH(B." FLD_CURRENCY_SYMBOL ") > 0 "
                  "THEN B." FLD_CURRENCY_SYMBOL " "
                  "ELSE A." FLD_CURRENCY_CODE " END, "
                  "A." FLD_ACCOUNT_ID " "
                  "FROM " TBL_ACCOUNTS " A INNER JOIN " TBL_CURRENCIES " B "
                  "ON A." FLD_CURRENCY_CODE " = B." FLD_CURRENCY_CODE " "
                  "WHERE A." FLD_ACCOUNT_TYPE_CODE " = '" + accountType + "'");

    // run query
    if (query.exec()) {
        // get result
        while(query.next()) {
            item = new QStandardItem(dblToCur(query.value(0).toDouble(),
                                              query.value(1).toString()));

            // set colour to red if smaller than 0
            if (query.value(0).toDouble() < 0)
                item->setForeground(brush);

            // set item properties
            item->setData(query.value(2).toInt(), Qt::UserRole);
            item->setTextAlignment(Qt::AlignRight);

            list.append(item);
        }
    } else {
        if (query.lastError().number() != -1)
            // set last error text
            setLastErrorText(query.lastError());
    }

    return list;
}


/**
  * Get list of all current account balances
  */
QList<QStandardItem *> BursarDb::accountBalances(const QString &accountType)
{
    QList<QStandardItem *> list;
    QSqlQuery query(m_dbConnection);
    QStandardItem *item;

    // create a red brush for negative values
    QBrush brush = QBrush(Qt::SolidPattern);
    brush.setColor(Qt::red);

    // prepare sql statement
    query.prepare("SELECT A." FLD_ACCOUNT_BALANCE ","
                  "CASE WHEN LENGTH(B." FLD_CURRENCY_SYMBOL ") > 0 "
                  "THEN B." FLD_CURRENCY_SYMBOL " "
                  "ELSE A." FLD_CURRENCY_CODE " END, "
                  "A." FLD_ACCOUNT_ID " "
                  "FROM " TBL_ACCOUNTS " A INNER JOIN " TBL_CURRENCIES " B "
                  "ON A." FLD_CURRENCY_CODE " = B." FLD_CURRENCY_CODE " "
                  "WHERE A." FLD_ACCOUNT_TYPE_CODE " = '" + accountType + "'");
    
    // run query
    if (query.exec()) {
        // get result
        while(query.next()) {
            item = new QStandardItem(dblToCur(query.value(0).toDouble(),
                                              query.value(1).toString()));

            // set colour to red if smaller than 0
            if (query.value(0).toDouble() < 0)
                item->setForeground(brush);

            // set item properties
            item->setData(query.value(2).toInt(), Qt::UserRole);
            item->setTextAlignment(Qt::AlignRight);

            list.append(item);
        }
    } else {
        if (query.lastError().number() != -1)
            // set last error text
            setLastErrorText(query.lastError());
    }

    return list;
}


/**
  * Load accounts for combobox
  */
bool BursarDb::loadAccounts(BurComboBox *comboBox)
{
    QSqlQuery query(m_dbConnection);

    // delete existing entries
    comboBox->clear();

    // build sql statement
    query.prepare("SELECT " FLD_ACCOUNT_ID "," FLD_ACCOUNT_NAME "," FLD_ACCOUNT_CODE " "
                  "FROM " TBL_ACCOUNTS);

    // run statement
    if (query.exec()) {
        // get result
        while(query.next()) {
            // add to combobox
            comboBox->addItem(query.value(1).toString() + " " + query.value(2).toString(),
                              query.value(0).toString());
        }

        return true;
    } else {
        if (query.lastError().number() != -1)
            // set last error text
            setLastErrorText(query.lastError());

        return false;
    }
}


/**
  * Load account types for combobox
  */
bool BursarDb::loadAccountTypes(BurComboBox *comboBox)
{
    QSqlQuery query(m_dbConnection);

    // delete existing entries and add blank entry
    comboBox->clear();
    comboBox->addItem(tr("<Select Account Type>"));

    // build sql statement
    query.prepare("SELECT " FLD_ACCOUNT_TYPE_CODE "," FLD_ACCOUNT_TYPE_NAME " "
                  "FROM " TBL_ACCOUNT_TYPES);

    // run statement
    if (query.exec()) {
        // get result
        while(query.next()) {
            // add to combobox
            comboBox->addItem(query.value(1).toString(),
                              query.value(0).toString());
        }

        return true;
    } else {
        if (query.lastError().number() != -1)
            // set last error text
            setLastErrorText(query.lastError());

        return false;
    }
}


/**
  * Load currencies for combobox
  */
bool BursarDb::loadCurrencies(BurComboBox *comboBox)
{
    QSqlQuery query(m_dbConnection);

    // delete existing entries and add blank entry
    comboBox->clear();
    comboBox->addItem(tr("<Select Currency>"));

    // build sql statement
    query.prepare("SELECT " FLD_CURRENCY_CODE "," FLD_CURRENCY_NAME " "
                  "FROM " TBL_CURRENCIES);

    // run statement
    if (query.exec()) {
        // get result
        while(query.next()) {
            // add to combobox
            comboBox->addItem(query.value(1).toString(),
                              query.value(0).toString());
        }

        return true;
    } else {
        if (query.lastError().number() != -1)
            // set last error text
            setLastErrorText(query.lastError());

        return false;
    }
}


/**
  * Load countries for combobox
  */
bool BursarDb::loadCountries(BurComboBox *comboBox)
{
    QSqlQuery query(m_dbConnection);

    // delete existing entries and add blank entry
    comboBox->clear();
    comboBox->addItem(tr("<Select Country>"));

    // build sql statement
    query.prepare("SELECT " FLD_COUNTRY_CODE "," FLD_COUNTRY_NAME " "
                  "FROM " TBL_COUNTRIES);

    // run statement
    if (query.exec()) {
        // get result
        while(query.next()) {
            // add to combobox
            comboBox->addItem(query.value(1).toString(),
                              query.value(0).toString());
        }

        return true;
    } else {
        if (query.lastError().number() != -1)
            // set last error text
            setLastErrorText(query.lastError());

        return false;
    }
}


/**
  * Import data from xml file
  */
bool BursarDb::importFromXml(const QString &fileName)
{
    QDomDocument doc;
    QFile file(fileName);

    // open file
    if (!file.open(QIODevice::ReadOnly)) {
        // set last error text
        setLastErrorText(tr("Could not open document '%1'").arg(fileName));

        return false;
    }

    // read file
    if (!doc.setContent(&file)) {
        setLastErrorText(tr("Could not read document '%1'").arg(fileName));
        file.close();

        return false;
    }

    // close file
    file.close();

    // get document element
    QDomElement docElement = doc.documentElement();

    // load account types
    bool imported = importXmlAccountTypes(docElement);

    // load countries
    if (imported) imported = importXmlCountries(docElement);

    // load transaction types
    if (imported) imported = importXmlTransactionTypes(docElement);

    return imported;
}




/*************************************************************************
 *  PRIVATE FUNCTIONS
 *************************************************************************/

/**
  * Create tables for a new database
  */
bool BursarDb::createTables()
{
    bool created = executeQuery(sqlCreateTableCurrencies());

    if (created) created = executeQuery(sqlCreateTableCountries());
    if (created) created = executeQuery(sqlCreateTableAccountTypes());
    if (created) created = executeQuery(sqlCreateTableAccounts());
    if (created) created = executeQuery(sqlCreateTableTransactionTypes());
    if (created) created = executeQuery(sqlCreateTableCategories());
    if (created) created = executeQuery(sqlCreateTableTransactions());
    if (created) created = executeQuery(sqlCreateTableSettings());
    
    debug("createTables: Created tables", created);
    
    return created;
}


/**
  * Execute a sql query
  */
bool BursarDb::executeQuery(const QString &query)
{
    QSqlQuery sql(m_dbConnection);

    // reset last error text
    resetLastErrorText();

    // run query
    sql.exec(query);

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
  * Initialise settings
  */
bool BursarDb::initSettings(const QString &title,  const QString &descr, int decDigits, const QString &curCode)
{
    QSqlQuery sql;

    // prepare sql statement
    sql.prepare("INSERT INTO " TBL_SETTINGS " (" FLD_DB_TITLE "," FLD_DB_DESCR "," FLD_DB_VERSION ","
                FLD_DECIMAL_DIGITS "," FLD_CURRENCY_CODE ") "
                "VALUES(:title, :descr, :version, :digits, :currency)");
    sql.bindValue(":title", title);
    sql.bindValue(":descr", descr);
    sql.bindValue(":version", DB_VERSION);
    sql.bindValue(":digits", decDigits);
    sql.bindValue(":currency", curCode);

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
  * Set database version
  */
bool BursarDb::setDbVersion()
{
    QSqlQuery query;

    // build sql statement
    query.prepare("UPDATE " TBL_SETTINGS " SET " FLD_DB_VERSION "=:version");
    query.bindValue(":version", DB_VERSION);

    // run statement
    if (query.exec()) {
        return true;
    } else {
        // set last error text
        setLastErrorText(query.lastError());

        return false;
    }
}


/**
  * Reset last error text
  */
void BursarDb::resetLastErrorText()
{
    m_lastErrorText->clear();
}


/**
  * Set last errror text from sql error
  */
void BursarDb::setLastErrorText(const QSqlError &error)
{
    m_lastErrorText->clear();
    m_lastErrorText->append(error.text());

    debug("setLastErrorText: " + error.text() + " (" +
          QString::number(error.number()) + ")");
}


/**
  * Set last errror text from string
  */
void BursarDb::setLastErrorText(const QString &error)
{
    m_lastErrorText->clear();
    m_lastErrorText->append(error);
}


/**
  * Import account types from xml file
  */
bool BursarDb::importXmlAccountTypes(QDomElement &docElement)
{
    QSqlQuery query;
    QDomNode node;
    QString code;
    QString name;

    // get element;
    QDomElement element = docElement.firstChildElement(XML_ACCOUNT_TYPES);

    // prepare sql statament
    query.prepare("INSERT INTO " TBL_ACCOUNT_TYPES
                  "(" FLD_ACCOUNT_TYPE_CODE "," FLD_ACCOUNT_TYPE_NAME ")"
                  "VALUES(:code,:name)");

    for (int i = 0; i < element.childNodes().count(); i++) {
        node = element.childNodes().item(i);

        code = node.attributes().namedItem(XML_ACCOUNT_TYPE_CODE).nodeValue();
        name = node.attributes().namedItem(XML_ACCOUNT_TYPE_NAME).nodeValue();

        query.bindValue(":code", code);
        query.bindValue(":name", name);

        if (!query.exec()) {
            // set last error text
            setLastErrorText(query.lastError());

            return false;
        }
    }

    return true;
}


/**
  * Import countries from xml file
  */
bool BursarDb::importXmlCountries(QDomElement &docElement)
{
    QSqlQuery query;
    QDomNode node;
    QString code;
    QString name;

    // get element;
    QDomElement element = docElement.firstChildElement(XML_COUNTRIES);

    // prepare sql statament
    query.prepare("INSERT INTO " TBL_COUNTRIES
                  "("FLD_COUNTRY_CODE "," FLD_COUNTRY_NAME ")"
                  "VALUES(:code,:name)");

    for (int i = 0; i < element.childNodes().count(); i++) {
        node = element.childNodes().item(i);

        code = node.attributes().namedItem(XML_COUNTRY_CODE).nodeValue();
        name = node.attributes().namedItem(XML_COUNTRY_NAME).nodeValue();

        query.bindValue(":code", code);
        query.bindValue(":name", name);

        if (!query.exec()) {
            // set last error text
            setLastErrorText(query.lastError());

            return false;
        }
    }

    return true;
}


/**
  * Import transaction types from xml file
  */
bool BursarDb::importXmlTransactionTypes(QDomElement &docElement)
{
    QSqlQuery query;
    QDomNode node;
    QString code;
    QString name;

    // get element;
    QDomElement element = docElement.firstChildElement(XML_TRANSACTION_TYPES);

    // prepare sql statament
    query.prepare("INSERT INTO " TBL_TRANSACTION_TYPES
                  "("FLD_TRANSACTION_TYPE_CODE "," FLD_TRANSACTION_TYPE_NAME ")"
                  "VALUES(:code,:name)");

    for (int i = 0; i < element.childNodes().count(); i++) {
        node = element.childNodes().item(i);

        code = node.attributes().namedItem(XML_TRANSACTION_TYPE_CODE).nodeValue();
        name = node.attributes().namedItem(XML_TRANSACTION_TYPE_NAME).nodeValue();

        query.bindValue(":code", code);
        query.bindValue(":name", name);

        if (!query.exec()) {
            // set last error text
            setLastErrorText(query.lastError());

            return false;
        }
    }

    return true;
}


/**
  * Write debug information
  */
void BursarDb::debug(const QString &text)
{
    qDebug() << "BursarDb::" + text;
}


/**
  * Write debug information
  */
void BursarDb::debug(const QString &text, bool result)
{
    debug(text + ": " + Utils::boolToStr(result));
}


/**
  * Convert a double to a currency string
  */
QString BursarDb::dblToCur(double value, const QString &currency)
{
    return currency + " " + m_locale->toString(value, 'f', decimalDigits());
}


/**
  * Reset the cache memory
  */
void BursarDb::resetCache()
{
    m_decimalDigits = -1;
}


/**
  * Create SQL line for create table statement
  */
QString BursarDb::sqlField(const QString &name, const QString &type,
                           int size, bool notNull) const
{
    QString sql;

    sql = name + " " + type;

    // add size information
    if (size > 0) sql = sql + "(" + Utils::intToStr(size) + ")";

    // add not null statement
    if (notNull) sql = sql + " NOT NULL";

    return sql;
}


/**
  * Returns create statement for table SETTINGS
  */
QString BursarDb::sqlCreateTableSettings() const
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
QString BursarDb::sqlCreateTableCurrencies() const
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
QString BursarDb::sqlCreateTableCountries() const
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
QString BursarDb::sqlCreateTableAccountTypes() const
{
    return "CREATE TABLE " + QString(TBL_ACCOUNT_TYPES) + "(" +
           sqlField(FLD_ACCOUNT_TYPE_CODE, "TEXT", MAX_ACCOUNT_TYPE_CODE, true) + "," +
           sqlField(FLD_ACCOUNT_TYPE_NAME, "TEXT", MAX_ACCOUNT_TYPE_NAME, true) + ","
           "PRIMARY KEY(" + QString(FLD_ACCOUNT_TYPE_CODE) + ")"
           ")";
}


/**
  * Returns create statement for table ACCOUNTS
  */
QString BursarDb::sqlCreateTableAccounts() const
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
  * Returns create statement for table TRANSACTION_TYPES
  */
QString BursarDb::sqlCreateTableTransactionTypes() const
{
    return "CREATE TABLE " + QString(TBL_TRANSACTION_TYPES) + "(" +
           sqlField(FLD_TRANSACTION_TYPE_CODE, "TEXT", MAX_TRANSACTION_TYPE_CODE, true) + "," +
           sqlField(FLD_TRANSACTION_TYPE_NAME, "TEXT", MAX_TRANSACTION_TYPE_NAME, true) + "," +
           "PRIMARY KEY(" + QString(FLD_TRANSACTION_TYPE_CODE) + ")"
           ")";
}


/**
  * Returns create statement for table CATEGRORIES
  */
QString BursarDb::sqlCreateTableCategories() const
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
QString BursarDb::sqlCreateTableTransactions() const
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
