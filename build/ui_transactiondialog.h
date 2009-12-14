/********************************************************************************
** Form generated from reading ui file 'transactiondialog.ui'
**
** Created: Mon Dec 14 15:28:00 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TRANSACTIONDIALOG_H
#define UI_TRANSACTIONDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_TransactionDialog
{
public:
    QFrame *frame;
    QTableView *tableView;
    QFrame *frame_2;

    void setupUi(QDialog *TransactionDialog)
    {
        if (TransactionDialog->objectName().isEmpty())
            TransactionDialog->setObjectName(QString::fromUtf8("TransactionDialog"));
        TransactionDialog->resize(400, 300);
        TransactionDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        frame = new QFrame(TransactionDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 382, 41));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        tableView = new QTableView(TransactionDialog);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 60, 381, 91));
        tableView->setAutoFillBackground(false);
        tableView->setAlternatingRowColors(true);
        frame_2 = new QFrame(TransactionDialog);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(10, 160, 381, 131));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);

        retranslateUi(TransactionDialog);

        QMetaObject::connectSlotsByName(TransactionDialog);
    } // setupUi

    void retranslateUi(QDialog *TransactionDialog)
    {
        TransactionDialog->setWindowTitle(QApplication::translate("TransactionDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(TransactionDialog);
    } // retranslateUi

};

namespace Ui {
    class TransactionDialog: public Ui_TransactionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSACTIONDIALOG_H
