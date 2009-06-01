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

#include "newaccountwizard.h"

#include "constants.h"
#include "utils.h"
#include "dbconstants.h"

#include <QVBoxLayout>
#include <QGridLayout>


/*************************************************************************
 *  NEWACCOUNTWIZARD CLASS
 *************************************************************************/

/**
  * Constructor
  */
NewAccountWizard::NewAccountWizard(QWidget *parent, BursarDb *db)
    : QWizard(parent)
{
    addPage(new NewAccountWizardIntro);
    addPage(new NewAccountWizardType(this, db));
    addPage(new NewAccountWizardGeneral(this, db));
    addPage(new NewAccountWizardFinal);

    // set database pointer
    m_db = db;

    // set window title
    setWindowTitle(tr("New Account"));

    // change default property for combobox
    setDefaultProperty("QComboBox", "currentText", "currentIndexChanged");

    // enable cancel button
    setOption(QWizard::NoCancelButton, false);

    // enable default button
    setOption(QWizard::NoDefaultButton, false);
}


void NewAccountWizard::accept()
{
    // get values
    //QString dbTitle = field("dbTitle").toString();
    //QString curCode = field("curCode").toString();
    //QString curName = field("curName").toString();
    //QString fileName = field("fileName").toString();

    // create database
    //m_db->createDatabase(dbTitle, fileName, curCode, curName);

    // close wizard
    QDialog::accept();
}




/*************************************************************************
 *  NEWACCOUNTWIZARDINTRO CLASS
 *************************************************************************/

/**
  * Constructor
  */
NewAccountWizardIntro::NewAccountWizardIntro(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));

    label = new QLabel(tr("This wizard will generate a new account."));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}




/*************************************************************************
 *  NEWACCOUNTWIZARDTYPE CLASS
 *************************************************************************/

/**
  * Constructor
  */
NewAccountWizardType::NewAccountWizardType(QWidget *parent, BursarDb *db)
    : QWizardPage(parent)
{
    // set title and subtitle
    setTitle(tr("Select Account Type"));
    setSubTitle(tr("Select the type of account which should be created."));

    // add widgets
    accountTypeLabel = new QLabel(tr("Account &Type:"));
    accountTypeCombo = new QComboBox();
    accountTypeLabel->setBuddy(accountTypeCombo);

    // load account types for combobox
    db->loadAccountTypes(accountTypeCombo);

    // register fields
    registerField("accountType*", accountTypeCombo);

    // set layout
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(accountTypeLabel, 0, 0);
    layout->addWidget(accountTypeCombo, 1, 0);
    setLayout(layout);
}




/*************************************************************************
 *  NEWACCOUNTWIZARDGENERAL CLASS
 *************************************************************************/

/**
  * Constructor
  */
NewAccountWizardGeneral::NewAccountWizardGeneral(QWidget *parent, BursarDb *db)
    : QWizardPage(parent)
{
    // set title and subtitle
    setTitle(tr("General Information"));
    setSubTitle(tr("Specify general information about the new account."));

    // add widgets
    accountNameLabel = new QLabel(tr("Account &Name:"));
    accountNameEdit = new QLineEdit();
    accountNameLabel->setBuddy(accountNameEdit);

    countryLabel = new QLabel(tr("Account C&ountry:"));
    countryCombo = new QComboBox();
    countryLabel->setBuddy(countryCombo);

    currencyLabel = new QLabel(tr("Account &Currency:"));
    currencyCombo = new QComboBox();
    currencyLabel->setBuddy(currencyCombo);

    // load data for comboboxes
    db->loadCountries(countryCombo);
    db->loadCurrencies(currencyCombo);

    // register fields
    registerField("accountName*", accountNameEdit);
    registerField("country*", countryCombo);
    registerField("currency*", currencyCombo);

    // set layout
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(accountNameLabel, 0, 0);
    layout->addWidget(accountNameEdit, 0, 1);
    layout->addWidget(countryLabel, 1, 0);
    layout->addWidget(countryCombo, 1, 1);
    layout->addWidget(currencyLabel, 2, 0);
    layout->addWidget(currencyCombo, 2, 1);
    setLayout(layout);
}



/*************************************************************************
 *  NEWACCOUNTWIZARDFINAL CLASS
 *************************************************************************/

/**
  * Constructor
  */
NewAccountWizardFinal::NewAccountWizardFinal(QWidget *parent)
    : QWizardPage(parent)
{
    // set title and subtitle
    setTitle(tr("Finalize"));
    setSubTitle(tr("Continue to create the account."));
}
