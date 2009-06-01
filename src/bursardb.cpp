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
#include "dbconstants.h"

#include "constants.h"

#include <QDebug>
#include <QSqlQuery>
#include <QVariant>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QSqlDriverCreator>


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
}


/**
  * Destructor
  */
BursarDb::~BursarDb()
{
    delete m_lastErrorText;
}


/**
  * Create new database
  */
bool BursarDb::createDatabase(const QString &dbTitle, const QString &fileName,
                              const QString &curCode, const QString &curName)
{
    // delete file if it already exists
    if (QFile::exists(fileName)) {
        QFile::remove(fileName);
    }

    // set database name
    m_dbConnection.setDatabaseName(fileName);

    // open database which will automatically create it
    bool created = m_dbConnection.open();

    qDebug() << "BursarDb::createDatabase: Database '" << fileName << "' opened: " << created;

    if (created) {
        // create tables
        created = createTables();

        qDebug() << "BursarDb::createDatabase: Create tables: " << created;
    }

    if (created) {
        // set database title
        created = setDatabaseTitle(dbTitle);

        qDebug() << "BursarDb::createDatabase: Set database title: " << created;
    }

    if (created) {
        // add base currency
        created = addBaseCurrency(curCode, curName);

        qDebug() << "BursarDb::createDatabase: Add base currency: " << created;
    }

    if (created) {
        // set base currency
        created = setBaseCurrency(curCode);

        qDebug() << "BursarDb::createDatabase: Set base currency: " << created;
    }

    if (created) {
        // import initial data from xml
        created = importFromXml("english.xml");
    }

    return created;
}


/**
  * Open existing Database
  */
bool BursarDb::openDatabase(const QString &fileName)
{
    // set database name
    m_dbConnection.setDatabaseName(fileName);
    
    // open database
    bool opened = m_dbConnection.open();

    qDebug() << "BursarDb::openDatabase: Database '" << fileName << "' opened: " << opened;

    return opened;
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
  * Returns if a database is opened
  */
bool BursarDb::isOpened() const
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
    query.prepare("SELECT DB_TITLE FROM SETTINGS");

    // run statement
    if (query.exec()) {
        // go to first record
        query.first();

        // return value
         return query.value(0).toString();
    } else {
        // set last error text
        setLastErrorText(query.lastError());

        qDebug() << "BursarDb::databaseTitle: " << query.lastError().text();

        // return empty string as fallback
        return "";
    }
}


/**
  * Set database title
  */
bool BursarDb::setDatabaseTitle(const QString &title)
{
    QSqlQuery query;

    // build sql statement
    query.prepare("UPDATE SETTINGS SET DB_TITLE = :title");
    query.bindValue(":title", title);

    qDebug() << "BursarDb::setDatabaseTitle: " << query.lastQuery();

    // run statement
    if (query.exec()) {
        return true;
    } else {
        // set last error text
        setLastErrorText(query.lastError());

        qDebug() << "BursarDb::setDatabaseTitle: " << query.lastError().text();

        return false;
    }
}


/**
  * Add base currency
  */
bool BursarDb::addBaseCurrency(const QString &curCode, const QString &curName)
{
    QSqlQuery query;

    // build sql statement
    query.prepare("INSERT INTO CURRENCIES (CUR_CODE, CUR_NAME) VALUES (:code, :name)");
    query.bindValue(":code", curCode);
    query.bindValue(":name", curName);

    qDebug() << "BursarDb::addBaseCurrency: " << query.lastQuery();

    // run statement
    if (query.exec()) {
        return true;
    } else {
        // set last error text
        setLastErrorText(query.lastError());

        qDebug() << "BursarDb::addBaseCurrency: " << query.lastError().text();

        return false;
    }
}


/**
  * Set base currency
  */
bool BursarDb::setBaseCurrency(const QString &curCode)
{
    QSqlQuery query;

    // build sql statement
    query.prepare("UPDATE SETTINGS SET CUR_CODE = :code");
    query.bindValue(":code", curCode);

    qDebug() << "BursarDb::setBaseCurrency: " << query.lastQuery();

    // run statement
    if (query.exec()) {
        return true;
    } else {
        // set last error text
        setLastErrorText(query.lastError());

        qDebug() << "BursarDb::setBaseCurrency: " << query.lastError().text();

        return false;
    }
}


/**
  * Get list of all current account names
  */
QList<QStandardItem *> BursarDb::currentAccountNames() const
{
    QList<QStandardItem *> list;
    QSqlQuery query(m_dbConnection);
    QString sql;
    
    // build sql statement and add arguments
    sql = QString("SELECT ACT_NAME FROM ACCOUNTS WHERE ACT_TYPE_CODE = '%1'");
    sql = sql.arg(ACT_CURRENT_ACCOUNT);
    
    qDebug() << "BursarDb::currentAccountNames: " << sql;

    // run query
    query.exec(sql);

    // check result
    if (query.lastError().type() == QSqlError::NoError && query.isActive()) {
        // get result
        while(query.next()) {
            list.append(new QStandardItem(query.value(0).toString()));
        }
    } else {
        qDebug() << "BursarDb::currentAccountNames: " << query.lastError().text();
    }

    return list;
}


/**
  * Get list of all current account balances
  */
QList<QStandardItem *> BursarDb::currentAccountBalances() const
{
    QSqlQuery query(m_dbConnection);
    QList<QStandardItem *> list;
    QStandardItem *item;
    QString sql;

    // create a red brush
    QBrush brush = QBrush(Qt::SolidPattern);
    brush.setColor(Qt::red);

    // build sql statement and add arguments
    sql = QString("SELECT ACT_BALANCE FROM ACCOUNTS WHERE ACT_TYPE_CODE = '%1'");
    sql = sql.arg(ACT_CURRENT_ACCOUNT);
    
    qDebug() << "BursarDb::currentAccountBalances: " << sql;

    // run query
    query.exec(sql);

    // check result
    if (query.lastError().type() == QSqlError::NoError && query.isActive()) {
        // get result
        while(query.next()) {
            item = new QStandardItem(query.value(0).toString());

            // set colour to red if smaller than 0
            if (query.value(0).toDouble() < 0)
                item->setForeground(brush);

            list.append(item);
        }
    } else {
        qDebug() << "BursarDb::currentAccountBalances: " << query.lastError().text();
    }

    return list;
}


/**
  * Load account types for combobox
  */
bool BursarDb::loadAccountTypes(QComboBox *comboBox)
{
    QSqlQuery query(m_dbConnection);

    // delete existing entries and add blank entry
    comboBox->clear();
    comboBox->addItem(tr("<Select Account Type>"));

    // build sql statement
    query.prepare("SELECT ACT_TYPE_NAME FROM ACCOUNT_TYPES");

    qDebug() << "BursarDb::loadAccountTypes: " << query.lastQuery();

    // run statement
    if (query.exec()) {
        // get result
        while(query.next()) {
            // add to combobox
            comboBox->addItem(query.value(0).toString());
        }

        return true;
    } else {
        // set last error text
        setLastErrorText(query.lastError());

        qDebug() << "BursarDb::loadAccountTypes: " << query.lastError().text();

        return false;
    }
}


/**
  * Load currencies for combobox
  */
bool BursarDb::loadCurrencies(QComboBox *comboBox)
{
    QSqlQuery query(m_dbConnection);

        // delete existing entries and add blank entry
    comboBox->clear();
    comboBox->addItem(tr("<Select Currency>"));

    // build sql statement
    query.prepare("SELECT CUR_NAME FROM CURRENCIES ORDER BY CUR_NAME");

    qDebug() << "BursarDb::loadCurrencies: " << query.lastQuery();

    // run statement
    if (query.exec()) {
        // get result
        while(query.next()) {
            // add to combobox
            comboBox->addItem(query.value(0).toString());
        }

        return true;
    } else {
        // set last error text
        setLastErrorText(query.lastError());

        qDebug() << "BursarDb::loadCurrencies: " << query.lastError().text();

        return false;
    }
}


/**
  * Load countries for combobox
  */
bool BursarDb::loadCountries(QComboBox *comboBox)
{
    QSqlQuery query(m_dbConnection);

    // delete existing entries and add blank entry
    comboBox->clear();
    comboBox->addItem(tr("<Select Country>"));

    // build sql statement
    query.prepare("SELECT CTY_NAME FROM COUNTRIES ORDER BY CTY_NAME");

    qDebug() << "BursarDb::loadCountries: " << query.lastQuery();

    // run statement
    if (query.exec()) {
        // get result
        while(query.next()) {
            // add to combobox
            comboBox->addItem(query.value(0).toString());
        }

        return true;
    } else {
        // set last error text
        setLastErrorText(query.lastError());

        qDebug() << "BursarDb::loadCountries: " << query.lastError().text();

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

    // add settings to new table
    if (created) created = addSettingsToTable();

    return created;
}


/**
  * Add settings to table
  */
bool BursarDb::addSettingsToTable()
{
    QSqlQuery query;

    // build sql statement
    query.prepare("INSERT INTO SETTINGS (DB_VERSION) VALUES(:version)");
    query.bindValue(":version", DB_VERSION);

    qDebug() << "BursarDb::addSettingsToTable: " << query.lastQuery();

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
        qDebug() << sql.lastError().text();

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
    query.prepare("UPDATE SETTINGS SET DB_VERSION = :version");
    query.bindValue(":version", DB_VERSION);

    qDebug() << "BursarDb::setDbVersion: " << query.lastQuery();

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
    query.prepare("INSERT INTO ACCOUNT_TYPES (ACT_TYPE_CODE, ACT_TYPE_NAME) "
                  "VALUES (:code, :name)");

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
    query.prepare("INSERT INTO COUNTRIES (CTY_CODE, CTY_NAME) "
                  "VALUES (:code, :name)");

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
  * Returns create statement for table SETTINGS
  */
QString BursarDb::sqlCreateTableSettings() const
{
    return QString("CREATE TABLE SETTINGS ("
                   "   DB_TITLE VARCHAR(60), "
                   "   DB_VERSION VARCHAR(5), "
                   "   CUR_CODE VARCHAR(3)"
                   ")");
}


/**
  * Returns create statement for table CURRENCIES
  */
QString BursarDb::sqlCreateTableCurrencies() const
{
    return QString("CREATE TABLE CURRENCIES ("
                   "   CUR_CODE VARCHAR(3) NOT NULL,"
                   "   CUR_NAME VARCHAR(20),"
                   "   PRIMARY KEY(CUR_CODE)"
                   ")");
}


/**
  * Returns create statement for table COUNTRIES
  */
QString BursarDb::sqlCreateTableCountries() const
{
    return "CREATE TABLE COUNTRIES ("
           "   CTY_CODE VARCHAR(3) NOT NULL,"
           "   CTY_NAME VARCHAR(30),"
           "   PRIMARY KEY(CTY_CODE)"
           ")";
}


/**
  * Returns create statement for table ACCOUNT_TYPES
  */
QString BursarDb::sqlCreateTableAccountTypes() const
{
    return "CREATE TABLE ACCOUNT_TYPES ("
           "   ACT_TYPE_CODE VARCHAR(1) NOT NULL,"
           "   ACT_TYPE_NAME VARCHAR(20) NOT NULL,"
           "   PRIMARY KEY(ACT_TYPE_CODE)"
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
           "   ACT_TYPE_CODE VARCHAR(1) NOT NULL,"
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
    return "CREATE TABLE TRANSACTION_TYPES ("
           "   TRN_TYPE_CODE VARCHAR(1) NOT NULL,"
           "   TRN_TYPE_NAME VARCHAR(20) NOT NULL,"
           "   PRIMARY KEY(TRN_TYPE_CODE)"
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
           "   TRN_TYPE_CODE VARCHAR(1) NOT NULL,"
           "   TRN_MEMO VARCHAR(300),"
           "   TRN_AMOUNT DECIMAL(8, 2),"
           "   TRN_RECONCILED VARCHAR(1) DEFAULT 'N',"
           "   TRN_CHEQUE_NO VARCHAR(15),"
           "   CONSTRAINT ACCOUNTS_FK FOREIGN KEY (ACT_ID) REFERENCES ACCOUNTS (ACT_ID) ON DELETE CASCADE,"
           "   CONSTRAINT TRANSACTION_TYPES_FK FOREIGN KEY (TRN_TYPE_CODE) REFERENCES TRANSACTION_TYPES (TRN_TYPE_CODE) ON DELETE RESTRICT,"
           "   CONSTRAINT CATEGORIES_FK FOREIGN KEY (CAT_ID) REFERENCES CATEGORIES (CAT_ID) ON DELETE RESTRICT"
           ")";
}

