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

#include "burdoc.h"

#include "constants.h"
#include "config.h"
#include "burutils.h"
#include "burdbcreator.h"

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
BurDoc::BurDoc(BurDebugLevel debugLevel)
    : BurDb(debugLevel)
{
    // set object name
    setObjectName("BurDoc");

    // initialise system locale
    m_locale = new QLocale(QLocale::system());

    // reset cache
    resetCache();
}


/**
  * Destructor
  */
BurDoc::~BurDoc()
{
    QStringList connections = QSqlDatabase::connectionNames();

    for (int i = 0; i < connections.count(); i++) {
        qDebug() << connections.at(i);
        QSqlDatabase::removeDatabase(connections.at(i));
    }

    delete m_locale;
}


/**
  * Create a new document
  */
bool BurDoc::createDocument(const QString &fileName, BurDbCreationParams *params)
{
    BurDbCreator creator(debugLevel());

    // set parameters
    creator.setParameters(params);

    if (creator.createDatabase(dbConnection(), fileName)) {
        // reset cache
        resetCache();

        return true;
    } else {
        return false;
    };
}


/**
  * Returns the document title
  */
QString BurDoc::title()
{
    QSqlQuery query(dbConnection());

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
  * Returns the document description
  */
QString BurDoc::description()
{
    QSqlQuery query(dbConnection());

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
AccountTreeModel *BurDoc::accountTreeModel()
{
    return m_accountTreeModel;
}


/**
  * Returns the journal table model
  */
JournalTableModel *BurDoc::journalTableModel()
{
    return m_journalTableModel;
}


/**
  * Returns the decimal digits
  */
int BurDoc::decimalDigits()
{
    if (m_decimalDigits == -1) {
        QSqlQuery query(dbConnection());

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
bool BurDoc::setDatabaseTitle(const QString &title)
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

   debug(FULL, "setDatabaseTitle: Set database title", result);

   return result;
}


/**
  * Add a new account
  */
bool BurDoc::addAccount(const QString &accountName, const QString &accountType,
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

    debug(FULL, "addAccount " + query.lastQuery());

    // run statement
    if (query.exec()) {
        result = true;
    } else {
        // set last error text
        setLastErrorText(query.lastError());
    }

    debug(FULL, "addAccount: Add new account", result);

    return result;
}





/**
  * Get list of all account names of the selected type
  */
QList<QStandardItem *> BurDoc::accountNames(const QString &accountType)
{
    QList<QStandardItem *> list;
    QSqlQuery query(dbConnection());
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
QList<QStandardItem *> BurDoc::accountBanks(const QString &accountType)
{
    QList<QStandardItem *> list;
    QSqlQuery query(dbConnection());
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
QList<QStandardItem *> BurDoc::accountCountries(const QString &accountType)
{
    QList<QStandardItem *> list;
    QSqlQuery query(dbConnection());
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
QList<QStandardItem *> BurDoc::accountBalances(const QString &accountType)
{
    QList<QStandardItem *> list;
    QSqlQuery query(dbConnection());
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
bool BurDoc::loadAccounts(BurComboBox *comboBox)
{
    QSqlQuery query(dbConnection());

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
bool BurDoc::loadAccountTypes(BurComboBox *comboBox)
{
    QSqlQuery query(dbConnection());

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
bool BurDoc::loadCurrencies(BurComboBox *comboBox)
{
    QSqlQuery query(dbConnection());

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
bool BurDoc::loadCountries(BurComboBox *comboBox)
{
    QSqlQuery query(dbConnection());

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
bool BurDoc::importFromXml(const QString &fileName)
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
  * Set database version
  */
bool BurDoc::setDbVersion()
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
  * Import account types from xml file
  */
bool BurDoc::importXmlAccountTypes(QDomElement &docElement)
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
bool BurDoc::importXmlCountries(QDomElement &docElement)
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
bool BurDoc::importXmlTransactionTypes(QDomElement &docElement)
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
  * Convert a double to a currency string
  */
QString BurDoc::dblToCur(double value, const QString &currency)
{
    return currency + " " + m_locale->toString(value, 'f', decimalDigits());
}


/**
  * Reset the cache memory
  */
void BurDoc::resetCache()
{
    m_decimalDigits = -1;
}









