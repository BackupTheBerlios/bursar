/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Mon Dec 14 15:28:00 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "burcombobox.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionNew;
    QAction *actionDefineCountries;
    QAction *actionDefineCurrencies;
    QAction *actionOpen;
    QAction *actionDefineTransactionTypes;
    QAction *actionDefineCategories;
    QAction *actionNewAccount;
    QAction *actionDefineAccountTypes;
    QAction *actionDeleteAccount;
    QAction *actionQuit;
    QAction *actionProperties;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QFrame *infoBar;
    QLabel *iconInfo;
    QLabel *labelTitle;
    QLabel *labelDescr;
    QHBoxLayout *horizontalLayout;
    QListWidget *sideMenu;
    QStackedWidget *contextView;
    QWidget *pageDashboard;
    QVBoxLayout *verticalLayout;
    QWidget *pageAccounts;
    QVBoxLayout *verticalLayout_3;
    QTreeView *treeAccounts;
    QFrame *frameAccountButtons;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *buttonNewAccount;
    QPushButton *buttonEditAccount;
    QPushButton *buttonDeleteAccount;
    QWidget *pageJournal;
    QVBoxLayout *verticalLayout_4;
    QFrame *frameJournalList;
    QGridLayout *gridLayout;
    QLabel *labelAccount;
    QTableView *tableJournal;
    BurComboBox *comboAccount;
    QFrame *frameJournalDetail;
    QGridLayout *gridLayout_2;
    QLabel *labelTrnDate;
    QLabel *labelMemo;
    QLabel *label_7;
    QLabel *labelRepDate;
    QDateEdit *editTrnDate;
    QDateEdit *editRepDate;
    QLineEdit *editMemo;
    QLabel *labelValDate;
    QDateEdit *editValDate;
    QLabel *labelTrnType;
    QComboBox *comboTrnType;
    QLabel *labelCategory;
    QLineEdit *lineEdit_2;
    QComboBox *comboCategory;
    QWidget *pageCategories;
    QWidget *pageRecurring;
    QWidget *pageReports;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QMenu *menuAccount;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(829, 664);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindowClass->sizePolicy().hasHeightForWidth());
        MainWindowClass->setSizePolicy(sizePolicy);
        MainWindowClass->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        MainWindowClass->setDocumentMode(false);
        MainWindowClass->setUnifiedTitleAndToolBarOnMac(true);
        actionNew = new QAction(MainWindowClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/database-new.svg")), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionNew->setIconVisibleInMenu(true);
        actionDefineCountries = new QAction(MainWindowClass);
        actionDefineCountries->setObjectName(QString::fromUtf8("actionDefineCountries"));
        actionDefineCurrencies = new QAction(MainWindowClass);
        actionDefineCurrencies->setObjectName(QString::fromUtf8("actionDefineCurrencies"));
        actionOpen = new QAction(MainWindowClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/icons/database-open.svg")), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionDefineTransactionTypes = new QAction(MainWindowClass);
        actionDefineTransactionTypes->setObjectName(QString::fromUtf8("actionDefineTransactionTypes"));
        actionDefineCategories = new QAction(MainWindowClass);
        actionDefineCategories->setObjectName(QString::fromUtf8("actionDefineCategories"));
        actionNewAccount = new QAction(MainWindowClass);
        actionNewAccount->setObjectName(QString::fromUtf8("actionNewAccount"));
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/icons/account-new.svg")), QIcon::Normal, QIcon::Off);
        actionNewAccount->setIcon(icon2);
        actionDefineAccountTypes = new QAction(MainWindowClass);
        actionDefineAccountTypes->setObjectName(QString::fromUtf8("actionDefineAccountTypes"));
        actionDeleteAccount = new QAction(MainWindowClass);
        actionDeleteAccount->setObjectName(QString::fromUtf8("actionDeleteAccount"));
        actionQuit = new QAction(MainWindowClass);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon3;
        icon3.addPixmap(QPixmap(QString::fromUtf8(":/icons/quit.svg")), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon3);
        actionProperties = new QAction(MainWindowClass);
        actionProperties->setObjectName(QString::fromUtf8("actionProperties"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setMargin(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        infoBar = new QFrame(centralWidget);
        infoBar->setObjectName(QString::fromUtf8("infoBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(infoBar->sizePolicy().hasHeightForWidth());
        infoBar->setSizePolicy(sizePolicy1);
        infoBar->setMinimumSize(QSize(0, 50));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(66, 66, 66, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(99, 99, 99, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(82, 82, 82, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(33, 33, 33, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(44, 44, 44, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        infoBar->setPalette(palette);
        infoBar->setAutoFillBackground(true);
        infoBar->setFrameShape(QFrame::NoFrame);
        infoBar->setFrameShadow(QFrame::Raised);
        iconInfo = new QLabel(infoBar);
        iconInfo->setObjectName(QString::fromUtf8("iconInfo"));
        iconInfo->setGeometry(QRect(5, 0, 41, 51));
        iconInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelTitle = new QLabel(infoBar);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setGeometry(QRect(55, 5, 451, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        labelTitle->setFont(font);
        labelDescr = new QLabel(infoBar);
        labelDescr->setObjectName(QString::fromUtf8("labelDescr"));
        labelDescr->setGeometry(QRect(55, 25, 451, 16));

        verticalLayout_2->addWidget(infoBar);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        sideMenu = new QListWidget(centralWidget);
        sideMenu->setObjectName(QString::fromUtf8("sideMenu"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(sideMenu->sizePolicy().hasHeightForWidth());
        sideMenu->setSizePolicy(sizePolicy2);
        sideMenu->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout->addWidget(sideMenu);

        contextView = new QStackedWidget(centralWidget);
        contextView->setObjectName(QString::fromUtf8("contextView"));
        contextView->setLineWidth(0);
        pageDashboard = new QWidget();
        pageDashboard->setObjectName(QString::fromUtf8("pageDashboard"));
        verticalLayout = new QVBoxLayout(pageDashboard);
        verticalLayout->setSpacing(0);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 1, 0, 0);
        contextView->addWidget(pageDashboard);
        pageAccounts = new QWidget();
        pageAccounts->setObjectName(QString::fromUtf8("pageAccounts"));
        verticalLayout_3 = new QVBoxLayout(pageAccounts);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setMargin(11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        treeAccounts = new QTreeView(pageAccounts);
        treeAccounts->setObjectName(QString::fromUtf8("treeAccounts"));
        treeAccounts->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_3->addWidget(treeAccounts);

        frameAccountButtons = new QFrame(pageAccounts);
        frameAccountButtons->setObjectName(QString::fromUtf8("frameAccountButtons"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frameAccountButtons->sizePolicy().hasHeightForWidth());
        frameAccountButtons->setSizePolicy(sizePolicy3);
        frameAccountButtons->setMinimumSize(QSize(0, 34));
        frameAccountButtons->setFrameShape(QFrame::NoFrame);
        frameAccountButtons->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frameAccountButtons);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setMargin(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        buttonNewAccount = new QPushButton(frameAccountButtons);
        buttonNewAccount->setObjectName(QString::fromUtf8("buttonNewAccount"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(buttonNewAccount->sizePolicy().hasHeightForWidth());
        buttonNewAccount->setSizePolicy(sizePolicy4);
        buttonNewAccount->setMinimumSize(QSize(80, 0));
        QIcon icon4;
        icon4.addPixmap(QPixmap(QString::fromUtf8(":/icons/add.svg")), QIcon::Normal, QIcon::Off);
        buttonNewAccount->setIcon(icon4);

        horizontalLayout_2->addWidget(buttonNewAccount);

        buttonEditAccount = new QPushButton(frameAccountButtons);
        buttonEditAccount->setObjectName(QString::fromUtf8("buttonEditAccount"));
        sizePolicy4.setHeightForWidth(buttonEditAccount->sizePolicy().hasHeightForWidth());
        buttonEditAccount->setSizePolicy(sizePolicy4);

        horizontalLayout_2->addWidget(buttonEditAccount);

        buttonDeleteAccount = new QPushButton(frameAccountButtons);
        buttonDeleteAccount->setObjectName(QString::fromUtf8("buttonDeleteAccount"));
        sizePolicy4.setHeightForWidth(buttonDeleteAccount->sizePolicy().hasHeightForWidth());
        buttonDeleteAccount->setSizePolicy(sizePolicy4);

        horizontalLayout_2->addWidget(buttonDeleteAccount);


        verticalLayout_3->addWidget(frameAccountButtons);

        contextView->addWidget(pageAccounts);
        pageJournal = new QWidget();
        pageJournal->setObjectName(QString::fromUtf8("pageJournal"));
        verticalLayout_4 = new QVBoxLayout(pageJournal);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setMargin(11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        frameJournalList = new QFrame(pageJournal);
        frameJournalList->setObjectName(QString::fromUtf8("frameJournalList"));
        frameJournalList->setFrameShape(QFrame::StyledPanel);
        frameJournalList->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frameJournalList);
        gridLayout->setSpacing(6);
        gridLayout->setMargin(11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelAccount = new QLabel(frameJournalList);
        labelAccount->setObjectName(QString::fromUtf8("labelAccount"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(labelAccount->sizePolicy().hasHeightForWidth());
        labelAccount->setSizePolicy(sizePolicy5);
        labelAccount->setScaledContents(false);

        gridLayout->addWidget(labelAccount, 0, 0, 1, 1);

        tableJournal = new QTableView(frameJournalList);
        tableJournal->setObjectName(QString::fromUtf8("tableJournal"));

        gridLayout->addWidget(tableJournal, 2, 0, 1, 2);

        comboAccount = new BurComboBox(frameJournalList);
        comboAccount->setObjectName(QString::fromUtf8("comboAccount"));
        sizePolicy1.setHeightForWidth(comboAccount->sizePolicy().hasHeightForWidth());
        comboAccount->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(comboAccount, 0, 1, 1, 1);


        verticalLayout_4->addWidget(frameJournalList);

        frameJournalDetail = new QFrame(pageJournal);
        frameJournalDetail->setObjectName(QString::fromUtf8("frameJournalDetail"));
        frameJournalDetail->setFrameShape(QFrame::StyledPanel);
        frameJournalDetail->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frameJournalDetail);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setMargin(11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelTrnDate = new QLabel(frameJournalDetail);
        labelTrnDate->setObjectName(QString::fromUtf8("labelTrnDate"));

        gridLayout_2->addWidget(labelTrnDate, 0, 0, 1, 1);

        labelMemo = new QLabel(frameJournalDetail);
        labelMemo->setObjectName(QString::fromUtf8("labelMemo"));

        gridLayout_2->addWidget(labelMemo, 4, 0, 1, 1);

        label_7 = new QLabel(frameJournalDetail);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 8, 0, 1, 1);

        labelRepDate = new QLabel(frameJournalDetail);
        labelRepDate->setObjectName(QString::fromUtf8("labelRepDate"));

        gridLayout_2->addWidget(labelRepDate, 0, 2, 1, 1);

        editTrnDate = new QDateEdit(frameJournalDetail);
        editTrnDate->setObjectName(QString::fromUtf8("editTrnDate"));
        editTrnDate->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        editTrnDate->setCalendarPopup(true);

        gridLayout_2->addWidget(editTrnDate, 0, 1, 1, 1);

        editRepDate = new QDateEdit(frameJournalDetail);
        editRepDate->setObjectName(QString::fromUtf8("editRepDate"));
        editRepDate->setCalendarPopup(true);

        gridLayout_2->addWidget(editRepDate, 0, 3, 1, 1);

        editMemo = new QLineEdit(frameJournalDetail);
        editMemo->setObjectName(QString::fromUtf8("editMemo"));

        gridLayout_2->addWidget(editMemo, 4, 1, 1, 5);

        labelValDate = new QLabel(frameJournalDetail);
        labelValDate->setObjectName(QString::fromUtf8("labelValDate"));

        gridLayout_2->addWidget(labelValDate, 0, 4, 1, 1);

        editValDate = new QDateEdit(frameJournalDetail);
        editValDate->setObjectName(QString::fromUtf8("editValDate"));
        editValDate->setCalendarPopup(true);

        gridLayout_2->addWidget(editValDate, 0, 5, 1, 1);

        labelTrnType = new QLabel(frameJournalDetail);
        labelTrnType->setObjectName(QString::fromUtf8("labelTrnType"));

        gridLayout_2->addWidget(labelTrnType, 3, 0, 1, 1);

        comboTrnType = new QComboBox(frameJournalDetail);
        comboTrnType->setObjectName(QString::fromUtf8("comboTrnType"));

        gridLayout_2->addWidget(comboTrnType, 3, 1, 1, 3);

        labelCategory = new QLabel(frameJournalDetail);
        labelCategory->setObjectName(QString::fromUtf8("labelCategory"));

        gridLayout_2->addWidget(labelCategory, 6, 0, 1, 1);

        lineEdit_2 = new QLineEdit(frameJournalDetail);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout_2->addWidget(lineEdit_2, 8, 2, 1, 1);

        comboCategory = new QComboBox(frameJournalDetail);
        comboCategory->setObjectName(QString::fromUtf8("comboCategory"));

        gridLayout_2->addWidget(comboCategory, 6, 1, 1, 5);


        verticalLayout_4->addWidget(frameJournalDetail);

        contextView->addWidget(pageJournal);
        pageCategories = new QWidget();
        pageCategories->setObjectName(QString::fromUtf8("pageCategories"));
        contextView->addWidget(pageCategories);
        pageRecurring = new QWidget();
        pageRecurring->setObjectName(QString::fromUtf8("pageRecurring"));
        contextView->addWidget(pageRecurring);
        pageReports = new QWidget();
        pageReports->setObjectName(QString::fromUtf8("pageReports"));
        contextView->addWidget(pageReports);

        horizontalLayout->addWidget(contextView);


        verticalLayout_2->addLayout(horizontalLayout);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 829, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuAccount = new QMenu(menuBar);
        menuAccount->setObjectName(QString::fromUtf8("menuAccount"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setIconSize(QSize(32, 32));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        mainToolBar->setFloatable(false);
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAccount->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionProperties);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuSettings->addAction(actionDefineCountries);
        menuSettings->addAction(actionDefineCurrencies);
        menuSettings->addSeparator();
        menuSettings->addAction(actionDefineTransactionTypes);
        menuSettings->addSeparator();
        menuSettings->addAction(actionDefineCategories);
        menuSettings->addSeparator();
        menuSettings->addAction(actionDefineAccountTypes);
        menuAccount->addAction(actionNewAccount);
        menuAccount->addSeparator();
        menuAccount->addAction(actionDeleteAccount);

        retranslateUi(MainWindowClass);

        contextView->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindowClass", "&New Database...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("MainWindowClass", "New Database", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDefineCountries->setText(QApplication::translate("MainWindowClass", "Define Countries...", 0, QApplication::UnicodeUTF8));
        actionDefineCurrencies->setText(QApplication::translate("MainWindowClass", "Define Currencies...", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindowClass", "Open Database...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindowClass", "Open Database", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDefineTransactionTypes->setText(QApplication::translate("MainWindowClass", "Define Transaction Types...", 0, QApplication::UnicodeUTF8));
        actionDefineCategories->setText(QApplication::translate("MainWindowClass", "Define Categories...", 0, QApplication::UnicodeUTF8));
        actionNewAccount->setText(QApplication::translate("MainWindowClass", "&New Account...", 0, QApplication::UnicodeUTF8));
        actionDefineAccountTypes->setText(QApplication::translate("MainWindowClass", "Define Account Types...", 0, QApplication::UnicodeUTF8));
        actionDeleteAccount->setText(QApplication::translate("MainWindowClass", "Delete Account...", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindowClass", "&Quit", 0, QApplication::UnicodeUTF8));
        actionProperties->setText(QApplication::translate("MainWindowClass", "Properties...", 0, QApplication::UnicodeUTF8));
        iconInfo->setText(QApplication::translate("MainWindowClass", "<Icon>", 0, QApplication::UnicodeUTF8));
        labelTitle->setText(QApplication::translate("MainWindowClass", "<Titel>", 0, QApplication::UnicodeUTF8));
        labelDescr->setText(QApplication::translate("MainWindowClass", "<Description>", 0, QApplication::UnicodeUTF8));
        buttonNewAccount->setText(QApplication::translate("MainWindowClass", "New Account", 0, QApplication::UnicodeUTF8));
        buttonEditAccount->setText(QApplication::translate("MainWindowClass", "Edit Account", 0, QApplication::UnicodeUTF8));
        buttonDeleteAccount->setText(QApplication::translate("MainWindowClass", "Delete Account", 0, QApplication::UnicodeUTF8));
        labelAccount->setText(QApplication::translate("MainWindowClass", "Account:", 0, QApplication::UnicodeUTF8));
        labelTrnDate->setText(QApplication::translate("MainWindowClass", "Transaction Date:", 0, QApplication::UnicodeUTF8));
        labelMemo->setText(QApplication::translate("MainWindowClass", "Memo:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindowClass", "Cheque No.:", 0, QApplication::UnicodeUTF8));
        labelRepDate->setText(QApplication::translate("MainWindowClass", "Reporting Date:", 0, QApplication::UnicodeUTF8));
        editTrnDate->setDisplayFormat(QApplication::translate("MainWindowClass", "MM/dd/yy", 0, QApplication::UnicodeUTF8));
        editRepDate->setDisplayFormat(QApplication::translate("MainWindowClass", "MM/dd/yy", 0, QApplication::UnicodeUTF8));
        labelValDate->setText(QApplication::translate("MainWindowClass", "Value Date:", 0, QApplication::UnicodeUTF8));
        editValDate->setDisplayFormat(QApplication::translate("MainWindowClass", "MM/dd/yy", 0, QApplication::UnicodeUTF8));
        labelTrnType->setText(QApplication::translate("MainWindowClass", "Transaction Type:", 0, QApplication::UnicodeUTF8));
        labelCategory->setText(QApplication::translate("MainWindowClass", "Category:", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindowClass", "&File", 0, QApplication::UnicodeUTF8));
        menuSettings->setTitle(QApplication::translate("MainWindowClass", "Settings", 0, QApplication::UnicodeUTF8));
        menuAccount->setTitle(QApplication::translate("MainWindowClass", "&Account", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
