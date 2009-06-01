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

#ifndef DBCONSTANTS_H_
#define DBCONSTANTS_H_

// Database Version
#define DB_VERSION "0.01"

// XML Format Version
#define XML_VERSION "0.01"

// Database Tables
#define TBL_ACCOUNTS "ACCOUNTS"
#define TBL_ACCOUNT_TYPES "ACCOUNT_TYPES"
#define TBL_CATEGORIES "CATEGORIES"
#define TBL_COUNTRIES "COUNTRIES"
#define TBL_CURRENCIES "CURRENCIES"
#define TBL_SETTINGS "SETTINGS"
#define TBL_TRANSACTIONS "TRANSACTIONS"
#define TBL_TRANSACTION_TYPES "TRANSACTION_TYPES"

// Database Fields
#define FLD_ACCOUNT_NAME "ACT_NAME"
#define FLD_ACCOUNT_TYPE_CODE "ACT_TYPE_CODE"
#define FLD_ACCOUNT_TYPE_NAME "ACT_TYPE_NAME"
#define FLD_ACCOUNT_CODE "ACT_CODE"
#define FLD_BANK_CODE "BANK_CODE"
#define FLD_BANK_NAME "BANK_NAME"
#define FLD_ACCOUNT_NOTES "ACT_NOTES"
#define FLD_COUNTRY_CODE "CTY_CODE"
#define FLD_COUNTRY_NAME "CTY_NAME"
#define FLD_CURRENCY_CODE "CUR_CODE"
#define FLD_CURRENCY_NAME "CUR_NAME"

// Max Lengths for Database Fields
#define MAX_DB_TITLE 60
#define MAX_CURRENCY_CODE 3
#define MAX_CURRENCY_NAME 20
#define MAX_ACCOUNT_NAME 30
#define MAX_ACCOUNT_CODE 20
#define MAX_BANK_CODE 20
#define MAX_BANK_NAME 30
#define MAX_ACCOUNT_NOTES 1024

// Xml Elements
#define XML_ACCOUNT_TYPES "ACCOUNT_TYPES"
#define XML_COUNTRIES "COUNTRIES"

// Xml Attributes
#define XML_ACCOUNT_TYPE_CODE "ACT_TYPE_CODE"
#define XML_ACCOUNT_TYPE_NAME "ACT_TYPE_NAME"
#define XML_COUNTRY_CODE "CTY_CODE"
#define XML_COUNTRY_NAME "CTY_NAME"

#endif // DBCONSTANTS_H
