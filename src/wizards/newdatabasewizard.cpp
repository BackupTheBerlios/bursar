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

#include "newdatabasewizard.h"

#include "constants.h"
#include "burutils.h"

#include <QFile>
#include <QFileDialog>
#include <QGridLayout>
#include <QMessageBox>
#include <QSpacerItem>
#include <QVBoxLayout>


/*************************************************************************
 *  NewDatabaseWizard
 *************************************************************************/

/**
  * Constructor
  */
NewDatabaseWizard::NewDatabaseWizard(QWidget *parent, BurDoc *doc)
    : QWizard(parent)
{
    // add pages
    addPage(new NewDatabaseWizardIntro);
    addPage(new NewDatabaseWizardGeneral);
    addPage(new NewDatabaseWizardFile);
    addPage(new NewDatabaseWizardSettings);
    addPage(new NewDatabaseWizardFinal);

    // set document pointer
    m_doc = doc;

    // set window title
    setWindowTitle(tr("Create a new database"));

    // enable cancel button
    setOption(QWizard::NoCancelButton, false);

    // enable default button
    setOption(QWizard::NoDefaultButton, false);
}


/**
  * Finalize wizard and create new database
  */
void NewDatabaseWizard::accept()
{
    // get values
    QString dbTitle = field("dbTitle").toString();
    QString dbDescr = field("dbDescr").toString();
    int decDigits = field("decDigits").toInt();
    QString curCode = field("curCode").toString();
    QString curName = field("curName").toString();
    QString curSymbol = field("curSymbol").toString();
    QString fileName = field("fileName").toString();

    // create new database
    if (m_doc->createDatabase(dbTitle, dbDescr, fileName, decDigits, curCode, curName, curSymbol)) {
        // close wizard
        QDialog::accept();
    } else {
        // show error message
        QMessageBox::warning(this, tr("Error"), *m_doc->lastErrorText());

        // cancel wizard
        QDialog::reject();
    }
}




/*************************************************************************
 *  NewDatabaseWizardIntro
 *************************************************************************/

/**
  * Constructor
  */
NewDatabaseWizardIntro::NewDatabaseWizardIntro(QWidget *parent)
    : QWizardPage(parent)
{
    // set title
    setTitle(tr("Introduction"));

    // create text label
    m_label = new QLabel(tr("This wizard will enable you to create a new database."));
    m_label->setWordWrap(true);

    // set layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_label);
    setLayout(layout);
}




/*************************************************************************
 *  NewDatabaseWizardGeneral
 *************************************************************************/

/**
  * Constructor
  */
NewDatabaseWizardGeneral::NewDatabaseWizardGeneral(QWidget *parent)
    : QWizardPage(parent)
{
    // set title and subtitle
    setTitle(tr("General Information"));
    setSubTitle(tr("Specify the general information about the new database."));

    // create widgets
    m_dbTitleLabel = new QLabel(tr("Database &Title:"));
    m_dbTitleEdit = new QLineEdit;
    m_dbTitleLabel->setBuddy(m_dbTitleEdit);

    m_dbDescrLabel = new QLabel(tr("Database &Description:"));
    m_dbDescrEdit = new QLineEdit;
    m_dbDescrLabel->setBuddy(m_dbDescrEdit);

    // set field sizes
    BurUtils::setFieldSizes(m_dbTitleEdit, MAX_DB_TITLE);
    BurUtils::setFieldSizes(m_dbDescrEdit, MAX_DB_DESCR);

    // register fields
    registerField("dbTitle*", m_dbTitleEdit);
    registerField("dbDescr", m_dbDescrEdit);

    // create page layout
    QVBoxLayout *pageLayout = new QVBoxLayout;
    pageLayout->addWidget(m_dbTitleLabel);
    pageLayout->addWidget(m_dbTitleEdit);
    pageLayout->addWidget(m_dbDescrLabel);
    pageLayout->addWidget(m_dbDescrEdit);
    setLayout(pageLayout);
}


/**
  * Destructor
  */
NewDatabaseWizardGeneral::~NewDatabaseWizardGeneral()
{
    delete m_dbDescrLabel;
    delete m_dbDescrEdit;

    delete m_dbTitleLabel;
    delete m_dbTitleEdit;
}




/*************************************************************************
 *  NewDatabaseWizardFile
 *************************************************************************/

/**
  * Constructor
  */
NewDatabaseWizardFile::NewDatabaseWizardFile(QWidget *parent)
    : QWizardPage(parent)
{
    // set title and subtitle
    setTitle(tr("Select file name"));
    setSubTitle(tr("Specify the file name of the database."));

    // create widgets
    m_fileLabel = new QLabel(tr("Filename:"));
    m_fileEdit = new QLineEdit;
    m_fileLabel->setBuddy(m_fileEdit);

    m_chooseButton = new QPushButton(tr("Choose"));

    // connect signals
    connect(m_chooseButton, SIGNAL(clicked()), this, SLOT(chooseButton_clicked()));
    connect(m_fileEdit, SIGNAL(editingFinished()), this, SLOT(fileEdit_editingFinished()));

    // register fields
    registerField("fileName*", m_fileEdit);

    // create layout
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(m_fileLabel, 0, 0, 1, 2);
    layout->addWidget(m_fileEdit, 1, 0);
    layout->addWidget(m_chooseButton, 1, 1);
    setLayout(layout);
}


