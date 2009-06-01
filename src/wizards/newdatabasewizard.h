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

#ifndef NEWDATABASEWIZARD_H
#define NEWDATABASEWIZARD_H

#include "bursardb.h"

#include <QWizard>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class NewDatabaseWizard : public QWizard
{
    Q_OBJECT

public:
    NewDatabaseWizard(QWidget *parent, BursarDb *db);

    void accept();

private:
    BursarDb *m_db;
};


class NewDatabaseWizardIntro : public QWizardPage
{
    Q_OBJECT

public:
    NewDatabaseWizardIntro(QWidget *parent = 0);

 private:
    QLabel *m_label;
};


class NewDatabaseWizardGeneral : public QWizardPage
{
    Q_OBJECT

public:
    NewDatabaseWizardGeneral(QWidget *parent = 0);

private slots:
    void curCodeEdit_editingFinished();

private:
    QLabel *m_dbTitleLabel;
    QLabel *m_curCodeLabel;
    QLabel *m_curNameLabel;
    QLineEdit *m_dbTitleEdit;
    QLineEdit *m_curCodeEdit;
    QLineEdit *m_curNameEdit;
};


class NewDatabaseWizardFile : public QWizardPage
{
    Q_OBJECT

public:
    NewDatabaseWizardFile(QWidget *parent = 0);

private slots:
    void chooseButton_clicked();
    void fileEdit_editingFinished();

private:
    QLabel *m_fileLabel;
    QLineEdit *m_fileEdit;
    QPushButton *m_chooseButton;
};


class NewDatabaseWizardFinal : public QWizardPage
{
    Q_OBJECT

public:
    NewDatabaseWizardFinal(QWidget *parent = 0);
};


#endif // NEWDATABASEWIZARD_H
