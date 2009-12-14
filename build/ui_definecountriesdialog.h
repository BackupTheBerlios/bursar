/********************************************************************************
** Form generated from reading ui file 'definecountriesdialog.ui'
**
** Created: Mon Dec 14 15:28:00 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DEFINECOUNTRIESDIALOG_H
#define UI_DEFINECOUNTRIESDIALOG_H

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

class Ui_DefineCountriesDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTableView *tableCountries;
    QPushButton *removeButton;
    QPushButton *addButton;

    void setupUi(QDialog *DefineCountriesDialog)
    {
        if (DefineCountriesDialog->objectName().isEmpty())
            DefineCountriesDialog->setObjectName(QString::fromUtf8("DefineCountriesDialog"));
        DefineCountriesDialog->resize(380, 300);
        DefineCountriesDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        buttonBox = new QDialogButtonBox(DefineCountriesDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(290, 20, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tableCountries = new QTableView(DefineCountriesDialog);
        tableCountries->setObjectName(QString::fromUtf8("tableCountries"));
        tableCountries->setGeometry(QRect(10, 10, 271, 241));
        tableCountries->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        removeButton = new QPushButton(DefineCountriesDialog);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setGeometry(QRect(100, 260, 91, 32));
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/remove.svg")), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon);
        addButton = new QPushButton(DefineCountriesDialog);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(10, 260, 91, 32));
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/icons/add.svg")), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon1);

        retranslateUi(DefineCountriesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), DefineCountriesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DefineCountriesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(DefineCountriesDialog);
    } // setupUi

    void retranslateUi(QDialog *DefineCountriesDialog)
    {
        DefineCountriesDialog->setWindowTitle(QApplication::translate("DefineCountriesDialog", "Define Countries", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("DefineCountriesDialog", "Remove", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("DefineCountriesDialog", "Add", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DefineCountriesDialog);
    } // retranslateUi

};

namespace Ui {
    class DefineCountriesDialog: public Ui_DefineCountriesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEFINECOUNTRIESDIALOG_H
