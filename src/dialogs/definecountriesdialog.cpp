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

#include "definecountriesdialog.h"
#include "ui_definecountriesdialog.h"

#include "constants.h"

#include <QMessageBox>
#include <QSqlDatabase>


/*************************************************************************
 *  PUBLIC FUNCTIONS
 *************************************************************************/

/**
  * Constructor
  */
DefineCountriesDialog::DefineCountriesDialog(QWidget *parent, BurDoc *doc) :
    QDialog(parent),
    m_ui(new Ui::DefineCountriesDialog)
{
    m_ui->setupUi(this);

    // initialise dialog
    init(doc);
}


/**
  * Destructor
  */
DefineCountriesDialog::~DefineCountriesDialog()
{
    delete m_ui;
    delete m_model;
}




/*************************************************************************
 *  PROTECTED FUNCTIONS
 *************************************************************************/

/**
  * Change event handler
  */
void DefineCountriesDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}




/*************************************************************************
 *  PRIVATE SLOTS
 *************************************************************************/

/**
  * Event: ok button clicked
  */
void DefineCountriesDialog::on_buttonBox_accepted()
{
    // submit changes to database
    m_model->submitAll();
    m_model->database().commit();
}


/**
  * Event: cancel button clicked
  */
void DefineCountriesDialog::on_buttonBox_rejected()
{
    // discharge changes
    m_model->revertAll();
}


/**
  * Event: add button clicked
  */
void DefineCountriesDialog::on_addButton_clicked()
{
    // insert row
    m_model->insertRows(m_model->rowCount(), 1);

    // set new row as current
    m_ui->tableCountries->setCurrentIndex(m_model->index(m_model->rowCount() - 1, 0));

    // enable remove button
    m_ui->removeButton->setEnabled(true);

    // set focus to table
    m_ui->tableCountries->setFocus();
}


/**
  * Event: remove button clicked
  */
void DefineCountriesDialog::on_removeButton_clicked()
{
    if (QMessageBox::question(this, tr("Remove Country"),
                              tr("Remove selected country?"),
                              QMessageBox::Yes | QMessageBox::No,
                              QMessageBox::No) == QMessageBox::Yes) {
        // remove row
        m_model->removeRow(m_ui->tableCountries->currentIndex().row());

        // enable or disable remove button
        m_ui->removeButton->setEnabled(m_model->rowCount() > 0);
    }
}




/*************************************************************************
 *  PRIVATE FUNCTIONS
 *************************************************************************/

/**
  * Initialise dialog
  */
void DefineCountriesDialog::init(BurDoc *doc)
{
    // create model
    createModel(doc);

    // setup table view
    setupTableView();

    // enable or disable remove button
    m_ui->removeButton->setEnabled(m_model->rowCount() > 0);
}


/**
  * Create model for table view
  */
void DefineCountriesDialog::createModel(BurDoc *doc)
{
    // create model
    m_model = new QSqlTableModel(this, doc->dbConnection());

    // setup model
    m_model->setTable(TBL_COUNTRIES);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->select();

    // set header titles
    m_model->setHeaderData(0, Qt::Horizontal, tr("Code"));
    m_model->setHeaderData(1, Qt::Horizontal, tr("Name"));
}


/**
  * Setup table view
  */
void DefineCountriesDialog::setupTableView()
{
    // set column widths
    m_ui->tableCountries->setModel(m_model);
    m_ui->tableCountries->setColumnWidth(0, 40);
    m_ui->tableCountries->setColumnWidth(1, 196);
}
