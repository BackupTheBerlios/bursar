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
#include "burutils.h"

#include "wizards/newdatabasewizard.h"
#include "wizards/newaccountwizard.h"

#include "dialogs/transactiondialog.h"
#include "dialogs/definecountriesdialog.h"
#include "dialogs/definecurrenciesdialog.h"

#include <QCloseEvent>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>


/*************************************************************************
 *  PUBLIC FUNCTIONS
 *************************************************************************/

/**
  * Constructor
  */
MainWindow::MainWindow(BurDoc *doc)
    : QMainWindow(NULL), m_ui(new Ui::MainWindowClass)
{
    m_ui->setupUi(this);

    // set document pointer
    m_doc = doc;

    setAttribute(Qt::WA_DeleteOnClose);

    // connect signals
    connect(m_ui->buttonNewAccount, SIGNAL(clicked(bool)), this, SLOT(on_actionNewAccount_triggered()));

    // initialize main menu
    initMainMenu();

    // initialize toolbar
    initToolBar();

    // initialize infobar
    initInfoBar();

    // initialize side menu
    initSideMenu();

    // refresh main window
    refreshMainWindow();
}


/**
  * Destructor
  */
MainWindow::~MainWindow()
{
    m_doc->closeDatabase();

    delete m_doc;
    delete m_ui;
}




/*************************************************************************
 *  PROTECTED FUNCTIONS
 *************************************************************************/

/**
  * Close event
  */
