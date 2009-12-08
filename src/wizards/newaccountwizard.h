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

#ifndef NEWACCOUNTWIZARD_H
#define NEWACCOUNTWIZARD_H

#include "burdoc.h"
#include "burcombobox.h"

#include <QWizard>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>

class NewAccountWizard : public QWizard
{
    Q_OBJECT

public:
    NewAccountWizard(QWidget *parent, BurDoc *oc);

    void accept();

private:
    BurDoc *m_doc;
};


class NewAccountWizardIntro : public QWizardPage
{
    Q_OBJECT

public:
    NewAccountWizardIntro(QWidget *parent = 0);

 private:
    QLabel *m_label;
};


class NewAccountWizardType : public QWizardPage
{
    Q_OBJECT

public:
    NewAccountWizardType(QWidget *parent = 0, BurDoc *doc = 0);

private:
    BurComboBox *m_accountTypeCombo;
};


class NewAccountWizardGeneral : public QWizardPage
{
    Q_OBJECT

public:
    NewAccountWizardGeneral(QWidget *parent = 0, BurDoc *doc = 0);

private:
    QLabel *m_accountNameLabel;
    QLineEdit *m_accountNameEdit;

    QLabel *m_countryLabel;
    BurComboBox *m_countryCombo;

    QLabel *m_currencyLabel;
    BurComboBox *m_currencyCombo;
};


class NewAccountWizardFinal : public QWizardPage
{
    Q_OBJECT

public:
    NewAccountWizardFinal(QWidget *parent = 0);
};


#endif // NEWACCOUNTWIZARD_H
