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

#include "ui_mainwindow.h"
#include "mainwindow.h"

#include "constants.h"

#include "wizards/newdatabasewizard.h"
#include "wizards/newaccountwizard.h"

#include "dialogs/definecountriesdialog.h"
#include "dialogs/definecurrenciesdialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>


/*************************************************************************
 *  PUBLIC FUNCTIONS
 *************************************************************************/

/**
  * Constructor
  */
MainWindow::MainWindow(BursarDb *db)
    : QMainWindow(NULL), m_ui(new Ui::MainWindowClass)
{
    m_ui->setupUi(this);

    // set database pointer
    m_db = db;

    // initialize mainmenu
    initMainMenu();

    // initialize toolbar
    initToolBar();

    // setup main window
    setupMainWindow();
}


/**
  * Destructor
  */
MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_db;
    delete m_accountTreeModel;
}


/**
  * Setup main window
  */
void MainWindow::setupMainWindow()
{
#ifdef Q_WS_MAC
    // Set up the left-hand side blue side bar.
    m_ui->accountTree->setAttribute(Qt::WA_MacShowFocusRect, false);
#endif

    // Set the palette.
    //QPalette palette = sidebar->palette();
    //QColor macSidebarColor(231, 237, 246);
    //QColor macSidebarHighlightColor(168, 183, 205);
    //palette.setColor(QPalette::Base, macSidebarColor);
    //palette.setColor(QPalette::Highlight, macSidebarHighlightColor);
    //sidebar->setPalette(palette);

    // set window title
    if (m_db->isOpened()) {
        this->setWindowTitle(QString(m_db->databaseTitle() + " - " + APP_NAME));
    } else {
        this->setWindowTitle(APP_NAME);
    }

    // setup menu items
    m_ui->actionNewAccount->setEnabled(m_db->isOpened());
    m_ui->actionDeleteAccount->setEnabled(m_db->isOpened());
    m_ui->actionDefineCurrencies->setEnabled(m_db->isOpened());
    m_ui->actionDefineCountries->setEnabled(m_db->isOpened());
    m_ui->actionDefineTransactionTypes->setEnabled(m_db->isOpened());
    m_ui->actionDefineCategories->setEnabled(m_db->isOpened());
    m_ui->actionDefineAccountTypes->setEnabled(m_db->isOpened());

    // setup account tree
    if (m_db->isOpened()) {
        m_ui->infoFrame->setVisible(true);

        // initialize account tree model
        //initAccountTreeModel();

        m_ui->accountTree->setVisible(true);
    } else {
        m_ui->infoFrame->setVisible(false);
        m_ui->accountTree->setVisible(false);
    }
}




/*************************************************************************
 *  PRIVATE SLOTS
 *************************************************************************/

/**
  * Create new document
  */
void MainWindow::on_actionNew_triggered()
{
    // show new database wizard
    showNewDatabaseWizard();
}


/**
  * Open existing document
  */
void MainWindow::on_actionOpen_triggered()
{
    QString fileName;
    QFileDialog dialog;

    dialog.setDefaultSuffix("bdb");

    fileName = dialog.getOpenFileName(this, tr("Open Database"), "", tr("Bursar Files (*.bdb);;All Files (*.*)"));

    if (fileName != "") {
        if (m_db->openDatabase(fileName)) {
            // setup main window
            setupMainWindow();
        }
    }
}


/**
  * Quit application
  */
void MainWindow::on_actionQuit_triggered()
{
    close();
}


/**
  * New account
  */
void MainWindow::on_actionNewAccount_triggered()
{
    // show new account wizard
    showNewAccountWizard();
}


/**
  * Delete account
  */
void MainWindow::on_actionDeleteAccount_triggered()
{
    showDeleteAccountDialog();
}


/**
  * Define currencies
  */
void MainWindow::on_actionDefineCurrencies_triggered()
{
    showDefineCurrenciesDialog();
}


/**
  * Define countries
  */
