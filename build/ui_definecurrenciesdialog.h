/********************************************************************************
** Form generated from reading ui file 'definecurrenciesdialog.ui'
**
** Created: Mon Dec 14 15:27:58 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DEFINECURRENCIESDIALOG_H
#define UI_DEFINECURRENCIESDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_DefineCurrenciesDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTableView *tableCurrencies;
    QPushButton *addButton;
    QPushButton *removeButton;

    void setupUi(QDialog *DefineCurrenciesDialog)
    {
        if (DefineCurrenciesDialog->objectName().isEmpty())
            DefineCurrenciesDialog->setObjectName(QString::fromUtf8("DefineCurrenciesDialog"));
        DefineCurrenciesDialog->resize(380, 300);
        DefineCurrenciesDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        buttonBox = new QDialogButtonBox(DefineCurrenciesDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(290, 20, 81, 241));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tableCurrencies = new QTableView(DefineCurrenciesDialog);
        tableCurrencies->setObjectName(QString::fromUtf8("tableCurrencies"));
        tableCurrencies->setGeometry(QRect(10, 10, 271, 241));
        tableCurrencies->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        addButton = new QPushButton(DefineCurrenciesDialog);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(10, 260, 91, 32));
        removeButton = new QPushButton(DefineCurrenciesDialog);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setGeometry(QRect(100, 260, 91, 32));

        retranslateUi(DefineCurrenciesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), DefineCurrenciesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DefineCurrenciesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(DefineCurrenciesDialog);
    } // setupUi

    void retranslateUi(QDialog *DefineCurrenciesDialog)
    {
        DefineCurrenciesDialog->setWindowTitle(QApplication::translate("DefineCurrenciesDialog", "Define Currencies", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("DefineCurrenciesDialog", "Add", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("DefineCurrenciesDialog", "Remove", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DefineCurrenciesDialog);
    } // retranslateUi

};

namespace Ui {
    class DefineCurrenciesDialog: public Ui_DefineCurrenciesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEFINECURRENCIESDIALOG_H
