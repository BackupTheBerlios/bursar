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

#ifndef NEWDOCUMENTWIZARD_H
#define NEWDOCUMENTWIZARD_H

#include "burdoc.h"

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QWizard>
#include <QWizardPage>


/*************************************************************************
 *  NewDocumentWizard
 *************************************************************************/

class NewDocumentWizard : public QWizard
{
    Q_OBJECT

public:
    NewDocumentWizard(QWidget *parent, BurDoc *doc);

    void accept();

private:
    BurDoc *m_doc;
};




/*************************************************************************
 *  NewDocumentWizardIntro
 *************************************************************************/

class NewDocumentWizardIntro : public QWizardPage
{
    Q_OBJECT

public:
    NewDocumentWizardIntro(QWidget *parent = 0);

 private:
    QLabel *m_label;
};




/*************************************************************************
 *  NewDocumentWizardGeneral
 *************************************************************************/

class NewDocumentWizardGeneral : public QWizardPage
{
    Q_OBJECT

public:
    NewDocumentWizardGeneral(QWidget *parent = 0);
    ~NewDocumentWizardGeneral();

private:
    QLabel *m_titleLabel;
    QLabel *m_descrLabel;
    QLineEdit *m_titleEdit;
    QLineEdit *m_descrEdit;
};




/*************************************************************************
 *  NewDocumentWizardFile
 *************************************************************************/

class NewDocumentWizardFile : public QWizardPage
{
    Q_OBJECT

public:
    NewDocumentWizardFile(QWidget *parent = 0);

private slots:
    void chooseButton_clicked();
    void fileEdit_editingFinished();

private:
    QLabel *m_fileLabel;
    QLineEdit *m_fileEdit;
    QPushButton *m_chooseButton;
};




/*************************************************************************
 *  NewDocumentWizardSettings
 *************************************************************************/

class NewDocumentWizardSettings : public QWizardPage
{
    Q_OBJECT

public:
    NewDocumentWizardSettings(QWidget *parent = 0);
    ~NewDocumentWizardSettings();

private slots:
    void curCodeEdit_editingFinished();

private:
    QLabel *m_decDigitsLabel;
    QLabel *m_curCodeLabel;
    QLabel *m_curNameLabel;
    QLabel *m_curSymbolLabel;
    QSpinBox *m_decDigitsSpin;
    QLineEdit *m_curCodeEdit;
    QLineEdit *m_curNameEdit;
    QLineEdit *m_curSymbolEdit;
    QGroupBox *m_curGroupBox;
};




/*************************************************************************
 *  NewDocumentWizardFinal
 *************************************************************************/

class NewDocumentWizardFinal : public QWizardPage
{
    Q_OBJECT

public:
    NewDocumentWizardFinal(QWidget *parent = 0);
};


#endif // NEWDOCUMENTWIZARD_H