void MainWindow::closeEvent(QCloseEvent *event)
 {
    qDebug() << "CloseEvent";
    m_doc->closeDatabase();

    event->accept();
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

    dialog.setDefaultSuffix(DB_DEFAULT_EXT);

    fileName = dialog.getOpenFileName(this, 
                                      tr("Open Database"), 
                                      "",
                                      tr("Bursar Database Files (*." DB_DEFAULT_EXT ");;All Files (*.*)"));

    if (fileName != "") {
        if (m_doc->openDatabase(fileName)) {
            // initialize account tree
            initAccountTree();

            // initialize journal table
            initJournalTable();

            // refresh main window
            refreshMainWindow();

            // show dashboard
            showDashboard();
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
  * Show current context page
  */
void MainWindow::on_sideMenu_itemClicked(QListWidgetItem *item)
{
    m_ui->contextView->setCurrentIndex(m_ui->sideMenu->currentRow());
}




/*************************************************************************
 *  PRIVATE FUNCTIONS
 *************************************************************************/

/**
  * Initialize main menu
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
  * Initialize tool bar
  */
void MainWindow::initToolBar()
{
    m_ui->mainToolBar->addAction(m_ui->actionNew);
    m_ui->mainToolBar->addAction(m_ui->actionOpen);
}


/**
  * Initialize info bar
  */
void MainWindow::initInfoBar()
{
    // load icons
    QIcon *l_iconInfo = new QIcon(":/icons/account.svg");

    // set icons
    m_ui->iconInfo->setPixmap(l_iconInfo->pixmap(QSize(32, 32), QIcon::Normal));

    // release icon
    delete l_iconInfo;
}


/**
  * Initialize side menu
  */
void MainWindow::initSideMenu()
{
    // set properties
    m_ui->sideMenu->setIconSize(QSize(32, 32));

    // add entries
    m_ui->sideMenu->addItem(new QListWidgetItem(QIcon(":/icons/account.svg"),
                                                tr("Dashboard"), m_ui->sideMenu));

    m_ui->sideMenu->addItem(new QListWidgetItem(QIcon(":/icons/account.svg"),
                                                tr("Accounts"), m_ui->sideMenu));

    m_ui->sideMenu->addItem(new QListWidgetItem(QIcon(":/icons/account.svg"),
                                                tr("Journal"), m_ui->sideMenu));

    m_ui->sideMenu->addItem(new QListWidgetItem(QIcon(":/icons/account.svg"),
                                                tr("Categories"), m_ui->sideMenu));

    m_ui->sideMenu->addItem(new QListWidgetItem(QIcon(":/icons/account.svg"),
                                                tr("Recurring Transactions"), m_ui->sideMenu));

    m_ui->sideMenu->addItem(new QListWidgetItem(QIcon(":/icons/account.svg"),
                                                tr("Reports"), m_ui->sideMenu));
}


/**
  * Initialize account tree
  */
void MainWindow::initAccountTree()
{
    // set model to widget
    m_ui->treeAccounts->setModel(m_doc->accountTreeModel());

    // set icon size
    m_ui->treeAccounts->setIconSize(QSize(32, 32));

    // show header
    m_ui->treeAccounts->setHeaderHidden(false);
}


/**
  * Initialize journal table
  */
void MainWindow::initJournalTable()
{
    // set model to widget
    m_ui->tableJournal->setModel(m_doc->journalTableModel());

    // set selection
    m_ui->tableJournal->setSelectionMode(QAbstractItemView::SingleSelection);

    // hide internal columns
    m_ui->tableJournal->setColumnHidden(m_doc->journalTableModel()->fieldIndex(FLD_JOURNAL_ID), true);

    // create mapper
    createJournalTableMapper();
}


/**
  * Refresh main window
  */
void MainWindow::refreshMainWindow()
{
    bool l_dbOpen = m_doc->isOpen();

    // set window title
    if (l_dbOpen) {
        this->setWindowTitle(QString(m_doc->databaseTitle() + " - " + APP_NAME));
    } else {
        this->setWindowTitle(APP_NAME);
    }

    // show or hide context view
    m_ui->contextView->setVisible(l_dbOpen);

    // show or hide side menu
    m_ui->sideMenu->setVisible(l_dbOpen);

    // show or hide info bar
    m_ui->infoBar->setVisible(l_dbOpen);

    // general setup
    if (l_dbOpen) {
        // refresh info bar
        refreshInfoBar();

        // refresh account tree
        refreshAccountTree();

        // refresh journal table
        refreshJournalTable();

        // refresh journal page
        m_doc->loadAccounts(m_ui->comboAccount);
    }
}


/**
  * Refresh main menu
  */
void MainWindow::refreshMainMenu()
{
    bool l_dbOpen = m_doc->isOpen();

    // setup menu items
    m_ui->actionProperties->setEnabled(l_dbOpen);
    m_ui->actionNewAccount->setEnabled(l_dbOpen);
    m_ui->actionDeleteAccount->setEnabled(l_dbOpen);
    m_ui->actionDefineCurrencies->setEnabled(l_dbOpen);
    m_ui->actionDefineCountries->setEnabled(l_dbOpen);
    m_ui->actionDefineTransactionTypes->setEnabled(l_dbOpen);
    m_ui->actionDefineCategories->setEnabled(l_dbOpen);
    m_ui->actionDefineAccountTypes->setEnabled(l_dbOpen);
}


/**
  * Refresh info bar
  */
void MainWindow::refreshInfoBar()
{
    // refresh info bar
    m_ui->labelTitle->setText(m_doc->databaseTitle());
    m_ui->labelDescr->setText(m_doc->databaseDescr());
}


/**
  * Refresh the account tree
  */
void MainWindow::refreshAccountTree()
{
    // load model data
    m_doc->accountTreeModel()->load();

    // set column widths
    m_ui->treeAccounts->setColumnWidth(0, 350);

    // expand all items
    m_ui->treeAccounts->expandAll();
}


/**
  * Refresh journal table
  */
void MainWindow::refreshJournalTable()
{
    // load model data
    m_doc->journalTableModel()->load();

    int idx = m_doc->journalTableModel()->fieldIndex(FLD_TRANSACTION_TYPE_NAME);

    m_ui->comboTrnType->setModel(m_doc->journalTableModel()->relationModel(idx));
    m_ui->comboTrnType->setModelColumn(1);
}


/**
  * Create mapper for journal table
  */
void MainWindow::createJournalTableMapper()
{
   // create mapper
   //m_journalTableMapper = new QDataWidgetMapper(this);

   // set model
   //m_journalTableMapper->setModel(m_journalTableModel);

   //m_journalTableMapper->addMapping(m_ui->editTrnDate, m_journalTableModel->fieldIndex("TRN_DATE"));
   //m_journalTableMapper->addMapping(m_ui->comboTrnType, m_journalTableModel->fieldIndex("TRN_TYPE_NAME"));
}


/**
  * Show dashboard
  */
void MainWindow::showDashboard()
{
    // show dasboard page
    if (m_doc->isOpen()) {
        m_ui->sideMenu->setCurrentRow(0);
        on_sideMenu_itemClicked(NULL);
    }
}


/**
  * Show "New Database" wizard
  */
void MainWindow::showNewDatabaseWizard()
{
    NewDatabaseWizard l_wizard(this, m_doc);

    if (l_wizard.exec() == QDialog::Accepted) {
        // initialize account tree
        initAccountTree();

        // initialize journal table
        initJournalTable();

        // refresh main window
        refreshMainWindow();

        // show dashboard
        showDashboard();
    }
}

/**
  * Show "New Account" wizard
  */
void MainWindow::showNewAccountWizard()
{
    NewAccountWizard::NewAccountWizard l_wizard(this, m_doc);

    if (l_wizard.exec() == QDialog::Accepted) {
        // refresh main window
        refreshMainWindow();
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
    DefineCountriesDialog l_dialog(this, m_doc);
    l_dialog.exec();
}


/**
  * Show "Define Currencies" dialog
  */
void MainWindow::showDefineCurrenciesDialog()
{
    DefineCurrenciesDialog l_dialog(this, m_doc);
    l_dialog.exec();
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
  * Show "Define Categories" dialog
  */
void MainWindow::showDefineCategoriesDialog()
{

}