void MainWindow::on_actionDefineCountries_triggered()
{
    showDefineCountriesDialog();
}


/**
  * Define transaction types
  */
void MainWindow::on_actionDefineTransactionTypes_triggered()
{
    showDefineTransactionTypesDialog();
}


/**
  * Define account types types
  */
void MainWindow::on_actionDefineAccountTypes_triggered()
{
    showDefineAccountTypesDialog();
}




/*************************************************************************
 *  PRIVATE FUNCTIONS
 *************************************************************************/

/**
  * Initialize MainMenu
  */
void MainWindow::initMainMenu()
{
#ifdef Q_WS_MAC
    // remove icons on mac platform
    m_ui->actionNew->setIconVisibleInMenu(false);
    m_ui->actionOpen->setIconVisibleInMenu(false);
    m_ui->actionQuit->setIconVisibleInMenu(false);
#endif
}


/**
  * Initialize ToolBar
  */
void MainWindow::initToolBar()
{
    m_ui->mainToolBar->addAction(m_ui->actionNew);
    m_ui->mainToolBar->addAction(m_ui->actionOpen);
    m_ui->mainToolBar->addSeparator();
    m_ui->mainToolBar->addAction(m_ui->actionNewAccount);
}


/**
  * Initialize Account Tree Model
  */
void MainWindow::initAccountTreeModel()
{
    // create model
    m_accountTreeModel = new QStandardItemModel();
    m_accountTreeModel->setColumnCount(2);

    // get root item
    QStandardItem *parentItem = m_accountTreeModel->invisibleRootItem();

    // add current accounts
    QStandardItem *item = new QStandardItem(tr("Current Accounts"));
    item->setIcon(QIcon(":/resources/database-new.svg"));
    parentItem->appendRow(item);

    item->appendRows(m_db->currentAccountNames());
    item->appendColumn(m_db->currentAccountBalances());

    parentItem->appendRow(new QStandardItem(tr("Saving Accounts")));
    parentItem->appendRow(new QStandardItem(tr("Credit Cards")));
    parentItem->appendRow(new QStandardItem(tr("Loans")));

    // set model to widget
    m_ui->accountTree->setModel(m_accountTreeModel);
    m_ui->accountTree->setColumnWidth(0, 350);
    m_ui->accountTree->setIconSize(QSize(32, 32));
}


/**
  * Show "New Database" wizard
  */
void MainWindow::showNewDatabaseWizard()
{
    NewDatabaseWizard wizard(this, m_db);

    if (wizard.exec() == QDialog::Accepted) {
        // setup main window
        setupMainWindow();
    }
}

/**
  * Show "New Account" wizard
  */
void MainWindow::showNewAccountWizard()
{
    NewAccountWizard::NewAccountWizard wizard(this, m_db);

    if (wizard.exec() == QDialog::Accepted) {
        // setup main window
        setupMainWindow();
    }
}


/**
  * Show "Delete Account" dialog
  */
void MainWindow::showDeleteAccountDialog()
{
//    DeleteAccountDialog dialog(this, m_db);
//    dialog.exec();
}


/**
  * Show "Define Countries" dialog
  */
void MainWindow::showDefineCountriesDialog()
{
    DefineCountriesDialog dialog(this, m_db);
    dialog.exec();
}


/**
  * Show "Define Currencies" dialog
  */
void MainWindow::showDefineCurrenciesDialog()
{
    DefineCurrenciesDialog dialog(this, m_db);
    dialog.exec();
}


/**
  * Show "Define Transaction Types" dialog
  */
void MainWindow::showDefineTransactionTypesDialog()
{
//    DefineTransactionTypesDialog dialog(this, m_db);
//    dialog.exec();
}


/**
  * Show "Define Account Types" dialog
  */
void MainWindow::showDefineAccountTypesDialog()
{
//    DefineAccountTypesDialog dialog(this, m_db);
//    dialog.exec();
}


/**
  * Show "Define Categories" dialog
  */
void MainWindow::showDefineCategoriesDialog()
{

}
