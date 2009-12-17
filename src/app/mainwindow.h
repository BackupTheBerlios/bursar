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

#include "burdoc.h"

#include <QListWidgetItem>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMainWindow>

namespace Ui
{
    class MainWindowClass;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(BurDoc *doc);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
    void on_actionNewAccount_triggered();
    void on_actionDeleteAccount_triggered();
    void on_actionDefineCountries_triggered();
    void on_actionDefineCurrencies_triggered();
    void on_actionDefineTransactionTypes_triggered();

    void on_sideMenu_itemClicked(QListWidgetItem *item);

private:
    void initToolBar();
    void initInfoBar();
    void initSideMenu();
    void initAccountTree();
    void initJournalTable();

    void refreshMainWindow();
    void refreshMainMenu();
    void refreshInfoBar();
    void refreshAccountTree();
    void refreshJournalTable();

    // setup journal table model
    void setupJournalTableModel();

    // create journal table mapper
    void createJournalTableMapper();

    void showDashboard();

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

    // main window widget
    Ui::MainWindowClass *m_ui;

    // bursar document
    BurDoc *m_doc;

    // journal table mapper
    QDataWidgetMapper *m_journalTableMapper;
};

#endif // MAINWINDOW_H
