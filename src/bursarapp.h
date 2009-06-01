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

#ifndef BURSARAPP_H
#define BURSARAPP_H

#include "mainwindow.h"
#include "bursardb.h"

#include <QApplication>
#include <QMenuBar>

class BursarApp : public QApplication
{
    Q_OBJECT

public:
    BursarApp(int argc, char *argv[]);
    ~BursarApp();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_actionAboutQt_triggered();

private:
    void createMacStyleMenu();

    // Bursar database
    BursarDb *m_db;

    // mac style menu
    QMenuBar *m_menuBar;

    // main window
    MainWindow *m_mainWindow;
};

#endif // BURSARAPP_H
