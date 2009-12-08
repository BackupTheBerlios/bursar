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

#include "burutils.h"
#include "constants.h"

#include <QApplication>


/*************************************************************************
 *  PUBLIC FUNCTIONS
 *************************************************************************/

/**
  * Convert a boolean to QString
  */
QString BurUtils::boolToStr(bool value)
{
    if (value) {
        return "true";
    } else {
        return "false";
    }
}


/**
  * Convert an integer to QString
  */
QString BurUtils::intToStr(int value)
{
    return QString::number(value);
}


/**
  * Add extension to filename
  */
QString BurUtils::addFileExtension(const QString &fileName, const QString &extension)
{
    QString newFileName = fileName;

    if (newFileName != "") {
        if (newFileName.right(4).toUpper() != QString(".").append(extension).toUpper()) {
            if (newFileName.right(1) != ".") {
                newFileName.append(".");
            }

            newFileName.append(extension);
        }
    }

    return newFileName;
}


/**
  * Find shared directory
  */
QString BurUtils::findSharedDir()
{
    // get current application dir
    QString dir = qApp->applicationDirPath();

#ifdef Q_WS_MAC
    // shared files are in application bundle
    return dir.append("/" DIR_MAC_SHARED);
#endif

#ifdef Q_WS_X11
    // shared files are in /usr/share or /usr/local/share
    if (dir.right(3) == "bin") {
        // standard unix installation
        return dir.left(dir.length() - 3).append("/share/" DIR_X11_SHARED);
    } else {
        // "sandbox" installation -> shared files are in subfolder
        return dir.append("/share/" DIR_X11_SHARED);
    }
#endif

#ifdef Q_WS_WIN
    // shared files will be in data directory
    return dir.append("\\" DIR_WIN_SHARED);
#endif
}


/**
  * Returns directory of db templates
  */
QString BurUtils::dbTemplatesDir()
{
    // find shared directory
    QString dir = findSharedDir();

#ifdef Q_WS_WIN
    return dir.append("\\" DIR_DBTEMPLATES "\\");
#else
    return dir.append("/" DIR_DBTEMPLATES "/");
#endif
}


/**
  * Set the maximum length and width of a QLineEdit
  */
void BurUtils::setFieldSizes(QLineEdit *lineEdit, int size)
{
    // set maximum input length
    lineEdit->setMaxLength(size);

    // set maximum field width (min. 30)
    lineEdit->setMaximumWidth(size * 15 > 30 ? size * 15 : 30);
}
