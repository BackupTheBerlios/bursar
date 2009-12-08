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

#ifndef BURDOC_H
#define BURDOC_H

#include "burdb.h"

#include "accounttreemodel.h"
#include "journaltablemodel.h"

#include "burcombobox.h"

#include <QDomElement>
#include <QLocale>
#include <QStandardItem>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>


class BurDoc : public BurDb
{
    Q_OBJECT

public:
    BurDoc(BurDebugLevel debugLevel);
    ~BurDoc();

    bool createDatabase(const QString &dbtitle, const QString &dbDescr,
                        const QString &fileName, const int decDigits,
                        const QString &curCode, const QString &curName,
                        const QString &curSymbol);

    QSqlDatabase dbConnection() const;
    QString databaseTitle();
    QString databaseDescr();

    AccountTreeModel *accountTreeModel();
    JournalTableModel *journalTableModel();

    int decimalDigits();

    bool setDatabaseTitle(const QString &title);

    bool addAccount(const QString &accountName, const QString &accountType,
                    const QString &countryCode, const QString &currencyCode);

    QList<QStandardItem *> accountNames(const QString &accountType);
    QList<QStandardItem *> accountBanks(const QString &accountType);
    QList<QStandardItem *> accountCountries(const QString &accountType);
    QList<QStandardItem *> accountBalances(const QString &accountType);

    bool loadAccounts(BurComboBox *comboBox);
    bool loadAccountTypes(BurComboBox *comboBox);
    bool loadCurrencies(BurComboBox *comboBox);
    bool loadCountries(BurComboBox *comboBox);

    bool importFromXml(const QString &fileName);
private:
    bool createTables();

    bool initSettings(const QString &title, const QString &descr, int decDigits, const QString &curCode);

    bool setDbVersion();

    bool addBaseCurrency(const QString &code, const QString &name, const QString &symbol);

    bool importXmlAccountTypes(QDomElement &docElement);
    bool importXmlCountries(QDomElement &docElement);
    bool importXmlTransactionTypes(QDomElement &docElement);

    QString dblToCur(double value, const QString &currency);

    void resetCache();

    QString sqlField(const QString &name, const QString &type,
                     int size = 0, bool notNull = false) const;

    QString sqlCreateTableSettings() const;
    QString sqlCreateTableCurrencies() const;
    QString sqlCreateTableCountries() const;
    QString sqlCreateTableAccountTypes() const;
    QString sqlCreateTableAccounts() const;
    QString sqlCreateTableTransactionTypes() const;
    QString sqlCreateTableCategories() const;
    QString sqlCreateTableTransactions() const;

    // database connection
    QSqlDatabase m_dbConnection;

    // account tree model
    AccountTreeModel *m_accountTreeModel;

    // journal table model
    JournalTableModel *m_journalTableModel;

    // system locale
    QLocale *m_locale;

    // decimal digits
    int m_decimalDigits;
};

#endif // BURSARDB_H
