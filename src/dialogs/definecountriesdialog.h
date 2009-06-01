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

#ifndef DEFINECOUNTRIESDIALOG_H
#define DEFINECOUNTRIESDIALOG_H

#include "bursardb.h"

#include <QtGui/QDialog>
#include <QSqlTableModel>

namespace Ui {
    class DefineCountriesDialog;
}

class DefineCountriesDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(DefineCountriesDialog)

public:
    explicit DefineCountriesDialog(QWidget *parent = 0, BursarDb *db = 0);
    virtual ~DefineCountriesDialog();

protected:
    virtual void changeEvent(QEvent *e);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_addButton_clicked();
    void on_removeButton_clicked();

private:
    void init(BursarDb *db);
    void createModel(BursarDb *db);
    void setupTableView();

    Ui::DefineCountriesDialog *m_ui;
    QSqlTableModel *m_model;
};

#endif // DEFINECOUNTRIESDIALOG_H
