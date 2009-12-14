/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Dec 14 18:46:30 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      37,   11,   11,   11, 0x08,
      63,   11,   11,   11, 0x08,
      89,   11,   11,   11, 0x08,
     121,   11,   11,   11, 0x08,
     156,   11,   11,   11, 0x08,
     193,   11,   11,   11, 0x08,
     231,   11,   11,   11, 0x08,
     280,  275,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_actionNew_triggered()\0"
    "on_actionOpen_triggered()\0"
    "on_actionQuit_triggered()\0"
    "on_actionNewAccount_triggered()\0"
    "on_actionDeleteAccount_triggered()\0"
    "on_actionDefineCountries_triggered()\0"
    "on_actionDefineCurrencies_triggered()\0"
    "on_actionDefineTransactionTypes_triggered()\0"
    "item\0on_sideMenu_itemClicked(QListWidgetItem*)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

const QMetaObject *MainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_actionNew_triggered(); break;
        case 1: on_actionOpen_triggered(); break;
        case 2: on_actionQuit_triggered(); break;
        case 3: on_actionNewAccount_triggered(); break;
        case 4: on_actionDeleteAccount_triggered(); break;
        case 5: on_actionDefineCountries_triggered(); break;
        case 6: on_actionDefineCurrencies_triggered(); break;
        case 7: on_actionDefineTransactionTypes_triggered(); break;
        case 8: on_sideMenu_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
