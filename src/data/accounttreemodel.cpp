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

#include "accounttreemodel.h"

#include "burdoc.h"
#include "constants.h"
#include "burutils.h"

#include <QDebug>
#include <QMessageBox>


/*************************************************************************
 *  PUBLIC FUNCTIONS
 *************************************************************************/

/**
  * Constructor
  */
AccountTreeModel::AccountTreeModel(BurDoc *doc)
    : QStandardItemModel()
{
    // set document pointer
    m_doc = doc;
}


/**
  * Destructor
  */
AccountTreeModel::~AccountTreeModel()
{
    delete m_doc;
}


/**
  * Load data
  */
void AccountTreeModel::load()
{
    // clear model
    this->clear();

    // set column count
    this->setColumnCount(4);

    // set header titles
    this->setHeaderData(0, Qt::Horizontal, tr("Account"));
    this->setHeaderData(1, Qt::Horizontal, tr("Bank"));
    this->setHeaderData(2, Qt::Horizontal, tr("Country"));
    this->setHeaderData(3, Qt::Horizontal, tr("Balance"));

    // get root item
    QStandardItem *rootItem = this->invisibleRootItem();

    // add main items
    QStandardItem *curItem = new QStandardItem(tr("Current Accounts"));
    curItem->setIcon(QIcon(":/icons/current-account.svg"));
    curItem->setData(-1, Qt::UserRole);
    rootItem->appendRow(curItem);

    QStandardItem *savItem = new QStandardItem(tr("Saving Accounts"));
    savItem->setIcon(QIcon(":/icons/savings-account.svg"));
    savItem->setData(-1, Qt::UserRole);
    rootItem->appendRow(savItem);

    QStandardItem *loanItem = new QStandardItem(tr("Loan Accounts"));
    loanItem->setIcon(QIcon(":/icons/loan-account.svg"));
    loanItem->setData(-1, Qt::UserRole);
    rootItem->appendRow(loanItem);

    QStandardItem *cardItem = new QStandardItem(tr("Credit Cards"));
    cardItem->setIcon(QIcon(":/icons/credit-card.svg"));
    cardItem->setData(-1, Qt::UserRole);
    rootItem->appendRow(cardItem);

    // load accounts
    curItem->appendRows(m_doc->accountNames(ACT_CURRENT_ACCOUNT));
    curItem->appendColumn(m_doc->accountBanks(ACT_CURRENT_ACCOUNT));
    curItem->appendColumn(m_doc->accountCountries(ACT_CURRENT_ACCOUNT));
    curItem->appendColumn(m_doc->accountBalances(ACT_CURRENT_ACCOUNT));

    savItem->appendRows(m_doc->accountNames(ACT_SAVINGS_ACCOUNT));
    savItem->appendColumn(m_doc->accountBanks(ACT_SAVINGS_ACCOUNT));
    savItem->appendColumn(m_doc->accountCountries(ACT_SAVINGS_ACCOUNT));
    savItem->appendColumn(m_doc->accountBalances(ACT_SAVINGS_ACCOUNT));

    loanItem->appendRows(m_doc->accountNames(ACT_LOAN_ACCOUNT));
    loanItem->appendColumn(m_doc->accountBanks(ACT_LOAN_ACCOUNT));
    loanItem->appendColumn(m_doc->accountCountries(ACT_LOAN_ACCOUNT));
    loanItem->appendColumn(m_doc->accountBalances(ACT_LOAN_ACCOUNT));

    cardItem->appendRows(m_doc->accountNames(ACT_CREDIT_CARD));
    cardItem->appendColumn(m_doc->accountBanks(ACT_CREDIT_CARD));
    cardItem->appendColumn(m_doc->accountCountries(ACT_CREDIT_CARD));
    cardItem->appendColumn(m_doc->accountBalances(ACT_CREDIT_CARD));
}
