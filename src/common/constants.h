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

#ifndef CONSTANTS_H_
#define CONSTANTS_H_


/*************************************************************************
 *  Application
 *************************************************************************/

// Application Name
#define APP_NAME "Bursar"

// Database Version
#define DB_VERSION "0.01"

// XML Format Version
#define XML_VERSION "0.01"

// Default extension for bursar files
#define DB_DEFAULT_EXT "dat"




/*************************************************************************
 *  General Settings
 *************************************************************************/

// max. decimal digits
#define MAX_DEC_DIGITS 6

// default decimal digits
#define DEFAULT_DEC_DIGITS 2


/*************************************************************************
 *  Directories
 *************************************************************************/

// Shared directory on unix
#define DIR_X11_SHARED "bursar"

// Shared directory on mac
#define DIR_MAC_SHARED "Content"

// Shared direcotry on windows
#define DIR_WIN_SHARED "data"

// Directory for database templates
#define DIR_DBTEMPLATES "dbtemplates"




/*************************************************************************
 *  Account Types
 *************************************************************************/

// Current Account
#define ACT_CURRENT_ACCOUNT "CUR"

// Savings Account
#define ACT_SAVINGS_ACCOUNT "SAV"

// Load Account
#define ACT_LOAN_ACCOUNT "LOA"

// Credit Card
#define ACT_CREDIT_CARD "CCD"




/*************************************************************************
 *  Database Schema
 *************************************************************************/

// Database Table Names
#define TBL_ACCOUNTS "ACCOUNTS"
#define TBL_ACCOUNT_TYPES "ACCOUNT_TYPES"
#define TBL_CATEGORIES "CATEGORIES"
#define TBL_COUNTRIES "COUNTRIES"
#define TBL_CURRENCIES "CURRENCIES"
#define TBL_PROJECTS "PROJECTS"
#define TBL_SETTINGS "SETTINGS"
#define TBL_TRANSACTIONS "TRANSACTIONS"
#define TBL_TRANSACTION_TYPES "TRANSACTION_TYPES"

// Database Field Names
#define FLD_ACCOUNT_BALANCE "ACT_BALANCE"
#define FLD_ACCOUNT_CODE "ACT_CODE"
#define FLD_ACCOUNT_ID "ACT_ID"
#define FLD_ACCOUNT_NAME "ACT_NAME"
#define FLD_ACCOUNT_NOTES "ACT_NOTES"
#define FLD_ACCOUNT_TYPE_CODE "ACT_TYPE_CODE"
#define FLD_ACCOUNT_TYPE_NAME "ACT_TYPE_NAME"
#define FLD_BANK_CODE "BANK_CODE"
#define FLD_BANK_NAME "BANK_NAME"
#define FLD_DB_TITLE "DB_TITLE"
#define FLD_DB_DESCR "DB_DESCR"
#define FLD_DB_VERSION "DB_VERSION"
#define FLD_DECIMAL_DIGITS "DECIMAL_DIGITS"
#define FLD_COUNTRY_CODE "CTY_CODE"
#define FLD_COUNTRY_NAME "CTY_NAME"
#define FLD_CURRENCY_CODE "CUR_CODE"
#define FLD_CURRENCY_NAME "CUR_NAME"
#define FLD_CURRENCY_SYMBOL "CUR_SYMBOL"
#define FLD_JOURNAL_ID "TRN_ID"
#define FLD_TRANSACTION_TYPE_CODE "TRN_TYPE_CODE"
#define FLD_TRANSACTION_TYPE_NAME "TRN_TYPE_NAME"

// Database Field Sizes
#define MAX_ACCOUNT_CODE 20
#define MAX_ACCOUNT_NAME 30
#define MAX_ACCOUNT_NOTES 1024
#define MAX_ACCOUNT_TYPE_CODE 3
#define MAX_ACCOUNT_TYPE_NAME 20
#define MAX_BANK_CODE 20
#define MAX_BANK_NAME 30
#define MAX_DB_TITLE 60
#define MAX_DB_DESCR 120
#define MAX_DB_VERSION 5
#define MAX_COUNTRY_CODE 3
#define MAX_COUNTRY_NAME 20
#define MAX_CURRENCY_CODE 3
#define MAX_CURRENCY_NAME 20
#define MAX_CURRENCY_SYMBOL 1
#define MAX_TRANSACTION_TYPE_CODE 3
#define MAX_TRANSACTION_TYPE_NAME 20




/*************************************************************************
 *  XML Schema
 *************************************************************************/

// Xml Elements
#define XML_ACCOUNT_TYPES "ACCOUNT_TYPES"
#define XML_COUNTRIES "COUNTRIES"
#define XML_TRANSACTION_TYPES "TRANSACTION_TYPES"

// Xml Attributes
#define XML_ACCOUNT_TYPE_CODE "ACT_TYPE_CODE"
#define XML_ACCOUNT_TYPE_NAME "ACT_TYPE_NAME"
#define XML_COUNTRY_CODE "CTY_CODE"
#define XML_COUNTRY_NAME "CTY_NAME"
#define XML_TRANSACTION_TYPE_CODE "TRN_TYPE_CODE"
#define XML_TRANSACTION_TYPE_NAME "TRN_TYPE_NAME"

#endif // CONSTANTS_H
