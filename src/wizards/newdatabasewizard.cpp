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
#include "utils.h"
#include "dbconstants.h"

#include <QFile>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>


/**
  * Constructor
  */
NewDatabaseWizard::NewDatabaseWizard(QWidget *parent, BursarDb *db)
    : QWizard(parent)
{
    addPage(new NewDatabaseWizardIntro);
    addPage(new NewDatabaseWizardGeneral);
    addPage(new NewDatabaseWizardFile);
    addPage(new NewDatabaseWizardFinal);

    // set database pointer
    m_db = db;

    // set window title
    setWindowTitle(tr("New Database"));

    // enable cancel button
    setOption(QWizard::NoCancelButton, false);

    // enable default button
    setOption(QWizard::NoDefaultButton, false);
}


void NewDatabaseWizard::accept()
{
    // get values
    QString dbTitle = field("dbTitle").toString();
    QString curCode = field("curCode").toString();
    QString curName = field("curName").toString();
    QString fileName = field("fileName").toString();

    // create database
    if (m_db->createDatabase(dbTitle, fileName, curCode, curName)) {
        // accept
        QDialog::accept();
    } else {
        // show error message
        QMessageBox::warning(this, tr("Error"), *m_db->lastErrorText());

        // reject
        QDialog::reject();
    }
}


NewDatabaseWizardIntro::NewDatabaseWizardIntro(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));

    m_label = new QLabel(tr("This wizard will generate a new database file, including "
                          "the general settings."));
    m_label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_label);
    setLayout(layout);
}


NewDatabaseWizardGeneral::NewDatabaseWizardGeneral(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("General Information"));
    setSubTitle(tr("Specify general information about the new database."));

    m_dbTitleLabel = new QLabel(tr("Database &title:"));
    m_dbTitleEdit = new QLineEdit;
    m_dbTitleEdit->setMaxLength(MAX_DB_TITLE);
    m_dbTitleLabel->setBuddy(m_dbTitleEdit);

    m_curCodeLabel = new QLabel(tr("Base Currency &code:"));
    m_curCodeEdit = new QLineEdit;
    m_curCodeEdit->setMaxLength(MAX_CURRENCY_CODE);
    m_curCodeLabel->setBuddy(m_curCodeEdit);

    m_curNameLabel = new QLabel(tr("Base Currency &name:"));
    m_curNameEdit = new QLineEdit;
    m_curNameEdit->setMaxLength(MAX_CURRENCY_NAME);
    m_curNameLabel->setBuddy(m_curNameEdit);

    connect(m_curCodeEdit, SIGNAL(editingFinished()), this, SLOT(curCodeEdit_editingFinished()));

    registerField("dbTitle*", m_dbTitleEdit);
    registerField("curCode*", m_curCodeEdit);
    registerField("curName*", m_curNameEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(m_dbTitleLabel, 0, 0);
    layout->addWidget(m_dbTitleEdit, 1, 0, 1, 2);
    layout->setRowMinimumHeight(2, 20);
    layout->addWidget(m_curCodeLabel, 3, 0);
    layout->addWidget(m_curCodeEdit, 3, 1);
    layout->addWidget(m_curNameLabel, 4, 0);
    layout->addWidget(m_curNameEdit, 4, 1);
    setLayout(layout);
}


void NewDatabaseWizardGeneral::curCodeEdit_editingFinished()
{
    // change text to upper
    m_curCodeEdit->setText(m_curCodeEdit->text().toUpper());
}


NewDatabaseWizardFile::NewDatabaseWizardFile(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Select file name"));
    setSubTitle(tr("Specify the file name of the database."));

    m_fileLabel = new QLabel(tr("Filename:"));
    m_fileEdit = new QLineEdit;
    m_fileLabel->setBuddy(m_fileEdit);

    m_chooseButton = new QPushButton(tr("Choose"));

    connect(m_chooseButton, SIGNAL(clicked()), this, SLOT(chooseButton_clicked()));
    connect(m_fileEdit, SIGNAL(editingFinished()), this, SLOT(fileEdit_editingFinished()));

    registerField("fileName*", m_fileEdit);

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
    m_fileEdit->setText(Utils::addFileExtension(fileName, DB_DEFAULT_EXT));
}


void NewDatabaseWizardFile::fileEdit_editingFinished()
{
    // add extension and set filename
    m_fileEdit->setText(Utils::addFileExtension(m_fileEdit->text(), DB_DEFAULT_EXT));

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


NewDatabaseWizardFinal::NewDatabaseWizardFinal(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Final"));
    setSubTitle(tr("Some text."));
}
