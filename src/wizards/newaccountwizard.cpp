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
#include "burutils.h"

#include <QDebug>
#include <QFormLayout>
#include <QMessageBox>
#include <QVBoxLayout>


/*************************************************************************
 *  NEWACCOUNTWIZARD CLASS
 *************************************************************************/

/**
  * Constructor
  */
NewAccountWizard::NewAccountWizard(QWidget *parent, BurDoc *doc)
    : QWizard(parent)
{
    addPage(new NewAccountWizardIntro);
    addPage(new NewAccountWizardType(this, doc));
    addPage(new NewAccountWizardGeneral(this, doc));
    addPage(new NewAccountWizardFinal);

    // set document pointer
    m_doc = doc;

    // set window title
    setWindowTitle(tr("Add New Account"));

    // enable cancel button
    setOption(QWizard::NoCancelButton, false);

    // enable default button
    setOption(QWizard::NoDefaultButton, false);
}


void NewAccountWizard::accept()
{
    // get values
    QString accountType = field("accountType").toString();
    QString accountName = field("accountName").toString();
    QString countryCode = field("countryCode").toString();
    QString currencyCode = field("currencyCode").toString();

    // add account
    m_doc->addAccount(accountName, accountType, countryCode, currencyCode);

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

    m_label = new QLabel(tr("This wizard will add a new account to the database."));
    m_label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_label);
    setLayout(layout);
}




/*************************************************************************
 *  NEWACCOUNTWIZARDTYPE CLASS
 *************************************************************************/

/**
  * Constructor
  */
NewAccountWizardType::NewAccountWizardType(QWidget *parent, BurDoc *doc)
    : QWizardPage(parent)
{
    // set title and subtitle
    setTitle(tr("Select Account Type"));
    setSubTitle(tr("Select the type of account which should be added."));

    // add widgets
    m_accountTypeCombo = new BurComboBox();

    // load account types for combobox
    doc->loadAccountTypes(m_accountTypeCombo);

    // register fields
    registerField("accountType*", m_accountTypeCombo,
                  "currentItemData", SIGNAL(currentItemDataChanged(QVariant)));

    // set layout
    QFormLayout *layout = new QFormLayout;
    layout->addRow(tr("Account &Type:"), m_accountTypeCombo);
    setLayout(layout);
}




/*************************************************************************
 *  NEWACCOUNTWIZARDGENERAL CLASS
 *************************************************************************/

/**
  * Constructor
  */
NewAccountWizardGeneral::NewAccountWizardGeneral(QWidget *parent, BurDoc *doc)
    : QWizardPage(parent)
{
    // set title and subtitle
    setTitle(tr("General Information"));
    setSubTitle(tr("Specify general information about the new account."));

    // add widgets
    m_accountNameLabel = new QLabel(tr("Account &Name:"));
    m_accountNameEdit = new QLineEdit();
    m_accountNameLabel->setBuddy(m_accountNameEdit);

    m_countryLabel = new QLabel(tr("Account C&ountry:"));
    m_countryCombo = new BurComboBox();
    m_countryLabel->setBuddy(m_countryCombo);

    m_currencyLabel = new QLabel(tr("Account &Currency:"));
    m_currencyCombo = new BurComboBox();
    m_currencyLabel->setBuddy(m_currencyCombo);

    // load data for comboboxes
    doc->loadCountries(m_countryCombo);
    doc->loadCurrencies(m_currencyCombo);

    // register fields
    registerField("accountName*", m_accountNameEdit);
    registerField("countryCode*", m_countryCombo,
                  "currentItemData", SIGNAL(currentItemDataChanged(QVariant)));
    registerField("currencyCode*", m_currencyCombo,
                  "currentItemData", SIGNAL(currentItemDataChanged(QVariant)));

    // set layout
    QFormLayout *layout = new QFormLayout;
    layout->addRow(m_accountNameLabel, m_accountNameEdit);
    layout->addRow(m_countryLabel, m_countryCombo);
    layout->addRow(m_currencyLabel, m_currencyCombo);
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
