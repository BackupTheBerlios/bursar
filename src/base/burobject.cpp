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

#include "burobject.h"
#include "burutils.h"


/*************************************************************************
 *  PUBLIC FUNCTIONS
 *************************************************************************/

/**
  * Constructor
  */
BurObject::BurObject(QString objectName, BurDebugLevel debugLevel) :
    QObject()
{
    // set object name
    m_objectName = objectName;

    // set debug level
    m_debugLevel = debugLevel;
}




/*************************************************************************
 *  PROTECTED FUNCTIONS
 *************************************************************************/

/**
  * Return debug level
  */
BurDebugLevel BurObject::debugLevel()
{
    return m_debugLevel;
}


/**
  * Write debug information
  */
void BurObject::debug(const QString &text)
{
    qDebug() << m_objectName + "::" + text;
}


/**
  * Write debug information
  */
void BurObject::debug(const QString &text, bool result)
{
    debug(text + ": " + BurUtils::boolToStr(result));
}
