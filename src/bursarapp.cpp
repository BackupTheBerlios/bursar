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

#include "bursarapp.h"
#include "constants.h"
#include "config.h"

#include "wizards/newdatabasewizard.h"

#include <QDebug>
#include <QDialog>
#include <QFileDialog>


/*************************************************************************
 *  PUBLIC FUNCTIONS
 *************************************************************************/

/**
  * Constructor
  */
BursarApp::BursarApp(int argc, char *argv[])
    : QApplication(argc, argv)
{
    // set application properties
    setApplicationName(APP_NAME);
    setApplicationVersion(APP_VERSION);

    // mac specific
#ifdef Q_WS_MAC
    // don't quit application when last window closes
    //setQuitOnLastWindowClosed(false);

    // create mac style menu
    //createMacStyleMenu();
#endif

    // create bursar document
    m_doc = new BurDoc(FULL);

    // create main window
    m_mainWindow = new MainWindow(m_doc);

#ifndef Q_WS_MAC
    // show main window
    m_mainWindow->show();
#endif
}


/**
  * Destructor
  */
BursarApp::~BursarApp()
{
    delete m_doc;

#ifdef Q_WS_MAC
    delete m_menuBar;
#endif
}




/*************************************************************************
 *  PRIVATE SLOTS
 *************************************************************************/

/**
  * Create new database
  */
void BursarApp::on_actionNew_triggered()
{
    NewDatabaseWizard wizard(NULL, m_doc);
    if (wizard.exec() == QDialog::Accepted) {
        // setup main window

        // show main window
        m_mainWindow->show();
    }
}


/**
  * Open existing database
  */
void BursarApp::on_actionOpen_triggered()
{
    QString fileName;
    QFileDialog dialog;

    dialog.setDefaultSuffix("bdb");

    fileName = dialog.getOpenFileName(NULL, tr("Open Database"), "", tr("Bursar Files (*.bdb);;All Files (*.*)"));

    if (fileName != "") {
        if (m_doc->openDatabase(fileName)) {
            // create main window
            //if (m_mainWindow != NULL) {
            //    m_mainWindow = new MainWindow(m_db);

                // show main window
            //    m_mainWindow->show();
            //} else {
                // initialize main window
                //m_mainWindow->init();
            //}
        }
    }
}


/**
  * Quit application
  */
void BursarApp::on_actionQuit_triggered()
{
    quit();
}


/**
  * Show infos about Bursar
  */
void BursarApp::on_actionAbout_triggered()
{
}


/**
  * Show infos about Qt
  */
void BursarApp::on_actionAboutQt_triggered()
{
    aboutQt();
}




/*************************************************************************
 *  PRIVATE FUNCTIONS
 *************************************************************************/

/**
  * Create menu for mac
  */
void BursarApp::createMacStyleMenu()
{
    // create menu
    m_menuBar = new QMenuBar();

    // add file menu
    QMenu *fileMenu = m_menuBar->addMenu(tr("&File"));
    QAction *actionNew = fileMenu->addAction(tr("&New..."));
    QAction *actionOpen = fileMenu->addAction(tr("&Open..."));
    QAction *actionQuit = fileMenu->addAction(tr("&Quit"));

    // add help menu
    QMenu *helpMenu = m_menuBar->addMenu(tr("&Help"));
    QAction *actionAbout = helpMenu->addAction(tr("About %1").arg(APP_NAME));
    QAction *actionAboutQt = helpMenu->addAction(tr("About Qt"));

    // connect signals to slots
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_triggered()));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_triggered()));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(on_actionQuit_triggered()));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(on_actionAbout_triggered()));
    connect(actionAboutQt, SIGNAL(triggered()), this, SLOT(on_actionAboutQt_triggered()));
}
