/****************************************************************************
** Meta object code from reading C++ file 'definecountriesdialog.h'
**
** Created: Mon Dec 14 18:46:31 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/dialogs/definecountriesdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'definecountriesdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DefineCountriesDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x08,
      47,   22,   22,   22, 0x08,
      71,   22,   22,   22, 0x08,
      94,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DefineCountriesDialog[] = {
    "DefineCountriesDialog\0\0on_buttonBox_accepted()\0"
    "on_buttonBox_rejected()\0on_addButton_clicked()\0"
    "on_removeButton_clicked()\0"
};

const QMetaObject DefineCountriesDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DefineCountriesDialog,
      qt_meta_data_DefineCountriesDialog, 0 }
};

const QMetaObject *DefineCountriesDialog::metaObject() const
{
    return &staticMetaObject;
}

void *DefineCountriesDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DefineCountriesDialog))
        return static_cast<void*>(const_cast< DefineCountriesDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int DefineCountriesDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_buttonBox_accepted(); break;
        case 1: on_buttonBox_rejected(); break;
        case 2: on_addButton_clicked(); break;
        case 3: on_removeButton_clicked(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
