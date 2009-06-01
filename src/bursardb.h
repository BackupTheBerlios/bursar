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

#ifndef BURSARDB_H
#define BURSARDB_H

#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QComboBox>
#include <QSqlError>
#include <QDomElement>
#include <QStandardItem>

class BursarDb : public QObject
{
    Q_OBJECT

public:
    BursarDb();
    ~BursarDb();

    bool createDatabase(const QString &dbtitle, const QString &fileName,
                        const QString &curCode, const QString &curName);
    bool openDatabase(const QString &fileName);

    QSqlDatabase dbConnection() const;
    QString databaseTitle();
    QString *lastErrorText() const;

    bool isOpened() const;

    bool setDatabaseTitle(const QString &title);

    bool addAccount(const QString &accountName, const QString &accountType,
                    const QString &currencyCode, const QString &countryCode);

    QList<QStandardItem *> currentAccountNames() const;
    QList<QStandardItem *> currentAccountBalances() const;

    bool loadAccountTypes(QComboBox *comboBox);
    bool loadCurrencies(QComboBox *comboBox);
    bool loadCountries(QComboBox *comboBox);

    bool importFromXml(const QString &fileName);
private:
    bool createTables();
    bool addSettingsToTable();

    bool executeQuery(const QString &query);

    bool setDbVersion();

    bool addBaseCurrency(const QString &code, const QString &name);
    bool setBaseCurrency(const QString &code);

    void resetLastErrorText();
    void setLastErrorText(const QSqlError &error);
    void setLastErrorText(const QString &text);

    bool importXmlAccountTypes(QDomElement &docElement);
    bool importXmlCountries(QDomElement &docElement);

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
    QString *m_lastErrorText;
};

#endif // BURSARDB_H
