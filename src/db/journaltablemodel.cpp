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

#include "journaltablemodel.h"

#include "bursardb.h"
#include "constants.h"
#include "utils.h"

#include <QDebug>


/*************************************************************************
 *  PUBLIC FUNCTIONS
 *************************************************************************/

/**
  * Constructor
  */
JournalTableModel::JournalTableModel(BursarDb *db)
    : QSqlRelationalTableModel()
{
    // set database pointer
    m_db = db;

    // initialise
    init(); 
}


/**
  * Destructor
  */
JournalTableModel::~JournalTableModel()
{
    delete m_db;
}


/**
  * Load data
  */
void JournalTableModel::load()
{
    // load data from database
    this->select();
}




/*************************************************************************
 *  PRIVATE FUNCTIONS
 *************************************************************************/

/**
  * Initialise 
  */
void JournalTableModel::init()
{
    // setup model
    this->setTable(TBL_TRANSACTIONS);
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // set the relations to the other database tables
    this->setRelation(indexAccountId(), QSqlRelation(TBL_ACCOUNTS,
                                                     FLD_ACCOUNT_ID,
                                                     FLD_ACCOUNT_NAME));

    this->setRelation(indexTransactionTypeCode(), QSqlRelation(TBL_TRANSACTION_TYPES,
                                                               FLD_TRANSACTION_TYPE_CODE,
                                                               FLD_TRANSACTION_TYPE_NAME));

    // set header titles
    //this->setHeaderData( 0, Qt::Horizontal, tr("Account") );
    //this->setHeaderData( 1, Qt::Horizontal, tr("Bank") );
    //this->setHeaderData( 2, Qt::Horizontal, tr("Country") );
    //this->setHeaderData( 3, Qt::Horizontal, tr("Balance") );
}


/**
  * Returns the index of field "account id"
  */
int JournalTableModel::indexAccountId()
{
    return this->fieldIndex(FLD_ACCOUNT_ID);
}


/**
  * Returns the index of field "transaction type code"
  */
int JournalTableModel::indexTransactionTypeCode()
{
    return this->fieldIndex(FLD_TRANSACTION_TYPE_CODE);
}
