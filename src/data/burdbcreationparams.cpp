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

#include "burdbcreationparams.h"


/*************************************************************************
 *  PUBLIC FUNCTIONS
 *************************************************************************/

/**
  * Constructor
  */
BurDbCreationParams::BurDbCreationParams()
    : BurObject()
{
    // set object name
    setObjectName("BurDbCreationParams");
}


/**
  * Returns database title
  */
QString BurDbCreationParams::databaseTitle() const
{
    return m_databaseTitle;
}


/**
  * Returns database description
  */
QString BurDbCreationParams::databaseDescr() const
{
    return m_databaseDescr;
}


/**
  * Returns number of decimal digits
  */
int BurDbCreationParams::decimalDigits() const
{
    return m_decimalDigits;
}


/**
  * Returns currency code
  */
QString& BurDbCreationParams::currencyCode() const
{
    return const_cast<QString &>(m_currencyCode);
}



/**
  * Returns currency name
  */
QString BurDbCreationParams::currencyName() const
{
    return m_currencyName;
}



/**
  * Returns currency symbol
  */
QString BurDbCreationParams::currencySymbol() const
{
    return m_currencySymbol;
}


/**
  * Set database title
  */
void BurDbCreationParams::setDatabaseTitle(const QString &databaseTitle)
{
    m_databaseTitle = databaseTitle;
}


/**
  * Set database description
  */
void BurDbCreationParams::setDatabaseDescr(const QString &databaseDescr)
{
    m_databaseDescr = databaseDescr;
}


/**
  * Set decimal digits
  */
void BurDbCreationParams::setDecimalDigits(const int decimalDigits)
{
    m_decimalDigits = decimalDigits;
}


/**
  * Set currency code
  */
void BurDbCreationParams::setCurrencyCode(const QString &currencyCode)
{
    m_currencyCode = currencyCode;
}


/**
  * Set currency name
  */
void BurDbCreationParams::setCurrencyName(const QString &currencyName)
{
    m_currencyName = currencyName;
}


/**
  * set currency symbol
  */
void BurDbCreationParams::setCurrencySymbol(const QString &currencySymbol)
{
    m_currencySymbol = currencySymbol;
}