void NewDatabaseWizardFile::chooseButton_clicked()
{
    QString fileName;
    QFileDialog dialog;

    // set dialog properties
    dialog.setDefaultSuffix(DB_DEFAULT_EXT);
    dialog.setConfirmOverwrite(true);

    // get filename
    fileName = dialog.getSaveFileName(NULL, tr("Create Database"), "", tr("Bursar Files (*.bdb);;All Files (*.*)"));

    // add extension and set filename
    m_fileEdit->setText(BurUtils::addFileExtension(fileName, DB_DEFAULT_EXT));
}


void NewDatabaseWizardFile::fileEdit_editingFinished()
{
    // add extension and set filename
    m_fileEdit->setText(BurUtils::addFileExtension(m_fileEdit->text(), DB_DEFAULT_EXT));

    // check if file exists
    if (QFile::exists(m_fileEdit->text())) {
        if (QMessageBox::warning(this, tr("File already exists"),
                                 tr("A file with the choose name already exists. "
                                    "Do you really want to overwrite it?"),
                                 QMessageBox::No, QMessageBox::Yes) == QMessageBox::No) {
            // remove filename
            m_fileEdit->clear();
        }
    }
}




/*************************************************************************
 *  NewDatabaseWizardSettings
 *************************************************************************/

/**
  * Constructor
  */
NewDatabaseWizardSettings::NewDatabaseWizardSettings(QWidget *parent)
    : QWizardPage(parent)
{
    // set title and subtitle
    setTitle(tr("Settings"));
    setSubTitle(tr("Specify the settings for the new database."));

    // create widgets
    m_decDigitsLabel = new QLabel(tr("&Decimal Digits:"));
    m_decDigitsSpin = new QSpinBox;
    m_decDigitsSpin->setRange(0, MAX_DEC_DIGITS);
    m_decDigitsSpin->setValue(DEFAULT_DEC_DIGITS);
    m_decDigitsLabel->setBuddy(m_decDigitsSpin);

    m_curGroupBox = new QGroupBox(tr("System Currency"));

    m_curCodeLabel = new QLabel(tr("Currency &Code:"));
    m_curCodeEdit = new QLineEdit;
    m_curCodeLabel->setBuddy(m_curCodeEdit);

    m_curNameLabel = new QLabel(tr("Currency &Name:"));
    m_curNameEdit = new QLineEdit;
    m_curNameLabel->setBuddy(m_curNameEdit);

    m_curSymbolLabel = new QLabel(tr("Currency &Symbol:"));
    m_curSymbolEdit = new QLineEdit;
    m_curSymbolLabel->setBuddy(m_curSymbolEdit);

    // connect signals
    connect(m_curCodeEdit, SIGNAL(editingFinished()), this, SLOT(curCodeEdit_editingFinished()));

    // set field sizes
    BurUtils::setFieldSizes(m_curCodeEdit, MAX_CURRENCY_CODE);
    BurUtils::setFieldSizes(m_curNameEdit, MAX_CURRENCY_NAME);
    BurUtils::setFieldSizes(m_curSymbolEdit, MAX_CURRENCY_SYMBOL);

    // register fields
    registerField("decDigits", m_decDigitsSpin);
    registerField("curCode*", m_curCodeEdit);
    registerField("curName*", m_curNameEdit);
    registerField("curSymbol", m_curSymbolEdit);

    // create group layout
    QGridLayout *groupLayout = new QGridLayout;
    groupLayout->addWidget(m_curCodeLabel, 0, 0);
    groupLayout->addWidget(m_curCodeEdit, 0, 1);
    groupLayout->addWidget(m_curNameLabel, 1, 0);
    groupLayout->addWidget(m_curNameEdit, 1, 1);
    groupLayout->addWidget(m_curSymbolLabel, 2, 0);
    groupLayout->addWidget(m_curSymbolEdit, 2, 1);
    m_curGroupBox->setLayout(groupLayout);

    // create page layout
    QGridLayout *pageLayout = new QGridLayout;
    pageLayout->addWidget(m_decDigitsLabel, 0, 0);
    pageLayout->addWidget(m_decDigitsSpin, 0, 1);
    pageLayout->addItem(new QSpacerItem(1, 20), 1, 0);
    pageLayout->addWidget(m_curGroupBox, 2, 0, 1, 4);
    setLayout(pageLayout);
}


/**
  * Destructor
  */
NewDatabaseWizardSettings::~NewDatabaseWizardSettings()
{
    delete m_curNameLabel;
    delete m_curNameEdit;

    delete m_curCodeLabel;
    delete m_curCodeEdit;

    delete m_curGroupBox;

    delete m_decDigitsLabel;
    delete m_decDigitsSpin;
}


void NewDatabaseWizardSettings::curCodeEdit_editingFinished()
{
    // change text to upper
    m_curCodeEdit->setText(m_curCodeEdit->text().toUpper());
}


/**
  * Constructor
  */
NewDatabaseWizardFinal::NewDatabaseWizardFinal(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Final"));
    setSubTitle(tr("Some text."));
}
