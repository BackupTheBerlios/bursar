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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bursardb.h"

#include <QMainWindow>

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(BursarDb *db);
    ~MainWindow();

    // setup main window
    void setupMainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
    void on_actionNewAccount_triggered();
    void on_actionDeleteAccount_triggered();
    void on_actionDefineCountries_triggered();
    void on_actionDefineCurrencies_triggered();
    void on_actionDefineTransactionTypes_triggered();
    void on_actionDefineAccountTypes_triggered();

private:
    // initialize mainmenu
    void initMainMenu();

    // initialize toolbar
    void initToolBar();

    // initialize account tree model
    void initAccountTreeModel();

    // show "New Database" wizard
    void showNewDatabaseWizard();

    // show "New Account" wizard
    void showNewAccountWizard();

    // show "Delete Account" dialog
    void showDeleteAccountDialog();

    // show "Define Currencies" dialog
    void showDefineCurrenciesDialog();

    // show "Define Countries" dialog
    void showDefineCountriesDialog();

    // show "Define Transaction Types" dialog
    void showDefineTransactionTypesDialog();

    // show "Define Account Types" dialog
    void showDefineAccountTypesDialog();

    // show "Define Categories" dialog
    void showDefineCategoriesDialog();

    Ui::MainWindowClass *m_ui;

    // bursar database
    BursarDb *m_db;

    // account tree model
    QStandardItemModel *m_accountTreeModel;
};

#endif // MAINWINDOW_H
