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

#ifndef BUROBJECT_H
#define BUROBJECT_H

#include <QObject>
#include <QString>
#include <QDebug>


/**
  * Debug Level
  */
enum BurDebugLevel {
    NONE,               /* no debug information        */
    MINIMAL,            /* minimal debug information   */
    FULL                /* full debug information      */
};


/**
  * Bursar Base Object
  */
class BurObject : public QObject
{
    Q_OBJECT

public:
    BurObject(const QString objectName, BurDebugLevel debugLevel = NONE);

protected:
    BurDebugLevel debugLevel();

    void debug(const QString &text);
    void debug(const QString &text, bool result);

private:
    // Object Name
    QString m_objectName;

    // Debug Level
    BurDebugLevel m_debugLevel;
};

#endif // BUROBJECT_H
